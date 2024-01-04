#include "overlay.h"
#include <sstream>
#include "million.h"
#include "../Hotkey/hotkey.h"
#include <process.h>
#include <stdio.h>
i_overlay& i_overlay::here()
{
	static i_overlay ins;
	return ins;
}

bool i_overlay::LoadTextureFromFile(const char* filename, PDIRECT3DTEXTURE9* out_texture, int* out_width, int* out_height)
{
	// Load texture from disk
	PDIRECT3DTEXTURE9 texture;
	HRESULT hr = D3DXCreateTextureFromFileA(p_Device, filename, &texture);
	if (hr != S_OK)
		return false;

	// Retrieve description of the texture surface so we can access its size
	D3DSURFACE_DESC my_image_desc;
	texture->GetLevelDesc(0, &my_image_desc);
	*out_texture = texture;
	*out_width = (int)my_image_desc.Width;
	*out_height = (int)my_image_desc.Height;
	return true;
}

std::int64_t __stdcall i_overlay::wndproc(HWND hwnd, unsigned int message, WPARAM wparam, LPARAM lparam)
{

	std::int64_t ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	ImGui_ImplWin32_WndProcHandler(hwnd, message, wparam, lparam);
	if (i_overlay::here().showmenu)
		return 1;

	return DefWindowProcA(i_overlay::here().MyWnd, message, wparam, lparam);
}

void styledark()
{
	ImGuiStyle* Style = &ImGui::GetStyle();
	ImVec4* Colors = Style->Colors;



	Style->Alpha = 1.0;
	Style->ChildRounding = 3;
	Style->WindowRounding = 5;
	Style->PopupRounding = 5;
	Style->GrabRounding = 2;
	Style->GrabMinSize = 20;
	Style->FrameRounding = 3;
	Style->WindowTitleAlign = ImVec2(0.5f, 0.5f);

	Style->Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	Style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	Style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.94f); // menu cale
	Style->Colors[ImGuiCol_ChildBg] = ImVec4(27 / 255.00f, 26 / 255.00f, 26 / 255.00f, 0 / 255.00f); // na lewo z tabami
	Style->Colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f); // chui wie
	Style->Colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f); //
	Style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);//
	Style->Colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.29f, 0.48f, 0.54f); // chui wie
	Style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f); // chui wie
	Style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f); // chui wie
	Style->Colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f); //
	Style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.29f, 0.48f, 1.00f); //
	Style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f); //nwm
	Style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f); //
	Style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f); //
	Style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f); //
	Style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f); //
	Style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f); //
	Style->Colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f); //
	Style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.64f, 0.62f, 0.63f, 1.00f); //
	Style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.64f, 0.62f, 0.63f, 1.00f); //
	Style->Colors[ImGuiCol_Button] = ImVec4(0.07f, 0.07f, 0.07f, 0.f); //
	Style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.07f, 0.07f, 0.07f, 0.f);//
	Style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.07f, 0.07f, 0.07f, 0.f); //
	Style->Colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.f); // chui wie
	Style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f); //
	Style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);//
	Style->Colors[ImGuiCol_Separator] = Colors[ImGuiCol_Border];  //
	Style->Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f); //
	Style->Colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f); // 
	Style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.20f); //
	Style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f); //
	Style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f); //
	Style->Colors[ImGuiCol_Tab] = ImVec4(0.26f, 0.59f, 0.98f, 0.f); // chui wie
	Style->Colors[ImGuiCol_TabHovered] = Colors[ImGuiCol_HeaderHovered];  //
	Style->Colors[ImGuiCol_TabActive] = ImLerp(Colors[ImGuiCol_HeaderActive], Colors[ImGuiCol_TitleBgActive], 0.60f); //
	Style->Colors[ImGuiCol_TabUnfocused] = ImLerp(Colors[ImGuiCol_Tab], Colors[ImGuiCol_TitleBg], 0.80f); //
	Style->Colors[ImGuiCol_TabUnfocusedActive] = ImLerp(Colors[ImGuiCol_TabActive], Colors[ImGuiCol_TitleBg], 0.40f); //
	Style->Colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f); //
	Style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f); //
	Style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f); //
	Style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f); //
	Style->Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f); //
	Style->Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);   // Prefer using Alpha=1.0 here
	Style->Colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);   // Prefer using Alpha=1.0 here
	Style->Colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f); // 
	Style->Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f); //
	Style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f); //
	Style->Colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f); //
	Style->Colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f); //
	Style->Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f); // nwm
	Style->Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f); //
	Style->Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f); //
	Style->Colors[ImGuiCol_PopupBg] = ImVec4(0.f, 0.f, 0.f, 0.f); //
	Style->Colors[ImGuiCol_Border] = ImVec4(1.0f, 1.0f, 1.0f, 0.03f); //
}

