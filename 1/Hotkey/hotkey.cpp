#include "hotkey.h"

Hotkey& Hotkey::hot()
{
	static Hotkey ins;
	return ins;
}

void Hotkey::start()
{
	if (key == 0)
	{
		Aimbotkey = 0x02;
	}
	if (key == 1)
	{
		Aimbotkey = 0x01;
	}
	if (key == 2)
	{
		Aimbotkey = 0x04;
	}
	if (key == 3)
	{
		Aimbotkey = 0x05;
	}
	if (key == 4)
	{
		Aimbotkey = 0x08;
	}
	if (key == 5)
	{
		Aimbotkey = 0x0D;
	}
	if (key == 6)
	{
		Aimbotkey = 0x10;
	}
	if (key == 7)
	{
		Aimbotkey = 0x11;
	}
	if (key == 8)
	{
		Aimbotkey = 0x12;

	}
	if (key == 9)
	{
		Aimbotkey = 0x13;
	}

}