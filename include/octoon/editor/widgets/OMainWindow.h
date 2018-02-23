#ifndef OCTOON_OMAINWINDOW_H
#define OCTOON_OMAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QMenu>
#include <QMenuBar>

#include <octoon\editor\widgets\OTitleBar.h>


class OMainWindow:public QMainWindow
{
    Q_OBJECT
public:
    explicit OMainWindow(QWidget *parent = Q_NULLPTR)
        :QMainWindow(parent)
    {
        // layout
        windowCentralWidget = new QWidget(this);
        vLayout = new QVBoxLayout(windowCentralWidget);
        // titlebar
        setWindowFlags(Qt::FramelessWindowHint | windowFlags());
        titleBar = new OTitleBar(windowCentralWidget);
        installEventFilter(titleBar);

        setWindowTitle("MainWindow");
        setWindowIcon(QIcon(":/rsc/images/logo/logo.png"));

        vLayout->setMargin(0);
        vLayout->addWidget(titleBar);
        vLayout->addWidget(&winFrame);

        windowCentralWidget->setLayout(vLayout);
		QMainWindow::setCentralWidget(windowCentralWidget);
    }

    ~OMainWindow()
    {
    }

	void setCentralWidget(QWidget *widget)
	{
		winFrame.setCentralWidget(widget);
	}

	void addDockWidget(Qt::DockWidgetArea area, QDockWidget *dockwidget)
	{
		winFrame.addDockWidget(area, dockwidget);
	}
protected:
    QMainWindow winFrame;
    QWidget * windowCentralWidget;
    QVBoxLayout *vLayout;
    OTitleBar *titleBar;
    QMenuBar *menuBar;
};
 

#endif // OCTOON_OMAINWINDOW_H