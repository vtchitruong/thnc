#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

#define input_file "rewardstudent.inp"
#define output_file "rewardstudent.out"

using namespace std;

int reward; // tổng số phần thưởng
int student; // tổng số học sinh

// D[r][s] là số cách mà s học sinh nhận r phần thưởng
vector<vector<int>> D;


void input()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen(input_file, "r", stdin);

    cin >> reward >> student;
}


// Cách 1: sử dụng mảng hai chiều
void process_1()
{
    // Khởi tạo giá trị 0 cho toàn bảng quy hoạch
    D.resize(student + 1, vector<int>(reward + 1, 0));

    // Chỉ có 1 cách để 0 học sinh nhận 0 phần thưởng
    D[0][0] = 1;    

    // Duyệt hàng (số học sinh) bằng biến s trong phạm vi [1..student]
    for (int s = 1; s < student + 1; ++s)
    {
        // Trường hợp 1: số phần thưởng < số học sinh
        // Chỉ có r học sinh được nhận r phần thưởng

        // Duyệt cột (số phần thưởng) bằng biến r trong phạm vi [0..s - 1]
        for (int r = 0; r < s; ++r)
        {
            D[s][r] = D[r][r];
        }

        // Trường hợp 2: số phần thưởng >= số học sinh
        // Trường hợp 2a: học sinh hạng chót sẽ không được nhận thưởng
        // Số cách chia thưởng là D[s - 1][r]

        // Trường hợp 2b: học sinh hạng chót vẫn được nhận thưởng
        // Số cách chia thưởng D[s][r] sẽ không thay đổi nếu ta bỏ bớt 1 phần thưởng của mỗi học sinh. Số phần thưởng tạm bỏ bớt là (r - s) 
        // Số cách chia thưởng là D[s][r - s]

        // Duyệt cột (số phần thưởng) bằng biến r trong phạm vi [s..reward]
        for (int r = s; r < reward + 1; ++r)
        {
            D[s][r] = D[s - 1][r] + D[s][r - s];
        }
    }
}


void output_1()
{
    freopen(output_file, "w", stdout);
    cout << D[student][reward];
}


void show_1()
{
    // In tiêu đề cột
    cout << string(6 + 2, ' ');
    for (int col = 0; col < reward + 1; ++col)
    {
        cout << setw(6) << col;
    }
    cout << '\n';

    // In đường phân cách
    cout << string(6 + 2, ' ');    
    cout << string((reward + 1) * 6, '-') << '\n';
 
    // In tiêu đề hàng và các giá trị    
    for (int row = 0; row < student + 1; ++row)
    {
        cout << setw(6) << row << " |";
        for (int col = 0; col < reward + 1; ++col)
        {
            cout << setw(6) << D[row][col];
        }
        cout << '\n';
    }

    cout << '\n';
}


// Cách 2: sử dụng mảng một chiều
vector<int> V;

void process_2()
{
    V.resize(reward + 1, 0);
    V[0] = 1;

    for (int s = 1; s < student + 1; ++s)
    {
        for (int r = s; r < reward + 1; ++r)
        {
            V[r] = V[r] + V[r - s];
        }
    }
}


void output_2()
{
    freopen(output_file, "w", stdout);
    cout << V[reward];
}


void show_2()
{
    // In tiêu đề
    cout << string(4 + 2, ' ');
    for (int col = 0; col < reward + 1; ++col)
    {
        cout << setw(4) << col;
    }
    cout << '\n';

    // In đường phân cách
    cout << string(4 + 2, ' ');    
    cout << string((reward + 1) * 4, '-') << '\n';
 
    // In giá trị
    cout << setw(6) << " |";
    for (int col = 0; col < reward + 1; ++col)
    {
        cout << setw(4) << V[col];
    }
    cout << '\n';    
}


int main()
{
    input();

    process_1();
    show_1();
    output();   
    
    // process_2();
    // output_2();
    // show_2();

    return 0;
}