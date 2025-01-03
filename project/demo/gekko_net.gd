extends Node

var config: GekkoNetConfig
var index: int
var local_player_id: int

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	index = 0
	local_player_id = -1;
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
	if toggled_on:
		var local_port = $"../UI/LocalPortInput".value
		var local_player = $"../UI/LocalPlayerInput".value
		var remote_addr =$"../UI/RemoteAddressInput".text
		
		$"../UI/SessionButton".text = "Stop Session"
		GekkoNet.start_session(config, local_port)
		
		if local_player == 0:
			local_player_id = GekkoNet.add_actor(GekkoNet.LocalPlayer, "")
			GekkoNet.add_actor(GekkoNet.RemotePlayer, remote_addr)
		else:
			GekkoNet.add_actor(GekkoNet.RemotePlayer, remote_addr)
			local_player_id = GekkoNet.add_actor(GekkoNet.LocalPlayer, "")
			
		GekkoNet.set_local_delay(local_player_id, 2)
	else:
		$"../UI/SessionButton".text = "Start Session"
		GekkoNet.stop_session()
