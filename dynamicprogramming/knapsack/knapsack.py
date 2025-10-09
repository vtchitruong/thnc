import os
import sys

input_file = os.path.join(sys.path[0], 'knapsack.inp')
output_file = os.path.join(sys.path[0], 'knapsack.out')

n = 0 # tổng số vật
weight_limit = 0 # giới hạn trọng lượng của balo

weight = [] # mảng lưu trọng lượng mỗi vật
value = [] # mảng lưu giá trị mỗi vật

# D[i][w] là tổng giá trị lớn nhất khi chọn một số vật nào đó trong phạm vi [0..i] mà tổng trọng lượng không vượt quá `w`.
D = []


def input():
    global n, weight_limit, weight, value

    with open(input_file) as f:
        n, weight_limit = map(int, f.readline().split())

        weight.append(0)
        value.append(0)
        for line in f.readlines():
            w, v = map(int, line.split())
            weight.append(w)
            value.append(v)


def process():
    global D

    # Khởi tạo giá trị 0 cho toàn bảng quy hoạch
    D = [[0 for col in range(weight_limit + 1)] for row in range(n + 1)]

    # Duyệt từng vật i trong phạm vi [1..n]
    for i in range(1, n + 1):
        # Duyệt từng giới hạn trọng lượng w trong phạm vi [1..weight_limit]
        for w in range(1, weight_limit + 1):
            # Giả sử không chọn vật i
            # Tổng giá trị các vật được chọn sẽ không thay đổi, tức vẫn là D[i - 1][w]
            D[i][w] = D[i - 1][w]

            # Nếu trọng lượng vật i không vượt quá giới hạn w
            if weight[i] <= w:
                # Xét xem giữa chọn và không chọn vật i, trường hợp nào làm cho tổng giá trị là lớn nhất
                D[i][w] = max(D[i][w], D[i - 1][w - weight[i]] + value[i])


def output():
    # Ngăn xếp chứa các vật được chọn
    item_stack = list()

    # Biến tạm wl dùng để lưu giới hạn trọng lượng
    wl = weight_limit

    # Biến tạm i dùng để lưu số thứ tự của vật
    i = n

    # Lặp cho đến khi i == 0 thì dừng
    while i:
        # Nếu tổng giá trị có sự thay đổi, nghĩa là vật i được chọn
        if not D[i][wl] == D[i - 1][wl]:
            # thì đẩy vật i vào ngăn xếp
            item_stack.append(i)

            # Lấy giới hạn trọng lượng còn lại sau khi đẩy vật i vào ngăn xếp
            wl = wl - weight[i]

        i -= 1

    with open(output_file, 'w') as f:
        f.write(f'{D[n][weight_limit]}\n')
        for idx, item in enumerate(reversed(item_stack)):
            line = f'{item} {weight[item]} {value[item]}'
            f.write(line) if idx == len(item_stack) - 1 else f.write(line + '\n')


def show():
    # In tiêu đề cột
    print(' ' * (6 + 2), end='')
    for c in range(weight_limit + 1):
        print(f'{c:>6}', end='')
    
    print()
    
    # In đường phân cách
    print(' ' * (6 + 2), end='')
    print('-' * ((weight_limit + 1) * 6))
    
    # In tiêu đề hàng và giá trị
    for r in range(n + 1):
        print(f'{r:>6} |', end='')
        for c in range(weight_limit + 1):
            print(f'{D[r][c]:>6}', end='')
        print()


if __name__ == '__main__':
    input()
    process()
    output()
    # show()