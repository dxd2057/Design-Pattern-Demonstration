#ifndef STATISTICS_DISPLAY_H
#define STATISTICS_DISPLAY_H

#include "DataObject.h"
#include "DisplayElement.h"
#include "Subject.h"
#include "Observer.h"
#include "WeatherData.h"
#include <iostream>

class StatisticsDisplay : public Observer, public DisplayElement {
    private:
        double minTemp{200};
        double maxTemp{0};
        double tempSum{0};
        int numOfReadings{0};
        Subject *weatherData = nullptr;
    public:
        StatisticsDisplay() = default;
        StatisticsDisplay(Subject *wd) : weatherData(wd) {
            weatherData->addObserver(this);
        }
        inline void update(Subject *sbj, DataObject *arg) override {
            if (auto *wd = dynamic_cast<WeatherData*>(sbj)) {
                double temp = wd->getTemperature();
                tempSum += temp;
                ++numOfReadings;
                if (temp > maxTemp) {
                    maxTemp = temp;
                }
                if (temp < minTemp) {
                    minTemp = temp;
                }
                display();
            }
        }
        inline void display() const override {
            std::cout << "Avg/Max/Min temperature = " << (tempSum / numOfReadings) << "/" << maxTemp << "/" << minTemp << '\n';
        }
};

#endif