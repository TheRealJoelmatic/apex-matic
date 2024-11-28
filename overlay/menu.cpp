#include "../ext/imgui/imgui.h"
#include "../global.h"
#include "../ext/xor/xor_cc.hpp"
#include <Windows.h>
#include "../ext/imgui/imgui_internal.h"
#include <map>
#include "../modules/modules.h"
#include <random>
#include "../ext/spoofer/CallStack-Spoofer.h"

void RandomizeSkinChangerValues() {
    SPOOF_FUNC;

    // Create a random device and generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Define the ranges for each skin
    std::uniform_int_distribution<> disP2020(1, 10);
    std::uniform_int_distribution<> disRE45(1, 16);
    std::uniform_int_distribution<> disALTERNATOR(1, 16);
    std::uniform_int_distribution<> disR99(1, 16);
    std::uniform_int_distribution<> disR301(1, 18);
    std::uniform_int_distribution<> disSPITFIRE(1, 16);
    std::uniform_int_distribution<> disG7(1, 21);

    std::uniform_int_distribution<> disFLATLINE(1, 20);
    std::uniform_int_distribution<> disHEMLOCK(1, 18);
    std::uniform_int_distribution<> disPROWLER(1, 11);
    std::uniform_int_distribution<> disREPEATER(1, 11);
    std::uniform_int_distribution<> disRAMPAGE(1, 11);
    std::uniform_int_distribution<> disCAR(1, 11);

    std::uniform_int_distribution<> disHAVOC(1, 14);
    std::uniform_int_distribution<> disLSTAR(1, 11);
    std::uniform_int_distribution<> disTRIPLETAKE(1, 11);
    std::uniform_int_distribution<> disVOLT(1, 14);
    std::uniform_int_distribution<> disNEMESIS(1, 9);

    std::uniform_int_distribution<> disMOZAMBIQUE(1, 11);
    std::uniform_int_distribution<> disPEACEKEEPER(1, 16);
    std::uniform_int_distribution<> disMASTIFF(1, 11);

    std::uniform_int_distribution<> disWINGMAN(1, 11);
    std::uniform_int_distribution<> disLONGBOW(1, 11);
    std::uniform_int_distribution<> disCHARGE_RIFLE(1, 11);
    std::uniform_int_distribution<> disSENTINEL(1, 10);

    std::uniform_int_distribution<> disEVA8(1, 11);
    std::uniform_int_distribution<> disDEVOTION(1, 11);
    std::uniform_int_distribution<> disBOCEK(1, 11);
    std::uniform_int_distribution<> disKRABER(1, 11);

    // Assign random values to each skin
    modules::SkinChangerValues::SkinP2020 = disP2020(gen);
    modules::SkinChangerValues::SkinRE45 = disRE45(gen);
    modules::SkinChangerValues::SkinALTERNATOR = disALTERNATOR(gen);
    modules::SkinChangerValues::SkinR99 = disR99(gen);
    modules::SkinChangerValues::SkinR301 = disR301(gen);
    modules::SkinChangerValues::SkinSPITFIRE = disSPITFIRE(gen);
    modules::SkinChangerValues::SkinG7 = disG7(gen);

    modules::SkinChangerValues::SkinFLATLINE = disFLATLINE(gen);
    modules::SkinChangerValues::SkinHEMLOCK = disHEMLOCK(gen);
    modules::SkinChangerValues::SkinPROWLER = disPROWLER(gen);
    modules::SkinChangerValues::SkinREPEATER = disREPEATER(gen);
    modules::SkinChangerValues::SkinRAMPAGE = disRAMPAGE(gen);
    modules::SkinChangerValues::SkinCAR = disCAR(gen);

    modules::SkinChangerValues::SkinHAVOC = disHAVOC(gen);
    modules::SkinChangerValues::SkinLSTAR = disLSTAR(gen);
    modules::SkinChangerValues::SkinTRIPLETAKE = disTRIPLETAKE(gen);
    modules::SkinChangerValues::SkinVOLT = disVOLT(gen);
    modules::SkinChangerValues::SkinNEMESIS = disNEMESIS(gen);

    modules::SkinChangerValues::SkinMOZAMBIQUE = disMOZAMBIQUE(gen);
    modules::SkinChangerValues::SkinPEACEKEEPER = disPEACEKEEPER(gen);
    modules::SkinChangerValues::SkinMASTIFF = disMASTIFF(gen);

    modules::SkinChangerValues::SkinWINGMAN = disWINGMAN(gen);
    modules::SkinChangerValues::SkinLONGBOW = disLONGBOW(gen);
    modules::SkinChangerValues::SkinCHARGE_RIFLE = disCHARGE_RIFLE(gen);
    modules::SkinChangerValues::SkinSENTINEL = disSENTINEL(gen);

    modules::SkinChangerValues::SkinEVA8 = disEVA8(gen);
    modules::SkinChangerValues::SkinDEVOTION = disDEVOTION(gen);
    modules::SkinChangerValues::SkinBOCEK = disBOCEK(gen);
    modules::SkinChangerValues::SkinKRABER = disKRABER(gen);
}

