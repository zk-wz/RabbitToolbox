#ifndef OCTOON_OTITLEBAR_H
#define OCTOON_OTITLEBAR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QApplication>

#ifdef Q_OS_WIN
#	include <qt_windows.h>
#endif


class OTitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit OTitleBar(QWidget *parent = Q_NULLPTR)
        :QWidget(parent)
    {
        setFixedHeight(30);

        iconLabel = new QLabel(this);
        titleLabel = new QLabel(this);
        minimizeButton = new QPushButton(this);
        maximizeButton = new QPushButton(this);
        closeButton = new QPushButton(this);

        iconLabel->setFixedSize(20, 20);
        iconLabel->setScaledContents(true);

        titleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

        minimizeButton->setFixedSize(27, 22);
        maximizeButton->setFixedSize(27, 22);
        closeButton->setFixedSize(27, 22);

        titleLabel->setObjectName("whiteLabel");
        minimizeButton->setObjectName("minimizeButton");
        maximizeButton->setObjectName("maximizeButton");
        closeButton->setObjectName("closeButton");

        minimizeButton->setToolTip("Minimize");
        maximizeButton->setToolTip("Maximize");
        closeButton->setToolTip("Close");

        QHBoxLayout *pLayout = new QHBoxLayout(this);
        pLayout->setMargin(0);
        pLayout->setObjectName("titlebarLayout");
        pLayout->addWidget(iconLabel);
        pLayout->addSpacing(5);
        pLayout->addWidget(titleLabel);
        pLayout->addWidget(minimizeButton);
        pLayout->addWidget(maximizeButton);
        pLayout->addWidget(closeButton);
        pLayout->setSpacing(0);
        pLayout->setContentsMargins(5, 0, 5, 0);

        setLayout(pLayout);

        connect(minimizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
        connect(maximizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
        connect(closeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    }
    ~OTitleBar() = default;

protected:

    // double click titlebar and maximize it
    virtual void mouseDoubleClickEvent(QMouseEvent *event) Q_DECL_OVERRIDE
    {
        Q_UNUSED(event);
        emit maximizeButton->clicked();
    }

    // drag and move the window
    virtual void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE
    {
#ifdef Q_OS_WIN
		if (ReleaseCapture())
		{
			QWidget *pWindow = this->window();
			if (pWindow->isTopLevel())
			{
				SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
			}
		}
		event->ignore();
#else
#endif
    }

    // set title and icon
    virtual bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE
    {
        switch ((int)event->type())
        {
        case (int)QEvent::WindowTitleChange:
        {
            QWidget *pWidget = qobject_cast<QWidget *>(obj);
            if (pWidget)
            {
                titleLabel->setText(pWidget->windowTitle());
                return true;
            }
        }
        case (int)QEvent::WindowIconChange:
        {
            QWidget *pWidget = qobject_cast<QWidget *>(obj);
            if (pWidget)
            {
                QIcon icon = pWidget->windowIcon();
                iconLabel->setPixmap(icon.pixmap(iconLabel->size()));
                return true;
            }
        }
        case (int)QEvent::WindowStateChange:
        case (int)QEvent::Resize:
            updateMaximize();
            return true;
        }
        return QWidget::eventFilter(obj, event);
    }

private slots:

    // minimize, maximize and close operation
    void onClicked()
    {
        QPushButton *pButton = qobject_cast<QPushButton *>(sender());
        QWidget *pWindow = this->window();
        if (pWindow->isTopLevel())
        {
            if (pButton == minimizeButton)
            {
                pWindow->showMinimized();
            }
            else if (pButton == maximizeButton)
            {
                pWindow->isMaximized() ? pWindow->showNormal() : pWindow->showMaximized();
            }
            else if (pButton == closeButton)
            {
                pWindow->close();
            }
        }
    }

private:

    // maximize
    void updateMaximize()
    {
        QWidget *pWindow = this->window();
        if (pWindow->isTopLevel())
        {
            bool bMaximize = pWindow->isMaximized();
            if (bMaximize)
            {
                maximizeButton->setToolTip(tr("Restore"));
                maximizeButton->setProperty("maximizeProperty", "restore");
            }
            else
            {
                maximizeButton->setProperty("maximizeProperty", "maximize");
                maximizeButton->setToolTip(tr("Maximize"));
            }

            // maximizeButton->setStyle(QApplication::style());
        }
    }

private:
    QLabel *iconLabel;
    QLabel *titleLabel;
    QPushButton *minimizeButton;
    QPushButton *maximizeButton;
    QPushButton *closeButton;
};



#endif // OCTOON_OTITLEBAR_H