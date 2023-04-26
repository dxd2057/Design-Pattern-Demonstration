#ifndef WEATHER_DATA_H
#define WEATHER_DATA_H

#include "Subject.h"
#include "Observer.h"

class WeatherData : public Subject {
    private:
        double temperature{0};
        double humidity{0};
        double pressure{0};
    public:
        WeatherData() = default;
        inline void measurementsChanged() {
            setChanged();
            notifyObservers();
        }
        inline void setMeasurements(const double &temp, const double &hum, const double &press) {
            temperature = temp;
            humidity = hum;
            pressure = press;
            measurementsChanged();
        }
        double getTemperature() {
            return temperature;
        }
        double getHumidity() {
            return humidity;
        }
        double getPressure() {
            return pressure;
        }
};

#endif