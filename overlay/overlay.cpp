#include <windows.h>
#include <d3d11.h>
#include <thread>
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <string>
#include <iomanip> // For formatting
#include <sstream>
#pragma comment(lib, "d3d11.lib")
#include "../ext/imgui/imgui.h"
#include "../ext/imgui/imgui_impl_dx11.h"
#include "../ext/imgui/imgui_impl_win32.h"
#include "../ext/imgui/imgui_internal.h"
#include <tchar.h>
#include "menu.h"

#include "font/tahoma.h"
#include "font/MuseoSansCyrl-500_0.h"
#include "theme.h"
#include "../modules/modules.h"
#include "renderer.h"
#include "../global.h"
#include "../modules/features/esp.h"
#include <dwmapi.h>
#include <dcomp.h>
#include "../main.h"
#include "../ext/spoofer/CallStack-Spoofer.h"

static ID3D11Device* g_pd3dDevice = nullptr;
static ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
static IDXGISwapChain* g_pSwapChain = nullptr;
static UINT g_ResizeWidth = 0, g_ResizeHeight = 0;
static ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;

bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LARGE_INTEGER frequency;
LARGE_INTEGER lastTime;
int frameCount = 0;
float fps = 0.0f;

void InitializeTiming() {
    SPOOF_FUNC;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&lastTime);
}

void UpdateFPS() {
    SPOOF_FUNC;
    LARGE_INTEGER currentTime;
    QueryPerformanceCounter(&currentTime);

    float deltaTime = static_cast<float>(currentTime.QuadPart - lastTime.QuadPart) / frequency.QuadPart;

    frameCount++;
    if (deltaTime >= 1.0f) { // Update every second
        fps = static_cast<float>(frameCount) / deltaTime;
        frameCount = 0;
        lastTime = currentTime;
    }
}

void DisplayFPS() {
    SPOOF_FUNC;
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1) << fps; // Format FPS to one decimal place
    std::string fpsText = "OVERLAY FPS: " + oss.str();
    renderer::drawText({ 10,10 }, IM_COL32(255, 255, 255, 255), fpsText.c_str(), false);
}

