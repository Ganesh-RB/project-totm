#include "stdafx.h"
/*
Testing main file
changes for testing are inside 
main.cpp(run tests instead of game)
stdafx.h (header has gtest.h now)
rest of game files same

new files (for testing only not in game)
dummy_state.h and dummy_state.cpp
test.cpp
*/
int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}