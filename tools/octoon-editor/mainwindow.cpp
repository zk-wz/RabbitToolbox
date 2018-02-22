#include <octoon/editor/mainwindow.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // dock
    viewDock = new QDockWidget(this);
    commandDock = new QDockWidget(this);

    // panel
    commandPanel = new QQuickWidget(commandDock);
    commandPanel->setSource(QUrl::fromLocalFile(":/qml/controls/OButton.qml"));
    viewPanel = new OViewWidget(viewDock);

    viewDock->setWidget(viewPanel);
    viewDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    viewDock->setWindowTitle("View Panel");

    commandDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    commandDock->setWidget(commandPanel);
    commandDock->setWindowTitle("Command Panel");
    this->setCentralWidget(viewDock);
    this->addDockWidget(Qt::RightDockWidgetArea,commandDock);
}

MainWindow::~MainWindow()
{
}
