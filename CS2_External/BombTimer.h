
#pragma once
#include <chrono>
#include <iostream>
#include <utility>
#include <sstream>
#include <ctime>
#include <string>
#include "MenuConfig.hpp"
#include"Entity.h"
namespace bmb
{
	bool isPlanted = false;
	std::time_t plantTime;

	uint64_t currentTimeMillis() {
		using namespace std::chrono;
		return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	}

	int getBombSite(bool Planted)
	{
		if (Planted)
		{
			int site;
			uintptr_t cPlantedC4;
			ProcessMgr.ReadMemory(gGame.GetClientDLLAddress() + Offset::PlantedC4, cPlantedC4);
			if (!ProcessMgr.ReadMemory<uintptr_t>(gGame.GetClientDLLAddress() + Offset::PlantedC4, cPlantedC4))
				return 0;
			if (!ProcessMgr.ReadMemory<uintptr_t>(cPlantedC4, cPlantedC4))
				return 0;

			if (!ProcessMgr.ReadMemory<int>(cPlantedC4 + Offset::C4.m_nBombSite, site))
				return 0;

			return site;
		}

	}

	void RenderWindow()
	{
		if (!MenuConfig::bmbTimer)

			return;

		bool isBombPlanted;
		bool IsBeingDefused;
		float DefuseTime;
		auto plantedAddress = gGame.GetClientDLLAddress() + Offset::PlantedC4 - 0x8;

		ProcessMgr.ReadMemory(plantedAddress, isBombPlanted);

		auto time = currentTimeMillis();

		if (isBombPlanted && !isPlanted && (plantTime == NULL || time - plantTime > 60000))
		{
			isPlanted = true;
			plantTime = time;
		}

		if (!isPlanted)
		{
			return;
		}
		// 定义自定义颜色
		ImVec4 titlebarColor = ImVec4(0.2f, 0.3f, 0.7f, 1.0f);  // 标题栏颜色
		ImVec4 backgroundColor = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);  // 背景颜色

		// 推送自定义颜色
		ImGui::PushStyleColor(ImGuiCol_TitleBgActive, titlebarColor);
		ImGui::PushStyleColor(ImGuiCol_TitleBg, titlebarColor);
		ImGui::PushStyleColor(ImGuiCol_WindowBg, backgroundColor);


		static float windowWidth = 300.0f;
		ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize;
		ImGui::SetNextWindowPos({ (ImGui::GetIO().DisplaySize.x - 200.0f) / 2.0f, 80.0f }, ImGuiCond_Once);
		ImGui::SetNextWindowSize({ windowWidth, 0 }, ImGuiCond_Once);
		ImGui::Begin(u8"C4倒计时", nullptr, flags);

		float remaining = (40000 - (int64_t)time + plantTime) / (float)1000;



		ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 180) * 0.5f);
		float barLength = remaining <= 0.0f ? 0.0f : remaining >= 40 ? 1.0f : (remaining / 40.0f);

		if (isPlanted && remaining >= 0)
		{
			std::ostringstream ss;
			ss.precision(3);
			ss << u8"C4安放在: " << (!getBombSite(isBombPlanted) ? "A" : "B") << u8"  点 倒计时: " << std::fixed << remaining << " s" << std::endl;
			ss << u8"无拆弹器需要10秒 有拆弹器需要5秒" << std::endl;
			ss << u8" ------注意把握好拆弹时间------";
			Gui.MyText(std::move(ss).str().c_str(), true);

		}
		else {
			Gui.MyText(u8"无安放C4", true);
			barLength = 0.0f;
		}
		ImGui::TextUnformatted(" ");
		ImGui::SameLine();
		Gui.MyProgressBar(barLength, { 280, 15 }, "", MenuConfig::BombTimerCol);

		if (isPlanted && !isBombPlanted)
		{
			isPlanted = false;
		}
		ImGui::PopStyleColor();
		ImGui::End();
	}
}