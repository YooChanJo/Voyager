#pragma once
#include "Log.h"
#include "Application.h"

// extern Voyager::Application* Voyager::CreateApplication(Voyager::ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{
	/* Initialize log */
	Voyager::Log::Init();
	VG_CORE_INFO("Initiating log...");

	/* Creation of the App */
	auto app = Voyager::CreateApplication({ argc, argv });

	/* Running of the App */
	app->Run();

	/* Memory cleanup */
	delete app;
	VG_CORE_INFO("Successful termination of program");
}