using namespace ImGui;

struct checkbox_animation {
    float animation;
};

bool CCheckbox(const char* label, bool* v)
{
    SPOOF_FUNC;
    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(label);
    const ImVec2 label_size = CalcTextSize(label, NULL, true);

    const float w = GetWindowWidth() - 30;
    const float square_sz = 17;
    const ImVec2 pos = window->DC.CursorPos;
    const ImRect frame_bb(ImVec2(pos.x + w - square_sz - 13.0f, pos.y), ImVec2(pos.x + w, pos.y + square_sz - 1.0f));
    const ImRect total_bb(pos, ImVec2(pos.x + square_sz + (label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f), pos.y + label_size.y + style.FramePadding.y * 2.0f));
    ItemSize(total_bb, style.FramePadding.y);
    if (!ItemAdd(total_bb, id))
    {
        IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags | ImGuiItemStatusFlags_Checkable | (*v ? ImGuiItemStatusFlags_Checked : 0));
        return false;
    }

    bool hovered, held;
    bool pressed = ButtonBehavior(frame_bb, id, &hovered, &held);
    if (pressed)
    {
        *v = !(*v);
        MarkItemEdited(id);
    }

    static std::map <ImGuiID, checkbox_animation> anim;
    auto it_anim = anim.find(id);
    if (it_anim == anim.end())
    {
        anim.insert({ id, { 0.0f } });
        it_anim = anim.find(id);
    }

    it_anim->second.animation = ImLerp(it_anim->second.animation, *v ? 1.0f : 0.0f, 0.12f * (1.0f - ImGui::GetIO().DeltaTime));

    RenderNavHighlight(total_bb, id);

    RenderFrame(frame_bb.Min, frame_bb.Max, ImColor(15, 15, 16), false, 9.0f);
    RenderFrame(frame_bb.Min, frame_bb.Max, ImColor(56 / 255.0f, 101 / 255.0f, 242 / 255.0f, it_anim->second.animation), false, 9.0f);

    window->DrawList->AddCircleFilled(ImVec2(frame_bb.Min.x + 8 + 14 * it_anim->second.animation, frame_bb.Min.y + 8), 5.0f, ImColor(1.0f, 1.0f, 1.0f), 30);

    if (label_size.x > 0.0f)
        RenderText(total_bb.Min, label);

    IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags | ImGuiItemStatusFlags_Checkable | (*v ? ImGuiItemStatusFlags_Checked : 0));
    return pressed;
}


