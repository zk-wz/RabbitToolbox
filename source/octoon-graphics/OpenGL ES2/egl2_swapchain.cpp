#include "egl2_swapchain.h"

namespace octoon 
{
	namespace graphics
	{
		OctoonImplementSubClass(EGL2Swapchain, GraphicsSwapchain, "EGL2Swapchain")

		EGL2Swapchain* EGL2Swapchain::_swapchain = nullptr;

		EGL2Swapchain::EGL2Swapchain() noexcept
			: _display(EGL_NO_DISPLAY)
			, _surface(EGL_NO_SURFACE)
			, _context(EGL_NO_CONTEXT)
			, _config(0)
			, _isActive(false)
		{
		}

		EGL2Swapchain::~EGL2Swapchain() noexcept
		{
			this->close();
		}

		bool
		EGL2Swapchain::setup(const GraphicsSwapchainDesc& swapchainDesc) noexcept
		{
			if (!initPixelFormat(swapchainDesc))
				return false;

			if (!initSurface(swapchainDesc))
				return false;

			if (!initSwapchain(swapchainDesc))
				return false;

			_swapchainDesc = swapchainDesc;
			return true;
		}

		void
		EGL2Swapchain::close() noexcept
		{
			if (_surface != EGL_NO_SURFACE)
			{
				::eglDestroySurface(_display, _surface);
				_surface = EGL_NO_SURFACE;
			}

			if (_context != EGL_NO_CONTEXT)
			{
				::eglDestroyContext(_display, _context);
				_context = EGL_NO_CONTEXT;
			}

			if (_display != EGL_NO_DISPLAY)
			{
				::eglTerminate(_display);
				_display = EGL_NO_DISPLAY;
			}
		}

		void
		EGL2Swapchain::setActive(bool active) noexcept
		{
			if (_isActive != active)
			{
				if (active)
				{
					if (eglMakeCurrent(_display, _surface, _surface, _context) == EGL_FALSE)
					{
						GL_PLATFORM_LOG("eglMakeCurrent() fail.");
						return;
					}

					if (_swapchain)
						_swapchain->setActive(false);

					_swapchain = this;
				}
				else
				{
					if (eglMakeCurrent(_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT) == EGL_FALSE)
					{
						GL_PLATFORM_LOG("eglMakeCurrent() fail.");
						return;
					}

					if (_swapchain == this)
						_swapchain = nullptr;
				}

				_isActive = active;
			}
		}

		bool
		EGL2Swapchain::getActive() const noexcept
		{
			return _isActive;
		}

		void
		EGL2Swapchain::setWindowResolution(std::uint32_t w, std::uint32_t h) noexcept
		{
			_swapchainDesc.setWidth(w);
			_swapchainDesc.setHeight(h);
		}

		void
		EGL2Swapchain::getWindowResolution(std::uint32_t& w, std::uint32_t& h) const noexcept
		{
			w = _swapchainDesc.getWidth();
			h = _swapchainDesc.getHeight();
		}

		void
		EGL2Swapchain::setSwapInterval(GraphicsSwapInterval interval) noexcept
		{
			assert(_display != EGL_NO_DISPLAY);

			switch (interval)
			{
			case GraphicsSwapInterval::Free:
				if (eglSwapInterval(_display, 0) == EGL_FALSE)
					GL_PLATFORM_LOG("eglSwapInterval(SwapInterval::Free) fail.");
				break;
			case GraphicsSwapInterval::Vsync:
				if (eglSwapInterval(_display, 1) == EGL_FALSE)
					GL_PLATFORM_LOG("eglSwapInterval(SwapInterval::Vsync) fail.");
				break;
			case GraphicsSwapInterval::Fps30:
				if (eglSwapInterval(_display, 2) == EGL_FALSE)
					GL_PLATFORM_LOG("eglSwapInterval(SwapInterval::Fps30) fail.");
				break;
			case GraphicsSwapInterval::Fps15:
				if (eglSwapInterval(_display, 3) == EGL_FALSE)
					GL_PLATFORM_LOG("eglSwapInterval(SwapInterval::Fps15) fail.");
				break;
			default:
				GL_PLATFORM_LOG("Invlid SwapInterval");
				return;
			}

			_swapchainDesc.setSwapInterval(interval);
		}

		GraphicsSwapInterval
		EGL2Swapchain::getSwapInterval() const noexcept
		{
			return _swapchainDesc.getSwapInterval();
		}

		void
		EGL2Swapchain::present() noexcept
		{
			assert(_isActive);
			assert(_display != EGL_NO_DISPLAY);
			assert(_surface != EGL_NO_SURFACE);

			if (::eglSwapBuffers(_display, _surface) == EGL_FALSE)
				GL_PLATFORM_LOG("eglSwapBuffers() fail.");
		}

		bool
		EGL2Swapchain::initSurface(const GraphicsSwapchainDesc& swapchainDesc)
		{
			EGLNativeWindowType hwnd = (EGLNativeWindowType)swapchainDesc.getWindHandle();
			_surface = ::eglCreateWindowSurface(_display, _config, hwnd, NULL);
			if (eglGetError() != EGL_SUCCESS)
			{
				GL_PLATFORM_LOG("eglCreateContext() fail.");
				return false;
			}

			return true;
		}

