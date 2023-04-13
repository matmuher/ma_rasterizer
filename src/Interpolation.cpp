#include <cassert>
#include <Interpolation.hpp>
#include <Debug.hpp>

// general interpolation function:
/*
        ^ (dep)
        |
        |        ******
        |   *****
        |***
        - - - - - - - > (indep)
*/
std::vector<float>  interpolate(int indep_st, int indep_end,
                                float dep_st, float dep_end)
{
    if (indep_st == indep_end)
        return {};

    std::vector<float> dep_values;

        // let i0 = 0, i1 = 1 -> all in all 2 pixels
        // i.e. (i1 - i0 + 1)
    int range_len_indep = indep_end - indep_st;
    float range_len_dep   = dep_end - dep_st;

    dep_values.reserve(range_len_indep);

        // slope shows how much should we move in dependent-axis
        // when move one step in independent axis
    float slope = range_len_dep / range_len_indep; 
    
    float dep_walker = dep_st;
    for (int indep_walker = 0; indep_walker <= range_len_indep; ++indep_walker)
    {
        dep_walker += slope;
        dep_values.push_back(dep_walker);
    }

    return dep_values;
}

std::vector<float> compute_slopes(  int indep_range,
                                    std::vector<float_range> dep)
{
    int attributes_num = dep.size();

    std::vector<float> slopes;
    slopes.reserve(attributes_num);

    for (int attr_id = 0; attr_id < attributes_num; ++attr_id)
    {
        // non zero, as we checked for degenerate case
        slopes.emplace_back((dep[attr_id].b - dep[attr_id].a) / (indep_range-1));
    }

    return slopes;
}

std::vector<attribute_values> interpolate_attributes( int_range indep,
                                                      std::vector<float_range> dep)
{
    assert(!dep.empty() && "Dependents are not provided\n");

    if (indep.a == indep.b)
    {
        info() << "Independent range is degenerate\n";
        return {};
    }
    int indep_range = abs(indep.a - indep.b) + 1;

    std::vector<float> slopes = compute_slopes(indep_range, dep);

    int attributes_num = dep.size();
    std::vector<attribute_values> ret(  attributes_num,
                                        attribute_values(indep_range, 0));

    for (int indep_walker = 0; indep_walker < indep_range; ++indep_walker)
    {
        for (int attr_id = 0; attr_id < attributes_num; ++attr_id)
        {
            ret[attr_id][indep_walker] = dep[attr_id].a + slopes[attr_id] * indep_walker;
        }
    }

    return ret;
}