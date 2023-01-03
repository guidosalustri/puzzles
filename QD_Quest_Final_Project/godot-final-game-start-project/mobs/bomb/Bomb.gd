extends Mob

onready var _shock_area := $ShockArea
onready var _shock_area_shape := $ShockArea/CollisionShape2D

func _ready() -> void:
	_animation_player.connect("animation_finished", self,"_on_AnimationPlayer_animation_finished")
	#_shock_area_shape.radius=0
	_shock_area.connect("body_entered", self,"_on_ShockArea_body_entered")
	_shock_area.connect("body_exited", self, "_on_ShockArea_body_exited")
func _physics_process(delta: float) -> void:
	if not _target:
		return
	if _target_within_range:
		_animation_player.play("will_explode")


func _on_AnimationPlayer_animation_finished(anim_name: String) -> void:
	if anim_name == "will_explode":
		_disable()
		_die_sound.play()
		_animation_player.play("explode")
	elif anim_name == "explode":
		queue_free()

func _on_ShockArea_body_entered(body:Robot)->void:
	if _animation_player.current_animation=="explode":
		body.take_damage(4)

func _on_AttackArea_body_entered(body: Robot) -> void:
	_target_within_range = true
	body.speed=300

func _on_AttackArea_body_exited(_body: Robot) -> void:
	_target_within_range = false
	_body.speed=650
	
	
	



