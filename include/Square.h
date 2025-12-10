#ifndef SQUARE_H
#define SQUARE_H

#include "Shape.h"

class Square : public Shape {
public:
    Square(Id id, double side) : Shape(id), side_(side) {}
    virtual ~Square() = default;

    std::string typeName() const override { return "Square"; }

    std::string description() const override {
        std::ostringstream oss;
        oss << typeName() << "(id=" << id() << ", side=" << side_ << ")";
        return oss.str();
    }

    double side() const { return side_; }

private:
    double side_;
};

#endif // SQUARE_H
