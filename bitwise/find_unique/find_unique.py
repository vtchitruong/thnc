from functools import reduce
from operator import xor

Array = [2, 3, 5, 5, 2, 4, 3]


# Cách 1: dùng vòng lặp và XOR dồn từng phần tử
def find_unique(A):
    # Khởi tạo phần tử duy nhất bằng 0 vì x ^ 0 = x
    unique_element = 0

    # Duyệt từng phần tử trong mảng A
    for a in A:
        unique_element ^= a

    return unique_element


# Cách 2: dùng hàm reduce()
def find_unique_2(A):
    return reduce(xor, A, 0)


if __name__ == '__main__':
    print(f'Mảng ban đầu: {Array}')

    unique = find_unique(Array)
    print(f'Phần tử duy nhất: {unique}')

    unique_2 = find_unique_2(Array)
    print(f'Phần tử duy nhất: {unique_2}')