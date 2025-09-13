#include <iostream>

using namespace std;

typedef long long int lli;

// M = 10^9 + 7
const lli M = 1e9 + 7;


// Hàm kiểm tra phép cộng modulo
void check_add_modulo(lli a, lli b)
{
    // vế trái
    lli left = (a + b) % M; 
    
    // vế phải
    lli right = (a % M + b % M) % M;

    cout << "a = " << a << "\n";
    cout << "b = " << b << "\n";

    cout << "vế trái == vế phải: ";
    
    if (left == right)
        cout << "true\n";
    else
        cout << "false\n"; 
}


// Hàm tính luỹ thừa modulo dựa trên thuật toán luỹ thừa nhanh
lli power_modulo(lli a, lli b)
{
    // Giảm a xuống modulo M để tránh tràn số
    a %= M;

    // Khởi tạo kết quả bằng 1
    long long res = 1;
    
    // Trong khi số mũ b vẫn chưa bằng 0
    while (b > 0)
    {
        // Nếu b là số lẻ
        // thì nhân kết quả hiện hành với a và lấy modulo M 
        if (b & 1)            
            res = (res * a) % M;
        
        // Dù b là chẵn hay lẻ thì vẫn tính luỹ thừa 2 của a
        a = (a * a) % M;
        
        // Dịch bit của b sang phải, tương đương với chia b cho 2
        b >>= 1;
    }
    
    return res;
}


int main()
{
    // Kiểm tra phép cộng modulo
    a = 1e9;
    b = 8;

    check_add_modulo(a, b);

    // Tính luỹ thừa modulo
    lli a = 3;
    lli b = 11;

    lli pm = power_modulo(a, b);

    cout << a << '^' << b << " mod " << M << " = " << pm << '\n';
    
    return 0;
}