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

	godot::String hello_node();

private:
	GekkoSession* _session = nullptr;
};
