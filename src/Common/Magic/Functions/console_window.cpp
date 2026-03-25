#include "pch.h"
#include "console_window.h"

namespace Console
{
	void Menu()
	{
		ImGui::BeginGroupPanel("Console");

		ImGui::Checkbox("Enable", &Options.ConsoleEnable);

		ImGui::EndGroupPanel();
	}

	void BeforeFrame()
	{
	}

	void OnFrame()
	{
	}

	bool Setup()
	{
        if (Options.ConsoleEnable)
		{
			AllocConsole();
			freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
			freopen_s((FILE**)stderr, "CONOUT$", "w", stderr);
		}

		return TRUE;
	}
}
