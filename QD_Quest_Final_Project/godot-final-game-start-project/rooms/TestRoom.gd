extends YSort


onready var spawner := $Spawner

func _ready() -> void:
	randomize()
	spawner.spawn()
