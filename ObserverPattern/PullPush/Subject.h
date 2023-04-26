#ifndef SUBJECT_H
#define SUBJECT_H

#include "DataObject.h"
#include "Observer.h"
#include <vector>
#include <algorithm>

class Subject {
    private:
        std::vector<Observer*> observers;
        bool changed = false;
    protected:
        void setChanged() {
            changed = true;
        }
        void clearChanged() {
            changed = false;
        }
        bool hasChanged() {
            return changed;
        }
    public:
        Subject() = default;
        virtual ~Subject() = default;
        void addObserver(Observer* o) {
            observers.push_back(o);
        }
        inline void deleteObserver(Observer* o) {
            if (observers.size() > 0) {
                observers.erase(std::remove(observers.begin(), observers.end(), o), observers.end());
            }
        }
        inline void notifyObservers(DataObject *arg = nullptr) {
            if (hasChanged()) {
                for (const auto &observer : observers) {
                    observer->update(this, arg);
                }
                clearChanged();
            }
        }
};

#endif