#include <octoon\editor\widgets\OViewWidget.h>

OViewWidget::OViewWidget(QWidget *parent) : QWidget(parent)
{
	is_init = false;
	setAttribute(Qt::WA_PaintOnScreen, true);
	setAttribute(Qt::WA_NativeWindow, true);
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
}

OViewWidget::~OViewWidget()
{
	if (gameApp_)
	{
		gameApp_.reset();
		gameApp_ = nullptr;
	}
}
