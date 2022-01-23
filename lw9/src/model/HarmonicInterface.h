#pragma once
#include <vector>
#include "EditedHarmonicInterface.h"

struct Point
{
    double x;
    double y;
};

typedef std::vector<Point> CoordinatesVector;

class HarmonicInterface : public EditedHarmonicInterface
{
public:
    virtual CoordinatesVector GetCoordinates() const = 0;
    virtual std::string ToString() const = 0;

    void DoOnChange();

	virtual ~HarmonicInterface() = default;
};
