#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <stack>
#include <queue>

#define rep(a, b)   for(uint32_t a = 0; a < (b); ++a)
#define all(a)      (a).begin(),(a).end()
#define uint        uint32_t
#define ll          long long
#define cf(a)       static_cast<float>(a)

struct Interval {
    ll position;
    uint color;
    uint layer;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint no_colors, layers;

    std::cin >> no_colors >> layers;

    auto color_lengths = std::vector<ll>(no_colors, 0);
    auto colors = std::vector<Interval>();
    rep (layer, layers) {
        uint color;
        ll start, end;
        std::cin >> start >> end >> color;

        colors.push_back(Interval{start, color, layer});
        colors.push_back(Interval{end, color, layer});
    }
    std::sort(colors.begin(), colors.end(), [](Interval a, Interval b) {
        if (a.position == b.position) return a.layer < b.layer;
        return a.position < b.position;
    });

    auto c_layers = std::stack<Interval>();
    for (auto& color : colors) {

        if (c_layers.empty()) c_layers.push(color);
        else {
            auto last = c_layers.top();

            if (last.layer == color.layer) {
                color_lengths[color.color] += color.position - last.position;
                c_layers.pop();
                if (!c_layers.empty()) c_layers.top().position = color.position;
            } else if (last.layer < color.layer) {
                color_lengths[last.color] += color.position - last.position;
                c_layers.push(color);
            } else if (last.layer > color.layer) {
                auto add_current = true;
                auto colors_above = std::vector<Interval>();
                while (!c_layers.empty() && c_layers.top().layer >= color.layer) {
                    // If matching layer found, remove it. It is too low to be accounted.
                    if (c_layers.top().layer != color.layer) {
                        colors_above.push_back(c_layers.top());
                    } else {
                        add_current = false;
                    }
                    c_layers.pop();
                }
                // Add current color layer, if not matching layer found.
                if (add_current) colors_above.push_back(color);
                std::reverse(colors_above.begin(), colors_above.end());
                // Add all color layers from highest to lowest.
                rep(i, colors_above.size()) c_layers.push(colors_above[i]);
            }
        }
    }

    rep (i, color_lengths.size()) std::cout << color_lengths[i] << "\n";
}