#include <iostream>
#include <numbers>
#include <array>
#include "../Math/Math.h"

#include "../Renderer/Canvas.h"
#include "../Renderer/PpmWriter.h"


int main()
{
    constexpr int width = 900;
    constexpr int height = 500;
    

    const rt_math::tuple center = rt_math::point(450, 250, 0);
    constexpr rt_math::color color = rt_math::color(1, 0, 0);
    constexpr float radius = 150.0f;

    const rt_math::tuple top = rt_math::point(0, 1, 0);
    std::array<rt_math::tuple, 12> hours{};
    const std::unique_ptr<Canvas> canvas(new Canvas(width, height));

    for(unsigned int i = 0; i < 12; ++i)
    {
        const rt_math::Matrix<4> transform = 
            rotation_z(std::numbers::pi_v<float> * 2 / 12 * static_cast<float>(i));
    
    
        hours[i] = transform * top;
    }

    canvas->write_pixel(static_cast<int>(center.x), static_cast<int>(center.y), color);

    for(unsigned int i = 0; i < 12; ++i)
    {
        canvas->write_pixel(
            static_cast<int>(hours[i].x * radius + center.x), 
            static_cast<int>(hours[i].y * radius + center.y),
            color);
    }


    const std::unique_ptr<PpmWriter> writer(new PpmWriter("clock.ppm"));
    writer->canvas_to_ppm(canvas.get());

    
}
