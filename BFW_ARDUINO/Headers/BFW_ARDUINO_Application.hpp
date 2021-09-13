#ifndef BFW_ARDUINO_Application_hpp

#define BFW_ARDUINO_Application_hpp



#include "BFW_ARDUINO.hpp"



namespace BFW_ARDUINO
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
