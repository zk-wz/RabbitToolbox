#ifndef OVIEWWIDGET_H
#define OVIEWWIDGET_H

#include <memory>

#include <QCoreApplication>
#include <QWidget>
#include <QDockWidget>
#include <QPaintEngine>
#include <QPaintEvent>
#include <QResizeEvent>
#include<QMouseEvent>
#include<QWheelEvent>
#include <QDateTime>
#include <QtQuickWidgets/QQuickWidget>

#include <octoon/octoon.h>

#include <octoon/game_application.h>
#include <octoon/input/input_event.h>

class OViewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OViewWidget(QWidget *parent = nullptr);
	~OViewWidget();

	bool OctoonInit(const char* gamedir, const char* scenename) noexcept;
	bool OctoonOpenWindow(const char* title, int w, int h) noexcept;

	void paintEvent(QPaintEvent * e);
	void resizeEvent(QResizeEvent * e);
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	void mouseDoubleClickEvent(QMouseEvent* event);
	void wheelEvent(QWheelEvent* event);  

	virtual QPaintEngine *paintEngine() const { return NULL; }

	void play();
private:
	octoon::GameApplicationPtr gameApp_;
	octoon::input::InputMousePtr inputMessage_;

	std::string gameRootPath_;
	std::string gameScenePath_;

	bool is_init;

signals:

public slots:
};

#endif // OVIEWWIDGET_H