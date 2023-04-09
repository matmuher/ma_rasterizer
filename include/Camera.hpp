#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <Homogeneous.hpp>
#include <Updater.hpp>

class Camera : public Updatable
{
// [MEMBERS]

// [project transform]

    Mat3x4f project_transform; 

    // pixel array props

        const int m_Width;
        const int m_Height;

    // view port props

        const float m_ViewPortDistance;
        const float m_ViewPortWidth;
        const float m_ViewPortHeight;

    // field of view planes

        std::vector<Plane> fov_planes;

// [camera transform]

    Mat4f camera_transform;

    float m_angle{};
    sf::Vector3f m_position{};

// [update flags]

    bool is_camera_transform_outdated{true};
    bool is_project_transform_outdated{true};

public:

// [FUNCTIONS]

// [ctors]

    Camera
        (
            Updater& updater,
            int Width = 1000,
            int Height = 1000,
            float ViewPortDistance = 1,
            float ViewPortWidth = 1,
            float ViewPortHeight = 1,
            float angle = 0,
            sf::Vector3f position = sf::Vector3f{0, 0, 0} 
        );

    // w - ViewPortWidth
    // h - ViewPortHeight
    // d - ViewPortDistance
    std::vector<Plane> init_fov_planes(float w, float h, float d)
    {
        std::vector<Plane> fov_planes;
        fov_planes.reserve(5);

        fov_planes.emplace_back(sf::Vector3f{0, 0, -d}, d);
        fov_planes.emplace_back(sf::Vector3f{ d, 0, -w/2}, 0); // left
        fov_planes.emplace_back(sf::Vector3f{-d, 0, -w/2}, 0); // right
        fov_planes.emplace_back(sf::Vector3f{0, -d, -h/2}, 0); // top
        fov_planes.emplace_back(sf::Vector3f{0,  d, -h/2}, 0); // bottom

        return fov_planes;
    }

// [setters]

    void set_rotation(float angle);

    void set_position(const sf::Vector3f& vec);

// [getters]

    const Mat4f& get_camera_transform() const; 

    const Mat3x4f& get_project_transform() const;

    int get_width() const;

    int get_height() const;

    float get_vp_width() const;
    float get_vp_height() const;
    float get_vp_dist() const;

    const std::vector<Plane>& get_fov_planes() const;

// [update]

    void update() override;

    void update_camera_transform();

    void update_project_transform();
};
