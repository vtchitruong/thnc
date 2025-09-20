#include <iostream>
#include <vector>

using namespace std;

typedef long long int lli;

const lli M = 1000000007;

// Hàm tính luỹ thừa modulo dựa trên thuật toán luỹ thừa nhanh
lli power_modulo(lli a, lli b)
{
    // Giảm a xuống modulo M để tránh tràn số
    a %= M;

    // Khởi tạo kết quả bằng 1
    lli res = 1;

    // Trong khi số mũ b vẫn chưa bằng 0
    while (b > 0)
    {
        // Nếu b là số lẻ thì nhân kết quả hiện hành với a và lấy modulo M 
        if (b & 1) res = (res * a) % M;

        // Dù b là chẵn hay lẻ thì vẫn tính luỹ thừa 2 của a
        a = (a * a) % M;

        // Dịch bit của b sang phải, tương đương với chia b cho 2
        b >>= 1;
    }

    return res;
}


// Hàm tính nghịch đảo modulo M của a
lli modulo_inverse(lli a)
{
    return power_modulo(a, M - 2);
}


// Hàm tính tổ hợp modulo
lli combination(lli n, lli k)
{
    if (k > n) return 0;

    // Khởi tạo mảng f (factorial) để lưu các giá trị giai thừa
    vector<lli> f(n + 1, 1);

    // Tính các giá trị giai thừa
    for (lli i = 1; i <= n; ++i)
    {
        f[i] = (f[i - 1] * i) % M;
    }

    // Tính tổ hợp modulo
    return (f[n] * modulo_inverse((f[k] * f[n - k]) % M)) % M;
}


int main()
{
    lli n = 10;
    lli k = 5;

    lli c = combination(n, k);

    cout << "C(" << n << ", " << k << ") = " << c << '\n';

    return 0;
}