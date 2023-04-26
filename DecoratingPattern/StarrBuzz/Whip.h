#ifndef WHIP_H
#define WHIP_H

#include "Beverage.h"
#include "CondimentDecorator.h"
#include <memory>
#include <string>

class Whip : public CondimentDecorator {
    public:
        Whip() = default;
        Whip(std::unique_ptr<Beverage> beverage) : CondimentDecorator{std::move(beverage)} {}
        std::string getDescription() const override {
            return beverage->getDescription() + ", Whip";
        }
        inline double cost() const override {
            double cost = beverage->cost();
            switch (beverage->getSize()) {
                case Beverage::Size::TALL:
                    cost += 0.05;
                    break;
                case Beverage::Size::GRANDE:
                    cost += 0.1;
                    break;
                case Beverage::Size::VENTI:
                    cost += 0.15;
                    break;
                default:
                    break;
            }
            return cost;
        }
};

#endif