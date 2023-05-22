#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <iterator>
#include <sstream>
#include <unordered_map>

#define rep(a, b)   for(uint32_t a = 0; a < (b); ++a)
#define all(a)      (a).begin(),(a).end()
#define uint        uint32_t

using Graph = std::vector<std::vector<int>>;
using ll = long long;

int main() {

    uint test_cases;
    std::cin >> test_cases;

    std::vector<uint> output;

    rep(test_case, test_cases) {
        std::vector<uint> snowflakes;
        uint largest_bag = 0;

        uint no_snowflakes;
        std::cin >> no_snowflakes;

        rep(i, no_snowflakes) {
            uint snowflake;
            std::cin >> snowflake;
            snowflakes.push_back(snowflake);
        }

        if (no_snowflakes == 1) {
            std::cout << "1\n";
            continue;
        }

        auto pos_map = std::unordered_map<uint, uint>();
        auto curr_bag_size = uint{0};
        auto start_position = uint{0};
        rep(i, no_snowflakes) {
            auto el = snowflakes[i];

            if (pos_map.find(el) == pos_map.end()) {
                pos_map[el] = i;
                ++curr_bag_size;
            } else {
                if (pos_map[el] < start_position) {
                    pos_map[el] = i;
                    ++curr_bag_size;
                } else {
                    largest_bag = std::max(largest_bag, curr_bag_size);
                    curr_bag_size -= pos_map[el] - start_position;
                    start_position = pos_map[el] + 1;
                    pos_map[el] = i;
                }
            }
        }

        std::cout << std::max(largest_bag, curr_bag_size) << "\n";
    }

    return 0;
}