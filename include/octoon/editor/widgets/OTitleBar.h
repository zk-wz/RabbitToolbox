#ifndef OCTOON_OTITLEBAR_H
#define OCTOON_OTITLEBAR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QApplication>
#include <QDesktopWidget>

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


class OTitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit OTitleBar(QWidget *parent = Q_NULLPTR)
        :QWidget(parent)
    {
        setFixedHeight(24);

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
        if (event->button() == Qt::LeftButton) 
        {
            this->m_drag = true;
            this->dragPos = event->pos();
            this->resizeDownPos = event->globalPos();
            this->mouseDownRect = this->rect();
        }
    }

    virtual void mouseMoveEvent(QMouseEvent * event)
    {
        if (resizeRegion != Default)
        {
            handleResize();
            return;
        }
        if(m_move) {
			this->window()->move(event->globalPos() - dragPos);
            return;
        }
        QPoint clientCursorPos = event->pos();
        QRect r = this->rect();
        QRect resizeInnerRect(resizeBorderWidth, resizeBorderWidth, r.width() - 2*resizeBorderWidth, r.height() - 2*resizeBorderWidth);
        if(r.contains(clientCursorPos) && !resizeInnerRect.contains(clientCursorPos)) {
            ResizeRegion resizeReg = getResizeRegion(clientCursorPos);
            setResizeCursor(resizeReg);
            if (m_drag && (event->buttons() & Qt::LeftButton)) {
                resizeRegion = resizeReg;
                handleResize();
            }
        }
        else {
            setCursor(Qt::ArrowCursor);
            if (m_drag && (event->buttons() & Qt::LeftButton)) {
                m_move = true;
				this->window()->move(event->globalPos() - dragPos);
            }
        }
    }

    void mouseReleaseEvent(QMouseEvent *event)
    {
        m_drag = false;
        if(m_move) {
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
		QDesktopWidget* desktop = QApplication::desktop();
        QPoint currentPos = pt - dragPos;
        if(currentPos.x()<desktop->screenGeometry().x())
		{
            currentPos.setX(desktop->screenGeometry().x());
        }
        else if (currentPos.x()+this->width()>desktop->screenGeometry().x())
		{
            currentPos.setX(desktop->screenGeometry().x() - this->width());
        }
        if(currentPos.y()<desktop->screenGeometry().y())
		{
            currentPos.setY(desktop->screenGeometry().y());
        }
		this->window()->move(currentPos);
    }
    void handleResize()
    {
        int xdiff = QCursor::pos().x() - resizeDownPos.x();
        int ydiff = QCursor::pos().y() - resizeDownPos.y();
        switch (resizeRegion)
        {
			case East:
			{
				this->window()->resize(mouseDownRect.width()+xdiff, this->height());
				break;
			}
			case West:
			{
				this->window()->resize(mouseDownRect.width()-xdiff, this->height());
				this->window()->move(resizeDownPos.x()+xdiff, this->y());
				break;
			}
			case South:
			{
				this->window()->resize(this->width(),mouseDownRect.height()+ydiff);
				break;
			}
			case North:
			{
				this->window()->resize(this->width(),mouseDownRect.height()-ydiff);
				this->window()->move(this->x(), resizeDownPos.y()+ydiff);
				break;
			}
			case SouthEast:
			{
				this->window()->resize(mouseDownRect.width() + xdiff, mouseDownRect.height() + ydiff);
				break;
			}
			case NorthEast:
			{
				this->window()->resize(mouseDownRect.width()+xdiff, mouseDownRect.height()-ydiff);
				this->window()->move(this->x(), resizeDownPos.y()+ydiff);
				break;
			}
			case NorthWest:
			{
				this->window()->resize(mouseDownRect.width()-xdiff, mouseDownRect.height()-ydiff);
				this->window()->move(resizeDownPos.x()+xdiff, resizeDownPos.y()+ydiff);
				break;
			}
			case SouthWest:
			{
				this->window()->resize(mouseDownRect.width()-xdiff, mouseDownRect.height()+ydiff);
				this->window()->move(resizeDownPos.x()+xdiff, this->y());
				break;
			}
        }
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

    bool m_drag, m_move;
    QPoint dragPos, resizeDownPos;
    const int resizeBorderWidth = 5;
    ResizeRegion resizeRegion;
    QRect mouseDownRect;
};



#endif // OCTOON_OTITLEBAR_H