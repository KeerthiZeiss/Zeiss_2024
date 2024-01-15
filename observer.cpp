#include <iostream>
#include <vector>
#include <algorithm>

class Thread;

class IObserver {
public:
   virtual void update(Thread* thread, int threadId) = 0;
};

class Thread {
    int id;
    std::string state;
    int priority;
    int culture;
    std::vector<IObserver*> observers;
    void notifyObservers() {
        for (auto observer : observers) {
            observer->update(this,id);
        }
    }

public:
 void setId(int threadId) {
        id = threadId;
    }
    void start() {
        state = "starting";
        notifyObservers();
    }

    void abort() {
        state = "aborting";
        notifyObservers();
    }

    void sleep() {
        state = "sleeping";
        notifyObservers();
    }

    void wait() {
        state = "wait";
        notifyObservers();
    }

    void suspended() {
        state = "suspended";
        notifyObservers();
    }

    std::string getState() const {
        return state;
    }
    void subscribe(IObserver* observer) {
        observers.push_back(observer);
    }

    void unsubscribe(IObserver* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }
    int getId() const {
        return id;
    }
};
class ConcreteObserver : public IObserver {
public:
    void update(Thread* thread, int threadId) override {
        std::cout << "Thread " << threadId << " has been updated. New state: " << thread->getState() << std::endl;
    }
};

int main() {
   Thread myThread;
    myThread.setId(1); 

    ConcreteObserver observer1;
    ConcreteObserver observer2;

    myThread.subscribe(&observer1);
    myThread.subscribe(&observer2);

    myThread.start();
    myThread.sleep();

    myThread.unsubscribe(&observer1);

    myThread.abort();

    return 0;
}
