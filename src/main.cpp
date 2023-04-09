#include <vector>
#include <iostream>

#include<Eigen/Geometry>

#include <MaRasterizer.hpp>
#include <Debug.hpp>

class TestRasterizer : public MaRasterizer
{
public:

        TestRasterizer(
                    int Width = 1000,
                    int Height = 1000,
                    float ViewPortDistance = 1.,
                    float ViewPortWidth = 1.,
                    float ViewPortHeight = 1., 
                    bool window_mode = false)
        : MaRasterizer(
                        Width,
                        Height,
                        ViewPortDistance,
                        ViewPortWidth,
                        ViewPortHeight,
                        window_mode
                        ) {}

    virtual void update_scene()
    {
        Plane plane1{{0, 0, -1}, 1};
        info() << "dist" << compute_dist({0, 0, -3}, plane1) << '\n';
        exit(1);

        static float t = 0;

        Instance cube1{updater, cube, 1, 0, {-4, 0, -15}};
        Instance cube2{updater, cube, 2, 0, {4, 0, -15}};
        exit(1);

        cube1.set_rotation(20*t);

        camera.set_rotation(t);
        camera.set_position({0, 0, t});

        t += 0.1;
        updater.update_all();

        draw_instance(cube1);
        draw_instance(cube2);
    }
};

int main()
{
    // TODO add enum for render mode
    TestRasterizer test_rasterizer(1000, 1000, 1, 1, 1, false);

    test_rasterizer.update_scene();
    test_rasterizer.save_scene();
    // test_rasterizer.render_scene();

    return 0;
}