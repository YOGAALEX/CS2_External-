#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <chrono>
#include <map>
#include "Entity.h"
#include "Utils/Format.hpp"

namespace Render
{
	void DrawFovCircle()
	{
		Vec2 CenterPoint = Gui.Window.Size / 2;

		// 添加修正系数，例如1.05来调整半径
		float CorrectionFactor = 0.80f; // 根据需要调整这个系数
		float Radius = tan(AimControl::AimFov / 180.f * M_PI / 2.f) * Gui.Window.Size.x * CorrectionFactor;

		Gui.Circle(CenterPoint, Radius, MenuConfig::AimFovRangeColor, 1);
	}

	void DrawCrossHair()
	{ 
		Vec2 SightPos = Gui.Window.Size / 2;
		Gui.Line({ SightPos.x - MenuConfig::CrossHairSize,SightPos.y }, { SightPos.x + MenuConfig::CrossHairSize,SightPos.y }, MenuConfig::CrossHairColor, 1);
		Gui.Line({ SightPos.x,SightPos.y - MenuConfig::CrossHairSize }, { SightPos.x ,SightPos.y + MenuConfig::CrossHairSize }, MenuConfig::CrossHairColor, 1);
	}

	void LineToEnemy(ImVec4 Rect, ImColor Color, float Thickness)
	{
		Gui.Line({ Rect.x + Rect.z / 2,Rect.y }, { Gui.Window.Size.x / 2,0 }, Color, Thickness);
	}

	void DrawFov(const CEntity& LocalEntity, float Size, ImColor Color, float Thickness)
	{
		float Length;
		float radian;
		Vec2 LineEndPoint[2];
		Vec2 Pos = Gui.Window.Size / 2;

		radian = (LocalEntity.Pawn.Fov / 2) * M_PI / 180;

		LineEndPoint[0].y = Pos.y - Size;
		LineEndPoint[1].y = LineEndPoint[0].y;

		Length = Size * tan(radian);

		LineEndPoint[0].x = Pos.x - Length;
		LineEndPoint[1].x = Pos.x + Length;

		Gui.Line(Pos, LineEndPoint[0], Color, 1.5);
		Gui.Line(Pos, LineEndPoint[1], Color, 1.5);
	}

	void DrawDistance(const CEntity& LocalEntity, CEntity& Entity, ImVec4 Rect)
	{
		int distance = static_cast<int>(Entity.Pawn.Pos.DistanceTo(LocalEntity.Pawn.Pos) / 100);
		std::string dis_str = Format("%im", distance);
		Gui.StrokeText(dis_str, { Rect.x + Rect.z + 4, Rect.y }, MenuConfig::DistanceColor, 16, false);
	}

	void HeadShootLine(const CEntity& LocalEntity, ImColor Color)
	{
		Vec2 Pos;
		Pos.x = Gui.Window.Size.x / 2;
		Pos.y = Gui.Window.Size.y / 2.0f - Gui.Window.Size.y / (2.0f * std::sin(LocalEntity.Pawn.Fov * M_PI / 180.0f) / std::sin(90.0f * M_PI / 180.0f)) * std::sin(LocalEntity.Pawn.ViewAngle.x * M_PI / 180.0f) / std::sin(90.0f * M_PI / 180.0f);

		// left
		Gui.RectangleFilled(Vec2{ Pos.x - 21, Pos.y - 1 }, Vec2{ 17, 3}, Color & IM_COL32_A_MASK);
		Gui.RectangleFilled(Vec2{ Pos.x - 20, Pos.y }, Vec2{ 17, 3 }, Color);

		// right
		Gui.RectangleFilled(Vec2{ Pos.x + 5, Pos.y - 1 }, Vec2{ 17, 3 }, Color & IM_COL32_A_MASK);
		Gui.RectangleFilled(Vec2{ Pos.x + 6, Pos.y }, Vec2{ 17, 3 }, Color);
	}

