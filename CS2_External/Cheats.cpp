#include "Cheats.h"
#include "Render.hpp"
#include "MenuConfig.hpp"
#include "Utils/ConfigMenu.hpp"
#include "Utils/ConfigSaver.hpp"
#include "OS-ImGui/OS-ImGui_Base.h"
#include "OS-ImGui/imgui/color.h"
#include"BombTimer.h"
#include"Rcs.h"

#include <iomanip> 

int tabs = 6;
int sub_tabs = 0;
static float tab_alpha = 0.f;
static float tab_add;
static int active_tab = 0;
static bool animated_background = true;
int PreviousTotalHits = 0;
void Particles()
{
	ImVec2 screen_size = { (float)GetSystemMetrics(SM_CXSCREEN), (float)GetSystemMetrics(SM_CYSCREEN) };

	static ImVec2 partile_pos[100];
	static ImVec2 partile_target_pos[100];
	static float partile_speed[100];
	static float partile_radius[100];

	for (int i = 1; i < 50; i++)
	{
		if (partile_pos[i].x == 0 || partile_pos[i].y == 0)
		{
			partile_pos[i].x = rand() % (int)screen_size.x + 1;
			partile_pos[i].y = 15.f;
			partile_speed[i] = 1 + rand() % 25;
			partile_radius[i] = rand() % 4;

			partile_target_pos[i].x = rand() % (int)screen_size.x;
			partile_target_pos[i].y = screen_size.y * 2;
		}

		partile_pos[i] = ImLerp(partile_pos[i], partile_target_pos[i], ImGui::GetIO().DeltaTime * (partile_speed[i] / 60));

		if (partile_pos[i].y > screen_size.y)
		{
			partile_pos[i].x = 0;
			partile_pos[i].y = 0;
		}

		ImGui::GetWindowDrawList()->AddCircleFilled(partile_pos[i], partile_radius[i], ImColor(255, 255, 255, 255));
	}

}


void HelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

void Cheats::shuiyin()
{
	// 设置中文本地化
	std::locale::global(std::locale("zh_CN.utf8"));

	// 获取当前时间
	auto end = std::chrono::system_clock::now();
	auto end_time = std::chrono::system_clock::to_time_t(end);

	// 格式化时间为中文
	std::tm* timeinfo = std::localtime(&end_time);
	std::ostringstream oss;
	oss.imbue(std::locale("zh_CN.utf8"));
	oss << std::put_time(timeinfo, u8"%Y年%m月%d日 %H:%M:%S");

	// 设置水印窗口位置和大小
	ImGui::SetNextWindowPos({ Gui.Window.Size.x - 300, 0 });
	ImGui::SetNextWindowSize(ImVec2(300, 50));
	ImGui::SetNextWindowBgAlpha(1.0f); // 设置背景不透明

	// 设置窗口背景为黑色和边框颜色为黄色
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 1.0f)); // 黑色背景
	ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 1.0f, 0.0f, 1.0f)); // 黄色边框
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 1.0f); // 设置边框大小

	ImGui::Begin("watermark", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

	// 计算文本在窗口中垂直居中的位置
	ImVec2 textSize = ImGui::CalcTextSize(oss.str().c_str());
	float textPosY = (ImGui::GetWindowSize().y - textSize.y) / 2.0f;

	// 设置文本位置为垂直居中
	ImGui::SetCursorPosY(textPosY);

	// 将文本颜色设置为红色并显示文本
	ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), u8" 晴枫 | %s", oss.str().c_str());

	ImGui::End();
	ImGui::PopStyleVar(); // 恢复边框大小
	ImGui::PopStyleColor(2); // 恢复之前的窗口背景颜色和边框颜色
}

