#ifndef BFW_WINDOWS_GUI_hpp

#define BFW_WINDOWS_GUI_hpp



#include "BFW_WINDOWS.hpp"



namespace BFW_WINDOWS
{

	namespace GUI
	{

		enum PopUpIds : const uint64_t
		{
			_ExamplePopUpId = 1,
			_SpawnButtonPopUpId = 2
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
			BFW::GUI::PopUp* LCapturePopUp;
			intptr_t LCaptureMouseX;
			intptr_t LCaptureMouseY;

			bool MCapture;
			BFW::GUI::PopUp* MCapturePopUp;
			intptr_t MCaptureMouseX;
			intptr_t MCaptureMouseY;

			bool RCapture;
			BFW::GUI::PopUp* RCapturePopUp;
			intptr_t RCaptureMouseX;
			intptr_t RCaptureMouseY;

			bool X1Capture;
			BFW::GUI::PopUp* X1CapturePopUp;
			intptr_t X1CaptureMouseX;
			intptr_t X1CaptureMouseY;

			bool X2Capture;
			BFW::GUI::PopUp* X2CapturePopUp;
			intptr_t X2CaptureMouseX;
			intptr_t X2CaptureMouseY;

			WindowData();
			WindowData(const WindowData& _Other) = default;
			WindowData(WindowData&& _Other) noexcept;
			WindowData& operator= (const WindowData& _Other) = default;
			WindowData& operator= (WindowData&& _Other) noexcept;

		};

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
		void GenerateExample(BFW::GUI::PopUp& _Parent, BFW::RunTime::Menu* _Menu);
		void RenderCursor(BFW::GUI::Window& _Wnd, const uint64_t _PopUpId);

	}

}



#endif