HRESULT i_overlay::init_wndparams(HWND hwnd)
{
	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &p_Object)))
		return E_FAIL;

	ZeroMemory(&p_Params, sizeof(p_Params));
	p_Params.Windowed = TRUE;
	p_Params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	p_Params.hDeviceWindow = hwnd;
	p_Params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	p_Params.BackBufferFormat = D3DFMT_A8R8G8B8;
	p_Params.BackBufferWidth = Width;
	p_Params.BackBufferHeight = Height;
	p_Params.EnableAutoDepthStencil = TRUE;
	p_Params.AutoDepthStencilFormat = D3DFMT_D16;
	p_Params.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	if (FAILED(p_Object->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &p_Params, 0, &p_Device))) {
		p_Object->Release();
		return E_FAIL;
	}

	ImGui::CreateContext();

	// LoadTextureFromFileAsync("unknown2.png", &my_texture, &my_image_width, &my_image_height);
	// Load the texture asynchronously to prevent potential UI freezes

	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = NULL;

	char windows_directory[MAX_PATH];

	// std::string segoeui_dir = (std::string)windows_directory + "\\Fonts\\segoeui.ttf";

	// global34 = io.Fonts->AddFontFromFileTTF(segoeui_dir.c_str(), 18.0f, &font_config, io.Fonts->GetGlyphRangesCyrillic());
	// ico_combo2 = io.Fonts->AddFontFromMemoryTTF(&icon, sizeof icon, 19, NULL, io.Fonts->GetGlyphRangesCyrillic());

	global3 = io.Fonts->AddFontFromMemoryTTF(segoui, sizeof(segoui), 17, NULL, io.Fonts->GetGlyphRangesCyrillic());



	watermarkFont = io.Fonts->AddFontFromFileTTF("C:\\Windows\\System32\\font_24.ttf", 180.0f, NULL, io.Fonts->GetGlyphRangesDefault());

	//D:\\NALEPSZE PROKETYY\\Bsing on\\CS2_External\\Off2\\offsets\\fivem-external-dupa\\menufnt.ttf

	menuFnt = io.Fonts->AddFontFromFileTTF("C:\\font.ttf", 17.0f, NULL, io.Fonts->GetGlyphRangesDefault());

	//menuFnt = io.Fonts->AddFontFromMemoryTTF(kimora, sizeof(kimora), 17, NULL, io.Fonts->GetGlyphRangesCyrillic());

	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX9_Init(p_Device);

	return S_OK;
}

void i_overlay::cleanup_d3d()
{
	if (p_Device != NULL) {
		p_Device->EndScene();
		p_Device->Release();
	}
	if (p_Object != NULL) {
		p_Object->Release();
	}
}

void set_window_target()
{
	i_overlay& overlay = i_overlay::here();
	i_memory& memory = i_memory::reeq();

	while (true) {
		overlay.GameWnd = memory.get_process_wnd(memory.pid);

		if (overlay.GameWnd) {
			ZeroMemory(&overlay.GameRect, sizeof(overlay.GameRect));
			GetWindowRect(overlay.GameWnd, &overlay.GameRect);

			DWORD dwStyle = GetWindowLong(overlay.GameWnd, GWL_STYLE);
			if (dwStyle & WS_BORDER) {
				overlay.GameRect.top += 32;
				overlay.Height -= 39;
			}

			overlay.ScreenCenterX = overlay.Width / 2;
			overlay.ScreenCenterY = overlay.Height / 2;

			MoveWindow(overlay.MyWnd, overlay.GameRect.left, overlay.GameRect.top, overlay.Width, overlay.Height, true);
		}
	}
}

