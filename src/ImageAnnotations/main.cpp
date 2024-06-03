#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QVBoxLayout>
#include <QWidget>

#include "LineAnnotation.hpp"

class AnnotationView : public QGraphicsView {
public:
    explicit AnnotationView(QWidget *parent = nullptr) : QGraphicsView(parent) {
        setRenderHint(QPainter::Antialiasing);
        setRenderHint(QPainter::SmoothPixmapTransform);
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget mainWindow;
    QVBoxLayout layout(&mainWindow);

    auto *view = new AnnotationView;
    auto *scene = new QGraphicsScene;

    // Load and display an image
    QPixmap image("path/to/your/image.png");
    auto *imageItem = new QGraphicsPixmapItem(image);
    scene->addItem(imageItem);

    // Add line and box annotations
    auto *line = new LineAnnotation(QPointF(50, 50), QPointF(200, 200), Qt::blue);
    scene->addItem(line);

    auto *box = new BoxAnnotation(QRectF(100, 100, 150, 100), Qt::blue);
    scene->addItem(box);

    view->setScene(scene);
    layout.addWidget(view);
    mainWindow.setLayout(&layout);
    mainWindow.show();

    return app.exec();
}