void OverlayThread()
{
    SPOOF_FUNC;
    try {
        WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"JUP", nullptr };
        ::RegisterClassExW(&wc);

        HWND hwnd = ::CreateWindowExW(WS_EX_TOPMOST | WS_EX_TOOLWINDOW, wc.lpszClassName, L"JUP", WS_POPUP, 0, 0, GetSystemMetrics(SM_CXSCREEN) / 0.90, GetSystemMetrics(SM_CYSCREEN) / 0.90, nullptr, nullptr, wc.hInstance, nullptr);

        SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 255, LWA_ALPHA);
        MARGINS margin = { -1 };
        DwmExtendFrameIntoClientArea(hwnd, &margin);

        if (!CreateDeviceD3D(hwnd))
        {
            CleanupDeviceD3D();
            ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
            return;
        }

        ::ShowWindow(hwnd, SW_SHOWDEFAULT);
        ::UpdateWindow(hwnd);

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

        ImGuiContext& g = *GImGui;

        io.IniFilename = nullptr;
        io.LogFilename = nullptr;

        ImFontConfig icons_config;
        ImFontConfig CustomFont;

        static const ImWchar icons_ranges[] = { 0xf000, 0xf3ff, 0 };

        CustomFont.FontDataOwnedByAtlas = false;

        icons_config.MergeMode = true;
        icons_config.PixelSnapH = true;
        icons_config.OversampleH = 3;
        icons_config.OversampleV = 3;

        io.Fonts->AddFontFromMemoryTTF((void*)LexendRegularfont, sizeof(LexendRegularfont), 17.f, &CustomFont);
        io.Fonts->AddFontFromMemoryTTF((void*)LexendRegularfont, sizeof(LexendRegularfont), 21.f, &CustomFont);
        io.Fonts->AddFontFromMemoryTTF((void*)LexendRegularfont, sizeof(LexendRegularfont), 40.f, &CustomFont);
        io.Fonts->AddFontFromMemoryTTF((void*)LexendRegularfont, sizeof(LexendRegularfont), 60.f, &CustomFont);
        io.Fonts->AddFontDefault();

        ImGui::StyleColorsDark();
        theme();

        ImGui_ImplWin32_Init(hwnd);
        ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

        ImVec4 clear_color = ImVec4(0.f, 0.f, 0.f, 0.f);

        InitializeTiming(); // Initialize timing here

        const int targetFPS = 60;
        const float targetFrameTime = 1.0f / targetFPS; // Approx 16.67 ms per frame
        LARGE_INTEGER frameStartTime, frameEndTime, elapsedMicroseconds;

        bool done = false;
        while (!done)
        {
            QueryPerformanceCounter(&frameStartTime);

            if (GetAsyncKeyState(VK_INSERT) & 1)
            {
                modules::menuopen = !modules::menuopen;
            }

            MSG msg;
            while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
            {
                ::TranslateMessage(&msg);
                ::DispatchMessage(&msg);

                if (msg.message == WM_QUIT)
                {
                    done = true;
                    break;
                }
            }

            if (done)
            {
                break;
            }

            if (g_ResizeWidth != 0 && g_ResizeHeight != 0)
            {
                CleanupRenderTarget();
                g_pSwapChain->ResizeBuffers(0, g_ResizeWidth, g_ResizeHeight, DXGI_FORMAT_UNKNOWN, 0);
                g_ResizeWidth = g_ResizeHeight = 0;
                CreateRenderTarget();
            }

            ImGui_ImplDX11_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();

            UpdateFPS();
            DisplayFPS();

            esp();

            if (modules::fovincirlce) {
                renderer::drawCircleFilled({ screenSize.x / 2, screenSize.y / 2 }, 100 * modules::AimFOV, IM_COL32(0, 0, 0, 125));
            }
            if (modules::fovcirlce) {
                renderer::drawCircleOutline({ screenSize.x / 2, screenSize.y / 2 }, 100 * modules::AimFOV, IM_COL32(255, 255, 255, 255));
            }


            if (modules::crosshair) {
                renderer::drawCross({ screenSize.x / 2, screenSize.y / 2 }, 10, IM_COL32(255, 255, 255, 255));
            }

            if (modules::menuopen) {
                rendermenu();
                SetWindowLong(hwnd, GWL_EXSTYLE, WS_EX_TOPMOST);
            }
            else {
                SetWindowLong(hwnd, GWL_EXSTYLE, WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED);
            }

            if (modules::streamproof) {
                SetWindowDisplayAffinity(hwnd, WDA_EXCLUDEFROMCAPTURE);
            }
            else {
                SetWindowDisplayAffinity(hwnd, WDA_NONE);
            }


            ImGui::Render();
            const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
            g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr);
            g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

            g_pSwapChain->Present(1, 0);
        }

        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();

        CleanupDeviceD3D();
        ::DestroyWindow(hwnd);
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
    }
    catch (const std::exception& e) {
        OverlayThread();
    }
}

bool CreateDeviceD3D(HWND hWnd)
{
    SPOOF_FUNC;
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 3;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    sd.SampleDesc.Count = 1;

    UINT createDeviceFlags = 0;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    HRESULT res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res == DXGI_ERROR_UNSUPPORTED)
        res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res != S_OK)
        return false;

    CreateRenderTarget();
    return true;
}

void CleanupDeviceD3D()
{
    SPOOF_FUNC;
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = nullptr; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = nullptr; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = nullptr; }
}

void CreateRenderTarget()
{
    SPOOF_FUNC;
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_mainRenderTargetView);
    pBackBuffer->Release();
}

void CleanupRenderTarget()
{
    SPOOF_FUNC;
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = nullptr; }
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    SPOOF_FUNC;
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
    {
        return true;
    }

    switch (msg)
    {
    case WM_SIZE:
        if (wParam == SIZE_MINIMIZED)
            return 0;
        g_ResizeWidth = (UINT)LOWORD(lParam);
        g_ResizeHeight = (UINT)HIWORD(lParam);
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU)
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }

    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}