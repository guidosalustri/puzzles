class_name Spawner
extends Sprite

export(Array, PackedScene) var list := []

#onready var spawner := $Spawner

func _ready() -> void:
	texture = null

func spawn() -> void:
	if not list:
		return
	# Get a random scene resource from the list array.
	var random_scene_index := randi() % list.size()
	var scene: PackedScene = list[random_scene_index]
# The array might have holes. We need to make sure we got an item.
	if not scene:
		return
	var node: Node2D = scene.instance()
	get_parent().add_child(node)
	node.global_position = global_position

