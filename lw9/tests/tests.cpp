#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"

#include "../lw9/Harmonic.h"
#include "../lw9/HarmonicsStorage.h"

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
}