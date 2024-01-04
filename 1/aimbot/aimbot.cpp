#include "aimbot.h"
#include <thread>
#include <chrono>
#include "../sdk/vectorh.h"
#include <iostream>
#include "natives.hpp"
#include "../Hotkey/hotkey.h"
i_aim& i_aim::aim()
{
	static i_aim ins;
	return ins;
}

uintptr_t i_aim::BestTarget()
{
	uintptr_t ClosestPlayer = 0;
	uintptr_t ReplayInterface = i_dupa::chu().i_replay;
	uintptr_t localplayer = i_dupa::chu().i_localplayer;
	float crosshair_dist;
	float closestdist = FLT_MAX;
	float dist;
	if (ReplayInterface)
	{
		uintptr_t PedReplayInterface = i_memory::reeq().Read<DWORD64>(ReplayInterface + 0x18);
		uintptr_t PedList = i_memory::reeq().Read<DWORD64>(PedReplayInterface + 0x100);
		int entitylist = i_memory::reeq().Read<int>(PedReplayInterface + 0x108);

		for (int i = 0U; i < entitylist; i++)
		{
			if (!PedList) continue;

			uintptr_t Ped = i_memory::reeq().Read<uintptr_t>(PedList + (i * 0x10));
			if (!Ped) continue;
			uint64_t playerinfos = i_memory::reeq().Read<uint64_t>(Ped + i_dupa::chu().playerinfo);
			int playeridaddr = i_memory::reeq().Read<int>(playerinfos + 0x88);
			std::string playeridstr = std::to_string(playeridaddr);
			auto it = std::find(i_esp::esp().friends.begin(), i_esp::esp().friends.end(), playeridstr);
			if (!targetfriend)
			{
				if (it != i_esp::esp().friends.end())
					continue; 
			}
			if (Ped == localplayer) continue;

			if (ignoreped)
			{
				if (!i_memory::reeq().Read<uintptr_t>(Ped + i_dupa::chu().playerinfo))
					continue;
			}


			float HealthPed = i_memory::reeq().Read<float>(Ped + 0x280);

			if (ignoredeath)
			{
				if (HealthPed == 0)
					continue;
			}

			if (ignoredown)
			{
				if (HealthPed == 150)
					continue;
			}

			D3DXVECTOR3 GetCordLocal= i_memory::reeq().Read<D3DXVECTOR3>(localplayer + 0x90);
			D3DXVECTOR3 GetCordPed = i_memory::reeq().Read<D3DXVECTOR3>(Ped + 0x90);
			D3DXVECTOR3 DistanceCalculation = (GetCordLocal - GetCordPed);
			double Distance = sqrtf(DistanceCalculation.x * DistanceCalculation.x + DistanceCalculation.y * DistanceCalculation.y + DistanceCalculation.z * DistanceCalculation.z);
			auto iop = i_sdk::sdk().get_bone_position(Ped, 0);
			D3DXVECTOR2 Head = i_sdk::sdk().world_to_screen(iop);
			float best_dist = FLT_MAX;
			float x = Head.x - GetSystemMetrics(SM_CXSCREEN) / 2.f;
			float y = Head.y - GetSystemMetrics(SM_CYSCREEN) / 2.f;
			crosshair_dist = sqrtf((x * x) + (y * y));


			if (Distance <= distance)
			{
				if (crosshair_dist < closestdist) {


					closestdist = crosshair_dist;
					ClosestPlayer = Ped;
				}
			}
		}
		return ClosestPlayer;
	}
}

