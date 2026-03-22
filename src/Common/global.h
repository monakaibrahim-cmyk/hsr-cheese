#pragma once
#include <windows.h>

struct OPTIONS
{
	unsigned char MenuKey = VK_INSERT;
	bool MenuCustomScale = FALSE;
	float MenuCustomScaleValue = 2.0f;

	bool FpsIndicator = TRUE;

	bool FovChanger = FALSE;
	unsigned char FovChangerKey = 0;
	bool FovChangerKeyHeld = FALSE;
	float FovChangerValue = 90.0f;

	bool HideUi = FALSE;
	unsigned char HideUiKey = 0;
	bool HideUiKeyHeld = FALSE;

	bool FpsUnlocker = FALSE;
	int FpsUnlockerValue = 120;

	bool DumbEnemies = FALSE;
	unsigned char DumbEnemiesKey = 0;
	bool DumbEnemiesKeyHeld = FALSE;

	bool GlobalSpeedChanger = FALSE;
	unsigned char GlobalSpeedChangerKey = 0;
	bool GlobalSpeedChangerKeyHeld = FALSE;
	float GlobalSpeedChangerValue = 2.0f;

	bool Noclip = FALSE;
	unsigned char NoclipKey = 0;
	bool NoclipKeyHeld = FALSE;
	float NoclipSpeed = 15.0f;
	bool NoclipUseCameraDirection = FALSE;

	bool FreeCamera = FALSE;
	unsigned char FreeCameraKey = 0;
	bool FreeCameraKeyHeld = FALSE;
	float FreeCameraSpeed = 15.0f;
	float FreeCameraMouseSensitivity = 1.0f;
	unsigned char FreeCameraForwardKey = 'W';
	unsigned char FreeCameraBackwardKey = 'S';
	unsigned char FreeCameraLeftKey = 'A';
	unsigned char FreeCameraRightKey = 'D';
	unsigned char FreeCameraUpKey = VK_SPACE;
	unsigned char FreeCameraDownKey = VK_CONTROL;
	unsigned char FreeCameraBoostKey = VK_SHIFT;

	bool Peeking = FALSE;

	bool CritIndicator = FALSE;

	bool BattleSpeedChanger = FALSE;
	unsigned char BattleSpeedChangerKey = 0;
	bool BattleSpeedChangerKeyHeld = FALSE;
	float BattleSpeedChangerValue = 5.0f;
};

extern OPTIONS Options;
