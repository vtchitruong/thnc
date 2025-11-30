#include <iostream>
#include <math.h>

#define input_file "ternary1.inp"
#define output_file "ternary1.out"

using namespace std;

int n;

// biến lưu một chuỗi tam phân hoàn chỉnh
string s;

// biến lưu toàn bộ output
string result = "";


void input()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen(input_file, "r", stdin);

    cin >> n;
}


void backtracking(int i)
{
    // Nếu chuỗi đã đủ số ký tự 
    if (i == n)
    {
        // thì nạp vào result
        result += s;
        result += '\n';
        return;
    }

    // Duyệt từng ký tự
    for (char c : {'0', '1', '2'})
    {
        // Gán ký tự đang duyệt cho vị trí i
        s[i] = c;

        // Ứng với i, gọi đệ quy để chuẩn bị gán cho vị trí i + 1
        backtracking(i + 1);
    }
}


void process()
{
    // Đặt kích thước cho s là 3 ký tự
    s.resize(n);

    // Đặt trước dung lượng cho đầu ra
    result.reserve((n + 1) * pow(3, n));

    // Gọi backtracking() bắt đầu từ vị trí 0
    backtracking(0);
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