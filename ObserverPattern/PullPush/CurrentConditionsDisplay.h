#ifndef CURRENT_CONDITIONS_DISPLAY
#define CURRENT_CONDITIONS_DISPLAY

#include "DataObject.h"
#include "DisplayElement.h"
#include "Observer.h"
#include "Subject.h"
#include "WeatherData.h"
#include <iostream>

class CurrentConditionDisplay : public Observer, public DisplayElement {
    private:
        double temperature{0};
        double humidity{0};
        Subject *observable;
    public:
        CurrentConditionDisplay() = default;
        CurrentConditionDisplay(Subject *sbj) : observable(sbj) {
            observable->addObserver(this);
        }
        inline void update(Subject *sbj, DataObject *arg) override {
            if (auto *wd = dynamic_cast<WeatherData*>(sbj)) {
                temperature = wd->getTemperature();
                humidity = wd->getHumidity();
                display();
            }
        }
        inline void display() const override {
            std::cout << "Current conditions: " << temperature << "F degrees and " << humidity << "\% humidity\n";
        }
};

#endif