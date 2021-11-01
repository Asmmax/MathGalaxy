#pragma once

class Application
{
private:
	bool _isValid;
private:
	Application();

public:
	~Application();
	Application(const Application& other) = delete;
	void operator=(const Application& other) = delete;
	static Application& getInstance();

	int run();
};