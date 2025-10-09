#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <iomanip>

#define input_file "lis.inp"
#define output_file "lis.out"

using namespace std;

int n;
vector<int> A;

// D[i] là độ dài dài nhất của dãy con [0..i]
vector<int> D;

// Mảng trace dùng để truy vết kết nối của các phần tử trong dãy con
// trace[i] = j nghĩa là trước phần tử `A[i]` là phần tử `A[j]`.
vector<int> trace;


void input()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen(input_file, "r", stdin);
    cin >> n;

    int x;
    for (int i = 0; i < n; ++i)
    {
        cin >> x;
        A.push_back(x);
    }
}


void process()
{
    // Khởi tạo giá trị 1 cho toàn bộ bảng quy hoạch D, nghĩa là độ dài dài nhất là 1
    D.resize(n, 1);

    // Khởi tạo giá trị -1 cho toàn mảng trace, nghĩa là chưa có kết nối nào
    trace.resize(n, -1);

    // Duyệt từng phần tử A[i] trong phạm vi [1..n - 1]
    for (int i = 1; i < n; ++i)
    {
        // Duyệt từng phần tử A[j] trong dãy con [0..i - 1]
        for (int j = 0; j < i; ++j)
        {
            // Nếu A[i] vẫn bảo đảm cho dãy con của A[j] tăng dần
            if (A[j] < A[i])
            {               
                // D[j] + 1 là độ dài dài nhất của dãy con [0..j] cộng thêm 1 phần tử (là A[i])
                // D[i] là độ dài dài nhất của dãy con [0..i]
                // Nếu vẫn bảo đảm độ dài là dài nhất: D[j] + 1 > D[i]
                if (D[j] + 1 > D[i])
                {
                    // thì ghi nhận độ dài dài nhất mới
                    D[i] = D[j] + 1;

                    // và ghi nhận kết nối A[i] với A[j]
                    trace[i] = j;
                }
            }
        }
    }
}


void output()
{   
    // Tìm vị trí của phần tử trong mảng D lưu độ dài dài nhất, gọi là finish
    vector<int>::iterator max_len = max_element(D.begin(), D.end());
    int finish = max_len - D.begin();

    // Dùng ngăn xếp để lưu các phần tử của dãy con dài nhất cần tìm
    stack<int> sub_seq; // subsequence
    while (!(trace[finish] == -1))
    {
        // Đẩy phần tử A[finish] vào ngăn xếp
        sub_seq.push(A[finish]);

        // Thực hiện truy ngược, lấy vị trí finish mới
        finish = trace[finish];
    }

    // Đẩy phần tử đầu tiên của dãy con dài nhất vào ngăn xếp
    sub_seq.push(A[finish]);

    freopen(output_file, "w", stdout);
    
    cout << *max_len << endl;

    while (!sub_seq.empty())
    {
        // In ra phần tử nằm ở đỉnh của ngăn xếp
        cout << sub_seq.top();

        // Nếu chưa phải là phần tử cuối của dãy con thì in khoảng trắng
        if (sub_seq.size() > 1) cout << ' ';

        // Xoá bỏ phần tử nằm ở đỉnh vừa in ra
        sub_seq.pop();
    }
}


// Hàm in ra các mảng liên quan trong chương trình
void show()
{
    // In tiêu đề cột
    cout << string(6 + 2, ' ');
    for (int col = 0; col < n; ++col)
    {
        cout << setw(6) << col;
    }
    cout << endl;

    // In đường phân cách
    cout << string(6 + 2, ' ');
    cout << string(n * 6, '-') << endl;

    // In tiêu đề hàng và giá trị
    cout << setw(8) << "a |";
    for (int col = 0; col < n; ++col)
    {
        cout << setw(6) << A[col];
    }
    cout << endl;

    cout << setw(8) << "d |";
    for (int col = 0; col < n; ++col)
    {
        cout << setw(6) << D[col];
    }
    cout << endl;   

    cout << setw(8) << "trace |";
    for (int col = 0; col < n; ++col)
    {
        cout << setw(6) << trace[col];
    }
    cout << endl;   
}


int main()
{
    input();    
    process();
    output();
    // show();

    return 0;
}

