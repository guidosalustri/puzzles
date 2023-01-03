extends Bullet

onready var _particles:= $IceSplashParticles2D
onready var _sprite:=$Sprite

func _ready() -> void:
	_audio.connect("finished", self, "queue_free")

func _physics_process(delta: float)-> void:
	speed+=300*delta

func _destroy():
	_disable()
	_particles.emitting=true
	_audio.play()
	_sprite.hide()
	#queue_free()
	
