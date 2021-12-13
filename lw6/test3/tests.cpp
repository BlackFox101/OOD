#pragma once
#define CATCH_CONFIG_MAIN

#include "../../catch2/catch.hpp"
#include "../task3/ModernGraphicsAdapter.h"

using namespace std;

TEST_CASE("Adapter drawLine with MoveTo")
{
	ostringstream output;
	{
		modern_graphics_lib::CModernGraphicsRenderer renderer(output);
		ModernGraphicsLibAdapter adapter(renderer);

		adapter.MoveTo(10, 10);
		adapter.LineTo(50, 50);
	}

	CHECK(output.str() == "<draw>\n"
		"  <line fromX=\"10\" fromY=\"10\" toX=\"50\" toY=\"50\">\n"
		"    <color r=\"1\" g=\"0\" b=\"0\" a=\"1\" />\n"
		"  </line>\n"
		"</draw>\n");
}

TEST_CASE("Adapter drawLine without MoveTo")
{
	ostringstream output;
	{
		modern_graphics_lib::CModernGraphicsRenderer renderer(output);
		ModernGraphicsLibAdapter adapter(renderer);

		adapter.LineTo(50, 50);
	}

	CHECK(output.str() == "<draw>\n"
		"  <line fromX=\"0\" fromY=\"0\" toX=\"50\" toY=\"50\">\n"
		"    <color r=\"1\" g=\"0\" b=\"0\" a=\"1\" />\n"
		"  </line>\n"
		"</draw>\n");
}

TEST_CASE("Set color")
{
	ostringstream output;
	{
		modern_graphics_lib::CModernGraphicsRenderer renderer(output);
		ModernGraphicsLibAdapter adapter(renderer);

		adapter.SetColor(0xABF0AC);
		adapter.LineTo(50, 50);
	}

	CHECK(output.str() == "<draw>\n"
		"  <line fromX=\"0\" fromY=\"0\" toX=\"50\" toY=\"50\">\n"
		"    <color r=\"1\" g=\"0.941176\" b=\"0.67451\" a=\"1\" />\n"
		"  </line>\n"
		"</draw>\n");
}