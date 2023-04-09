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
        Instance cube1{updater, cube, 1, 0, {0, 0, 0}};
        //Instance cube2{updater, cube, 2, 0, {4, 0, -15}};
       
        updater.update_all();

        draw_instance(cube1);
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