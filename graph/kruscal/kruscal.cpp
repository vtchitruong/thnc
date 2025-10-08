#include <iostream>

using namespace std;


find(int x)
{
    if (rep[x] != x)
        rep[x] = find(rep[x])

    return rep[x];
}


union()
{
    
}


void kruscal()
{

}


#include <iostream>
#include <vector>
#include <algorithm>

// Cấu trúc để biểu diễn một cạnh của đồ thị
struct Edge {
    int u, v, weight;
};

// So sánh hai cạnh dựa trên trọng số, dùng cho hàm sort
bool compareEdges(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

// Cấu trúc Disjoint Set Union (DSU)
struct DSU {
    std::vector<int> parent;
    DSU(int n) {
        parent.resize(n);
        for (int i = 0; i < n; ++i) {
            parent[i] = i; // Ban đầu, mỗi đỉnh là cha của chính nó
        }
    }

    // Hàm tìm gốc của tập hợp chứa đỉnh u (với Path Compression)
    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]); // Tối ưu hóa đường đi
    }

    // Hàm hợp nhất hai tập hợp chứa u và v
    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j; // Gán gốc của tập này làm con của gốc tập kia
        }
    }
};

// Hàm thực hiện thuật toán Kruskal
void kruskal(int V, std::vector<Edge>& edges) {
    // 1. Sắp xếp tất cả các cạnh theo trọng số tăng dần
    std::sort(edges.begin(), edges.end(), compareEdges);

    // 2. Khởi tạo DSU
    DSU dsu(V);

    std::vector<Edge> mst;
    int total_weight = 0;

    // 3. Duyệt qua các cạnh đã sắp xếp
    for (const auto& edge : edges) {
        int u = edge.u;
        int v = edge.v;
        int weight = edge.weight;

        // Kiểm tra xem việc thêm cạnh có tạo chu trình không
        if (dsu.find(u) != dsu.find(v)) {
            // Nếu không, thêm cạnh vào MST
            dsu.unite(u, v);
            mst.push_back(edge);
            total_weight += weight;

            // Dừng khi đã có đủ V-1 cạnh
            if (mst.size() == V - 1) {
                break;
            }
        }
    }
    
    // In kết quả
    std::cout << "Cac canh cua Cay Khung Nho Nhat (MST):\n";
    for (const auto& edge : mst) {
        // Chuyển đổi chỉ số thành ký tự để dễ đọc (0->A, 1->B, ...)
        std::cout << "Canh " << (char)('A' + edge.u) << " - " << (char)('A' + edge.v) 
                  << " co trong so " << edge.weight << std::endl;
    }
    std::cout << "Tong trong so cua MST: " << total_weight << std::endl;
}

int main() {
    int V = 6; // Số đỉnh
    
    // Danh sách các cạnh của đồ thị trong ví dụ
    std::vector<Edge> edges = {
        {0, 1, 1}, // A-B, 1
        {2, 4, 2}, // C-E, 2
        {3, 5, 3}, // D-F, 3
        {0, 2, 4}, // A-C, 4
        {2, 3, 5}, // C-D, 5
        {1, 3, 6}, // B-D, 6
        {4, 5, 7}, // E-F, 7
        {1, 4, 8}  // B-E, 8
    };

    kruskal(V, edges);

    return 0;
}

int main()
{

    return 0;
}