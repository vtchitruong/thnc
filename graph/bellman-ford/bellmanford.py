import os
import sys

input_file = os.path.join(sys.path[0], 'bellmanford2.inp')
output_file = os.path.join(sys.path[0], 'bellmanford2.out')

number_of_vertices = number_of_edges = start = finish = 0

# Danh sách lưu cạnh của đồ thị
g = []

# d[v] là khoảng cách ngắn nhất từ đỉnh start đến đỉnh v
d = []

# trace[v] = u nghĩa là: liền trước đỉnh v là đỉnh u, tức u -> v
trace = []

negative_cycle = False

INF = 10 ** 18

def input():
    global number_of_vertices, number_of_edges, start, finish, g

    sys.stdin = open(input_file, 'r')

    # Đọc toàn bộ dữ liệu vào bộ nhớ đệm và tách thành các token
    data = sys.stdin.read().split()

    iterator = iter(data)

    number_of_vertices = int(next(iterator))
    number_of_edges = int(next(iterator))
    start = int(next(iterator))
    finish = int(next(iterator))

    for _ in range(number_of_edges):
        u = int(next(iterator))
        v = int(next(iterator))
        weight = int(next(iterator))

        g.append((u, v, weight))


def process():
    global d, trace, negative_cycle

    # Khởi tạo mảng khoảng cách d
    d = [INF] * (number_of_vertices + 1)
    d[start] = 0

    # Khởi tạo mảng truy vết trace
    trace = [-1] * (number_of_vertices + 1)

    # Bước 1: Lặp tối đa (v - 1) lần để cập nhật khoảng cách
    for i in range(number_of_vertices):    
        updated = False

        for u, v, weight in g:
            # Chỉ xét các cạnh xuất phát từ đỉnh u đã có đường đi từ đỉnh start
            if d[u] != INF and d[u] + weight < d[v]:            
                d[v] = d[u] + weight
                trace[v] = u
                updated = True

        # Dừng sớm nếu đường đi đã ổn định, không còn cập nhật mới
        if not updated:
            break
    
    # Bước 2: Duyệt toàn bộ các cạnh ở lần lặp thứ v để phát hiện chu trình âm
    for u, v, weight in g:
        # Nếu khoảng cách vẫn tiếp tục giảm thì có chu trình âm
        if d[u] != INF and d[u] + weight < d[v]:
            negative_cycle = True
            return


def output():
    sys.stdout = open(output_file, 'w')

    # Trường hợp tồn tại chu trình âm
    if negative_cycle:
        print(-2)
        return
    
    # Trường hợp không tồn tại đường đi từ start đến finish
    if d[finish] == INF:
        print(-1)
        return
    
    # Đường đi kết quả
    path = []

    fn = finish

    # Lần ngược từ finish về start bằng mảng trace
    while fn != start:
        path.append(fn)
        fn = trace[fn]
    
    path.append(start)

    # In ra khoảng cách ngắn nhất từ start đến finish
    print(d[finish])

    # In ra đường đi ngắn nhất từ start đến finish
    output_path = ' '.join(map(str, reversed(path)))
    print(output_path)


if __name__ == '__main__':
    input()
    process()
    output()