	//// 方框绘制  有问题
	//ImVec4 Get2DBox(const CEntity& Entity)
	//{
	//	BoneJointPos Head = Entity.GetBone().BonePosList[BONEINDEX::head];
	//	
	//	Vec2 Size, Pos;
	//	Size.y = (Entity.Pawn.ScreenPos.y - Head.ScreenPos.y) * 1.09;
	//	Size.x = Size.y * 0.6;

	//	Pos = ImVec2(Entity.Pawn.ScreenPos.x - Size.x / 2, Head.ScreenPos.y- Size.y*0.08);

	//	return ImVec4{ Pos.x,Pos.y,Size.x,Size.y };

	//	
	//}

	ImVec4 Get2DBox(CEntity& Entity)
	{
		const float FixedPlayerHeight = 75.0f;
		Vec3 TopPos3D;

		TopPos3D = Entity.Pawn.Pos;
		TopPos3D.z += FixedPlayerHeight;

		Vec2 GroundPos2D, TopPos2D;
		if (!gGame.View.WorldToScreen(Entity.Pawn.Pos, GroundPos2D) || !gGame.View.WorldToScreen(TopPos3D, TopPos2D))
			return ImVec4{ 0.0f, 0.0f, 0.0f, 0.0f };

		if (TopPos2D.y < 0.0f || GroundPos2D.y > ImGui::GetIO().DisplaySize.y)
			return ImVec4{ 0.0f, 0.0f, 0.0f, 0.0f };


		Vec2 Size, Pos;
		Size.y = std::abs(TopPos2D.y - GroundPos2D.y);
		Size.x = Size.y * 0.60;

		Pos.x = GroundPos2D.x - Size.x / 2;
		Pos.y = TopPos2D.y;

		return ImVec4{ Pos.x, Pos.y, Size.x, Size.y };
	}

	//// 骨骼绘制  有问题
	//void DrawBone(const CEntity& Entity, ImColor Color, float Thickness)
	//{
	//	BoneJointPos Previous, Current;
	//	for (auto i : BoneJointList::List)
	//	{
	//		Previous.Pos = Vec3(0, 0, 0);
	//		for (auto Index : i)
	//		{
	//			Current = Entity.GetBone().BonePosList[Index];
	//			if (Previous.Pos == Vec3(0, 0, 0))
	//			{
	//				Previous = Current;
	//				//pGame->View->Gui->Text(Current.Name.c_str(), Current.ScreenPos, ImColor(255, 255, 0, 255));
	//				continue;
	//			}
	//			if (Previous.IsVisible && Current.IsVisible)
	//			{
	//				Gui.Line(Previous.ScreenPos, Current.ScreenPos, Color, Thickness);
	//				//pGame->View->Gui->Text(Current.Name.c_str(), Current.ScreenPos, ImColor(255, 255, 0, 255));
	//			}
	//			Previous = Current;
	//		}
	//	}
	//}
	// 
	//void DrawBone(CEntity& Entity, ImColor Color, float Thickness)
	//{
	//	ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
	//	Vec3 EntityPos = Entity.Pawn.Pos;
	//	Vec3 BonePos27 = Entity.GetBone().BonePosList[27].Pos;

	//	float MaxDistance = 45.0f;
	//	float DistanceToBone27 = sqrt(
	//		pow(BonePos27.x - EntityPos.x, 2) +
	//		pow(BonePos27.y - EntityPos.y, 2) +
	//		pow(BonePos27.z - EntityPos.z, 2)
	//	);

	//	if (DistanceToBone27 > MaxDistance)
	//		return;

	//	for (const auto& boneList : BoneJointList::List)
	//	{
	//		BoneJointPos Previous;
	//		bool isFirstBone = true;
	//		for (const auto& Index : boneList)
	//		{
	//			BoneJointPos Current = Entity.GetBone().BonePosList[Index];
	//			if (!isFirstBone && Previous.IsVisible && Current.IsVisible)
	//			{
	//				draw_list->AddLine(
	//					ImVec2(Previous.ScreenPos.x, Previous.ScreenPos.y),
	//					ImVec2(Current.ScreenPos.x, Current.ScreenPos.y),
	//					Color, Thickness
	//				);
	//			}