char Licence[50] = "";
void i_overlay::setup_window()
{
	(HANDLE)_beginthreadex(nullptr, 0, reinterpret_cast<_beginthreadex_proc_type>(&set_window_target), 0, 0, 0);
	WNDCLASSEXA wcex = {
		sizeof(WNDCLASSEXA),
		0,
		wndproc,
		0,
		0,
		nullptr,
		LoadIcon(nullptr, IDI_APPLICATION),
		LoadCursor(nullptr, IDC_ARROW),
		nullptr,
		nullptr,
		("Top"),
		LoadIcon(nullptr, IDI_APPLICATION)
	};

	RECT Rect;
	GetWindowRect(GetDesktopWindow(), &Rect);

	RegisterClassExA(&wcex);

	MyWnd = CreateWindowA(("Top"), ("Top"), WS_POPUP, Rect.left, Rect.top, Rect.right, Rect.bottom, NULL, NULL, wcex.hInstance, NULL);
	SetWindowLong(MyWnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT);
	SetLayeredWindowAttributes(MyWnd, RGB(0, 0, 0), 255, LWA_ALPHA);

	MARGINS margin = { -1 };
	DwmExtendFrameIntoClientArea(MyWnd, &margin);

	ShowWindow(MyWnd, SW_SHOW);
}


void i_overlay::style()
{
	ImGuiStyle* Style = &ImGui::GetStyle();
	ImVec4* Colors = Style->Colors;


	ImGui::StyleColorsDark();
}

void i_overlay::CustomStyleColor()
{
	ImGuiStyle& s = ImGui::GetStyle();


	s.WindowBorderSize = 0;

	s.PopupBorderSize = 0;
	s.FrameBorderSize = 1.0f;
	s.FrameRounding = 4.f;

}
int slider_int = 0;
int slider_int2 = 0;
int slider_int3s = 0;
bool test = false;
bool test2 = false;
bool test3 = false;
bool test4 = false;
const char* items[3] = { "head","chest", "legs" };

const char* const KeyNames[] = {
	"VK_RBUTTON",
	"VK_LBUTTON",
	"VK_MBUTTON",
	"VK_XBUTTON1",
	"VK_XBUTTON2",
	"VK_TAB",
	"VK_SHIFT",
	"VK_CONTROL",
	"VK_ALT",
};

bool aimbot = false;
bool esp = false;
bool autotarget = false;
bool autoshot = false;
bool drawfov = false;

ImFont* LexendRegular;

int fov = 0;
int smooth = 0;

int Hotkey = 2;

bool active = true;
bool active2 = false;
int subtab3 = 0;
int subtab2 = 0;

uint64_t selectedped = 0;

void rainbowclr()
{
	float r = 1;
	float g = 1;
	float b = 1;
rain1:
	Sleep(10);
	r = 10;
	Sleep(10);
	r = 20;
	g = 10;
	Sleep(10);
	r = 30;
	g = 20;
	Sleep(10);
	r = 40;
	g = 30;
	Sleep(10);
	r = 50;
	g = 40;
	Sleep(10);
	r = 50;
	g = 50;
	goto rain1;
}

