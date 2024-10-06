#include "PrismFX/prismfx.h"
#include "PrismFX/core/entry_point.h"

// std
#include <iostream>



class SceneTest : public PFX::Scene
{
	public:
		SceneTest() = default;
		~SceneTest() = default;

		void OnAttach() override 
		{

		}

		void OnDetach() override
		{

		}

		void OnUpdate() override
		{
			if (PFX::Input::IsKeyPressed(PFX::Key::W))
			{
				std::cout << "W is pressed!\n";
			}

			if (PFX::Input::IsMouseButtonPressed(PFX::Mouse::BLeft))
			{
				std::cout << "BLeft is pressed!\n";
			}

			std::cout << "X: " << PFX::Input::GetMouseX() << " Y: " << PFX::Input::GetMouseY() << "\n";
		}

		void OnEvent(PFX::Event& p_event) override
		{

		}
};


class Sandbox : public PFX::Application
{
	public:
		Sandbox()
		{
			PFX::WindowCreateInfo wci{};
			wci.Title = "SandboxApp";
			wci.Width = 640;
			wci.Height = 480;
			wci.Mode = PFX::WindowMode::BORDERLESS;
			PFX::Window* window = PFX::Window::Create(wci);

			SetWindow(window);

			PFX::SceneManager::LoadScene(new SceneTest());
		}

		~Sandbox() = default;
};


PFX::Application* PFX::CreateApplication()
{
	return new Sandbox();
}