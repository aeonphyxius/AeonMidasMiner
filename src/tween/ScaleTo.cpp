#include <ScaleTo.h>


using namespace tweens;

ScaleTo::ScaleTo(const glm::vec3 par_origin, const glm::vec3 par_target, float par_seconds, bool par_loop,  EaseType curve) :
	origin(par_origin),
	target(par_target),
	to_target(false),
	curve(curve),
	time(par_seconds),
	loop(par_loop)
{	
	
}

void ScaleTo::onUpdate()
{
	if (timer.started())
	{
		if (!timer.finished())
		{	
			
			scale = glm::vec3( (to_target ? target : origin).x * timer.getDelta() + (to_target ? origin : target).x * (1.0f - timer.getDelta()),
							   (to_target ? target : origin).y * timer.getDelta() + (to_target ? origin : target).y * (1.0f - timer.getDelta()),
								 1);
			parent->setScale(scale);						
		}
		else
		{
			if (loop){
				parent->setScale(to_target ? target : origin);
				to_target = !to_target;
				timer.start(time);
			}
			else{
				destroy();
			}
		}
	}
	else
	{
		to_target = !to_target;
		timer.start(time);
	}
}

