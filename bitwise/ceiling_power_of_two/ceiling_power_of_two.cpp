#include <iostream>

using namespace std;

typedef unsigned int ui;


ui ceiling_power_of_two(ui n)
{
    if (n == 0) return 1;

    n--;
    
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    
    n++;

    return n;
}


int main()
{
    ui num;
    cout << "Nhập n: ";
    cin >> num;

    ui result = ceiling_power_of_two(num);
    cout << "Luỹ thừa của 2 nhỏ nhất mà lớn hơn hoặc bằng n: " << result;

    return 0;
}