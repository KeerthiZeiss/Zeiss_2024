#include <iostream>
#include <string>
#include <vector>
using namespace std;
class SearchStrategy {
public:
    virtual bool invoke(const string& content) const = 0;
    virtual ~SearchStrategy() = default;
};
class StartsWithStrategy : public SearchStrategy {
private:
    string startsWith;

public:
    void setStartsWith(const string& value) {
        startsWith = value;
    }

    bool invoke(const string& content) const override {
        return content.substr(0, startsWith.size()) == startsWith;
    }
};

class SelectionFilter {
private:
    SearchStrategy* searchStrategy;  

public:
    void setFilter(SearchStrategy* strategy) {
        searchStrategy = strategy;
    }

    vector<string> filter(const vector<string>& contentList) const {
        vector<string> result;
        for (const auto& content : contentList) {
            if (searchStrategy->invoke(content)) {
                result.push_back(content);
            }
        }
        return result;
    }
};

int main() {
    vector<string> strings = {"Its Keerthi!", "Kite", "Apple", "Banana", "Kiwi"};
    SearchStrategy* startsWithStrategy = new StartsWithStrategy();
    dynamic_cast<StartsWithStrategy*>(startsWithStrategy)->setStartsWith("K"); 

    SelectionFilter selectionFilter;
    selectionFilter.setFilter(startsWithStrategy);

    vector<string> filteredStrings = selectionFilter.filter(strings);

    for (const auto& str : filteredStrings) {
        cout << str << " ";
    }
    delete startsWithStrategy;

    return 0;
}
