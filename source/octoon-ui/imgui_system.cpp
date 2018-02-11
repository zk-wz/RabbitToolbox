#include <octoon/ui/imgui_system.h>

#include <imgui.h>
#include <imgui_dock.h>

namespace octoon
{
	namespace imgui
	{
		System::System() noexcept
			: initialize_(false)
			, window_(nullptr)
			, imguiPath_("../../ui/imgui.layout")
			, imguiDockPath_("../../ui/imgui_dock.layout")
		{
		}

		System::~System() noexcept
		{
			this->close();
		}

		bool
		System::open(input::WindHandle window) except
		{
			assert(window);
			assert(!initialize_);
#if _WINDOWS
			assert(::IsWindow((HWND)window));
#endif

			GuiStyle style;
			setStyle(style);

			ImGuiIO& io = ImGui::GetIO();
			io.ImeWindowHandle = window_ = window;
			io.IniFilename = imguiPath_.c_str();
			io.KeyMap[ImGuiKey_Tab] = input::InputKey::Tab;
			io.KeyMap[ImGuiKey_LeftArrow] = input::InputKey::ArrowLeft;
			io.KeyMap[ImGuiKey_RightArrow] = input::InputKey::ArrowRight;
			io.KeyMap[ImGuiKey_UpArrow] = input::InputKey::ArrowUp;
			io.KeyMap[ImGuiKey_DownArrow] = input::InputKey::ArrowDown;
			io.KeyMap[ImGuiKey_PageUp] = input::InputKey::PageUp;
			io.KeyMap[ImGuiKey_PageDown] = input::InputKey::PageDown;
			io.KeyMap[ImGuiKey_Home] = input::InputKey::Home;
			io.KeyMap[ImGuiKey_End] = input::InputKey::End;
			io.KeyMap[ImGuiKey_Delete] = input::InputKey::Delete;
			io.KeyMap[ImGuiKey_Backspace] = input::InputKey::Backspace;
			io.KeyMap[ImGuiKey_Enter] = input::InputKey::KP_Enter;
			io.KeyMap[ImGuiKey_Escape] = input::InputKey::Escape;
			io.KeyMap[ImGuiKey_A] = input::InputKey::A;
			io.KeyMap[ImGuiKey_C] = input::InputKey::C;
			io.KeyMap[ImGuiKey_V] = input::InputKey::V;
			io.KeyMap[ImGuiKey_X] = input::InputKey::X;
			io.KeyMap[ImGuiKey_Y] = input::InputKey::Y;
			io.KeyMap[ImGuiKey_Z] = input::InputKey::Z;

			graphics::GraphicsDeviceDesc deviceDesc;
			deviceDesc.setDeviceType(graphics::GraphicsDeviceType::GraphicsDeviceTypeOpenGL);
			device_ = graphics::GraphicsSystem::instance()->createDevice(deviceDesc);
			if (!device_)
				return false;

			graphics::GraphicsSwapchainDesc swapchainDesc;
			swapchainDesc.setWindHandle(window);
			swapchainDesc.setWidth(1);
			swapchainDesc.setHeight(1);
			swapchainDesc.setSwapInterval(graphics::GraphicsSwapInterval::GraphicsSwapIntervalVsync);
			swapchainDesc.setImageNums(2);
			swapchainDesc.setColorFormat(graphics::GraphicsFormat::GraphicsFormatB8G8R8A8UNorm);
			swapchainDesc.setDepthStencilFormat(graphics::GraphicsFormat::GraphicsFormatD24UNorm_S8UInt);
			swapchain_ = device_->createSwapchain(swapchainDesc);
			if (!swapchain_)
				return false;

			graphics::GraphicsContextDesc contextDesc;
			contextDesc.setSwapchain(swapchain_);
			context_ = device_->createDeviceContext(contextDesc);
			if (!context_)
				return false;

			graphics::GraphicsDataDesc dataDesc;
			dataDesc.setType(graphics::GraphicsDataType::GraphicsDataTypeStorageVertexBuffer);
			dataDesc.setStream(0);
			dataDesc.setStreamSize(0xFFF * sizeof(ImDrawVert));
			dataDesc.setUsage(graphics::GraphicsUsageFlagBits::GraphicsUsageFlagWriteBit);

			vbo_ = device_->createGraphicsData(dataDesc);
			if (!vbo_)
				return false;

			graphics::GraphicsDataDesc elementDesc;
			elementDesc.setType(graphics::GraphicsDataType::GraphicsDataTypeStorageIndexBuffer);
			elementDesc.setStream(0);
			elementDesc.setStreamSize(0xFFF * sizeof(ImDrawIdx));
			elementDesc.setUsage(graphics::GraphicsUsageFlagBits::GraphicsUsageFlagWriteBit);

			ibo_ = device_->createGraphicsData(elementDesc);
			if (!ibo_)
				return false;

			initialize_ = true;
			return true;
		}