	//			Vec3 HeadPos = Entity.GetBone().BonePosList[BoneJointList::List.front().front()].Pos;
	//			float SquaredDistanceToHead = pow(HeadPos.x - LocalController.vOldOrigin.x, 2) +
	//				pow(HeadPos.y - LocalController.vOldOrigin.y, 2) +
	//				pow(HeadPos.z - LocalController.vOldOrigin.z, 2);

	//			float DistanceToHead = sqrt(SquaredDistanceToHead) * 0.0254f;

	//			if (DistanceToHead < 35.0f)
	//			{

	//				if (Index == BONEINDEX::head && Current.IsVisible)
	//				{
	//					BoneJointPos Head = Entity.GetBone().BonePosList[BoneJointList::List.front().front()];
	//					draw_list->AddCircle(
	//						ImVec2(Head.ScreenPos.x, Head.ScreenPos.y - 6.5f),
	//						9.0f, Color, 12, Thickness
	//					);
	//				}

	//			}

	//			isFirstBone = false;
	//			Previous = Current;
	//		}
	//	}
	//}

	//  无问题
	void DrawBone(CEntity& Entity, CEntity& LocalEntity, ImColor Color, float Thickness)
	{
		ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
		Vec3 EntityPos = Entity.Pawn.Pos;
		Vec3 BonePos27 = Entity.GetBone().BonePosList[27].Pos;

		float MaxDistance = 45.0f;
		float DistanceToBone27 = sqrt(
			pow(BonePos27.x - EntityPos.x, 2) +
			pow(BonePos27.y - EntityPos.y, 2) +
			pow(BonePos27.z - EntityPos.z, 2)
		);

		if (DistanceToBone27 > MaxDistance)
			return;

		for (const auto& boneList : BoneJointList::List)
		{
			BoneJointPos Previous;
			bool isFirstBone = true;
			for (const auto& Index : boneList)
			{
				BoneJointPos Current = Entity.GetBone().BonePosList[Index];
				if (!isFirstBone && Previous.IsVisible && Current.IsVisible)
				{
					draw_list->AddLine(
						ImVec2(Previous.ScreenPos.x, Previous.ScreenPos.y),
						ImVec2(Current.ScreenPos.x, Current.ScreenPos.y),
						Color, Thickness
					);
				}


				Vec3 HeadPos = Entity.GetBone().BonePosList[BoneJointList::List.front().front()].Pos;
				float SquaredDistanceToHead = pow(HeadPos.x - LocalEntity.Pawn.Pos.x, 2) +
					pow(HeadPos.y - LocalEntity.Pawn.Pos.y, 2) +
					pow(HeadPos.z - LocalEntity.Pawn.Pos.z, 2);

				float DistanceToHead = sqrt(SquaredDistanceToHead) * 0.0254f;

				if (DistanceToHead < 35.0f)
				{

					if (Index == BONEINDEX::head && Current.IsVisible)
					{
						BoneJointPos Head = Entity.GetBone().BonePosList[BoneJointList::List.front().front()];
						draw_list->AddCircle(
							ImVec2(Head.ScreenPos.x, Head.ScreenPos.y - 6.5f),
							9.0f, Color, 12, Thickness
						);
					}

				}

				isFirstBone = false;
				Previous = Current;
			}
		}
	}

