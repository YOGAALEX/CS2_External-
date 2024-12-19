#include "Misc.h"

#include <iostream>
#include <Shellapi.h>


namespace Misc
{
	Hitmarker hitmarker;

	bool aKeyPressed = false;
	bool dKeyPressed = false;
	bool wKeyPressed = false;
	bool sKeyPressed = false;

	

	void HitManager(const CEntity& aLocalPlayer, int& PreviousTotalHits) noexcept
	{
		if (MenuConfig::HitMarker || MenuConfig::HitSound)
		{
			uintptr_t pBulletServices;
			int totalHits;
			ProcessMgr.ReadMemory(aLocalPlayer.Pawn.Address + Offset::Pawn.BulletServices, pBulletServices);
			ProcessMgr.ReadMemory(pBulletServices + Offset::Pawn.TotalHit, totalHits);

			if (totalHits != PreviousTotalHits) {
				if (totalHits == 0 && PreviousTotalHits != 0)
				{
					// `totalHits` changed from non-zero to zero, do nothing
				}
				else
				{
					// Hit Marker
					if (MenuConfig::HitMarker)
					{
						hitmarker.alpha = 255.f;
						hitmarker.startTime = std::chrono::steady_clock::now();
					}

					// Hit Sound
					switch (MenuConfig::HitSound)
					{
					case 1:
						PlaySoundA(reinterpret_cast<char*>(neverlose_sound), NULL, SND_ASYNC | SND_MEMORY);
						break;
					case 2:
						PlaySoundA(reinterpret_cast<char*>(skeet_sound), NULL, SND_ASYNC | SND_MEMORY);
						break;
					case 3:
						PlaySoundA(reinterpret_cast<char*>(Fuck), NULL, SND_ASYNC | SND_MEMORY);
						break;
					case 4:
						PlaySoundA(reinterpret_cast<char*>(Senpai), NULL, SND_ASYNC | SND_MEMORY);
						break;
					default:
						break;
					}

				}
			}
			PreviousTotalHits = totalHits;
		}

		// Update Hit Marker
		if (hitmarker.alpha > 0.f)
		{
			// std::cout << hitmarker.alpha << std::endl;
			auto now = std::chrono::steady_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - hitmarker.startTime).count();
			if (duration >= 500.f)
				hitmarker.alpha = 0;
			else
				hitmarker.alpha = 1.f - duration / 500.f;
		}
	}

	void HitMarker(float Size, float Gap)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImVec2 center = ImVec2(Gui.Window.Size.x / 2, Gui.Window.Size.y / 2);

		if (hitmarker.alpha > 0.f)
		{
			ImColor col = ImColor(255.f, 255.f, 255.f, hitmarker.alpha);

			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(center.x - Size, center.y - Size), ImVec2(center.x - Gap, center.y - Gap), col & IM_COL32_A_MASK, 2.4f);
			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(center.x - Size, center.y + Size), ImVec2(center.x - Gap, center.y + Gap), col & IM_COL32_A_MASK, 2.4f);
			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(center.x + Size, center.y - Size), ImVec2(center.x + Gap, center.y - Gap), col & IM_COL32_A_MASK, 2.4f);
			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(center.x + Size, center.y + Size), ImVec2(center.x + Gap, center.y + Gap), col & IM_COL32_A_MASK, 2.4f);
			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(center.x - Size, center.y - Size), ImVec2(center.x - Gap, center.y - Gap), col, 1.4f);
			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(center.x - Size, center.y + Size), ImVec2(center.x - Gap, center.y + Gap), col, 1.4f);
			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(center.x + Size, center.y - Size), ImVec2(center.x + Gap, center.y - Gap), col, 1.4f);
			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(center.x + Size, center.y + Size), ImVec2(center.x + Gap, center.y + Gap), col, 1.4f);
		}
	}
	/*void RadarHack(const CEntity& EntityList) noexcept
	{
		

		if (!MenuConfig::RadarHack)
			return;

		bool SpottedStatus = true;
		ProcessMgr.WriteMemory(EntityList.Pawn.Address + Offset::Pawn.bSpottedByMask, SpottedStatus);
	}*/
	void FastStop() noexcept
	{
		if (!MenuConfig::FastStop)
			return;
		// Disable when bhopping
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
			return;
		// Disable when slow walking
		if (GetAsyncKeyState(VK_LSHIFT) & 0x8000)
			return;

		Misc::StopKeyEvent('A', &aKeyPressed, 'D', 50.f);
		Misc::StopKeyEvent('D', &dKeyPressed, 'A', 50.f);
		Misc::StopKeyEvent('W', &wKeyPressed, 'S', 50.f);
		Misc::StopKeyEvent('S', &sKeyPressed, 'W', 50.f);
	}
}
