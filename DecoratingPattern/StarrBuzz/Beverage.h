#ifndef BEVERAGE_H
#define BEVERAGE_H

#include <string>

class Beverage {
    public:
        enum class Size {TALL, GRANDE, VENTI};
        Beverage() = default;
        virtual ~Beverage() = default;
        virtual std::string getDescription() const {
            return description;
        }
        virtual double cost() const = 0;
        virtual void setSize(Size s) {
            size = s;
        }
        virtual Size getSize() const {
            return size;
        }
        virtual inline std::string getSizeString() const {
            switch (size) {
                case Size::TALL:
                    return "Tall";
                case Size::GRANDE:
                    return "Grande";
                case Size::VENTI:
                    return "Venti";
                default:
                    return "Unknown";
            }
        }
    protected:
        std::string description{"Unknown Beverage"};
        Size size{Size::TALL};
};

#endif