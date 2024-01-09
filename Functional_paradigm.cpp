#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

std::function<bool(const std::string&)> isDivisibleBy(int divisor) {
    return [divisor](const std::string& str) {
        return str.length() % divisor == 0;
    };
}

std::vector<std::string> search(const std::vector<std::string>& strings, const std::function<bool(const std::string&)>& criteria) {
    std::vector<std::string> result;
    for (const std::string& str : strings) {
        if (criteria(str)) {
            result.push_back(str);
        }
    }
    return result;
}

void printDivisibleStrings(const std::vector<std::string>& divisibleStrings) {
    std::cout << "Strings with length divisible by divisor: ";
    for (const std::string& str : divisibleStrings) {
        std::cout << str << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<std::string> strings = {"apple", "banana", "orange", "grape", "kiwi"};
    auto isDivisibleBy3 = isDivisibleBy(3);
    
    std::vector<std::string> divisibleStrings = search(strings, isDivisibleBy3);
    printDivisibleStrings(divisibleStrings);
    
    return 0;
}


