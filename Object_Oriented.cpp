#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

class LengthDivisibilityCriteria  {
private:
    int divisor;

public:
    LengthDivisibilityCriteria(int divisor) : divisor(divisor) {}

    bool satisfiesCriteria(const string& str) const{
        return str.length() % divisor == 0;
    }
};

class StringSearch {
public:
    static vector<string> search(const vector<string>& strings, const LengthDivisibilityCriteria& criteria) {
        vector<string> result;
        for (const string& str : strings) {
            if (criteria.satisfiesCriteria(str)) {
                result.push_back(str);
            }
        }
        return result;
    }
};


void printonTerminal(const vector<string>& divisibleStrings) {
    cout << "Strings with length divisible by divisor: ";
    for (const string& str : divisibleStrings) {
        cout << str << " ";
    }
    cout <<endl;
}

int main() {
    vector<string> strings = {"apple", "banana", "orange", "grape", "kiwi"};
    LengthDivisibilityCriteria isDivisibleBy3(3);
    
   vector<string> divisibleStrings = StringSearch::search(strings, isDivisibleBy3);
    printonTerminal(divisibleStrings);
    
    return 0;
}
