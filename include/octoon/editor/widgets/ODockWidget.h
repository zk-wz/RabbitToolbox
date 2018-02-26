#ifndef OCTOON_ODOCKWIDGET_H
#define OCTOON_ODOCKWIDGET_H

#include <QMainWindow>
#include <QDockWidget>
#include <QLayout>
#include <QMenu>
#include <QMenuBar>

#include <octoon\editor\widgets\OTitleBar.h>
#include <octoon\editor\widgets\ODockTitleBar.h>


class ODockWidget:public QDockWidget
{
    Q_OBJECT
public:
    explicit ODockWidget(const QString &title, QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags())
        :QDockWidget(title, parent, flags)
    {
		titleBar = new ODockTitleBar(title, this, flags);
        this->setTitleBarWidget(titleBar);
    }

	explicit ODockWidget(QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags())
		:QDockWidget(parent, flags)
	{
		titleBar = new ODockTitleBar("", this, flags);
		this->setTitleBarWidget(titleBar);
	}

    ~ODockWidget()
    {
    }
	void setWindowTitle(const QString &title)
	{
		titleBar->setWindowTitle(title);
		QDockWidget::setWindowTitle(title);
	}
private:
	ODockTitleBar * titleBar;
};
 

#endif // OCTOON_ODOCKWIDGET_H