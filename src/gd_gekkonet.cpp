#include "gd_gekkonet.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void GekkoNet::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("hello_node"), &GekkoNet::hello_node);
}

GekkoNet::GekkoNet()
{
	gekko_create(&_session);
}

GekkoNet::~GekkoNet()
{
	gekko_destroy(_session);
}

// Override built-in methods with your own logic. Make sure to declare them in the header as well!

void GekkoNet::_ready()
{
}

void GekkoNet::_process(double delta)
{
}

godot::String GekkoNet::hello_node()
{
	return "Hello GekkoNet Node!\n";
}
