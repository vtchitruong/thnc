#include <iostream>

#define input_file "ab1.inp"
#define output_file "ab1.out"

using namespace std;

int n;

// biến lưu chuỗi hoàn chỉnh
string s;


void input()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen(input_file, "r", stdin);

    cin >> n;
}


void backtracking(int i, char previous)
{
    // Nếu đã đủ số lượng ký tự
    if (i == n)
    {
        // thì đặt ký tự '\0' để kết thúc chuỗi
        s[i] = '\0';
        cout << s << '\n'; 
        return;
    }

    // Gán A cho vị trí i
    s[i] = 'A';

    // Ứng với i, gọi đệ quy để chuẩn bị gán cho vị trí i + 1
    backtracking(i + 1, 'A');

    // Nếu ký tự liền trước khác B
    if (previous != 'B')
    {
        // Gán B cho vị trí i
        s[i] = 'B';

        // Gọi đệ quy để chuẩn bị gán cho vị trí i + 1
        backtracking(i + 1, 'B');
    }
}


void process_output()
{
    freopen(output_file, "w", stdout);

    // Khởi tạo chuỗi s gồm n ký tự
    s.assign(n, '_');

    backtracking(0, '?');
}


int main()
{
    input();
    process_output();

    return 0;
}