#include "renderer.h"
#include <vector>
#include <random>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <filesystem>
#include "../ext/spoofer/CallStack-Spoofer.h"

std::string getBuildID() {
    SPOOF_FUNC;

    // Extract the time components
    int hour = std::stoi(std::string(__TIME__).substr(0, 2));
    int minute = std::stoi(std::string(__TIME__).substr(3, 2));
    int second = std::stoi(std::string(__TIME__).substr(6, 2));

    // Convert the time to minutes since midnight
    int totalMinutes = hour * 60 + minute;

    // Extract the day component from the date
    int day = std::stoi(std::string(__DATE__).substr(4, 2));

    // Generate a 6-digit build ID
    // We'll use a combination of total minutes and day to ensure the number remains within 6 digits
    int buildID = (totalMinutes * 100) + (day % 100); // Ensure day component is two digits

    // Convert the build ID to a string
    std::ostringstream oss;
    oss << std::setw(6) << std::setfill('0') << buildID; // Ensure the build ID is 6 digits long
    return oss.str();
}

std::string watermarkText = "APEX Matic ";
std::string buildInfoText = "- Public Build - Build ID : " + getBuildID() + "  ";

void renderer::drawLine(const ImVec2& a, const ImVec2& b, ImU32 color, bool shadow)
{
    SPOOF_FUNC;

	if (shadow)
		ImGui::GetForegroundDrawList()->AddLine(a, b, IM_COL32_BLACK, 3.f);

	ImGui::GetForegroundDrawList()->AddLine(a, b, color, 1.f);
}

void renderer::drawBoxWithShadow(const ImVec2& topLeft, const ImVec2& bottomRight, ImU32 color, bool shadow) {
    SPOOF_FUNC;

    ImVec2 shadowOffset = ImVec2(5, 5); // Offset for the shadow

    // Box coordinates
    ImVec2 topRight = ImVec2(bottomRight.x, topLeft.y);
    ImVec2 bottomLeft = ImVec2(topLeft.x, bottomRight.y);

    // Draw shadow if enabled
    if (shadow) {
        ImU32 shadowColor = IM_COL32(0, 0, 0, 128); // Semi-transparent black for shadow
        drawLine(topLeft + shadowOffset, topRight + shadowOffset, shadowColor, false);
        drawLine(topRight + shadowOffset, bottomRight + shadowOffset, shadowColor, false);
        drawLine(bottomRight + shadowOffset, bottomLeft + shadowOffset, shadowColor, false);
        drawLine(bottomLeft + shadowOffset, topLeft + shadowOffset, shadowColor, false);
    }

    // Draw the white box
    drawLine(topLeft, topRight, color, false);
    drawLine(topRight, bottomRight, color, false);
    drawLine(bottomRight, bottomLeft, color, false);
    drawLine(bottomLeft, topLeft, color, false);
}

void renderer::drawCross(const ImVec2& center, float size, ImU32 color, bool shadow)
{
    SPOOF_FUNC;

    float thickness = 2.0f;

    ImVec2 horizontalStart(center.x - size, center.y - thickness / 2.0f);
    ImVec2 horizontalEnd(center.x + size, center.y + thickness / 2.0f);
    ImVec2 verticalStart(center.x - thickness / 2.0f, center.y - size);
    ImVec2 verticalEnd(center.x + thickness / 2.0f, center.y + size);

    ImDrawList* drawList = ImGui::GetForegroundDrawList();
    drawList->AddRectFilled(horizontalStart, horizontalEnd, color);
    drawList->AddRectFilled(verticalStart, verticalEnd, color);
}

void renderer::drawText(const ImVec2& a, ImU32 color, const std::string& text, bool shadow)
{
    SPOOF_FUNC;

    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
    if (shadow)
    {
        ImGui::GetForegroundDrawList()->AddText(a + ImVec2(0.f, 1.f), IM_COL32_BLACK, text.c_str());
        ImGui::GetForegroundDrawList()->AddText(a - ImVec2(0.f, 1.f), IM_COL32_BLACK, text.c_str());
        ImGui::GetForegroundDrawList()->AddText(a - ImVec2(1.f, 0.f), IM_COL32_BLACK, text.c_str());
        ImGui::GetForegroundDrawList()->AddText(a + ImVec2(1.f, 0.f), IM_COL32_BLACK, text.c_str());
    }

    ImGui::GetForegroundDrawList()->AddText(a, color, text.c_str());
    ImGui::PopFont();
}

void drawTextFont(const ImVec2& a, ImU32 color, const std::string& text, bool shadow)
{
    SPOOF_FUNC;

    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
    if (shadow)
    {
        ImGui::GetForegroundDrawList()->AddText(a + ImVec2(0.f, 1.f), IM_COL32_BLACK, text.c_str());
        ImGui::GetForegroundDrawList()->AddText(a - ImVec2(0.f, 1.f), IM_COL32_BLACK, text.c_str());
        ImGui::GetForegroundDrawList()->AddText(a - ImVec2(1.f, 0.f), IM_COL32_BLACK, text.c_str());
        ImGui::GetForegroundDrawList()->AddText(a + ImVec2(1.f, 0.f), IM_COL32_BLACK, text.c_str());
    }

    ImGui::GetForegroundDrawList()->AddText(a, color, text.c_str());
    ImGui::PopFont();
}

void renderer::drawCircleOutline(const ImVec2& center, float radius, ImU32 color) {
    SPOOF_FUNC;
    ImGui::GetForegroundDrawList()->AddCircle(center, radius, color, 0, 2.0f);
}

void renderer::drawCircleFilled(const ImVec2& center, float radius, ImU32 color) {
    SPOOF_FUNC;
    ImGui::GetForegroundDrawList()->AddCircleFilled(center, radius, color, 0);
}

// Comparator function to sort strings by rendered width in descending order
bool compareByRenderedWidthDescending(const std::string& a, const std::string& b) {
    SPOOF_FUNC;
    return ImGui::CalcTextSize(a.c_str()).x > ImGui::CalcTextSize(b.c_str()).x;
}


ImU32 generatePurpleColor(std::mt19937& gen) {
    SPOOF_FUNC;
    std::uniform_int_distribution<> dis(0, 255);
    int r, g, b;

    // Ensure the colors are different shades of purple
    r = dis(gen) / 2 + 128; // Make sure red is between 128 and 255
    g = dis(gen) / 4;       // Make sure green is between 0 and 63
    b = dis(gen) / 2 + 128; // Make sure blue is between 128 and 255

    return IM_COL32(r, g, b, 255);
}
