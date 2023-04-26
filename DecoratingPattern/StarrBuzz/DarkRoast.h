#ifndef DARK_ROAST_H
#define DARK_ROAST_H

#include "Beverage.h"

class DarkRoast : public Beverage {
    public:
        DarkRoast() {
            description = "Most Excellent Dark Roast";
        }
        double cost() const override {
            return 0.99;
        }
};

#endif