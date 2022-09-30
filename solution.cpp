#include <algorithm>
#include <bitset>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
#define pb push_back
#define pi pair<int, int>
#define l first
#define r second
#define all(x) x.begin(), x.end()

using namespace std;

const int MAXS = 5005;

int m[MAXS][MAXS];

struct rect {
    int x1, y1, x2, y2;

    rect() {}
};

struct cell {
    int x, y;
};

bool operator<(const cell& c1, const cell& c2) {
    if (c1.x != c2.x) {
        return c1.x < c2.x;
    }
    return c1.y < c2.y;
}

vector<pair<int, int>> cells, nc;

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n, S, k;
    cin >> n >> S >> k;
    vector<rect> v(n);    
    for (int i = 0; i < n; i++) {
        cin >> v[i].x1 >> v[i].y1 >> v[i].x2 >> v[i].y2;
        for (int j = v[i].y1; j <= v[i].y2; j++) {
            m[j][v[i].x1] += 1;
            m[j][v[i].x2 + 1] -= 1;
        }
    }
    int count = 0;
    for (int i = 1; i <= S; i++) {
        int bal = 0;
        for (int j = 1; j <= S + 1; j++) {
            bal += m[i][j];
            m[i][j] = (bal > 0);
            count += m[i][j];
        }
    }
    for (int i = 0; i <= S + 1; i++) {
        for (int j = 0; j <= S + 1; j++) {
            if (m[i][j]) {
                cells.push_back({i, j});
            }
            m[i][j] = 0;
        }
    }
    cout << count << '\n';
    for (int _ = 1; _ < k; _++) {
        for (auto [r, c] : cells) {
            ++m[r - 1][c];
            ++m[r][c - 1];
            ++m[r + 1][c];
            ++m[r][c + 1];
        }
        for (auto [r, c] : cells) {
            if (m[r - 1][c] == 2) {
                nc.push_back({r - 1, c});
            }
            if (m[r + 1][c] == 2) {
                nc.push_back({r + 1, c});
            }
            if (m[r][c - 1] == 2) {
                nc.push_back({r, c - 1});
            }
            if (m[r][c + 1] == 2) {
                nc.push_back({r, c + 1});
            }
            if (m[r][c] == 2) {
                nc.push_back({r, c});
            }
            m[r - 1][c] = 0;
            m[r + 1][c] = 0;
            m[r][c - 1] = 0;
            m[r][c + 1] = 0;
            m[r][c] = 0;
        }
        cells = nc;
        nc.clear();
        cout << cells.size() << '\n';
    }
    return 0;
}
