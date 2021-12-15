#include <iostream>
#include "simulator.h"

#include "../Renderer/Canvas.h"
#include "../Renderer/PpmWriter.h"

int main()
{

	const rt_math::tuple startingPoint = rt_math::point(0, 1, 0);
	const rt_math::tuple startingVelocity = normalize(rt_math::vector(1, 1.8f, 0)) * 11.25f;

	Projectile *projectile = new Projectile(
        startingPoint,
        startingVelocity
    );

	const Environment* environment = new Environment(
        rt_math::vector(0.0f, -0.1f, 0.0f),
        rt_math::vector(-0.01f, 0.0f, 0.0f)
    );

    constexpr int width = 900;
    constexpr int height = 500;
    Canvas* canvas = new Canvas(width, height);
    

    while(projectile->position.y >= 0.0f)
    {

#ifdef VERBOSE
      std::cout
    		<< "x: " << projectile->position.x
    		<< " y: " << projectile->position.y << std::endl;
#endif

        canvas->write_pixel(
            static_cast<unsigned int>(round(projectile->position.x)),
            height - static_cast<unsigned int>(round(projectile->position.y)),
            rt_math::color(1, 0, 0)
        );

        tick(environment, projectile);
    }

    delete environment;
    delete projectile;

    const PpmWriter* writer = new PpmWriter("projectile.ppm");
    writer->canvas_to_ppm(canvas);

    delete writer;
    delete canvas;
}
