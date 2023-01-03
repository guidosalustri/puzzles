extends Mob

export (float, 0.01, 1.0) var rotation_factor := 0.1


onready var _hitbox:=$HitBox
var _target_last_pos:Vector2=Vector2.ZERO
var pos_fixed :=false
var _shoot :=false
var first:=true

func _ready() -> void:
	_hitbox.connect("body_entered",self,"_on_HitBox_body_entered") 


func _physics_process(delta: float) -> void:
	if not _target:
		return
	if _target and not pos_fixed and _target_within_range:
		point_at(_target)
		if first:
			_before_attack_timer.start()
			first=false
		_target_last_pos=_target.global_position
	if _shoot:
		follow(_target_last_pos)
		yield(get_tree().create_timer(1),"timeout")
		queue_free()


func point_at(body:Robot)->void:
	var pointing := body.global_position.angle_to_point(global_position)
	_sprite.rotation = lerp_angle(_sprite.rotation, pointing, rotation_factor)
	
	
func _on_HitBox_body_entered(body:Robot)->void:
	if _target:
		body.take_damage(6)


func _on_BeforeAttackTimer_timeout() -> void:
	pos_fixed=true
	_cooldown_timer.start()
#	if not _target:
#		return

func _on_CoolDownTimer_timeout() -> void:
	speed=1800
	_shoot=true


func _on_DetectionArea_body_exited(_body: Robot) -> void:
	_sprite_alert.visible = true


