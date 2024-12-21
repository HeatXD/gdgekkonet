#pragma once

#include <godot_cpp/classes/node.hpp>

#define GEKKONET_STATIC
#include <gekkonet.h>

using namespace godot;

class GekkoNet : public Node
{
	GDCLASS(GekkoNet, Node);

protected:
	static void _bind_methods();

public:
	GekkoNet();
	~GekkoNet();

	void _ready() override;
	void _process(double delta) override;


// GekkoNet Private Functions
public:
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

	void set_spectator_delay(unsigned char delay);
	unsigned short get_spectator_delay();

// GekkoNet Private Members
private:
	GekkoSession* _session = nullptr;
	GekkoConfig _config;
};
