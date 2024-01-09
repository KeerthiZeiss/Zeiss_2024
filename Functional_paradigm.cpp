#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

bool isEven(int num) {
    return num % 2 == 0;
}

std::vector<int> search(const std::vector<int>& nums, std::function<bool(int)> isEven) {
    std::vector<int> result;
    for (int num : nums) {
        if (isEven(num)) {
            result.push_back(num);
        }
    }
    return result;
}

void printevennumbers(std::vector<int> evenNumbers) { 
    std::cout << "Even numbers: ";
    for (int num : evenNumbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> evenNumbers = search(numbers, isEven);
    printevennumbers(evenNumbers); 
    return 0;
}
