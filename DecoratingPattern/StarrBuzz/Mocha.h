#ifndef MOCHA_H
#define MOCHA_H

#include "Beverage.h"
#include "CondimentDecorator.h"
#include <memory>
#include <string>

class Mocha : public CondimentDecorator {
    public:
        Mocha() = default;
        Mocha(std::unique_ptr<Beverage> beverage) : CondimentDecorator{std::move(beverage)} {}
        std::string getDescription() const override {
            return beverage->getDescription() + ", Mocha";
        }
        inline double cost() const override {
            double cost = beverage->cost();
            switch (beverage->getSize()) {
                case Beverage::Size::TALL:
                    cost += 0.15;
                    break;
                case Beverage::Size::GRANDE:
                    cost += 0.2;
                    break;
                case Beverage::Size::VENTI:
                    cost += 0.25;
                    break;
                default:
                    break;
            }
            return cost;
        }
};

#endif