	// 朝向绘制
	void ShowLosLine(const CEntity& Entity, const float Length, ImColor Color, float Thickness)
	{
		Vec2 StartPoint, EndPoint;
		Vec3 Temp;
		BoneJointPos Head = Entity.GetBone().BonePosList[BONEINDEX::head];

		StartPoint = Head.ScreenPos;

		float LineLength = cos(Entity.Pawn.ViewAngle.x * M_PI / 180) * Length;

		Temp.x = Head.Pos.x + cos(Entity.Pawn.ViewAngle.y * M_PI / 180) * LineLength;
		Temp.y = Head.Pos.y + sin(Entity.Pawn.ViewAngle.y * M_PI / 180) * LineLength;
		Temp.z = Head.Pos.z - sin(Entity.Pawn.ViewAngle.x * M_PI / 180) * Length;

		if (!gGame.View.WorldToScreen(Temp, EndPoint))
			return;

		Gui.Line(StartPoint, EndPoint, Color, Thickness);
	}

	// 2D骨骼框绘制
	ImVec4 Get2DBoneRect(const CEntity& Entity)
	{
		Vec2 Min, Max, Size;
		Min = Max = Entity.GetBone().BonePosList[0].ScreenPos;

		for (auto &BoneJoint : Entity.GetBone().BonePosList)
		{
			if (!BoneJoint.IsVisible)
				continue;
			Min.x = min(BoneJoint.ScreenPos.x, Min.x);
			Min.y = min(BoneJoint.ScreenPos.y, Min.y);
			Max.x = max(BoneJoint.ScreenPos.x, Max.x);
			Max.y = max(BoneJoint.ScreenPos.y, Max.y);
		}
		Size.x = Max.x - Min.x;
		Size.y = Max.y - Min.y;

		return ImVec4(Min.x, Min.y, Size.x, Size.y);
	}

	class HealthBar
	{
	private:
		using TimePoint_ = std::chrono::steady_clock::time_point;
	private:
		// 显示备份血条时间(ms)
		const int ShowBackUpHealthDuration = 500;
		// 最大血量
		float MaxHealth = 0.f;
		// 当前血量
		float CurrentHealth = 0.f;
		// 最近备份血量大小
		float LastestBackupHealth = 0.f;
		// 血条坐标
		ImVec2 RectPos{};
		// 血条大小
		ImVec2 RectSize{};
		// 正在显示备份血量
		bool InShowBackupHealth = false;
		// 显示备份血量起始时间戳
		TimePoint_ BackupHealthTimePoint{};
	public:
		HealthBar() {}
		// 横向
		void DrawHealthBar_Horizontal(float MaxHealth, float CurrentHealth, ImVec2 Pos, ImVec2 Size);
		// 纵向
		void DrawHealthBar_Vertical(float MaxHealth, float CurrentHealth, ImVec2 Pos, ImVec2 Size);
	private:
		// 颜色缓动
		ImColor Mix(ImColor Col_1, ImColor Col_2, float t);
		// 第一阶段血条颜色 0.5-1
		ImColor FirstStageColor = ImColor(96, 246, 113, 220);
		// 第二阶段血条颜色 0.5-0.2
		ImColor SecondStageColor = ImColor(247, 214, 103, 220);
		// 第三阶段血条颜色 0.2-0.0
		ImColor ThirdStageColor = ImColor(255, 95, 95, 220);
		// 备份血条颜色
		ImColor BackupHealthColor = ImColor(255, 255, 255, 220);
		// 边框颜色
		ImColor FrameColor = ImColor(45, 45, 45, 220);
		// 背景颜色
		ImColor BackGroundColor = ImColor(90, 90, 90, 220);
	};

