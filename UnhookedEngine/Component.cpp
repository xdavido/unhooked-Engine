#include "Component.h"

Component::Component(GameObject* owner)
{
	type = COMP_Type::NONE;
	active = true;
	this->owner = owner;
}

Component::~Component()
{
}

