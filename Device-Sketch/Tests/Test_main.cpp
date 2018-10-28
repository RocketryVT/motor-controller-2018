// TestTransmissionFunctions.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Assert.h"
#include "../Desktop-tests-src/Arduino.h"
#include "Test_main.h"
#include "Test_Transmission.h"
#include "Test_FloatToBinary.h"

void Test_main(bool istestondevice)
{
	using namespace Test;

	// Initialize test results string
	resstriter = 0;

	// Do Tests
	TestFloatConversions();
	TestTransmission();

	if (istestondevice) {
		// Run tests on connected hardware
		// Ouput Test Results String to serial port as response
	}
	else {
		print(resstr);
	}

	return;
}

