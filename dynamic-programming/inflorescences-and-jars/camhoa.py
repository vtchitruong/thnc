import os
import sys

input_file = os.path.join(sys.path[0], 'camhoa.inp')
output_file = os.path.join(sys.path[0], 'camhoa.out')

k = 0  # số bó hoa
n = 0  # số lọ
values = []

# D[i][j] là tổng giá trị thẩm mỹ lớn nhất khi cắm i bó hoa đầu tiên vào j lọ hoa đầu tiên
# i: inflorescence (cụm hoa), j: jar (lọ)
D = []


def input():
    global k, n, values
    with open(input_file, 'r') as f:
        k, n = map(int, f.readline().split())

        values = [[0] * (n + 1) for _ in range(k + 1)]

        for i in range(1, k + 1):
            values[i][1:] = list(map(int, f.readline().split()))


def process():
    global k, n, values, D

    # Khởi tạo giá trị 0 cho toàn bảng quy hoạch D
    D = [[0 for j in range(n + 1)] for i in range(k + 1)]

    # Duyệt từng hàng i (inflorescence)
    for i in range(1, k + 1):
        # Duyệt từng cột j (jar)
        for j in range(1, n + 1):
            if i <= j:
                # TH1: lọ j không được chọn cắm
                j_not_chosen = D[i][j - 1]

                # TH2: lọ j được chọn cắm
                j_chosen = D[i - 1][j - 1] + values[i][j]

                # Lấy giá trị thẩm mỹ tốt nhất
                D[i][j] = max(j_not_chosen, j_chosen)


def output():
    global k, n, D

    # inflorescence
    # inflor[i] = j: chọn lọ j cho bó hoa i
    inflor = [0] * (k + 1)

    i = k
    j = n

    while i > 0 and j > 0:
        if i <= j and D[i][j] != D[i][j - 1]:
            # Chọn lọ j cho bó hoa i
            inflor[i] = j

            # Lùi về bó hoa liền trước
            i -= 1

            # Lùi về lọ liền trước
            j -= 1
        else:
            # Chỉ lùi về lọ liền trước
            j -= 1

    with open(output_file, 'w') as f:
        f.write(f'{D[k][n]}\n')

        for i in range(1, k + 1):
            f.write(f'{inflor[i]} ')


def show():
    for i in range(1, k + 1):
        for j in range(1, n + 1):
            print(f'{D[i][j]:>4}', end='')

        print()


if __name__ == '__main__':
    input()
    process()
    output()
    show()