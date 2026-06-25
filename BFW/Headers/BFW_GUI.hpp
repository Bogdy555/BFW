#ifndef BFW_GUI_hpp

#define BFW_GUI_hpp



#include "BFW.hpp"



namespace BFW
{

	namespace GUI
	{

#if defined BFW_WINDOWS_PLATFORM || defined BFW_LINUX_PLATFORM

		class BFW_API Window
		{

		public:

			Window();
			Window(const Window& _Other) = delete;
			Window(Window&& _Other) noexcept = delete;
			~Window();

			const bool Create(const uint32_t _ExStyle, const BFW_CHAR_TYPE* _ClassName, const BFW_CHAR_TYPE* _WindowName, const uint32_t _Style, const int32_t _X, const int32_t _Y, const int32_t _Width, const int32_t _Height, const HWND _ParentHandle, const HMENU _MenuHandle, const HINSTANCE _InstanceHandle, void* _Param, const HACCEL _AccelHandle, const bool (*_ThreadInitFnc)(void* _UserData), void (*_ThreadCleanUpFnc)(void* _UserData), const bool (*_WndInitFnc)(Window* _Wnd), void (*_WndCleanUpFnc)(Window* _Wnd), void* _UserData);
			void Destroy();
			const bool GoFullScreen(const HWND _InsertAfter = HWND_TOP, const uint32_t _Flags = SWP_ASYNCWINDOWPOS);
			const bool GoWindowed(const uint32_t _Style = WS_OVERLAPPEDWINDOW, const HWND _InsertAfter = HWND_TOP, const uint32_t _Flags = SWP_ASYNCWINDOWPOS);
			void SetCursorIcon(const HCURSOR _Cursor);
			void UpdateInputState();
			void CleanInputState();
			void CleanEvents();
			const bool Show(const int32_t _ShowCmd);
			const bool UpdateContent();

			const bool CheckOn() const;
			const HWND GetHandle() const;
			void* GetUserData();
			const void* GetUserData() const;
			const bool IsFullScreen() const;
			const HCURSOR GetCursorIcon() const;
			const bool ShouldClose() const;
			const bool HasFocus() const;
			const Input::Key* GetKeys() const;
			const bool GetMousePosition(intptr_t& _MouseX, intptr_t& _MouseY) const;
			const Vector<uint8_t> GetKeyEvents() const;
			const Vector<Input::ClickEvent> GetLeftClicks() const;
			const Vector<Input::ClickEvent> GetRightClicks() const;
			const Vector<Input::ClickEvent> GetMiddleClicks() const;
			const Vector<Input::ClickEvent> GetX1Clicks() const;
			const Vector<Input::ClickEvent> GetX2Clicks() const;
			const Vector<Input::ClickEvent> GetLeftDoubleClicks() const;
			const Vector<Input::ClickEvent> GetRightDoubleClicks() const;
			const Vector<Input::ClickEvent> GetMiddleDoubleClicks() const;
			const Vector<Input::ClickEvent> GetX1DoubleClicks() const;
			const Vector<Input::ClickEvent> GetX2DoubleClicks() const;
			const Vector<Input::WheelEvent> GetWheelEvents() const;
			const Vector<Input::WheelEvent> GetHorizontalWheelEvents() const;
			const Vector<BFW_CHAR_TYPE> GetCharEvents() const;
			const bool GetClientSize(size_t& _Width, size_t& _Height) const;
			const bool GetWindowSize(size_t& _Width, size_t& _Height) const;
			const uint64_t GetRefreshRate() const;

			operator const HWND () const;

			Window& operator= (const Window& _Other) = delete;
			Window& operator= (Window&& _Other) noexcept = delete;

			static Window* GetWindowPtr(const HWND _Handle);
			static const bool IsDefaultMessage(const UINT _Msg);
			static LRESULT HandleDefaultMessage(HWND _hWnd, UINT _Msg, WPARAM _wParam, LPARAM _lParam);

		private:

			static void WndThreadFnc(bool& _Done, bool& _Fail, Window* _Wnd, const uint32_t _ExStyle, const BFW_CHAR_TYPE* _ClassName, const BFW_CHAR_TYPE* _WindowName, const uint32_t _Style, const int32_t _X, const int32_t _Y, const int32_t _Width, const int32_t _Height, const HWND _ParentHandle, const HMENU _MenuHandle, const HINSTANCE _InstanceHandle, void* _Param, const HACCEL _AccelHandle, const bool (*_ThreadInitFnc)(void* _UserData), void (*_ThreadCleanUpFnc)(void* _UserData), const bool (*_WndInitFnc)(Window* _Wnd), void (*_WndCleanUpFnc)(Window* _Wnd), void* _UserData);

