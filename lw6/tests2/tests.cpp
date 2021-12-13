#pragma once
#define CATCH_CONFIG_MAIN

#include "../../catch2/catch.hpp"
#include "../task2/ModernGraphicsAdapter.h"

using namespace std;

TEST_CASE("Class Adapter")
{
	WHEN("Adapter drawLine with MoveTo")
	{
		ostringstream output;
		{
			ModernGraphicsLibAdapter adapter(output);

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
			ModernGraphicsLibAdapter adapter(output);

			adapter.LineTo(50, 50);
		}

		CHECK(output.str() == "<draw>\n"
			"  <line fromX=\"0\" fromY=\"0\" toX=\"50\" toY=\"50\">\n"
			"</draw>\n");
	}
}