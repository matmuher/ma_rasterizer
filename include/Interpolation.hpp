#pragma once

#include <vector>

struct float_range
{
    float a, b;
};

struct int_range
{
    int a, b;
};

using attribute_values = std::vector<float>;


std::vector<float> interpolate(int indep_st, int indep_end,
                                float dep_st, float dep_end);

std::vector<attribute_values> interpolate_attributes( int_range indep,
                                                      std::vector<float_range> dep);