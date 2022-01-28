#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "Harmonic.h"
#include "HarmonicStorage.h"

using namespace std;

TEST_CASE("Harmonic")
{
    Harmonic harmonic(HarmonicType::Sin, 1, 1, 0);
    WHEN("Type")
    {
        THEN("GetType")
        {
            CHECK(harmonic.GetType() == HarmonicType::Sin);
        }
        THEN("SetType")
        {
            harmonic.SetType(HarmonicType::Cos);
            CHECK(harmonic.GetType() == HarmonicType::Cos);
        }
    }

    WHEN("Amplitude")
    {
        THEN("GetAmplitude")
        {
            CHECK(harmonic.GetAmplitude() == 1);
        }
        THEN("SetAmplitude")
        {
            harmonic.SetAmplitude(5);
            CHECK(harmonic.GetAmplitude() == 5);
        }
    }

    WHEN("Frequency")
    {
        THEN("GetFrequency")
        {
            CHECK(harmonic.GetFrequency() == 1);
        }
        THEN("SetFrequency")
        {
            harmonic.SetFrequency(5);
            CHECK(harmonic.GetFrequency() == 5);
        }
    }

    WHEN("Phase")
    {
        THEN("GetPhase")
        {
            CHECK(harmonic.GetPhase() == 0);
        }
        THEN("SetPhase")
        {
            harmonic.SetPhase(3);
            CHECK(harmonic.GetPhase() == 3);
        }
    }

    WHEN("GetYByX")
    {
        THEN("Correct coordinates")
        {
            Harmonic harmonic(HarmonicType::Sin, 4.38, 2.25, 1.5);

            CHECK(floor(harmonic.GetYByX(0) * 100) / 100 == 4.36);
            CHECK(floor(harmonic.GetYByX(0.1) * 100) / 100 == 4.32);
            CHECK(floor(harmonic.GetYByX(0.2) * 100) / 100 == 4.06);
            CHECK(floor(harmonic.GetYByX(0.3) * 100) / 100 == 3.60);
            CHECK(floor(harmonic.GetYByX(0.4) * 100) / 100 == 2.95);
            CHECK(floor(harmonic.GetYByX(0.5) * 100) / 100 == 2.16);
        }
    }
}

TEST_CASE("HarmonicsStorage")
{
    WHEN("AddHarmonic")
    {
        HarmonicStorage storage;
        shared_ptr<IHarmonic> harmonic = make_shared<Harmonic>(HarmonicType::Sin, 1, 1, 0);
        storage.AddHarmonic(harmonic);
        THEN("GetHarmonicCount == 1")
        {
            CHECK(storage.GetHarmonicCount() == 1);
        }
    }

    WHEN("GetHarmonicByIndex")
    {
        HarmonicStorage storage;
        shared_ptr<IHarmonic> harmonic = make_shared<Harmonic>(HarmonicType::Sin, 1, 1, 0);
        storage.AddHarmonic(harmonic);
        WHEN("Index - 1 > Count")
        {
            THEN("throw exception")
            {
                CHECK_THROWS(storage.GetHarmonicByIndex(1));
            }
        }
        THEN("GetHarmonicByIndex get added harmonic ")
        {
            CHECK(storage.GetHarmonicByIndex(0) == harmonic);
        }
    }

    WHEN("RemoveHarmonicByIndex")
    {
        HarmonicStorage storage;
        shared_ptr<IHarmonic> harmonic = make_shared<Harmonic>(HarmonicType::Sin, 1, 1, 0);
        storage.AddHarmonic(harmonic);
        WHEN("Index - 1 > Count")
        {
            THEN("throw exception")
            {
                CHECK_THROWS(storage.RemoveHarmonicByIndex(1));
            }
        }
        CHECK_NOTHROW(storage.RemoveHarmonicByIndex(0));
        THEN("RemoveHarmonicByIndex delete harmonic")
        {
            CHECK(storage.GetHarmonicCount() == 0);
            CHECK_THROWS(storage.GetHarmonicByIndex(0));
        }
    }
    
    WHEN("GetSumYByX")
    {
        std::shared_ptr<IHarmonicStorage> model = std::make_shared<HarmonicStorage>();
        std::shared_ptr<IHarmonic> harmonic = std::make_shared<Harmonic>(HarmonicType::Sin, 3, -3, 0.3);
        model->AddHarmonic(harmonic);

        harmonic = std::make_shared<Harmonic>(HarmonicType::Sin, 4.38, 2.25, 1.5);
        model->AddHarmonic(harmonic);

        harmonic = std::make_shared<Harmonic>(HarmonicType::Cos, 1, 1, 5);
        model->AddHarmonic(harmonic);
        THEN("Correct coordinates")
        {
            CHECK(floor(model->GetSumYByX(0) * 100) / 100 == 5.53);
            CHECK(floor(model->GetSumYByX(0.1) * 100) / 100 == 4.70);
            CHECK(floor(model->GetSumYByX(0.2) * 100) / 100 == 3.65);
            CHECK(floor(model->GetSumYByX(0.3) * 100) / 100 == 2.46);
            CHECK(floor(model->GetSumYByX(0.4) * 100) / 100 == 1.24);
            CHECK(floor(model->GetSumYByX(0.5) * 100) / 100 == 0.07);
        }
    }
}