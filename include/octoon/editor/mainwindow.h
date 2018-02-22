#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QtQuickWidgets/QQuickWidget>

#include "widgets/OViewWidget.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    QDockWidget *viewDock;
    QDockWidget *commandDock;
    QQuickWidget *commandPanel;
    OViewWidget *viewPanel;
};

#endif // MAINWINDOW_H
