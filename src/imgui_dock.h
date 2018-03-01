#pragma once


namespace ImGui
{


IMGUI_API void ShutdownDock();
IMGUI_API void RootDock(const ImVec2& pos, const ImVec2& size);
IMGUI_API bool BeginDock(const char* label, bool* opened = nullptr, ImGuiWindowFlags extra_flags = 0, const ImVec2& default_size = ImVec2(-1, -1));
IMGUI_API void EndDock();
IMGUI_API void SetDockActive();
IMGUI_API void SaveDock();
IMGUI_API void LoadDock(bool load_default);

// hacks
IMGUI_API bool isDockDocked(const char* label);
IMGUI_API bool isNonDockedDockAt(const ImVec2& pos);
IMGUI_API void setTabActive(const char *label);


} // namespace ImGui