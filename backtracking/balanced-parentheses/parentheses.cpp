#include <iostream>

#define input_file "parentheses1.inp"
#define output_file "parentheses1.out"

using namespace std;

int n;

// biến lưu một chuỗi ngoặc hoàn chỉnh
char s[29];


void input()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen(input_file, "r", stdin);

    cin >> n;
}


void backtracking(int i, int open, int close)
{
    // Nếu đã đủ số lượng ngoặc
    if (close == n && open == n)
    {
        // thì đặt ký tự '\0' để kết thúc chuỗi
        s[i] = '\0';
        cout << s << '\n';
        return;
    }

    // Nếu chưa đủ số lượng ngoặc mở 
    if (open < n)
    {
        // thì mở ngoặc tại vị trí i
        s[i] = '(';

        // Ứng với i, gọi đệ quy để mở ngoặc tại vị trí i + 1 cho đủ số lượng
        backtracking(i + 1, open + 1, close);
    }

    // Nếu chưa đủ số lượng đóng ngoặc
    if (close < open)
    {
        // thì đóng ngoặc tại vị trí i
        s[i] = ')';

        // Ứng với i, gọi đệ quy để đóng ngoặc tại vị trí i + 1 cho đủ số lượng
        backtracking(i + 1, open, close + 1);
    }
}


void process_output()
{
    freopen(output_file, "w", stdout);

    backtracking(0, 0, 0);
}


int main()
{
    input();
    process_output();

    return 0;
}