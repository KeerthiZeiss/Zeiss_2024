#include <iostream>
#include <string>
#include <vector>
using namespace std;

class StartsWithStrategy {
private:
    string startsWith;

public:
    void setStartsWith(const string& value) {
        startsWith = value;
    }

    bool invoke(const string& content) const {
        return content.substr(0, startsWith.size()) == startsWith;
    }
};

class SelectionFilter {
private:
    StartsWithStrategy startsWithStrategy;

public:
    void setFilter(const StartsWithStrategy& strategy) {
        startsWithStrategy = strategy;
    }

    vector<string> filter(const vector<string>& contentList) const {
        vector<string> result;
        for (const auto& content : contentList) {
            if (startsWithStrategy.invoke(content)) {
                result.push_back(content);
            }
        }
        return result;
    }
};

int main() {
    vector<string> strings = {"Its Keerthi!", "Kite", "Apple", "Banana", "Kiwi"};

    StartsWithStrategy startsWithStrategy;
    startsWithStrategy.setStartsWith("K");

    SelectionFilter selectionFilter;
    selectionFilter.setFilter(startsWithStrategy);

    vector<string> filteredStrings = selectionFilter.filter(strings);

    for (const auto& str : filteredStrings) {
        cout << str << " ";
    }

    return 0;
}
