#include "stdafx.h"
#include "CppUnitTest.h"

#define __PROFILE
#include <Profiler.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
#pragma comment(lib, "ProfilerD.lib")

namespace UnitTest1
{		

	TEST_CLASS(UnitTest1)
	{
	public:
		void Test()
		{
			StartProfile;
			StopProfile;
		}
		TEST_METHOD(TestMethod1)
		{
			// TODO: Your test code here
			StartProfile;
			for (int i = 0; i < 100; i++)
				Test();
			StopProfile;

			Assert::AreEqual(1, 1, L"1 == 1", LINE_INFO());
		}

	};
}