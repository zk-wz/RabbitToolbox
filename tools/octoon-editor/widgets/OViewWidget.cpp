#include <octoon\editor\widgets\OViewWidget.h>
#include "..\..\..\include\octoon\editor\widgets\OViewWidget.h"

OViewWidget::OViewWidget(QWidget *parent) : QWidget(parent)
{
	is_init = false;
	setAttribute(Qt::WA_PaintOnScreen, true);
	setAttribute(Qt::WA_NativeWindow, true);
	setMouseTracking(true);
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

		if (!gameApp_->open(hwnd, w, h, w, h))
			throw std::exception("GameApplication::open() failed");

		gameApp_->set_active(true);

		if (!gameScenePath_.empty())
		{
			if (!gameApp_->open_scene(gameScenePath_))
				throw std::exception("GameApplication::open_scene() failed");
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
	if (!is_init)
	{
		is_init = true;
		OctoonInit(QCoreApplication::applicationFilePath().toStdString().c_str(), "");
		OctoonOpenWindow("Octoon Studio", width(), height());
	}

	if (gameApp_)
		gameApp_->update();
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
	}
}

void OViewWidget::mousePressEvent(QMouseEvent * e)
{
	if (gameApp_)
	{
		octoon::input::InputEvent event;
		event.event = octoon::input::InputEvent::MouseButtonDown;
		if (e->buttons() == Qt::LeftButton)
		{
			event.button.button = octoon::input::InputButton::MOUSE0;
		}
		else if (e->buttons() == Qt::RightButton)
		{
			event.button.button = octoon::input::InputButton::MOUSE1;
		}
		event.button.clicks = true;
		event.button.x = e->x();
		event.button.y = e->y();
		event.button.timestamp = QDateTime::currentDateTime().toMSecsSinceEpoch();
		event.button.windowID = (std::uint64_t)winId();
		event.button.padding1 = 0;
		event.button.which = 0;

		gameApp_->send_input_event(event);
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
		event.motion.xrel = e->windowPos().x();
		event.motion.yrel = e->windowPos().y();
		event.motion.timestamp = QDateTime::currentDateTime().toMSecsSinceEpoch();
		event.motion.state = false;
		event.motion.windowID = (std::uint64_t)winId();

		gameApp_->send_input_event(event);
	}
}

void OViewWidget::mouseReleaseEvent(QMouseEvent * e)
{
	if (gameApp_)
	{
		octoon::input::InputEvent event;
		event.event = octoon::input::InputEvent::MouseButtonUp;
		if (e->buttons() == Qt::LeftButton)
		{
			event.button.button = octoon::input::InputButton::MOUSE0;
		}
		else if (e->buttons() == Qt::RightButton)
		{
			event.button.button = octoon::input::InputButton::MOUSE1;
		}
		event.button.clicks = true;
		event.button.x = e->x();
		event.button.y = e->y();
		event.button.timestamp = QDateTime::currentDateTime().toMSecsSinceEpoch();
		event.button.windowID = (std::uint64_t)winId();
		event.button.padding1 = 0;
		event.button.which = 0;

		gameApp_->send_input_event(event);
	}
}

void OViewWidget::mouseDoubleClickEvent(QMouseEvent * e)
{
	if (gameApp_)
	{
		octoon::input::InputEvent doubleClick;
		doubleClick.event = octoon::input::InputEvent::MouseButtonDoubleClick;
		if (e->buttons() == Qt::LeftButton)
		{
			doubleClick.button.button = octoon::input::InputButton::MOUSE0;
		}
		else if (e->buttons() == Qt::RightButton)
		{
			doubleClick.button.button = octoon::input::InputButton::MOUSE1;
		}
		doubleClick.button.clicks = true;
		doubleClick.button.x = e->x();
		doubleClick.button.y = e->y();
		doubleClick.button.timestamp = QDateTime::currentDateTime().toMSecsSinceEpoch();
		doubleClick.button.windowID = (std::uint64_t)winId();
		doubleClick.button.padding1 = 0;
		doubleClick.button.which = 0;

		gameApp_->send_input_event(doubleClick);
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
	}
}

OViewWidget::~OViewWidget()
{
	if (gameApp_)
	{
		gameApp_.reset();
		gameApp_ = nullptr;
	}
}
