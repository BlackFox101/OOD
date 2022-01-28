#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "Harmonic.h"
#include "HarmonicsStorage.h"

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

    WHEN("ToString")
    {
        CHECK(harmonic.ToString() == "1*sin(1*x + 0)");
        Harmonic h(HarmonicType::Cos, 4, 2, 7);
        CHECK(h.ToString() == "4*cos(2*x + 7)");
    }

    WHEN("GetSumCoodrinates")
    {
        THEN("Correct coordinates")
        {
            Harmonic harmonic(HarmonicType::Sin, 4.38, 2.25, 1.5);
            auto coordinates = harmonic.GetCoordinates();
            auto point = coordinates[0];
            CHECK(floor(point.y * 100) / 100 == 4.36);
            point = coordinates[1];
            CHECK(floor(point.y * 100) / 100 == 4.32);
            point = coordinates[2];
            CHECK(floor(point.y * 100) / 100 == 4.06);
            point = coordinates[3];
            CHECK(floor(point.y * 100) / 100 == 3.60);
            point = coordinates[4];
            CHECK(floor(point.y * 100) / 100 == 2.95);
            point = coordinates[5];
            CHECK(floor(point.y * 100) / 100 == 2.16);
        }
    }
}

TEST_CASE("HarmonicsStorage")
{
    WHEN("AddHarmonic")
    {
        HarmonicsStorage storage;
        shared_ptr<HarmonicInterface> harmonic = make_shared<Harmonic>(HarmonicType::Sin, 1, 1, 0);
        storage.AddHarmonic(harmonic);
        THEN("GetHarmonicCount == 1")
        {
            CHECK(storage.GetHarmonicCount() == 1);
        }
    }

    WHEN("GetHarmonicByIndex")
    {
        HarmonicsStorage storage;
        shared_ptr<HarmonicInterface> harmonic = make_shared<Harmonic>(HarmonicType::Sin, 1, 1, 0);
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
        HarmonicsStorage storage;
        shared_ptr<HarmonicInterface> harmonic = make_shared<Harmonic>(HarmonicType::Sin, 1, 1, 0);
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

    WHEN("GetSumCoodrinates")
    {
        std::shared_ptr<HarmonicsStorageInterface> model = std::make_shared<HarmonicsStorage>();
        std::shared_ptr<HarmonicInterface> harmonic = std::make_shared<Harmonic>(HarmonicType::Sin, 3, -3, 0.3);
        model->AddHarmonic(harmonic);

        harmonic = std::make_shared<Harmonic>(HarmonicType::Sin, 4.38, 2.25, 1.5);
        model->AddHarmonic(harmonic);

        harmonic = std::make_shared<Harmonic>(HarmonicType::Cos, 1, 1, 5);
        model->AddHarmonic(harmonic);
        THEN("Correct coordinates")
        {
            auto coordinates = model->GetSumCoordinates();
            auto point = coordinates[0];
            CHECK(floor(point.y * 100) / 100 == 5.53);
            CHECK(point.x == 0);

            point = coordinates[1];
            CHECK(floor(point.y * 100) / 100 == 4.70);
            CHECK(point.x == 1);

            point = coordinates[2];
            CHECK(floor(point.y * 100) / 100 == 3.65);
            CHECK(point.x == 2);

            point = coordinates[3];
            CHECK(floor(point.y * 100) / 100 == 2.46);
            CHECK(point.x == 3);

            point = coordinates[4];
            CHECK(floor(point.y * 100) / 100 == 1.24);
            CHECK(point.x == 4);

            point = coordinates[5];
            CHECK(floor(point.y * 100) / 100 == 0.07);
            CHECK(point.x == 5);
        }
    }
}