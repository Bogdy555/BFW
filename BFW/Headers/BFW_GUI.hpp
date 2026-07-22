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

			const bool Create(const uint32_t _ExStyle, const BFW_CHAR_TYPE* _ClassName, const BFW_CHAR_TYPE* _WindowName, const uint32_t _Style, const int32_t _X, const int32_t _Y, const int32_t _Width, const int32_t _Height, const HWND _ParentHandle, const HMENU _MenuHandle, const HINSTANCE _InstanceHandle, void* _Param, const HACCEL _AccelHandle, const ThreadInitFnc _ThreadInit, const ThreadCleanUpFnc _ThreadCleanUp, const WndInitFnc _WndInit, const WndCleanUpFnc _WndCleanUp, void* _UserData);
			void Destroy();
			const bool GoFullScreen(const HWND _InsertAfter = HWND_TOP, const uint32_t _Flags = SWP_ASYNCWINDOWPOS | SWP_FRAMECHANGED);
			const bool GoWindowed(const uint32_t _Style = WS_OVERLAPPEDWINDOW, const HWND _InsertAfter = HWND_TOP, const uint32_t _Flags = SWP_ASYNCWINDOWPOS | SWP_FRAMECHANGED);
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

			static void WndThreadFnc(bool& _Done, bool& _Fail, Window* _Wnd, const uint32_t _ExStyle, const BFW_CHAR_TYPE* _ClassName, const BFW_CHAR_TYPE* _WindowName, const uint32_t _Style, const int32_t _X, const int32_t _Y, const int32_t _Width, const int32_t _Height, const HWND _ParentHandle, const HMENU _MenuHandle, const HINSTANCE _InstanceHandle, void* _Param, const HACCEL _AccelHandle, const ThreadInitFnc _ThreadInit, const ThreadCleanUpFnc _ThreadCleanUp, const WndInitFnc _WndInit, const WndCleanUpFnc _WndCleanUp, void* _UserData);

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
			_NodeWindowPopUpId = 0,
			_LeftResizePopUpId = 1,
			_RightResizePopUpId = 2,
			_TopResizePopUpId = 3,
			_BottomResizePopUpId = 4,
			_LeftTopResizePopUpId = 5,
			_LeftBottomResizePopUpId = 6,
			_RightTopResizePopUpId = 7,
			_RightBottomResizePopUpId = 8,
			_HScrollWindowPopUpId = 9,
			_HScrollButtonPopUpId = 10,
			_VScrollWindowPopUpId = 11,
			_VScrollButtonPopUpId = 12,
			_ScrollCornerPopUpId = 13
		};

		enum BFW_API PanelTypes : const uint8_t
		{
			_NullPanelType = 0,
			_LeftPanelType = 1,
			_RightPanelType = 2,
			_TopPanelType = 3,
			_BottomPanelType = 4
		};

		struct BFW_API RenderingDescriptor
		{

			SetupRenderDataFnc SetupData;
			CleanUpRenderDataFnc CleanUpData;
			RenderFnc RenderBottom;
			RenderFnc RenderMiddle;
			RenderFnc RenderTop;
			CompositFnc Composit;

			RenderingDescriptor();
			RenderingDescriptor(const SetupRenderDataFnc& _SetupData, const CleanUpRenderDataFnc& _CleanUpData, const RenderFnc& _RenderBottom, const RenderFnc& _RenderMiddle, const RenderFnc& _RenderTop, const CompositFnc& _Composit);
			RenderingDescriptor(const RenderingDescriptor& _Other) = default;
			RenderingDescriptor(RenderingDescriptor&& _Other) noexcept;
			RenderingDescriptor& operator= (const RenderingDescriptor& _Other) = default;
			RenderingDescriptor& operator= (RenderingDescriptor&& _Other) noexcept;

		};

		class BFW_API SafePopUpPointer
		{

		public:

			SafePopUpPointer();
			SafePopUpPointer(PopUp* _Pointer);
			SafePopUpPointer(const SafePopUpPointer& _Other);
			SafePopUpPointer(SafePopUpPointer&& _Other) noexcept;
			~SafePopUpPointer();

			operator PopUp* ();
			operator const PopUp* () const;

			PopUp* operator-> ();
			const PopUp* operator-> () const;

			PopUp& operator* ();
			const PopUp& operator* () const;

			SafePopUpPointer& operator= (PopUp* _Pointer);
			SafePopUpPointer& operator= (const SafePopUpPointer& _Other);
			SafePopUpPointer& operator= (SafePopUpPointer&& _Other) noexcept;

		private:

			friend PopUp;

			PopUp* Pointer;

		};

		class BFW_API PopUp
		{

		public:

			PopUp();
			PopUp(const PopUp& _Other);
			PopUp(PopUp&& _Other) noexcept;
			~PopUp();

			PopUp& Begin(const uint64_t _Id, const uint8_t _PanelType, const size_t _MinWidth, const size_t _MinHeight, const size_t _Width, const size_t _Height, const intptr_t _PositionX, const intptr_t _PositionY, const size_t _ScrollX, const size_t _ScrollY, const RenderingDescriptor& _RenderFunctions, const HitBoxFnc _HitBox, void* _UserData);
			PopUp& PushLeftPanel(const uint64_t _Id, const size_t _MinWidth, const size_t _MinHeight, const size_t _Width, const size_t _ScrollX, const size_t _ScrollY, const RenderingDescriptor& _RenderFunctions, const HitBoxFnc _HitBox, void* _UserData, const bool _Focused = false);
			PopUp& PushRightPanel(const uint64_t _Id, const size_t _MinWidth, const size_t _MinHeight, const size_t _Width, const size_t _ScrollX, const size_t _ScrollY, const RenderingDescriptor& _RenderFunctions, const HitBoxFnc _HitBox, void* _UserData, const bool _Focused = false);
			PopUp& PushTopPanel(const uint64_t _Id, const size_t _MinWidth, const size_t _MinHeight, const size_t _Height, const size_t _ScrollX, const size_t _ScrollY, const RenderingDescriptor& _RenderFunctions, const HitBoxFnc _HitBox, void* _UserData, const bool _Focused = false);
			PopUp& PushBottomPanel(const uint64_t _Id, const size_t _MinWidth, const size_t _MinHeight, const size_t _Height, const size_t _ScrollX, const size_t _ScrollY, const RenderingDescriptor& _RenderFunctions, const HitBoxFnc _HitBox, void* _UserData, const bool _Focused = false);
			PopUp& PushNode(const uint64_t _Id, const size_t _MinWidth, const size_t _MinHeight, const size_t _ScrollX, const size_t _ScrollY, const RenderingDescriptor& _RenderFunctions, const HitBoxFnc _HitBox, void* _UserData, const bool _Focused = false);
			const size_t PushPopUpLayer();
			PopUp& PushPopUp(const size_t _Layer, const uint64_t _Id, const size_t _MinWidth, const size_t _MinHeight, const size_t _Width, const size_t _Height, const intptr_t _PositionX, const intptr_t _PositionY, const size_t _ScrollX, const size_t _ScrollY, const RenderingDescriptor& _RenderFunctions, const HitBoxFnc _HitBox, void* _UserData, const bool _Focused = false);
			void Render(void* _Global);
			void ScrollH(const intptr_t _Delta, const IgnoreScrollFnc _IgnoreScroll);
			void ScrollV(const intptr_t _Delta, const IgnoreScrollFnc _IgnoreScroll);
			void ScrollWithMouseH(const intptr_t _Delta, intptr_t& _Accumulation, const IgnoreScrollFnc _IgnoreScroll);
			void ScrollWithMouseV(const intptr_t _Delta, intptr_t& _Accumulation, const IgnoreScrollFnc _IgnoreScroll);
			void ResizeWithMouse(const uint64_t _ResizePopUpId, PopUp& _Parent, const intptr_t _MouseDeltaX, const intptr_t _MouseDeltaY, intptr_t& _AccumulationX, intptr_t& _AccumulationY, const ResizePopUpLayerFnc _ResizePopUpLayer, const GetMinFnc _GetMinX, const GetMinFnc _GetMinY, const size_t _ResizeSize, const ForceScrollFnc _ForceHScroll, const ForceScrollFnc _ForceVScroll, const size_t _ScrollSize, const size_t _ScrollTopPadding, const size_t _ScrollPadding, const GetRenderingDescriptorFnc _GetRenderingDescriptor, const GetHitBoxFnc _GetHitBox, const GenerateUserDataFnc _GenerateUserData, const ReleaseUserDataFnc _ReleaseUserData, void* _Global);
			void MoveLayerWithMouse(const size_t _Layer, const intptr_t _MouseDeltaX, const intptr_t _MouseDeltaY);
			void GenerateResizeBars(const bool _IsNode, const size_t _ResizeSize, const GetRenderingDescriptorFnc _GetRenderingDescriptor, const GetHitBoxFnc _GetHitBox, const GenerateUserDataFnc _GenerateUserData, void* _Global);
			void GenerateScrollBars(const bool _HasHScroll, const bool _HasVScroll, const bool _ForceHScroll, const bool _ForceVScroll, const size_t _ScrollSize, const size_t _ScrollTopPadding, const size_t _ScrollPadding, const GetRenderingDescriptorFnc _GetRenderingDescriptor, const GetHitBoxFnc _GetHitBox, const GenerateUserDataFnc _GenerateUserData, void* _Global);
			void ResizeChilds(const ResizePopUpLayerFnc _ResizePopUpLayer, const GetMinFnc _GetMinX, const GetMinFnc _GetMinY, const size_t _ResizeSize, const ForceScrollFnc _ForceHScroll, const ForceScrollFnc _ForceVScroll, const size_t _ScrollSize, const size_t _ScrollTopPadding, const size_t _ScrollPadding, const GetRenderingDescriptorFnc _GetRenderingDescriptor, const GetHitBoxFnc _GetHitBox, const GenerateUserDataFnc _GenerateUserData, const ReleaseUserDataFnc _ReleaseUserData, void* _Global);
			void SetForegroundLayer(const size_t _Layer);
			void MoveControlsOnTop();
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
			void SetRenderFunctions(const RenderingDescriptor& _RenderFunctions);
			void SetSetupData(const SetupRenderDataFnc _SetupData);
			void SetCleanUpData(const CleanUpRenderDataFnc _CleanUpData);
			void SetRenderBottom(const RenderFnc _RenderBottom);
			void SetRenderMiddle(const RenderFnc _RenderMiddle);
			void SetRenderTop(const RenderFnc _RenderTop);
			void SetComposit(const CompositFnc _Composit);
			void SetHitBox(const HitBoxFnc _HitBox);

			SafePopUpPointer GetChildFromMouse(const intptr_t _MouseX, const intptr_t _MouseY, Vector<SafePopUpPointer>* _Path = nullptr);
			const SafePopUpPointer GetChildFromMouse(const intptr_t _MouseX, const intptr_t _MouseY, Vector<const SafePopUpPointer>* _Path = nullptr) const;
			const bool FindFocusedPopUpLayer(size_t& _Layer, const PopUp& _PopUp) const;
			const bool FindFocusedPopUpLayer(size_t& _Layer, const uint64_t _PopUpId) const;
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
			const RenderingDescriptor& GetRenderFunctions();
			const SetupRenderDataFnc GetSetupData() const;
			const CleanUpRenderDataFnc GetCleanUpData() const;
			const RenderFnc GetRenderBottom() const;
			const RenderFnc GetRenderMiddle() const;
			const RenderFnc GetRenderTop() const;
			const CompositFnc GetComposit() const;
			const HitBoxFnc GetHitBox() const;

			PopUp& operator= (const PopUp& _Other);
			PopUp& operator= (PopUp&& _Other) noexcept;

			static void GlobalToLocal(intptr_t& _PositionX, intptr_t& _PositionY, const Vector<SafePopUpPointer>& _Path);
			static void GlobalToLocal(intptr_t& _PositionX, intptr_t& _PositionY, const Vector<const SafePopUpPointer>& _Path);
			static void LocalToGlobal(intptr_t& _PositionX, intptr_t& _PositionY, const Vector<SafePopUpPointer>& _Path);
			static void LocalToGlobal(intptr_t& _PositionX, intptr_t& _PositionY, const Vector<const SafePopUpPointer>& _Path);
			static const bool IsValidPath(const Vector<SafePopUpPointer>& _Path);
			static const bool IsValidPath(const Vector<const SafePopUpPointer>& _Path);
			static const bool FindMovableWindow(const IsMovableFnc _IsMovable, size_t& _Index, const Vector<SafePopUpPointer>& _Path);
			static const bool FindMovableWindow(const IsMovableFnc _IsMovable, size_t& _Index, const Vector<const SafePopUpPointer>& _Path);
			static const bool FindScrollableWindow(const IsScrollableFnc _IsScrollable, size_t& _Index, const Vector<SafePopUpPointer>& _Path);
			static const bool FindScrollableWindow(const IsScrollableFnc _IsScrollable, size_t& _Index, const Vector<const SafePopUpPointer>& _Path);

		private:

			friend SafePopUpPointer;

			size_t FocusedPanel;
			Vector<PopUp> Panels;
			size_t FocusedNode;
			Vector<PopUp> Nodes;
			Vector<size_t> FocusedPopUps;
			Vector<Vector<PopUp>> PopUps;

			mutable Vector<SafePopUpPointer*> SafePointers;

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
			RenderingDescriptor RenderFunctions;
			HitBoxFnc HitBox;

		};

	}

}



#endif
