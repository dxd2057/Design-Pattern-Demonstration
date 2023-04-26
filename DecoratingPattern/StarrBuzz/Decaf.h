#ifndef DECAF_H
#define DECAF_H

#include "Beverage.h"

class Decaf : public Beverage {
    public:
        Decaf() {
            description = "Decaffeinated Coffee";
        }
        double cost() const override {
            return 1.05;
        }
};

#endif