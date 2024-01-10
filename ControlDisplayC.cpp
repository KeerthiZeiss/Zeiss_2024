#include <iostream>
#include <string>
using namespace std;
class ConsoleDisplay {
private:
    string content;

public:
    void setContent(const string& value) {
        content = value;
    }
    void display() const {
        cout << "Content: " << content <<endl;
    }
};

int main() {
   ConsoleDisplay ConsoleDisplay;
    ConsoleDisplay.setContent("Its Keerthi!");
   ConsoleDisplay.display();
    return 0;
}
