#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "Game.h"
#include "Entity.h"
#include <iostream>


namespace AimControl
{
	inline int HotKey = VK_LBUTTON;
	inline float AimFov =15;
	inline float Smooth = 0.1;
	inline Vec2 RCSScale = { 1.f,1.f };
	inline int RCSBullet = 1;
   
	inline std::vector<int> HotKeyList{VK_LBUTTON, VK_LMENU, VK_RBUTTON, VK_XBUTTON1, VK_XBUTTON2, VK_CAPITAL, VK_LSHIFT, VK_LCONTROL};// added new button VK_LBUTTON
	
	inline void SetHotKey(int Index)
	{
		HotKey = HotKeyList.at(Index);
	}

    inline void AimBot(const CEntity& Local, Vec3 LocalPos, Vec3 AimPos)
    {
        float Yaw, Pitch;
        float Distance, Norm;
        Vec3 OppPos;

        OppPos = AimPos - LocalPos;

        Distance = sqrt(pow(OppPos.x, 2) + pow(OppPos.y, 2));

        Yaw = atan2f(OppPos.y, OppPos.x) * 57.295779513 - Local.Pawn.ViewAngle.y;
        Pitch = -atan2f(OppPos.z, Distance) * 57.295779513 - Local.Pawn.ViewAngle.x;

        // Normalize Yaw and Pitch to be within [-180, 180] or [0, 360]
      /*  Yaw = fmod(Yaw + 360.0f, 360.0f);
        if (Yaw > 180.0f) Yaw -= 360.0f;

        Pitch = fmod(Pitch + 360.0f, 360.0f);  //注释掉效果最好
        if (Pitch > 180.0f) Pitch -= 360.0f;*/

        Norm = sqrt(pow(Yaw, 2) + pow(Pitch, 2));


        if (Norm > AimFov)
            return;
       
     

        Yaw = Yaw * (1 - Smooth) + Local.Pawn.ViewAngle.y;
        Pitch = Pitch * (1 - Smooth) + Local.Pawn.ViewAngle.x;

        // 设置视角，无需RCS
        gGame.SetViewAngle(Yaw, Pitch);
    }
}
