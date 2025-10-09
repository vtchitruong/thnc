import os
import sys
from collections import deque

input_file = os.path.join(sys.path[0], 'lis.inp')
output_file = os.path.join(sys.path[0], 'lis.out')

n = 0
A = []

# D[i] là độ dài dài nhất của dãy con [0..i]
D = []

# Mảng trace dùng để truy vết kết nối của các phần tử trong dãy con
# trace[i] = j nghĩa là trước phần tử `A[i]` là phần tử `A[j]`.
trace = []


def input():
    with open(input_file) as f:
        global n
        n = int(f.readline())

        global A    
        A = list(map(int, f.readline().split()))


def process():    
    global D, trace
    
    # Khởi tạo giá trị 1 cho toàn bộ bảng quy hoạch D, nghĩa là độ dài dài nhất là 1
    D = [1 for _ in range(n)]

    # Khởi tạo giá trị -1 cho toàn mảng trace, nghĩa là chưa có kết nối nào
    trace = [-1 for _ in range(n)]

    # Duyệt từng phần tử A[i] trong phạm vi [1..n - 1]
    for i in range(1, n):
        # Duyệt từng phần tử A[j] trong dãy con [0..i - 1]
        for j in range(i):
            # Nếu A[i] vẫn bảo đảm cho dãy con của A[j] tăng dần
            if A[j] < A[i]: # if increasing
                
                # D[j] + 1 là độ dài dài nhất của dãy con [0..j] cộng thêm 1 phần tử (là A[i])
                # D[i] là độ dài dài nhất của dãy con [0..i]
                # Nếu vẫn bảo đảm độ dài là dài nhất: D[j] + 1 > D[i]
                if D[j] + 1 > D[i]:
                    # thì ghi nhận độ dài dài nhất mới
                    D[i] = D[j] + 1

                    # và ghi nhận kết nối A[i] với A[j]
                    trace[i] = j


def output():
    # Tìm vị trí của phần tử trong mảng D lưu độ dài dài nhất, gọi là finish
    max_length = max(D)
    finish = D.index(max_length)

    # Dùng ngăn xếp để lưu các phần tử của dãy con dài nhất cần tìm
    sub_seq = deque() #subsequence
    while not trace[finish] == -1:
        # Đẩy phần tử A[finish] vào ngăn xếp
        sub_seq.append(A[finish])

        # Thực hiện truy ngược, lấy vị trí finish mới
        finish = trace[finish]
    
    # Đẩy phần tử đầu tiên của dãy con dài nhất vào ngăn xếp
    sub_seq.append(A[finish])

    with open(output_file, 'w') as f:
        f.write(f'{max_length}\n')
        
        s = ' '.join([str(e) for e in reversed(sub_seq)])        
        f.write(s)


def show():
    # In tiêu đề cột
    print(' ' * (6 + 2), end='')
    
    for col in range(n):
        print(f'{col:>6}', end='')
    print()
    
    # In đường phân cách
    print(' ' * (6 + 2), end='')
    print('-' * (n * 6))
    
    # In mảng a
    print(f'{'a |':>8}', end='')
    for col in range(n):
        print(f'{A[col]:>6}', end='')
    print()
    
    # In mảng d
    print(f'{'d |':>8}', end='')
    for col in range(n):
        print(f'{D[col]:>6}', end='')
    print()
    
    # In mảng trace
    print(f'{'trace |':>8}', end='')
    for col in range(n):
        print(f'{trace[col]:>6}', end='')
    print()


if __name__ == '__main__':
    input()
    process()
    # output()
    show()