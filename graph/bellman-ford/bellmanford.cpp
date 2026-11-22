#include <iostream>
#include <vector>
#include <stack>

#define input_file "bellmanford2.inp"
#define output_file "bellmanford2.out"

using namespace std;

typedef long long int lli;

// Cấu trúc cạnh trong đồ thị
struct edge
{
    int u, v;
    lli w;
};

int number_of_vertices, number_of_edges, start, finish;

// Danh sách lưu cạnh của đồ thị
vector<edge> g;

// d[v] là khoảng cách ngắn nhất từ đỉnh start đến đỉnh v
vector<lli> d;

// trace[v] = u nghĩa là: liền trước đỉnh v là đỉnh u, tức u -> v
vector<int> trace;

bool negative_cycle = false;

const lli INF = 1e18;

void input()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen(input_file, "r", stdin);

    cin >> number_of_vertices >> number_of_edges >> start >> finish;

    int u, v;
    lli weight;

    for (int i = 0; i < number_of_edges; ++i)
    {
        cin >> u >> v >> weight;
        g.push_back({u, v, weight});
    }
}

void process()
{
    // Khởi tạo mảng khoảng cách d
    d.assign(number_of_vertices + 1, INF);
    d[start] = 0;

    // Khởi tạo mảng truy vết trace
    trace.assign(number_of_vertices + 1, -1);

    // Bước 1: Lặp tối đa (v - 1) lần để cập nhật khoảng cách
    for (int i = 0; i < number_of_vertices; ++i)
    {
        bool updated = false;

        for (const auto &edge : g)
        {
            int u = edge.u;
            int v = edge.v;
            lli weight = edge.w;

            // Chỉ xét các cạnh xuất phát từ đỉnh u đã có đường đi từ đỉnh start
            if (d[u] != INF && d[u] + weight < d[v])
            {
                d[v] = d[u] + weight;
                trace[v] = u;
                updated = true;
            }
        }

        // Dừng sớm nếu đường đi đã ổn định, không còn cập nhật mới
        if (!updated)
            break;
    }

    // Bước 2: Duyệt toàn bộ các cạnh ở lần lặp thứ v để phát hiện chu trình âm
    for (const auto &edge : g)
    {
        int u = edge.u;
        int v = edge.v;
        lli weight = edge.w;

        // Nếu khoảng cách vẫn tiếp tục giảm thì có chu trình âm
        if (d[u] != INF && d[u] + weight < d[v])
        {
            negative_cycle = true;
            return;
        }
    }
}

void output()
{
    freopen(output_file, "w", stdout);

    // Trường hợp tồn tại chu trình âm
    if (negative_cycle)
    {
        cout << -2;
        return;
    }

    // Trường hợp không tồn tại đường đi từ start đến finish
    if (d[finish] == INF)
    {
        cout << -1;
        return;
    }

    // Đường đi kết quả
    stack<int> path;

    int fn = finish;

    // Lần ngược từ finish về start bằng mảng trace
    while (fn != start)
    {
        path.push(fn);
        fn = trace[fn];
    }

    path.push(start);

    // In ra khoảng cách ngắn nhất từ start đến finish
    cout << d[finish] << '\n';

    // In ra đường đi ngắn nhất từ start đến finish
    while (!path.empty())
    {
        cout << path.top() << (path.size() > 1 ? " " : "");
        path.pop();
    }
}

int main()
{
    input();
    process();
    output();

    return 0;
}