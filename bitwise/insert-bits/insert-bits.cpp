#include <iostream>
#include <bitset>
#include <string>

using namespace std;

int insert_bits(int n, int m, int start, int end)
{
    // Tạo chuỗi bit 1 nằm bên trái của start
    int left = ~0 << (start + 1);

    // Tạo chuỗi bit 1 nằm bên phải của end
    int right = (1 << end) - 1;

    // Tạo mặt nạ để che hai bên của start và end, đồng thời để hở khoảng giữa từ start đến end
    int mask = left | right;

    // Áp mặt nạ vào n để "xóa" các bit ở vị trí từ start đến end
    int n_cleared = n & mask;

    // Dịch chuyển các bit của m sang trái end bước để khớp với đoạn cần chèn trong n
    int m_shifted = m << end;

    // Chèn m vô n
    return n_cleared | m_shifted;
}

int main()
{
    int n = 0b1010101010101010;
    int m = 0b10011;

    cout << "n = " << bitset<16>(n) << '\n';
    cout << "m = " << bitset<16>(m) << '\n';

    int start = 6;
    int end = 2;

    int res = insert_bits(n, m, start, end);

    // Chuyển bit thành chuỗi
    string bits = bitset<16>(res).to_string();

    // Định dạng lại để dễ quan sát khi in ra
    string formatted = bits.substr(0, 15 - start) + ' ' + bits.substr(15 - start, start - end + 1) + ' ' + bits.substr(15 - end + 1, 16);

    cout << "Sau khi chèn m vô n: " << formatted;

    return 0;
}