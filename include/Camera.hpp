#pragma once

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

// [update]

    void update() override;

    void update_camera_transform();

    void update_project_transform();
};
