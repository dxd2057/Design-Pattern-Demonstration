#ifndef SOY_H
#define SOY_H

#include "Beverage.h"
#include "CondimentDecorator.h"
#include <memory>
#include <string>

class Soy : public CondimentDecorator {
    public:
        Soy() = default;
        Soy(std::unique_ptr<Beverage> beverage) : CondimentDecorator{std::move(beverage)} {}
        std::string getDescription() const override {
            return beverage->getDescription() + ", Soy";
        }
        inline double cost() const override {
            double cost = beverage->cost();
            switch (beverage->getSize()) {
                case Beverage::Size::TALL:
                    cost += 0.10;
                    break;
                case Beverage::Size::GRANDE:
                    cost += 0.15;
                    break;
                case Beverage::Size::VENTI:
                    cost += 0.20;
                    break;
                default:
                    break;
            }
            return cost;
        }
};

#endif