#include "HarmonicType.h"

std::string HarmonicTypeToString(HarmonicType type)
{
	switch (type)
	{
	case HarmonicType::Cos:
		return "cos";
	default:
		return "sin";
	}
}