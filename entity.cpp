#include "entity.h"

Entity::Entity()
{

}

Entity::~Entity()
{

}

double Entity::X()
{
	return x;
}

double Entity::X(double nx)
{
	x = nx;
	return x;
}

double Entity::Y()
{
	return y;
}

double Entity::Y(double ny)
{
	y = ny;
	return y;
}

Engine *Entity::get_engine()
{
	return eng_handle;
}

void Entity::set_engine(Engine *handle)
{
	eng_handle = handle;
}
