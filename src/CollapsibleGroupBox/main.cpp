#include "CollapsibleGroupBox.hpp"
#include <QApplication>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  QWidget widget;
  auto *layout = new QVBoxLayout;

  widget.setLayout(layout);

  auto *gb = new CollapsibleGroupBox("GroupBox Title");
  layout->addWidget(gb);
  {
    auto *layout = new QVBoxLayout;
    gb->setLayout(layout);
    auto *label1 = new QLabel("Label 1");
    layout->addWidget(label1);
    auto *label2 = new QLabel("Label 2");
    layout->addWidget(label2);
  }

  // Important to add this in the parent layout so the CollapsibleGroupBox can
  // truly collapse
  layout->addStretch();

  widget.show();
  return app.exec();
}