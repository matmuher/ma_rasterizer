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

Dict<Attribute, float> compute_slopes(
                                        int indep_range,
                                        Dict<Attribute, FloatRange> dep
                                    )
{
    Dict<Attribute, float> slopes;

    for (const auto& [attribute, attr_range] : dep)
    {
        // non zero, as we checked for degenerate case
        slopes[attribute] = (dep[attribute].b - dep[attribute].a) / (indep_range-1);
    }

    return slopes;
}

Dict<Attribute, FloatRange> create_range_dict(  const Dict<Attribute, float>& lhs,
                                                const Dict<Attribute, float>& rhs)
{
    Dict<Attribute, FloatRange> ret;

    for (const auto& [attribute, lhs_val] : lhs)
    {
        assert ((rhs.find(attribute) != rhs.end()) && "Attribute dicts of vertices dont match");

        float rhs_val = rhs.at(attribute);
        ret[attribute] = FloatRange{lhs_val, rhs_val};
    }

    return ret;
}


Dict<Attribute, AttributeValues> interpolate_attributes(
                                                        int indep_a,
                                                        int indep_b,
                                                        Dict<Attribute, float> dep_a,
                                                        Dict<Attribute, float> dep_b
                                                        )
{
    return interpolate_attributes(IntRange{indep_a, indep_b}, create_range_dict(dep_a, dep_b));
}

Dict<Attribute, AttributeValues> interpolate_attributes(
                                                        IntRange indep,
                                                        Dict<Attribute, FloatRange> dep
                                                        )
{
    assert(!dep.empty() && "Dependents are not provided\n");

    if (indep.a == indep.b)
    {
        info() << "Independent range is degenerate\n";
        return {};
    }
    int indep_range = abs(indep.a - indep.b) + 1;

    Dict<Attribute, float> slopes = compute_slopes(indep_range, dep);

    Dict<Attribute, AttributeValues> ret;

    for (int indep_walker = 0; indep_walker < indep_range; ++indep_walker)
    {
        for (const auto& [attribute, attr_range] : dep)
        {
            ret[attribute].push_back(dep[attribute].a + slopes[attribute] * indep_walker);
        }
    }

    return ret;
}