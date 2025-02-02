#include "gd_gekkonet.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

GekkoNet *GekkoNet::singleton = nullptr;

void GekkoNetConfig::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_num_players"), &GekkoNetConfig::get_num_players);
	ClassDB::bind_method(D_METHOD("set_num_players", "num_players"), &GekkoNetConfig::set_num_players);
	ClassDB::bind_method(D_METHOD("get_input_size"), &GekkoNetConfig::get_input_size);
	ClassDB::bind_method(D_METHOD("set_input_size", "input_size"), &GekkoNetConfig::set_input_size);
	ClassDB::bind_method(D_METHOD("get_max_spectators"), &GekkoNetConfig::get_max_spectators);
	ClassDB::bind_method(D_METHOD("set_max_spectators", "num_spectators"), &GekkoNetConfig::set_max_spectators);
	ClassDB::bind_method(D_METHOD("get_input_prediction_window"), &GekkoNetConfig::get_input_prediction_window);
	ClassDB::bind_method(D_METHOD("set_input_prediction_window", "window"), &GekkoNetConfig::set_input_prediction_window);
	ClassDB::bind_method(D_METHOD("get_state_size"), &GekkoNetConfig::get_state_size);
	ClassDB::bind_method(D_METHOD("set_state_size", "state_size"), &GekkoNetConfig::set_state_size);
	ClassDB::bind_method(D_METHOD("get_spectator_delay"), &GekkoNetConfig::get_spectator_delay);
	ClassDB::bind_method(D_METHOD("set_spectator_delay", "delay"), &GekkoNetConfig::set_spectator_delay);
	ClassDB::bind_method(D_METHOD("get_limited_saving"), &GekkoNetConfig::get_limited_saving);
	ClassDB::bind_method(D_METHOD("set_limited_saving", "limited_saving"), &GekkoNetConfig::set_limited_saving);
	ClassDB::bind_method(D_METHOD("get_desync_detection"), &GekkoNetConfig::get_desync_detection);
	ClassDB::bind_method(D_METHOD("set_desync_detection", "desync_detection"), &GekkoNetConfig::set_desync_detection);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "num_players", PROPERTY_HINT_RANGE, "0,255"), "set_num_players", "get_num_players");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "input_size"), "set_input_size", "get_input_size");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "max_spectators", PROPERTY_HINT_RANGE, "0,255"), "set_max_spectators", "get_max_spectators");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "input_prediction_window", PROPERTY_HINT_RANGE, "0,255"), "set_input_prediction_window", "get_input_prediction_window");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "state_size"), "set_state_size", "get_state_size");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "spectator_delay", PROPERTY_HINT_RANGE, "0,128"), "set_spectator_delay", "get_spectator_delay");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "limited_saving"), "set_limited_saving", "get_limited_saving");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "desync_detection"), "set_desync_detection", "get_desync_detection");
}

GekkoNetConfig::GekkoNetConfig()
{
	num_players = 0;
	input_size = 0;
	max_spectators = 0;
	input_prediction_window = 0;
	state_size = 0;
	spectator_delay = 0;
	limited_saving = false;
	desync_detection = false;
}

GekkoNetConfig::~GekkoNetConfig()
{
}

void GekkoNetConfig::set_num_players(unsigned char num_players)
{
	this->num_players = num_players;
}

unsigned char GekkoNetConfig::get_num_players()
{
	return num_players;
}

void GekkoNetConfig::set_input_size(int input_size)
{
	this->input_size = input_size;
}

int GekkoNetConfig::get_input_size()
{
	return input_size;
}

void GekkoNetConfig::set_max_spectators(unsigned char num_spectators)
{
	max_spectators = num_spectators;
}

unsigned char GekkoNetConfig::get_max_spectators()
{
	return max_spectators;
}

void GekkoNetConfig::set_input_prediction_window(unsigned char window)
{
	input_prediction_window = window;
}

unsigned char GekkoNetConfig::get_input_prediction_window()
{
	return input_prediction_window;
}

void GekkoNetConfig::set_state_size(int state_size)
{
	this->state_size = state_size;
}

int GekkoNetConfig::get_state_size()
{
	return state_size;
}

void GekkoNetConfig::set_limited_saving(bool limited_saving)
{
	this->limited_saving = limited_saving;
}

bool GekkoNetConfig::get_limited_saving()
{
	return limited_saving;
}

void GekkoNetConfig::set_desync_detection(bool desync_detection)
{
	this->desync_detection = desync_detection;
}

bool GekkoNetConfig::get_desync_detection()
{
	return desync_detection;
}

void GekkoNetConfig::set_spectator_delay(unsigned char delay)
{
	spectator_delay = delay;
}

unsigned char GekkoNetConfig::get_spectator_delay()
{
	return spectator_delay;
}

