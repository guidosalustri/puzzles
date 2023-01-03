class_name SpellIcePunch
extends Spell


func _physics_process(delta: float) -> void:
	if Input.is_action_just_pressed("shoot") and _cooldown_timer.is_stopped():
		shoot()


func shoot() -> void:
	_cooldown_timer.start()
	var r:=-PI/8
	for i in range(3):
		var bullet: Bullet = bullet_scene.instance()
		get_tree().root.add_child(bullet)
		bullet.global_transform = global_transform
		bullet.max_range = max_range
		bullet.speed = max_bullet_speed
		#bullet.randomize_rotation(deg2rad(random_angle_degrees))
		bullet.rotate(r)
		r+=PI/8
		_audio.play() 
