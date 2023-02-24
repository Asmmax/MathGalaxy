#pragma once
#include <string>

class AWidget
{
private:
	std::string _name;
	AWidget* _parent;
	bool _isVisible;
	int _width;
	int _height;
public:
	AWidget(const std::string& name, int width = 0, int height = 0);
	virtual ~AWidget() {}

	void setParent(AWidget* parent);

	void setVisible(bool visible);
	bool getVisible() const { return _isVisible; }

	void setup();

protected:
	virtual void setupContent() = 0;

private:
	void setupAsChild();
	void setupAsRoot();
};
