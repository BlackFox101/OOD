#pragma once
#include <vector>
#include "EditedHarmonicInterface.h"

class HarmonicInterface : public EditedHarmonicInterface
{
public:
    struct Point
    {
        double x;
        double y;
    };

    typedef std::vector<Point> CoordinatesVector;

    virtual CoordinatesVector GetCoordinates() const = 0;
    virtual std::string ToString() const = 0;

    void DoOnChange();

	virtual ~HarmonicInterface() = default;
};
