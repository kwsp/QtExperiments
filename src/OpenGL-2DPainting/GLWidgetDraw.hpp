#pragma once

#include "Helper.hpp"
#include <QTimer>
#include <QtOpenGLWidgets/QtOpenGLWidgets>

class GLWidget : public QOpenGLWidget {
  Q_OBJECT

public:
  GLWidget(Helper *helper, QWidget *parent)
      : QOpenGLWidget(parent), helper(helper) {
    elapsed = 0;
    setFixedSize(200, 200);
    setAutoFillBackground(false);
  }

public slots:
  void animate() {
    elapsed = (elapsed + qobject_cast<QTimer *>(sender())->interval()) % 1000;
    update();
  }

protected:
  void paintEvent(QPaintEvent *event) override {
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    helper->paint(&painter, event, elapsed);
    painter.end();
  }

private:
  Helper *helper;
  int elapsed;
};