void Cheats::New_Menu()
{

	ImGui::SetNextWindowSize(ImVec2(855 * dpi_scale, 790 * dpi_scale));
	ImGui::Begin("Menu", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);
	{
		ImGuiStyle& s = ImGui::GetStyle();

		s.Colors[ImGuiCol_WindowBg] = ImColor(60, 65, 80, 60);
		s.Colors[ImGuiCol_ChildBg] = ImColor(20, 20, 20, 255);
		s.Colors[ImGuiCol_PopupBg] = ImColor(26, 26, 26, 255);
		s.Colors[ImGuiCol_Text] = ImColor(120, 120, 120, 255);
		s.Colors[ImGuiCol_TextDisabled] = ImColor(100, 100, 100, 255);
		s.Colors[ImGuiCol_Border] = ImColor(28, 28, 28, 255);
		s.Colors[ImGuiCol_TextSelectedBg] = ImColor(25, 22, 33, 100);

		s.Colors[ImGuiCol_ScrollbarGrab] = ImColor(24, 24, 24, 255);
		s.Colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(24, 24, 24, 255);
		s.Colors[ImGuiCol_ScrollbarGrabActive] = ImColor(24, 24, 24, 255);

		s.WindowBorderSize = 0;
		s.WindowPadding = ImVec2(0, 0);
		s.WindowRounding = 5.f;
		s.PopupBorderSize = 0.f;
		s.PopupRounding = 5.f;
		s.ChildRounding = 7;
		s.ChildBorderSize = 1.f;
		s.FrameBorderSize = 1.0f;
		s.ScrollbarSize = 3.0f;
		s.FrameRounding = 5.f;
		s.ItemSpacing = ImVec2(0, 20);
		s.ItemInnerSpacing = ImVec2(10, 0);

		const auto& p = ImGui::GetWindowPos();

		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 0));
		ImGui::BeginChild("G-Tab", ImVec2(173 * dpi_scale, 790 * dpi_scale), false);
		{
			ImGui::GetForegroundDrawList()->AddText(OSImGui::tab_text3, 20 * dpi_scale, ImVec2(20 * dpi_scale + p.x, 12 * dpi_scale + p.y), ImColor(0, 255, 255, 255), "CS2 hacker");
			ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(0 + p.x, 0 + p.y), ImVec2(273 * dpi_scale + p.x, 790 * dpi_scale + p.y), ImGui::GetColorU32(colors::Tab_Child), s.WindowRounding);

			ImGui::SetCursorPosY(60);

			ImGui::SetWindowFontScale(dpi_scale);
			/*if (ImGui::Tab("H", "Aimbot", "Legit,Trigger,Rage", 0 == tabs, ImVec2(150 * dpi_scale, 42 * dpi_scale))) tabs = 0; //注释掉
			if (ImGui::Tab("G", "Changer", "Inventory & Profile", 1 == tabs, ImVec2(150 * dpi_scale, 42 * dpi_scale))) tabs = 1;
			if (ImGui::Tab("F", "Visuals", "Player,World,Glow", 2 == tabs, ImVec2(150 * dpi_scale, 42 * dpi_scale))) tabs = 2;
			if (ImGui::Tab("E", "Misc", "Other settings", 3 == tabs, ImVec2(150 * dpi_scale, 42 * dpi_scale))) tabs = 3;
			if (ImGui::Tab("D", "Binds", "Use keyboard to on", 4 == tabs, ImVec2(150 * dpi_scale, 42 * dpi_scale))) tabs = 4;
			if (ImGui::Tab("C", "Minigames", "Snake", 5 == tabs, ImVec2(150 * dpi_scale, 42 * dpi_scale))) tabs = 5;
			if (ImGui::Tab("B", "Config", "Manage your configs", 6 == tabs, ImVec2(150 * dpi_scale, 42 * dpi_scale))) tabs = 6;
			if (ImGui::Tab("A", "Chat", "Chat box", 7 == tabs, ImVec2(150 * dpi_scale, 42 * dpi_scale))) tabs = 7;
			if (ImGui::Tab("I", "Search", "Search for cheats", 8 == tabs, ImVec2(150 * dpi_scale, 42 * dpi_scale))) tabs = 8;*/
			//--------------------------------
			if (ImGui::Tab("F", "Esp", "", 0 == tabs, ImVec2(150 * dpi_scale, 42 * dpi_scale))) tabs = 0;
			if (ImGui::Tab("H", "Aimbot", "", 1 == tabs, ImVec2(150 * dpi_scale, 42 * dpi_scale))) tabs = 1;
			//if (ImGui::Tab("G", "Changer", "Inventory & Profile", 1 == tabs, ImVec2(150 * dpi_scale, 42 * dpi_scale))) tabs = 1;
			if (ImGui::Tab("B", "TriggerBot", "", 2 == tabs, ImVec2(150 * dpi_scale, 42 * dpi_scale))) tabs = 2;
			if (ImGui::Tab("I", "Rcs", "", 3 == tabs, ImVec2(150 * dpi_scale, 42 * dpi_scale))) tabs = 3;
			if (ImGui::Tab("E", "Radar", "", 4 == tabs, ImVec2(150 * dpi_scale, 42 * dpi_scale))) tabs = 4;
			//if (ImGui::Tab("D", "Binds", "Use keyboard to on", 4 == tabs, ImVec2(150 * dpi_scale, 42 * dpi_scale))) tabs = 4;
			//if (ImGui::Tab("C", "Minigames", "Snake", 5 == tabs, ImVec2(150 * dpi_scale, 42 * dpi_scale))) tabs = 5;
			
			if (ImGui::Tab("A", "Misc", "",5 == tabs, ImVec2(150 * dpi_scale, 42 * dpi_scale))) tabs = 5;
			//if (ImGui::Tab("I", "Search", "Search for cheats", 8 == tabs, ImVec2(150 * dpi_scale, 42 * dpi_scale))) tabs = 8;
			if (ImGui::Tab("C", "Log", "", 6 == tabs, ImVec2(150 * dpi_scale, 42 * dpi_scale))) tabs = 6;
			//if (ImGui::Tab("G", "Changer", "Inventory & Profile", 6 == tabs, ImVec2(150 * dpi_scale, 42 * dpi_scale))) tabs = 6;
			
		}ImGui::EndChild();


		ImGui::PopStyleColor();

		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(0 + p.x, 0 + p.y), ImVec2(855 * dpi_scale + p.x, 790 * dpi_scale + p.y), ImGui::GetColorU32(colors::main_color), s.WindowRounding);

		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(0 + p.x, 755 * dpi_scale + p.y), ImVec2(855 * dpi_scale + p.x, 755 * dpi_scale + p.y), ImGui::GetColorU32(colors::lite_color), s.WindowRounding);

		//   ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(0 + p.x, 0 + p.y), ImVec2(705 + p.x, 60 + p.y), ImGui::GetColorU32(colors::lite_color), s.WindowRounding);

		ImGui::GetForegroundDrawList()->AddText(OSImGui::tab_text3, 16 * dpi_scale, ImVec2(10 * dpi_scale + p.x, 765 * dpi_scale + p.y), ImColor(0,255, 255, 255), "Welcome");
		ImGui::GetForegroundDrawList()->AddText(OSImGui::tab_text3, 16 * dpi_scale, ImVec2(370 * dpi_scale + p.x, 765 * dpi_scale + p.y), ImColor(0, 255, 255, 255), "[Home]  Display/Hidden menu");
		ImGui::GetForegroundDrawList()->AddText(OSImGui::tab_text3, 16 * dpi_scale, ImVec2(750 * dpi_scale + p.x, 765 * dpi_scale + p.y), ImColor(0,255, 255, 255), "QingFeng");
		tab_alpha = ImClamp(tab_alpha + (7.f * ImGui::GetIO().DeltaTime * (tabs == active_tab ? 1.f : -1.f)), 0.f, 1.f);
		tab_add = ImClamp(tab_add + (std::round(50.f) * ImGui::GetIO().DeltaTime * (tabs == active_tab ? 1.f : -1.f)), 0.f, 1.f);

		if (tab_alpha == 0.f && tab_add == 0.f) active_tab = tabs;


		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab_alpha * s.Alpha);

		ImGui::SetCursorPos(ImVec2(203 * dpi_scale, 30 * dpi_scale));

		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 0));
		ImGui::BeginChild("General", ImVec2(717 * dpi_scale, 720 * dpi_scale), false);
		{
			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImGui::GetColorU32(colors::lite_color));
			switch (active_tab) {

			
			case 0:
			{
				ImGui::BeginChildPos("", ImVec2(620 * dpi_scale, 100 * dpi_scale));
				{
					ImGui::GetForegroundDrawList()->AddText(OSImGui::tab_text3, 26 * dpi_scale, ImVec2(475 * dpi_scale + p.x, 55 * dpi_scale + p.y), ImColor(255, 255, 255, 255), "Esp");
					ImGui::GetForegroundDrawList()->AddText(OSImGui::tab_text3, 16 * dpi_scale, ImVec2(305 * dpi_scale + p.x, 85 * dpi_scale + p.y), ImColor(255, 255, 255, 255), "Being a qualified actor is better than anything else, Trumpet Entertainment.");
				}
				ImGui::EndChild();
				ImGui::SetCursorPosY(120 * dpi_scale);
				ImGui::BeginChildPos("Esp", ImVec2(300 * dpi_scale, 580 * dpi_scale));
				{
					ImGui::SetWindowFontScale(dpi_scale);
					//ImGui::Checkbox("Glow", &MenuConfig::EnemySensor);
					//ImGui::SameLine(0.0f, 5.0f);

	//					HelpMarker("Since the V club has not been repaired yet, this function will be invalid at any time, so play early and enjoy it early");
					/*ImGui::Checkbox(u8"雷达", &MenuConfig::RadarHack);
					ImGui::SameLine(0.0f, 5.0f);

					HelpMarker(u8"此功能开启后自瞄中【掩体判断】将失效");*/
					ImGui::Checkbox("Box", &MenuConfig::ShowBoxESP);
					ImGui::Combo("Box type", &MenuConfig::BoxType, "Ordinary\0Dynamic");
					ImGui::Checkbox("Bones", &MenuConfig::ShowBoneESP);
					ImGui::SameLine(0.0f, 5.0f);

					HelpMarker("Due to the in-game hibernation mechanic, bones may not be refreshed in time when you are too far away from the enemy");
					ImGui::Checkbox("EyeRay", &MenuConfig::ShowEyeRay);
					ImGui::SameLine(0.0f, 5.0f);

					HelpMarker("Due to the in-game hibernation mechanic, bones may not be refreshed in time when you are too far away from the enemy");
					ImGui::Checkbox("Health Bar", &MenuConfig::ShowHealthBar);
					ImGui::Combo("Bar type", &MenuConfig::HealthBarType, u8"竖直\0水平");
					ImGui::Checkbox("Weapons", &MenuConfig::ShowWeaponESP);
					ImGui::Checkbox("C4 Timer", &MenuConfig::bmbTimer);
					ImGui::TextColored(ImVec4(0, 255, 0, 255), "Tip: Slide the mouse wheel");
					ImGui::Checkbox("Distance", &MenuConfig::ShowDistance);
					
					ImGui::Checkbox("Name", &MenuConfig::ShowPlayerName);
				/*	ImGui::Checkbox("HeadShootLine", &MenuConfig::ShowHeadShootLine);
					ImGui::Checkbox("FovLine", &MenuConfig::ShowFovLine);*/
					//float FovLineSizeMin = 20.f, FovLineSizeMax = 120.f;
					//ImGui::SliderFloat("FovLineSize", &MenuConfig::FovLineSize, FovLineSizeMin, FovLineSizeMax, "%.1f", ImGuiSliderFlags_None);

					ImGui::Checkbox("Line", &MenuConfig::ShowLineToEnemy);
					ImGui::Checkbox("Crosshairs", &MenuConfig::ShowCrossHair);
					float CrossHairSizeMin = 15, CrossHairSizeMax = 200;
					ImGui::SliderFloat("Crosshairs Size", &MenuConfig::CrossHairSize, CrossHairSizeMin, CrossHairSizeMax, "%.1f", ImGuiSliderFlags_None);
				

				}
				ImGui::EndChild();
				ImGui::SetCursorPos(ImVec2(320 * dpi_scale, 120 * dpi_scale));
				ImGui::BeginChildPos("Color", ImVec2(300 * dpi_scale, 580 * dpi_scale));
				{
					ImGui::SetWindowFontScale(dpi_scale);
					//ImGui::ColorEdit4("T Glow##GlowColor", reinterpret_cast<float*>( &MenuConfig::GlowColor1), ImGuiColorEditFlags_NoInputs);
					//ImGui::ColorEdit4("CT Glow##GlowColor", reinterpret_cast<float*>(&MenuConfig::GlowColor2), ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4("Box##BoxColor", reinterpret_cast<float*>(&MenuConfig::BoxColor), ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4("Bones##BoneColor", reinterpret_cast<float*>(&MenuConfig::BoneColor), ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4("EyeRay##EyeRay", reinterpret_cast<float*>(&MenuConfig::EyeRayColor), ImGuiColorEditFlags_NoInputs);
					//ImGui::ColorEdit4("Headshot Line Color##HeadShootLineColor", reinterpret_cast<float*>(&MenuConfig::HeadShootLineColor), ImGuiColorEditFlags_NoInputs);
					//ImGui::ColorEdit4("Fov Line Color##FovLineColor", reinterpret_cast<float*>(&MenuConfig::FovLineColor), ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4("Line##LineToEnemyColor", reinterpret_cast<float*>(&MenuConfig::LineToEnemyColor), ImGuiColorEditFlags_NoInputs);
			
					ImGui::ColorEdit4("Weapons##WeaponColor", reinterpret_cast<float*>(&MenuConfig::WeaponColor), ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4("Name##NameColor", reinterpret_cast<float*>(&MenuConfig::NameColor), ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4("Distance##DistanceColor", reinterpret_cast<float*>(&MenuConfig::DistanceColor), ImGuiColorEditFlags_NoInputs);
					
					ImGui::ColorEdit4("Crosshairs##CrossHairColor", reinterpret_cast<float*>(&MenuConfig::CrossHairColor), ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4("C4 Timer##BombTimerCol", reinterpret_cast<float*>(&MenuConfig::BombTimerCol), ImGuiColorEditFlags_NoInputs);
					/*ImGui::SliderFloat(u8"方框厚度", &MenuConfig::BoxThickness, 1.00, 2.00, "%.2f", ImGuiSliderFlags_None);
					ImGui::SliderFloat(u8"骨骼厚度", &MenuConfig::BoneThickness, 1.00, 2.00, "%.2f", ImGuiSliderFlags_None);*/
				/*	ImGui::TextColored(ImVec4(0, 255, 0, 255), u8"注意:竞技、优先模式掉框重新");
			
					ImGui::TextColored(ImVec4(0, 255, 0, 255), u8"打开辅助即可");*/
					
				}
				ImGui::EndChild();
			}
				  break;
			case 1:
			{

				ImGui::BeginChildPos("", ImVec2(620 * dpi_scale, 100 * dpi_scale));
				{
					ImGui::GetForegroundDrawList()->AddText(OSImGui::tab_text3, 26 * dpi_scale, ImVec2(475 * dpi_scale + p.x, 55 * dpi_scale + p.y), ImColor(255, 255, 255, 255), "Aimbot");
					ImGui::GetForegroundDrawList()->AddText(OSImGui::tab_text3, 16 * dpi_scale, ImVec2(305 * dpi_scale + p.x, 85 * dpi_scale + p.y), ImColor(255, 255, 255, 255), "Science and technology power, can not do without, but can not do without");
				}
				ImGui::EndChild();
				ImGui::SetCursorPosY(120 * dpi_scale);
				ImGui::BeginChildPos("Aimbot", ImVec2(620 * dpi_scale, 580 * dpi_scale));
				{
					ImGui::SetWindowFontScale(dpi_scale);
					ImGui::Checkbox("Enable", &MenuConfig::AimBot);

					ImGui::Keybind("Hotkey--Default Alt key", &MenuConfig::AimBotHotKey, true); 
					ImGui::TextColored(ImVec4(0, 255, 0, 255), "Tip: The self-aim hotkey is not recommended to be set to the left button");
					ImGui::TextColored(ImVec4(0, 255, 0, 255), "Tip: If you see a person in your self-aim, press and hold the hotkey");
					ImGui::TextColored(ImVec4(0, 255, 0, 255), "and release when you kill one");
					if (ImGui::Combo("Position", &MenuConfig::AimPosition, "Head\0Neck\0Spine"))
					{
						switch (MenuConfig::AimPosition)
						{
						case 0:
							MenuConfig::AimPositionIndex = BONEINDEX::head;
							break;
						case 1:
							MenuConfig::AimPositionIndex = BONEINDEX::neck_0;
							break;
						case 2:
							MenuConfig::AimPositionIndex = BONEINDEX::spine_1;
							break;
						default:
							break;
						}
					}
					float FovMin = 2.0f, FovMax = 89.f;
					float SmoothMin = 0.f, SmoothMax = 0.9f;
					ImGui::SliderFloat("Range", &AimControl::AimFov, FovMin, FovMax, "%.1f", ImGuiSliderFlags_None);
					ImGui::SliderFloat("Smooth", &AimControl::Smooth, SmoothMin, SmoothMax, "%.1f", ImGuiSliderFlags_None);
					ImGui::Checkbox("VisualCheck", &MenuConfig::VisibleCheck);// 移除可视检查
					ImGui::SameLine(0.0f, 5.0f);
					
					HelpMarker("Only when you see a person [and] a red mark on the map will you aim at yourself");
					ImGui::SameLine(0.0f, 30.0f); 
					
					ImGui::Checkbox("Range circles", &MenuConfig::ShowAimFovRange);

					ImGui::ColorEdit4("Range circle color##FovCircleColor", reinterpret_cast<float*>(&MenuConfig::AimFovRangeColor), ImGuiColorEditFlags_NoInputs);
					ImGui::TextColored(ImVec4(0, 255, 0, 255), "Note: Shoot when locked to someone, don't press the fire button and don't let go");
				}
				ImGui::EndChild();
				
				//ImGui::SetCursorPos(ImVec2(320 * dpi_scale, 390 * dpi_scale));
				//ImGui::BeginChildPos(u8"压枪", ImVec2(300 * dpi_scale, 310 * dpi_scale));

				//{

				//	int BulletMin = 0, BulletMax = 6;  //初版
				//	float RecoilMin = 0.f, RecoilMax = 2.f;
				//	ImGui::TextColored(ImVec4(0, 255, 0, 255), u8"注意:此功能需要启用自瞄");
				//	ImGui::SliderInt(u8"子弹阈值--推荐1或2", &AimControl::RCSBullet, BulletMin, BulletMax, "%d", ImGuiSliderFlags_None);
				//	ImGui::SliderFloat(u8"水平---推荐0.8", &AimControl::RCSScale.x, RecoilMin, RecoilMax, "%.1f", ImGuiSliderFlags_None);
				//	ImGui::SliderFloat(u8"下压---推荐1.2", &AimControl::RCSScale.y, RecoilMin, RecoilMax, "%.1f", ImGuiSliderFlags_None);

				//}
				//ImGui::EndChild();

			}
			break;
			case 2: {
				ImGui::BeginChildPos("", ImVec2(620 * dpi_scale, 100 * dpi_scale));
				{
					ImGui::GetForegroundDrawList()->AddText(OSImGui::tab_text3, 26 * dpi_scale, ImVec2(450 * dpi_scale + p.x, 55 * dpi_scale + p.y), ImColor(255, 255, 255, 255), "TriggerBot");
					ImGui::GetForegroundDrawList()->AddText(OSImGui::tab_text3, 16 * dpi_scale, ImVec2(305 * dpi_scale + p.x, 85 * dpi_scale + p.y), ImColor(255, 255, 255, 255), "Have you ever heard of automatic shooting? Every mistake is a trigger");
				}
				ImGui::EndChild();
				ImGui::SetCursorPosY(120 * dpi_scale);
				
					
					ImGui::BeginChildPos("TriggerBot", ImVec2(620 * dpi_scale, 580 * dpi_scale));
					{
						ImGui::SetWindowFontScale(dpi_scale);
						ImGui::Checkbox("Enable", &MenuConfig::TriggerBot);
						ImGui::Keybind("Hotkey--Default Caps key", &MenuConfig::TriggerHotKey, true);
						if (ImGui::Combo("Mode", &MenuConfig::TriggerMode, "Hotkey\0Automatic"))
						{

							TriggerBot::SetMode(MenuConfig::TriggerMode);
						}
						ImGui::TextColored(ImVec4(0, 255, 0, 255), "Hint: The trigger is to shoot when the crosshair is on the enemy");
						ImGui::TextColored(ImVec4(0, 255, 0, 255), "Note: Button mode requires a hotkey to fire");
						ImGui::TextColored(ImVec4(0, 255, 0, 255), "Automatic mode automatically fires without hotkeys");
						DWORD TriggerDelayMin = 15, TriggerDelayMax = 500;
						ImGui::SliderInt("Delay/ms", &TriggerBot::TriggerDelay, TriggerDelayMin, TriggerDelayMax, "%d", ImGuiSliderFlags_None);
						
					}
					ImGui::EndChild();

				
			}
				  break;
			case 3: {
				ImGui::BeginChildPos("", ImVec2(620 * dpi_scale, 100 * dpi_scale));
				{
					ImGui::GetForegroundDrawList()->AddText(OSImGui::tab_text3, 26 * dpi_scale, ImVec2(450 * dpi_scale + p.x, 55 * dpi_scale + p.y), ImColor(255, 255, 255, 255), "Rcs");
					ImGui::GetForegroundDrawList()->AddText(OSImGui::tab_text3, 16 * dpi_scale, ImVec2(300 * dpi_scale + p.x, 85 * dpi_scale + p.y), ImColor(255, 255, 255, 255), "It's better than your mouse macro, and it's better than your pressure gun software");
				}
				ImGui::EndChild();
				ImGui::SetCursorPosY(120 * dpi_scale);

				
				ImGui::BeginChildPos("Rcs", ImVec2(620 * dpi_scale, 580 * dpi_scale));
				{
					ImGui::Checkbox("Enable", &MenuConfig::RCS);
					ImGui::SliderFloat("Start pressing from the first few bullets", &MenuConfig::RCSBullet, 1, 6, "%.0f", ImGuiSliderFlags_None);

					ImGui::SliderFloat("Rcs X", &RCS::RCSScale.x, 0.f, 2.0f, "%.2f", ImGuiSliderFlags_None);
					ImGui::SliderFloat("Rcs Y", &RCS::RCSScale.y, 0.f, 2.f, "%.2f", ImGuiSliderFlags_None);
					ImGui::TextColored(ImVec4(0, 255, 0, 255), "-------------------Bullet ballistics-------------------");
					float scalex = (2.22 - RCS::RCSScale.x) * .5f;
					float scaley = (2.12 - RCS::RCSScale.y) * .5f;//Simulate reasonable error values
					ImVec2 BulletPos = ImGui::GetCursorScreenPos();

					// Example Preview
					ImVec2 BulletPos0, BulletPos1, BulletPos2, BulletPos3, BulletPos4, BulletPos5, BulletPos6, BulletPos7, BulletPos8, BulletPos9, BulletPos10, BulletPos11, BulletPos12, BulletPos13, BulletPos14, BulletPos15;
					BulletPos.y += 123 * scaley;
					BulletPos0.x = BulletPos.x + 125; BulletPos0.y = BulletPos.y + 5;
					BulletPos1.x = BulletPos0.x - 3 * scalex; BulletPos1.y = BulletPos0.y - 5 * scaley;
					BulletPos2.x = BulletPos1.x + 2 * scalex; BulletPos2.y = BulletPos1.y - 10 * scaley;
					BulletPos3.x = BulletPos2.x + 4 * scalex; BulletPos3.y = BulletPos2.y - 11 * scaley;
					BulletPos4.x = BulletPos3.x - 3 * scalex; BulletPos4.y = BulletPos3.y - 31 * scaley;
					BulletPos5.x = BulletPos4.x - 1 * scalex; BulletPos5.y = BulletPos4.y - 20 * scaley;
					BulletPos6.x = BulletPos5.x - 2 * scalex; BulletPos6.y = BulletPos5.y - 17 * scaley;
					BulletPos7.x = BulletPos6.x - 15 * scalex; BulletPos7.y = BulletPos6.y - 9 * scaley;
					BulletPos8.x = BulletPos7.x + 7 * scalex; BulletPos8.y = BulletPos7.y - 8 * scaley;
					BulletPos9.x = BulletPos8.x + 33 * scalex; BulletPos9.y = BulletPos8.y + 2 * scaley;
					BulletPos10.x = BulletPos9.x + 1 * scalex; BulletPos10.y = BulletPos9.y - 16 * scaley;
					BulletPos11.x = BulletPos10.x - 9 * scalex; BulletPos11.y = BulletPos10.y + 20 * scaley;
					BulletPos12.x = BulletPos11.x - 3 * scalex; BulletPos12.y = BulletPos11.y - 9 * scaley;
					BulletPos13.x = BulletPos12.x + 15 * scalex; BulletPos13.y = BulletPos12.y - 5 * scaley;
					BulletPos14.x = BulletPos13.x + 10 * scalex; BulletPos14.y = BulletPos13.y - 4 * scaley;

					ImGui::GetWindowDrawList()->AddCircleFilled(BulletPos0, 4.f, ImColor(255, 0, 0, 255));
					ImGui::GetWindowDrawList()->AddCircleFilled(BulletPos1, 4.f, ImColor(255, 0, 0, 255));
					ImGui::GetWindowDrawList()->AddCircleFilled(BulletPos2, 4.f, ImColor(255, 0, 0, 255));
					ImGui::GetWindowDrawList()->AddCircleFilled(BulletPos3, 4.f, ImColor(255, 0, 0, 255));
					ImGui::GetWindowDrawList()->AddCircleFilled(BulletPos4, 4.f, ImColor(255, 0, 0, 255));
					ImGui::GetWindowDrawList()->AddCircleFilled(BulletPos5, 4.f, ImColor(255, 0, 0, 255));
					ImGui::GetWindowDrawList()->AddCircleFilled(BulletPos6, 4.f, ImColor(255, 0, 0, 255));
					ImGui::GetWindowDrawList()->AddCircleFilled(BulletPos7, 4.f, ImColor(255, 0, 0, 255));
					ImGui::GetWindowDrawList()->AddCircleFilled(BulletPos8, 4.f, ImColor(255, 0, 0, 255));
					ImGui::GetWindowDrawList()->AddCircleFilled(BulletPos9, 4.f, ImColor(255, 0, 0, 255));
					ImGui::GetWindowDrawList()->AddCircleFilled(BulletPos10, 4.f, ImColor(255, 0, 0, 255));
					ImGui::GetWindowDrawList()->AddCircleFilled(BulletPos11, 4.f, ImColor(255, 0, 0, 255));
					ImGui::GetWindowDrawList()->AddCircleFilled(BulletPos12, 4.f, ImColor(255, 0, 0, 255));
					ImGui::GetWindowDrawList()->AddCircleFilled(BulletPos13, 4.f, ImColor(255, 0, 0, 255));
					ImGui::GetWindowDrawList()->AddCircleFilled(BulletPos14, 4.f, ImColor(255, 0, 0, 255));

					ImGui::SetCursorScreenPos(ImVec2(BulletPos.x, BulletPos.y + 10));

				}
				ImGui::EndChild();


			}
				  break;


			case 4: {
				ImGui::BeginChildPos("", ImVec2(620 * dpi_scale, 100 * dpi_scale));
				{
					ImGui::GetForegroundDrawList()->AddText(OSImGui::tab_text3, 26 * dpi_scale, ImVec2(450 * dpi_scale + p.x, 55 * dpi_scale + p.y), ImColor(255, 255, 255, 255), "Radar");
					ImGui::GetForegroundDrawList()->AddText(OSImGui::tab_text3, 16 * dpi_scale, ImVec2(305 * dpi_scale + p.x, 85 * dpi_scale + p.y), ImColor(255, 255, 255, 255), "Have a nice day playing and having a good day.");
				}
				ImGui::EndChild();
				ImGui::SetCursorPosY(120 * dpi_scale);
				ImGui::BeginChildPos("Radar", ImVec2(620 * dpi_scale, 580 * dpi_scale));
				{ImGui::SetWindowFontScale(dpi_scale);
				ImGui::Checkbox("Animated menus", &animated_background);
				ImGui::SliderFloat("Menu resolution", &dpi_scale, 1.0f, 1.2f, "%.3f", 0);
				ImGui::Checkbox("Radar", &MenuConfig::ShowRadar);
				ImGui::Combo("Radar style", &MenuConfig::RadarType, "circle\0arrowhead\0Arrow circles");

				ImGui::Checkbox("Radar crosshair", &MenuConfig::ShowRadarCrossLine);
				ImGui::ColorEdit4("Radar reticle color##CrossLineColor", reinterpret_cast<float*>(&MenuConfig::RadarCrossLineColor), ImGuiColorEditFlags_NoInputs);

				float ProportionMin = 500.f, ProportionMax = 3300.f;
				float RadarRangeMin = 100.f, RadarRangeMax = 300.f;
				float RadarPointSizeProportionMin = 0.8f, RadarPointSizeProportionMax = 2.f;
				ImGui::SliderFloat("Radar size" , &MenuConfig::RadarPointSizeProportion, RadarPointSizeProportionMin, RadarPointSizeProportionMax, "%.1f", ImGuiSliderFlags_None);
				ImGui::SliderFloat("Radar scale" , &MenuConfig::Proportion, ProportionMin,ProportionMax, "%.1f", ImGuiSliderFlags_None);
				ImGui::SliderFloat("Radar range", &MenuConfig::RadarRange, RadarRangeMin, RadarRangeMax, "%.1f", ImGuiSliderFlags_None);

				}
				ImGui::EndChild();
			}
				  break;
			case 5:
			{	
				ImGui::BeginChildPos("", ImVec2(620 * dpi_scale, 100 * dpi_scale));
				{
					ImGui::GetForegroundDrawList()->AddText(OSImGui::tab_text3, 26 * dpi_scale, ImVec2(450 * dpi_scale + p.x, 55 * dpi_scale + p.y), ImColor(255, 255, 255, 255), "Misc");
					ImGui::GetForegroundDrawList()->AddText(OSImGui::tab_text3, 16 * dpi_scale, ImVec2(300 * dpi_scale + p.x, 85 * dpi_scale + p.y), ImColor(255, 255, 255, 255), "After-sales working hours: 10 a.m. - 10 p.m., thank you for your understanding.");
				}
				ImGui::EndChild();
				ImGui::SetCursorPosY(120 * dpi_scale);
				ImGui::BeginChildPos("Misc", ImVec2(620 * dpi_scale, 580 * dpi_scale));
				{
					ImGui::Keybind("Menu show/hide hotkeys", &MenuConfig::MenuKery, true);
					ImGui::Checkbox("Ignore the flash", &MenuConfig::AntiFlashbang);
					ImGui::Checkbox("Quick emergency stops", &MenuConfig::FastStop);
					ImGui::Checkbox("Checkteam", &MenuConfig::TeamCheck);
					ImGui::SameLine(0.0f, 5.0f);

					HelpMarker("Deathmatch and other modes are on");
					ImGui::Checkbox("Live broadcast, anti-screenshot", &MenuConfig::OBSBypass);
					
					ImGui::SameLine(0.0f, 5.0f);

					HelpMarker("The recording and screenshot tool cannot capture the cheating footage, only you can see it");
					//ImGui::Checkbox(u8"显示时间", &MenuConfig::MenuLogo);
					ImGui::Checkbox("Hit feedback", &MenuConfig::HitMarker);
				
					ImGui::Combo("Hit sounds", &MenuConfig::HitSound, "Null\0one\0two\0three\0four\0");
					
					ImVec4 original_text_color = ImGui::GetStyle().Colors[ImGuiCol_Text];

					// 设置新的文本颜色
					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.5f, 0.0f, 0.5f, 1.0f));  // 紫色

					// 创建按钮
					if (ImGui::Button("Click I Secure Exit Assist", { 300, 50 }))
					{
						exit(0);
					}

					// 恢复原始的文本颜色
					ImGui::PopStyleColor();
					
					//ImGui::TextColored(ImVec4(0, 255, 0, 255), u8"谢谢各位老板的支持，老板的好评就是我的动力，非常感谢。");
					//ImGui::TextColored(ImVec4(0, 255, 0, 255), u8"谢谢各位老板的支持，老板的好评就是我的动力，非常感谢。");
				}
				ImGui::EndChild();
			}
			break;
			
			case 6:
			{
				ImGui::BeginChildPos("", ImVec2(620 * dpi_scale, 100 * dpi_scale));
				{
					ImGui::GetForegroundDrawList()->AddText(OSImGui::tab_text3, 26 * dpi_scale, ImVec2(450 * dpi_scale + p.x, 55 * dpi_scale + p.y), ImColor(255, 255, 255, 255),"Changelog");
					ImGui::GetForegroundDrawList()->AddText(OSImGui::tab_text3, 16 * dpi_scale, ImVec2(300 * dpi_scale + p.x, 85 * dpi_scale + p.y), ImColor(255, 255, 255, 255), "The game is usually updated at 4-6 am, then I will finish the update at 8-12 am");
				}
				ImGui::EndChild();
				ImGui::SetCursorPosY(120 * dpi_scale);
				ImGui::BeginChildPos("Log", ImVec2(620 * dpi_scale, 580 * dpi_scale));
				{
					ImGui::TextColored(ImVec4(0, 255, 255, 255), "---- due to the frequent updates of VAC anti-cheat recently, it is best to use a small account");
					ImGui::TextColored(ImVec4(0, 255, 255, 255), "and find customer service if there is no small number");
					ImGui::TextColored(ImVec4(0, 255, 0, 255), "2024.09.10,The game was updated today, and the software has been updated");
					ImGui::TextColored(ImVec4(0, 255, 0, 255), "2024.09.04-2,Added [Perspective] Glow, and Miscellaneous [Quick Stop]");
					ImGui::TextColored(ImVec4(0, 255, 0, 255), "2024.09.04-1,The game was updated today, and the software has been updated");
					ImGui::TextColored(ImVec4(0, 255, 0, 255), "2024.08.28-2,Repair boxes, bones");
					ImGui::TextColored(ImVec4(0, 255, 0, 255), "2024.08.28-1,Scrambled features, added miscellaneous [hit hints and sound effects]");
				
					ImGui::TextColored(ImVec4(0, 255, 0, 255), "2024.08.22,The game has been updated again today, and the software has been updated");
					ImGui::TextColored(ImVec4(0, 255, 0, 255), "2024.08.21,The game was suddenly updated today, and the software has been updated");
					ImGui::TextColored(ImVec4(0, 255, 0, 255), "2024.08.20,The game was updated today, and the software has been updated");
					ImGui::TextColored(ImVec4(0, 255, 0, 255), "2024.08.15,The game was updated in the early hours of this morning, and the software has been updated");
					ImGui::TextColored(ImVec4(0, 255, 0, 255), "2024.08.09,The game is updated once today, and it is updated once darkly");
					ImGui::TextColored(ImVec4(0, 255, 0, 255), "2024.08.05,Added C4 timer function to rewrite the pressure gun frame");
					ImGui::TextColored(ImVec4(0, 255, 0, 255), "2024.08.02,Changed the feature and added a trigger mode");
					ImGui::TextColored(ImVec4(0, 255, 0, 255), "2024.07.26,Major updates to the game to enhance the stability of the Great Earth");
					ImGui::TextColored(ImVec4(0, 255, 0, 255), "2024.07.23,Major updates to the game to enhance the stability of the Great Earth");
					ImGui::TextColored(ImVec4(0, 255, 0, 255), "2024.07.12,The game has been updated, the menu has been updated, it is more intuitive");
					ImGui::TextColored(ImVec4(0, 255, 0, 255), "and the stability of the Great Earth has been strengthened");
					ImGui::TextColored(ImVec4(0, 255, 0, 255), "2024.07.06,The game has been updated to strengthen the stability of the Great Earth");
					
				}
				ImGui::EndChild();
			}
			break;
			}
			
			ImGui::PopStyleColor(1);

			ImGui::Spacing();

			ImGui::EndChild();

			ImGui::PopStyleColor(1);
		}
		if (animated_background)
			Particles();
		ImGui::PopStyleVar(1);

	}
	ImGui::End();
}

