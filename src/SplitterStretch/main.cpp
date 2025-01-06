#include <QApplication>
#include <QPushButton>
#include <QSplitter>
#include <QTextEdit>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  QSplitter *splitter = new QSplitter;

  QTextEdit *textEdit1 = new QTextEdit("Text Edit 1");
  QTextEdit *textEdit2 = new QTextEdit("Text Edit 2");

  splitter->addWidget(textEdit1);
  splitter->addWidget(textEdit2);

  // Set the stretch factor
  splitter->setStretchFactor(
      0, 1); // This makes textEdit1 expand more than textEdit2
  splitter->setStretchFactor(
      1,
      3); // This gives textEdit2 three times the amount of space as textEdit1

  splitter->show();

  return app.exec();
}
