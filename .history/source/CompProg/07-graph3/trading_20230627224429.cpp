#include <iostream>
#include <vector>
#include <limits>

std::vector<int> findInfiniteMoneyGlitch(int n, const std::vector<std::string>& currencies, const std::vector<std::vector<double>>& exchangeRates) {
    // Step 1: Initialize variables
    std::vector<double> dist(n, std::numeric_limits<double>::infinity());
    dist[0] = 0;
    std::vector<int> parent(n, -1);
    std::vector<int> glitchCurrencies;

    // Step 2: Bellman-Ford algorith
    for (int i = 0; i < n - 1; ++i) {
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                if (dist[u] + exchangeRates[u][v] < dist[v]) {
                    dist[v] = dist[u] + exchangeRates[u][v];
                    parent[v] = u;
                }
            }
        }
    }

    // Step 3: Check for negative cycles
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            if (dist[u] + exchangeRates[u][v] < dist[v]) {
                // Negative cycle found
                // Step 4: Trace back the cycle
                int cycleStart = v;
                while (std::find(glitchCurrencies.begin(), glitchCurrencies.end(), cycleStart) == glitchCurrencies.end()) {
                    glitchCurrencies.push_back(cycleStart);
                    cycleStart = parent[cycleStart];
                }

                glitchCurrencies.push_back(cycleStart);
                return std::vector<int>(glitchCurrencies.rbegin(), glitchCurrencies.rend());
            }
        }
    }

    return std::vector<int>();
}

int main() {
    // Step 0: Read input
    int n;
    std::cin >> n;

    std::vector<std::string> currencies(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> currencies[i];
    }

    std::vector<std::vector<double>> exchangeRates(n, std::vector<double>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> exchangeRates[i][j];
        }
    }

    // Step 5: Find infinite money glitch
    std::vector<int> glitch = findInfiniteMoneyGlitch(n, currencies, exchangeRates);

    // Step 6: Print the output
    if (glitch.empty()) {
        std::cout << "noglitch" << std::endl;
    } else {
        std::cout << "money!" << std::endl;
        std::cout << glitch.size() << std::endl;
        for (int i : glitch) {
            std::cout << currencies[i] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}