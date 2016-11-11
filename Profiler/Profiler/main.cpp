//
//#include "Profiler.h"
//#include <iostream>
//#if defined( DEBUG ) || defined( _DEBUG )
//#define _CRTDBG_MAP_ALLOC  
//#include <stdlib.h>  
//#include <crtdbg.h>  
//#endif
//using namespace std;
//void test();
//void FuncA();
//void FuncC();
//int main()
//{
//#if defined( DEBUG ) || defined( _DEBUG )
//	_CrtDumpMemoryLeaks();
//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
//	//_crtBreakAlloc = 242;
//#endif
//
//	StartProfiler;
//	
//	test();
//	FuncA();
//	FuncC();
//	
//
//	ProfileReturn 0;
//}
//
//
//void test()
//{
//	ProfileStart;
//	int a = 1;
//	for (int i = 0; i < 100000000; i++)
//	{
//		a += a;
//	}
//	ProfileReturn;
//}
//
//void FuncA()
//{
//	ProfileStart;
//	int a = 1;
//	while(a < 100000000)
//	{
//		a += a;
//	}
//	ProfileReturn;
//}
//
//inline void FuncB()
//{
//	ProfileStart;
//	int a = 1;
//	while (a < 200000000)
//	{
//		a += a;
//	}
//	ProfileReturn;
//}
//
//void FuncC()
//{
//	ProfileStart;
//	FuncA();
//	for (int i = 0; i < 1000000; i++)
//	{
//		FuncB();
//		/*int a = 1;
//		while (a < 200000000)
//		{
//			a += a;
//		}*/
//	}
//	ProfileReturn;
//}