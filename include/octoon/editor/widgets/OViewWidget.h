#ifndef OVIEWWIDGET_H
#define OVIEWWIDGET_H

#include <memory>

#include <QCoreApplication>
#include <QWidget>
#include <QDockWidget>
#include <QPaintEngine>
#include <QPaintEvent>
#include <QResizeEvent>
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

	virtual QPaintEngine *paintEngine() const { return NULL; }
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