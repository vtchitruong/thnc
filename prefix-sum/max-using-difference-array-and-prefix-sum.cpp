#include <iostream>
#include <vector>

using namespace std;

long process(int n, vector<vector<int>> queries)
{
    // Khởi tạo mảng a gồm n + 1 phần tử
    vector<long> a(n + 1, 0);

    // Duyệt từng truy vấn
    for (int i = 0; i < queries.size(); ++i)
    {
        int left = queries[i][0];
        int right = queries[i][1];
        int k = queries[i][2];

        // Đánh dấu vị trí bắt đầu cộng
        // Giá trị tại vị trí bắt đầu này sẽ ảnh hưởng đến mọi vị trí >= left
        a[left] += k;

        // Đánh dấu vị trí kết thúc cộng
        // Việc này giúp ngăn giá trị +k lan sang các vị trí > right
        if (right + 1 < n + 1)
            a[right + 1] -= k;
    }

    long max_value = 0;
    long prefix_sum = a[0];

    // Duyệt và khôi phục mảng a
    for (int i = 1; i < n + 1; ++i)
    {
        // Cộng dồn để lấy giá trị thực của phần tử tại vị trí i
        prefix_sum += a[i];

        // Cập nhật giá trị lớn nhất trong mảng
        if (prefix_sum > max_value)
            max_value = prefix_sum;
    }

    return max_value;
}

int main()
{
    int n = 10;
    vector<vector<int>> queries = {{1, 5, 3}, {4, 8, 7}, {6, 9, 1}};

    long res = process(n, queries);
    cout << res;

    return 0;
}