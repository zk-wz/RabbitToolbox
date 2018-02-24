#include <octoon\editor\widgets\OViewWidget.h>
#include "..\..\..\include\octoon\editor\widgets\OViewWidget.h"

OViewWidget::OViewWidget(QWidget *parent) : QWidget()
{
	init_flag = false;
	setAttribute(Qt::WA_PaintOnScreen, true);
	//setAttribute(Qt::WA_NativeWindow, true);
	//setAttribute(Qt::WA_OpaquePaintEvent, false);
	setMouseTracking(true);
	this->setUpdatesEnabled(false);

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(appUpdate()));
	timer->start(20);
}

bool OViewWidget::OctoonInit(const char* gamedir, const char* scenename) noexcept
{
	if (gamedir)
	{
		char drive[3];
		char dir[MAX_PATH];
		char filename[MAX_PATH];
		char ext[MAX_PATH];

		::_splitpath(gamedir, drive, dir, filename, ext);

		gameRootPath_ = drive;
		gameRootPath_ += dir;
		::SetCurrentDirectory(gameRootPath_.c_str());
	}

	if (scenename)
		gameScenePath_ = scenename;
	return true;
}

bool OViewWidget::OctoonOpenWindow(const char* title, int w, int h) noexcept
{
	assert(!gameApp_);
	try
	{
		octoon::WindHandle hwnd = (octoon::WindHandle)winId();

		gameApp_ = std::make_shared<octoon::GameApplication>();
		gameApp_->open(hwnd, w, h, w, h);
		gameApp_->set_active(true);

		if (!gameScenePath_.empty())
		{
			if (!gameApp_->open_scene(gameScenePath_))
				throw std::runtime_error("GameApplication::open_scene() failed");
		}

		return true;
	}
	catch (...)
	{
		OctoonCloseWindow();

		gameApp_.reset();
		gameApp_ = nullptr;

		return false;
	}
}

void OViewWidget::paintEvent(QPaintEvent *e)
{
	if (!init_flag)
	{
		init_flag = true;
		OctoonInit(QCoreApplication::applicationFilePath().toStdString().c_str(), "");
		OctoonOpenWindow("Octoon Studio", width(), height());
	}
	appUpdate();
}

void OViewWidget::resizeEvent(QResizeEvent *e)
{
	if (gameApp_)
	{
		{
			octoon::input::InputEvent event;
			event.event = octoon::input::InputEvent::SizeChangeDPI;
			event.change.w = width();
			event.change.h = height();
			event.change.windowID = (std::uint64_t)winId();
			event.change.timestamp = QDateTime::currentDateTime().toMSecsSinceEpoch();
			gameApp_->send_input_event(event);
		}
		{
			octoon::input::InputEvent event;
			event.event = octoon::input::InputEvent::SizeChange;
			event.change.w = width();
			event.change.h = height();
			event.change.windowID = (std::uint64_t)winId();
			event.change.timestamp = QDateTime::currentDateTime().toMSecsSinceEpoch();
			gameApp_->send_input_event(event);
		}
		appUpdate();
	}
}

void OViewWidget::mouseMoveEvent(QMouseEvent * e)
{
	if (gameApp_)
	{
		octoon::input::InputEvent event;
		event.event = octoon::input::InputEvent::MouseMotion;
		event.motion.x = e->pos().x();
		event.motion.y = e->pos().y();
		event.motion.xrel = e->screenPos().x();
		event.motion.yrel = e->screenPos().y();
		event.motion.timestamp = QDateTime::currentDateTime().toMSecsSinceEpoch();
		event.motion.state = false;
		event.motion.windowID = (std::uint64_t)winId();

		gameApp_->send_input_event(event);
		appUpdate();
	}
}

