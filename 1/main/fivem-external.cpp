#include "fivem-external.h"
#include <iostream>
#include "../Hotkey/hotkey.h"


i_dupa& i_dupa::chu()
{
	static i_dupa ins;
	return ins;
}


void i_overlay::render()
{

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	i_aim::aim().start();
	i_esp::esp().start();
	i_exploits::exp().start();
	Hotkey::hot().start();

	bool dupanie = true;

	static auto FrameRate = 1.0f;
	struct tm ptm;
	FrameRate = ImGui::GetIO().Framerate;


	if (i_aim::aim().showfov)
	{
		//Normal
		ImGui::GetForegroundDrawList()->AddCircle(ImVec2(ScreenCenterX, ScreenCenterY), i_aim::aim().fov, i_esp::esp().FovColor, 12000, 2.f);
		//Silent
		//ImGui::GetForegroundDrawList()->AddCircle(ImVec2(ScreenCenterX, ScreenCenterY), i_aim::aim().silentfov, i_esp::esp().SilFovColor, 12000, 1.6f);
	}

	if (i_aim::aim().dupanie)
	{

		float oldfsize2 = ImGui::GetFont()->Scale;
		ImGui::PushFont(menuFnt);
		ImGui::GetFont()->Scale = 0.8;

		ImGui::PushFont(ImGui::GetFont());

		ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(5, 3), ImVec2(124, 6), ImColor(62, 62, 63, 255), 1.8f);
		ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(5, 5), ImVec2(124, 26), ImColor(2, 2, 5, 255), 1.8f);
		ImGui::GetForegroundDrawList()->AddText(ImVec2(10, 9), ImColor(255, 255, 255, 255), "Hus On Top");

		ImGui::PopFont();

		ImGui::GetFont()->Scale = oldfsize2;

	}


	if ((GetAsyncKeyState)(VK_F4) & 1)
	{
		showmenu = !showmenu;
	}

	if (showmenu)
	{
		menu();
		SetWindowLongA(MyWnd, GWL_EXSTYLE, WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);
			
	}
	else
	{
		SetWindowLongA(MyWnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);
	}
	
	ImGui::GetIO().MouseDrawCursor = showmenu;
	ImGui::GetIO().WantCaptureKeyboard = showmenu;
	ImGui::EndFrame();
	p_Device->SetRenderState(D3DRS_ZENABLE, false);
	p_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	p_Device->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
	p_Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

	if (p_Device->BeginScene() >= 0)
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		p_Device->EndScene();
	}

	HRESULT result = p_Device->Present(NULL, NULL, NULL, NULL);

	if (result == D3DERR_DEVICELOST && p_Device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
	{
		ImGui_ImplDX9_InvalidateDeviceObjects();
		p_Device->Reset(&d3dpp);
		ImGui_ImplDX9_CreateDeviceObjects();
	}
}

void i_dupa::logs()
{
	system("cls");
	std::cout << skCrypt("\n loaded !");
	std::cout << skCrypt("\n Default Menu Key: F4");
	
}




