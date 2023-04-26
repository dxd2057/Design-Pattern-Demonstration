#ifndef FORECAST_DISPLAY_H
#define FORECAST_DISPLAY_H

#include "DataObject.h"
#include "DisplayElement.h"
#include "Observer.h"
#include "Subject.h"
#include "WeatherData.h"
#include <iostream>

class ForecastDisplay : public Observer, public DisplayElement {
    private:
        double currentPressure{29.92};
        double lastPressure{0};
        Subject *observable = nullptr;
    public:
        ForecastDisplay() = default;
        ForecastDisplay(Subject *sbj) : observable(sbj) {
            observable->addObserver(this);
        }
        inline void update(Subject *sbj, DataObject *arg) override {
            if (auto *wd = dynamic_cast<WeatherData*>(sbj)) {
                lastPressure = currentPressure;
                currentPressure = wd->getPressure();
                display();
            }
        }
        inline void display() const override {
            std::cout << "Forecast: ";
            if (currentPressure > lastPressure) {
                std::cout << "Improving weather on the way!\n";
            } else if (currentPressure == lastPressure) {
                std::cout << "More of the same\n";
            } else if (currentPressure < lastPressure) {
                std::cout << "Watch out for cooler, rainy weather\n";
            }
        }
};

#endif