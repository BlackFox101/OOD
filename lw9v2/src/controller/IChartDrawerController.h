#pragma once
#include "IControllerHarmonicEditor.h"
#include "IChartDrawerControllerCreator.h"

class IChartDrawerController : public IControllerHarmonicEditor, public IChartDrawerControllerCreator
{
public:
    virtual void DeleteHarmonic(size_t index) = 0;

    virtual ~IChartDrawerController() = default;
};