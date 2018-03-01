#ifndef OCTOON_OMAINWINDOW_H
#define OCTOON_OMAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QLayout>
#include <QMenu>
#include <QMenuBar>
#include <QQuickWidget>
#include <QDesktopWidget>

#include <octoon\editor\widgets\OTitleBar.h>

enum ResizeRegion
{
	Default,
	North,
	NorthEast,
	East,
	SouthEast,
	South,
	SouthWest,
	West,
	NorthWest
};



class OMainWindow:public QMainWindow
{
    Q_OBJECT
public:
    explicit OMainWindow(QWidget *parent = Q_NULLPTR)
        :QMainWindow(parent)
    {
		// menu
		menuBar = new QMenuBar(this);
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
		vLayout->addWidget(menuBar);
        vLayout->addWidget(&winFrame);

        windowCentralWidget->setLayout(vLayout);
		QMainWindow::setCentralWidget(windowCentralWidget);
    }

    ~OMainWindow()
    {
    }


	void mousePressEvent(QMouseEvent *event)
	{
		if (event->button() == Qt::LeftButton)
		{
			this->m_drag = true;
			this->dragPos = event->pos();
			this->resizeDownPos = event->globalPos();
			this->mouseDownRect = this->rect();
		}
	}
	void mouseMoveEvent(QMouseEvent * event)
	{
		if (resizeRegion != Default)
		{
			handleResize();
			return;
		}
		if (m_move)
		{
			move(event->globalPos() - dragPos);
			return;
		}
		QPoint clientCursorPos = event->pos();
		QRect r = this->rect();
		QRect resizeInnerRect(resizeBorderWidth, resizeBorderWidth, r.width() - 2 * resizeBorderWidth, r.height() - 2 * resizeBorderWidth);
		if (r.contains(clientCursorPos) && !resizeInnerRect.contains(clientCursorPos)) 
		{
			ResizeRegion resizeReg = getResizeRegion(clientCursorPos);
			setResizeCursor(resizeReg);
			if (m_drag && (event->buttons() & Qt::LeftButton))
			{
				resizeRegion = resizeReg;
				handleResize();
			}
		}
		else 
		{
			setCursor(Qt::ArrowCursor);
			if (m_drag && (event->buttons() & Qt::LeftButton)) {
				m_move = true;
				move(event->globalPos() - dragPos);
			}
		}
	}
	void mouseReleaseEvent(QMouseEvent *event)
	{
		m_drag = false;
		if (m_move) 
		{
			m_move = false;
			handleMove(event->globalPos());
		}
		resizeRegion = Default;
		setCursor(Qt::ArrowCursor);
	}
	void setResizeCursor(ResizeRegion region)
	{
		switch (region)
		{
		case North:
		case South:
			setCursor(Qt::SizeVerCursor);
			break;
		case East:
		case West:
			setCursor(Qt::SizeHorCursor);
			break;
		case NorthWest:
		case SouthEast:
			setCursor(Qt::SizeFDiagCursor);
			break;
		default:
			setCursor(Qt::SizeBDiagCursor);
			break;
		}
	}
	ResizeRegion getResizeRegion(QPoint clientPos)
	{
		if (clientPos.y() <= resizeBorderWidth) {
			if (clientPos.x() <= resizeBorderWidth)
				return NorthWest;
			else if (clientPos.x() >= this->width() - resizeBorderWidth)
				return NorthEast;
			else
				return North;
		}
		else if (clientPos.y() >= this->height() - resizeBorderWidth) {
			if (clientPos.x() <= resizeBorderWidth)
				return SouthWest;
			else if (clientPos.x() >= this->width() - resizeBorderWidth)
				return SouthEast;
			else
				return South;
		}
		else {
			if (clientPos.x() <= resizeBorderWidth)
				return West;
			else
				return East;
		}
	}
	void handleMove(QPoint pt)
	{
		//QDesktopWidget* desktop = QApplication::desktop();
		QPoint currentPos = pt - dragPos;
		/*
		if (currentPos.x()<desktop->screenGeometry().x())
		{
		currentPos.setX(desktop->screenGeometry().x());
		}
		else if (currentPos.x()>desktop->screenGeometry().width())
		{
		currentPos.setX(desktop->screenGeometry().width() - this->width());
		}
		if (currentPos.y()<desktop->screenGeometry().y())
		{
		currentPos.setY(desktop->screenGeometry().y());
		}
		*/
		
		move(currentPos);
	}
	void handleResize()
	{
		int xdiff = QCursor::pos().x() - resizeDownPos.x();
		int ydiff = QCursor::pos().y() - resizeDownPos.y();
		switch (resizeRegion)
		{
		case East:
		{
			resize(mouseDownRect.width() + xdiff, this->height());
			break;
		}
		case West:
		{
			resize(mouseDownRect.width() - xdiff, this->height());
			move(resizeDownPos.x() + xdiff, this->y());
			break;
		}
		case South:
		{
			resize(this->width(), mouseDownRect.height() + ydiff);
			break;
		}
		case North:
		{
			resize(this->width(), mouseDownRect.height() - ydiff);
			move(this->x(), resizeDownPos.y() + ydiff);
			break;
		}
		case SouthEast:
		{
			resize(mouseDownRect.width() + xdiff, mouseDownRect.height() + ydiff);
			break;
		}
		case NorthEast:
		{
			resize(mouseDownRect.width() + xdiff, mouseDownRect.height() - ydiff);
			move(this->x(), resizeDownPos.y() + ydiff);
			break;
		}
		case NorthWest:
		{
			resize(mouseDownRect.width() - xdiff, mouseDownRect.height() - ydiff);
			move(resizeDownPos.x() + xdiff, resizeDownPos.y() + ydiff);
			break;
		}
		case SouthWest:
		{
			resize(mouseDownRect.width() - xdiff, mouseDownRect.height() + ydiff);
			move(resizeDownPos.x() + xdiff, this->y());
			break;
		}
		}
	}


	void setCentralWidget(QWidget *widget)
	{
		winFrame.setCentralWidget(widget);
	}

	void addDockWidget(Qt::DockWidgetArea area, QDockWidget *dockwidget)
	{
		winFrame.addDockWidget(area, dockwidget);
	}

	void setTabPosition(Qt::DockWidgetAreas areas, QTabWidget::TabPosition tabPosition)
	{
		winFrame.setTabPosition(areas, tabPosition);
	}

	void setDockOptions(DockOptions options)
	{
		winFrame.setDockOptions(options);
	}

	void setMenuBar(QMenuBar *menubar)
	{
		vLayout->replaceWidget(menuBar, menubar);
		menuBar = menubar;
	}
protected:
    QMainWindow winFrame;
    QWidget * windowCentralWidget;
    QVBoxLayout *vLayout;
    OTitleBar *titleBar;
	QMenuBar *menuBar;

	bool m_drag, m_move;
	QPoint dragPos, resizeDownPos;
	const int resizeBorderWidth = 5;
	ResizeRegion resizeRegion;
	QRect mouseDownRect;
};
 

#endif // OCTOON_OMAINWINDOW_H