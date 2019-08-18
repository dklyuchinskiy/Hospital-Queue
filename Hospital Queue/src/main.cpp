#include <iostream>
#include "Libs.h"
#include "test_runner.h"
#include "tests.h"
#include "Doctor.h"
#include "functions.h"

int main()
{
	TestRunner tr;
//	RUN_TEST(tr, TestOnePatient);
//	RUN_TEST(tr, TestDifferentAmountOfDocs);
	RUN_TEST(tr, TestBasicEqualPatsAndDocs);

	system("pause");
	return 0;
}