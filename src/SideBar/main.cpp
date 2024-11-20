#include <QApplication>
#include <QDockWidget>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QToolBar>
#include <QVBoxLayout>

class MainWindow : public QMainWindow {
public:
  explicit MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
    // Central widget
    auto *centralWidget = new QWidget(this);
    auto *centralLayout = new QVBoxLayout(centralWidget);
    centralLayout->addWidget(new QLabel("Main Content Area", centralWidget));
    setCentralWidget(centralWidget);

    // Dock widget
    auto *dockWidget = new QDockWidget("Side Panel", this);
    dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea |
                                Qt::RightDockWidgetArea);

    // Content for the dock
    auto *dockContent = new QWidget(dockWidget);
    auto *dockLayout = new QVBoxLayout(dockContent);
    dockLayout->addWidget(new QLabel("Dock Content", dockContent));
    dockContent->setLayout(dockLayout);
    dockWidget->setWidget(dockContent);

    // Add the dock widget to the left side
    addDockWidget(Qt::LeftDockWidgetArea, dockWidget);

    // Toolbar with toggle action
    QToolBar *toolbar = addToolBar("Toolbar");
    QAction *toggleDockAction = toolbar->addAction("Toggle Dock");
    toggleDockAction->setCheckable(true);
    toggleDockAction->setChecked(true);

    connect(toggleDockAction, &QAction::toggled, dockWidget,
            &QDockWidget::setVisible);
    connect(dockWidget, &QDockWidget::visibilityChanged, toggleDockAction,
            &QAction::setChecked);
  }
};

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  MainWindow mainWindow;
  mainWindow.resize(800, 600);
  mainWindow.show();

  return app.exec();
}
