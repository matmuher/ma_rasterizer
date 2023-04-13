#include <MaRasterizer.hpp>
#include <Debug.hpp>
#include <cassert>


#define LOG_CALL info() << __PRETTY_FUNCTION__ << '\n';


inline sf::Color shade(const sf::Color& clr, float h)
{
    h = clamp(h);

    auto tmp = sf::Color{   
                        sf::Uint8(clr.r * h),
                        sf::Uint8(clr.g * h),
                        sf::Uint8(clr.b * h),
                        sf::Uint8(clr.a)
                    };

    std::cout << h << '\n';
    std::cout << clr << '\n';
    std::cout << tmp << '\n';
    return tmp;
}

/*
    Fill triangle taking into account how
    vertexes are shaded.

    Scheme:
        1. Interpolate shading on edges
        2. Interpolate shading between edges
        3. Implement shading to concrete pixel
*/

/*
    if h_i is out of [0;1] range,
    it will be clamped to fit this range
*/
void MaRasterizer::fill_triangle( sf::Vector2i P0, float h0,
                        sf::Vector2i P1, float h1,
                        sf::Vector2i P2, float h2,
                        sf::Color color)
{
    sort_by_y(P0, h0, P1, h1, P2, h2);

    info() << "Fill triangle: " << P0 << ' ' << P1 << ' ' << P2 << '\n';

    auto h01 = interpolate(P0.y, P1.y, h0, h1);
    auto x01 = interpolate(P0.y, P1.y, P0.x, P1.x);

    // P1 appears in both x01, x12. Leave ony one
    if (!x01.empty())
    {
        x01.pop_back();
    }
    if (!h01.empty())
    {
        h01.pop_back();
    }
    
    auto h12 = interpolate(P1.y, P2.y, h1, h2);
    auto x12 = interpolate(P1.y, P2.y, P1.x, P2.x);
    
    x01.insert(x01.end(), x12.begin(), x12.end());
    std::vector<float>& x012 = x01;

    h01.insert(h01.end(), h12.begin(), h12.end());
    std::vector<float>& h012 = h01;

    auto h02 = interpolate(P0.y, P2.y, h0, h2);
    auto x02 = interpolate(P0.y, P2.y, P0.x, P2.x);

    std::vector<float>* x_left_ptr = &x012;
    std::vector<float>* x_right_ptr = &x02;

    std::vector<float>* h_left_ptr = &h012;
    std::vector<float>* h_right_ptr = &h02;

    // head_vector(x012);
    // head_vector(x02);

    if (x012[P1.y-P0.y] > x02[P1.y-P0.y])
    {
        x_left_ptr = &x02;
        x_right_ptr = &x012;

        h_left_ptr = &h02;
        h_right_ptr = &h012;
    }

    std::vector<float>& x_left = *x_left_ptr;
    std::vector<float>& x_right = *x_right_ptr;

    std::vector<float>& h_left = *h_left_ptr;
    std::vector<float>& h_right = *h_right_ptr; 

    for (int y_walker = P0.y; y_walker < P2.y; ++y_walker)
    {
        info() << "meow\n";
        int y_shift = y_walker - P0.y;

        int x_l = x_left[y_shift];
        int x_r = x_right[y_shift];

        std::vector<float> h_horizontal = interpolate(x_l, x_r,
                                                    h_left[y_shift], h_right[y_shift]);

        head_vector(h_horizontal);

        for (int x = x_l; x < x_r; ++x)
            setPixel(x, y_walker, shade(color, h_horizontal[x - x_l]));
    }
}

void delete_last_element(Dict<Attribute, AttributeValues>& attrs)
{
    LOG_CALL;

    for (auto& [attribute, values] : attrs)
    {
        if (!attrs[attribute].empty())
        {
            attrs[attribute].pop_back();
        }
    }
}

void merge_attribute_values
                            (
                                Dict<Attribute, AttributeValues>& lhs,
                                const Dict<Attribute, AttributeValues>& rhs
                            )
{
    LOG_CALL;

    for (auto& [attribute, lhs_values] : lhs)
    {
        assert ((rhs.find(attribute) != rhs.end()) && "Attribute dicts of vertices dont match");

        const AttributeValues& rhs_values = rhs.at(attribute);

        lhs_values.insert(lhs_values.end(), rhs_values.cbegin(), rhs_values.cend());
    }
}

