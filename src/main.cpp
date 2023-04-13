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
        // static float t = 0;

        // Instance cube1{updater, cube, 1, 0, {1, 0, 15}};
        // Instance cube2{updater, cube, 1, t, {3, 0, -15}};
       
        // updater.update_all();

        // draw_instance(cube1);
        // draw_instance(cube2);

        info() << "WTF\n";
        rasterize_triangle( {{0, 0}, {{"h", 0.2}, {"z", 20}}}, 
                            {{0, 200}, {{"h", 1.0}, {"z", 20}}},
                            {{200, 0}, {{"h", 0.0}, {"z", 20}}},
                            sf::Color::Red);
        
        
        rasterize_triangle( {{0, 0}, {{"h", 0.2}, {"z", 10}}}, 
                            {{200, 0}, {{"h", 1.0}, {"z", 10}}},
                            {{200, 200}, {{"h", 0.0}, {"z", 10}}},
                            sf::Color::Blue);
        // t += 0.5;
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
    
    TestRasterizer test_rasterizer(200, 200, 1, 1, 1, mode);
    test_rasterizer.render_scene();

    // Dict<Attribute, AttributeValues> ret = 
    //                         interpolate_attributes( {0, 3},
    //                                                 {
    //                                                 {"a", {0., 3.}}, 
    //                                                 {"b", {1., 2.}},
    //                                                 {"z", {-1., -2.}}
    //                                                 }
    //                                                 );

    return 0;
}