#ifndef BFW_WINDOWS_GUI_hpp

#define BFW_WINDOWS_GUI_hpp



#include "BFW_WINDOWS.hpp"



namespace BFW_WINDOWS
{

	namespace GUI
	{

		enum PopUpIds : const uint64_t
		{
			_DebugWindowPopUpId = 14,
			_SpawnButtonPopUpId = 15
		};

		struct PopUpData
		{

			size_t Width, Height;
			uint8_t* Pixels;

			BFW::GUI::Window* Wnd;

			PopUpData();
			PopUpData(const PopUpData& _Other) = default;
			PopUpData(PopUpData&& _Other) noexcept;
			PopUpData& operator= (const PopUpData& _Other) = default;
			PopUpData& operator= (PopUpData&& _Other) noexcept;

		};

		struct WindowData
		{

			std::mutex* LayoutMutex;
			BFW::GUI::PopUp Layout;

			bool LCapture;
			BFW::Vector<BFW::GUI::SafePopUpPointer> LCapturePath;
			intptr_t LCaptureMouseX;
			intptr_t LCaptureMouseY;
			intptr_t LCaptureMouseXLastFrame;
			intptr_t LCaptureMouseYLastFrame;
			intptr_t ScrollAccumulationX;
			intptr_t ScrollAccumulationY;

			bool MCapture;
			BFW::Vector<BFW::GUI::SafePopUpPointer> MCapturePath;
			intptr_t MCaptureMouseX;
			intptr_t MCaptureMouseY;
			intptr_t MCaptureMouseXLastFrame;
			intptr_t MCaptureMouseYLastFrame;

			bool RCapture;
			BFW::Vector<BFW::GUI::SafePopUpPointer> RCapturePath;
			intptr_t RCaptureMouseX;
			intptr_t RCaptureMouseY;
			intptr_t RCaptureMouseXLastFrame;
			intptr_t RCaptureMouseYLastFrame;

			bool X1Capture;
			BFW::Vector<BFW::GUI::SafePopUpPointer> X1CapturePath;
			intptr_t X1CaptureMouseX;
			intptr_t X1CaptureMouseY;
			intptr_t X1CaptureMouseXLastFrame;
			intptr_t X1CaptureMouseYLastFrame;

			bool X2Capture;
			BFW::Vector<BFW::GUI::SafePopUpPointer> X2CapturePath;
			intptr_t X2CaptureMouseX;
			intptr_t X2CaptureMouseY;
			intptr_t X2CaptureMouseXLastFrame;
			intptr_t X2CaptureMouseYLastFrame;

			WindowData();
			WindowData(const WindowData& _Other) = default;
			WindowData(WindowData&& _Other) noexcept;
			WindowData& operator= (const WindowData& _Other) = default;
			WindowData& operator= (WindowData&& _Other) noexcept;

		};

		extern const float MouseCaptureScrollSpeed;
		extern const size_t MouseCaptureScrollScale;

		extern const size_t MainWindowMinX;
		extern const size_t MainWindowMinY;
		extern const size_t ChildWindowMinX;
		extern const size_t ChildWindowMinY;

		extern const size_t ResizeSize;
		extern const size_t ScrollSize;
		extern const size_t TopPadding;
		extern const size_t Padding;
		extern const size_t ScrollTopPadding;
		extern const size_t ScrollPadding;

		extern const size_t DebugWindowMinX;
		extern const size_t DebugWindowMinY;

		LRESULT CALLBACK MainWindowProc(HWND _hWnd, UINT _Msg, WPARAM _wParam, LPARAM _lParam);
		const bool MainWindowThreadInit(void* _UserData);
		void MainWindowThreadCleanUp(void* _UserData);
		const bool MainWindowInit(BFW::GUI::Window* _Wnd);
		void MainWindowCleanUp(BFW::GUI::Window* _Wnd);

		LRESULT CALLBACK ChildWindowProc(HWND _hWnd, UINT _Msg, WPARAM _wParam, LPARAM _lParam);
		const bool ChildWindowThreadInit(void* _UserData);
		void ChildWindowThreadCleanUp(void* _UserData);
		const bool ChildWindowInit(BFW::GUI::Window* _Wnd);
		void ChildWindowCleanUp(BFW::GUI::Window* _Wnd);

		void SetupRenderData(BFW::GUI::PopUp& _Wnd, BFW::GUI::PopUp& _ParentWnd, void* _Global);
		void CleanUpRenderData(BFW::GUI::PopUp& _Wnd, void* _Global);
		void RenderGray25(BFW::GUI::PopUp& _Wnd, void* _Global);
		void RenderGray30(BFW::GUI::PopUp& _Wnd, void* _Global);
		void RenderGray40(BFW::GUI::PopUp& _Wnd, void* _Global);
		void Composit(BFW::GUI::PopUp& _ParentWnd, BFW::GUI::PopUp& _ChildWnd, void* _Global);

		const size_t GetMinX(const uint64_t _PopUpId);
		const size_t GetMinY(const uint64_t _PopUpId);
		const bool ForceHScroll(const uint64_t _PopUpId);
		const bool ForceVScroll(const uint64_t _PopUpId);
		const bool IgnoreHScroll(const uint64_t _PopUpId);
		const bool IgnoreVScroll(const uint64_t _PopUpId);
		const bool FindScrollableWindow(size_t& _Index, const BFW::Vector<BFW::GUI::SafePopUpPointer>& _Path);
		void ResizeChilds(BFW::GUI::PopUp& _Parnet);
		void GenerateScrollBars(BFW::GUI::PopUp& _Parent, const bool _HasHScroll, const bool _HasVScroll, const bool _ForceHScroll, const bool _ForceVScroll);
		void GenerateResizeBars(BFW::GUI::PopUp& _Parent, const bool _IsNode);
		void RenderCursor(BFW::GUI::Window& _Wnd, const uint64_t _PopUpId);

	}

}



#endif