void GekkoNet::_bind_methods()
{
	// METHODS
	ClassDB::bind_method(D_METHOD("start_session", "config", "local_port"), &GekkoNet::start_session);
	ClassDB::bind_method(D_METHOD("stop_session"), &GekkoNet::stop_session);
	ClassDB::bind_method(D_METHOD("update_session_events"), &GekkoNet::update_session_events);
	ClassDB::bind_method(D_METHOD("update_game_events"), &GekkoNet::update_game_events);
	ClassDB::bind_method(D_METHOD("add_actor", "player_type", "address"), &GekkoNet::add_actor);
	ClassDB::bind_method(D_METHOD("set_local_delay", "local_player", "delay"), &GekkoNet::set_local_delay);
	ClassDB::bind_method(D_METHOD("frames_ahead"), &GekkoNet::frames_ahead);
	ClassDB::bind_method(D_METHOD("add_local_input", "local_player", "input"), &GekkoNet::add_local_input);

	// PLAYER TYPE
	BIND_CONSTANT(LocalPlayer);
	BIND_CONSTANT(RemotePlayer);
	BIND_CONSTANT(Spectator);

	// GAME EVENT TYPE
	BIND_CONSTANT(EmptyGameEvent);
	BIND_CONSTANT(AdvanceEvent);
	BIND_CONSTANT(SaveEvent);
	BIND_CONSTANT(LoadEvent);

	// SESSION EVENT TYPE
	BIND_CONSTANT(EmptySessionEvent);
	BIND_CONSTANT(PlayerSyncing);
	BIND_CONSTANT(PlayerConnected);
	BIND_CONSTANT(PlayerDisconnected);
	BIND_CONSTANT(SessionStarted);
	BIND_CONSTANT(SpectatorPaused);
	BIND_CONSTANT(SpectatorUnpaused);
	BIND_CONSTANT(DesyncDetected);

	// Callbacks
	ClassDB::bind_method(D_METHOD("cb_advance_game", "callable"), &GekkoNet::cb_advance_game);
	ClassDB::bind_method(D_METHOD("cb_load_game", "callable"), &GekkoNet::cb_load_game);
	ClassDB::bind_method(D_METHOD("cb_save_game", "callable"), &GekkoNet::cb_save_game);
}
GekkoNet *GekkoNet::get_singleton()
{
	return singleton;
}

GekkoNet::GekkoNet()
{
	CRASH_COND(singleton != nullptr);
	singleton = this;
}

GekkoNet::~GekkoNet()
{
	CRASH_COND(singleton != this);
	singleton = nullptr;
	stop_session();
}

void GekkoNet::start_session(Ref<GekkoNetConfig> config, unsigned short local_port)
{
	if (config.is_null())
		return;

	gekko_create(&_session);
	gekko_start(_session, config.ptr());

	if (local_port == 0)
		return;

	// maybe later allow for custom adapters
	gekko_net_adapter_set(_session, gekko_default_adapter(local_port));
}

void GekkoNet::stop_session()
{
	gekko_destroy(_session);
	_session = nullptr;
}

void GekkoNet::update_session_events()
{
	if (_session == nullptr)
		return;

	int count = 0;
	auto events = gekko_session_events(_session, &count);

	for (int i = 0; i < count; i++)
	{
		auto ev = events[i];
		godot::UtilityFunctions::print("Session Event:", ev->type);
	}
}

void GekkoNet::update_game_events()
{
	if (_session == nullptr)
		return;

	int count = 0;
	auto updates = gekko_update_session(_session, &count);

	for (int i = 0; i < count; i++)
	{
		auto ev = updates[i];
		godot::PackedByteArray data_arr;

		switch (ev->type)
		{
		case AdvanceEvent:
			if (on_advance_game.is_null())
				break;
			data_arr.resize(ev->data.adv.input_len);
			memcpy(data_arr.ptrw(), ev->data.adv.inputs, ev->data.adv.input_len);
			on_advance_game.call(data_arr);
			break;
		case SaveEvent:
			if (on_save_game.is_null())	
				break;
			handle_save_event(&ev->data.save);
			break;
		case LoadEvent:
			if (on_load_game.is_null())
				break;
			data_arr.resize(ev->data.load.state_len);
			memcpy(data_arr.ptrw(), ev->data.load.state, ev->data.load.state_len);
			on_load_game.call(data_arr);
			break;
		default:
			break;
		}
	}
}

int GekkoNet::add_actor(int player_type, godot::String address)
{
	if (_session == nullptr)
		return -1;

	// cast to type.
	auto type = static_cast<GekkoPlayerType>(player_type);

	// no string? well then lets assume its a local player.
	if (address.is_empty())
		return gekko_add_actor(_session, type, nullptr);

	// else its a remote player
	auto addr = address.utf8();
	auto remote = GekkoNetAddress{(void *)addr.get_data(), (unsigned int)addr.length()};

	return gekko_add_actor(_session, type, &remote);
}

void GekkoNet::set_local_delay(int local_player, unsigned char delay)
{
	if (_session == nullptr)
		return;
	gekko_set_local_delay(_session, local_player, delay);
}

float GekkoNet::frames_ahead()
{
	if (_session == nullptr)
		return 0.f;
	return gekko_frames_ahead(_session);
}

void GekkoNet::cb_advance_game(godot::Callable callable)
{
	on_advance_game = callable;
}

void GekkoNet::cb_load_game(godot::Callable callable)
{
	on_load_game = callable;
}

void GekkoNet::cb_save_game(godot::Callable callable)
{
	on_save_game = callable;
}

void GekkoNet::handle_save_event(GekkoGameEvent::EventData::Save *event)
{
	// Create an array to store the return values
	if (on_save_game.is_null())
		return;

	Variant result = on_save_game.call(event->frame);
	if (result.get_type() == Variant::DICTIONARY)
	{
		godot::Dictionary save_info = result;

		if (save_info.has("checksum") && save_info["checksum"].get_type() == Variant::INT)
			*event->checksum = (int)save_info["checksum"];

		if (save_info.has("state_len") && save_info["state_len"].get_type() == Variant::INT)
			*event->state_len = (int)save_info["state_len"];
		else
			ERR_PRINT("No state_len supplied into savestates");

		if (save_info.has("state") && save_info["state"].get_type() == Variant::PACKED_BYTE_ARRAY)
		{
			godot::PackedByteArray state = save_info["state"];
			memcpy(event->state, state.ptr(), state.size());
		}
		else
			ERR_PRINT("No state supplied into savestates");
	}
}

void GekkoNet::add_local_input(int local_player, godot::PackedByteArray input)
{
	if (_session == nullptr || local_player == -1 || input.is_empty())
		return;
	gekko_add_local_input(_session, local_player, (void *)input.ptr());
}
