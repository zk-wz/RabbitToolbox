#include <octoon/editor/mainwindow.h>

MainWindow::MainWindow(QWidget *parent) :
    OMainWindow(parent)
{
	this->setWindowTitle("Octoon Studio");
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

	fileMenu->addAction(tr("New"));
	fileMenu->addAction(tr("Open"));

	this->setMenuBar(menuBar);

    // dock
    viewDock = new ODockWidget(this);
    commandDock = new ODockWidget(this);
    hierarchyDock = new ODockWidget(this);
	materialDock = new ODockWidget(this);

    // panel
    commandPanel = new QQuickWidget;
	commandPanel->setResizeMode(QQuickWidget::SizeViewToRootObject);
    commandPanel->setSource(QUrl::fromLocalFile(QApplication::applicationDirPath() + "/qml/controls/OButton.qml"));
	
    hierarchyPanel = new QQuickWidget;
	hierarchyPanel->setResizeMode(QQuickWidget::SizeViewToRootObject);
    hierarchyPanel->setSource(QUrl::fromLocalFile(QApplication::applicationDirPath() + "/qml/hierarchy_panel.qml"));
	
	materialPanel = new QQuickWidget;
	materialPanel->setResizeMode(QQuickWidget::SizeViewToRootObject);
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
	materialDock->setMinimumHeight(100);

    this->setCentralWidget(viewDock);
    this->addDockWidget(Qt::RightDockWidgetArea,commandDock);
    this->addDockWidget(Qt::LeftDockWidgetArea,hierarchyDock);
	this->addDockWidget(Qt::BottomDockWidgetArea, materialDock);
}

MainWindow::~MainWindow()
{
}
