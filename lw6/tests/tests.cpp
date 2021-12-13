#pragma once
#define CATCH_CONFIG_MAIN

#include "../../catch2/catch.hpp"
#include "../task1/ModernGraphicsAdapter.h"

using namespace std;

TEST_CASE("Object Adapter")
{
	WHEN("Adapter drawLine with MoveTo")
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
			"</draw>\n");
	}

	WHEN("Adapter drawLine without MoveTo")
	{
		ostringstream output;
		{
			modern_graphics_lib::CModernGraphicsRenderer renderer(output);
			ModernGraphicsLibAdapter adapter(renderer);

			adapter.LineTo(50, 50);
		}

		CHECK(output.str() == "<draw>\n"
			"  <line fromX=\"0\" fromY=\"0\" toX=\"50\" toY=\"50\">\n"
			"</draw>\n");
	}
}