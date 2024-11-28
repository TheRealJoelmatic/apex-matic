#define WIN32_LEAN_AND_MEAN
#define _M_X64
#ifndef _WIN32
#define _WIN32
#endif

#include <iostream>
#include <filesystem>

#include "offsets.h"
#include "ext/xor/xor_cc.hpp"
#include "global.h"
#include "memory/utils.h"
#include "ext/termcolor/termcolor.hpp"
#include "modules/loop.h"
#include "mapper/KD.h"
#include <thread>
#include "overlay/overlay.h"
#include <random>
#include <codecvt>
#include "main.h"
#include "ext/spoofer/CallStack-Spoofer.h"

using namespace std;

void SetConsoleSize(int width, int height) {
    SPOOF_FUNC;

    HWND console = GetConsoleWindow();

    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, width, height, TRUE);

    LONG style = GetWindowLong(console, GWL_STYLE);
    style &= ~(WS_SIZEBOX | WS_MAXIMIZEBOX);
    SetWindowLong(console, GWL_STYLE, style);
}
void CreateConsole() {
    SPOOF_FUNC;

    AllocConsole();
    FILE* newStdout;
    freopen_s(&newStdout, "CONOUT$", "w", stdout);
    freopen_s(&newStdout, "CONOUT$", "w", stderr);
    freopen_s(&newStdout, "CONIN$", "r", stdin);
    std::cout.clear();
    std::cerr.clear();
    std::cin.clear();
    std::wcout.clear();
    std::wcerr.clear();
    std::wcin.clear();
}
std::wstring string_to_wstring(const std::string& str) {
    SPOOF_FUNC;

    if (str.empty()) {
        return std::wstring();
    }

    // Determine the size of the destination wide string, including null terminator
    size_t requiredSize = 0;
    mbstowcs_s(&requiredSize, nullptr, 0, str.c_str(), 0);

    if (requiredSize == 0) {
        throw std::runtime_error("Conversion error occurred");
    }

    // Create a wide string buffer of the appropriate size
    std::wstring wstr(requiredSize, L'\0');

    // Perform the conversion
    size_t convertedChars = 0;
    mbstowcs_s(&convertedChars, &wstr[0], requiredSize, str.c_str(), requiredSize - 1);

    // Remove the null terminator that mbstowcs_s adds to the string
    wstr.resize(convertedChars - 1);

    return wstr;
}

std::string generateRandomString(size_t size) {
    SPOOF_FUNC;
    const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    const size_t max_index = sizeof(charset) - 2; // Adjusted to avoid out-of-bounds access

    std::string randomString(size, 0);
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, max_index);

    for (size_t i = 0; i < size; ++i) {
        randomString[i] = charset[distribution(generator)];
    }

    return randomString;
}

bool download_driver(const std::string& url, const std::string& filename) {
    SPOOF_FUNC;
    std::string command = "curl -o \"" + filename + "\" \"" + url + "\"" + " > nul 2>&1";
    return (system(command.c_str()) == 0);
}

bool delete_file(const std::string& filename) {
    SPOOF_FUNC;
    return std::filesystem::remove(filename);
}




void loadDriver() {
    SPOOF_FUNC;

    system(_("cls"));
    SetConsoleTitleA((LPCSTR)generateRandomString(164).c_str());
    std::cout << _("~~~~~~~~~~~~~~~~~~~~~~~~~~~ Apex Matic ~~~~~~~~~~~~~~~~~~~~~~~~~~~") << std::endl;
    std::cout << _("") << std::endl;
    std::cout << _("") << std::endl;
    std::cout << _("MAKE SURE THE GAME IS CLOSED!") << std::endl;
    std::cout << _("") << std::endl;
    std::cout << _("") << std::endl;
    std::cout << _("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~") << std::endl;
    system(_("pause"));
    system(_("cls"));
    std::cout << _("LOADING") << std::endl;
    system(_("taskkill /F /IM r5apex.exe > nul 2>&1"));
    Sleep(500);
    system(_("taskkill /F /IM EpicGamesLauncher.exe > nul 2>&1"));
    system(_("taskkill /F /IM EasyAntiCheatLauncher.exe > nul 2>&1"));
    system(_("taskkill /F /IM BEService.exe > nul 2>&1"));
    system(_("taskkill /F /IM BattleEyeLauncher.exe > nul 2>&1"));
    system(_("taskkill /F /IM Steam.exe > nul 2>&1"));
    system("wevtutil cl System");
    system(_("cls"));

    Sleep(500);


    std::string url = "";
    std::string filename = "C:\\Windows\\System32\\drivers\\" + generateRandomString(12);
    if (download_driver(url, filename)) {
    }
    else {
        std::cout << _("FAILD TO LOAD DRIVER") << std::endl;
        std::cout << _("Common Fixes: ") << std::endl;
        std::cout << _("- Disable firewall or DNS") << std::endl;
        std::cout << _("- Disable any antivirus") << std::endl;
        std::cout << _("- Try again") << std::endl;
        std::cout << _("- Restarting your PC") << std::endl;
        system(_("pause"));
        return;
    }

    int r = kdmain(string_to_wstring(filename));

    delete_file(filename);
    system("wevtutil cl System");
    system("for /F \"tokens = \" %1 in ('wevtutil el') DO wevtutil cl \" % 1\"");
    system(_("cls"));
    if (r == -1) {
        //SFC /scannow
        std::cout << _("FAILD TO LOAD DRIVER") << std::endl;
        system(_("SFC /scannow"));
        std::cout << _("") << std::endl;
        std::cout << _("Common Fixes: ") << std::endl;
        std::cout << _("- Disable any antivirus") << std::endl;
        std::cout << _("- Try again") << std::endl;
        std::cout << _("- Restarting your PC") << std::endl;
        system(_("pause"));
        return;
    }
    else{
        std::cout << _("LOADED") << std::endl;
    }

    system(_("pause"));
}


void consoleTitle() {
    SPOOF_FUNC;

    while (true) {
        SetConsoleTitleA((LPCSTR)generateRandomString(32).c_str());
        Sleep(1000);
    }
}

void startmeu() {
    SPOOF_FUNC;

    system(_("cls"));
    std::thread overlayThread(OverlayThread);
    std::cout << _("~~~~~~~~~~~~~~~~~~~~~~~~~~~ Apex Matic ~~~~~~~~~~~~~~~~~~~~~~~~~~~") << std::endl;
    std::cout << _("[+] Made by @Joelmatic [+]") << std::endl;
    std::cout << _("") << std::endl;
    std::cout << _("MAKE SURE TO MAP THE DRIVER BEFORE LOADING THE CHEAT") << std::endl;
    std::wcout << _("1 - Load Cheat") << std::endl;
    std::cout << _("") << std::endl;
    std::wcout << _("2 - MAP Driver") << std::endl;
    std::cout << _("") << std::endl;

    std::string input;
    cin >> input;

    if (input == "1") {
        cheatloop();
    }
    if (input == "2") {
        loadDriver();
        startmeu();
    }

    startmeu();
    system("pause");
}

static int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nCmdShow) {
    SPOOF_FUNC;

    SetConsoleSize(1200, 600);
    screenSize.x = GetSystemMetrics(SM_CXSCREEN);
    screenSize.y = GetSystemMetrics(SM_CYSCREEN);

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    std::locale::global(std::locale(_("en_US.UTF-8")));
    std::wcout.imbue(std::locale());

    CreateConsole();

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_CHECK_ALWAYS_DF | _CRTDBG_DELAY_FREE_MEM_DF);

    std::thread consoleTitleThread(consoleTitle);

    startmeu();
    system("pause");
}