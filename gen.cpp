#include "testlib.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#define x first
#define y second

using namespace std;

map<string, string> params;

long long get(string name, long long def = 0) {
    if (params.count(name)) {
        return stoll(params[name]);
    } else {
        return def;
    }
}

char get_ch(string name, char def = 'a') {
    if (params.count(name)) {
        return params[name][0];
    } else {
        return def;
    }
}

vector<int> parts(int n, int k, int dist = 1) {
    vector<int> idx(k + 1);
    for (int i = 1; i < k; i++) {
        idx[i] = rnd.next(0, n - dist * k);
    }
    idx[k] = n;
    sort(idx.begin(), idx.end());
    for (int i = 0; i < k; i++) {
        idx[i] += dist * i;
    }
    return idx;
}

vector<string> modes = {"random", "rev_parts", "reverses"};
vector<string> modes_plus = {"random", "rev_parts", "reverses", "de_bruijn"};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    for (int i = 1; i < argc; i++) {
        string s = string(argv[i]);
        if (s.find("=") != string::npos) {
            auto pos = s.find("=");
            params[s.substr(0, pos)] = s.substr(pos + 1);
        } else {
            params[s] = "";
        }
    }
    int n = get("n", 500);
    int S = get("S", 5000);
    int k = get("k", 100);
    cout << n << ' ' << S << ' ' << k << endl;
    for (int i = 0; i < n; i++) {
        int x1 = rnd.next(S - 2);
        int x2 = rnd.next(S - 2);
        int y1 = rnd.next(S - 2);
        int y2 = rnd.next(S - 2);
        if (x1 > x2) {
            swap(x1, x2);
        }
        x2 += 2;
        if (y1 > y2) {
            swap(y1, y2);
        }
        y2 += 2;
        cout << x1 + 1 << ' ' << y1 + 1 << ' ' << x2 + 1 << ' ' << y2 + 1 << endl;
    }   
    return 0;
}
