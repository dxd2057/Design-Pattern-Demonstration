#ifndef CONDIMENT_DECORATOR_H
#define CONDIMENT_DECORATOR_H

#include "Beverage.h"
#include <memory>

class CondimentDecorator : public Beverage {
    protected:
        std::unique_ptr<Beverage> beverage;
    public:
        CondimentDecorator() = default;
        CondimentDecorator(std::unique_ptr<Beverage> b) : beverage{std::move(b)} {}
        virtual std::string getDescription() const override {
            return "Unknown Condiment";
        }
        void setSize(Size s) override {
            beverage->setSize(s);
        }
        Beverage::Size getSize() const override {
            return beverage->getSize();
        }
        std::string getSizeString() const override {
            return beverage->getSizeString();
        }
};

#endif