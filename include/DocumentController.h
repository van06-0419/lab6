#ifndef DOCUMENT_CONTROLLER_H
#define DOCUMENT_CONTROLLER_H

#include "Document.h"
#include "Shape.h"
#include "Square.h"
#include "Circle.h"
#include "IView.h"

#include <memory>
#include <string>
#include <iostream>

class DocumentController : public std::enable_shared_from_this<DocumentController> {
public:
    DocumentController() = default;

    void attachView(std::weak_ptr<IView> view) {
        view_ = view;
    }

    std::shared_ptr<Document> newDocument() {
        auto doc = std::make_shared<Document>(nextDocId_++);
        model_ = doc;
        std::cout << "[Controller] Created document " << doc->id() << std::endl;
        notifyViewDocChanged();
        return doc;
    }

    bool importDocument(const std::string& path) {
        ensureModel();
        std::cout << "[Controller] Importing from file: " << path << std::endl;
        model_->importFromFile(path);
        notifyViewDocChanged();
        return true;
    }

    bool exportDocument(const std::string& path) {
        if (!model_) {
            std::cout << "[Controller] No active document. Export failed." << std::endl;
            return false;
        }
        std::cout << "[Controller] Exporting to file: " << path << std::endl;
        model_->exportToFile(path);
        return true;
    }

    Shape::Id createSquare(double side) {
        ensureModel();
        auto id = allocateShapeId();
        auto s = std::make_shared<Square>(id, side);
        model_->addShape(s);
        notifyViewDocChanged();
        return id;
    }

    Shape::Id createCircle(double r) {
        ensureModel();
        auto id = allocateShapeId();
        auto s = std::make_shared<Circle>(id, r);
        model_->addShape(s);
        notifyViewDocChanged();
        return id;
    }

    bool deleteShape(Shape::Id id) {
        if (!model_) {
            std::cout << "[Controller] No active document. Cannot delete shape." << std::endl;
            return false;
        }
        bool ok = model_->removeShape(id);
        notifyViewDocChanged();
        return ok;
    }

    std::shared_ptr<Document> currentDocument() const { return model_; }

private:
    void ensureModel() {
        if (!model_) {
            model_ = newDocument();
        }
    }

    void notifyViewDocChanged() {
        if (auto v = view_.lock()) {
            v->onDocumentChanged(model_);
        }
    }

    Shape::Id allocateShapeId() {
        static Shape::Id s_id = 100;
        return s_id++;
    }

private:
    std::shared_ptr<Document> model_;
    std::weak_ptr<IView> view_;
    static inline Document::Id nextDocId_ = 1;
};

using DocumentControllerPtr = std::shared_ptr<DocumentController>;

#endif // DOCUMENT_CONTROLLER_H
