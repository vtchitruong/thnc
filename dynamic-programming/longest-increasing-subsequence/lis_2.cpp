#include <bits/stdc++.h>

#define inputFile "lis1.inp"
#define outputFile "lis1.out"

using namespace std;

int n;
vector<int> a;

vector<int> d; // d[i] là độ dài lớn nhất của chuỗi con tính từ đầu tới i
vector<int> trace;

void Input()
{
    ifstream f;
    f.open(inputFile);

    f >> n;

    a.push_back(INT_MIN);

    int x;
    for (int i = 0; i < n; ++i)
    {
        f >> x;
        a.push_back(x);
    }

    a.push_back(INT_MAX);

    f.close();
}

void Init()
{
    d.resize(n + 2);
    d[n + 1] = 1; // phần tử cuối INT_MAX

    trace.resize(n + 2);
}

void Process()
{
    int jmax;
    for (int i = n; i >= 0; --i)
    {
        jmax = n + 1; // khởi tạo 

        for (int j = i + 1; j < n + 2; ++j)
        {
            if (a[i] < a[j]) // xét tăng
            {
                if (d[j] > d[jmax])
                {
                    jmax = j;
                }

                d[i] = d[jmax] + 1;
                trace[i] = jmax;
            }
        }
    }
}

void Output()
{
    ofstream f;
    f.open(outputFile);

    // độ dài dãy con dài nhất là phần tử đầu tiên của mảng d
    // phải trừ 2 phần tử ở 2 đầu mảng d do thêm vào ở giai đoạn khởi tạo.
    int max_len = d[0] - 2;

    f << max_len << endl;

    int start = trace[0]; // a[0] hiện đang là phần tử INT_MIN

    while (!(start == n + 1))
    {
        f << a[start];
        start = trace[start];
        if (!(start == n + 1)) f << ' ';
    }

    f.close();
}

int main()
{
    Input();
    Init();    
    Process();
    Output();
    return 0;
}

