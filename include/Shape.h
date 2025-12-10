#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <sstream>
#include <memory>

class Shape {
public:
    using Id = unsigned int;
    Shape(Id id) : id_(id) {}
    virtual ~Shape() = default;

    Shape(const Shape&) = delete;
    Shape& operator=(const Shape&) = delete;

    Shape(Shape&&) = default;
    Shape& operator=(Shape&&) = default;

    Id id() const { return id_; }

    virtual std::string typeName() const = 0;
    virtual std::string description() const {
        std::ostringstream oss;
        oss << typeName() << "(id=" << id_ << ")";
        return oss.str();
    }

private:
    Id id_;
};

using ShapePtr = std::shared_ptr<Shape>;

#endif // SHAPE_H