void i_overlay::menu()
{

	styledark();
	ImDrawList* draw;
	ImGui::SetNextWindowSize(ImVec2({ 690,454 }));



	ImGui::SetNextWindowBgAlpha(0.98f);
	ImGui::Begin(skCrypt("GameOverlayUI"), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse);
	{
		ImVec2 pos;
		auto p = ImGui::GetWindowPos();
		pos = ImGui::GetWindowPos();
		draw = ImGui::GetWindowDrawList();




		float oldfsize = ImGui::GetFont()->Scale;

		float oldfsize3 = ImGui::GetFont()->Scale;

		ImGui::PushFont(menuFnt);
		ImGui::GetFont()->Scale = 2.2;
		ImGui::PushFont(ImGui::GetFont());

		draw->AddText(ImVec2(pos.x + 15, pos.y + 12), ImColor(230, 230, 230), (skCrypt(("HUS UD"))));

		ImGui::GetFont()->Scale = oldfsize;
		ImGui::PopFont();

		ImGui::GetFont()->Scale = oldfsize;

		ImGui::PushFont(global3);
		ImGui::PopFont();


		ImGui::PushFont(global3);
		ImGui::SetCursorPos({ 15, 75 });

		ImGui::PushFont(ImGui::GetFont());

		if (ImGui::Button(skCrypt("Aimbot "), ImVec2(130, 30)))
		{

				subtab2 = 0;
				subtab3 = 0;
		}

		ImGui::SetCursorPos({ 15, 115 });
		if (ImGui::Button(skCrypt("Visuals "), ImVec2(130, 30)))
		{

			subtab2 = 1;
			subtab3 = 5;
		}

		ImGui::SetCursorPos({ 15, 155 });
		if (ImGui::Button(skCrypt("Settings"), ImVec2(130, 30)))
		{
			subtab2 = 6;
			subtab3 = 6;
		}



		// Gora

		draw->AddLine(ImVec2(pos.x + 15, pos.y + 46), ImVec2(pos.x + 670, pos.y + 47), ImColor(110, 110, 110), 2.f);

		if (subtab3 == 0)
		{
			draw->AddRectFilled(ImVec2(pos.x + 19, pos.y + 75), ImVec2(pos.x + 24, pos.y + 105), ImColor(130, 130, 130), 1.4f, 0); //102,102,255

			ImGui::SetCursorPos({ 215, 20 });

			if (ImGui::Button(skCrypt("Aimbot"), ImVec2(90, 20)))
			{
				subtab2 = 0;
			}

			ImGui::SetCursorPos({ 310, 20 });
			if (ImGui::Button(skCrypt("Trigger"), ImVec2(90, 20)))
			{
				subtab2 = 42;
			}
		}

		if (subtab3 == 5)
		{
			draw->AddRectFilled(ImVec2(pos.x + 19, pos.y + 115), ImVec2(pos.x + 24, pos.y + 145), ImColor(130, 130, 130), 1.4f, 0);

			ImGui::SetCursorPos({ 215, 20 });
			if (ImGui::Button(skCrypt("Visuals"), ImVec2(90, 20)))
			{
				subtab2 = 1;
			}

			ImGui::SetCursorPos({ 310, 20 });
			if (ImGui::Button(skCrypt("Colors"), ImVec2(90, 20)))
			{
				subtab2 = 4;
			}
		}

		if (subtab3 == 6)
		{
			draw->AddRectFilled(ImVec2(pos.x + 19, pos.y + 155), ImVec2(pos.x + 24, pos.y + 185), ImColor(130, 130, 130), 1.4f, 0);

			ImGui::SetCursorPos({ 215, 20 });
			if (ImGui::Button(skCrypt("Misc"), ImVec2(90, 20)))
			{
				subtab2 = 7;
			}

			ImGui::SetCursorPos({ 310, 20 });
			if (ImGui::Button(skCrypt("Configs"), ImVec2(90, 20)))
			{
				subtab2 = 6;
			}
		}
		
		//Aimbot
		if (subtab2 == 0)
		{
			ImGui::PushFont(global3);
			ImGui::SetCursorPos({ 165, 53 });
			ImGui::Text("Settings");

			ImGui::SetCursorPos({ 160, 70 });
			ImGui::BeginChild((("Aim Settings")), ImVec2(250, 362));
			{			
				ImGui::SetCursorPos({ 15, 15 });
				ImGui::Checkbox(skCrypt("Memory Aim"), &i_aim::aim().memory);

				ImGui::SetCursorPosX(15);
				ImGui::Checkbox(skCrypt("Draw Fov"), &i_aim::aim().showfov);

				ImGui::SetCursorPosX(15);
				ImGui::Checkbox(skCrypt("Target Peds"), &i_aim::aim().targetpeds);

				ImGui::SetCursorPosX(15);
				ImGui::Checkbox(skCrypt("Target Dead"), &i_aim::aim().targetdead);

				const char* Boness[]{ "Head","Neck","Chest" };
				ImGui::SetCursorPosX(10);
				ImGui::Combo(skCrypt((("Bone"))), &i_aim::aim().boneid, Boness, IM_ARRAYSIZE(Boness), ImGuiComboFlags_NoArrowButton);

				ImGui::SetCursorPosX(10);
				ImGui::Combo((((("Bind")))), &Hotkey::hot().key, KeyNames, IM_ARRAYSIZE(KeyNames), ImGuiComboFlags_NoArrowButton);			
			}
			ImGui::EndChild();

			if (i_aim::aim().targetpeds)
			{
				i_aim::aim().ignoreped = false;
			}
			else
			{
				i_aim::aim().ignoreped = true;
			}

			if (i_aim::aim().targetpeds)
			{
				i_aim::aim().ignoredeath = false;
			}
			else
			{
				i_aim::aim().ignoredeath = true;
			}

			ImGui::SetCursorPos({ 420, 53 });
			ImGui::Text("Aimbot");
			ImGui::SetCursorPos({ 415, 70 });
			ImGui::BeginChild((("Aimbot")), ImVec2(250, 165));
			{
				ImGui::SetCursorPos({ 15, 15 });
				ImGui::Checkbox(skCrypt("Mouse Aim"), &i_aim::aim().aimenable);

				ImGui::SetCursorPosX(5);
				ImGui::SetCursorPosY(45);
				ImGui::PushItemWidth(225);
				ImGui::SliderInt(skCrypt(("Fov")), &i_aim::aim().fov, 1.0f, 360);

				ImGui::SetCursorPosX(5);
				ImGui::PushItemWidth(225);
				ImGui::SliderInt(skCrypt(("Smooth")), &i_aim::aim().smooth, 1, 15);

				ImGui::SetCursorPosX(5);
				ImGui::PushItemWidth(225);
				ImGui::SliderInt(skCrypt(("Distance")), &i_aim::aim().distance, 5.0f, 340);

			}
			ImGui::EndChild();


			ImGui::SetCursorPos({ 420, 238 });
			ImGui::Text("Silent");	
			ImGui::SetCursorPos({ 415, 255 });
			ImGui::BeginChild((("Silent")), ImVec2(250, 174));
			{
				ImGui::SetCursorPos({ 15, 15 });

				ImGui::Checkbox(skCrypt("Enable "), &i_aim::aim().silentv2);

				if (i_aim::aim().silentv2) {

					ImGui::PushFont(watermarkFont);
					ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(0, ScreenCenterY - 250), ImVec2(4800, ScreenCenterY + 250), ImColor(25, 25, 25,180));
					ImGui::GetForegroundDrawList()->AddText(ImVec2(ScreenCenterX - 600, ScreenCenterY-120), ImColor(255, 55, 55), "Silent aim in progress");
					ImGui::PopFont();
				}

				

				ImGui::SetCursorPosX(5);
				//ImGui::SetCursorPosY(45);
				ImGui::PushItemWidth(225);
				ImGui::SliderInt(skCrypt(("Fov ")), &i_aim::aim().silentfov, 1.0f, 200);

				ImGui::SetCursorPosX(5);
				ImGui::PushItemWidth(225);
				ImGui::SliderInt(skCrypt(("Hitchance")), &i_aim::aim().silhitchance, 10, 100);

				ImGui::SetCursorPosX(5);
				ImGui::PushItemWidth(225);
				ImGui::SliderInt(skCrypt(("Distance ")), &i_aim::aim().sildistance, 5.0f, 300);
			}
			ImGui::EndChild();

			ImGui::PopFont();
		}

		//triggerbot
		if (subtab2 == 42)
		{
			ImGui::PushFont(global3);
			ImGui::SetCursorPos({ 165, 53 });
			ImGui::Text("Settings ");

			ImGui::SetCursorPos({ 160, 70 });
			ImGui::BeginChild((("Trigger Settings")), ImVec2(250, 165));
			{
				ImGui::SetCursorPos({ 15, 15 });
				ImGui::Text("Soon...");

			}
			ImGui::EndChild();

			ImGui::SetCursorPos({ 420, 53 });
			ImGui::Text("Trigger");

			ImGui::SetCursorPos({ 415, 70 });
			ImGui::BeginChild((("Trigger bot")), ImVec2(250, 165));
			{


			}
			ImGui::EndChild();

			ImGui::PopFont();
		}




		if (subtab2 == 1)
		{

			ImGui::PushFont(global3);
			ImGui::SetCursorPos({ 160, 55 });
			ImGui::BeginChild(skCrypt(("Visuals")), ImVec2(510, 319));
			{

				ImGui::SetCursorPos({ 15,15 });
				ImGui::Checkbox(skCrypt("Box"), &i_esp::esp().box);
				ImGui::SetCursorPosX(15);

				ImGui::Checkbox(skCrypt("Show Distance"), &i_esp::esp().distance);
				ImGui::SetCursorPosX(15);
				ImGui::Checkbox(skCrypt("Skeleton"), &i_esp::esp().skeleton);
				ImGui::SetCursorPosX(15);
				ImGui::Checkbox(skCrypt("Snaplines"), &i_esp::esp().lines);
				ImGui::SetCursorPosX(15);
				ImGui::Checkbox(skCrypt("Ignore Ped"), &i_esp::esp().ignoreped);
				ImGui::SetCursorPosX(15);
				ImGui::Checkbox(skCrypt("Ignore Dead"), &i_esp::esp().ignoredead);
				ImGui::SetCursorPosX(15);
				const char* HealthbarStyle[]{ "Right","Left","Up" };
				ImGui::Checkbox(skCrypt("Healthbar"), &i_esp::esp().heathbar);

				ImGui::SetCursorPosX(15);
				ImGui::PushItemWidth(125);
				ImGui::Combo(skCrypt(((("Healthbar Type")))), &i_esp::esp().HealthBar_type, HealthbarStyle, 3, ImGuiComboFlags_NoArrowButton);


				const char* BoxStyle[]{ "2D","Rounded" };
				ImGui::SetCursorPosX(15);
				ImGui::PushItemWidth(125);
				ImGui::Combo(skCrypt(((("Box Type")))), &i_esp::esp().boxtype, BoxStyle, 2, ImGuiComboFlags_NoArrowButton);


				ImGui::SetCursorPos({ 180,20 });
				ImGui::PushItemWidth(225);
				ImGui::SliderInt(skCrypt(("Distance")), &i_esp::esp().distanceint, 5.0f, 500);
			}
			ImGui::EndChild();
			ImGui::PopFont();
		}
		if (subtab2 == 4)
		{

			ImGui::SetCursorPos({ 160, 55 });
			ImGui::BeginChild(skCrypt(("Colors")), ImVec2(510, 319));
			{



				//ImGui::SetCursorPosX(15);
				//ImGui::ColorEdit3(skCrypt("Skel"), (float*)&i_esp::esp().skeletoncolor);
				ImGui::SetCursorPosX(15);
				ImGui::Text("Skeleton");
				ImGui::SetCursorPosX(15);
				ImGui::SetNextItemWidth(134);
				ImGui::ColorPicker4(skCrypt(" 4 "), (float*)&i_esp::esp().skeletoncolor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSmallPreview | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoSidePreview);

				
				ImGui::SetCursorPosX(234);
				ImGui::SetCursorPosY(8);
				ImGui::Text("Box");
				ImGui::SetCursorPosX(234);
				ImGui::SetNextItemWidth(134);
				ImGui::SameLine;
				ImGui::ColorPicker4(skCrypt(("    2     ")), (float*)&i_esp::esp().boxcolor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSmallPreview | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoSidePreview);

				ImGui::SetCursorPosX(15);
				ImGui::SetCursorPosY(170);
				ImGui::Text("Aimbot Fov");
				ImGui::SetCursorPosX(15);
				ImGui::SetNextItemWidth(134);
				ImGui::SameLine;
				ImGui::ColorPicker4(skCrypt(("      f            ")), (float*)&i_esp::esp().FovColor, ImGuiColorEditFlags_NoInputs| ImGuiColorEditFlags_NoSmallPreview| ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoSidePreview);


				ImGui::SetCursorPosX(15);
				ImGui::SetCursorPosY(332);
				ImGui::Text("Silent Fov");
				ImGui::SetCursorPosX(15);
				ImGui::SetNextItemWidth(134);
				ImGui::SameLine;
				ImGui::ColorPicker4(skCrypt(("                   f21        ")), (float*)&i_esp::esp().SilFovColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSmallPreview | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoSidePreview);

				ImGui::SetCursorPosX(234);
				ImGui::SetCursorPosY(170);
				ImGui::Text("Snaplines");
				ImGui::SetCursorPosX(234);
				ImGui::SetNextItemWidth(134);
				ImGui::SameLine;
				ImGui::ColorPicker4(skCrypt(("          1       ")), (float*)&i_esp::esp().LineColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSmallPreview | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoSidePreview);


			}ImGui::EndChild;
		}
		if (subtab2 == 6)
		{


			ImGui::SetCursorPos({ 160, 55 });
			ImGui::BeginChild(skCrypt(("Configs")), ImVec2(510, 319));
			{
				
			}ImGui::EndChild;
		}

		if (subtab2 == 7)
		{


			ImGui::PushFont(global3);
			ImGui::SetCursorPos({ 160, 55 });
			ImGui::BeginChild(skCrypt(("Informations")), ImVec2(510, 319));
			{
				ImGui::SetCursorPos({ 15,15 });

				ImGui::Checkbox("Watermark", &i_aim::aim().dupanie);

			}
			ImGui::EndChild();
			ImGui::PopFont();
		}
	}
	ImGui::End();
}

