#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <queue>

#define rep(a, b)   for(uint32_t a = 0; a < (b); ++a)
#define all(a)      (a).begin(),(a).end()
#define uint        uint32_t
#define cf(a)       static_cast<float>(a)

using Graph = std::vector<std::vector<int>>;
using ll = long long;

struct Household {
    uint32_t no_ponies;
    uint32_t distributed_cakes = 1;
    uint32_t max_slices_per_pony;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint32_t no_test_cases;
    std::cin >> no_test_cases;

    rep(test_case, no_test_cases) {
        uint number_of_households = 0;
        uint total_cake = 0;
        std::cin >> number_of_households >> total_cake;

        uint no_cake = total_cake - number_of_households;

        auto households = std::vector<Household>();
        rep (household, number_of_households) {
            uint no_ponies;
            std::cin >> no_ponies;

            Household h;
            h.no_ponies = no_ponies;
            if (no_ponies == 1) h.max_slices_per_pony = 0;
            else h.max_slices_per_pony = h.no_ponies;
            households.push_back(h);
        }

        auto pq = std::priority_queue(households.begin(), households.end(), [](Household& a, Household& b) {
            if (a.max_slices_per_pony == b.max_slices_per_pony) {
                return a.no_ponies < b.no_ponies;
            }
            return a.max_slices_per_pony < b.max_slices_per_pony;
        });

        while (no_cake > 0) {
            auto h = pq.top();
            h.distributed_cakes++;
            no_cake--;
            h.max_slices_per_pony = static_cast<uint>(std::ceil(cf(h.no_ponies) / cf(h.distributed_cakes)));

            pq.pop();
            pq.push(h);
        }

        std::cout << pq.top().max_slices_per_pony << "\n";
    }
}
