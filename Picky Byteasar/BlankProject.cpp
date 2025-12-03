#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

const int powerS = 1 << 20;
int n, m, cnt[2 * powerS][5], tagMap[2 * powerS][5];
char str[powerS];


void applyMapping(int u, int m[5]) {
    int new_count[5] = { 0 };
    int new_tag[5];

    for (int j = 0; j < 5; ++j) {
        new_count[m[j]] += cnt[u][j];
        new_tag[j] = m[tagMap[u][j]];
    }

    for (int k = 0; k < 5; ++k) {
        cnt[u][k] = new_count[k];
        tagMap[u][k] = new_tag[k];
    }
}


void pushToCh(int u) {
    applyMapping(2 * u, tagMap[u]);
    applyMapping(2 * u + 1, tagMap[u]);
    iota(tagMap[u], tagMap[u] + 5, 0);
}


int find_idx_of_k(int u, int k, int c) {
    if (u >= powerS) return u - powerS;
    pushToCh(u);
    if (cnt[2 * u][c] >= k) {
        return find_idx_of_k(2 * u, k, c);
    }
    else {
        return find_idx_of_k(2 * u + 1, k - cnt[2 * u][c], c);
    }
}


void updateRange(int u, int l, int r, int finish, int char1, int char2) {
    if (l > finish) return;
    if (r <= finish) {
        int map[5];
        iota(map, map + 5, 0);
        map[char1] = char2;
        applyMapping(u, map); return;
    }
    pushToCh(u);
    int middle = (r + l) / 2;
    updateRange(2 * u, l, middle, finish, char1, char2);
    updateRange(2 * u + 1, middle + 1, r, finish, char1, char2);
    for (int k = 0; k < 5; ++k) {
        cnt[u][k] = cnt[2 * u + 1][k] + cnt[2 * u][k];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> str;
    for (int i = 0; i < 2 * powerS; ++i) iota(tagMap[i], tagMap[i] + 5, 0);
    for (int i = 0; i < n; ++i) cnt[powerS + i][str[i] - 'a'] = 1;
    for (int k = powerS - 1; k > 0; --k) {
        for (int j = 0; j < 5; ++j) {
            cnt[k][j] = cnt[2 * k][j] + cnt[2 * k + 1][j];
        }
    }
    for (int i = 0; i < m; i++) {
        int k;
        char from_char, to_char;
        cin >> k >> from_char >> to_char;
        int u = from_char - 'a';
        int v = to_char - 'a';
        int target_index = find_idx_of_k(1, k, u);
        updateRange(1, 0, powerS - 1, target_index, u, v);
    }

    for (int i = 1; i < powerS; ++i) {
        pushToCh(i);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (cnt[powerS + i][j]) cout << char('a' + j);
        }
    }
}