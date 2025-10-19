import os
import sys

input_file = os.path.join(sys.path[0], 'rewardstudent.inp')
output_file = os.path.join(sys.path[0], 'rewardstudent.out')

reward = 0 # tổng số phần thưởng
student = 0 # tổng số học sinh

# D[r][s] là số cách mà s học sinh nhận r phần thưởng
D = None


def input():
    with open(input_file, 'r') as f:
        global reward, student
        reward, student = map(int, f.readline().split())


# Cách 1: sử dụng mảng hai chiều
def process_1():
    global D
    
    # Khởi tạo giá trị 0 cho toàn bảng quy hoạch
    D = [[0 for col in range(reward + 1)] for row in range(student + 1)]
    
    # Chỉ có 1 cách để 0 học sinh nhận 0 phần thưởng
    D[0][0] = 1

    # Duyệt hàng (số học sinh) bằng biến s trong phạm vi [1..student]
    for s in range(1, student + 1):
        # Trường hợp 1: số phần thưởng < số học sinh
        # Chỉ có r học sinh được nhận r phần thưởng

        # Duyệt cột (số phần thưởng) bằng biến r trong phạm vi [0..s - 1]
        for r in range(0, s):
            D[s][r] = D[r][r]
        
        # Trường hợp 2: số phần thưởng >= số học sinh
        # Trường hợp 2a: học sinh hạng chót sẽ không được nhận thưởng
        # Số cách chia thưởng là D[s - 1][r]

        # Trường hợp 2b: học sinh hạng chót vẫn được nhận thưởng
        # Số cách chia thưởng D[s][r] sẽ không thay đổi nếu ta bỏ bớt 1 phần thưởng của mỗi học sinh. Số phần thưởng tạm bỏ bớt là (r - s) 
        # Số cách chia thưởng là D[s][r - s]

        # Duyệt cột (số phần thưởng) bằng biến r trong phạm vi [s..reward]        
        for r in range(s, reward + 1):
            D[s][r] = D[s - 1][r] + D[s][r - s]


def output_1():
    with open(output_file, 'w') as f:            
        f.write(f'{D[student][reward]}')


def show_1():
    global D

    # In tiêu đề cột
    print(' ' * 8, end='')
    for col in range(reward + 1):
        print(f'{col:6}', end='')
    print()

    # In đường phân cách
    print(' ' * 8 + '-' * ((reward + 1) * 6))

    # Hàng
    for row in range(student + 1):
        print(f'{row:6} |', end='')
        for col in range(reward + 1):
            print(f'{D[row][col]:6}', end='')
        print()


# Cách 2: sử dụng mảng một chiều
L = list()

def process_2():
    global L
    L = [0 for _ in range(reward + 1)]
    L[0] = 1

    for s in range(1, student + 1):
        for r in range(s, reward + 1):
            L[r] = L[r] + L[r - s]


def output_2():
    global reward, L

    with open(output_file, 'w') as f:            
        f.write(f'{L[reward]}')


def show_2():
    global L

    # Tiêu đề cột
    print(' ' * 4, end='')
    for col in range(reward + 1):
        print(f'{col:4}', end='')
    
    print()

    # In đường phân cách
    print(' ' * 4 + '-' * ((reward + 1) * 4))

    # In giá trị
    print(f'{' ':2} |', end='')
    for col in range(reward + 1):
        print(f'{L[col]:4}', end='')
    
    print()


if __name__ == '__main__':
    input()
    
    process_1()
    show_1()
    output_1()
    
    # process_2()
    # output_2()
    # show_2()