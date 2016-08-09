#include <iostream>
#include <gtest/gtest.h>

#include "../inner_template_class.h"

int main(int argc, char **argv) 
{
    Holder<int> t;

	::testing::InitGoogleTest( &argc, argv );
	return RUN_ALL_TESTS();
}