			HWND Handle;
			std::thread* WndThread;
			void* UserData;

			bool FullScreen;
			RECT WndRect;
			WINDOWPLACEMENT WndPlace;

			std::mutex* WindowMutex;
			HCURSOR Cursor;
			bool Close;
			bool Focus;
			bool RawKeys[256];
			Input::Key Keys[256];
			bool Tracking;
			bool HasMouse;
			intptr_t MouseX;
			intptr_t MouseY;
			Vector<uint8_t> KeyEvents;
			Vector<Input::ClickEvent> LClicks;
			Vector<Input::ClickEvent> MClicks;
			Vector<Input::ClickEvent> RClicks;
			Vector<Input::ClickEvent> X1Clicks;
			Vector<Input::ClickEvent> X2Clicks;
			Vector<Input::ClickEvent> LDblClicks;
			Vector<Input::ClickEvent> MDblClicks;
			Vector<Input::ClickEvent> RDblClicks;
			Vector<Input::ClickEvent> X1DblClicks;
			Vector<Input::ClickEvent> X2DblClicks;
			Vector<Input::WheelEvent> WheelEvents;
			Vector<Input::WheelEvent> HWheelEvents;
			Vector<BFW_CHAR_TYPE> CharEvents;

		};

#endif

		enum BFW_API PopUpIds : const uint64_t
		{
			_NodePopUpId = 0
		};

		enum BFW_API PanelTypes : const uint8_t
		{
			_NullPanelType = 0,
			_LeftPanelType = 1,
			_RightPanelType = 2,
			_TopPanelType = 3,
			_BottomPanelType = 4
		};

		typedef void (*SetupRenderDataFnc)(void* _Wnd, void* _ParentWnd, void* _Global);
		typedef void (*CleanUpRenderDataFnc)(void* _Wnd, void* _Global);
		typedef void (*RenderFnc)(void* _Wnd, void* _Global);
		typedef void (*CompositFnc)(void* _ParentWnd, void* _ChildWnd, void* _Global);

		class BFW_API PopUp
		{

		public:

			PopUp();
			PopUp(const PopUp& _Other);
			PopUp(PopUp&& _Other) noexcept;
			~PopUp();

			PopUp& Begin(const uint64_t _Id, const uint8_t _PanelType, const size_t _MinWidth, const size_t _MinHeight, const size_t _Width, const size_t _Height, const intptr_t _PositionX, const intptr_t _PositionY, const size_t _ScrollX, const size_t _ScrollY, const SetupRenderDataFnc _SetupData, const CleanUpRenderDataFnc _CleanUpData, const RenderFnc _RenderBottom, const RenderFnc _RenderMiddle, const RenderFnc _RenderTop, const CompositFnc _Composit, void* _UserData);
			PopUp& PushLeftPanel(const uint64_t _Id, const size_t _MinWidth, const size_t _MinHeight, const size_t _Width, const size_t _ScrollX, const size_t _ScrollY, const SetupRenderDataFnc _SetupData, const CleanUpRenderDataFnc _CleanUpData, const RenderFnc _RenderBottom, const RenderFnc _RenderMiddle, const RenderFnc _RenderTop, const CompositFnc _Composit, void* _UserData, const bool _Focused = false);
			PopUp& PushRightPanel(const uint64_t _Id, const size_t _MinWidth, const size_t _MinHeight, const size_t _Width, const size_t _ScrollX, const size_t _ScrollY, const SetupRenderDataFnc _SetupData, const CleanUpRenderDataFnc _CleanUpData, const RenderFnc _RenderBottom, const RenderFnc _RenderMiddle, const RenderFnc _RenderTop, const CompositFnc _Composit, void* _UserData, const bool _Focused = false);
			PopUp& PushTopPanel(const uint64_t _Id, const size_t _MinWidth, const size_t _MinHeight, const size_t _Height, const size_t _ScrollX, const size_t _ScrollY, const SetupRenderDataFnc _SetupData, const CleanUpRenderDataFnc _CleanUpData, const RenderFnc _RenderBottom, const RenderFnc _RenderMiddle, const RenderFnc _RenderTop, const CompositFnc _Composit, void* _UserData, const bool _Focused = false);
			PopUp& PushBottomPanel(const uint64_t _Id, const size_t _MinWidth, const size_t _MinHeight, const size_t _Height, const size_t _ScrollX, const size_t _ScrollY, const SetupRenderDataFnc _SetupData, const CleanUpRenderDataFnc _CleanUpData, const RenderFnc _RenderBottom, const RenderFnc _RenderMiddle, const RenderFnc _RenderTop, const CompositFnc _Composit, void* _UserData, const bool _Focused = false);
			PopUp& PushNode(const uint64_t _Id, const size_t _MinWidth, const size_t _MinHeight, const size_t _ScrollX, const size_t _ScrollY, const SetupRenderDataFnc _SetupData, const CleanUpRenderDataFnc _CleanUpData, const RenderFnc _RenderBottom, const RenderFnc _RenderMiddle, const RenderFnc _RenderTop, const CompositFnc _Composit, void* _UserData, const bool _Focused = false);
			const size_t PushPopUpLayer();
			PopUp& PushPopUp(const size_t _Layer, const uint64_t _Id, const size_t _MinWidth, const size_t _MinHeight, const size_t _Width, const size_t _Height, const intptr_t _PositionX, const intptr_t _PositionY, const size_t _ScrollX, const size_t _ScrollY, const SetupRenderDataFnc _SetupData, const CleanUpRenderDataFnc _CleanUpData, const RenderFnc _RenderBottom, const RenderFnc _RenderMiddle, const RenderFnc _RenderTop, const CompositFnc _Composit, void* _UserData, const bool _Focused = false);
			void Render(void* _Global);
			void SetFocusedPanel(const size_t _FocusedPanel);
			void SetFocusedNode(const size_t _FocusedNode);
			void SetId(const uint64_t _Id);
			void SetPanelType(const uint8_t _PanelType);
			void SetTrueWidth(const size_t _MinWidth);
			void SetTrueHeight(const size_t _MinHeight);
			void SetWidth(const size_t _Width);
			void SetHeight(const size_t _Height);
			void SetPositionX(const intptr_t _PositionX);
			void SetPositionY(const intptr_t _PositionY);
			void SetScrollX(const size_t _ScrollX);
			void SetScrollY(const size_t _ScrollY);
			void SetUserData(void* _UserData);
			void SetSetupData(const SetupRenderDataFnc _SetupData);
			void SetCleanUpData(const CleanUpRenderDataFnc _CleanUpData);
			void SetRenderBottom(const RenderFnc _RenderBottom);
			void SetRenderMiddle(const RenderFnc _RenderMiddle);
			void SetRenderTop(const RenderFnc _RenderTop);
			void SetComposit(const CompositFnc _Composit);