void i_dupa::start()
{

	i_memory::reeq().initialize();
	if (i_memory::reeq().find_build(L"FiveM_b2545_GTAProcess.exe"))
	{
		i_dupa::chu().isbuild2802 = false;
		i_memory::reeq().base = i_memory::reeq().get_base_address("FiveM_b2545_GTAProcess.exe");
		i_dupa::chu().i_world = i_memory::reeq().Read<uintptr_t>(i_memory::reeq().base + 0x25667E8);
		i_dupa::chu().i_replay = i_memory::reeq().Read<uintptr_t>(i_memory::reeq().base + 0x1F2E7A8);
		i_dupa::chu().i_viewport = i_memory::reeq().Read<uintptr_t>(i_memory::reeq().base + 0x1FD6F70);
		i_dupa::chu().i_camera = 0x1FD7B48;
		i_dupa::chu().i_veh = 0x0D30;
		i_dupa::chu().i_handling = 0x938;
		i_dupa::chu().i_enginehealth = 0x908;
		i_dupa::chu().i_localplayer = i_memory::reeq().Read<uintptr_t>(i_world + 0x8);
		playerinfo = 0x10C8;
		i_dupa::chu().logs();
		i_overlay::here().initialize();
	}
	else if (i_memory::reeq().find_build(L"FiveM_b2699_GTAProcess.exe"))
	{
		i_dupa::chu().isbuild2802 = false;
		i_memory::reeq().base = i_memory::reeq().get_base_address("FiveM_b2699_GTAProcess.exe");
		i_dupa::chu().i_world = i_memory::reeq().Read<uintptr_t>(i_memory::reeq().base + 0x26684D8);
		i_dupa::chu().i_replay = i_memory::reeq().Read<uintptr_t>(i_memory::reeq().base + 0x20304C8);
		i_dupa::chu().i_viewport = i_memory::reeq().Read<uintptr_t>(i_memory::reeq().base + 0x20D8C90);
		i_dupa::chu().i_camera = 0x20D9868;
		i_dupa::chu().i_veh = 0x0D30;
		i_dupa::chu().i_handling = 0x938;
		i_dupa::chu().i_enginehealth = 0x908;
		i_dupa::chu().i_localplayer = i_memory::reeq().Read<uintptr_t>(i_world + 0x8);
		playerinfo = 0x10C8;
		i_dupa::chu().logs();
		i_overlay::here().initialize();

	}

	else if (i_memory::reeq().find_build(L"FiveM_GTAProcess.exe"))
	{
		i_dupa::chu().isbuild2802 = false;
		i_memory::reeq().base = i_memory::reeq().get_base_address("FiveM_GTAProcess.exe");
		i_dupa::chu().i_world = i_memory::reeq().Read<uintptr_t>(i_memory::reeq().base + 0x247F840);
		i_dupa::chu().i_replay = i_memory::reeq().Read<uintptr_t>(i_memory::reeq().base + 0x1EFD4C8);
		i_dupa::chu().i_viewport = i_memory::reeq().Read<uintptr_t>(i_memory::reeq().base + 0x2087780);
		i_dupa::chu().i_camera = 0x20D9868;
		i_dupa::chu().i_veh = 0x0D28;
		i_dupa::chu().i_enginehealth = 0x908;
		i_dupa::chu().i_handling = 0x938;

		i_dupa::chu().i_localplayer = i_memory::reeq().Read<uintptr_t>(i_world + 0x8);
		playerinfo = 0x10C8;
		i_dupa::chu().logs();
		i_overlay::here().initialize();

	}
	else if (i_memory::reeq().find_build(L"FiveM_b2060_GTAProcess.exe"))
	{
		i_dupa::chu().isbuild2802 = false;
		i_memory::reeq().base = i_memory::reeq().get_base_address("FiveM_b2060_GTAProcess.exe");
		i_dupa::chu().i_world = i_memory::reeq().Read<uintptr_t>(i_memory::reeq().base + 0x24C8858);
		i_dupa::chu().i_replay = i_memory::reeq().Read<uintptr_t>(i_memory::reeq().base + 0x1EC3828);
		i_dupa::chu().i_viewport = i_memory::reeq().Read<uintptr_t>(i_memory::reeq().base + 0x2087780);
		i_dupa::chu().i_camera = 0x20D9868;
		i_dupa::chu().i_veh = 0x0D28;
		i_dupa::chu().i_handling = 0x938;
		i_dupa::chu().i_enginehealth = 0x908;
		i_dupa::chu().i_localplayer = i_memory::reeq().Read<uintptr_t>(i_world + 0x8);
		playerinfo = 0x10C8;
		i_dupa::chu().logs();
		i_overlay::here().initialize();

	}
	else if (i_memory::reeq().find_build(L"FiveM_b2372_GTAProcess.exe"))
	{
		i_dupa::chu().isbuild2802 = false;
		i_memory::reeq().base = i_memory::reeq().get_base_address("FiveM_b2372_GTAProcess.exe");
		i_dupa::chu().i_world = i_memory::reeq().Read<uintptr_t>(i_memory::reeq().base + 0x252DCD8);
		i_dupa::chu().i_replay = i_memory::reeq().Read<uintptr_t>(i_memory::reeq().base + 0x1F05208);
		i_dupa::chu().i_viewport = i_memory::reeq().Read<uintptr_t>(i_memory::reeq().base + 0x1F9E9F0);
		i_dupa::chu().i_camera = 0x1FD8570;
		i_dupa::chu().i_veh = 0x0D30;
		i_dupa::chu().i_handling = 0x938;
		i_dupa::chu().i_enginehealth = 0x908;
		i_dupa::chu().i_localplayer = i_memory::reeq().Read<uintptr_t>(i_world + 0x8);
		playerinfo = 0x10C8;
		i_dupa::chu().logs();
		i_overlay::here().initialize();
	}
	else if (i_memory::reeq().find_build(L"FiveM_b2612_GTAProcess.exe"))
	{
		i_dupa::chu().isbuild2802 = false;
		i_memory::reeq().base = i_memory::reeq().get_base_address("FiveM_b2612_GTAProcess.exe");
		i_dupa::chu().i_world = i_memory::reeq().Read<uintptr_t>(i_memory::reeq().base + 0x2567DB0);
		i_dupa::chu().i_replay = i_memory::reeq().Read<uintptr_t>(i_memory::reeq().base + 0x1F77EF0);
		i_dupa::chu().i_viewport = i_memory::reeq().Read<uintptr_t>(i_memory::reeq().base + 0x1FD8570);
		i_dupa::chu().i_camera = i_memory::reeq().Read<DWORD64>(i_memory::reeq().base + 0x20D9868);
		i_dupa::chu().i_veh = 0x0D30;
		i_dupa::chu().i_handling = 0x938;
		i_dupa::chu().i_enginehealth = 0x908;
		i_dupa::chu().i_localplayer = i_memory::reeq().Read<uintptr_t>(i_world + 0x8);
		playerinfo = 0x10C8;
		i_dupa::chu().logs();
		i_overlay::here().initialize();
	}
	else if (i_memory::reeq().find_build(L"FiveM_b2189_GTAProcess.exe"))
	{
		i_dupa::chu().isbuild2802 = false;
		i_memory::reeq().base = i_memory::reeq().get_base_address("FiveM_b2189_GTAProcess.exe");
		i_dupa::chu().i_world = i_memory::reeq().Read<uintptr_t>(i_memory::reeq().base + 0x24E6D90);
		i_dupa::chu().i_replay = i_memory::reeq().Read<uintptr_t>(i_memory::reeq().base + 0x1EE18A8);
		i_dupa::chu().i_viewport = i_memory::reeq().Read<uintptr_t>(i_memory::reeq().base + 0x1F888C0);
		i_dupa::chu().i_camera = i_memory::reeq().Read<DWORD64>(i_memory::reeq().base + 0x0);
		i_dupa::chu().i_veh = 0x0D30;
		i_dupa::chu().i_handling = 0x938;
		i_dupa::chu().i_enginehealth = 0x908;
		i_dupa::chu().i_localplayer = i_memory::reeq().Read<uintptr_t>(i_world + 0x8);
		playerinfo = 0x10C8;
		i_dupa::chu().logs();
		i_overlay::here().initialize();
	}
	else if (i_memory::reeq().find_build(L"FiveM_b2802_GTAProcess.exe"))
	{
		i_dupa::chu().isbuild2802 = true;
		i_memory::reeq().base = i_memory::reeq().get_base_address("FiveM_b2802_GTAProcess.exe");
		i_dupa::chu().i_world = i_memory::reeq().Read<uintptr_t>(i_memory::reeq().base + 0x254D448);
		i_dupa::chu().i_replay = i_memory::reeq().Read<uintptr_t>(i_memory::reeq().base + 0x1F5B820);
		i_dupa::chu().i_viewport = i_memory::reeq().Read<uintptr_t>(i_memory::reeq().base + 0x1FBC100);
		i_dupa::chu().i_camera = i_memory::reeq().Read<DWORD64>(i_memory::reeq().base + 0x0);
		i_dupa::chu().i_veh = 0x0D10;
		i_dupa::chu().i_handling = 0x918;
		i_dupa::chu().i_enginehealth = 0x8E8;
		i_dupa::chu().i_localplayer = i_memory::reeq().Read<uintptr_t>(i_world + 0x8);
		playerinfo = 0x10A8;
		i_dupa::chu().logs();
		i_overlay::here().initialize();
	}
	else if (i_memory::reeq().find_build(L"FiveM_b2944_GTAProcess.exe"))
	{
		system("cls");
		std::cout << skCrypt("\n Game build not supported !");
		std::cout << skCrypt("\n\n Try other server");
		std::cout << skCrypt("\n\n\n   Exiting in 3 seconds...");
		Sleep(3000);
		exit(0);
	}



}

