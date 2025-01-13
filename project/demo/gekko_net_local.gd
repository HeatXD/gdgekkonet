extends Node

var input: PackedByteArray 
var config: GekkoNetConfig

var P1: int
var P2: int

class Gamestate:
	var pos: PackedVector2Array
	
	func _init():
		pos = PackedVector2Array([Vector2.ZERO, Vector2.ZERO])

var GS: Gamestate

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	GekkoNet.connect("on_advance_game", Callable(self, "_on_advance"))
	
	GS = Gamestate.new()
	
	config = GekkoNetConfig.new()
	config.num_players = 2
	config.input_size = 1
	config.max_spectators = 0
	config.input_prediction_window = 0
	
	input = PackedByteArray([0,0])
	
	GekkoNet.start_session(config, 0)
	
	P1 = GekkoNet.add_actor(GekkoNet.LocalPlayer, "")
	P2 = GekkoNet.add_actor(GekkoNet.LocalPlayer, "")
	
	GekkoNet.set_local_delay(P1, 1)
	
func _physics_process(_delta: float) -> void:
	fetch_local_inputs()
	GekkoNet.add_local_input(P1, input.slice(0, 1))
	GekkoNet.add_local_input(P2, input.slice(1, 2))
	GekkoNet.update_session_events()
	GekkoNet.update_game_events()
	update_positions()
	
func fetch_local_inputs():
	input[0] = 0
	input[1] = 0
	
	if Input.is_action_pressed("ui_up"): # W key
		input[0] = set_bit(input[0], 0)  
	if Input.is_action_pressed("ui_left"): # A key
		input[0] = set_bit(input[0], 1)  
	if Input.is_action_pressed("ui_down"): # S key
		input[0] = set_bit(input[0], 2)  
	if Input.is_action_pressed("ui_right"): # D key
		input[0] = set_bit(input[0], 3)  
		
	if Input.is_action_pressed("up"):
		input[1] = set_bit(input[1], 0)  
	if Input.is_action_pressed("left"):
		input[1] = set_bit(input[1], 1)  
	if Input.is_action_pressed("down"):
		input[1] = set_bit(input[1], 2)  
	if Input.is_action_pressed("right"):
		input[1] = set_bit(input[1], 3) 
		
func update_positions():
	$"Players/0".position = GS.pos[0];
	$"Players/1".position = GS.pos[1];

func set_bit(value: int, bit_position: int) -> int:
	var mask = 1 << bit_position
	return value | mask
	
func check_bit(value: int, bit_position: int) -> bool:
	var mask = 1 << bit_position
	return (value & mask) != 0

func _on_advance(inputs: PackedByteArray):
	for i in range(GS.pos.size()):
		if check_bit(inputs[i], 0):
			GS.pos[i].y -= 2
		if check_bit(inputs[i], 1):
			GS.pos[i].x -= 2
		if check_bit(inputs[i], 2):
			GS.pos[i].y += 2
		if check_bit(inputs[i], 3):
			GS.pos[i].x += 2
