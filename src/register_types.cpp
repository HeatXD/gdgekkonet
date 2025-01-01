#include "register_types.h"
#include "gd_gekkonet.h"

#include <gdextension_interface.h>
#include <godot_cpp/classes/engine.hpp>

static GekkoNet *_GekkoNet;

void gd_gekkonet_initialize(ModuleInitializationLevel p_level)
{
	if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE)
	{
		ClassDB::register_class<GekkoNet>();
		ClassDB::register_class<GekkoNetConfig>();
		_GekkoNet = memnew(GekkoNet);
		Engine::get_singleton()->register_singleton("GekkoNet", GekkoNet::get_singleton());
	}
}

void gd_gekkonet_terminate(ModuleInitializationLevel p_level)
{
	if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE)
	{
		Engine::get_singleton()->unregister_singleton("GekkoNet");
		memdelete(_GekkoNet);
	}
}

extern "C"
{
	GDExtensionBool GDE_EXPORT gd_gekkonet_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization)
	{
		godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

		init_obj.register_initializer(gd_gekkonet_initialize);
		init_obj.register_terminator(gd_gekkonet_terminate);
		init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

		return init_obj.init();
	}
}
