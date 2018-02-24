#ifndef OCTOON_ODOCKDOCKTITLEBAR_H
#define OCTOON_ODOCKDOCKTITLEBAR_H

#include <QSize>
#include <QDockWidget>
#include <QMouseEvent>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QStyle>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>

class ODockTitleBar : public QWidget
{
    Q_OBJECT
public:
    ODockTitleBar(const QString &title, QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags())
        :QWidget(parent)
    {
        //pixMap
		/*
		minPix = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
        closePix  = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
        floatPix = style()->standardPixmap(QStyle::SP_TitleBarNormalButton);
		*/
		minPix.load("./resource/images/button/minimizeButton_white.png");
		closePix.load("./resource/images/button/closeButton_white.png");
		floatPix.load("./resource/images/button/maximizeButton_white.png");
        name = title;

        // buttons
        QHBoxLayout *pLayout = new QHBoxLayout(this);
        nameLabel = new QLabel(name, this);
        //minButton = new QPushButton(this);
        closeButton = new QPushButton(this);
        floatButton = new QPushButton(this);

		pLayout->setMargin(0);

		//minButton->setFixedHeight(16);
		//minButton->setFixedWidth(16);
		closeButton->setFixedHeight(16);
		closeButton->setFixedWidth(16);
		floatButton->setFixedHeight(16);
		floatButton->setFixedWidth(16);

        //minButton->setIcon(QIcon(minPix));
        closeButton->setIcon(QIcon(closePix));
        floatButton->setIcon(QIcon(floatPix));

        pLayout->addWidget(nameLabel);
        pLayout->addStretch();
        // pLayout->addWidget(minButton);
        pLayout->addWidget(floatButton);
        pLayout->addWidget(closeButton);

        this->setLayout(pLayout);

		//connect(minButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
		connect(floatButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
		connect(closeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    }

	void setWindowTitle(const QString &title)
	{
		name = title;
		nameLabel->setText(name);
	}

    QSize sizeHint() const { return minimumSizeHint(); }
    QSize minimumSizeHint() const {return QSize(156, 24);}

    int width;
    QString name;//receive parents name

private slots:
	// minimize, maximize and close operation
	void onClicked()
	{
		QPushButton *pButton = qobject_cast<QPushButton *>(sender());
		QDockWidget *dw = qobject_cast<QDockWidget*>(parentWidget());
		if (pButton == minButton)
		{
			if (dw->widget()->isVisible()) 
			{
				//click minPix ,dw setMinimumWidth
				dw->setMinimumWidth(width);
				dw->widget()->hide();
			}
			else
			{
				dw->widget()->show();
			}
		}
		else if (pButton == floatButton)
		{
			dw->setFloating(!dw->isFloating());
		}
		else if (pButton == closeButton)
		{
			dw->close();
		}
	}

private:
    QPixmap minPix, closePix, floatPix;
    QPushButton * minButton;
    QPushButton * closeButton;
    QPushButton * floatButton;
    QLabel *nameLabel;
};

#endif // OCTOON_ODOCKDOCKTITLEBAR_H
