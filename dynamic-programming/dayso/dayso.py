import os
import sys

input_file = os.path.join(sys.path[0], 'dayso1.inp')
output_file = os.path.join(sys.path[0], 'dayso1.out')

INF = float('inf')

n = K = 0
a = []
result = 0

# d[i] là điểm số lớn nhất khi người chơi dừng cuộc chơi tại vị trí i
d = []

def input():
    global n, K, a

    sys.stdin = open(input_file, 'r')
    data = sys.stdin.read().split()
    iterator = iter(data)

    n = int(next(iterator))
    K = int(next(iterator))
    
    a = [0] * (n + 1)
    
    for i in range(1, n + 1):
        x = int(next(iterator))
        a[i] = x
    

def process():
    global result

    # Khởi tạo mảng d
    d = [-INF] * (n + 1)
    d[0] = 0

    # Duyệt từng ô trong dãy số
    for i in range(1, n + 1):
        # Duyệt số bước nhảy
        for k in range(1, K + 1):
            if i - k >= 0:
                d[i] = max(d[i], d[i - k] + a[i])

        # Cập nhật điểm số tổng thể lớn nhất
        result = max(result, d[i])
    

def output():
    sys.stdout = open(output_file, 'w')
    
    print(result)


if __name__ == '__main__':
    input()
    process()
    output()