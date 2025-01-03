#pragma once

#include <godot_cpp/classes/node.hpp>

#define GEKKONET_STATIC
#include <gekkonet.h>

using namespace godot;

class GekkoNetConfig : public RefCounted, public GekkoConfig
{
	GDCLASS(GekkoNetConfig, RefCounted);

protected:
	static void _bind_methods();

public:
	GekkoNetConfig();
	~GekkoNetConfig();

private:
	void set_num_players(unsigned char num_players);
	unsigned char get_num_players();

	void set_input_size(int input_size);
	int get_input_size();

	void set_max_spectators(unsigned char num_spectators);
	unsigned char get_max_spectators();

	void set_input_prediction_window(unsigned char window);
	unsigned char get_input_prediction_window();

	void set_state_size(int state_size);
	int get_state_size();

	void set_limited_saving(bool limited_saving);
	bool get_limited_saving();

	void set_desync_detection(bool desync_detection);
	bool get_desync_detection();

	void set_spectator_delay(unsigned char delay);
	unsigned char get_spectator_delay();
};

class GekkoNet : public Object
{
	GDCLASS(GekkoNet, Object);

	static GekkoNet* singleton;

protected:
	static void _bind_methods();

public:
	static GekkoNet* get_singleton();

	GekkoNet();
	~GekkoNet();

	void start_session(Ref<GekkoNetConfig> config, unsigned short local_port);
	void stop_session();

	int add_actor(int player_type, godot::String address);
	void set_local_delay(int local_player, unsigned char delay);
	float frames_ahead();

	bool has_session();

private:
	GekkoSession* _session = nullptr;
};