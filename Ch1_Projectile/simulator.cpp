#include "simulator.h"


Projectile *tick(const Environment *environment, const Projectile* projectile)
{
	const rt_math::tuple position = projectile->position + projectile->velocity;
	const rt_math::tuple velocity = projectile->velocity + environment->gravity + environment->wind;

	return new Projectile(position, velocity);
}