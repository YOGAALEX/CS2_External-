#pragma once
#include "Game.h"
#include "Bone.h"

namespace MenuConfig
{
	inline std::string path = "";

	inline bool ShowBoneESP = false;
	inline bool ShowBoxESP = false;
	inline bool ShowHealthBar = false;
	inline bool ShowWeaponESP = false;
	inline bool ShowDistance = false;
	inline bool ShowEyeRay = false;
	inline bool ShowPlayerName = false;

	inline bool AimBot = false;
	inline int AimBotHotKey = 18;
	// 0: head 1: neck 3: spine
	inline int  AimPosition = 1;
	inline bool ShowAimFovRange = false;
	inline ImColor AimFovRangeColor = ImColor(51, 255, 51, 255);
	inline DWORD  AimPositionIndex = BONEINDEX::head;
	inline bool VisibleCheck = false;// 移除可视检查
	// 0: normal 1: dynamic
	inline int  BoxType = 0;
	// 0: Vertical 1: Horizontal
	inline int  HealthBarType = 0;

	inline ImColor BoneColor = ImColor(255, 0, 0, 255); 
	inline ImColor BoxColor = ImColor(0, 255, 255, 255);
	inline ImColor EyeRayColor = ImColor(255, 255, 0, 255);
	inline float  BoxThickness = 1;
	inline float BoneThickness = 1;

	inline ImColor WeaponColor = ImColor(255, 255, 0, 255);
	inline ImColor NameColor = ImColor(255, 255, 0, 255);
	inline ImColor DistanceColor = ImColor(255, 255, 0, 255);
	inline bool ShowMenu = true;

	inline bool ShowRadar = false;
	inline float RadarRange = 150;
	inline float RadarPointSizeProportion = 1.f;
	inline bool ShowRadarCrossLine = true;
	inline ImColor RadarCrossLineColor = ImColor(220, 220, 220, 255);
	// 0: circle 1: arrow 2: circle with arrow
	inline int RadarType = 1;
	inline float Proportion = 2230;

	inline bool TriggerBot = false;
	inline int TriggerHotKey = 20;
	inline int TriggerMode = 0;
	inline bool Pressed = false;// for toggle mode
	inline bool Shoot = false;// so that it doesn抰 aim when the trigger hits

	inline bool TeamCheck = true;
	inline bool OBSBypass = true;

	inline bool BunnyHop = false;
	
	inline bool ShowHeadShootLine = false;
	inline ImColor HeadShootLineColor = ImColor(255, 255, 255, 255);

	inline bool ShowFovLine = false;
	inline ImColor FovLineColor = ImColor(55, 55, 55, 220);
	inline float FovLineSize = 60.f;

	inline bool ShowLineToEnemy = false;
	inline ImColor LineToEnemyColor = ImColor(0, 255, 255, 220);

	inline bool ShowCrossHair = true;
	inline ImColor CrossHairColor = ImColor(255, 255, 0, 255);
	inline float CrossHairSize = 20;

	inline bool ShowWhenSpec = true;

	inline bool AntiFlashbang = false;
	inline bool bmbTimer = true;
	inline ImColor BombTimerCol = ImColor(255, 120, 0, 255);

	inline bool RCS = false;
	inline float RCSBullet = 1;
	inline bool MenuLogo = false;
	inline int MenuKery = 36;

	inline int	HitSound = 0;
	inline bool HitMarker = false;
	inline bool EnemySensor = true;
	inline float GlowColor1[4] = { 1.0f, 0.0f, 1.0f, 1.0f }; // 紫色
	inline float GlowColor2[4] = { 0.0f, 1.0f, 1.0f, 1.0f }; 
	inline bool FastStop = false;
	//inline bool RadarHack = false;
	
}