#include <octoon/editor/mainwindow.h>

MainWindow::MainWindow(QWidget *parent) :
    OMainWindow(parent)
{
	// menu
	menuBar = new QMenuBar(this);
	QMenu *fileMenu = new QMenu(tr("File"), this);
	QMenu *editMenu = new QMenu(tr("Edit"), this);
	QMenu *viewMenu = new QMenu(tr("View"), this);
	QMenu *helpMenu = new QMenu(tr("Help"), this);

	menuBar->addMenu(fileMenu);
	menuBar->addMenu(editMenu);
	menuBar->addMenu(viewMenu);
	menuBar->addMenu(helpMenu);
	this->setMenuBar(menuBar);

    // dock
    viewDock = new ODockWidget(this);
    commandDock = new ODockWidget(this);
    hierarchyDock = new ODockWidget(this);
	materialDock = new ODockWidget(this);

    // panel
    commandPanel = new QQuickWidget(commandDock);
    commandPanel->setSource(QUrl::fromLocalFile(QApplication::applicationDirPath() + "/qml/controls/OButton.qml"));
    hierarchyPanel = new QQuickWidget(hierarchyDock);
    hierarchyPanel->setSource(QUrl::fromLocalFile(QApplication::applicationDirPath() + "/qml/controls/OButton.qml"));
	materialPanel = new QQuickWidget(materialDock);
	materialPanel->setSource(QUrl::fromLocalFile(QApplication::applicationDirPath() + "/qml/material_panel.qml"));
    viewPanel = new OViewWidget(viewDock);

    viewDock->setWidget(viewPanel);
    viewDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    viewDock->setWindowTitle("View Panel");

    commandDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    commandDock->setWidget(commandPanel);
    commandDock->setWindowTitle("Command Panel");

	hierarchyDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	hierarchyDock->setWidget(hierarchyPanel);
	hierarchyDock->setWindowTitle("Hierarchy Panel");

	materialDock->setAllowedAreas(Qt::BottomDockWidgetArea | Qt::TopDockWidgetArea);
	materialDock->setWidget(materialPanel);
	materialDock->setWindowTitle("Material Panel");

    this->setCentralWidget(viewDock);
    this->addDockWidget(Qt::RightDockWidgetArea,commandDock);
    this->addDockWidget(Qt::LeftDockWidgetArea,hierarchyDock);
	this->addDockWidget(Qt::BottomDockWidgetArea, materialDock);
}

MainWindow::~MainWindow()
{
}