		void
		System::close() noexcept
		{
			vbo_.reset();
			ibo_.reset();
			texture_.reset();

			context_.reset();
			swapchain_.reset();
			device_.reset();

			if (initialize_)
			{
				ImGui::ShutdownDock();
				ImGui::Shutdown();

				initialize_ = false;
			}
		}

		bool
		System::inject_mouse_move(float absx, float absy) noexcept
		{
			auto& io = ImGui::GetIO();
			io.MousePos.x = absx;
			io.MousePos.y = absy;
			return true;
		}

		bool
		System::inject_mouse_press(float absx, float absy, input::InputButton::Code code) noexcept
		{
			auto& io = ImGui::GetIO();
			io.MouseDown[code] = true;
			io.MousePos.x = absx;
			io.MousePos.y = absy;
			return true;
		}

		bool
		System::inject_mouse_release(float absx, float absy, input::InputButton::Code code) noexcept
		{
			auto& io = ImGui::GetIO();
			io.MouseDown[code] = false;
			io.MousePos.x = absx;
			io.MousePos.y = absy;
			return true;
		}

		bool
		System::inject_mouse_wheel(float wheel) noexcept
		{
			auto& io = ImGui::GetIO();
			io.MouseWheel = wheel;
			return true;
		}

		bool
		System::inject_key_press(input::InputKey::Code key, wchar_t char_) noexcept
		{
			auto& io = ImGui::GetIO();
			if (key != input::InputKey::Code::None)
			{
				if (key == input::InputKey::Code::LeftControl)
					io.KeyCtrl = true;
				else if (key == input::InputKey::Code::LeftShift)
					io.KeyShift = true;
				else if (key == input::InputKey::Code::LeftAlt)
					io.KeyAlt = true;
				else if (key == input::InputKey::Code::LeftSuper)
					io.KeySuper = true;

				io.KeysDown[key] = true;
			}
			else
			{
				io.AddInputCharacter(char_);
			}

			return true;
		}

		bool
		System::inject_key_release(input::InputKey::Code key) noexcept
		{
			auto& io = ImGui::GetIO();
			if (key == input::InputKey::Code::LeftControl)
				io.KeyCtrl = false;
			else if (key == input::InputKey::Code::LeftShift)
				io.KeyShift = false;
			else if (key == input::InputKey::Code::LeftAlt)
				io.KeyAlt = false;
			else if (key == input::InputKey::Code::LeftSuper)
				io.KeySuper = false;

			io.KeysDown[key] = false;
			return true;
		}

		bool
		System::inject_window_focus(bool focus) noexcept
		{
			if (focus)
			{
				auto& io = ImGui::GetIO();

				std::memset(io.KeysDown, 0, sizeof(io.KeysDown));
				std::memset(io.MouseDown, 0, sizeof(io.MouseDown));
			}

			return true;
		}

		void
		System::set_viewport(std::uint32_t w, std::uint32_t h) noexcept
		{
			ImGuiIO& io = ImGui::GetIO();
			io.DisplaySize.x = w;
			io.DisplaySize.y = h;
		}

		void
		System::get_viewport(std::uint32_t& w, std::uint32_t& h) noexcept
		{
			ImGuiIO& io = ImGui::GetIO();
			w = io.DisplaySize.x;
			h = io.DisplaySize.y;
		}

		void
		System::set_framebuffer_scale(std::uint32_t w, std::uint32_t h) noexcept
		{
			ImGuiIO& io = ImGui::GetIO();
			io.DisplayFramebufferScale.x = w;
			io.DisplayFramebufferScale.y = h;

			math::float4x4 project;
			project.make_ortho_lh(0, w, h, 0, 0, 1);

			// _materialProj->uniform4fmat(project);
		}

		void
		System::get_framebuffer_scale(std::uint32_t& w, std::uint32_t& h) noexcept
		{
			ImGuiIO& io = ImGui::GetIO();
			w = io.DisplayFramebufferScale.x;
			h = io.DisplayFramebufferScale.y;
		}

		bool
		System::load_font(const char* path, float font_size) noexcept
		{
			static const ImWchar ranges[] =
			{
				0x0020, 0x00FF, // Basic Latin + Latin Supplement
				0x4e00, 0x9FAF, // CJK Ideograms
				0,
			};

			std::uint8_t* pixels;
			int width, height;

			auto io = ImGui::GetIO();
			io.Fonts->ClearFonts();
			io.Fonts->AddFontFromFileTTF(path, font_size, 0, 0);
			io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

			graphics::GraphicsTextureDesc fontDesc;
			fontDesc.setSize(width, height);
			fontDesc.setTexDim(graphics::GraphicsTextureDim::GraphicsTextureDim2D);
			fontDesc.setTexFormat(graphics::GraphicsFormat::GraphicsFormatR8G8B8A8UNorm);
			fontDesc.setStream(pixels);
			fontDesc.setStreamSize(width * height * sizeof(std::uint32_t));
			fontDesc.setTexTiling(graphics::GraphicsImageTiling::GraphicsImageTilingLinear);
			fontDesc.setSamplerFilter(graphics::GraphicsSamplerFilter::GraphicsSamplerFilterLinearMipmapLinear, graphics::GraphicsSamplerFilter::GraphicsSamplerFilterLinear);
			fontDesc.setSamplerWrap(graphics::GraphicsSamplerWrap::GraphicsSamplerWrapClampToEdge);

			texture_ = device_->createTexture(fontDesc);
			if (!texture_)
				return false;

			io.Fonts->TexID = (void*)texture_.get();

			return true;
		}

