#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <queue>
#include <map>
#include <unordered_map>
#include <set>
#include <stack>


#define rep(a, b)   for(uint a = 0; a < (b); ++a)
#define all(a)      (a).begin(),(a).end()
#define uint        uint32_t
#define endl        '\n'

using namespace std;
using Graph = vector<vector<int>>;
using ll = long long;

struct Interval {
    uint id;
    ll start;
    ll end;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    auto startComp = [](Interval a, Interval b) {
        if (a.start == b.start) return a.end > b.end;
        return a.start > b.start;
    };
    auto endComp = [](Interval a, Interval b) {
        if (a.end == b.end) return a.start > b.start;
        return a.end > b.end;
    };

    auto intervals = priority_queue<Interval, vector<Interval>, decltype(startComp)>(startComp);

    uint no_intervals;
    cin >> no_intervals;
    rep (i, no_intervals) {
        ll start, end;
        cin >> start >> end;

        Interval interval;
        interval.id = i + 1;
        interval.start = start;
        interval.end = end;

        intervals.push(interval);
    }

    auto left = priority_queue<Interval, vector<Interval>, decltype(endComp)>(endComp);
    auto last_pos = ll{-1};
    while (intervals.size() > 0) {
        auto val = intervals.top();
        intervals.pop();

        while (!left.empty() && last_pos < val.start - 1) {
            ++last_pos;
            std::cout << left.top().id << endl;
            left.pop();
        }

        if (val.start > last_pos && left.empty()) {
            last_pos = val.start;
            std::cout << val.id << endl;
        } else {
            left.push(val);
        }

    }

    while (!left.empty()) {
        std::cout << left.top().id << endl;
        left.pop();
    }

    return 0;
}