void OViewWidget::mousePressEvent(QMouseEvent * e)
{
	if (gameApp_)
	{
		octoon::input::InputEvent event;
		event.event = octoon::input::InputEvent::MouseButtonDown;
		event.button.clicks = true;
		event.button.x = e->x();
		event.button.y = e->y();
		event.button.timestamp = QDateTime::currentDateTime().toMSecsSinceEpoch();
		event.button.windowID = (std::uint64_t)winId();
		event.button.padding1 = 0;
		event.button.which = 0;

		if (e->button() == Qt::LeftButton)
			event.button.button = octoon::input::InputButton::Left;
		else if (e->button() == Qt::RightButton)
			event.button.button = octoon::input::InputButton::Right;
		else if (e->button() == Qt::MiddleButton)
			event.button.button = octoon::input::InputButton::Middle;

		gameApp_->send_input_event(event);
		appUpdate();
	}
}

void OViewWidget::mouseReleaseEvent(QMouseEvent * e)
{
	if (gameApp_)
	{
		octoon::input::InputEvent event;
		event.event = octoon::input::InputEvent::MouseButtonUp;
		event.button.clicks = false;
		event.button.x = e->x();
		event.button.y = e->y();
		event.button.timestamp = QDateTime::currentDateTime().toMSecsSinceEpoch();
		event.button.windowID = (std::uint64_t)winId();
		event.button.padding1 = 0;
		event.button.which = 0;

		if (e->button() == Qt::LeftButton)
			event.button.button = octoon::input::InputButton::Left;
		else if (e->button() == Qt::RightButton)
			event.button.button = octoon::input::InputButton::Right;
		else if (e->button() == Qt::MiddleButton)
			event.button.button = octoon::input::InputButton::Middle;

		gameApp_->send_input_event(event);
		appUpdate();
	}
}

void OViewWidget::mouseDoubleClickEvent(QMouseEvent * e)
{
	if (gameApp_)
	{
		octoon::input::InputEvent doubleClick;
		doubleClick.event = octoon::input::InputEvent::MouseButtonDoubleClick;
		doubleClick.button.clicks = true;
		doubleClick.button.x = e->x();
		doubleClick.button.y = e->y();
		doubleClick.button.timestamp = QDateTime::currentDateTime().toMSecsSinceEpoch();
		doubleClick.button.windowID = (std::uint64_t)winId();
		doubleClick.button.padding1 = 0;
		doubleClick.button.which = 0;

		if (e->button() == Qt::LeftButton)
			doubleClick.button.button = octoon::input::InputButton::Left;
		else if (e->button() == Qt::RightButton)
			doubleClick.button.button = octoon::input::InputButton::Right;
		else if (e->button() == Qt::MiddleButton)
			doubleClick.button.button = octoon::input::InputButton::Middle;

		gameApp_->send_input_event(doubleClick);
		appUpdate();
	}
}

void OViewWidget::wheelEvent(QWheelEvent * e)
{
	if (gameApp_)
	{
		octoon::input::InputEvent event;
		event.event = e->delta() > 0 ? octoon::input::InputEvent::MouseWheelUp : octoon::input::InputEvent::MouseWheelDown;
		event.wheel.timestamp = QDateTime::currentDateTime().toMSecsSinceEpoch();
		event.wheel.windowID = (std::uint64_t)winId();

		gameApp_->send_input_event(event);
		appUpdate();
	}
}

void OViewWidget::appUpdate()
{
	if (!init_flag)
	{
		init_flag = true;
		OctoonInit(QCoreApplication::applicationFilePath().toStdString().c_str(), "");
		OctoonOpenWindow("Octoon Studio", width(), height());
	}

	if (gameApp_)
		gameApp_->update();
}

//void OViewWidget::scenceUpdate()
//{
//	this->viewport()->update();
//}

void OViewWidget::play()
{
	if(!timer->isActive())
		timer->start(30);
}

void OViewWidget::pause()
{
	if (timer->isActive())
		timer->stop();
}

OViewWidget::~OViewWidget()
{
	if (gameApp_)
	{
		gameApp_.reset();
		gameApp_ = nullptr;
	}
}