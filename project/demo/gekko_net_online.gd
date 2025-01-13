extends Node

var input: PackedByteArray 
var config: GekkoNetConfig

var local_player_id : int

class Gamestate:
	var position: PackedVector2Array
	
	func _init():
		position = PackedVector2Array([Vector2(600,300), Vector2(600,300)])

var GS: Gamestate

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	GekkoNet.cb_advance_game(Callable(self, "_on_advance"))
	GekkoNet.cb_load_game(Callable(self, "_on_load"))
	GekkoNet.cb_save_game(Callable(self, "_on_save"))
	
	input = PackedByteArray([0,0])
	GS = Gamestate.new()
	
	# i know this size will be fixes so its fine.
	var state_size = var_to_bytes(GS).size()
	
	print(state_size)
	
	local_player_id = -1;
	config = GekkoNetConfig.new()
	config.num_players = 2
	config.input_size = 1
	config.state_size = state_size
	config.max_spectators = 0
	config.input_prediction_window = 10
	config.desync_detection = true
	config.limited_saving = false

func _physics_process(_delta: float) -> void:
	handle_rift()
	fetch_local_inputs()
	GekkoNet.add_local_input(local_player_id, input)
	GekkoNet.update_session_events()
	GekkoNet.update_game_events()
	update_positions()
	
func handle_rift():
	var frames_ahead = GekkoNet.frames_ahead()
	
	if frames_ahead > 2:
		Engine.physics_ticks_per_second = 58
	elif frames_ahead < -2:
		Engine.physics_ticks_per_second = 62
	else:
		Engine.physics_ticks_per_second = 60
		
func fetch_local_inputs():
	input[0] = 0
		
	if Input.is_action_pressed("up"):
		input[0] = set_bit(input[0], 0)  
	if Input.is_action_pressed("left"):
		input[0] = set_bit(input[0], 1)  
	if Input.is_action_pressed("down"):
		input[0] = set_bit(input[0], 2)  
	if Input.is_action_pressed("right"):
		input[0] = set_bit(input[0], 3) 
		
func update_positions():
	$"Players/0".position = GS.position[0];
	$"Players/1".position = GS.position[1];
	$"../FPSLabel".text = " %.1f" % Engine.get_physics_ticks_per_second()
	
func set_bit(value: int, bit_position: int) -> int:
	var mask = 1 << bit_position
	return value | mask
	
func check_bit(value: int, bit_position: int) -> bool:
	var mask = 1 << bit_position
	return (value & mask) != 0
	
func _on_advance(inputs: PackedByteArray):
	for i in range(inputs.size()):
		if check_bit(inputs[i], 0):
			GS.position[i].y -= 2
		if check_bit(inputs[i], 1):
			GS.position[i].x -= 2
		if check_bit(inputs[i], 2):
			GS.position[i].y += 2
		if check_bit(inputs[i], 3):
			GS.position[i].x += 2
			
func _on_load(state: PackedByteArray):
	# print(state)
	GS.position = bytes_to_var(state)
	
func _on_save(frame_to_save: int):
	# print("save: " + str(frame_to_save))
	var state = var_to_bytes(GS.position)
	var return_values = {
		"checksum": 0,
		"state_len": state.size(),
		"state": state  
	}
	# print(return_values)
	return return_values

func _on_session_button_toggled(toggled_on: bool) -> void:
	if toggled_on:
		var local_port = $"../UI/LocalPortInput".value
		var local_player = $"../UI/LocalPlayerInput".value
		var remote_addr =$"../UI/RemoteAddressInput".text
		
		$"../UI/SessionButton".text = "Stop Session"
		
		GS = Gamestate.new()
		
		GekkoNet.start_session(config, local_port)
		
		if local_player == 0:
			local_player_id = GekkoNet.add_actor(GekkoNet.LocalPlayer, "")
			GekkoNet.add_actor(GekkoNet.RemotePlayer, remote_addr)
		else:
			GekkoNet.add_actor(GekkoNet.RemotePlayer, remote_addr)
			local_player_id = GekkoNet.add_actor(GekkoNet.LocalPlayer, "")
			
		GekkoNet.set_local_delay(local_player_id, 1)
	else:
		$"../UI/SessionButton".text = "Start Session"
		GekkoNet.stop_session()
