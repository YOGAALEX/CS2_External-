//#include "Glow.h"
//#include <thread>
//
//DWORD ConvertToABGR(const float color[4])
//{
//	// 颜色值从 0.0f - 1.0f 转换为 0 - 255
//	BYTE alpha = static_cast<BYTE>(color[3] * 255); // Alpha
//	BYTE blue = static_cast<BYTE>(color[2] * 255); // Blue
//	BYTE green = static_cast<BYTE>(color[1] * 255); // Green
//	BYTE red = static_cast<BYTE>(color[0] * 255); // Red
//
//	// ABGR 格式：Alpha | Blue | Green | Red
//	return (alpha << 24) | (blue << 16) | (green << 8) | red;
//}
//
//void Glow::Run(const CEntity& Entity)
//{
//    int on = 1;
//    int off = 0;
//
//    // 将 RGBA 转化为 ABGR 格式的 DWORD 颜色
//    DWORD color1 = ConvertToABGR(MenuConfig::GlowColor1);
//    DWORD color2 = ConvertToABGR(MenuConfig::GlowColor2);
//    // 使用 ImGui 的颜色编辑器来修改 GlowColor
// 
//
//    if (!MenuConfig::EnemySensor)
//    {
//        ProcessMgr.WriteMemory(Entity.Pawn.Address + Offset::Entity.GlowFunction, off);
//    }
//    else {
//        if (Entity.Controller.TeamID == 2) //土匪
//        {
//            ProcessMgr.WriteMemory(Entity.Pawn.Address + Offset::Entity.GlowFunction, on);
//            ProcessMgr.WriteMemory(Entity.Pawn.Address + Offset::Entity.GlowColorOverride, color1);
//        }
//        if (Entity.Controller.TeamID == 3) //警察
//        {
//            ProcessMgr.WriteMemory(Entity.Pawn.Address + Offset::Entity.GlowFunction, on);
//            ProcessMgr.WriteMemory(Entity.Pawn.Address + Offset::Entity.GlowColorOverride, color2);
//        }
//    }
//}