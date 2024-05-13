#include "Cursor.h"

//note: 本当はWM_MOUSEMOVEのタイミングで行うのが適切 
void Cursor::update()
{
	if (is_custom)
	{
		SetCursor(current);
	}
}

void Cursor::set_cursor(LPSTR id)
{
	is_custom = id != system_cursor;
	current = LoadCursor(NULL, id);
	SetCursor(current);
}