uintptr_t GetDistancePlayer()
{
	uintptr_t ClosestPlayer = 0;
	float closestdist = FLT_MAX;
	float dist;
	hk_World* World = (hk_World*)*(uint64_t*)(FiveM::World);
	if (!World)
		return NULL;

	hk_Ped* LocalPlayer = World->LocalPlayer();
	if (!LocalPlayer)
		return NULL;

	hk_ReplayInterface* ReplayInterface = (hk_ReplayInterface*)*(uint64_t*)(FiveM::ReplayInterface);
	if (!ReplayInterface)
		return NULL;

	hk_PedInterface* PedInterface = ReplayInterface->PedInterface();
	if (!PedInterface)
		return NULL;

	for (int index = 0; index < PedInterface->PedMaximum(); index++)
	{
		hk_Ped* Peds = PedInterface->PedList()->Ped(index);
		if (!Peds) continue;


		if (i_aim::aim().ignoreped)
		{

			auto ped_type = Peds->GetPedType();
			if (!ped_type) continue;
			ped_type = ped_type << 11 >> 25;


			if (ped_type != 2) {
				continue;
			}
		}

		if (Peds == LocalPlayer) continue;

		if (Peds->GetHealth() <= 0) continue;

		Vector3 DistanceCalculation = (LocalPlayer->GetCoordinate() - Peds->GetCoordinate());
		double Distance = sqrtf(DistanceCalculation.x * DistanceCalculation.x + DistanceCalculation.y * DistanceCalculation.y + DistanceCalculation.z * DistanceCalculation.z);







		if (Distance <= i_aim::aim().sildistance)
		{
			ImVec2 PedPos = FiveM::WorldToScreen(Peds->GetCoordinate());

			ImVec2 Head = FiveM::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds), 0x796e);
			if (!IsOnScreen(Head)) continue;

			ImVec2 middle = ImVec2(FiveM::WindowSize.x / 2, FiveM::WindowSize.y / 2);
			dist = FiveM::pythag(middle, Head);

			if (dist < closestdist)
			{
				{


					closestdist = dist;
					ClosestPlayer = reinterpret_cast<uint64_t>(Peds);


				}
			}

		}
	}
	return ClosestPlayer;
}


void i_aim::aimbot(uintptr_t Ped)
{
	auto get_distance = [](double x1, double y1, double x2, double y2) {
		return sqrtf(pow(x2 - x1, 2.0) + pow(y2 - y1, 2.0));
	};
	int bones;
	if (boneid == 0)
	{
		bones = 0;
	}
	if (boneid == 1)
	{
		bones = 1;
	}

	auto bone_pos = i_sdk::sdk().get_bone_position(Ped, bones);
	D3DXVECTOR2 screen = i_sdk::sdk().world_to_screen(bone_pos);

	if (screen == D3DXVECTOR2(0, 0))
		return;


	auto center_x = GetSystemMetrics(SM_CXSCREEN) / 2;
	auto center_y = GetSystemMetrics(SM_CYSCREEN) / 2;
	auto fov1 = get_distance(center_x, center_y, screen.x, screen.y);

	float TargetX = 0;
	float TargetY = 0;

	if (screen.x != 0) {
		if (screen.x > center_x) {
			TargetX = -(center_x - screen.x);
			TargetX /= smooth - 0.5;
			if (TargetX + center_x > center_x * 2) TargetX = 0;
		}

		if (screen.x < center_x) {
			TargetX = screen.x - center_x;
			TargetX /= smooth - 0.5;
			if (TargetX + center_x < 0) TargetX = 0;
		}
	}

	if (screen.y != 0) {
		if (screen.y > center_y) {
			TargetY = -(center_y - screen.y);
			TargetY /= smooth - 0.5;
			if (TargetY + center_y > center_y * 2) TargetY = 0;
		}

		if (screen.y < center_y) {
			TargetY = screen.y - center_y;
			TargetY /= smooth - 0.5;
			if (TargetY + center_y < 0) TargetY = 0;
		}
	}

	if (fov1 < fov)
	{
		if ((GetAsyncKeyState)(Hotkey::hot().Aimbotkey) & 0x8000) {

			mouse_event(MOUSEEVENTF_MOVE, float(TargetX), float(TargetY), 0, 0);


		}
	}
}

