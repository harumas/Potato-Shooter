#pragma once
#include <vector>
#include "Device.h"
#include "Module.h"

class GUI
{
private:
	bool prev_enter = false;
	bool enabled = false;

protected:
	ResourceHandler* handler;

	GUI();
	virtual bool in_range(int mouse_x, int mouse_y) = 0;

public:
	virtual void set_handler(ResourceHandler* handler);
	virtual void load(ServiceLocator* locator) = 0;

	virtual void on_enter() {};
	virtual void on_mouse_down() {};
	virtual void on_mouse_up() {};
	virtual void on_exit() {};
	virtual void on_enable() {};
	virtual void on_disable() {};

	bool is_enabled();
	void enable();
	void disable();

	virtual	void update(int mouse_x, int mouse_y, bool is_mouse_down, bool is_mouse_up);

	virtual void draw() = 0;
};


class GUIUpdater
{
public:
	static void register_gui(GUI* gui);
	static void set_service(ServiceLocator& locator);
	static void update();
	static void draw();
	static void clear();

private:
	static std::vector<GUI*> guis;
	static shared_ptr<Device> device;
	static shared_ptr<ResourceHandler> handler;
	static ServiceLocator* locator;
};


