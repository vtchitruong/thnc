#include <iostream>
#include <vector>
#include <algorithm>

#define input_file "dayso1.inp"
#define output_file "dayso1.out"

using namespace std;

const int INF = 1e9;

int n, K;
vector<int> a;
int result;

// d[i] là điểm số lớn nhất khi người chơi dừng cuộc chơi tại vị trí i
vector<int> d;

void input()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen(input_file, "r", stdin);

    cin >> n >> K;

    a.resize(n + 1, 0);

    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i];
    }
}

void process()
{
    // Khởi tạo mảng d
    d.resize(n + 1, -INF);
    d[0] = 0;

    // Duyệt từng ô trong dãy số
    for (int i = 1; i <= n; ++i)
    {
        // Duyệt số bước nhảy
        for (int k = 1; k <= K; ++k)
        {
            if (i - k >= 0)
            {
                d[i] = max(d[i], d[i - k] + a[i]);
            }
        }

        // Cập nhật điểm số tổng thể lớn nhất
        result = max(result, d[i]);
    }
}

void output()
{
    freopen(output_file, "w", stdout);

    cout << result;
}

int main()
{
    input();
    process();
    output();

    return 0;
}