#include <iostream>
#include <cstring>

#define input_file "ab1.inp"
#define output_file "ab1.out"

using namespace std;

// Khai báo hằng số kích thước để lưu tạm output là 1 MB
const size_t BUFFER_LIMIT = 1 << 20;

int n;

// biến lưu chuỗi hoàn chỉnh
char s[28];

// con trỏ FILE dùng fwrite để ghi nhanh
FILE *f;

// biến lưu toàn bộ output
string result = "";


void input()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen(input_file, "r", stdin);

    cin >> n;
}


// Hàm dùng để ghi result ra tập tin
inline void flush_buffer()
{
    // Nếu có dữ liệu
    if (!result.empty())
    {
        // thì ghi tất cả dữ liệu ra tập tin
        fwrite(result.data(), 1, result.size(), f);

        // Xoá để chuẩn bị ghi tiếp
        result.clear();
    }
}


void backtracking(int i, char previous)
{
    // Nếu đã đủ số lượng ký tự
    if (i == n)
    {
        // thì thêm n ký tự của s vào result
        result.append(s, s + n);

        // và thêm ký tự xuống dòng
        result.push_back('\n');

        // Nếu result đầy rồi thì ghi ra tập tin
        if (result.size() >= BUFFER_LIMIT)
            flush_buffer();

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
    // Khởi tạo s gồm n ký tự 'A'
    memset(s, 'A', n);

    // Đặt trước dư ra 1024 byte cho result để tránh realloc nhiều lần
    result.reserve(BUFFER_LIMIT + 1024);

    f = fopen(output_file, "wb");

    backtracking(0, '?');

    // Ghi phần còn sót lại ra tập tin
    flush_buffer();

    fclose(f);
}


int main()
{
    input();
    process_output();

    return 0;
}