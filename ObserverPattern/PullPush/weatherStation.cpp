#include "WeatherData.h"
#include "CurrentConditionsDisplay.h"
#include "StatisticsDisplay.h"
#include "ForecastDisplay.h"
#include "HeatIndex.h"


#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    WeatherData weatherData;
    CurrentConditionDisplay currentDisplay(&weatherData);
    StatisticsDisplay statisticsDisplay(&weatherData);
    ForecastDisplay forecastDisplay(&weatherData);
    HeatIndexDisplay heatIndex(&weatherData);

    weatherData.setMeasurements(80, 65, 30.4);
    weatherData.setMeasurements(82, 70, 29.2);
    weatherData.setMeasurements(78, 90, 29.2);

    return 0;
}