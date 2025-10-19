#include <iostream>
#include <vector>
#include <stack>
#include <iomanip>

#define input_file "camhoa.inp"
#define output_file "camhoa.out"

using namespace std;

int k, n;
vector<vector<int>> values;

// D[i][j] là tổng giá trị thẩm mỹ lớn nhất khi cắm i bó hoa đầu tiên vào j lọ hoa đầu tiên
// i: inflorescence (cụm hoa), j: jar (lọ)
vector<vector<int>> D;


void input()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen(input_file, "r", stdin);

    cin >> k >> n;

    values.resize(k + 1, vector<int>(n + 1, 0));

    for (int i = 1; i < k + 1; ++i)
    {
        for (int j = 1; j < n + 1; ++j)
        {
            cin >> values[i][j];
        }
    }
}


void process()
{
    // Khởi tạo giá trị 0 cho toàn bảng quy hoạch D
    D.resize(k + 1, vector<int>(n + 1, 0));

    // giá trị thẩm mỹ lớn nhất trong trường hợp 1 và 2
    int j_not_chosen, j_chosen;

    // Duyệt từng hàng i (inflorescence)
    for (int i = 1; i < k + 1; ++i)
    {
        // Duyệt từng cột j (jar)
        for (int j = 1; j < n + 1; ++j)
        {
            // Nếu số bó hoa ít hơn hoặc bằng số lọ
            if (i <= j)
            {
                // TH1: lọ j không được chọn cắm
                j_not_chosen = D[i][j - 1];

                // TH2: lọ j được chọn cắm
                j_chosen = D[i - 1][j - 1] + values[i][j];
                
                // Lấy giá trị thẩm mỹ tốt nhất
                D[i][j] = max(j_not_chosen, j_chosen);
            }
        }
    }
}


void output()
{
    // inflorescence
    // inflor[i] = j: chọn lọ j cho bó hoa i
    vector<int> inflor(k + 1, 0);

    int i = k;
    int j = n;

    while (i > 0 && j > 0)
    {
        if (i <= j)
            if (D[i][j] != D[i][j - 1])
            {
                // Chọn lọ j cho bó hoa i
                inflor[i] = j;
                
                // Lùi về bó hoa liền trước
                --i;

                // Lùi về lọ liền trước
                --j;
            }        
        else
        {
            // Chỉ lùi về lọ liền trước
            --j;
        }
    }

    freopen(output_file, "w", stdout);

    cout << D[k][n] << '\n';

    for (int i = 1; i < k + 1; ++i)
    {
        cout << inflor[i] << ' ';
    }
}


void show()
{
    for (int i = 1; i < k + 1; ++i)
    {
        for (int j = 1; j < n + 1; ++j)
        {
            cout << setw(4) << D[i][j] << ' ';
        }

        cout << endl;
    }
}


int main()
{
    input();
    process();
    show();
    output();

    return 0;
}