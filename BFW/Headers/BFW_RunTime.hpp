#ifndef BFW_RunTime_hpp

#define BFW_RunTime_hpp



#include "BFW.hpp"



namespace BFW
{

	namespace RunTime
	{

		class BFW_API Application
		{

		public:

			Application();
			Application(const Application& _Other) = delete;
			Application(Application&& _Other) noexcept = delete;
			virtual ~Application();

#ifdef BFW_WINDOWS_PLATFORM

			const int32_t Run(const HINSTANCE _InstanceHandle, const BFW_CHAR_TYPE* _CmdLine, const int32_t _ShowCmd, const BFW_CHAR_TYPE* _SharedInstanceMemoryName, const BFW_CHAR_TYPE* _SharedInstanceMutexName);

#endif

#ifdef BFW_LINUX_PLATFORM

			const int32_t Run(const size_t _ArgC, const BFW_CHAR_TYPE** _ArgV, const BFW_CHAR_TYPE* _SharedInstanceMemoryName, const BFW_CHAR_TYPE* _SharedInstanceMutexName);

#endif

#ifdef BFW_ESP32_PLATFORM

			const int32_t Run();

#endif

			void TurnOn();
			void Close(const int32_t _ReturnValue);

			void SetCurrentMenu(const uint64_t _CurrentMenu);

			void UpdateCurrentFrameTime();
			void SetLagTime(const float _LagTime);
			void SetSimulationSpeed(const float _SimulationSpeed);
			void SetSync(const uint64_t _Sync);

			void UpdateWorkingDirectory();

			const bool CheckOn() const;
			const int32_t GetReturnValue() const;

			const uint64_t GetCurrentMenu() const;

			Time::Timer& GetFrameTime(const size_t _Index);
			const Time::Timer& GetFrameTime(const size_t _Index) const;
			const float GetTimeStep() const;
			const float GetUITimeStep() const;
			const float GetLagTime() const;
			const float GetSimulationSpeed() const;
			const uint64_t GetSync() const;

			const FileSystem::Directory& GetWorkingDirectory() const;
			const FileSystem::DirectoryDiff& GetWorkingDirectoryDiff() const;

#ifdef BFW_WINDOWS_PLATFORM

			const Trie<Trie<FileSystem::FileContent>>& GetResources() const;

#endif

#if defined BFW_WINDOWS_PLATFORM || defined BFW_LINUX_PLATFORM

			MultiProcessing::SharedMemory& GetSharedInstanceMemory();
			const MultiProcessing::SharedMemory& GetSharedInstanceMemory() const;
			MultiProcessing::SharedMutex& GetSharedInstanceMutex();
			const MultiProcessing::SharedMutex& GetSharedInstanceMutex() const;
			const size_t GetArgC() const;
			const BFW_CHAR_TYPE* GetArgV(const size_t _Index) const;

#endif

#ifdef BFW_WINDOWS_PLATFORM

			const HINSTANCE GetInstanceHandle() const;
			const BFW_CHAR_TYPE* GetCmdLine() const;
			const int32_t GetShowCmd() const;

#endif

			Application& operator= (const Application& _Other) = delete;
			Application& operator= (Application&& _Other) noexcept = delete;

		protected:

			virtual void Setup() = 0;
			virtual void Update() = 0;
			virtual void Stop() = 0;

		private:

			bool On;
			int32_t ReturnValue;

			uint64_t CurrentMenu;

			Time::Timer FrameTime[2];
			float LagTime;
			float SimulationSpeed;
			uint64_t Sync;

			FileSystem::Directory WorkingDirectory;
			FileSystem::DirectoryDiff WorkingDirectoryDiff;

#ifdef BFW_WINDOWS_PLATFORM

			Trie<Trie<FileSystem::FileContent>> Resources;

#endif

#if defined BFW_WINDOWS_PLATFORM || defined BFW_LINUX_PLATFORM

			MultiProcessing::SharedMemory SharedInstanceMemory;
			MultiProcessing::SharedMutex SharedInstanceMutex;

#endif

#ifdef BFW_WINDOWS_PLATFORM

			HINSTANCE InstanceHandle;
			const BFW_CHAR_TYPE* CmdLine;
			int32_t ShowCmd;

#endif

#ifdef BFW_LINUX_PLATFORM

			size_t ArgC;
			const BFW_CHAR_TYPE** ArgV;

#endif

		};

		enum BFW_API Menus : const uint64_t
		{
			_NullMenu = 0
		};

		class BFW_API Menu
		{

		public:

			Menu();
			Menu(const Menu& _Other) = delete;
			Menu(Menu&& _Other) noexcept = delete;
			virtual ~Menu();

			const uint64_t Run(Application* _ApplicationObj, Menu* _ParentMenu = nullptr);

			virtual const uint64_t GetType() const = 0;

			Menu& operator= (const Menu& _Other) = delete;
			Menu& operator= (Menu&& _Other) noexcept = delete;

			void TurnOn();
			void Close(const uint64_t _NextMenu);
			void QueueMenu(const uint64_t _QueuedMenu);

			void UpdateCurrentFrameTime();
			void SetLagTime(const float _LagTime);
			void SetSimulationSpeed(const float _SimulationSpeed);
			void SetSync(const uint64_t _Sync);

			void UpdateWorkingDirectory();

			const bool CheckOn() const;
			const uint64_t GetNextMenu() const;
			const uint64_t GetQueuedMenu() const;

			Application* GetApplicationObj();
			const Application* GetApplicationObj() const;
			Menu* GetParentMenu();
			const Menu* GetParentMenu() const;

			Time::Timer& GetFrameTime(const size_t _Index);
			const Time::Timer& GetFrameTime(const size_t _Index) const;
			const float GetTimeStep() const;
			const float GetUITimeStep() const;
			const float GetLagTime() const;
			const float GetSimulationSpeed() const;
			const uint64_t GetSync() const;

			const FileSystem::Directory& GetWorkingDirectory() const;
			const FileSystem::DirectoryDiff& GetWorkingDirectoryDiff() const;

#ifdef BFW_WINDOWS_PLATFORM

			const Trie<Trie<FileSystem::FileContent>>& GetResources() const;

#endif

		protected:

			virtual void SpawnQueuedMenu(const uint64_t _QueuedMenu) = 0;
			virtual void Setup() = 0;
			virtual void Update() = 0;
			virtual void Stop() = 0;

		private:

			bool On;
			uint64_t NextMenu;
			uint64_t QueuedMenu;

			Application* ApplicationObj;
			Menu* ParentMenu;

		};

	}

}



#endif
