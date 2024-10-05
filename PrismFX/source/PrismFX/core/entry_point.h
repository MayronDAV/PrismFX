#pragma once

/*
	Must be included ONLY in the application file or it will crash
*/

#include "PrismFX/core/application.h"
#include "PrismFX/core/log.h"

extern PFX::Application* PFX::CreateApplication();

int main(int argc, char** argv)
{
	PFX::Log::Init();

	auto app = PFX::CreateApplication();
	app->Init();
	app->Run();
	delete app;
}