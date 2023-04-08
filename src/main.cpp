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
        Instance cube1{cube, 1, 0, {-4, 0, -15}};
        Instance cube2{cube, 2, 0, {4, 0, -15}};

        cube1.update_transform();
        cube2.update_transform();

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