		bool
		EGL2Swapchain::initPixelFormat(const GraphicsSwapchainDesc& swapchainDesc) noexcept
		{
			EGLint pixelFormat[80];
			EGLint index = 0;

			pixelFormat[index++] = EGL_SURFACE_TYPE;
			pixelFormat[index++] = EGL_WINDOW_BIT;

			pixelFormat[index++] = EGL_RENDERABLE_TYPE;
			pixelFormat[index++] = EGL_OPENGL_ES2_BIT;

			if (swapchainDesc.getImageNums() != 2)
			{
				GL_PLATFORM_LOG("Invalid image number");
				return false;
			}

			auto colorFormat = swapchainDesc.getColorFormat();
			if (colorFormat == GraphicsFormat::B8G8R8A8UNorm)
			{
				pixelFormat[index++] = EGL_BUFFER_SIZE;
				pixelFormat[index++] = 32;

				pixelFormat[index++] = EGL_RED_SIZE;
				pixelFormat[index++] = 8;

				pixelFormat[index++] = EGL_GREEN_SIZE;
				pixelFormat[index++] = 8;

				pixelFormat[index++] = EGL_BLUE_SIZE;
				pixelFormat[index++] = 8;

				pixelFormat[index++] = EGL_ALPHA_SIZE;
				pixelFormat[index++] = 8;
			}
			else
			{
				GL_PLATFORM_LOG("Can't support color format");
				return false;
			}

			auto depthStencilFormat = swapchainDesc.getDepthStencilFormat();
			if (depthStencilFormat == GraphicsFormat::D16UNorm)
			{
				pixelFormat[index++] = EGL_DEPTH_SIZE;
				pixelFormat[index++] = 16;

				pixelFormat[index++] = EGL_STENCIL_SIZE;
				pixelFormat[index++] = 0;
			}
			else if (depthStencilFormat == GraphicsFormat::X8_D24UNormPack32)
			{
				pixelFormat[index++] = EGL_DEPTH_SIZE;
				pixelFormat[index++] = 24;

				pixelFormat[index++] = EGL_STENCIL_SIZE;
				pixelFormat[index++] = 0;
			}
			else if (depthStencilFormat == GraphicsFormat::D32_SFLOAT)
			{
				pixelFormat[index++] = EGL_DEPTH_SIZE;
				pixelFormat[index++] = 32;

				pixelFormat[index++] = EGL_STENCIL_SIZE;
				pixelFormat[index++] = 0;
			}
			else if (depthStencilFormat == GraphicsFormat::D16UNorm_S8UInt)
			{
				pixelFormat[index++] = EGL_DEPTH_SIZE;
				pixelFormat[index++] = 16;

				pixelFormat[index++] = EGL_STENCIL_SIZE;
				pixelFormat[index++] = 8;
			}
			else if (depthStencilFormat == GraphicsFormat::D24UNorm_S8UInt)
			{
				pixelFormat[index++] = EGL_DEPTH_SIZE;
				pixelFormat[index++] = 24;

				pixelFormat[index++] = EGL_STENCIL_SIZE;
				pixelFormat[index++] = 8;
			}
			else if (depthStencilFormat == GraphicsFormat::D32_SFLOAT_S8UInt)
			{
				pixelFormat[index++] = EGL_DEPTH_SIZE;
				pixelFormat[index++] = 32;

				pixelFormat[index++] = EGL_STENCIL_SIZE;
				pixelFormat[index++] = 8;
			}
			else
			{
				GL_PLATFORM_LOG("Can't support depth stencil format");
				return false;
			}

			pixelFormat[index++] = EGL_NONE;

			_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
			if (_display == EGL_NO_DISPLAY)
			{
				GL_PLATFORM_LOG("eglGetDisplay() fail.");
				return false;
			}

			if (::eglInitialize(_display, nullptr, nullptr) == EGL_FALSE)
			{
				GL_PLATFORM_LOG("eglInitialize() fail.");
				return false;
			}

			if (::eglBindAPI(EGL_OPENGL_ES_API) == EGL_FALSE)
			{
				GL_PLATFORM_LOG("eglBindAPI() fail.");
				return false;
			}

			EGLint num = 0;
			if (::eglChooseConfig(_display, pixelFormat, &_config, 1, &num) == EGL_FALSE)
			{
				GL_PLATFORM_LOG("eglChooseConfig() fail.");
				return false;
			}

			return true;
		}

		bool
		EGL2Swapchain::initSwapchain(const GraphicsSwapchainDesc& swapchainDesc) noexcept
		{
			EGLint attribs[80];
			EGLint index = 0;

		#if !defined(_BUILD_PLATFORM_ANDROID)
			attribs[index++] = EGL_CONTEXT_MAJOR_VERSION;
			attribs[index++] = 2;

			attribs[index++] = EGL_CONTEXT_MINOR_VERSION;
			attribs[index++] = 0;
		#else
			attribs[index++] = EGL_CONTEXT_CLIENT_VERSION;
			attribs[index++] = 2;
		#endif

			attribs[index++] = EGL_NONE;
			attribs[index++] = EGL_NONE;

			_context = ::eglCreateContext(_display, _config, EGL_NO_CONTEXT, attribs);
			if (eglGetError() != EGL_SUCCESS)
			{
				GL_PLATFORM_LOG("eglCreateContext() fail.");
				return false;
			}

			this->setSwapInterval(swapchainDesc.getSwapInterval());
			return true;
		}

		const GraphicsSwapchainDesc&
		EGL2Swapchain::getGraphicsSwapchainDesc() const noexcept
		{
			return _swapchainDesc;
		}

		void
		EGL2Swapchain::setDevice(GraphicsDevicePtr device) noexcept
		{
			_device = device;
		}

		GraphicsDevicePtr
		EGL2Swapchain::getDevice() noexcept
		{
			return _device.lock();
		}
	}
}