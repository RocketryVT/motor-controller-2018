// TestFloatToBinary.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Test_FloatToBinary.h"
#include <iostream>
#include "Assert.h"
#include "Transmission.h"


/**
 * So uh, maybe this will work and maybe it won't. The float may be defined
 * differently on Arduino than on Windows. Using these conversions though, I
 * can bypass this a little to make sure that the values are converted correctly
 * on the serial interface.
 *
 * Update: 18/04/29
 * Arduino, Matlab, and Visual C++ use IEEE 754 standard 32 bit float points,
 * this method works
 */
int TestFloatConversions()
{
	using namespace std;
	using namespace Test;
	using namespace Transmission;
	cout << "=== Begining Test for binary to float ===" << endl;

	bool pass = true;
	
	// Test conversion from float to char (positive)
	float x = 12345.6789f;
	unsigned char a = 0;
	unsigned char b = 0;
	unsigned char c = 0;
	unsigned char d = 0;
	cout << "-- Test floatToChars (positive)" << endl;
	floatToChars(x, &a, &b, &c, &d);
	pass &= assert_equals((long)a, (long)0x46, "floatToChars (positive) 1: a is incorrect");
	pass &= assert_equals((long)b, (long)0x40, "floatToChars (positive) 2: b is incorrect");
	pass &= assert_equals((long)c, (long)0xE6, "floatToChars (positive) 3: c is incorrect");
	pass &= assert_equals((long)d, (long)0xB7, "floatToChars (positive) 4: d is incorrect");

	// Test conversion from float to char (negative)
	x = -12345.6789f;
	a = 0;
	b = 0;
	c = 0;
	d = 0;
	cout << "-- Test floatToChars (negative)" << endl;
	floatToChars(x, &a, &b, &c, &d);
	pass &= assert_equals((long)a, (long)0xC6, "floatToChars (negative) 1: a is incorrect");
	pass &= assert_equals((long)b, (long)0x40, "floatToChars (negative) 2: b is incorrect");
	pass &= assert_equals((long)c, (long)0xE6, "floatToChars (negative) 3: c is incorrect");
	pass &= assert_equals((long)d, (long)0xB7, "floatToChars (negative) 4: d is incorrect");

	// Test conversion from chars to float (Youtube example)
	x = -8.21529491902680293569190591134E-34;
	a = 0x88;
	b = 0x88;
	c = 0x80;
	d = 0x00;
	cout << "-- Test charsToFloat (Youtube example)" << endl;
	float y = charsToFloat(a, b, c, d);
	pass &= assert_equals(x, y, 1e-34, "charsToFloat (Youtube example): result is incorrect");
	pass &= assert_true(!isnan(y), "charsToFloat (Youtube example): result is NAN");

	// Test conversion from chars to float (positive)
	x = 12345.6789f;
	a = 0x46;
	b = 0x40;
	c = 0xE6;
	d = 0xB7;
	cout << "-- Test charsToFloat (positive)" << endl;
	y = charsToFloat(a, b, c, d);
	pass &= assert_equals(x, y, 1e-8, "charsToFloat (positive): result is incorrect");
	pass &= assert_true(!isnan(y), "charsToFloat (positive): result is NAN");

	// Test conversion from chars to float (negative)
	x = -12345.6789f;
	a = 0xC6;
	b = 0x40;
	c = 0xE6;
	d = 0xB7;
	cout << "-- Test charsToFloat (negative)" << endl;
	y = charsToFloat(a, b, c, d);
	pass &= assert_equals(x, y, 1e-8, "charsToFloat (negative): result is incorrect");
	pass &= assert_true(!isnan(y), "charsToFloat (negative): result is NAN");

	// Forward and backwards
	x = 1234.1234f;
	cout << "-- Test charsToFloat (F&B)" << endl;
	floatToChars(x, &a, &b, &c, &d);
	y = charsToFloat(a, b, c, d);
	pass &= assert_equals(x, y, 1e-8, "charsToFloat (F&B): result is incorrect");
	pass &= assert_true(!isnan(y), "charsToFloat (F&B): result is NAN");

	// Ouput results
	if (pass) {
		cout << "=== TestFloatConversions PASSED ===" << endl;
	}
	else {
		cout << "=== TestFloatConversions FAILED ===" << endl;
	}

    return 0;
}

