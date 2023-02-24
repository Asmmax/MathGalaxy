#pragma once
#include "IApplicationImpl.hpp"
#include <memory>
#include <vector>

class GLFWApplicationImpl : public IApplicationImpl
{
private:
	std::vector<std::shared_ptr<IWindowImpl>> _windows;

public:
	bool init() override;
	void terminate() override;
	IWindowImpl* createWindow(int width, int height, const std::string& title) override;
};
