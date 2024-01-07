#include "renderHelper.hpp"

ImVec4 Renderer::mapRGBAToVectorColor(int red, int green, int blue, float alpha)
{
    return ImVec4(red / 255.f, green / 255.f, blue / 255.f, alpha);
}

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::howToPlayRender(GLuint program)
{
}

void Renderer::aiPlayRender(GLuint program)
{
}

void Renderer::playMenuRender(GLuint program)
{
}

void Renderer::menuRender(int width, int height, gameState *state)
{
    // TODO create buttons and use some text idk
    ImGuiStyle *style = &ImGui::GetStyle();
    ImGui::StyleColorsDark(style);
    colorS gold = cHelper.getColor(GOLD);
    colorS d_purple = cHelper.getColor(DEEP_PURPLE);
    style->Colors[ImGuiCol_WindowBg] = mapRGBAToVectorColor(d_purple.red, d_purple.green, d_purple.blue, 0.5f);
    style->Colors[ImGuiCol_Button] = mapRGBAToVectorColor(d_purple.red, d_purple.green, d_purple.blue, 0.5f);
    style->Colors[ImGuiCol_ButtonHovered] = mapRGBAToVectorColor(d_purple.red, d_purple.green, d_purple.blue, 1.f);
    style->Colors[ImGuiCol_Text] = mapRGBAToVectorColor(gold.red, gold.green, gold.blue, 1.f);
    style->WindowRounding = 1.f;
    style->WindowBorderSize = 1.f;
    // style.
    const float unit = ImGui::GetFontSize();
    // Init menu GUI
    ImGui::Begin("Game menu", nullptr, windowFlag);
    ImGui::SetWindowSize(ImVec2(width - 4 * unit, height - 4 * unit));
    ImGui::SetWindowPos(ImVec2(2 * unit, 2 * unit));
    // Print GUI name of game
    ImGui::SetWindowFontScale(2.0f);
    ImGui::SetCursorPos(ImVec2((width - ImGui::CalcTextSize(gameName).x) * 0.5f, (height - 200.f) / 5));
    ImGui::Text("HEROES OF DERILIA");
    ImGui::SetWindowFontScale(1.25f);
    // Create centered buttons
    ImGui::SetCursorPos(ImVec2((width - 270) * 0.5f, (height - 200.f) / 5 * 2));
    if (ImGui::Button("Play vs AI", ImVec2(270, 50)))
    {
        state->PlayVsAI();
    }
    ImGui::SetCursorPos(ImVec2((width - 270) * 0.5f, (height - 200.f) / 5 * 3));
    if (ImGui::Button("2 Player mode locally", ImVec2(270, 50)))
    {
        state->PlayLocalPVP();
    }
    ImGui::SetCursorPos(ImVec2((width - 270) * 0.5f, (height - 200.f) / 5 * 4));
    if (ImGui::Button("How to Play", ImVec2(270, 50)))
    {
        state->HowToPlay();
    }
    ImGui::SetCursorPos(ImVec2((width - 270) * 0.5f, (height - 200.f)));
    if (ImGui::Button("Exit game", ImVec2(270, 50)))
    {
        state->Exit();
    }
    ImGui::End();
}

void Renderer::localPvPRender(GLuint program)
{
}