void Cheats::RadarSetting(Base_Radar& Radar)
{
	// Radar window
	ImGui::SetNextWindowBgAlpha(0.1f);
	ImGui::Begin("Radar", 0, ImGuiWindowFlags_NoResize);
	ImGui::SetWindowSize({ MenuConfig::RadarRange * 2,MenuConfig::RadarRange * 2 });

	// Radar.SetPos({ Gui.Window.Size.x / 2,Gui.Window.Size.y / 2 });
	Radar.SetDrawList(ImGui::GetWindowDrawList());
	Radar.SetPos({ ImGui::GetWindowPos().x + MenuConfig::RadarRange, ImGui::GetWindowPos().y + MenuConfig::RadarRange });
	Radar.SetProportion(MenuConfig::Proportion);
	Radar.SetRange(MenuConfig::RadarRange);
	Radar.SetSize(MenuConfig::RadarRange * 2);
	Radar.SetCrossColor(MenuConfig::RadarCrossLineColor);

	Radar.ArcArrowSize *= MenuConfig::RadarPointSizeProportion;
	Radar.ArrowSize *= MenuConfig::RadarPointSizeProportion;
	Radar.CircleSize *= MenuConfig::RadarPointSizeProportion;

	Radar.ShowCrossLine = MenuConfig::ShowRadarCrossLine;
	Radar.Opened = true;
}