		void
		System::render() noexcept
		{
			auto drawData = ImGui::GetDrawData();
			if (!drawData)
				return;

			std::size_t totalVertexSize = drawData->TotalVtxCount * sizeof(ImDrawVert);
			std::size_t totalIndirectSize = drawData->TotalIdxCount * sizeof(ImDrawIdx);
			if (totalVertexSize == 0 || totalIndirectSize == 0)
				return;

			if (!vbo_ || vbo_->getGraphicsDataDesc().getStreamSize() < totalVertexSize)
			{
				graphics::GraphicsDataDesc dataDesc;
				dataDesc.setType(graphics::GraphicsDataType::GraphicsDataTypeStorageVertexBuffer);
				dataDesc.setStream(0);
				dataDesc.setStreamSize(totalVertexSize);
				dataDesc.setUsage(vbo_->getGraphicsDataDesc().getUsage());

				vbo_ = device_->createGraphicsData(dataDesc);
				if (!vbo_)
				return;
			}

			if (!ibo_ || ibo_->getGraphicsDataDesc().getStreamSize() < totalIndirectSize)
			{
				graphics::GraphicsDataDesc elementDesc;
				elementDesc.setType(graphics::GraphicsDataType::GraphicsDataTypeStorageIndexBuffer);
				elementDesc.setStream(0);
				elementDesc.setStreamSize(totalIndirectSize);
				elementDesc.setUsage(ibo_->getGraphicsDataDesc().getUsage());

				ibo_ = device_->createGraphicsData(elementDesc);
				if (!ibo_)
					return;
			}

			ImDrawVert* vbo;
			ImDrawIdx* ibo;

			if (!vbo_->map(0, totalVertexSize, (void**)&vbo))
				return;

			if (!ibo_->map(0, totalIndirectSize, (void**)&ibo))
				return;

			for (int n = 0; n < drawData->CmdListsCount; n++)
			{
				const ImDrawList* cmd_list = drawData->CmdLists[n];
				std::memcpy(vbo, cmd_list->VtxBuffer.Data, cmd_list->VtxBuffer.size() * sizeof(ImDrawVert));
				std::memcpy(ibo, cmd_list->IdxBuffer.Data, cmd_list->IdxBuffer.size() * sizeof(ImDrawIdx));
				vbo += cmd_list->VtxBuffer.size();
				ibo += cmd_list->IdxBuffer.size();
			}

			vbo_->unmap();
			ibo_->unmap();

			auto& io = ImGui::GetIO();

			context_->renderBegin();

			context_->clearFramebuffer(0, graphics::GraphicsClearFlagBits::GraphicsClearFlagColorBit, float4(0.1,0.2,0.3), 1, 0);
			context_->setViewport(0, graphics::Viewport(0, 0, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y));
			context_->setScissor(0, graphics::Scissor(0, 0, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y));

			context_->setVertexBufferData(0, vbo_, 0);
			context_->setIndexBufferData(ibo_, 0, graphics::GraphicsIndexType::GraphicsIndexTypeUInt16);

			std::uint32_t vdx_buffer_offset = 0;
			std::uint32_t idx_buffer_offset = 0;

			/*for (int n = 0; n < drawData->CmdListsCount; n++)
			{
				const ImDrawList* cmd_list = drawData->CmdLists[n];

				for (const ImDrawCmd* pcmd = cmd_list->CmdBuffer.begin(); pcmd != cmd_list->CmdBuffer.end(); pcmd++)
				{
					auto texture = (graphics::GraphicsTexture*)pcmd->TextureId;
					if (texture)
						_materialDecal->uniformTexture(texture->downcast_pointer<graphics::GraphicsTexture>());
					else
						_materialDecal->uniformTexture(nullptr);

					ImVec4 scissor((int)pcmd->ClipRect.x, (int)pcmd->ClipRect.y, (int)(pcmd->ClipRect.z - pcmd->ClipRect.x), (int)(pcmd->ClipRect.w - pcmd->ClipRect.y));

					context_->setScissor(0, graphics::Scissor(scissor.x, scissor.y, scissor.z, scissor.w));

					//context_->setMaterialPass(_materialTech->getPass(0));
					context_->drawIndexed(pcmd->ElemCount, 1, idx_buffer_offset, vdx_buffer_offset, 0);

					idx_buffer_offset += pcmd->ElemCount;
				}

				vdx_buffer_offset += cmd_list->VtxBuffer.size();
			}*/

			context_->renderEnd();
			context_->present();
		}
	}
}