#include <iostream>
#include <vector>
#include <stack>

#define input_file "forest.inp"
#define output_file "forest.out"

using namespace std;

const int MAX = 1000;

int number_of_rows, number_of_cols;
vector<string> forest;

// Ô xuất phát và ô kết thúc
pair<int, int> start, finish;

// Mảng trace dùng để đánh dấu và truy vết đường đi
vector<vector<int>> trace;

// Mảng lưu 4 hướng di chuyển: lên, xuống, trái, phải
vector<pair<int, int>> steps = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};


void input()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen(input_file, "r", stdin);

    cin >> number_of_rows >> number_of_cols;

    // Đọc từng hàng và đưa vào mảng forest
    string row;
    for (int r = 0; r < number_of_rows; ++r)
    {
        cin >> row;
        forest.push_back(row);
    }
}


void dfs(pair<int, int> current)
{
    // Điều kiện dừng đệ quy DFS là nhà thám hiểm đã đến được bìa rừng
    bool border =  (current.first == 0 || current.first == number_of_rows - 1 ||
                    current.second == 0 || current.second == number_of_cols - 1);
    
    if (border)
    {
        // Cập nhật ô kết thúc
        finish.first = current.first;
        finish.second = current.second;
        return;
    }

    pair<int, int> next;

    // Duyệt từng hướng đi
    for (int s = 0; s < 4; ++s)
    {
        // Lấy toạ độ của ô next
        next.first = current.first + steps[s].first;
        next.second = current.second + steps[s].second;

        // Nếu nhà thám hiểm vẫn còn trong bên trong phạm vi khu rừng
        // và ô next chưa duyệt và không có bẫy
        if (next.first >= 0 && next.first < number_of_rows && next.second >= 0 && next.second < number_of_cols
            && trace[next.first][next.second] == -1 && forest[next.first][next.second] == 'O')
        {
            // thì đánh dấu ô next bằng cách gộp toạ độ hàng và cột vào chung một giá trị
            trace[next.first][next.second] = current.second * MAX + current.first;

            // Gọi đệ quy đối với ô next
            dfs(next);
        }
    }
}


void process()
{
    // Khởi tạo biến start là vị trí xuất phát của nhà thám hiểm
    for (int r = 0; r < number_of_rows; r++)
    {
        int c = forest[r].find('E');

        if (c != string::npos)
        {
            start.first = r;
            start.second = c;
            break;
        }
    }

    // Khởi tạo -1 cho toàn bộ mảng trace
    trace.resize(number_of_rows, vector<int>(number_of_cols, -1));

    // Bắt đầu DFS
    dfs(start);
}


void output()
{
    // Dùng ngăn xếp để lưu đường đi kết quả
    stack<pair<int, int>> path;

    // Nạp ô finish ở bìa rừng vào ngăn xếp
    path.push(finish);

    // Dựa vào mảng trace để truy vết các ô nằm trước ô finish
    while (trace[finish.first][finish.second] != -1)
    {
        // Tách giá trị đã gộp ở dfs() thành hai thành phần toạ độ riêng lẻ
        int r = trace[finish.first][finish.second] % MAX;
        int c = trace[finish.first][finish.second] / MAX;

        // Đẩy toạ độ riêng lẻ vào ngăn xếp
        path.push({r, c});

        // Tiếp tục lùi ô finish
        finish.first = r;
        finish.second = c;
    }

    freopen(output_file, "w", stdout);

    while (!path.empty())
    {
        cout << path.top().first << ' ' << path.top().second;
        path.pop();
        if (path.size() != 0) cout << '\n';
    }
}


int main()
{
    input();
    process();
    output();   

    return 0;
}