void Cheats::Run()
{
	// Show menu
	static std::chrono::time_point LastTimePoint = std::chrono::steady_clock::now();
	auto CurTimePoint = std::chrono::steady_clock::now();

	if (GetAsyncKeyState(MenuConfig::MenuKery)
		&& CurTimePoint - LastTimePoint >= std::chrono::milliseconds(150)) {
		MenuConfig::ShowMenu = !MenuConfig::ShowMenu;
		LastTimePoint = CurTimePoint;
	}


	if (MenuConfig::ShowMenu)
		New_Menu();
	if (MenuConfig::MenuLogo)
	{
		shuiyin();
	}
	// Update matrix
	if (!ProcessMgr.ReadMemory(gGame.GetMatrixAddress(), gGame.View.Matrix, 64))
		return;

	// Update EntityList Entry
	gGame.UpdateEntityListEntry();

	DWORD64 LocalControllerAddress = 0;
	DWORD64 LocalPawnAddress = 0;

	if (!ProcessMgr.ReadMemory(gGame.GetLocalControllerAddress(), LocalControllerAddress))
		return;
	if (!ProcessMgr.ReadMemory(gGame.GetLocalPawnAddress(), LocalPawnAddress))
		return;

	// LocalEntity
	CEntity LocalEntity;
	static int LocalPlayerControllerIndex = 1; //移除可视检查
	LocalEntity.UpdateClientData();
	if (!LocalEntity.UpdateController(LocalControllerAddress))
		return;
	if (!LocalEntity.UpdatePawn(LocalPawnAddress) && !MenuConfig::ShowWhenSpec)
		return;

	RCS::RecoilControl(LocalEntity);
	bmb::RenderWindow();
	// HealthBar Map
	static std::map<DWORD64, Render::HealthBar> HealthBarMap;

	// AimBot data
	float DistanceToSight = 0;
	float MaxAimDistance = 100000;
	Vec3  HeadPos{ 0,0,0 };
	Vec3  AimPos{ 0,0,0 };

	// Radar Data
	Base_Radar Radar;
	if (MenuConfig::ShowRadar)
		RadarSetting(Radar);
	// 添加刷新数据的时间记录

	//static std::chrono::time_point LastRefreshTime = std::chrono::steady_clock::now();

	//// 检测F5按键
	//if (GetAsyncKeyState(VK_F5))
	//{
	//	auto CurTimePoint = std::chrono::steady_clock::now();
	//	if (CurTimePoint - LastRefreshTime >= std::chrono::milliseconds(500)) // 防止频繁刷新
	//	{
	//		// 刷新EntityList Entry
	//		gGame.UpdateEntityListEntry();

	//		// 重新更新本地玩家Controller和Pawn地址
	//		if (!ProcessMgr.ReadMemory(gGame.GetLocalControllerAddress(), LocalControllerAddress))
	//			return;
	//		if (!ProcessMgr.ReadMemory(gGame.GetLocalPawnAddress(), LocalPawnAddress))
	//			return;

	//		LastRefreshTime = CurTimePoint; // 更新上次刷新时间
	//	}
	//}


	for (int i = 0; i < 64; i++)
	{
		CEntity Entity;
		DWORD64 EntityAddress = 0;
		if (!ProcessMgr.ReadMemory<DWORD64>(gGame.GetEntityListEntry() + (i + 1) * 0x78, EntityAddress))
			continue;

		if (EntityAddress == LocalEntity.Controller.Address)
		{
			LocalPlayerControllerIndex = i; //移除可视检查
			continue;
		}

		if (!Entity.UpdateController(EntityAddress))
			continue;

		if (!Entity.UpdatePawn(Entity.Pawn.Address))
			continue;

		
		

		//if (MenuConfig::TeamCheck && Entity.Pawn.TeamID == LocalEntity.Pawn.TeamID) //测试
		//	continue;

		if (MenuConfig::TeamCheck && Entity.Controller.TeamID == LocalEntity.Controller.TeamID) 
			continue;

		if (!Entity.IsAlive())
			continue;



		if (!Entity.IsInScreen())
			continue;

	
		

		// Add entity to radar
		if (MenuConfig::ShowRadar)
			Radar.AddPoint(LocalEntity.Pawn.Pos, LocalEntity.Pawn.ViewAngle.y, Entity.Pawn.Pos, ImColor(237, 85, 106, 200), MenuConfig::RadarType, Entity.Pawn.ViewAngle.y);
		// Box
		ImVec4 Rect;
		switch (MenuConfig::BoxType)
		{
		case 0:
			Rect = Render::Get2DBox(Entity);
			break;
		case 1:
			Rect = Render::Get2DBoneRect(Entity);
			break;
		default:
			break;
		}
		// Draw Box
		if (MenuConfig::ShowBoxESP)
			Gui.Rectangle({ Rect.x,Rect.y }, { Rect.z,Rect.w }, MenuConfig::BoxColor, MenuConfig::BoxThickness);

		// Line to enemy
		if (MenuConfig::ShowLineToEnemy)
			Render::LineToEnemy(Rect, MenuConfig::LineToEnemyColor, 1.3);


		// Draw Bone
		if (MenuConfig::ShowBoneESP)
			//Render::DrawBone(Entity, MenuConfig::BoneColor, 1.3);
			Render::DrawBone(Entity,LocalEntity, MenuConfig::BoneColor, MenuConfig::BoneThickness);
		// Draw eyeRay
		if (MenuConfig::ShowEyeRay)
			Render::ShowLosLine(Entity, 50, MenuConfig::EyeRayColor, 1.3);



		// Draw HealthBar
		if (MenuConfig::ShowHealthBar)
		{
			ImVec2 HealthBarPos, HealthBarSize;
			if (MenuConfig::HealthBarType == 0)
			{
				// Vertical
				HealthBarPos = { Rect.x - 7.f,Rect.y };
				HealthBarSize = { 7 ,Rect.w };
			}
			else
			{
				// Horizontal
				HealthBarPos = { Rect.x + Rect.z / 2 - 70 / 2,Rect.y - 13 };
				HealthBarSize = { 70,8 };
			}
			Render::DrawHealthBar(EntityAddress, 100, Entity.Pawn.Health, HealthBarPos, HealthBarSize, MenuConfig::HealthBarType);
		}

		// Draw weaponName
		if (MenuConfig::ShowWeaponESP)
			Gui.StrokeText(Entity.Pawn.WeaponName, { Rect.x,Rect.y + Rect.w }, MenuConfig::WeaponColor, 14);

		if (MenuConfig::ShowDistance)
			Render::DrawDistance(LocalEntity, Entity, Rect);

		if (MenuConfig::ShowPlayerName)
		{
			if (MenuConfig::HealthBarType == 0)
				Gui.StrokeText(Entity.Controller.PlayerName, { Rect.x + Rect.z / 2,Rect.y - 14 }, MenuConfig::NameColor, 14, true);
			else
				Gui.StrokeText(Entity.Controller.PlayerName, { Rect.x + Rect.z / 2,Rect.y - 13 - 14 }, MenuConfig::NameColor, 14, true);
		}

		// Bone Debug
	/*	for (int BoneIndex = 0; BoneIndex < Entity.BoneData.BonePosList.size(); BoneIndex++)
		{
			Vec2 ScreenPos{};
			if (gGame.View.WorldToScreen(Entity.BoneData.BonePosList[BoneIndex].Pos, ScreenPos))
			{
				Gui.Text(std::to_string(BoneIndex), ScreenPos, ImColor(255, 255, 255, 255));
			}
		}*/

		DistanceToSight = Entity.GetBone().BonePosList[BONEINDEX::head].ScreenPos.DistanceTo({ Gui.Window.Size.x / 2,Gui.Window.Size.y / 2 });
	

		if (DistanceToSight < MaxAimDistance)
		{
			MaxAimDistance = DistanceToSight;
			// From: https://github.com/redbg/CS2-Internal/blob/fc8e64430176a62f8800b7467884806708a865bb/src/include/Cheats.hpp#L129
			if (!MenuConfig::VisibleCheck ||
				Entity.Pawn.bSpottedByMask & (DWORD64(1) << (LocalPlayerControllerIndex)) ||
				LocalEntity.Pawn.bSpottedByMask & (DWORD64(1) << (i)))
			
			{
				AimPos = Entity.GetBone().BonePosList[MenuConfig::AimPositionIndex].Pos;
				if (MenuConfig::AimPositionIndex == BONEINDEX::head)
					AimPos.z -= 1.f;

			}
		
		}
		// 
		
		//if (DistanceToSight < MaxAimDistance)
		//{
		//	MaxAimDistance = DistanceToSight;

		//	// 无论是否启用VisibleCheck，都会继续处理自瞄
		//	AimPos = Entity.GetBone().BonePosList[MenuConfig::AimPositionIndex].Pos;
		//	if (MenuConfig::AimPositionIndex == BONEINDEX::head)
		//		AimPos.z -= 1.f;
		//}

		
		//Glow::Run(Entity);
		//Misc::RadarHack(Entity);
	}

	
	if (MenuConfig::AimBot && GetAsyncKeyState(MenuConfig::AimBotHotKey))
	{
		if (AimPos != Vec3(0, 0, 0))
		{
			AimControl::AimBot(LocalEntity, LocalEntity.Pawn.CameraPos, AimPos);
		}
	}


	//// Fov line
	//if (MenuConfig::ShowFovLine)
	//	Render::DrawFov(LocalEntity, MenuConfig::FovLineSize, MenuConfig::FovLineColor, 1.5);

	// Radar render
	if (MenuConfig::ShowRadar)
	{
		Radar.Render();
		//End for radar window
		ImGui::End();
	}
	//MenuConfig::TriggerHotKey   TriggerBot::HotKey
	// TriggerBot
	if (MenuConfig::TriggerMode == 1 && MenuConfig::TriggerBot && CurTimePoint - LastTimePoint >= std::chrono::milliseconds(150))
	{
		MenuConfig::Shoot = true;
		TriggerBot::Run(LocalEntity);
		MenuConfig::Shoot = false;
		LastTimePoint = CurTimePoint;
	}
	else if (MenuConfig::TriggerMode == 0 && MenuConfig::TriggerBot && GetAsyncKeyState(MenuConfig::TriggerHotKey))
	{
		MenuConfig::Shoot = true;
		TriggerBot::Run(LocalEntity);
		MenuConfig::Shoot = false;
	}

	Misc::HitManager(LocalEntity, PreviousTotalHits);
	Misc::HitMarker(30.f, 10.f);

	Misc::FastStop();
	// Fov circle
	if (MenuConfig::ShowAimFovRange)
		Render::DrawFovCircle();

	// HeadShoot Line
	if (MenuConfig::ShowHeadShootLine)
		Render::HeadShootLine(LocalEntity, MenuConfig::HeadShootLineColor);

	// CrossHair
	if (MenuConfig::ShowCrossHair)
		Render::DrawCrossHair();



	//if (MenuConfig::BunnyHop)
	//	Bunnyhop::Run(LocalEntity);

	if (MenuConfig::AntiFlashbang)
		AntiFlashbang::Run(LocalEntity);

	


}