	void HealthBar::DrawHealthBar_Horizontal(float MaxHealth, float CurrentHealth, ImVec2 Pos, ImVec2 Size)
	{
		auto InRange = [&](float value, float min, float max) -> bool
		{
			return value > min && value <= max;
		};

		ImDrawList* DrawList = ImGui::GetBackgroundDrawList();

		this->MaxHealth = MaxHealth;
		this->CurrentHealth = CurrentHealth;
		this->RectPos = Pos;
		this->RectSize = Size;

		// 占比
		float Proportion = CurrentHealth / MaxHealth;
		// 血量条宽度
		float Width = RectSize.x * Proportion;
		// 血量条颜色
		ImColor Color;

		// 背景
		DrawList->AddRectFilled(RectPos,
			{ RectPos.x + RectSize.x,RectPos.y + RectSize.y },
			BackGroundColor, 5, 15);

		// 颜色切换
		float Color_Lerp_t = pow(Proportion, 2.5);
		if (InRange(Proportion, 0.5, 1))
			Color = Mix(FirstStageColor, SecondStageColor, Color_Lerp_t * 3 - 1);
		else
			Color = Mix(SecondStageColor, ThirdStageColor, Color_Lerp_t * 4);

		// 更新最近备份血量
		if (LastestBackupHealth == 0
			|| LastestBackupHealth < CurrentHealth)
			LastestBackupHealth = CurrentHealth;

		if (LastestBackupHealth != CurrentHealth)
		{
			if (!InShowBackupHealth)
			{
				BackupHealthTimePoint = std::chrono::steady_clock::now();
				InShowBackupHealth = true;
			}

			std::chrono::steady_clock::time_point CurrentTime = std::chrono::steady_clock::now();
			if (CurrentTime - BackupHealthTimePoint > std::chrono::milliseconds(ShowBackUpHealthDuration))
			{
				// 超时就停止显示备份血量，并且更新最近备份血量
				LastestBackupHealth = CurrentHealth;
				InShowBackupHealth = false;
			}

			if (InShowBackupHealth)
			{
				// 备份血量绘制宽度
				float BackupHealthWidth = LastestBackupHealth / MaxHealth * RectSize.x;
				// 备份血量alpha渐变
				float BackupHealthColorAlpha = 1 - 0.95 * (std::chrono::duration_cast<std::chrono::milliseconds>(CurrentTime - BackupHealthTimePoint).count() / (float)ShowBackUpHealthDuration);
				ImColor BackupHealthColorTemp = BackupHealthColor;
				BackupHealthColorTemp.Value.w = BackupHealthColorAlpha;
				// 备份血量宽度缓动
				float BackupHealthWidth_Lerp = 1 * (std::chrono::duration_cast<std::chrono::milliseconds>(CurrentTime - BackupHealthTimePoint).count() / (float)ShowBackUpHealthDuration);
				BackupHealthWidth_Lerp *= (BackupHealthWidth - Width);
				BackupHealthWidth -= BackupHealthWidth_Lerp;
				// 备份血条
				DrawList->AddRectFilled(RectPos,
					{ RectPos.x + BackupHealthWidth,RectPos.y + RectSize.y },
					BackupHealthColorTemp, 5);
			}
		}

		// 血条
		DrawList->AddRectFilled(RectPos,
			{ RectPos.x + Width,RectPos.y + RectSize.y },
			Color, 5);

		// 边框
		DrawList->AddRect(RectPos,
			{ RectPos.x + RectSize.x,RectPos.y + RectSize.y },
			FrameColor, 5, 15, 1);
	}

