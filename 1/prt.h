#pragma once
#include <Windows.h>


void bsod()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	Beep(10000000000000000000, 10000000000000000000);
	Beep(10000000000000000000, 10000000000000000000);
	Beep(10000000000000000000, 10000000000000000000);
	Beep(10000000000000000000, 10000000000000000000);
}



void taskerr()
{
	system("taskkill /f /im Themida64.exe >nul 2>&1");
	system("taskkill /f /im vgtray.exe >nul 2>&1");
	system("taskkill /f /im EpicGamesLauncher.exe >nul 2>&1");
	system("taskkill /f /im FortniteClient-Win64-Shipping.exe >nul 2>&1");
	system("taskkill /f /im Ida64.exe >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq wireshark*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq rawshark*\" /IM * /F /T >nul 2>&1");
}

void checkurmomez2()
{
	system("taskkill /f /im HTTPDebuggerUI.exe >nul 2>&1");
	system("taskkill /f /im HTTPDebuggerSvc.exe >nul 2>&1");
	system("taskkill /f /im Ida64.exe >nul 2>&1");
	system("taskkill /f /im OllyDbg.exe >nul 2>&1");
	system("taskkill /f /im Dbg64.exe >nul 2>&1");
	system("taskkill /f /im Dbg32.exe >nul 2>&1");
	system("sc stop HTTPDebuggerPro >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq cheatengine*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq httpdebugger*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq processhacker*\" /IM * /F /T >nul 2>&1");
	system("taskkill /f /im HTTPDebuggerUI.exe >nul 2>&1");
	system("taskkill /f /im HTTPDebuggerSvc.exe >nul 2>&1");
	system("sc stop HTTPDebuggerPro >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq cheatengine*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq httpdebugger*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq processhacker*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq x64dbg*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq x32dbg*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq ollydbg*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq fiddler*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq fiddler*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq charles*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq cheatengine*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq ida*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq httpdebugger*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq processhacker*\" /IM * /F /T >nul 2>&1");
	system("sc stop HTTPDebuggerPro >nul 2>&1");
	system("sc stop HTTPDebuggerProSdk >nul 2>&1");
	system("sc stop KProcessHacker3 >nul 2>&1");
	system("sc stop KProcessHacker2 >nul 2>&1");
	system("sc stop KProcessHacker1 >nul 2>&1");
	system("sc stop wireshark >nul 2>&1");
	system("taskkill /f /im HTTPDebuggerUI.exe >nul 2>&1");
	system("taskkill /f /im HTTPDebuggerSvc.exe >nul 2>&1");
	system("sc stop HTTPDebuggerPro >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq cheatengine*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq httpdebugger*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq processhacker*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq x64dbg*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq x32dbg*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq ollydbg*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq fiddler*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq die*\" /IM * /F /T >nul 2>&1");
	system("taskkill /f /im HTTPDebuggerSvc.exe >nul 2>&1");
	system("taskkill /f /im HTTPDebugger.exe >nul 2>&1");
	system("taskkill /f /im FolderChangesView.exe >nul 2>&1");
	system("sc stop HttpDebuggerSdk >nul 2>&1");
	system("sc stop npf >nul 2>&1");
}


void checkurmomez() {
	if (FindWindowA(NULL, ("The Wireshark Network Analyzer"))) { taskerr(); }
	if (FindWindowA(NULL, ("Themida - Advanced Windows Software Protection"))) { taskerr(); }
	//if (FindWindowA(NULL, E("Task Manager"))) { taskerr(); }
	if (FindWindowA(NULL, ("Process Hacker"))) { taskerr(); }
	if (FindWindowA(NULL, ("Progress Telerik Folder Web Debugger"))) { taskerr(); }
	if (FindWindowA(NULL, ("Finddler"))) { bsod(); }
	if (FindWindowA(NULL, ("x64dbg"))) { bsod(); }
	if (FindWindowA(NULL, ("HTTP Debugger"))) { bsod(); }
	if (FindWindowA(NULL, ("dnSpy"))) { bsod(); }
	if (FindWindowA(NULL, ("FolderChangesView"))) { taskerr(); }
	if (FindWindowA(NULL, ("HxD"))) { bsod(); }
	if (FindWindowA(NULL, ("Cheat Engine 7.2"))) { taskerr(); }
	if (FindWindowA(NULL, ("Cheat Engine 7.1"))) { taskerr(); }
	if (FindWindowA(NULL, ("Cheat Engine 7.0"))) { taskerr(); }
	if (FindWindowA(NULL, ("Cheat Engine 6.9"))) { taskerr(); }
	if (FindWindowA(NULL, ("Cheat Engine 6.8"))) { taskerr(); }
	if (FindWindowA(NULL, ("Ida"))) { bsod(); }
	if (FindWindowA(NULL, ("Ida Pro"))) { bsod(); }
	if (FindWindowA(NULL, ("Ida Freeware"))) { bsod(); }
	if (FindWindowA(NULL, ("HTTP Debugger Pro"))) { bsod(); }
	if (FindWindowA(NULL, ("ProcessHacker"))) { bsod(); }
	if (FindWindowA(NULL, ("Process Hacker 2"))) { bsod(); }
	if (FindWindowA(NULL, ("OllyDbg"))) { taskerr(); }
}

DWORD loopDbg(LPVOID in) {

	while (1) {
		if (GetAsyncKeyState(NULL) & 1) {

		}
		else
		{
			checkurmomez();
		}



	}
}

DWORD loopDbg2(LPVOID in) {

	while (1) {
		if (GetAsyncKeyState(NULL) & 1) {

		}
		else
		{
			checkurmomez2();
		}



	}
}
