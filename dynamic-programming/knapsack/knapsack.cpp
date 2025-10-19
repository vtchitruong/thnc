#include <iostream>
#include <vector>
#include <stack>
#include <iomanip>

#define input_file "knapsack.inp"
#define output_file "knapsack.out"

using namespace std;

int n; // tổng số vật
int weight_limit; // giới hạn trọng lượng của balo

vector<int> weight; // mảng lưu trọng lượng mỗi vật
vector<int> value; // mảng lưu giá trị mỗi vật

// D[i][w] là tổng giá trị lớn nhất khi chọn một số vật nào đó trong phạm vi [0..i] mà tổng trọng lượng không vượt quá `w`.
vector<vector<int>> D;


void input()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen(input_file, "r", stdin);

    cin >> n >> weight_limit;

    weight.resize(n + 1, 0);
    value.resize(n + 1, 0);

    for (int i = 1; i < n + 1; ++i)
    {
        cin >> weight[i] >> value[i];
    }
}


void process()
{
    // Khởi tạo giá trị 0 cho toàn bảng quy hoạch
    D.resize(n + 1, vector<int>(weight_limit + 1, 0));

    // Duyệt từng vật i trong phạm vi [1..n]
    for (int i = 1; i < n + 1; ++i)
    {
        // Duyệt từng giới hạn trọng lượng w trong phạm vi [1..weight_limit]
        for (int w = 1; w < weight_limit + 1; ++w)
        {
            // Giả sử không chọn vật i
            // Tổng giá trị các vật được chọn sẽ không thay đổi, tức vẫn là D[i - 1][w]
            D[i][w] = D[i - 1][w];
            
            // Nếu trọng lượng vật i không vượt quá giới hạn w
            if (weight[i] <=  w)
            {
                // Xét xem giữa chọn và không chọn vật i, trường hợp nào làm cho tổng giá trị là lớn nhất
                D[i][w] = max(D[i][w], D[i - 1][w - weight[i]] + value[i]);
            }
        }
    }
}


void output()
{
    // Ngăn xếp chứa các vật được chọn
    stack<int> item_stack;
    
    // Biến tạm wl dùng để lưu giới hạn trọng lượng
    int wl = weight_limit;

    // Biến tạm i dùng để lưu số thứ tự của vật
    int i = n;

    // Lặp cho đến khi i == 0 thì dừng
    while (i)
    {
        // Nếu tổng giá trị có sự thay đổi, nghĩa là vật i được chọn
        if (D[i][wl] != D[i - 1][wl])
        {
            // thì đẩy vật i vào ngăn xếp
            item_stack.push(i);

            // Lấy giới hạn trọng lượng còn lại sau khi đẩy vật i vào ngăn xếp
            wl = wl - weight[i];
        }

        --i;
    }

    freopen(output_file, "w", stdout);

    cout << D[n][weight_limit] << '\n';

    while (!item_stack.empty())
    {
        i = item_stack.top();
        cout << i << ' ' << weight[i] << ' ' << value[i];
        if (item_stack.size() > 1) cout << '\n';
        item_stack.pop();
    }
}

// Hàm in bảng quy hoạch
void show()
{
    // In tiêu đề cột
    cout << string(6 + 2, ' ');
    for (int c = 0; c < weight_limit + 1; ++c)
    {
        cout << setw(6) << c;
    }

    cout << '\n';

    // In đường phân cách
    cout << string(6 + 2, ' ');    
    cout << string((weight_limit + 1) * 6, '-') << '\n';
 
    // In tiêu đề hàng và giá trị
    for (int r = 0; r < n + 1; ++r)
    {
        cout << setw(6) << r << " |";
        for (int c = 0; c < weight_limit + 1; ++c)
        {
            cout << setw(6) << D[r][c];
        }
        cout << '\n';
    }
}


int main()
{
    input();
    process();
    output();
    // show();

    return 0;
}