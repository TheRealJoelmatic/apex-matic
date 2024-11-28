#pragma once

#include <string>

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

#define IMGUI_DEFINE_MATH_OPERATORS
#include "../ext/imgui/imgui.h"
#include "../ext/imgui/imgui_internal.h"
#include "../ext/imgui/imgui_impl_win32.h"
#include "../ext/imgui/imgui_impl_dx11.h"

inline bool renderModulesList = true;
inline bool renderModules = true;
inline bool renderWaterMark = true;
inline bool sortModules = true;

inline bool buildInfo = true;
inline bool showWaterMarkOnModules = false;
inline bool showWaterMarkOnTopLeft = true;

inline float spacing = 1.5f;
inline float xPosition = 10.0f;
inline float yPosition = 5.0f;

struct RGB {
	int red, green, blue;
};

namespace renderer
{
	void drawLine(const ImVec2& a, const ImVec2& b, ImU32 color, bool shadow = true);
	void drawCross(const ImVec2& center, float size, ImU32 color, bool shadow = false);
	void drawText(const ImVec2& a, ImU32 color, const std::string& text, bool shadow = true);
	void drawCircleOutline(const ImVec2& center, float radius, ImU32 color);
	void drawBoxWithShadow(const ImVec2& topLeft, const ImVec2& bottomRight, ImU32 color, bool shadow);
	void drawCircleFilled(const ImVec2& center, float radius, ImU32 color);
	void watermark();
}
