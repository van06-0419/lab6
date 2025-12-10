#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"

class Circle : public Shape {
public:
    Circle(Id id, double r) : Shape(id), radius_(r) {}
    virtual ~Circle() = default;

    std::string typeName() const override { return "Circle"; }

    std::string description() const override {
        std::ostringstream oss;
        oss << typeName() << "(id=" << id() << ", r=" << radius_ << ")";
        return oss.str();
    }

    double radius() const { return radius_; }

private:
    double radius_;
};

#endif // CIRCLE_H
