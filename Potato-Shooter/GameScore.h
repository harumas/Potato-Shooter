#pragma once

class GameScore
{
	int total = 0;
	int font_handle;
	bool is_clear_flag = false;

public:
	GameScore()
	{
		font_handle = CreateFontToHandle("BIZ UD Gothic", 12, 5, DX_FONTTYPE_EDGE);
	}

	void add(int delta)
	{
		if (delta < 0)
		{
			delta = 0;
		}

		total += delta;
	}

	int get()
	{
		return total;
	}

	bool is_clear()
	{
		return is_clear_flag;
	}

	void draw()
	{
		DrawRotaFormatStringToHandle(30, 30, 2, 2, 0, 0, 0, GetColor(255, 255, 255), font_handle, GetColor(0, 0, 0), FALSE, "Score: %ld", total);
	}

	void set_status(bool is_clear)
	{
		is_clear_flag = is_clear;
	}

	void reset()
	{
		total = 0;
		is_clear_flag = false;
	}
};
