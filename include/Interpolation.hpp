#pragma once

#include <vector>
#include <map>
#include <string>

struct FloatRange
{
    float a, b;
};

struct IntRange
{
    int a, b;
};

using Attribute = std::string;
using AttributeValues = std::vector<float>;

template<class KeyType, class ValType >
using Dict = std::map<KeyType, ValType>;

std::vector<float> interpolate(int indep_st, int indep_end,
                                float dep_st, float dep_end);

Dict<Attribute, AttributeValues> interpolate_attributes(
                                                        IntRange indep,
                                                        Dict<Attribute, FloatRange> dep
                                                        );


Dict<Attribute, AttributeValues> interpolate_attributes(
                                                        int indep_a,
                                                        int indep_b,
                                                        Dict<Attribute, float> dep_a,
                                                        Dict<Attribute, float> dep_b
                                                        );

Dict<Attribute, FloatRange> create_range_dict(  const Dict<Attribute, float>& lhs,
                                                const Dict<Attribute, float>& rhs);

