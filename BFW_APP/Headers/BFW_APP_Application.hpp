#ifndef BFW_APP_Application_hpp

#define BFW_APP_Application_hpp



#include "..\Headers\BFW_APP.hpp"



namespace BFW_APP
{

	class Application : public BFW::Application
	{

	public:

		Application();
		Application(const Application& _Other) = delete;
		Application(Application&& _Other) noexcept = delete;
		~Application();

		void Setup() override;
		void Update() override;
		void Stop() override;

		void operator= (const Application& _Other) = delete;
		void operator= (Application&& _Other) noexcept = delete;

	private:



	};

}



#endif
