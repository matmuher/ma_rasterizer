#pragma once

#include <string>
#include <array>
#include <SFML/Graphics.hpp>
#include <Model.hpp>
#include <Homogeneous.hpp>

class MaRasterizer
{
private:

// [camera settings]

    const int m_Width;
    const int m_Height;

    const float m_ViewPortDistance;
    const float m_ViewPortWidth;
    const float m_ViewPortHeight;

protected:

    Mat4f camera_transform;
    bool is_camera_need_update{false};

    Mat3x4f project_transform; 

    float rotate_angle{};
    sf::Vector3f translation_vec{};

private:

// [implementation detailes]

    mutable sf::RenderWindow window;

    sf::Image image;

    const std::string file_name = "querida_triangulo.png"; 

public:

// [CTOR]

    MaRasterizer(   int Width = 1000,
                    int Height = 1000,
                    float ViewPortDistance = 1.,
                    float ViewPortWidth = 1.,
                    float ViewPortHeight = 1., 
                    bool window_mode = false);
    
// [DRAWING]

    inline bool is_in_borders(int x, int y) const;

    void setPixel(int x, int y, const sf::Color& color);

    std::vector<float> interpolate(int indep_st, int indep_end,
                                   float dep_st, float dep_end) const;

    void draw_line(sf::Vector2i P0, sf::Vector2i P1, sf::Color color);
    
    void draw_triangle(sf::Vector2i P0, sf::Vector2i P1, sf::Vector2i P2, sf::Color color);
    
    void fill_triangle(sf::Vector2i P0, sf::Vector2i P1, sf::Vector2i P2, sf::Color color);

    void fill_triangle( sf::Vector2i P0, float h0,
                        sf::Vector2i P1, float h1,
                        sf::Vector2i P2, float h2,
                        sf::Color color);

    void draw_model(const Model& model);
    void draw_instance(const Instance& instance);

// [CONVERTION]

sf::Vector2i CanvasToPixel(const sf::Vector2i& cnvs_pnt) const;
sf::Vector2i ViewPortToCanvas(const sf::Vector2f& view_port_pnt) const;
sf::Vector2i ViewPortToPixel(const sf::Vector2f& view_port_pnt) const;

// [PROJECT ON VIEW PORT]

inline float project_component(float component, float z) const;
sf::Vector2f ProjectOnViewPort(const sf::Vector3f& pnt) const;
sf::Vector2i ProjectOnPixel(const sf::Vector3f& pnt) const;

// [CAMERA TRANFORMATION]

void set_camera_rotation(float angle);

void set_camera_translation(sf::Vector3f vec);

void update_camera_transform();

void update_project_transform();

// [SCENE MANAGING]

    void clear_scene();

    virtual void update_scene() = 0;

    void render_scene();

    void save_scene() const;
};

// [USEFUL]

inline float clamp(float num)
{
    if (num < 0)
        return 0;

    if (num > 1)
        return 1;

    return num;
}

inline sf::Color shade(const sf::Color& clr, float h);

void sort_by_y(sf::Vector2i& P0, sf::Vector2i& P1, sf::Vector2i& P2);

void sort_by_y( sf::Vector2i& P0, float& h0,
                sf::Vector2i& P1, float& h1,
                sf::Vector2i& P2, float& h2);

sf::Vector3f vec_move(sf::Vector3f src, const sf::Vector3f& move_vector);

sf::Vector3f vec_rotate_z(sf::Vector3f vec, float rotate_angle);

sf::Vector3f vec_transform(sf::Vector3f vec, float rotate_angle, const sf::Vector3f& move_vector);