

#define __PROFILE
#include "Profiler.h"
#include <iostream>
#if defined( DEBUG ) || defined( _DEBUG )
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  
#endif
using namespace std;
void test();
void FuncA();
void FuncC();
void FuncB();
#include <thread>


int main()
{
	#if defined( DEBUG ) || defined( _DEBUG )
		_CrtDumpMemoryLeaks();
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
		//_crtBreakAlloc = 242;
	#endif
	
		auto t = std::thread(FuncB);

		StartProfile;
		test();
		FuncA();
		FuncC();
		StopProfile;

		//StartProfile;
		//FuncB();
		//FuncA();
		//for (int i = 0; i < 10; i++)
		//	test();
		//StopProfile;

		t.join();
}


void test()
{
	StartProfile;
	int a = 1;
	for (int i = 0; i < 100000000; i++)
	{
		a += a;
	}
	ProfileReturnVoid;
}

void FuncA()
{
	StartProfile;
	int a = 1;
	while(a < 100000000)
	{
		a += a;
	}
	ProfileReturnVoid;
}

inline void FuncB()
{
	StartProfile;
	int a = 1;
	while (a < 10000)
	{
		a += 1;
	}
	ProfileReturnVoid;
}

void FuncC()
{
	StartProfile;
	FuncA();
	for (int i = 0; i < 1000000; i++)
	{
		FuncB();
		/*int a = 1;
		while (a < 200000000)
		{
			a += a;
		}*/
	}
	ProfileReturnVoid;
}