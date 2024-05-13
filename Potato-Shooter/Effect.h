#pragma once
#include <string>
#include "Module.h"
#include "GUI.h"
#include "DelayPromise.h"
#include "ResourceHandler.h" 

class Effect :public GUI
{
public:
	Effect(string data_path, int count, int width, double ext_rate);
	~Effect();
	void play(Vector2 point, double duration);
	void update(int mouse_x, int mouse_y, bool is_mouse_down, bool is_mouse_up) override;
	void draw() override;
	bool is_playing();

	virtual void load(ServiceLocator* locator) override;

protected:
	bool in_range(int mouse_x, int mouse_y) override;

private:
	shared_ptr<Time> timer;

	bool playing = false;
	int* frames = nullptr;
	int frame_count = 0;

	Vector2Int draw_point = Vector2Int(0, 0);
	double ext_rate = 0;
	double frame_time_unit = 0;
	double current_time = 0;
	int current_frame = 0;
};