void i_overlay::signal()
{
	ZeroMemory(&Message, sizeof(MSG));
	style();
	static RECT old_rc;
	while (Message.message != WM_QUIT)
	{
		if (PeekMessage(&Message, MyWnd, 0, 0, PM_REMOVE)) {
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		HWND hwnd_active = GetForegroundWindow();


		if (hwnd_active == GameWnd) {
			HWND hwndtest = GetWindow(hwnd_active, GW_HWNDPREV);
			SetWindowPos(MyWnd, hwndtest, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

		}
		if (showmenu)
		{

		}
		RECT rc;
		POINT xy;

		ZeroMemory(&rc, sizeof(RECT));
		ZeroMemory(&xy, sizeof(POINT));
		GetClientRect(GameWnd, &rc);
		ClientToScreen(GameWnd, &xy);
		rc.left = xy.x;
		rc.top = xy.y;

		ImGuiIO& io = ImGui::GetIO();
		io.ImeWindowHandle = GameWnd;
		io.DeltaTime = 1.0f / 60.0f;

		POINT p;
		GetCursorPos(&p);
		io.MousePos.x = p.x - xy.x;
		io.MousePos.y = p.y - xy.y;
		if (GetAsyncKeyState(0x1)) {
			io.MouseDown[0] = true;
			io.MouseClicked[0] = true;
			io.MouseClickedPos[0].x = io.MousePos.x;
			io.MouseClickedPos[0].x = io.MousePos.y;
		}
		else io.MouseDown[0] = false;

		if (rc.left != old_rc.left || rc.right != old_rc.right || rc.top != old_rc.top || rc.bottom != old_rc.bottom) {

			old_rc = rc;

			Width = rc.right;
			Height = rc.bottom;

			p_Params.BackBufferWidth = Width;
			p_Params.BackBufferHeight = Height;
			SetWindowPos(MyWnd, (HWND)0, xy.x, xy.y, Width, Height, SWP_NOREDRAW);
			p_Device->Reset(&p_Params);
		}
		i_overlay::here().render();

		Sleep(10);
	}
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	i_overlay::here().cleanup_d3d();
	DestroyWindow(i_overlay::here().MyWnd);


}

std::wstring MBytesToWString(const char* lpcszString)
{
	int len = strlen(lpcszString);
	int unicodeLen = ::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, NULL, 0);
	wchar_t* pUnicode = new wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, (LPWSTR)pUnicode, unicodeLen);
	std::wstring wString = (wchar_t*)pUnicode;
	delete[] pUnicode;
	return wString;
}

