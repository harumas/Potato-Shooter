#pragma once

#include "Extension.h"
#include "ResourceHandler.h" 
#include "ServiceLocator.h" 
#include "Device.h" 
#include "Time.h" 
#include "Weapon.h" 

class Entity
{
protected:
	std::shared_ptr<ResourceHandler> handler_owner; //インスタンスの所有権

	Entity(ServiceLocator& locator) :
		enabled(false)
	{
		handler_owner = locator.resolve<ResourceHandler>();
	};
	bool enabled;

public:
	virtual void update(const double& dt) = 0;
	virtual void draw() = 0;
	virtual void post_draw() {};
	virtual void enable() = 0;
	virtual void disable() = 0;

	bool is_enabled() const
	{
		return enabled;
	};
};


