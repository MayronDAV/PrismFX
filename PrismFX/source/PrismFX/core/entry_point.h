#pragma once

/*
	Must be included ONLY in the application file or it will crash
*/

#include "PrismFX/core/application.h"

extern PFX::Application* PFX::CreateApplication();

int main(int argc, char** argv)
{
	auto app = PFX::CreateApplication();
	app->Run();
	delete app;
}