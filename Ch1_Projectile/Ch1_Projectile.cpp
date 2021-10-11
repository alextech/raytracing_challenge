#include <iostream>
#include "simulator.h"

int main()
{
	const rt_math::tuple startingPoint = rt_math::point(0, 1, 0);
	const rt_math::tuple startingVelocity = normalize(rt_math::vector(1, 1, 0));

    Projectile *projectile = new Projectile(
        startingPoint,
        startingVelocity
    );

    Environment* environment = new Environment(
        rt_math::vector(0.0f, -0.1f, 0.0f),
        rt_math::vector(-0.01f, 0.0f, 0.0f)
    );

    float y_position = projectile->position.y;
    while(y_position >= 0.0f)
    {
        std::cout
    		<< "x: " << projectile->position.x
    		<< " y: " << projectile->position.y << std::endl;

        projectile = tick(environment, projectile);
        y_position = projectile->position.y;
    }
}