void determine_side(Dict<Attribute, AttributeValues>*& left_ptr,
                    Dict<Attribute, AttributeValues>*& right_ptr,
                    Dict<Attribute, AttributeValues>& attr012,
                    Dict<Attribute, AttributeValues>& attr02,
                    int middle_index)
{
    assert(middle_index > 0 && "Vertices shouldnt be in the same place");

    if (attr012["x"][middle_index-1] < attr02["x"][middle_index-1])
    {
        left_ptr = &attr012; 
        right_ptr = &attr02;
    }
    else
    {
        left_ptr = &attr02;
        right_ptr = &attr012;
    }
}

Dict<Attribute, float> get_point_attributes (   int idep_shift,
                                                const Dict<Attribute, AttributeValues>& attributes)
{
    Dict<Attribute, float> ret;

    for (auto& [attribute, values] : attributes)
    {
        ret[attribute] = values[idep_shift];
    }

    return ret;
}

 void MaRasterizer::rasterize_triangle(   ExtendedVertex P0_ext,
                            ExtendedVertex P1_ext,
                            ExtendedVertex P2_ext,
                            sf::Color color)
{
    sort_by_y(P0_ext, P1_ext, P2_ext);

    rasterize_triangle( P0_ext.vec, P0_ext.attrs,
                        P1_ext.vec, P1_ext.attrs,
                        P2_ext.vec, P2_ext.attrs,
                        color);
}

void MaRasterizer::rasterize_triangle(
                            sf::Vector2i P0, Dict<Attribute, float> P0_attr,
                            sf::Vector2i P1, Dict<Attribute, float> P1_attr,
                            sf::Vector2i P2, Dict<Attribute, float> P2_attr,
                            sf::Color color
                            )
{
    LOG_CALL;

    P0_attr["x"] = P0.x;
    P1_attr["x"] = P1.x;
    P2_attr["x"] = P2.x;

    Dict<Attribute, AttributeValues> attr01 = interpolate_attributes    (
                                                                        P0.y, P1.y,
                                                                        P0_attr, P1_attr
                                                                        );

    delete_last_element(attr01); 

    auto attr12 = interpolate_attributes    (
                                            P1.y, P2.y,
                                            P1_attr, P2_attr
                                            );

    merge_attribute_values(attr01, attr12);
    Dict<Attribute, AttributeValues>& attr012 = attr01;
    
    auto attr02 = interpolate_attributes    (
                                            P0.y, P2.y,
                                            P0_attr, P2_attr
                                            );

    Dict<Attribute, AttributeValues>* left_ptr{};
    Dict<Attribute, AttributeValues>* right_ptr{};

    determine_side( left_ptr, right_ptr,
                    attr012, attr02,
                    (P2.y - P0.y) / 2);

    Dict<Attribute, AttributeValues>& attr_left = *left_ptr;
    Dict<Attribute, AttributeValues>& attr_right = *right_ptr;

    for (int y_walker = P0.y; y_walker < P2.y; ++y_walker)
    {
        info() << "YWalker: " << y_walker << '\n';

        int y_shift = y_walker - P0.y;

        int x_l = attr_left["x"][y_shift];
        int x_r = attr_right["x"][y_shift];

        Dict<Attribute, AttributeValues> horizontal_attr =
                                interpolate_attributes  (
                                                    x_l,
                                                    x_r,
                                                    get_point_attributes(y_shift, attr_left),
                                                    get_point_attributes(y_shift, attr_right)
                                                        );

        for (int x = x_l; x < x_r; ++x)
        {
     
            if (z_buffer.getVal(x, y_walker) < horizontal_attr["z"][x - x_l])
            {
                z_buffer.setVal(x, y_walker, horizontal_attr["z"][x - x_l]);

                setPixel(x, y_walker, shade(color, horizontal_attr["h"][x - x_l]));
            }
        }
    }
}