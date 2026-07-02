#ifndef BFW_WINDOWS_RunTime_hpp

#define BFW_WINDOWS_RunTime_hpp



#include "BFW_WINDOWS.hpp"



namespace BFW_WINDOWS
{

	namespace RunTime
	{

		class Application : public BFW::RunTime::Application
		{

		public:

			Application();
			Application(const Application& _Other) = delete;
			Application(Application&& _Other) noexcept = delete;
			~Application();

			const bool AddChildWindow();
			void RemoveChildWindow(const size_t _Index);

			BFW::Input::Controller& GetController(const size_t _Index);
			const BFW::Input::Controller& GetController(const size_t _Index) const;

			BFW::GUI::Window& GetMainWindow();
			const BFW::GUI::Window& GetMainWindow() const;
			GUI::WindowData& GetMainWindowData();
			const GUI::WindowData& GetMainWindowData() const;
			BFW::Vector<BFW::GUI::Window*>& GetChildWindows();
			const BFW::Vector<BFW::GUI::Window*>& GetChildWindows() const;
			BFW::Vector<GUI::WindowData*>& GetChildWindowsData();
			const BFW::Vector<GUI::WindowData*>& GetChildWindowsData() const;

			Application& operator= (const Application& _Other) = delete;
			Application& operator= (Application&& _Other) noexcept = delete;

		private:

			void Setup() override;
			void Update() override;
			void Stop() override;

			const bool InitInstance();

			const bool InitWindows();
			void CleanUpWindows();

			BFW::Input::Controller Controllers[4];

			BFW::GUI::Window MainWindow;
			GUI::WindowData MainWindowData;
			BFW::Vector<BFW::GUI::Window*> ChildWindows;
			BFW::Vector<GUI::WindowData*> ChildWindowsData;

		};

		enum Menus : const uint64_t
		{
			_MainMenu = 1
		};

		class MainMenu : public BFW::RunTime::Menu
		{

		public:

			MainMenu();
			MainMenu(const MainMenu& _Other) = delete;
			MainMenu(MainMenu&& _Other) noexcept;
			~MainMenu();

			const uint64_t GetType() const override;

			MainMenu& operator= (const MainMenu& _Other) = delete;
			MainMenu& operator= (MainMenu&& _Other) noexcept;

		private:

			void SpawnQueuedMenu(const uint64_t _QueuedMenu) override;
			void Setup() override;
			void Update() override;
			void Stop() override;

			void GenerateDebugWindow(BFW::GUI::PopUp& _Parent, const bool _IsNode);

			void InitGUI();
			void CleanUpGUI();

			const bool SpawnButtonCallBack();
			void MouseCaptureResize(BFW::GUI::Window& _Wnd, GUI::WindowData& _WndData, const uint64_t _ResizePopUpId, const intptr_t _MouseDeltaX, const intptr_t _MouseDeltaY);
			void MouseCaptureMove(BFW::GUI::Window& _Wnd, GUI::WindowData& _WndData, const intptr_t _MouseDeltaX, const intptr_t _MouseDeltaY);

			void MouseCaptureInputs(BFW::GUI::Window& _Wnd, GUI::WindowData& _WndData);
			void DeleteMouseCaptureInputs(BFW::GUI::Window& _Wnd, GUI::WindowData& _WndData);
			void HandleWindowInputs(BFW::GUI::Window& _Wnd, GUI::WindowData& _WndData, const bool _IsMainWindow);
			void RenderWindow(BFW::GUI::Window& _Wnd, GUI::WindowData& _WndData);

			void Input();
			void DeleteInputs();
			void Engine();
			void FrameBuild();

		};

	}

}



#endif
