

#define __PROFILE
#include "Profiler.h"
#include <iostream>
#if defined( DEBUG ) || defined( _DEBUG )
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  
#endif
using namespace std;
uint32_t thread = 0;
void test();
void FuncA();
void FuncC();
void FuncB();
int main()
{
#if defined( DEBUG ) || defined( _DEBUG )
	_CrtDumpMemoryLeaks();
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	//_crtBreakAlloc = 242;
#endif

	InitProfilerThreads(2);
	StartProfileThread(thread);
	test();
	FuncA();
	FuncC();
	StopProfileThread(thread);

	thread = 1;

	StartProfileThread(thread);
	FuncB();
	FuncA();
	for (int i = 0; i < 10; i++)
		test();
	StopProfileThread(thread);
	ShutdownProfiler;
}


void test()
{
	StartProfileThread(thread);
	int a = 1;
	for (int i = 0; i < 100000000; i++)
	{
		a += a;
	}
	ProfileReturnVoidThread(thread);
}

void FuncA()
{
	StartProfileThread(thread);
	int a = 1;
	while(a < 100000000)
	{
		a += a;
	}
	ProfileReturnVoidThread(thread);
}

inline void FuncB()
{
	StartProfileThread(thread);
	int a = 1;
	while (a < 200000000)
	{
		a += a;
	}
	ProfileReturnVoidThread(thread);
}

void FuncC()
{
	StartProfileThread(thread);
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
	ProfileReturnVoidThread(thread);
}