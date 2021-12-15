#include "simulator.h"


void tick(const Environment *environment, Projectile* projectile)
{
	const rt_math::tuple position = projectile->position + projectile->velocity;
	const rt_math::tuple velocity = projectile->velocity + environment->gravity + environment->wind;

	projectile->position = position;
	projectile->velocity = velocity;
}