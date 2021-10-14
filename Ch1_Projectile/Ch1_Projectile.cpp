#include <iostream>
#include "simulator.h"

int main()
{

	const rt_math::tuple startingPoint = rt_math::point(0, 1, 0);
	const rt_math::tuple startingVelocity = normalize(rt_math::vector(1, 1, 0));

	const Projectile *projectile = new Projectile(
        startingPoint,
        startingVelocity
    );

	const Environment* environment = new Environment(
        rt_math::vector(0.0f, -0.1f, 0.0f),
        rt_math::vector(-0.01f, 0.0f, 0.0f)
    );

    while(projectile->position.y >= 0.0f)
    {
        std::cout
    		<< "x: " << projectile->position.x
    		<< " y: " << projectile->position.y << std::endl;

        const Projectile *oldProjectilePtr = projectile;
        projectile = tick(environment, projectile);

        delete oldProjectilePtr;
    }

    delete environment;
    delete projectile;
}
