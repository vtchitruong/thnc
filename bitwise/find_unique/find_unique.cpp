#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

vector<int> Array = { 2, 3, 5, 5, 2, 4, 3 };


// Cách 1: dùng vòng lặp và XOR dồn từng phần tử
int find_unique(vector<int> A)
{
    // Khởi tạo phần tử duy nhất bằng 0 vì x ^ 0 = x
    int unique_element = 0;

    // Duyệt từng phần tử trong mảng A
    for (int a : A)
    {
        unique_element ^= a;
    }

    return unique_element;
}


// Cách 2: dùng hàm accumulate()
int find_unique_2(vector<int> A)
{
    return accumulate(A.begin(), A.end(), 0, bit_xor<int>());
}


int main()
{
    cout << "Mảng ban đầu: ";
    for (int a : Array)
    {
        cout << a << ' ';
    }

    int unique = find_unique(Array);
    cout << "\nPhần tử duy nhất: " << unique;

    int unique_2 = find_unique_2(Array);
    cout << "\nPhần tử duy nhất: " << unique_2;

    return 0;
}
