#pragma once

#include "Helper.hpp"
#include <QTimer>
#include <QWidget>

class Widget : public QWidget {
  Q_OBJECT

public:
  Widget(Helper *helper, QWidget *parent) : QWidget(parent), helper(helper) {
    elapsed = 0;
    setFixedSize(200, 200);
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