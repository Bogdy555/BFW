#ifndef BFW_WINDOWS_GUI_hpp

#define BFW_WINDOWS_GUI_hpp



#include "BFW_WINDOWS.hpp"



namespace BFW_WINDOWS
{

	namespace GUI
	{

		enum PopUpIds : const uint64_t
		{
			_LeftResizePopUpId = 1,
			_RightResizePopUpId = 2,
			_TopResizePopUpId = 3,
			_BottomResizePopUpId = 4,
			_LeftTopResizePopUpId = 5,
			_LeftBottomResizePopUpId = 6,
			_RightTopResizePopUpId = 7,
			_RightBottomResizePopUpId = 8,
			_ExamplePopUpId = 9,
			_SpawnButtonPopUpId = 10
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

			std::mutex* RenderingMutex;
			BFW::GUI::PopUp Layout;

			bool LCapture;
			BFW::Vector<BFW::GUI::PopUp*> LCapturePath;
			intptr_t LCaptureMouseX;
			intptr_t LCaptureMouseY;
			intptr_t LCaptureMouseXLastFrame;
			intptr_t LCaptureMouseYLastFrame;

			bool MCapture;
			BFW::Vector<BFW::GUI::PopUp*> MCapturePath;
			intptr_t MCaptureMouseX;
			intptr_t MCaptureMouseY;
			intptr_t MCaptureMouseXLastFrame;
			intptr_t MCaptureMouseYLastFrame;

			bool RCapture;
			BFW::Vector<BFW::GUI::PopUp*> RCapturePath;
			intptr_t RCaptureMouseX;
			intptr_t RCaptureMouseY;
			intptr_t RCaptureMouseXLastFrame;
			intptr_t RCaptureMouseYLastFrame;

			bool X1Capture;
			BFW::Vector<BFW::GUI::PopUp*> X1CapturePopUp;
			intptr_t X1CaptureMouseX;
			intptr_t X1CaptureMouseY;
			intptr_t X1CaptureMouseXLastFrame;
			intptr_t X1CaptureMouseYLastFrame;

			bool X2Capture;
			BFW::Vector<BFW::GUI::PopUp*> X2CapturePopUp;
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

		extern const size_t ChildMinX;
		extern const size_t ChildMinY;

		extern const size_t ResizeSize;

		extern const size_t ExampleMinX;
		extern const size_t ExampleMinY;

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

		void SetupRenderData(void* _Wnd, void* _ParentWnd, void* _Global);
		void CleanUpRenderData(void* _Wnd, void* _Global);
		void RenderGray20(void* _Wnd, void* _Global);
		void RenderGray30(void* _Wnd, void* _Global);
		void RenderGray40(void* _Wnd, void* _Global);
		void Composit(void* _ParentWnd, void* _ChildWnd, void* _Global);

		void ResizeChilds(BFW::GUI::PopUp& _Layout, BFW::RunTime::Menu* _Menu);
		void GenerateExample(BFW::GUI::PopUp& _Parent, BFW::RunTime::Menu* _Menu, const bool _IsNode);
		void RenderCursor(BFW::GUI::Window& _Wnd, const uint64_t _PopUpId);

	}

}



#endif
