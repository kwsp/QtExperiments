#include <QApplication>
#include <QGestureEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPinchGesture>
#include <QVBoxLayout>
#include <QWidget>

#include "LineAnnotation.hpp"

class AnnotationView : public QGraphicsView {
public:
  explicit AnnotationView(QWidget *parent = nullptr)
      : QGraphicsView(parent), m_scene(new QGraphicsScene) {
    setScene(m_scene);

    setRenderHint(QPainter::Antialiasing);
    setRenderHint(QPainter::SmoothPixmapTransform);

    setDragMode(DragMode::ScrollHandDrag);
    viewport()->setAttribute(Qt::WA_AcceptTouchEvents);
    grabGesture(Qt::PinchGesture);
  }

  auto scene() -> QGraphicsScene * { return m_scene; }

protected:
  bool event(QEvent *event) override {
    if (event->type() == QEvent::Gesture) {
      return gestureEvent(static_cast<QGestureEvent *>(event));
    }
    return QGraphicsView::event(event);
  }

private:
  bool gestureEvent(QGestureEvent *event) {
    if (QGesture *pinch = event->gesture(Qt::PinchGesture)) {
      pinchTriggered(static_cast<QPinchGesture *>(pinch));
    }
    return true;
  }

  void pinchTriggered(QPinchGesture *gesture) {
    if (gesture->state() == Qt::GestureState::GestureUpdated) {
      const qreal scaleFactor = gesture->scaleFactor();
      m_scaleFactor = m_scaleFactor * scaleFactor;
      QTransform transform;
      transform.scale(m_scaleFactor, m_scaleFactor);
      setTransform(transform);
    }
  }

  qreal m_scaleFactor{1.0};

  QGraphicsScene *m_scene;
};

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  QWidget mainWindow;
  QVBoxLayout layout(&mainWindow);

  auto *view = new AnnotationView;
  auto *scene = view->scene();

  // Load and display an image
  QPixmap image("path/to/your/image.png");
  auto *imageItem = new QGraphicsPixmapItem(image);
  scene->addItem(imageItem);

  // Add line and box annotations
  auto *line = new LineAnnotation(QPointF(50, 50), QPointF(200, 200), Qt::blue);
  scene->addItem(line);

  auto *box = new BoxAnnotation(QRectF(100, 100, 150, 100), Qt::blue);
  scene->addItem(box);

  layout.addWidget(view);
  mainWindow.setLayout(&layout);
  mainWindow.show();

  return app.exec();
}