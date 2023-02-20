#include "gui/MenuPanel.hpp"
#include "gui/menu/MenuList.hpp"
#include "imgui.h"

void MenuPanel::setup()
{
    if (ImGui::BeginMainMenuBar())
    {
        for (auto& list : _lists) {
            list->setup();
        }

        ImGui::EndMainMenuBar();
    }
}

void MenuPanel::addList(const std::shared_ptr<MenuList>& list)
{
    _lists.push_back(list);
}
