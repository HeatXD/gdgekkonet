extends Label

var index:int = 0

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	text += get_child(0).hello_node();

func _process(delta: float) -> void:
	index += 1
	if index == 600:
		get_child(0).queue_free()
