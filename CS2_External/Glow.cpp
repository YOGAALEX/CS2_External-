//#include "Glow.h"
//#include <thread>
//
//DWORD ConvertToABGR(const float color[4])
//{
//	// ��ɫֵ�� 0.0f - 1.0f ת��Ϊ 0 - 255
//	BYTE alpha = static_cast<BYTE>(color[3] * 255); // Alpha
//	BYTE blue = static_cast<BYTE>(color[2] * 255); // Blue
//	BYTE green = static_cast<BYTE>(color[1] * 255); // Green
//	BYTE red = static_cast<BYTE>(color[0] * 255); // Red
//
//	// ABGR ��ʽ��Alpha | Blue | Green | Red
//	return (alpha << 24) | (blue << 16) | (green << 8) | red;
//}
//
//void Glow::Run(const CEntity& Entity)
//{
//    int on = 1;
//    int off = 0;
//
//    // �� RGBA ת��Ϊ ABGR ��ʽ�� DWORD ��ɫ
//    DWORD color1 = ConvertToABGR(MenuConfig::GlowColor1);
//    DWORD color2 = ConvertToABGR(MenuConfig::GlowColor2);
//    // ʹ�� ImGui ����ɫ�༭�����޸� GlowColor
// 
//
//    if (!MenuConfig::EnemySensor)
//    {
//        ProcessMgr.WriteMemory(Entity.Pawn.Address + Offset::Entity.GlowFunction, off);
//    }
//    else {
//        if (Entity.Controller.TeamID == 2) //����
//        {
//            ProcessMgr.WriteMemory(Entity.Pawn.Address + Offset::Entity.GlowFunction, on);
//            ProcessMgr.WriteMemory(Entity.Pawn.Address + Offset::Entity.GlowColorOverride, color1);
//        }
//        if (Entity.Controller.TeamID == 3) //����
//        {
//            ProcessMgr.WriteMemory(Entity.Pawn.Address + Offset::Entity.GlowFunction, on);
//            ProcessMgr.WriteMemory(Entity.Pawn.Address + Offset::Entity.GlowColorOverride, color2);
//        }
//    }
//}