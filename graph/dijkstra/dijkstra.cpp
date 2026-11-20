#include <iostream>
#include <vector>
#include <queue>
#include <stack>

#define input_file "dijkstra.inp"
#define output_file "dijkstra.out"

using namespace std;

typedef long long int lli;

int number_of_vertices, number_of_edges, start, finish;

// Danh sách kề lưu đồ thị
vector<vector<pair<int, lli>>> g;

// d[u] là khoảng cách ngắn nhất từ đỉnh start đến đỉnh u
vector<lli> d;

// trace[v] = u nghĩa là: liền trước đỉnh v là đỉnh u, tức u -> v
vector<int> trace;

const lli INF = 1e18;

void input()
{
    ios_base::sync_with_stdio(false);
    freopen(input_file, "r", stdin);

    cin >> number_of_vertices >> number_of_edges >> start >> finish;

    g.resize(number_of_vertices + 1);

    int u, v;
    lli weight;
    for (int i = 0; i < number_of_edges; ++i)
    {
        cin >> u >> v >> weight;
        g[u].push_back({v, weight});
    }
}

void process()
{
    // Khởi tạo mảng khoảng cách d
    d.assign(number_of_vertices + 1, INF);
    d[start] = 0;

    // Khởi tạo mảng truy vết trace
    trace.assign(number_of_vertices + 1, -1);

    // Hàng đợi ưu tiên lưu cặp {khoảng cách, đỉnh}, ưu tiên khoảng cách nhỏ nhất
    priority_queue<pair<lli, int>, vector<pair<lli, int>>, greater<pair<lli, int>>> q;
    q.push({0, start});

    // Trong khi q vẫn còn phần tử
    while (!q.empty())
    {
        // Lấy ra cặp {khoảng cách, đỉnh} có khoảng cách nhỏ nhất
        lli d_u = q.top().first;
        int u = q.top().second;
        q.pop();

        // Bỏ qua nếu đã tìm được đường đi ngắn hơn đến u trước đó
        if (d_u > d[u])
            continue;

        // Dừng thuật toán khi đã chốt được đường đi ngắn nhất đến đích
        if (u == finish)
            break;

        // Duyệt các đỉnh v kề với đỉnh u
        for (auto &edge : g[u])
        {
            // v là đỉnh kề với đỉnh u
            int v = edge.first;

            // w là trọng số của cạnh u -> v
            lli w = edge.second;

            // Nếu đường đi start -> u -> v nhanh hơn đường đi start -> v
            // tức đi qua u giúp rút ngắn khoảng cách đến v
            if (d[u] + w < d[v])
            {
                d[v] = d[u] + w;
                trace[v] = u;
                q.push({d[v], v});
            }
        }
    }
}

void output()
{
    freopen(output_file, "w", stdout);

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