std::string WStringToUTF8(const wchar_t* lpwcszWString)
{
	char* pElementText;
	int iTextLen = ::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, NULL, 0, NULL, NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, (iTextLen + 1) * sizeof(char));
	::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, pElementText, iTextLen, NULL, NULL);
	std::string strReturn(pElementText);
	delete[] pElementText;
	return strReturn;
}

void i_overlay::RectFilled(float x, float y, float x1, float y1, ImColor color, float rounding, int rounding_corners_flags)
{
	ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x1, y1), color, rounding, rounding_corners_flags);
}

void i_overlay::DrawHealthBarhorizontal(ImVec2 pos, ImVec2 pos2, ImVec2 dim, ImColor col)
{

	ImGui::GetForegroundDrawList()->AddLine(ImVec2(pos.x + dim.y, pos.y), ImVec2(pos2.x, pos.y), col, dim.x);

}

void i_overlay::DrawRectImGui(int x, int y, int w, int h, ImVec4 color, float thickness)
{
	ImGui::GetForegroundDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(color), 0, 0, thickness);
}

void i_overlay::DrawLeftProgressBar(int x, int y, int w, int h, int thick, int m_health)
{
	int G = (255 * m_health / 100);
	int R = 255 - G;
	RGBA healthcol = { R, G, 0, 255 };

	DrawFilledRect(x - (w / 2) - 3, y, thick, (h)*m_health / 100, &healthcol);
}

