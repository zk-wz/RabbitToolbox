#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <memory>

#include <QCoreApplication>
#include <QApplication>
#include <QMainWindow>
#include <QDockWidget>
#include <QPaintEvent>
#include <QResizeEvent>

#include <QMenuBar>
#include <QMenu>
#include <QtQuickWidgets/QQuickWidget>

#include <octoon/octoon.h>

#include <octoon/game_application.h>
#include <octoon/input/input_event.h>

#include <octoon/editor/widgets/OMainWindow.h>
#include <octoon/editor/widgets/OViewWidget.h>
#include <octoon/editor/widgets/ODockWidget.h>


class MainWindow : public OMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    ODockWidget *viewDock;
    ODockWidget *commandDock;
    ODockWidget *hierarchyDock;
	ODockWidget *materialDock;
    QQuickWidget *commandPanel;
    QQuickWidget *hierarchyPanel;
	QQuickWidget *materialPanel;
    OViewWidget *viewPanel;
};

#endif // MAINWINDOW_H
