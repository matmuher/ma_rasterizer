#include <LinearAlgebra.hpp>

const float PRESICION = 0.0001;

bool is_equal(float lhs, float rhs)
{
    return fabs(lhs - rhs) < PRESICION;    
}

bool is_less(float lhs, float rhs)
{
    return lhs < (rhs - PRESICION);    
}

Mat4f create_scale_matrix(float scale)
{
    Mat4f temp;
    
    temp << 
            scale,  0.f,    0.f,    0,
            0.f,    scale,  0.f,    0,
            0.f,    0.f,    scale,  0,
            0.f,    0.f,    0.f,    1.f
            ;

    info() << "Scale matrix:\n\n" << temp << "\n\n";

    return temp;
}

Mat4f create_translation_matrix(sf::Vector3f vec)
{
    Mat4f temp;

    temp << 
            1.f, 0.f, 0.f, vec.x,
            0.f, 1.f, 0.f, vec.y,
            0.f, 0.f, 1.f, vec.z,
            0.f, 0.f, 0.f, 1.f
            ;

    info() << "Translation matrix:\n\n" << temp << "\n\n";

    return temp;
}

Mat4f create_rotation_y_matrix(float phi)
{
    Mat4f temp;
    
    temp <<
            cosf(phi),  0, sinf(phi),   0,
                0,      1,   0,         0,
            -sinf(phi), 0, cosf(phi),   0,
                0,      0,   0,         1;

    info() << "Rotation matrix:\n\n" << temp << "\n\n";

    return temp;
}

Mat3x4f create_projection_matrix(float d, float v_w, float v_h,
                                 int C_w, int C_h)
{
    Mat3x4f temp;
    
    temp << 
            (-d) * C_w / v_w,         0,                 C_w / 2.,    0,
                0,           -(-d) * C_h / v_h,          C_h / 2.,    0,
                0,                    0,                      1,      0;

    info() << "Projection matrix:\n\n" << temp << "\n\n";

    return temp;
}

sf::Vector3f homogeneous_to_cartesian_3d(float x, float y, float z, float w)
{
    sf::Vector3f vec{x, y, z};

    if (is_equal(w, 0))
    {
        return vec;
    }
    else
    {
        return vec * (1/w);
    }
}

sf::Vector2f homogeneous_to_cartesian_2d(float x, float y, float z)
{
    sf::Vector2f vec{x, y};

    if (is_equal(z, 0))
    {
        return vec;
    }
    else
    {
        return vec * (1/z);
    }
}

float deg2rad(float deg)
{
    return deg / 180. * M_PI;
}

float square(const sf::Vector3f& vec)
{
    return (vec.x*vec.x) + (vec.y*vec.y) + (vec.z*vec.z);
}

float dot_product(const sf::Vector3f& lhs, const sf::Vector3f& rhs)
{
    float result = (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z);

    info() << lhs << " * " << rhs << " = " << result << "\n";

    return result;
}

sf::Vector3f normalize(const sf::Vector3f& vec)
{
    return vec * (1 / sqrtf(dot_product(vec, vec)));
}
