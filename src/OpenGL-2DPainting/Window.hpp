#pragma once

#include "GLWidgetDraw.hpp"
#include "WidgetDraw.hpp"
#include <QWidget>

class Window : public QWidget {
  Q_OBJECT

public:
  Window() {
    setWindowTitle(tr("2D Painting on Native and OpenGL Widgets"));

    auto *native = new Widget(&helper, this);
    auto *openGL = new GLWidget(&helper, this);
    auto *nativeLabel = new QLabel(tr("Native"));
    nativeLabel->setAlignment(Qt::AlignHCenter);
    auto *openGLLabel = new QLabel(tr("OpenGL"));
    openGLLabel->setAlignment(Qt::AlignHCenter);

    auto *layout = new QGridLayout;
    layout->addWidget(native, 0, 0);
    layout->addWidget(openGL, 0, 1);
    layout->addWidget(nativeLabel, 1, 0);
    layout->addWidget(openGLLabel, 1, 1);
    setLayout(layout);

    // Native: 28% CPU on M1
    // OpenGL: 20% CPU on M1
    // Both: 34% CPU
    auto *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, native, &Widget::animate);
    connect(timer, &QTimer::timeout, openGL, &GLWidget::animate);
    timer->start(20);
  }

private:
  Helper helper;
};