void i_aim::MemoryAim(uintptr_t Ped)
{
	auto get_distance = [](double x1, double y1, double x2, double y2) {
		return sqrtf(pow(x2 - x1, 2.0) + pow(y2 - y1, 2.0));
		};
	int bones;
	if (boneid == 0)
	{
		bones = 0;
	}
	if (boneid == 1)
	{
		bones = 1;
	}

	auto bone_pos = i_sdk::sdk().get_bone_position(Ped, bones);
	D3DXVECTOR2 screen = i_sdk::sdk().world_to_screen(bone_pos);

	if (screen == D3DXVECTOR2(0, 0))
		return;


	auto center_x = GetSystemMetrics(SM_CXSCREEN) / 2;
	auto center_y = GetSystemMetrics(SM_CYSCREEN) / 2;
	auto fov1 = get_distance(center_x, center_y, screen.x, screen.y);

	float TargetX = 0;
	float TargetY = 0;

	if (screen.x != 0) {
		if (screen.x > center_x) {
			TargetX = -(center_x - screen.x);
			TargetX /= smooth - 0.5;
			if (TargetX + center_x > center_x * 2) TargetX = 0;
		}

		if (screen.x < center_x) {
			TargetX = screen.x - center_x;
			TargetX /= smooth - 0.5;
			if (TargetX + center_x < 0) TargetX = 0;
		}
	}

	if (screen.y != 0) {
		if (screen.y > center_y) {
			TargetY = -(center_y - screen.y);
			TargetY /= smooth - 0.5;
			if (TargetY + center_y > center_y * 2) TargetY = 0;
		}

		if (screen.y < center_y) {
			TargetY = screen.y - center_y;
			TargetY /= smooth - 0.5;
			if (TargetY + center_y < 0) TargetY = 0;
		}
	}

	if (fov1 < fov)
	{
		if ((GetAsyncKeyState)(Hotkey::hot().Aimbotkey) & 0x8000) {

			mouse_event(MOUSEEVENTF_MOVE, float(TargetX), float(TargetY), 0, 0);


		}
	}

}

PVector3 ToPVector3(Vector3 pVec)
{
	return PVector3(pVec.x, pVec.y, pVec.z);
}

Vector3 ToVector3(PVector3 pVec)
{
	return Vector3(pVec.x, pVec.y, pVec.z);
}
DWORD64 TICKS = GetTickCount64();

void i_aim::silent(uintptr_t Ped)
{
	auto player = PLAYER::PLAYER_PED_ID();
	auto WeaponHash = WEAPON::GET_SELECTED_PED_WEAPON(player);
	auto WeaponDamage = WEAPON::GET_WEAPON_DAMAGE(WeaponHash, NULL);

	if (silentfov)
	{
		auto get_distance = [](double x1, double y1, double x2, double y2) {
			return sqrtf(pow(x2 - x1, 2.0) + pow(y2 - y1, 2.0));
			};
		hk_Ped* PedCC = (hk_Ped*)GetDistancePlayer();
		if (!PedCC) return;
		ImVec2 screen = FiveM::WorldToScreen(PedCC->GetCoordinate());

		auto center_x = FiveM::WindowSize.x / 2;
		auto center_y = FiveM::WindowSize.y / 2;
		auto fov = get_distance(center_x, center_y, screen.x, screen.y);
		if (fov < i_aim::aim().silentfov)
			return;

	}


	if (GetDistancePlayer() != NULL && PED::IS_PED_SHOOTING(player))
	{

		if (!i_aim::aim().aimenableMagic)
		{
			if (GetTickCount64() - TICKS > 450.f)
			{

				hk_Ped* PedC = (hk_Ped*)GetDistancePlayer();
				if (!PedC) return;
				auto InPut = ENTITY::GET_ENTITY_COORDS(player, (bool)true);

				auto Out = ToPVector3(PedC->GetCoordinate());
				MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(InPut.x, InPut.y, InPut.z, Out.x, Out.y, Out.z, (int)WeaponDamage, false, WeaponHash, player, true, false, 3.f);
			}

		}
		else
		{

			if (GetTickCount64() - TICKS > 450.f)
			{

				hk_Ped* PedC = (hk_Ped*)GetDistancePlayer();
				if (!PedC) return;

				auto Out = ToPVector3(PedC->GetCoordinate());
				MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Out.x - 0.1, Out.y, Out.z, Out.x + 0.1, Out.y, Out.z, (int)WeaponDamage, false, WeaponHash, player, true, false, 3.f);
			}
		}
		TICKS = GetTickCount64();


	}

}


