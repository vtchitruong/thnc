#include <iostream>
#include <vector>
#include <stack>

#define input_file "floydwarshall.inp"
#define output_file "floydwarshal.out"

using namespace std;

typedef long long int lli;

int number_of_vertices, number_of_edges, start, finish;

// Ma trận kề lưu đồ thị
vector<vector<lli>> g;

// trace[u][v] chứa đỉnh liền trước v trên đường đi ngắn nhất từ u đến v
vector<vector<int>> trace;

const lli INF = 1e18;

void input()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen(input_file, "r", stdin);

    cin >> number_of_vertices >> number_of_edges >> start >> finish;

    g.assign(number_of_vertices + 1, vector<lli>(number_of_vertices + 1, INF));

    for (int u = 1; u <= number_of_vertices; ++u)
        g[u][u] = 0;

    int u, v;
    lli weight;
    for (int i = 0; i < number_of_edges; ++i)
    {
        cin >> u >> v >> weight;
        g[u][v] = min(g[u][v], weight);
    }
}

void process()
{
    // Khởi tạo mảng truy vết trace
    trace.assign(number_of_vertices + 1, vector<int>(number_of_vertices + 1, -1));

    for (int u = 1; u <= number_of_vertices; ++u)
    {
        for (int v = 1; v <= number_of_vertices; ++v)
        {
            if (g[u][v] != INF && u != v)
                trace[u][v] = u;
        }
    }

    // Duyệt các đỉnh trung gian k
    for (int k = 1; k <= number_of_vertices; ++k)
    {
        // Duyệt từng cặp đỉnh u, v
        for (int u = 1; u <= number_of_vertices; ++u)
        {
            for (int v = 1; v <= number_of_vertices; ++v)
            {
                // Nếu có thể đi u -> k -> v nhanh hơn so với u -> v
                if (g[u][k] != INF && g[k][v] != INF && g[u][k] + g[k][v] < g[u][v])
                {
                    // Thì cập nhật lại khoảng cách u -> v
                    g[u][v] = g[u][k] + g[k][v];

                    // Lưu vết đỉnh liền trước v trên đường đi u -> k -> v
                    trace[u][v] = trace[k][v];
                }
            }
        }
    }
}

void output()
{
    freopen(output_file, "w", stdout);

    // Trường hợp không tồn tại đường đi từ start đến finish
    if (g[start][finish] == INF)
    {
        cout << -1;
        return;
    }

    // Đường đi kết quả
    stack<int> path;

    int fn = finish;

    while (fn != start)
    {
        path.push(fn);
        fn = trace[start][fn];
    }

    path.push(start);

    // In ra khoảng cách ngắn nhất từ start đến finish
    cout << g[start][finish] << '\n';

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