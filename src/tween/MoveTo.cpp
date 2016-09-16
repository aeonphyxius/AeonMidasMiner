#include <MoveTo.h>

using namespace tweens;

MoveTo::MoveTo(const glm::vec3 par_origin, const glm::vec3 par_target, float par_seconds, bool par_loop, EaseType curve) :
origin(par_origin),
target(par_target),
to_target(false),
curve(curve),
time(par_seconds),
loop(par_loop)
{

}

void MoveTo::onUpdate()
{

	if (timer.started())
	{
		if (timer.started())
		{
			if (!timer.finished())
			{
				auto new_pos = glm::vec3((to_target ? target : origin).x * timer.getDelta(curve) + (to_target ? origin : target).x * (1.0f - timer.getDelta(curve)),
					(to_target ? target : origin).y * timer.getDelta(curve) + (to_target ? origin : target).y * (1.0f - timer.getDelta(curve)),
					1);
				parent->setPosition(new_pos);
			}
			else
			{
				if (loop){
					parent->setPosition(to_target ? target : origin);
					to_target = !to_target;
					timer.start(time);
				}
				else{
					parent->setPosition(to_target ? target : origin);
					destroy();
				}
			}
		}
	}
	else
	{
		to_target = !to_target;
		timer.start(time);
	}
}

MoveToBack::MoveToBack(const glm::vec3 par_origin, const glm::vec3 par_target, float par_seconds,EaseType curve) :
origin(par_origin),
target(par_target),
to_target(false),
curve(curve),
time(par_seconds)
{

}

void MoveToBack::onUpdate()
{

	if (timer.started())
	{
		if (timer.started())
		{
			if (!timer.finished())
			{
				auto new_pos = glm::vec3((to_target ? target : origin).x * timer.getDelta(curve) + (to_target ? origin : target).x * (1.0f - timer.getDelta(curve)),
					(to_target ? target : origin).y * timer.getDelta(curve) + (to_target ? origin : target).y * (1.0f - timer.getDelta(curve)),
					1);
				parent->setPosition(new_pos);
			}
			else
			{
				if (to_target){
					parent->setPosition(target);
					to_target = !to_target;
					timer.start(time);
				}
				else{
					parent->setPosition(origin);
					destroy();
				}
			}
		}
	}
	else
	{
		to_target = !to_target;
		timer.start(time);
	}
}