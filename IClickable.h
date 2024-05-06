#pragma once

/// <summary>
/// Abstract class for clickable game objects
/// </summary>
class IClickable
{
public:
	void virtual onClick() = 0;
	void virtual onHover() = 0;
};