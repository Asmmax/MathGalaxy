#pragma once
#include <string>

class AWidget
{
private:
	std::string _name;
	AWidget* _parent;
	bool _isVisible;
public:
	AWidget(const std::string& name);
	virtual ~AWidget() {}

	void setParent(AWidget* parent);

	void setVisible(bool visible);
	bool getVisible() const { return _isVisible; }

	void setup();

protected:
	virtual void draw() = 0;

private:
	void drawAsChild();
	void drawAsRoot();
};
