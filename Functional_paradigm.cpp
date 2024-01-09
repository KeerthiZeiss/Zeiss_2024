#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
bool isStringLengthEven(const std::string& str) {
    return str.length() % 2 == 0;
}

std::vector<std::string> search(const std::vector<std::string>& strings, std::function<bool(const std::string&)> filter) {
    std::vector<std::string> result;
    for (const std::string& str : strings) {
        if (filter(str)) {
            result.push_back(str);
        }
    }
    return result;
}

void printEvenStrings(const std::vector<std::string>& evenStrings) {
    std::cout << "Strings with even length: ";
    for (const std::string& str : evenStrings) {
        std::cout << str << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<std::string> strings = {"apple", "banana", "orange", "grape", "kiwi"};
    std::vector<std::string> evenStrings = search(strings, isStringLengthEven);
    printEvenStrings(evenStrings);
    return 0;
}