void i_overlay::DrawFilledRect(int x, int y, int w, int h, RGBA* color)
{
	ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 153.0, color->B / 51.0, color->A / 255.0)), 0, 0);
}
void i_overlay::DrawShieldbar(int x, int y, int w, int h, int thick, int m_health)
{
	int G = (255 * m_health / 100);
	int R = 255 - G;

	DrawFilledRect(x - (w / 2) - 3, y, thick, (h)*m_health / 100, &Col.darkblue);
}

void i_overlay::DrawHealthBar(ImVec2 pos, ImVec2 dim, ImColor col)
{


	ImGui::GetForegroundDrawList()->AddLine(pos, ImVec2(pos.x, pos.y - dim.y), col, dim.x);

}
void i_overlay::DrawLine(const ImVec2& x, const ImVec2 y, ImU32 color, const FLOAT width)
{
	ImGui::GetForegroundDrawList()->AddLine(x, y, color, width);
}

void i_overlay::DrawOutlinedText(ImFont* pFont, const std::string& text, const ImVec2& pos, float size, ImU32 color, bool center)
{
	std::stringstream stream(text);
	std::string line;

	float y = 0.0f;
	int index = 0;

	while (std::getline(stream, line))
	{
		ImVec2 textSize = pFont->CalcTextSizeA(size, FLT_MAX, 0.0f, line.c_str());

		if (center)
		{

			ImGui::GetForegroundDrawList()->AddText(pFont, size, ImVec2(pos.x - textSize.x / 2.0f, pos.y + textSize.y * index), ImGui::GetColorU32(color), line.c_str());
		}
		else
		{//

			ImGui::GetForegroundDrawList()->AddText(pFont, size, ImVec2(pos.x, pos.y + textSize.y * index), ImGui::GetColorU32(color), line.c_str());
		}

		y = pos.y + textSize.y * (index + 1);
		index++;
	}
}

