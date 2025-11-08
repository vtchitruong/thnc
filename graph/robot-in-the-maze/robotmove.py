import os
import sys
import queue

input_file = os.path.join(sys.path[0], 'robotmove.inp')
output_file = os.path.join(sys.path[0], 'robotmove.out')

number_of_rows = 0
number_of_cols = 0
maze = []

# Ô xuất phát và ô kết thúc
start = []
finish = []

# Mảng trace dùng để đánh dấu và truy vết đường đi
trace = []


def input():
    global number_of_rows, number_of_cols, maze, start, finish

    with open(input_file, 'r') as f:
        number_of_rows, number_of_cols, s_row, s_col, f_row, f_col = map(int, f.readline().split())
        start = [s_row, s_col]
        finish = [f_row, f_col]

        lines = f.readlines()

        # Khởi tạo ma trận maze gồm toàn phần tử 0
        maze.append([])

        for line in lines:
            line = '0' +  line.strip()            
            maze.append(list(map(int, line)))


def process():
    global maze, trace

    # Khởi tạo giá trị 'N' cho toàn bộ mảng trace
    trace = [['N' for col in range(number_of_cols + 1)] for row in range(number_of_rows + 1)]
    
    # Ô start được đánh dấu bằng ký tự 'S'
    trace[start[0]][start[1]] = 'S'

    # Hàng đợi q chứa các ô cần duyệt
    q = queue.Queue()

    # Nạp ô start vào hàng đợi
    q.put(start)

    # Trong khi hàng đợi vẫn còn ô chờ duyệt
    while q:
        # Lấy ô ở đầu hàng đợi
        current = q.get()

        # Dừng vòng lặp khi ô sắp duyệt là ô kết thúc, tức đã đến đích
        if current == finish:
            return

        # Thử đi lên một ô
        if current[0] > 1 and maze[current[0] - 1][current[1]] == 0 and trace[current[0] - 1][current[1]] == 'N':
            # Lấy toạ độ của ô trên
            next = current.copy()
            next[0] -= 1

            # Đẩy vào hàng đợi
            q.put(next)

            # Đánh dấu đã duyệt bằng ký tự U: up
            trace[next[0]][next[1]] = 'U'

        # Thử đi xuống một ô
        if current[0] < number_of_rows and maze[current[0] + 1][current[1]] == 0 and trace[current[0] + 1][current[1]] == 'N':
            # Lấy toạ độ của ô dưới
            next = current.copy()
            next[0] += 1

            # Đẩy vào hàng đợi
            q.put(next)

            # Đánh dấu đã duyệt bằng ký tự D: down
            trace[next[0]][next[1]] = 'D'

        # Thử qua trái một ô
        if current[1] > 1 and maze[current[0]][current[1] - 1] == 0 and trace[current[0]][current[1] - 1] == 'N':
            # Lấy toạ độ của ô trái
            next = current.copy()
            next[1] -= 1

            # Đẩy vào hàng đợi
            q.put(next)

            # Đánh dấu đã duyệt bằng ký tự L: left
            trace[next[0]][next[1]] = 'L'

        # Thử qua phải một ô
        if current[1] < number_of_cols and maze[current[0]][current[1] + 1] == 0 and trace[current[0]][current[1] + 1] == 'N':
            # Lấy toạ độ của ô phải
            next = current.copy()
            next[1] += 1

            # Đẩy vào hàng đợi
            q.put(next)

            # Đánh dấu đã duyệt bằng ký tự R: right
            trace[next[0]][next[1]] = 'R'


def output():
    global start, finish, trace

    # Dùng ngăn xếp để lưu đường đi kết quả
    path = list()

    # Nếu tồn tại đường đi đến ô finish thì mới bắt đầu cho ô finish lùi
    if trace[finish[0]][finish[1]] != 'N':
        # Dựa vào mảng trace để truy vết các ô nằm trước ô finish
        while not trace[finish[0]][finish[1]] == 'S':
            # Đẩy ô finish vào ngăn xếp
            path.append(finish.copy())

            # Tiếp tục lùi ô finish
            direction= trace[finish[0]][finish[1]]
            if direction== 'U':
                finish[0] += 1
            elif direction== 'D':
                finish[0] -= 1
            elif direction== 'L':
                finish[1] += 1
            elif direction== 'R':
                finish[1] -= 1
        
        # Đẩy ô start vào ngăn xếp
        path.append(start)
    
    with open(output_file, 'w') as f:
        if not path:
            f.write('-1')
        else:
            f.writelines([f'{path[i][0]} {path[i][1]}\n' for i in range(len(path) - 1, 0, -1)])
            f.write(f'{path[0][0]} {path[0][1]}')


if __name__ == '__main__':
    input()
    process()
    output()