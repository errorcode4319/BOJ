#include <iostream>
#include <vector>
#include <cstdint>

using i64 = int64_t; 

std::vector<i64> g_vTree(1000000 << 2);
int g_RS;   // range start
int g_RE;   // range end

// numbers, pos left, pos right
i64 init(const std::vector<i64>& vNum, int idx, int l, int r) {
    if (l == r) 
        return g_vTree[idx] = vNum[l];
    int m = (l + r) / 2;
    return g_vTree[idx] = init(vNum, idx*2, l, m) + init(vNum, idx*2+1, m+1, r);
}
// cur node index, left, right 
i64 sum(int idx, int l, int r) {
    if (g_RE < l || r < g_RS)
        return 0;
    if (g_RS <= l && r <= g_RE)
        return g_vTree[idx];
    int m = (l + r) / 2;
    return sum(idx*2, l, m) + sum(idx*2+1, m+1, r);
}
// cur node index, left, right, target idx, value
i64 update(int idx, int l, int r, int target, i64 val) {
    if (target < l || r < target) 
        return g_vTree[idx];
    if (l == r)
        return g_vTree[idx] = val;
    int m = (l + r) / 2;
    return g_vTree[idx] = update(idx * 2, l, m, target, val) + update(idx * 2 + 1, m+1, r, target, val);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0);
    int n, m, k;
    std::cin >> n >> m >> k;
    std::vector<i64> vNum(n+1);
    for(int i=1;i<=n;i++)
        std::cin >> vNum[i];
    
    init(vNum, 1, 1, n);
    
    i64 cnt = m+k, a, b, c;
    while(cnt--) {
        std::cin >> a >> b >> c;
        if(a == 1) {
            update(1, 1, n, b, c);
        }
        if(a == 2) {
            g_RS = int(b);
            g_RE = int(c);
            std::cout << sum(1, 1, n) << std::endl;
        }
    }
}