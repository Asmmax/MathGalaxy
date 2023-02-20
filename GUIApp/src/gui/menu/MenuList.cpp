#include "gui/menu/MenuList.hpp"
#include "imgui.h"

MenuList::MenuList(const std::string& name):
    _name(name),
    _isEnabled(true)
{
}

void MenuList::enable()
{
    _isEnabled = true;
}

void MenuList::disable()
{
    _isEnabled = false;
}

void MenuList::setup()
{
    if (ImGui::BeginMenu(_name.c_str(), _isEnabled))
    {
        for (auto& item : _items) {
            item->setup();
        }

        ImGui::EndMenu();
    }
}

void MenuList::addItem(const std::shared_ptr<IMenuItem>& item)
{
	_items.push_back(item);
}

void MenuList::Separator::setup()
{
    ImGui::Separator();
}

void MenuList::addSeparator()
{
    _items.push_back(std::make_shared<Separator>());
}
