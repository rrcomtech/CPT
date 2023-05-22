#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>

#define rep(a, b)   for(uint32_t a = 0; a < (b); ++a)
#define all(a)      (a).begin(),(a).end()
#define uint        uint32_t

using Graph = std::vector<std::vector<int>>;
using ll = long long;

struct WorldPosition {
    int position;
    int height;
};

struct Interval {
    int leftPos;
    int rightPos;
};

float calculateRain(std::string world, std::vector<WorldPosition> wps, uint32_t leftPos, uint32_t rightPos) {
    auto highestPoint = wps[leftPos].height;
    auto total = float{0};

    for (auto currPos = leftPos; currPos <= rightPos; ++currPos) {
        if (world[currPos] == '/' || world[currPos] == '\\') {
            total += static_cast<float>(highestPoint - wps[currPos].height + 0.5);
        } else {
            total += static_cast<float>(highestPoint - wps[currPos].height);
        }
    }
    return total;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint32_t test_cases;
    std::cin >> test_cases;
    auto worlds = std::vector<std::string>(test_cases);
    rep(i, test_cases) {
        std::string temp;
        std::cin >> temp;
        worlds[i] = temp;
    }

    for (auto world : worlds) {
        auto worldUnnormedHeights = std::vector<WorldPosition>();
        // Build Height of each position

        auto world_lowest = 0;
        auto world_highest = 0;
        auto currHeight = 0;
        auto currPos = 0;
        for (char curr : world) {
            WorldPosition wp;
            wp.position = currPos++;
            
            if (curr == '/') wp.height = ++currHeight;
            if (curr == '\\') wp.height = currHeight--;
            if (curr == '_') wp.height = currHeight;
            worldUnnormedHeights.push_back(wp);

            world_lowest = std::min(wp.height, world_lowest);
            world_highest = std::max(wp.height, world_highest);
        }

        // Norm everything to non-negative values.
        auto worldHeights = std::vector<WorldPosition>();
        for (auto wp : worldUnnormedHeights) {
            WorldPosition pos;
            pos.position = wp.position;
            pos.height = wp.height + std::abs(world_lowest);
            worldHeights.push_back(pos);
        }
        
        auto total_rain = float{0};
        rep(pos, worldHeights.size()) {
            // No start of valley.
            if (world[pos] == '_' || world[pos] == '/') continue;

            auto endOfValley = pos + 1;
            while (endOfValley < worldHeights.size() && worldHeights[endOfValley].height != worldHeights[pos].height) ++endOfValley;
            
            if (!(endOfValley >= worldHeights.size())) {
                total_rain += calculateRain(world, worldHeights, pos, endOfValley);
                pos = endOfValley;
            }
        }

        std::cout << static_cast<uint>(total_rain) << "\n";
    }
}