import os
import sys

input_file = os.path.join(sys.path[0], 'forest.inp')
output_file = os.path.join(sys.path[0], 'forest.out')

MAX = 1000

number_of_rows = 0
number_of_cols = 0
forest = []

# Ô xuất phát và ô kết thúc
start = []
finish = []

# Mảng trace dùng để đánh dấu và truy vết đường đi
trace = []

# Mảng lưu 4 hướng di chuyển: lên, xuống, trái, phải
steps = [(-1, 0), (1, 0), (0, -1), (0, 1)]


def input_data():  
    global number_of_rows, number_of_cols, forest

    with open(input_file, 'r') as f:
        number_of_rows, number_of_cols = list(map(int, f.readline().split()))
        forest = [line.strip() for line in f.readlines()]


def dfs(current):
    global MAX, finish, forest, trace, steps

    # Điều kiện dừng đệ quy DFS là nhà thám hiểm đã đến được bìa rừng
    border = (current[0] == 0 or current[0] == number_of_rows - 1 or 
              current[1] == 0 or current[1] == number_of_cols - 1)
    
    if border:
        # Cập nhật ô kết thúc
        finish = current
        return
    
    # Duyệt từng hướng đi
    for s in steps:
        # Lấy toạ độ của ô next
        next = [current[0] + s[0], current[1] + s[1]]

        # Nếu nhà thám hiểm vẫn còn trong bên trong phạm vi khu rừng
        # và ô next chưa duyệt và không có bẫy
        if 0 <= next[0] < number_of_rows and 0 <= next[1] < number_of_cols and trace[next[0]][next[1]] == -1 and forest[next[0]][next[1]] == 'O':
            # thì đánh dấu ô next bằng cách gộp toạ độ hàng và cột vào chung một giá trị                    
            trace[next[0]][next[1]] = current[1] * MAX + current[0]

            # Gọi đệ quy đối với ô next
            dfs(next)


def process():
    global forest, start, trace
    
    # Khởi tạo biến start là vị trí xuất phát của nhà thám hiểm
    for r, row_data in enumerate(forest):
        if 'E' in row_data:
            c = row_data.index('E')
            start = [r, c]
            break
    
    # Khởi tạo -1 cho toàn bộ mảng trace
    trace = [[-1 for col in range(number_of_cols)] for row in range(number_of_rows)]

    # Bắt đầu DFS
    dfs(start)


def output():
    global finish, trace

    # Dùng ngăn xếp để lưu đường đi kết quả
    path = list()
    
    # Nạp ô finish ở bìa rừng vào ngăn xếp
    path.append(finish)
    
    # Dựa vào mảng trace để truy vết các ô nằm trước ô finish
    while not trace[finish[0]][finish[1]] == -1:
        # Tách giá trị đã gộp ở dfs() thành hai thành phần toạ độ riêng lẻ
        r = trace[finish[0]][finish[1]] % MAX
        c = trace[finish[0]][finish[1]] // MAX

        # Đẩy toạ độ riêng lẻ vào ngăn xếp
        path.append([r, c])

        # Tiếp tục lùi ô finish
        finish = [r, c]

    with open(output_file, 'w') as f:
        result = '\n'.join([str(' '.join([str(number) for number in position])) for position in reversed(path)])    
        f.write(result)


if __name__ == '__main__':
    input_data()
    process() 
    output()