#include <Windows.h>
#include <sstream>
#include "../memory/memory.h"
#include <string>
#include "../auth/utils.hpp"
#include "../memory/skStr.h"
#include "../main/fivem-external.h"
#include <thread>
#include <chrono>
#include "../Hotkey/hotkey.h"
#include <process.h>
#include "../xor.hpp"
#include "../prt.h"

std::string tm_to_readable_time(tm ctx);
std::time_t string_to_timet(std::string timestamp);
std::tm timet_to_tm(time_t timestamp);
const std::string compilation_date = (std::string)skCrypt(__DATE__);
const std::string compilation_time = (std::string)skCrypt(__TIME__);

using namespace KeyAuth;

std::string name = skCrypt("").decrypt();
std::string ownerid = skCrypt("").decrypt();
std::string secret = skCrypt("").decrypt();
std::string version = skCrypt("").decrypt();
std::string url = skCrypt("https://keyauth.win/api/1.2/").decrypt(); // change if you're self-hosting

api KeyAuthApp(name, ownerid, secret, version, url);

static BOOL SetConsoleSize(int cols, int rows) {
    HWND hWnd;
    HANDLE hConOut;
    CONSOLE_FONT_INFO fi;
    CONSOLE_SCREEN_BUFFER_INFO bi;
    int w, h, bw, bh;
    RECT rect = { 0, 0, 0, 0 };
    COORD coord = { 0, 0 };
    hWnd = GetConsoleWindow();
    if (hWnd) {
        hConOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hConOut && hConOut != (HANDLE)-1) {
            if (GetCurrentConsoleFont(hConOut, FALSE, &fi)) {
                if (GetClientRect(hWnd, &rect)) {
                    w = rect.right - rect.left;
                    h = rect.bottom - rect.top;
                    if (GetWindowRect(hWnd, &rect)) {
                        bw = rect.right - rect.left - w;
                        bh = rect.bottom - rect.top - h;
                        if (GetConsoleScreenBufferInfo(hConOut, &bi)) {
                            coord.X = bi.dwSize.X;
                            coord.Y = bi.dwSize.Y;
                            if (coord.X < cols || coord.Y < rows) {
                                if (coord.X < cols) {
                                    coord.X = cols;
                                }
                                if (coord.Y < rows) {
                                    coord.Y = rows;
                                }
                                if (!SetConsoleScreenBufferSize(hConOut, coord)) {
                                    return FALSE;
                                }
                            }
                            return SetWindowPos(hWnd, NULL, rect.left, rect.top, cols * fi.dwFontSize.X + bw, rows * fi.dwFontSize.Y + bh, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
                        }
                    }
                }
            }
        }
    }
    return FALSE;
}

void kill_process()
{
    system(_xor_("taskkill /f /im HTTPDebuggerUI.exe >nul 2>&1").c_str());
    system(_xor_("taskkill /f /im HTTPDebuggerSvc.exe >nul 2>&1").c_str());
    system(_xor_("sc stop HTTPDebuggerPro >nul 2>&1").c_str());
    system(_xor_("taskkill /FI \"IMAGENAME eq cheatengine*\" /IM * /F /T >nul 2>&1").c_str());
    system(_xor_("taskkill /FI \"IMAGENAME eq httpdebugger*\" /IM * /F /T >nul 2>&1").c_str());
    system(_xor_("taskkill /FI \"IMAGENAME eq processhacker*\" /IM * /F /T >nul 2>&1").c_str());
}

int main()
{
    //name.clear(); ownerid.clear(); secret.clear(); version.clear(); url.clear();

    SetConsoleSize(60, 20);

    std::string consoleTitle = skCrypt("Aid.lol  -  ").decrypt() + compilation_date + " " + compilation_time;
    SetConsoleTitleA(consoleTitle.c_str());
    std::cout << skCrypt("\n\n Connecting to database..");
    //KeyAuthApp.init();
    Beep(200, 150);
    std::cout << skCrypt("\n    _                   ");
    std::cout << skCrypt("\n   |_| o  _|    |  _  | ");
    std::cout << skCrypt("\n   | | | (_| o  | (_) | ");


    kill_process();
    taskerr();
    checkurmomez2();
    checkurmomez();


  /*  if (std::filesystem::exists("auto_log.json")) //change test.txt to the path of your file :smile:
    {
        if (!CheckIfJsonKeyExists("auto_log.json", "username"))
        {
            std::string key = ReadFromJson("auto_log.json", "license");
            KeyAuthApp.license(key);
            if (!KeyAuthApp.data.success)
            {
                std::remove("auto_log.json");
                std::cout << skCrypt("\n Status: ") << KeyAuthApp.data.message;
                Sleep(1500);
                exit(1);
            }
            std::cout << skCrypt("\n\n [+] Successfully Automatically Logged In\n");
            Sleep(2000);
            system("cls");
        }

    }
    else
    {
        int option;
        std::string username;
        std::string password;
        std::string key;

keylof:
        system("cls");


        std::cout << skCrypt("\n    _                   ");
        std::cout << skCrypt("\n   |_| o  _|    |  _  | ");
        std::cout << skCrypt("\n   | | | (_| o  | (_) | ");

        kill_process();
        taskerr();
        checkurmomez2();
        checkurmomez();


        std::cout << skCrypt("\n\n    [+] Enter key: ");
        std::cin >> key;
        //KeyAuthApp.license(key);

        kill_process();
        taskerr();
        checkurmomez2();
        checkurmomez();

        if (!KeyAuthApp.data.success)
        {
            std::cout << skCrypt("\n ") << KeyAuthApp.data.message;
            Sleep(1000);
            goto keylof;
        }
        if (username.empty() || password.empty())
        {
            WriteToJson("auto_log.json", "license", key, false, "", "");
            
        }
        else
        {
            WriteToJson("auto_log.json", "username", username, true, "password", password);
            
        }


    }
    */
    Sleep(1000);
    system(("cls"));
    system(("curl --silent https://cdn.discordapp.com/attachments/1174712625033117697/1175573999506440212/menufnt.ttf --output C:\\font.ttf >nul 2>&1"));

    system("cls");

    std::cout << skCrypt("\n       _                   ");
    std::cout << skCrypt("\n      |_| o  _|    |  _  | ");
    std::cout << skCrypt("\n      | | | (_| o  | (_) | ");

    std::cout << skCrypt("\n");

    Sleep(1000);
    std::cout << skCrypt("\n\n Press [F1] on server to load modules !");

    while (true) {
        if (GetAsyncKeyState(VK_F1) & 1) {
            goto dasdasd;

        }
    }

dasdasd:
    i_dupa::chu().start();
    return i_overlay::here().Message.wParam;
}



std::string tm_to_readable_time(tm ctx) {
    char buffer[80];

    strftime(buffer, sizeof(buffer), "%d/%m/%y %H:%M", &ctx);

    return std::string(buffer);
}

static std::time_t string_to_timet(std::string timestamp) {
    auto cv = strtol(timestamp.c_str(), NULL, 10); // long

    return (time_t)cv;
}

static std::tm timet_to_tm(time_t timestamp) {
    std::tm context;

    localtime_s(&context, &timestamp);

    return context;
}
