import os
import sys

input_file = os.path.join(sys.path[0], 'candypack1.inp')
output_file = os.path.join(sys.path[0], 'candypack1.out')

n = 0
m = 0

pack = [] # pack[i] là số kẹo của gói thứ i

# D[candy_amount] là số thứ tự của gói được chọn để đạt được candy_amount kẹo và là nhỏ nhất
D = []


def input():
    global n, m, pack

    with open(input_file, 'r') as f:
        n, m = map(int, f.readline().split())

        # Gói thứ 0 không có kẹo
        pack = [0]
        some_packs = list(map(int, f.readline().split()))
        pack.extend(some_packs)


def process():
    global D

    # Khởi tạo giá trị vô cực cho toàn bảng quy hoạch
    D = [float('inf')] * (m + 1)

    # Không có gói nào được chọn cho D[candy_amount = 0]
    D[0] = 0

    # Duyệt số kẹo cần lấy từ 1 đến m
    for candy_amount in range(1, m + 1):
        # Duyệt từng gói từ 1 đến n
        for i in range(1, n + 1):
            # Số kẹo của gói thứ i phải ít hơn số candy_amount kẹo đang xét
            if pack[i] <= candy_amount:
                # D[candy_amount - pack[i]] là số thứ tự của gói nào đó trước khi chọn gói i
                if D[candy_amount - pack[i]] < i:
                    # Đánh dấu chọn gói i để đạt được candy_amount kẹo
                    D[candy_amount] = i

                    # Thoát vòng lặp i ngay khi tìm được gói i đầu tiên nhằm thoả yêu cầu ưu tiên chọn gói có số thứ tự nhỏ nhất
                    break


def output():
    global D, m

    # ngăn xếp chứa các gói được chọn
    chosen_packs = []

    # Nếu D[m] là vô cực thì không tìm được lời giải
    # Ngược lại, thì thực hiện truy ngược từ D[m] về đầu mảng
    if D[m] != int(1e12):
        # Số kẹo còn lại dùng để truy ngược
        remaining_amount = m

        # Trong khi vẫn còn kẹo để xét
        while remaining_amount > 0:
            # Nạp số thứ tự của gói được chọn vào chosen_packs
            chosen_packs.append(D[remaining_amount])

            # Trừ đi số kẹo của gói vừa nạp vào
            remaining_amount -= pack[chosen_packs[-1]]

    with open(output_file, 'w') as f:
        if len(chosen_packs) == 0:
            f.write(-1)
        else:
            f.write(' '.join(map(str, chosen_packs[::-1])))


# Hàm in ra bảng quy hoạch
def show():
    global D, m

    print(f'candy_amount | D[candy_amount]')

    for i in range(1, m + 1):
        print(f'{i:>12} | ', end='')

        print('INF' if D[i] == float('inf') else D[i])


if __name__ == '__main__':
    input()
    process()
    output()

    # show()