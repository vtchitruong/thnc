import os
import sys

input_file = os.path.join(sys.path[0], 'floydwarshall.inp')
output_file = os.path.join(sys.path[0], 'floydwarshal.out')

number_of_vertices = number_of_edges = start = finish = 0

# Ma trận kề lưu đồ thị
g = []

# trace[u][v] chứa đỉnh liền trước v trên đường đi ngắn nhất từ u đến v
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

    g = [[INF] * (number_of_vertices + 1) for _ in range(number_of_vertices + 1)]

    for u in range(1, number_of_vertices + 1):
        g[u][u] = 0

    for _ in range(number_of_edges):
        u = int(next(iterator))
        v = int(next(iterator))
        weight = int(next(iterator))

        g[u][v] = min(g[u][v], weight)


def process():
    global g, trace

    # Khởi tạo mảng truy vết trace
    trace = [[-1] * (number_of_vertices + 1) for _ in range(number_of_vertices + 1)]

    for u in range(1, number_of_vertices + 1):
        for v in range(1, number_of_vertices + 1):
            if g[u][v] != INF and u != v:
                trace[u][v] = u

    # Duyệt các đỉnh trung gian k
    for k in range(number_of_vertices + 1):
        # Duyệt từng cặp đỉnh u, v
        for u in range(number_of_vertices + 1):
            for v in range(number_of_vertices + 1):            
                # Nếu có thể đi u -> k -> v nhanh hơn so với u -> v
                if g[u][k] != INF and g[k][v] != INF and g[u][k] + g[k][v] < g[u][v]:                
                    # Thì cập nhật lại khoảng cách u -> v
                    g[u][v] = g[u][k] + g[k][v]

                    # Lưu vết đỉnh liền trước v trên đường đi u -> k -> v
                    trace[u][v] = trace[k][v]
   

def output():
    sys.stdout = open(output_file, 'w')

    # Trường hợp không tồn tại đường đi từ start đến finish
    if g[start][finish] == INF:    
        print(-1)
        return
    
    # Đường đi kết quả
    path = []

    fn = finish

    # Lần ngược từ finish về start bằng mảng trace
    while fn != start:    
        path.append(fn)
        fn = trace[start][fn]
    
    path.append(start)

    # In ra khoảng cách ngắn nhất từ start đến finish
    print(g[start][finish])

    # In ra đường đi ngắn nhất từ start đến finish
    output_path = ' '.join(map(str, reversed(path)))
    print(output_path)
    

if __name__ == '__main__':
    input()
    process()
    output()