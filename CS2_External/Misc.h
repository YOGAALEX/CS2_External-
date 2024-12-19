#pragma once
#define _USE_MATH_DEFINES

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <sstream>
#include <string>
#include <thread>
#include <time.h>
#include <vector>
#include <Windows.h>


#include "Sounds.h"
#include "Entity.h"
#include "MenuConfig.hpp"
#include "OS-ImGui\imgui\imgui.h"


#pragma comment(lib, "winmm.lib")

namespace Misc
{
	inline bool Zoom = false;

	static inline std::vector<ImColor> colorList = {
		ImColor(255, 0, 0),     // Red
		ImColor(255, 165, 0),   // Orange
		ImColor(255, 255, 0),   // Yellow
		ImColor(0, 128, 0),     // Green
		ImColor(0, 0, 255),     // Purple
	};

	inline std::vector<std::string> Nades = { "smokegrenade", "flashbang", "hegrenade", "molotov", "decoy", "incgrenade" };

	struct Vector3
	{
		float x, y, z;
		Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
	};

	struct Hitmarker {
		float alpha;
		std::chrono::steady_clock::time_point startTime;
	};

	static inline void StopKeyEvent(int WalkKey, bool* KeyStatus, int StopKey, float duration) {
		if (GetAsyncKeyState(WalkKey) & 0x8000) {
			*KeyStatus = true;
		}
		else {
			if (*KeyStatus) {
				keybd_event(StopKey, MapVirtualKey(StopKey, 0), KEYEVENTF_SCANCODE, 0);
				Sleep(50);
				keybd_event(StopKey, MapVirtualKey(StopKey, 0), KEYEVENTF_KEYUP, 0);
				*KeyStatus = false;
			}
		}
	}

	
	void HitMarker(float Size, float Gap);

	void HitManager(const CEntity& aLocalPlayer, int& PreviousTotalHits) noexcept;
	//void RadarHack(const CEntity& EntityList) noexcept;
	void FastStop() noexcept;
}