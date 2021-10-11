#pragma once
#include "../Math/Math.h"

class Projectile
{
	public:
		const rt_math::tuple position;
		const rt_math::tuple velocity;

		Projectile(rt_math::tuple position, rt_math::tuple velocity)
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

Projectile* tick(const Environment* environment, const Projectile* projectile);
