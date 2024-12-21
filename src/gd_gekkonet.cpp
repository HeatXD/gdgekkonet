#include "gd_gekkonet.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void GekkoNet::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_num_players"), &GekkoNet::get_num_players);
	ClassDB::bind_method(D_METHOD("set_num_players", "num_players"), &GekkoNet::set_num_players);
	ClassDB::bind_method(D_METHOD("get_input_size"), &GekkoNet::get_input_size);
	ClassDB::bind_method(D_METHOD("set_input_size", "input_size"), &GekkoNet::set_input_size);
	ClassDB::bind_method(D_METHOD("get_max_spectators"), &GekkoNet::get_max_spectators);
	ClassDB::bind_method(D_METHOD("set_max_spectators", "num_spectators"), &GekkoNet::set_max_spectators);
	ClassDB::bind_method(D_METHOD("get_input_prediction_window"), &GekkoNet::get_input_prediction_window);
	ClassDB::bind_method(D_METHOD("set_input_prediction_window", "window"), &GekkoNet::set_input_prediction_window);
	ClassDB::bind_method(D_METHOD("get_state_size"), &GekkoNet::get_state_size);
	ClassDB::bind_method(D_METHOD("set_state_size", "state_size"), &GekkoNet::set_state_size);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "num_players", PROPERTY_HINT_RANGE, "0,255,2"), "set_num_players", "get_num_players");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "input_size"), "set_input_size", "get_input_size");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "max_spectators", PROPERTY_HINT_RANGE, "0,255,2"), "set_max_spectators", "get_max_spectators");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "input_prediction_window", PROPERTY_HINT_RANGE, "0,255,2"), "set_input_prediction_window", "get_input_prediction_window");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "state_size"), "set_state_size", "get_state_size");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "spectator_delay", PROPERTY_HINT_RANGE, "0,128,1"), "set_spectator_delay", "get_spectator_delay");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "limited_saving"), "set_limited_saving", "get_limited_saving");
}

GekkoNet::GekkoNet()
{
	_config = {};
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

void GekkoNet::set_num_players(unsigned char num_players)
{
}

unsigned char GekkoNet::get_num_players()
{
    return 0;
}

void GekkoNet::set_input_size(int input_size)
{
}

int GekkoNet::get_input_size()
{
    return 0;
}

void GekkoNet::set_max_spectators(unsigned char num_spectators)
{
}

unsigned char GekkoNet::get_max_spectators()
{
    return 0;
}

void GekkoNet::set_input_prediction_window(unsigned char window)
{
}

unsigned char GekkoNet::get_input_prediction_window()
{
    return 0;
}

void GekkoNet::set_state_size(int state_size)
{
}

int GekkoNet::get_state_size()
{
    return 0;
}

void GekkoNet::set_limited_saving(bool limited_saving)
{
}

bool GekkoNet::get_limited_saving()
{
    return false;
}

void GekkoNet::set_spectator_delay(unsigned char delay)
{
}

unsigned short GekkoNet::get_spectator_delay()
{
    return 0;
}
