import os
import sys
import heapq

input_file = os.path.join(sys.path[0], 'dijkstra.inp')
output_file = os.path.join(sys.path[0], 'dijkstra.out')

number_of_vertices = number_of_edges = start = finish = 0

# Danh sách kề lưu đồ thị
g = []

# d[u] là khoảng cách ngắn nhất từ đỉnh start đến đỉnh u
d = []

# trace[v] = u nghĩa là: liền trước đỉnh v là đỉnh u, tức u -> v
trace = []

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

    g = [[] for _ in range(number_of_vertices + 1)]

    for i in range(number_of_edges):
        u = int(next(iterator))
        v = int(next(iterator))
        weight = int(next(iterator))

        g[u].append((v, weight))
    

def process():
    global d, trace

    # Khởi tạo mảng khoảng cách d
    d = [INF] * (number_of_vertices + 1)
    d[start] = 0

    # Khởi tạo mảng truy vết trace
    trace = [-1] * (number_of_vertices + 1)

    # Hàng đợi ưu tiên lưu cặp khoảng cách, đỉnh, ưu tiên khoảng cách nhỏ nhất
    q = [(0, start)]

    # Trong khi q vẫn còn phần tử
    while q:
        # Lấy ra cặp khoảng cách, đỉnh có khoảng cách nhỏ nhất
        d_u, u = heapq.heappop(q)

        # Bỏ qua nếu đã tìm được đường đi ngắn hơn đến u trước đó
        if d_u > d[u]:
            continue

        # Dừng thuật toán khi đã chốt được đường đi ngắn nhất đến đích
        if u == finish:
            break

        # Duyệt các đỉnh v kề với đỉnh u
        for v, w in g[u]:
            # Nếu đường đi start -> u -> v nhanh hơn đường đi start -> v
            # tức đi qua u giúp rút ngắn khoảng cách đến v
            if d[u] + w < d[v]:
                d[v] = d[u] + w
                trace[v] = u
                heapq.heappush(q, (d[v], v))


def output():
    sys.stdout = open(output_file, 'w')

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