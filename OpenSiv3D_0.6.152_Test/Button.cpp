#include "stdafx.h"
#include "Button.h"

Button::Button(Rect buttonObj, Color color) :
	m_buttonObj(buttonObj),m_buttonNormalColor(color),
	m_buttonOverColor(Palette::Red),m_buttonClickColor(Palette::Gray)
{

}

bool Button::ButtonClicked()
{
	return m_buttonObj.leftReleased();
}

void Button::Draw()
{
	if (m_buttonObj.mouseOver())
	{
		if (m_buttonObj.leftClicked())
		{
			m_buttonObj.draw(m_buttonClickColor);
		}
		else
		{
			m_buttonObj.draw(m_buttonOverColor);
		}
	}
	else
	{
		m_buttonObj.draw(m_buttonNormalColor);
	}
}