void i_overlay::DrawString(float fontSize, int x, int y, bool bCenter, bool stroke, const char* pText, ...)
{
	va_list va_alist;
	char buf[1024] = { 0 };
	va_start(va_alist, pText);
	_vsnprintf_s(buf, sizeof(buf), pText, va_alist);
	va_end(va_alist);
	std::string text = WStringToUTF8(MBytesToWString(buf).c_str());
	if (bCenter)
	{
		ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
		x = x - textSize.x / 4;
		y = y - textSize.y;
	}
	if (stroke)
	{
		ImGui::GetForegroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetForegroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetForegroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetForegroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
	}
	ImGui::GetForegroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y), ImColor(189, 175, 255), text.c_str());
}

static const char* keyNames[] = {
	"",
	"Left Mouse",
	"Right Mouse",
	"Cancel",
	"Middle Mouse",
	"Mouse 5",
	"Mouse 4",
	"",
	"Backspace",
	"Tab",
	"",
	"",
	"Clear",
	"Enter",
	"",
	"",
	"Shift",
	"Control",
	"Alt",
	"Pause",
	"Caps",
	"",
	"",
	"",
	"",
	"",
	"",
	"Escape",
	"",
	"",
	"",
	"",
	"Space",
	"Page Up",
	"Page Down",
	"End",
	"Home",
	"Left",
	"Up",
	"Right",
	"Down",
	"",
	"",
	"",
	"Print",
	"Insert",
	"Delete",
	"",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"",
	"",
	"",
	"",
	"",
	"Numpad 0",
	"Numpad 1",
	"Numpad 2",
	"Numpad 3",
	"Numpad 4",
	"Numpad 5",
	"Numpad 6",
	"Numpad 7",
	"Numpad 8",
	"Numpad 9",
	"Multiply",
	"Add",
	"",
	"Subtract",
	"Decimal",
	"Divide",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",
};

static bool Items_ArrayGetter(void* data, int idx, const char** out_text)
{
	const char* const* items = (const char* const*)data;
	if (out_text)
		*out_text = items[idx];
	return true;
}

void i_overlay::HotkeyButton(int aimkey, void* changekey, int status)
{
	const char* preview_value = NULL;
	if (aimkey >= 0 && aimkey < IM_ARRAYSIZE(keyNames))
		Items_ArrayGetter(keyNames, aimkey, &preview_value);

	std::string aimkeys;
	if (preview_value == NULL)
		aimkeys = ("Select Key");
	else
		aimkeys = preview_value;

	if (status == 1)
	{
		aimkeys = ("Press key to bind");
	}
	if (ImGui::Button(aimkeys.c_str(), ImVec2(100, 20)))
	{
		if (status == 0)
		{
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)changekey, nullptr, 0, nullptr);
		}
	}
}


void i_overlay::initialize()
{

	// some stuff xyzus
	setup_window();
	init_wndparams(MyWnd);
	Sleep(2000);
	signal();
}


