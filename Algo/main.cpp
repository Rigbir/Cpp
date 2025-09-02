#include <iostream>
#include <vector>
#include <algorithm>

int lBinSearch(int l, int r, const int x, const std::vector<int>& v) {
    while (l < r) {
        int m = (l + r) / 2;
        if (v[m] == x) {
            return l;
        }
        if (v[m] >= x) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    if (l == v.size()) return 0;
    else return l;
}

int rBinSearch(int l, int r, const int x, const std::vector<int>& v) {
    while (l < r) {
        int m = (l + r) / 2;
        if (v[m] == x) {
            return l;
        }
        if (v[m] >= x) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    if (l == v.size()) return 0;
    else return l;
}

std::vector<int> input() {
    int x;
    std::cin >> x;

    std::vector<int> v(x);
    for (int i = 0; i < x; ++i) {
        std::cin >> v[i];
    }

    return v;
}

void forum() {
    std::vector<int> v = input();
    std::vector<int> v2 = input();
    std::ranges::sort(v);

    std::vector<std::pair<int, int>> result;

    for (int i = 0; i < v2.size(); ++i) {
        int left = lBinSearch(0, v.size(), v2[i], v);
        int right = rBinSearch(0, v.size(), v2[i], v);
        result.push_back({left, right});
    }

    for (const auto& [l, r] : result) {
        std::cout << l << ' ' << r << '\n';
    }
}

int main() {
    forum();
}
