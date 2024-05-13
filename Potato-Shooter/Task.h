#pragma once

#include "ServiceLocator.h"

class Task
{
public:
	virtual void initialize(ServiceLocator& locator) = 0;
	virtual void start() = 0;
	virtual void execute(const double& dt) = 0;
	virtual void draw() = 0;
	virtual void post_draw() {};
	virtual bool is_starting() = 0;
	virtual bool is_executing() = 0;
};
