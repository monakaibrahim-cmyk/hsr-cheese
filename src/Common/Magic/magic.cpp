#include "pch.h"
#include "magic.h"

/* Adventure */
#include "Functions/dumb_enemies.h"
#include "Functions/noclip.h"
#include "Functions/peeking.h"

/* Battle */
#include "Functions/battle_speed_changer.h"
#include "Functions/crit_indicator.h"

/* Visuals */
#include "Functions/fov_changer.h"
#include "Functions/fps_indicator.h"
#include "Functions/free_camera.h"
#include "Functions/hide_ui.h"

/* Misc */
#include "Functions/config.h"
#include "Functions/fps_unlocker.h"
#include "Functions/global_speed_changer.h"
#include "Menu/menu_settings.h"

namespace Cheat
{
	static HOOK LoadLibraryExWHook = {};

	static HMODULE LoadLibraryExWDetour(LPCWSTR lpLibFileName, HANDLE hFile, DWORD dwFlags)
	{
		HMODULE hModule = CALL_ORIGINAL(LoadLibraryExWHook, LoadLibraryExWDetour, lpLibFileName, hFile, dwFlags);

		if (!hIl2Cpp)
		{
			if (hModule && hModule == GetModuleHandleW(L"telemetry.dll"))
			{
				hIl2Cpp = GetModuleHandleW(L"GameAssembly.dll");

				/* Adventure */
				DumbEnemies::Setup();
				Noclip::Setup();
				Peeking::Setup();

				/* Battle */
				BattleSpeedChanger::Setup();
				CritIndicator::Setup();

				/* Visuals */
				FovChanger::Setup();
				FpsIndicator::Setup();
				FreeCamera::Setup();
				HideUi::Setup();

				/* Misc */
				Config::Setup();
				FpsUnlocker::Setup();
				GlobalSpeedChanger::Setup();
				MenuSettings::Setup();
			}
		}

		return hModule;
	}

	void MenuAdventure()
	{
		DumbEnemies::Menu();
		Noclip::Menu();
		Peeking::Menu();
	}

	void MenuBattle()
	{
		BattleSpeedChanger::Menu();
		CritIndicator::Menu();
	}

	void MenuVisuals()
	{
		FovChanger::Menu();
		FpsIndicator::Menu();
		FreeCamera::Menu();
		HideUi::Menu();
	}

	void MenuMisc()
	{
		Config::Menu();
		FpsUnlocker::Menu();
		GlobalSpeedChanger::Menu();
		MenuSettings::Menu();
	}

	void BeforeFrame()
	{
		/* Adventure */
		DumbEnemies::BeforeFrame();
		Noclip::BeforeFrame();
		Peeking::BeforeFrame();

		/* Battle */
		BattleSpeedChanger::BeforeFrame();
		CritIndicator::BeforeFrame();

		/* Visuals */
		FovChanger::BeforeFrame();
		FpsIndicator::BeforeFrame();
		FreeCamera::BeforeFrame();
		HideUi::BeforeFrame();

		/* Misc */
		Config::BeforeFrame();
		FpsUnlocker::BeforeFrame();
		GlobalSpeedChanger::BeforeFrame();
		MenuSettings::BeforeFrame();
	}

	void OnFrame()
	{
		/* Adventure */
		DumbEnemies::OnFrame();
		Noclip::OnFrame();
		Peeking::OnFrame();

		/* Battle */
		BattleSpeedChanger::OnFrame();
		CritIndicator::OnFrame();

		/* Visuals */
		FovChanger::OnFrame();
		FpsIndicator::OnFrame();
		FreeCamera::OnFrame();
		HideUi::OnFrame();

		/* Misc */
		Config::OnFrame();
		FpsUnlocker::OnFrame();
		GlobalSpeedChanger::OnFrame();
		MenuSettings::OnFrame();
	}

	bool Setup()
	{
		HMODULE hKernelBase = GetModuleHandleW(L"kernelbase.dll");

		if (!hKernelBase)
		{
			return FALSE;
		}

		if (!IsHookActive(&LoadLibraryExWHook) && !CreateHook(&LoadLibraryExWHook, GetProcAddress(hKernelBase, "LoadLibraryExW"), LoadLibraryExWDetour, TRUE))
		{
			return FALSE;
		}

		return TRUE;
	}
}