	void HealthBar::DrawHealthBar_Vertical(float MaxHealth, float CurrentHealth, ImVec2 Pos, ImVec2 Size)
	{
		auto InRange = [&](float value, float min, float max) -> bool
		{
			return value > min && value <= max;
		};

		ImDrawList* DrawList = ImGui::GetBackgroundDrawList();

		this->MaxHealth = MaxHealth;
		this->CurrentHealth = CurrentHealth;
		this->RectPos = Pos;
		this->RectSize = Size;

		// 占比
		float Proportion = CurrentHealth / MaxHealth;
		// 血量条高度
		float Height = RectSize.y * Proportion;
		// 血量条颜色
		ImColor Color;

		// 背景
		DrawList->AddRectFilled(RectPos,
			{ RectPos.x + RectSize.x,RectPos.y + RectSize.y },
			BackGroundColor, 5, 15);

		// 颜色切换
		float Color_Lerp_t = pow(Proportion, 2.5);
		if (InRange(Proportion, 0.5, 1))
			Color = Mix(FirstStageColor, SecondStageColor, Color_Lerp_t * 3 - 1);
		else
			Color = Mix(SecondStageColor, ThirdStageColor, Color_Lerp_t * 4);

		// 更新最近备份血量
		if (LastestBackupHealth == 0
			|| LastestBackupHealth < CurrentHealth)
			LastestBackupHealth = CurrentHealth;

		if (LastestBackupHealth != CurrentHealth)
		{
			if (!InShowBackupHealth)
			{
				BackupHealthTimePoint = std::chrono::steady_clock::now();
				InShowBackupHealth = true;
			}

			std::chrono::steady_clock::time_point CurrentTime = std::chrono::steady_clock::now();
			if (CurrentTime - BackupHealthTimePoint > std::chrono::milliseconds(ShowBackUpHealthDuration))
			{
				// 超时就停止显示备份血量，并且更新最近备份血量
				LastestBackupHealth = CurrentHealth;
				InShowBackupHealth = false;
			}

			if (InShowBackupHealth)
			{
				// 备份血量绘制高度
				float BackupHealthHeight = LastestBackupHealth / MaxHealth * RectSize.y;
				// 备份血量alpha渐变
				float BackupHealthColorAlpha = 1 - 0.95 * (std::chrono::duration_cast<std::chrono::milliseconds>(CurrentTime - BackupHealthTimePoint).count() / (float)ShowBackUpHealthDuration);
				ImColor BackupHealthColorTemp = BackupHealthColor;
				BackupHealthColorTemp.Value.w = BackupHealthColorAlpha;
				// 备份血量高度缓动
				float BackupHealthHeight_Lerp = 1 * (std::chrono::duration_cast<std::chrono::milliseconds>(CurrentTime - BackupHealthTimePoint).count() / (float)ShowBackUpHealthDuration);
				BackupHealthHeight_Lerp *= (BackupHealthHeight - Height);
				BackupHealthHeight -= BackupHealthHeight_Lerp;
				// 备份血条
				DrawList->AddRectFilled({ RectPos.x,RectPos.y + RectSize.y - BackupHealthHeight },
					{ RectPos.x + RectSize.x,RectPos.y + RectSize.y },
					BackupHealthColorTemp, 5);
			}
		}

		// 血条
		DrawList->AddRectFilled({ RectPos.x,RectPos.y + RectSize.y - Height },
			{ RectPos.x + RectSize.x,RectPos.y + RectSize.y },
			Color, 5);

		// 边框
		DrawList->AddRect(RectPos,
			{ RectPos.x + RectSize.x,RectPos.y + RectSize.y },
			FrameColor, 5, 15, 1);
	}

	ImColor HealthBar::Mix(ImColor Col_1, ImColor Col_2, float t)
	{
		ImColor Col;
		Col.Value.x = t * Col_1.Value.x + (1 - t) * Col_2.Value.x;
		Col.Value.y = t * Col_1.Value.y + (1 - t) * Col_2.Value.y;
		Col.Value.z = t * Col_1.Value.z + (1 - t) * Col_2.Value.z;
		Col.Value.w = Col_1.Value.w;
		return Col;
	}

	// Sign可用任何类型敌人标识，默认可传敌人地址
	void DrawHealthBar(DWORD Sign, float MaxHealth, float CurrentHealth, ImVec2 Pos, ImVec2 Size, bool Horizontal)
	{
		static std::map<DWORD, HealthBar> HealthBarMap;
		if (!HealthBarMap.count(Sign))
		{
			HealthBarMap.insert({ Sign,HealthBar() });
		}
		if (HealthBarMap.count(Sign))
		{
			if (Horizontal)
				HealthBarMap[Sign].DrawHealthBar_Horizontal(MaxHealth, CurrentHealth, Pos, Size);
			else
				HealthBarMap[Sign].DrawHealthBar_Vertical(MaxHealth, CurrentHealth, Pos, Size);
		}
	}

}
