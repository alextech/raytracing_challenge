#pragma once
#include "../Math/Math.h"

class Projectile
{
	public:
		rt_math::tuple position;
		rt_math::tuple velocity;

		Projectile(rt_math::tuple const position, rt_math::tuple const velocity)
			: position(position), velocity(velocity) {}
};

class Environment
{
	public:
		const rt_math::tuple gravity;
		const rt_math::tuple wind;

		Environment(rt_math::tuple gravity, rt_math::tuple wind)
			: gravity(gravity), wind(wind) {}
};

void tick(const Environment* environment, Projectile* projectile);