void AimVec(Vector3 point)
{
	//	auto draw_list = ImGui::GetBackgroundDrawList();
	DWORD64 addr = FiveM::GetCamera();
	if (addr)
	{
		Vector3 CrosshairPos = *(Vector3*)(addr + 0x60);
		Vector3 caca(CrosshairPos.x - point.x, CrosshairPos.y - point.y, CrosshairPos.z - point.z);
		float distance = caca.Length();

		__try
		{
			uint64_t CamData = *(DWORD64*)(addr + 0x10);
			if (CamData != NULL)
			{
				if (*(float*)(CamData + 0x130) == 8.0f)
				{
					*(float*)(CamData + 0x130) = 111.0f;
					*(float*)(CamData + 0x134) = 111.0f;
					*(float*)(CamData + 0x4CC) = 0.0f;

					if (*(float*)(CamData + 0x49C) == 1.0f)
						*(float*)(CamData + 0x49C) = 0.0f;

					*(float*)(CamData + 0x2AC) = 0.0f;
					*(float*)(CamData + 0x2B0) = 0.0f;
				}
			}
		}
		__except ((GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION) ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {}



		int smooth = 0;

		smooth = i_aim::aim().smooth + 1.5f;

		float threshold = 0.5f / (10 * 20);
		Vector3 Out = Vector3((point.x - CrosshairPos.x) / distance, (point.y - CrosshairPos.y) / distance, (point.z - CrosshairPos.z) / distance);

		if (smooth <= 1)
		{
			*(Vector3*)(addr + 0x40) = Out;  //FPS
			*(Vector3*)(addr + 0x3D0) = Out; //TPS
		}
		else
		{
			//First Person
			{
				Vector3 angles = *(Vector3*)(addr + 0x40);
				if (((Out.x - angles.x) > threshold) || ((angles.x - Out.x) > threshold))
				{
					if (angles.x > Out.x)
						*(float*)(addr + 0x40 + 0x0) -= threshold;
					else if (angles.x < Out.x)
						*(float*)(addr + 0x40 + 0x0) += threshold;
				}
				if (((Out.y - angles.y) > threshold) || ((angles.y - Out.y) > threshold))
				{
					if (angles.y > Out.y)
						*(float*)(addr + 0x40 + 0x4) -= threshold;
					else if (angles.y < Out.y)
						*(float*)(addr + 0x40 + 0x4) += threshold;
				}
				if (((Out.z - angles.z) > threshold) || ((angles.z - Out.z) > threshold))
				{
					if (angles.z > Out.z)
						*(float*)(addr + 0x40 + 0x8) -= threshold;
					else if (angles.z < Out.z)
						*(float*)(addr + 0x40 + 0x8) += threshold;
				}
			}
			//Third Person
			{
				Vector3 angles = *(Vector3*)(addr + 0x3D0);
				if (((Out.x - angles.x) > threshold) || ((angles.x - Out.x) > threshold))
				{
					if (angles.x > Out.x)
						*(float*)(addr + 0x3D0 + 0x0) -= threshold;
					else if (angles.x < Out.x)
						*(float*)(addr + 0x3D0 + 0x0) += threshold;
				}
				if (((Out.y - angles.y) > threshold) || ((angles.y - Out.y) > threshold))
				{
					if (angles.y > Out.y)
						*(float*)(addr + 0x3D0 + 0x4) -= threshold;
					else if (angles.y < Out.y)
						*(float*)(addr + 0x3D0 + 0x4) += threshold;
				}
				if (((Out.z - angles.z) > threshold) || ((angles.z - Out.z) > threshold))
				{
					if (angles.z > Out.z)
						*(float*)(addr + 0x3D0 + 0x8) -= threshold;
					else if (angles.z < Out.z)
						*(float*)(addr + 0x3D0 + 0x8) += threshold;
				}
			}
		}
	}
}


void i_aim::start()
{
	if (i_dupa::chu().i_localplayer)
	{
		if (aimenable)
		{
			if (aimbottype == 0)
			{
				if (i_aim::aim().BestTarget())
				{
					aimbot(BestTarget());
				}
			}
			if (aimbottype == 1)
			{
				if (i_aim::aim().BestTarget())
				{
					silent(BestTarget());
				}
			}
		}

		if (i_aim::aim().aimenableS)
		{
			if (i_aim::aim().BestTarget())
			{
				silent(BestTarget());
			}
		}

		if (i_aim::aim().aimenableMagic)
		{
			if (i_aim::aim().BestTarget())
			{
				silent(BestTarget());
			}
		}

		if (i_aim::aim().memory)
		{
			if (i_aim::aim().BestTarget())
			{
				MemoryAim(BestTarget());
			}
		}
		
	}
}