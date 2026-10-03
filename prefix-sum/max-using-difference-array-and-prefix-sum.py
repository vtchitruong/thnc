def process(n, queries):
    # Khởi tạo mảng a gồm n + 1 phần tử
    a = [0] * (n + 1)

    # Duyệt từng truy vấn
    for i in range(len(queries)):
        left = queries[i][0]
        right = queries[i][1]
        k = queries[i][2]

        # Đánh dấu vị trí bắt đầu cộng
        # Giá trị tại vị trí bắt đầu này sẽ ảnh hưởng đến mọi vị trí >= left
        a[left] += k

        # Đánh dấu vị trí kết thúc cộng
        # Việc này giúp ngăn giá trị +k lan sang các vị trí > right
        if right + 1 < n + 1:
            a[right + 1] -= k
    
    max_value = 0
    prefix_sum = a[0]

    # Duyệt và khôi phục mảng a
    for i in range(1, n + 1):    
        # Cộng dồn để lấy giá trị thực của phần tử tại vị trí i
        prefix_sum += a[i]

        # Cập nhật giá trị lớn nhất trong mảng
        if prefix_sum > max_value:
            max_value = prefix_sum
    
    return max_value


if __name__ == '__main__':
    n = 10
    queries = [[1, 5, 3], [4, 8, 7], [6, 9, 1]]

    res = process(n, queries)
    print(res)
