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

void Renderer::howToPlayRender(int width, int height, gameState *state)
{
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
    const float unit = ImGui::GetFontSize();
    float window_width = width - 4 * unit;
    // Init how to play menu GUI
    ImGui::SetNextWindowPos(ImVec2(2 * unit, 2 * unit));
    ImGui::Begin("How to play", nullptr, windowFlag);
    ImGui::SetWindowSize(ImVec2(window_width, height - 4 * unit));
    // Display How to play text
    ImGui::SetWindowFontScale(2.0f);
    ImGui::SetCursorPos(ImVec2((window_width - ImGui::CalcTextSize(howToPlayS).x) * 0.5f, 4 * unit));
    ImGui::Text(howToPlayS);
    // Init scrollable child window
    ImGui::SetWindowFontScale(1.25f);
    ImGui::SetNextWindowPos(ImVec2(2 * unit + 200, height - (height - 4 * unit - 200) - 100));
    ImGui::BeginChild("How to play description", ImVec2(window_width - 400, height - 4 * unit - 200), true, childWindowFlags);
    ImGui::SetCursorPos(ImVec2(4 * unit, 2 * unit));
    ImGui::PushTextWrapPos(window_width - 400 - 4 * unit);
    ImGui::Text(howToPlayDesc);
    ImGui::EndChild();
    ImGui::SetCursorPos(ImVec2(4 * unit, 4 * unit));
    if (ImGui::Button("Back", ImVec2(70, 50)))
    {
        state->PrintStateList();
        state->Back();
    }
    ImGui::End();
}

void Renderer::aiPlayRender(int width, int height, gameState *state, GLuint gearTexture)
{
    ImGuiStyle *style = &ImGui::GetStyle();
    ImGui::StyleColorsDark(style);
    colorS silver = cHelper.getColor(SILVER);
    // colorS lightBlack = cHelper.getColor(LIGHT_BLACK);
    style->Colors[ImGuiCol_Button] = mapRGBAToVectorColor(silver.red, silver.green, silver.blue, 0.01f);
    style->Colors[ImGuiCol_ButtonHovered] = mapRGBAToVectorColor(silver.red, silver.green, silver.blue, 0.1f);
    ImGui::Begin("Toggle Menu", nullptr, toggleMenuFlags);
    if (ImGui::ImageButton((void *)(intptr_t)gearTexture, ImVec2(16, 16)))
    {
        state->PlayMenu();
    }
    ImGui::End();
}

void Renderer::playMenuRender(int width, int height, gameState *state)
{
    ImGuiStyle *style = &ImGui::GetStyle();
    ImGui::StyleColorsDark(style);
    colorS silver = cHelper.getColor(SILVER);
    colorS lightBlack = cHelper.getColor(LIGHT_BLACK);
    style->Colors[ImGuiCol_WindowBg] = mapRGBAToVectorColor(silver.red, silver.green, silver.blue, 0.1f);
    style->Colors[ImGuiCol_Button] = mapRGBAToVectorColor(silver.red, silver.green, silver.blue, 0.5f);
    style->Colors[ImGuiCol_ButtonHovered] = mapRGBAToVectorColor(silver.red, silver.green, silver.blue, 0.8f);
    style->Colors[ImGuiCol_Text] = mapRGBAToVectorColor(lightBlack.red, lightBlack.green, lightBlack.blue, 1.f);
    style->WindowRounding = 5.f;
    ImGui::Begin("Play Menu", nullptr, playMenuFlags);
    if (ImGui::Button("Back", ImVec2(100, 50))) {
        state->Back();
    }
    ImGui::End();
}

void Renderer::menuRender(int width, int height, gameState *state)
{
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
    const float unit = ImGui::GetFontSize();
    float window_width = width - 4 * unit;
    // Init menu GUI
    ImGui::Begin("Game menu", nullptr, windowFlag);
    ImGui::SetWindowSize(ImVec2(window_width, height - 4 * unit));
    ImGui::SetWindowPos(ImVec2(2 * unit, 2 * unit));
    // Print GUI name of game
    ImGui::SetWindowFontScale(2.0f);
    ImGui::SetCursorPos(ImVec2((window_width - ImGui::CalcTextSize(gameName).x) * 0.5f, (height - 200.f) / 5));
    ImGui::Text(gameName);
    ImGui::SetWindowFontScale(1.25f);
    // Create centered buttons
    // TODO fix buttons width based on length of string 
    ImGui::SetCursorPos(ImVec2((window_width - 270) * 0.5f, (height - 200.f) / 5 * 2));
    if (ImGui::Button("Play vs AI", ImVec2(270, 50)))
    {
        state->PlayVsAI();
    }
    ImGui::SetCursorPos(ImVec2((window_width - 270) * 0.5f, (height - 200.f) / 5 * 3));
    if (ImGui::Button("2 Player mode locally", ImVec2(270, 50)))
    {
        state->PlayLocalPVP();
    }
    ImGui::SetCursorPos(ImVec2((window_width - 270) * 0.5f, (height - 200.f) / 5 * 4));
    if (ImGui::Button("How to Play", ImVec2(270, 50)))
    {
        state->HowToPlay();
    }
    ImGui::SetCursorPos(ImVec2((window_width - 270) * 0.5f, (height - 200.f)));
    if (ImGui::Button("Exit game", ImVec2(270, 50)))
    {
        state->Exit();
    }
    ImGui::End();
}

void Renderer::localPvPRender(GLuint program)
{
}
