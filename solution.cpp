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

const int MAXS = 5002;

bool m[MAXS][MAXS];

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

map<cell, int> cells;

void mkzero(cell cur) {
    if (min(cur.x, cur.y) < 1 || 
        max(cur.x, cur.y) > 5000) {
        return;
    }
    if (!m[cur.x][cur.y]) {
        return;
    }
    m[cur.x][cur.y] = 0;
    mkzero({cur.x - 1, cur.y});
    mkzero({cur.x + 1, cur.y});
    mkzero({cur.x, cur.y - 1});
    mkzero({cur.x, cur.y + 1});
}

void borderline(cell cur) {
    cells[cur] = 0;
    m[cur.x][cur.y] = 0;
    if (m[cur.x + 1][cur.y]) {
        borderline({cur.x + 1, cur.y});
    } else if (m[cur.x][cur.y + 1]) {
        borderline({cur.x, cur.y + 1});
    } else if (m[cur.x - 1][cur.y]) {
        borderline({cur.x - 1, cur.y});
    } else if (m[cur.x][cur.y - 1]) {
        borderline({cur.x, cur.y - 1});
    }
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n, S, k;
    cin >> n >> S >> k;
    vector<rect> v(n);    
    for (int i = 0; i < n; i++) {
        cin >> v[i].x1 >> v[i].y1 >> v[i].x2 >> v[i].y2;
        for (int j = v[i].x1; j <= v[i].x2; j++) {
            m[j][v[i].y1] = m[j][v[i].y2] = 1;
        }
        for (int j = v[i].y1; j <= v[i].y2; j++) {
            m[v[i].x1][j] = m[v[i].x2][j] = 1;
        }
    }
    for (int i = 1; i <= S; i++) {
        for (int j = 1; j <= S; j++) {
            if (m[i][j]) {
                borderline({i, j});
            }
        }
    }
    for (int _ = 0; _ < k; _++) {
        for (auto [pt, x] : cells) {
            if (pt.x < S) {
                cells[{pt.x + 1, pt.y}] += 1;
            }
            if (pt.x > 1) {
                cells[{pt.x - 1, pt.y}] += 1;
            }
            if (pt.y < S) {
                cells[{pt.x, pt.y + 1}] += 1;
            }
            if (pt.y > 1) {
                cells[{pt.x, pt.y - 1}] += 1;
            }
        }
        map<cell, int> nc;
        for (auto [pt, x] : cells) {
            if (x == 2) {
                nc.insert({pt, 0});
            }
        }
        cells = nc;
        cout << cells.size() << '\n';
    }
    return 0;
}