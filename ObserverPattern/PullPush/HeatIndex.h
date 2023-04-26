#ifndef HEAT_INDEX_H
#define HEAT_INDEX_H

#include "DataObject.h"
#include "DisplayElement.h"
#include "Subject.h"
#include "Observer.h"
#include "WeatherData.h"
#include <iostream>

double computeHeatIndex(const double t, const double rh) {
    double index = (16.923 + (0.185212 * t) + (5.37941 * rh) - (0.100254 * t * rh) + (0.00941695 * (t * t)) + (0.00728898 * (rh * rh)) + (0.000345372 * (t * t * rh)) - (0.000814971 * (t * rh * rh)) + (0.0000102102 * (t * t * rh * rh)) - (0.000038646 * (t * t * t)) + (0.0000291583 * (rh * rh * rh)) + (0.00000142721 * (t * t * t * rh)) + (0.000000197483 * (t * rh * rh * rh)) - (0.0000000218429 * (t * t * t * rh * rh)) + 0.000000000843296 * (t * t * rh * rh * rh)) - (0.0000000000481975 * (t * t * t * rh * rh * rh));
    return index;
}

class HeatIndexDisplay : public Observer, public DisplayElement {
    private:
        double heatIndex{0};
        Subject *observable = nullptr;
    public:
        HeatIndexDisplay() = default;
        HeatIndexDisplay(Subject *sbj) : observable(sbj) {
            observable->addObserver(this);
        }
        inline void update(Subject *sbj, DataObject *arg) override {
            if (auto *wd = dynamic_cast<WeatherData*>(sbj)) {
                heatIndex = computeHeatIndex(wd->getTemperature(), wd->getHumidity());
                display();
            }
        }
        inline void display() const override {
            std::cout << "Heat index is " << heatIndex << '\n';
        }
};

#endif