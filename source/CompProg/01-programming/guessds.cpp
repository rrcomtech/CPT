#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>

#define rep(a, b)   for(uint32_t a = 0; a < (b); ++a)
#define all(a)      (a).begin(),(a).end()

using Graph = std::vector<std::vector<int>>;
using ll = long long;

int main() {
    std::cout << "? insert 3" << std::endl;
    std::cout << "? insert 3" << std::endl;
    std::cout << "? remove" << std::endl;
    int removed2;
    std::cin >> removed2;

    std::cout << "? empty" << std::endl;
    std::string isEmpty;
    std::cin >> isEmpty;

    if (isEmpty == "yes") {
        std::cout << "! set" << std::endl;
        return 0;
    }

    std::cout << "? remove" << std::endl;
    std::cin >> removed2;
    
    std::cout << "? insert 3" << std::endl;
    std::cout << "? insert 1" << std::endl;
    std::cout << "? insert 2" << std::endl;
    std::cout << "? remove" << std::endl; 

    int removed;
    std::cin >> removed;
    if (removed == 1 || (removed != 2 && removed != 3)) {
        std::cout << "! pq" << std::endl;
        return 0;
    } 
    if (removed == 2) {
        std::cout << "! stack" << std::endl;
        return 0;
    }
    if (removed == 3) {
        std::cout << "! queue" << std::endl;
    }
    return 0;
}