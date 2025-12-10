#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <chrono>

#include "../include/IView.h"
#include "../include/DocumentController.h"

// 我们在 main.cpp 中实现 ConsoleView，它同时包含“事件处理函数”
class ConsoleView : public IView, public std::enable_shared_from_this<ConsoleView> {
public:
    ConsoleView(std::shared_ptr<DocumentController> controller)
        : controller_(controller) {
        controller_->attachView(shared_from_this());
    }

    // IView 事件：这些函数通常由 GUI 事件触发（这里直接被 main 调用）
    void onNewDocumentRequested() override {
        std::cout << "[View] New document requested\n";
        controller_->newDocument();
    }

    void onImportRequested(const std::string& path) override {
        std::cout << "[View] Import requested: " << path << std::endl;
        controller_->importDocument(path);
    }

    void onExportRequested(const std::string& path) override {
        std::cout << "[View] Export requested: " << path << std::endl;
        controller_->exportDocument(path);
    }

    void onCreateSquareRequested(double side) override {
        std::cout << "[View] Create Square requested (side=" << side << ")\n";
        auto id = controller_->createSquare(side);
        std::cout << "[View] 创建了图元 id=" << id << " (Square)\n";
    }

    void onCreateCircleRequested(double r) override {
        std::cout << "[View] Create Circle requested (r=" << r << ")\n";
        auto id = controller_->createCircle(r);
        std::cout << "[View] 创建了图元 id=" << id << " (Circle)\n";
    }

    void onDeleteShapeRequested(Shape::Id id) override {
        std::cout << "[View] Delete Shape requested id=" << id << std::endl;
        controller_->deleteShape(id);
    }

    // 模型更新回调
    void onDocumentChanged(std::shared_ptr<Document> doc) override {
        std::cout << "[View] Document changed. 当前文档 id=" << (doc ? doc->id() : 0)
                  << " 图元数=" << (doc ? doc->shapeCount() : 0) << std::endl;
    }

private:
    std::shared_ptr<DocumentController> controller_;
};


// 简单的“GUI 事件驱动”模拟：在 main 中创建 view/controller，并顺序触发事件。
// 要点：GUI 事件处理函数（如按钮回调）与 main 放在同一文件（满足实验要求）。
int main() {
    std::cout << "=== 简易矢量编辑器（架构演示） ===\n";

    auto controller = std::make_shared<DocumentController>();

    // 由于 ConsoleView 构造需要 shared_from_this()，我们先创建空 shared_ptr，再初始化
    std::shared_ptr<ConsoleView> view;
    {
        // 临时 lambda 来完成 enable_shared_from_this 的正确初始化顺序
        auto mk = [&](){
            auto ptr = std::make_shared<ConsoleView>(controller);
            return ptr;
        };
        view = mk();
    }

    // 模拟：用户点击“新建文档”
    view->onNewDocumentRequested();

    // 模拟：用户导入文件
    view->onImportRequested("demo_import.vg");

    // 模拟：用户创建图元（按钮事件）
    view->onCreateSquareRequested(44.0); // 创建边长为 44 的正方形
    view->onCreateCircleRequested(8.5);  // 创建半径为 8.5 的圆

    // 模拟：删除某个图元（按 id）
    view->onDeleteShapeRequested(100); // 示例 id（可能存在或不存在）

    // 模拟：导出当前文档
    view->onExportRequested("demo_export.vg");

    std::cout << "=== 演示结束 ===\n";
    return 0;
}
