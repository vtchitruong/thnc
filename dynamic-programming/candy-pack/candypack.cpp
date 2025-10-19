#include <iostream>
#include <vector>
#include <stack>
#include <iomanip>

#define input_file "candypack1.inp"
#define output_file "candypack1.out"

using namespace std;

int n; // tổng số gói
int m; // tổng số kẹo cần lấy

vector<int> pack; // pack[i] là số kẹo của gói thứ i

// D[candy_amount] là số thứ tự của gói được chọn để đạt được candy_amount kẹo và là nhỏ nhất
vector<int> D;


void input()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    freopen(input_file, "r", stdin);
    
    cin >> n >> m;

    // Gói thứ 0 không có kẹo
    pack.push_back(0);

    int x;
    for (int i = 1; i < n + 1; ++i)
    {
        cin >> x;
        pack.push_back(x);
    }
}


void process()
{
    // Khởi tạo giá trị vô cực cho toàn bảng quy hoạch
    D.resize(m + 1, INT_MAX);

    // Không có gói nào được chọn cho D[candy_amount = 0]
    D[0] = 0;

    // Duyệt số kẹo cần lấy từ 1 đến m
    for (int candy_amount = 1; candy_amount < m + 1; ++candy_amount)
    {
        // Duyệt từng gói từ 1 đến n
        for (int i = 1; i < n + 1; ++i)
        {
            // Số kẹo của gói thứ i phải ít hơn số candy_amount kẹo đang xét
            if (pack[i] <= candy_amount)
            {
                // D[candy_amount - pack[i]] là số thứ tự của gói nào đó trước khi chọn gói i
                if (D[candy_amount - pack[i]] < i)
                {
                    // Đánh dấu chọn gói i để đạt được candy_amount kẹo
                    D[candy_amount] = i;

                    // Thoát vòng lặp i ngay khi tìm được gói i đầu tiên nhằm thoả yêu cầu ưu tiên chọn gói có số thứ tự nhỏ nhất
                    break;
                }
            }
        }
    }
}


void output()
{
    // ngăn xếp chứa các gói được chọn
    stack<int> chosen_packs;

    // Nếu D[m] là vô cực thì không tìm được lời giải
    // Ngược lại, thì thực hiện truy ngược từ D[m] về đầu mảng
    if (D[m] != INT_MAX)
    {
        // Số kẹo còn lại dùng để truy ngược
        int remaining_amount = m;

        // Trong khi vẫn còn kẹo
        while (remaining_amount > 0)
        {
            // Nạp gói được chọn vào chosen_packs
            chosen_packs.push(D[remaining_amount]);
            
            // Trừ đi số kẹo của gói vừa nạp vào
            remaining_amount -= pack[chosen_packs.top()];
        }
    }

    freopen(output_file, "w", stdout);

    if (chosen_packs.empty())
    {
        cout << -1;
    }
    else
    {
        while (!chosen_packs.empty())
        {
            cout << chosen_packs.top();
            if (chosen_packs.size() != 1) cout << ' ';
            chosen_packs.pop();
        }
    }
}


// Hàm in ra bảng quy hoạch
void show()
{
    cout << "candy_amount | D[candy_amount]" << '\n';

    for (int i = 1; i < m + 1; ++i)
    {
        cout << setw(12) << i << " | ";
        
        if (D[i] == INT_MAX)
            cout << "INF";
        else
            cout << D[i];

        cout << '\n';
    }
}


int main()
{
    input();
    process();
    //output();
    
    show();
    return 0;
}