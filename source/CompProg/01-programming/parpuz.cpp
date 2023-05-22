#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <stack>
#include <sstream>
#include <iterator>

#define rep(a, b)   for(uint32_t a = 0; a < (b); ++a)
#define all(a)      (a).begin(),(a).end()
#define uint        uint32_t
#define cf(a)       static_cast<float>(a)

bool isValid(std::string puzzle) {
    // Declare a stack to hold the previous brackets.
    auto temp = std::stack<char>();
    for (uint i = 0; i < puzzle.length(); i++) {
        if (temp.empty()) temp.push(puzzle[i]);
        else if ((temp.top() == '(' && puzzle[i] == ')')) temp.pop();
        else temp.push(puzzle[i]);
    }
    return temp.empty();
}

std::string reduce(std::string piece) {
    // Declare a stack to hold the previous brackets.
    auto temp = std::stack<char>();
    for (uint i = 0; i < piece.length(); i++) {
        if (temp.empty()) temp.push(piece[i]);
        else if ((temp.top() == '(' && piece[i] == ')')) temp.pop();
        else temp.push(piece[i]);
    }

    auto res = std::string("");
    while (!temp.empty()) {
        res = temp.top() + res;
        temp.pop();
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint no_parts;
    std::cin >> no_parts;

    auto parts = std::vector<std::string>();
    rep(i, no_parts) {
        std::string temp;
        std::cin >> temp;
        //std::cout << "Prev: " << temp << "\n";
        temp = reduce(temp);
        //std::cout << "Reduced: " << temp << "\n";
        if (temp != "") {
            parts.insert(
                std::upper_bound(parts.begin(), parts.end(), temp),
                temp
            );
        }
    }

    if (parts.size() == 0) {
        std::cout << "YES" << "\n";
        return 0;
    }

    do {
        auto permutation = std::string("");
        if (parts[0][0] == ')') continue;
        for (auto part : parts) { 
            //std::cout << part << " ";
            permutation = permutation + part;
        }
        //std::cout << "\n";

        if (isValid(permutation)) {
            std::cout << "YES" << "\n";
            return 0;
        }
    } while (std::next_permutation(parts.begin(), parts.end()));

    std::cout << "NO" << "\n";
}