#pragma once
#include <string>

enum class HarmonicType
{
    Sin,
    Cos
};

std::string HarmonicTypeToString(HarmonicType type);