#pragma once
class Canvas
{
private:
public:
	Canvas() {};
	virtual void onRender() = 0;
	~Canvas() {};
};