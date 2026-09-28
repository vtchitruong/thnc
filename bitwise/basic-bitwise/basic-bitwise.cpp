#include <iostream>
#include <bitset>
#include <cstdint>

using namespace std;

int main()
{
    // Tạo chuỗi bit 0
    int zeros = 0;
    cout << "Chuỗi 8 bit 0: " << bitset<8>(zeros) << '\n';

    // Tạo chuỗi bit 1
    int ones = ~0;
    cout << "Chuỗi 8 bit 1: " << bitset<8>(ones) << '\n';

    cout << "------------------------\n";

    uint8_t n = 0b10001101;
    uint8_t mask = 0b11110000;

    // Dùng phép toán OR để bật nửa trái thành 1 và bảo toàn nửa phải
    uint8_t or_result = n | mask;

    cout << bitset<8>(n) << " (n)\n";
    cout << "OR\n";
    cout << bitset<8>(mask) << " (mask)\n";
    cout << "--------\n";
    cout << bitset<8>(or_result) << '\n';

    cout << "------------------------\n";

    // Dùng phép toán AND để bảo toàn nửa trái và xóa bỏ nửa phải
    uint8_t and_result = n & mask;

    cout << bitset<8>(n) << " (n)\n";
    cout << "AND\n";
    cout << bitset<8>(mask) << " (mask)\n";
    cout << "--------\n";
    cout << bitset<8>(and_result) << '\n';

    cout << "------------------------\n";

    int p = 3;

    // Tính 2^p
    unsigned int power = 1U << p;
    cout << "2^" << p << " = " << power << '\n';

    cout << "------------------------\n";

    // Tạo mặt nạ trái
    uint8_t left = ~0 << p;
    cout << "Mặt nạ trái: " << bitset<8>(left) << '\n';

    // Tạo mặt nạ phải
    uint right = (1U << p) - 1;
    cout << "Mặt nạ phải: " << bitset<8>(right) << '\n';

    return 0;
}