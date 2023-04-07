#include <vector>
#include <iostream>

#include<Eigen/Geometry>

#include <MaRasterizer.hpp>
#include <Debug.hpp>

class TestRasterizer : public MaRasterizer
{
public:

    TestRasterizer(int Width, int Height) : MaRasterizer(Width, Height) {}

    virtual void update_scene()
    {
        set_camera_rotation(360);
        set_camera_translation({1, 1, 1});
        update_camera_transform();
        std::cout << camera_transform << '\n';

        Instance cube1{cube, {-4, 0, -15}, 0, 1.5};
        Instance cube2{cube, {4, 0, -15}, -90, 1};

        draw_instance(cube1);
        draw_instance(cube2);
    }
};

int main()
{
    TestRasterizer test_rasterizer(500, 500);

    test_rasterizer.update_scene();
    test_rasterizer.save_scene();

    return 0;
}