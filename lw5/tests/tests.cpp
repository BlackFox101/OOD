#pragma once
#define CATCH_CONFIG_MAIN

#include "../../catch2/catch.hpp"

#include "../HtmlEditor/CImageSize.h"

//CHECK(true);
//REQUIRE(true);
//CHECK_THROWS();
//CHECK_NOTHROW();

TEST_CASE("Checking values")
{
	CHECK_NOTHROW(CImageSize(100, 1));
	CHECK_THROWS(CImageSize(101, 1));
	CHECK_THROWS(CImageSize(0, 1));
	CHECK_NOTHROW(CImageSize(1, 1));

	CHECK_NOTHROW(CImageSize(1, 100));
	CHECK_THROWS(CImageSize(1, 101));
	CHECK_THROWS(CImageSize(1, 0));
	CHECK_NOTHROW(CImageSize(1, 1));
}