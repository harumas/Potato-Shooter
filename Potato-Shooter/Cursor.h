#include <windows.h>

class Cursor
{
public:
	void update();
	void set_cursor(LPSTR id);

private:
	HCURSOR current;
	LPSTR system_cursor = IDC_ARROW;
	bool is_custom;
};
