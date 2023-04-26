#include <iostream>
#include <vector>
#include <algorithm>

class Observer {
    public:
        virtual ~Observer() = default;
        virtual void update(double temp, double humidity, double pressure) = 0;
};

class Subject {
    public:
        virtual ~Subject() = default;
        virtual void registerObserver(Observer* o) = 0;
        virtual void removeObserver(Observer* o) = 0;
        virtual void notifyObservers() = 0;
};

class DisplayElement {
    public:
        virtual ~DisplayElement() = default;
        virtual void display() = 0;
};

class WeatherData : public Subject {
    private:
        std::vector<Observer*> observers;
        double temperature{0};
        double humidity{0};
        double pressure{0};
    public:
        WeatherData() = default;
        void registerObserver(Observer* o) override {
            observers.push_back(o);
        }
        void removeObserver(Observer* o) override {
            if (observers.size() > 0) {
                observers.erase(std::remove(observers.begin(), observers.end(), o), observers.end());
            }
        }
        void notifyObservers() override {
            for (auto& observer : observers) {
                observer->update(temperature, humidity, pressure);
            }
        }
        void measurementChanged() {
            notifyObservers();
        }
        void setMeasurements(const double &temp, const double &hum, const double &press) {
            temperature = temp;
            humidity = hum;
            pressure = press;
            measurementChanged();
        }
};

class CurrentConditionsDisplay : public Observer, public DisplayElement {
    private:
        double temperature{0};
        double humidity{0};
        Subject *weatherData = nullptr;

    public:
        CurrentConditionsDisplay() = default;
        CurrentConditionsDisplay(Subject *weatherData) : weatherData{weatherData} {
            weatherData->registerObserver(this);
        }
        void update(double temp, double humidity, double pressure) override {
            this->temperature = temp;
            this->humidity = humidity;
            display();
        }
        void display() override {
            std::cout << "Current conditions: " << temperature << "F degrees and " << humidity << "\% humidity\n";
        }
};

class StatisticsDisplay : public Observer, public DisplayElement {
    private:
        double minTemp{200};
        double maxTemp{0};
        double tempSum{0};
        int numReadings{0};
        Subject *weatherData = nullptr;
    
    public:
        StatisticsDisplay() = default;
        StatisticsDisplay(Subject *weatherData) : weatherData{weatherData} {
            weatherData->registerObserver(this);
        }
        void update(double temp, double humidity, double pressure) override {
            tempSum += temp;
            ++numReadings;
            if (temp > maxTemp) {
                maxTemp = temp;
            }
            if (temp < minTemp) {
                minTemp = temp;
            }
            display();
        }
        void display() override {
            std::cout << "Avg/Max/Min temperature = " << (tempSum / numReadings) << "/" << maxTemp << "/" << minTemp << '\n';
        }
};

class ForecastDisplay : public Observer, public DisplayElement {
    private:
        double currentPressure{29.92};
        double lastPressure{0};
        Subject *weatherData = nullptr;
    public:
        ForecastDisplay() = default;
        ForecastDisplay(Subject *weatherData) : weatherData{weatherData} {
            weatherData->registerObserver(this);
        }
        void update(double temp, double humidity, double pressure) override {
            lastPressure = currentPressure;
            currentPressure = pressure;
            display();
        }
        void display() override {
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

double computeHeatIndex(const double &t, const double &rh) {
    double index = (double)((16.923 + (0.185212 * t) + (5.37941 * rh) - (0.100254 * t * rh) 
				+ (0.00941695 * (t * t)) + (0.00728898 * (rh * rh)) 
				+ (0.000345372 * (t * t * rh)) - (0.000814971 * (t * rh * rh)) +
				(0.0000102102 * (t * t * rh * rh)) - (0.000038646 * (t * t * t)) + (0.0000291583 * 
					(rh * rh * rh)) + (0.00000142721 * (t * t * t * rh)) + 
				(0.000000197483 * (t * rh * rh * rh)) - (0.0000000218429 * (t * t * t * rh * rh)) +
				0.000000000843296 * (t * t * rh * rh * rh)) - (0.0000000000481975 * (t * t * t * rh * rh * rh)));

	return index;
}

class HeatIndex : public Observer, public DisplayElement {
    private:
        double heatIndex{0};
        Subject *weatherData = nullptr;
    public:
        HeatIndex() = default;
        HeatIndex(Subject *weatherData) : weatherData{weatherData} {
            weatherData->registerObserver(this);
        }
        void update(double temp, double humidity, double pressure) {
            heatIndex = computeHeatIndex(temp, humidity);
            display();
        }
        void display() {
            std::cout << "Heat index is " << heatIndex << '\n';
        }
};

int main() {
    WeatherData weatherData;
    CurrentConditionsDisplay currentDisplay(&weatherData);
    StatisticsDisplay statisticsDisplay(&weatherData);
    ForecastDisplay forecastDisplay(&weatherData);
    HeatIndex heatIndex(&weatherData);

    weatherData.setMeasurements(80, 65, 30.4);
    weatherData.setMeasurements(82, 70, 29.2);
    weatherData.setMeasurements(78, 90, 29.2);

    return 0;
}