#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "Shape.h"
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <iostream>

#include "Square.h"
#include "Circle.h"

class Document {
public:
    using Id = unsigned int;

    Document(Id id) : id_(id) {
        std::cout << "[Document] Created document id=" << id_ << std::endl;
    }

    ~Document() {
        std::cout << "[Document] Destroyed document id=" << id_ << std::endl;
    }

    Id id() const { return id_; }

    void addShape(const ShapePtr& s) {
        shapes_.push_back(s);
        std::cout << "[Document] Added shape to document " << id_
                  << ": " << s->description() << std::endl;
    }

    bool removeShape(Shape::Id id) {
        auto it = std::find_if(shapes_.begin(), shapes_.end(),
            [id](const ShapePtr& s){ return s->id() == id; });
        if (it != shapes_.end()) {
            std::cout << "[Document] Removed shape from document " << id_
                      << ": " << (*it)->description() << std::endl;
            shapes_.erase(it);
            return true;
        }
        std::cout << "[Document] Shape with id=" << id
                  << " not found for removal" << std::endl;
        return false;
    }

    bool exportToFile(const std::string& path) const {
        std::cout << "[Document] Exporting document " << id_
                  << " to file: " << path << std::endl;
        std::cout << "[Document] Summary: " << shapes_.size()
                  << " shapes total" << std::endl;
        for (const auto& s : shapes_) {
            std::cout << "  - " << s->description() << std::endl;
        }
        return true;
    }

    bool importFromFile(const std::string& path) {
        std::cout << "[Document] Importing from file into document "
                  << id_ << ": " << path << std::endl;

        // Add sample shapes for demonstration
        addShape(std::make_shared<Square>(nextShapeId_++, 10.0));
        addShape(std::make_shared<Circle>(nextShapeId_++, 5.0));

        return true;
    }

    size_t shapeCount() const { return shapes_.size(); }

private:
    Id id_;
    std::vector<ShapePtr> shapes_;
    static inline Shape::Id nextShapeId_ = 1;
};

using DocumentPtr = std::shared_ptr<Document>;

#endif // DOCUMENT_H