			PopUp* GetChildFromMouse(const intptr_t _MouseX, const intptr_t _MouseY, Vector<PopUp*>* _Path = nullptr);
			const PopUp* GetChildFromMouse(const intptr_t _MouseX, const intptr_t _MouseY, Vector<const PopUp*>* _Path = nullptr) const;
			const size_t GetFocusedPanel() const;
			Vector<PopUp>& GetPanels();
			const Vector<PopUp>& GetPanels() const;
			const size_t GetFocusedNode() const;
			Vector<PopUp>& GetNodes();
			const Vector<PopUp>& GetNodes() const;
			Vector<size_t>& GetFocusedPopUps();
			const Vector<size_t>& GetFocusedPopUps() const;
			Vector<Vector<PopUp>>& GetPopUps();
			const Vector<Vector<PopUp>>& GetPopUps() const;
			const uint64_t GetId() const;
			const uint8_t GetPanelType() const;
			const size_t GetTrueWidth() const;
			const size_t GetTrueHeight() const;
			const size_t GetWidth() const;
			const size_t GetHeight() const;
			const intptr_t GetPositionX() const;
			const intptr_t GetPositionY() const;
			const size_t GetScrollX() const;
			const size_t GetScrollY() const;
			void* GetUserData();
			const void* GetUserData() const;
			const SetupRenderDataFnc GetSetupData() const;
			const CleanUpRenderDataFnc GetCleanUpData() const;
			const RenderFnc GetRenderBottom() const;
			const RenderFnc GetRenderMiddle() const;
			const RenderFnc GetRenderTop() const;
			const CompositFnc GetComposit() const;

			PopUp& operator= (const PopUp& _Other);
			PopUp& operator= (PopUp&& _Other) noexcept;

		private:

			size_t FocusedPanel;
			Vector<PopUp> Panels;
			size_t FocusedNode;
			Vector<PopUp> Nodes;
			Vector<size_t> FocusedPopUps;
			Vector<Vector<PopUp>> PopUps;

			uint64_t Id;
			uint8_t PanelType;

			size_t TrueWidth;
			size_t TrueHeight;
			size_t Width;
			size_t Height;
			intptr_t PositionX;
			intptr_t PositionY;
			size_t ScrollX;
			size_t ScrollY;

			void* UserData;
			SetupRenderDataFnc SetupData;
			CleanUpRenderDataFnc CleanUpData;
			RenderFnc RenderBottom;
			RenderFnc RenderMiddle;
			RenderFnc RenderTop;
			CompositFnc Composit;

		};

	}

}



#endif
