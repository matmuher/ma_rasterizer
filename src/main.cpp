#include <vector>
#include <iostream>

#include<Eigen/Geometry>

#include <MaRasterizer.hpp>
#include <Debug.hpp>
#include <Interpolation.hpp>

class TestRasterizer : public MaRasterizer
{
public:

        TestRasterizer(
                    int Width = 1000,
                    int Height = 1000,
                    float ViewPortDistance = 1.,
                    float ViewPortWidth = 1.,
                    float ViewPortHeight = 1., 
                    RenderMode mode = RenderMode::Picture)
        : MaRasterizer(
                        Width,
                        Height,
                        ViewPortDistance,
                        ViewPortWidth,
                        ViewPortHeight,
                        mode
                        ) {}

    virtual void update_scene()
    {
        static float t = 0;

        Instance cube1{updater, cube, 1, 0, {1, 0, 15}};
        Instance cube2{updater, cube, 1, t, {3, 0, -15}};
       
        updater.update_all();

        draw_instance(cube1);
        draw_instance(cube2);

        t += 0.5;
    }
};

int main(int argc, const char* argv[])
{
    RenderMode mode = RenderMode::Picture;

    if (argc > 1)
    {
        if (strcmp(argv[1], "-w") == 0)
        {
            mode = RenderMode::Window;
        }
        else if (strcmp(argv[1], "-p") == 0)
        {
            mode = RenderMode::Picture;
        }
    }
    
    // TestRasterizer test_rasterizer(1000, 1000, 1, 1, 1, mode);
    // test_rasterizer.render_scene();

    std::vector<attribute_values> ret = 
                            interpolate_attributes( {0, 3}, 
                                                    {
                                                        {0., 3.}, 
                                                        {1., 2.},
                                                        {-1., -2.}
                                                    }
                                                    );

    for (const auto& attribute_values : ret)
    {
        auto& outs = info();
        for (float elem : attribute_values)
        {
            outs << elem << ' ';
        }
        outs << '\n';
    }

    return 0;
}