#include <Interpolation.hpp>


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
