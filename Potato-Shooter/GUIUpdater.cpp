#include "GUI.h"
#include "ServiceLocator.h" 

std::vector<GUI*> GUIUpdater::guis = std::vector<GUI*>();
shared_ptr<ResourceHandler> GUIUpdater::handler = nullptr;
shared_ptr<Device> GUIUpdater::device = nullptr;
ServiceLocator* GUIUpdater::locator = nullptr;

void GUIUpdater::register_gui(GUI* gui)
{
	gui->set_handler(handler.get());
	gui->load(locator);
	guis.emplace_back(gui);
}

void GUIUpdater::set_service(ServiceLocator& locator)
{
	GUIUpdater::locator = &locator;
	GUIUpdater::handler = locator.resolve<ResourceHandler>();
	GUIUpdater::device = locator.resolve<Device>();
}

void GUIUpdater::clear()
{
	guis.clear();
	guis.shrink_to_fit();
}

void GUIUpdater::update()
{
	int mouse_x = device->mouse_x;
	int mouse_y = device->mouse_y;
	bool is_mouse_down = device->is_mouse_down(MOUSE_INPUT_LEFT);
	bool is_mouse_up = device->is_mouse_up(MOUSE_INPUT_LEFT);

	for (GUI* gui : guis)
	{
		if (gui->is_enabled())
		{
			gui->update(mouse_x, mouse_y, is_mouse_down, is_mouse_up);
		}
	}
}

void GUIUpdater::draw()
{
	for (GUI* gui : guis)
	{
		if (gui->is_enabled())
		{
			gui->draw();
		}
	}
}

