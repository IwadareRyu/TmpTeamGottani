#pragma once
class Button
{
public:
	Button(Rect buttonObj,Color color);
	~Button() {};
	bool ButtonClicked();
	void Draw();
	Rect m_buttonObj;
	Color m_buttonNormalColor;
	Color m_buttonOverColor;
	Color m_buttonClickColor;
};