void CenteredColoredText(const char* text, float r, float g, float b)
{
    SPOOF_FUNC;
    ImVec4 color = ImVec4(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
    ImGui::PushStyleColor(ImGuiCol_Text, color);
    ImVec2 windowSize = ImGui::GetWindowSize();
    ImVec2 textSize = ImGui::CalcTextSize(text);
    ImGui::SetCursorPosX((windowSize.x - textSize.x) * 0.5f);
    ImGui::Text("%s", text);
    ImGui::PopStyleColor();
}

void ShowGlowModeDropdown(const char* label, int& glowMode) {
    SPOOF_FUNC;
    const char* glowModeItems[] = {
        "Blue outline",         // 4
        "Blue Flashing",        // 13
        "Blue Full",            // 44
        "Gold outline",         // 15 (already covered by Yellow outline)
        "Green outline",        // 20
        "Lime Full",            // 2
        "Orange outline",       // 1
        "Orange Full",          // 36
        "Purple outline",       // 35
        "Red outline",          // 19
        "White outline",        // 9
        "White Full",           // 59
        "Yellow outline",       // 15
        "Yellow Flashing"       // 11
        "Black Full"       // 75
    };

    int glowModeValues[] = {
        4, 13, 44, 15, 20, 2, 1, 36, 35, 19, 9, 59, 15, 11,75
    };

    static int currentItem = 0; // Default selected item index

    // Find current item based on glowMode
    for (int i = 0; i < IM_ARRAYSIZE(glowModeValues); ++i) {
        if (glowMode == glowModeValues[i]) {
            currentItem = i;
            break;
        }
    }

    if (ImGui::BeginCombo(label, glowModeItems[currentItem])) {
        for (int n = 0; n < IM_ARRAYSIZE(glowModeItems); n++) {
            bool isSelected = (currentItem == n);
            if (ImGui::Selectable(glowModeItems[n], isSelected)) {
                currentItem = n;
                glowMode = glowModeValues[n]; // Set the glowMode based on selected value
            }
            if (isSelected) {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }
}

void ShowViewModelGlowDropdown(const char* label, int& viewModelGlowID) {
    SPOOF_FUNC;
    const char* viewModelGlowItems[] = {
        "Blue Full",        // 25
        "Cyan outline",     // 13
        "Cyan Glitch",      // 24
        "Cyan Full",        // 30
        "Cyan Flash",       // 31
        "Hot Pink solid",   // 36
        "Orange Outline",   // 27
        "Orange lines",     // 37
        "Orange Outline (thin)", // 39
        "Red Flash",        // 18
        "Red Flash",        // 32
        "White solid",      // 34
        "White lines",      // 74
        "Yellow solid",      // 29
        "Purple solid",      // 50
        "Black solid"      // 75
    };

    int viewModelGlowIDs[] = {
        25, 13, 24, 30, 31, 36, 27, 37, 39, 18, 32, 34, 74, 29, 50, 75
    };

    static int currentItem = 0; // Default selected item index

    // Find current item based on viewModelGlowID
    for (int i = 0; i < IM_ARRAYSIZE(viewModelGlowIDs); ++i) {
        if (viewModelGlowID == viewModelGlowIDs[i]) {
            currentItem = i;
            break;
        }
    }

    if (ImGui::BeginCombo(label, viewModelGlowItems[currentItem])) {
        for (int n = 0; n < IM_ARRAYSIZE(viewModelGlowItems); n++) {
            bool isSelected = (currentItem == n);
            if (ImGui::Selectable(viewModelGlowItems[n], isSelected)) {
                currentItem = n;
                viewModelGlowID = viewModelGlowIDs[n]; // Set the viewModelGlowID based on selected value
            }
            if (isSelected) {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }
}

const char* items[] = { "Dynamic", "Static" };
static int item_current_idx = 0; // Current item selected

void rendermenu() {
    SPOOF_FUNC;

    if (!modules::menuopen) {
        return;
    }

    ImGui::SetNextWindowSize(ImVec2(1000, 600), ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2(screenSize.x / 2, screenSize.y / 2), ImGuiCond_FirstUseEver);

    ImGui::Begin(_("menu"), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
    
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
    CenteredColoredText(_("Apex Matic - Full (@Joelmatic)"), 160, 32, 240);
    ImGui::PopFont();

    ImGui::Text(_(""));

    if (ImGui::BeginTabBar(_("MyTabBar")))
    {
        if (ImGui::BeginTabItem(_("Glow")))
        {
            ImGui::Text(_(""));
            ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
            CenteredColoredText(_("Glow"), 240, 160, 32);
            ImGui::PopFont();
            ImGui::Text(_(""));
            ImGui::Separator();
            ImGui::Separator();
            ImGui::Text(_(""));

            CCheckbox(_("Glow"), &modules::glow);
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("Give everyone an glow outline");

            CCheckbox(_("Ignore Self"), &modules::glowIgnoreSelf);
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(_("Will not glow you in thrid person"));

            ImGui::Text(_("Glow Mode     "));
            ImGui::SameLine();
            if (ImGui::BeginCombo(_("##combo"), items[item_current_idx]))
            {
                for (int n = 0; n < IM_ARRAYSIZE(items); n++)
                {
                    const bool is_selected = (item_current_idx == n);
                    if (ImGui::Selectable(items[n], is_selected))
                    {
                        item_current_idx = n; 
                        if (item_current_idx == 0)
                        {
                            modules::staticGlow = false;
                        }
                        else
                        {
                            modules::staticGlow = true;
                        }
                    }
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }

            if (modules::staticGlow) {
                ImGui::Text(_("Glow Color     "));
                ImGui::SameLine();
                ShowGlowModeDropdown("    ", modules::glowMode);

                ImGui::InputInt("(Glow ID) ", &modules::glowMode);
            }

            ImGui::Text(_(""));
            ImGui::Separator();
            ImGui::Separator();

            ImGui::Text(_(""));
            ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
            CenteredColoredText(_("Veiw Model Glow"), 240, 160, 32);
            ImGui::PopFont();
            ImGui::Text(_(""));
            ImGui::Separator();
            ImGui::Separator();
            ImGui::Text(_(""));

            CCheckbox(_("Glow "), &modules::ViewModelGlows);
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("Make your self glow");

            ShowViewModelGlowDropdown("  ", modules::ViewModelglowMode);
            ImGui::InputInt("(Glow ID)", &modules::ViewModelglowMode);

            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem(_("ESP ")))
        {
            ImGui::Text(_(""));
            ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
            CenteredColoredText(_("ESP"), 240, 160, 32);
            ImGui::PopFont();
            ImGui::Text(_(""));
            ImGui::Separator();
            ImGui::Separator();

            CCheckbox(_("ESP "), &modules::esp);
            CCheckbox(_("Ignore Self "), &modules::espIgnoreSelf);
            ImGui::Text(_("Max Distance "));
            ImGui::SameLine();
            ImGui::SliderFloat("##     ", &modules::espMaxDistance, 5000, 20000);

            CCheckbox(_("Bone "), &modules::boneESP);

            CCheckbox(_("Boxs 2d "), &modules::Boxs2d);
            CCheckbox(_("Snaplines "), &modules::snaplines);

            CCheckbox(_("Crosshair "), &modules::crosshair);

            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem(_("Aimbot ")))
        {
            ImGui::Text(_(""));
            ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
            CenteredColoredText(_("Aimbot"), 240, 160, 32);
            ImGui::PopFont();
            ImGui::Text(_(""));
            ImGui::Separator();
            ImGui::Separator();
            ImGui::Text(_(""));

            CCheckbox(_("Aimbot "), &modules::aimbot);
            CCheckbox(_("Ingore Knocked "), &modules::aimbotIngoreKnocked);
            CCheckbox(_("Show Fov Circle "), &modules::fovcirlce);

            ImGui::Text(_("Fov Circle Size"));
            ImGui::SameLine();
            ImGui::SliderFloat("##  ", &modules::AimFOV, 0, 10);

            ImGui::Text(_("Max Distance"));
            ImGui::SameLine();
            ImGui::SliderFloat("##     ", &modules::aimbotMaxDistance, 0, 20000);

            ImGui::Text(_(""));
            ImGui::Separator();
            ImGui::Separator();
            ImGui::Text(_(""));

            ImGui::Text(_("Speed     "));
            ImGui::SameLine();
            ImGui::SliderFloat("##    ", &modules::speed, 0, 20);

            //ImGui::Text(_("Smoothness"));
            //ImGui::SameLine();
            //ImGui::SliderFloat("##   ", &modules::smoothness, 30, 10);
            //ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem(_("Skin Changer")))
        {
            ImGui::Text(_(""));
            ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
            CenteredColoredText(_("Skin Changer"), 240, 160, 32);
            ImGui::PopFont();
            ImGui::Text(_(""));
            ImGui::Separator();
            ImGui::Separator();
            ImGui::Text(_(""));

            CCheckbox(_("Enabled"), &modules::SkinChanger);
            CCheckbox(_("One Size Fits All"), &modules::oneSize);

            ImGui::Text(_(""));
            ImGui::Separator();
            ImGui::Separator();
            ImGui::Text(_(""));

            if (modules::oneSize) {
                ImGui::SliderInt(_("Skin ID"), &modules::SkinId, 0, 20);
            }
            else {
                if (ImGui::Button(_("Randomize"))) {
                    RandomizeSkinChangerValues();
                }
                ImGui::Text(_(""));
                Vector2D itemSize = { 300, 350 };

                ImGui::BeginChild(_("Group 1"), ImVec2(itemSize.x, itemSize.y), true);
                ImGui::TextColored(ImVec4(0.990, 0.768, 0.039, 1.00f), _("Light"));

                ImGui::Text("P2020");
                ImGui::SliderInt("##P2020", &modules::SkinChangerValues::SkinP2020, 0, 10);
                ImGui::Text("RE-45 Auto");
                ImGui::SliderInt("##RE45", &modules::SkinChangerValues::SkinRE45, 0, 16);
                ImGui::Text("Alternator SMG");
                ImGui::SliderInt("##ALTERNATOR", &modules::SkinChangerValues::SkinALTERNATOR, 0, 16);
                ImGui::Text("R-99 SMG");
                ImGui::SliderInt("##R99", &modules::SkinChangerValues::SkinR99, 0, 16);
                ImGui::Text("R-301 Carbine");
                ImGui::SliderInt("##R301", &modules::SkinChangerValues::SkinR301, 0, 18);
                ImGui::Text("M600 Spitfire");
                ImGui::SliderInt("##SPITFIRE", &modules::SkinChangerValues::SkinSPITFIRE, 0, 16);
                ImGui::Text("G7 Scout");
                ImGui::SliderInt("##G7", &modules::SkinChangerValues::SkinG7, 0, 21);

                ImGui::EndChild();

                ImGui::SameLine();

                // Group 2
                ImGui::BeginChild("Group 2", ImVec2(itemSize.x, itemSize.y), true);
                ImGui::TextColored(ImVec4(0.00990, 0.990, 0.761, 1.00f), "Heavy");
                ImGui::Text("VK-47 Flatline");
                ImGui::SliderInt("##FLATLINE", &modules::SkinChangerValues::SkinFLATLINE, 0, 20);
                ImGui::Text("Hemlock Burst AR");
                ImGui::SliderInt("##HEMLOCK", &modules::SkinChangerValues::SkinHEMLOCK, 0, 18);
                ImGui::Text("Prowler Burst SMG");
                ImGui::SliderInt("##PROWLER", &modules::SkinChangerValues::SkinPROWLER, 0, 11);
                ImGui::Text("30-30 Repeater");
                ImGui::SliderInt("##REPEATER", &modules::SkinChangerValues::SkinREPEATER, 0, 11);
                ImGui::Text("Rampage LMG");
                ImGui::SliderInt("##RAMPAGE", &modules::SkinChangerValues::SkinRAMPAGE, 0, 11);
                ImGui::Text("C.A.R SMG");
                ImGui::SliderInt("##CAR", &modules::SkinChangerValues::SkinCAR, 0, 11);
                ImGui::EndChild();

                ImGui::SameLine();

                // Group 3
                ImGui::BeginChild("Group 3", ImVec2(itemSize.x, itemSize.y), true);
                ImGui::TextColored(ImVec4(0, 0.99, 0, 1.00f), "Energy");
                ImGui::Text("Havoc Rifle");
                ImGui::SliderInt("##HAVOC", &modules::SkinChangerValues::SkinHAVOC, 0, 14);
                ImGui::Text("L-Star EMG");
                ImGui::SliderInt("##LSTAR", &modules::SkinChangerValues::SkinLSTAR, 0, 11);
                ImGui::Text("Triple-Take");
                ImGui::SliderInt("##TRIPLETAKE", &modules::SkinChangerValues::SkinTRIPLETAKE, 0, 11);
                ImGui::Text("Volt");
                ImGui::SliderInt("##VOLT", &modules::SkinChangerValues::SkinVOLT, 0, 14);
                ImGui::Text("Nemesis Burst AR");
                ImGui::SliderInt("##NEMESIS", &modules::SkinChangerValues::SkinNEMESIS, 0, 9);

                ImGui::EndChild();

                ImGui::Spacing();

                // Group 4
                ImGui::BeginChild("Group 4", ImVec2(itemSize.x, itemSize.y), true);
                ImGui::TextColored(ImVec4(0.99, 0, 0, 1.00f), "Shotguns");

                ImGui::Text("Mozambique");
                ImGui::SliderInt("##MOZAMBIQUE", &modules::SkinChangerValues::SkinMOZAMBIQUE, 0, 11);
                ImGui::Text("Peacekeeper");
                ImGui::SliderInt("##PEACEKEEPER", &modules::SkinChangerValues::SkinPEACEKEEPER, 0, 16);
                ImGui::Text("Mastiff");
                ImGui::SliderInt("##MASTIFF", &modules::SkinChangerValues::SkinMASTIFF, 0, 11);

                ImGui::EndChild();

                ImGui::SameLine();

                // Group 5
                ImGui::BeginChild("Group 5", ImVec2(itemSize.x, itemSize.y), true);
                ImGui::TextColored(ImVec4(0.00990, 0.337, 0.990, 1.00f), "Snipers");

                ImGui::Text("Wingman");
                ImGui::SliderInt("##WINGMAN", &modules::SkinChangerValues::SkinWINGMAN, 0, 11);
                ImGui::Text("Longbow DMR");
                ImGui::SliderInt("##LONGBOW", &modules::SkinChangerValues::SkinLONGBOW, 0, 11);
                ImGui::Text("Charge Rifle");
                ImGui::SliderInt("##CHARGE_RIFLE", &modules::SkinChangerValues::SkinCHARGE_RIFLE, 0, 11);
                ImGui::Text("Sentinel");
                ImGui::SliderInt("##SENTINEL", &modules::SkinChangerValues::SkinSENTINEL, 0, 10);

                ImGui::EndChild();

                ImGui::SameLine();

                // Group 6
                ImGui::BeginChild("Group 6", ImVec2(itemSize.x, itemSize.y), true);
                ImGui::TextColored(ImVec4(0.99, 0.530, 0.945, 1.00f), "Legendary");

                ImGui::Text("EVA-8 Auto");
                ImGui::SliderInt("##EVA8", &modules::SkinChangerValues::SkinEVA8, 0, 11);
                ImGui::Text("Devotion LMG");
                ImGui::SliderInt("##DEVOTION", &modules::SkinChangerValues::SkinDEVOTION, 0, 11);
                ImGui::Text("Bocek Compound Bow");
                ImGui::SliderInt("##BOCEK", &modules::SkinChangerValues::SkinBOCEK, 0, 11);
                ImGui::Text("Kraber .50-CAL Sniper");
                ImGui::SliderInt("##KRABER", &modules::SkinChangerValues::SkinKRABER, 0, 11);

                ImGui::EndChild();
                
            }
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem(_("Other")))
        {
            CCheckbox(_("Stream Proof"), &modules::streamproof);
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    ImGui::End();
}