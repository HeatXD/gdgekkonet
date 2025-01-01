extends Node

var config: GekkoNetConfig
var index: int

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	index = 0
	config = GekkoNetConfig.new()
	config.num_players = 2
	config.input_size = 1
	config.state_size = 1
	config.max_spectators = 0
	config.input_prediction_window = 10
	config.desync_detection = true
	config.limited_saving = false
	
func _physics_process(delta: float) -> void:
	pass


func _on_session_button_toggled(toggled_on: bool) -> void:
	print(toggled_on)
	if toggled_on:
		$"../UI/SessionButton".text = "Stop Session"
		GekkoNet.start_session(config, $"../UI/LocalPortInput".value)
		
	else:
		$"../UI/SessionButton".text = "Start Session"
		GekkoNet.stop_session()
