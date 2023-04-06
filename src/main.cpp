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
        translation_vec += {0, 0, 5};
        rotate_angle += 20;

        Instance cube1{cube, {-4, 0, -15}, 0, 1.5};
        Instance cube2{cube, {4, 0, -15}, -90, 1};

        draw_instance(cube1);
        draw_instance(cube2);
    }
};

using Matrix = Eigen::MatrixXd;

int main()
{
    // Matrix mat(3, 3);
    // mat(0, 1) = 5;
    // mat(1, 0) = -5;
    // std::cout << mat;

    TestRasterizer test_rasterizer(500, 500);

    test_rasterizer.update_scene();
    test_rasterizer.save_scene();

    return 0;
}