// TestTransmissionFunctions.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Test_main.h"
#include "Test_Transmission.h"
#include "Test_FloatToBinary.h"
//#include "Transmission.h"
//#include "Hardware.h"
//#include "Control.h"

int Test_main()
{
	// Do tests I wrote earlier
	TestFloatConversions();

	// Test for packet compilation
	TestTransmission();

    return 0;
}

