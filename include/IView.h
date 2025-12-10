#ifndef IVIEW_H
#define IVIEW_H

#include <memory>
#include <string>
#include "Document.h"

class IView {
public:
    virtual ~IView() = default;

    virtual void onNewDocumentRequested() = 0;
    virtual void onImportRequested(const std::string& path) = 0;
    virtual void onExportRequested(const std::string& path) = 0;
    virtual void onCreateSquareRequested(double side) = 0;
    virtual void onCreateCircleRequested(double r) = 0;
    virtual void onDeleteShapeRequested(Shape::Id id) = 0;

    virtual void onDocumentChanged(std::shared_ptr<Document> doc) = 0;
};

#endif // IVIEW_H
