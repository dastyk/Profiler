#include "Profiler.h"


#include <string>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

Profiler* Profiler::_instance = nullptr;

Profiler::Profiler(uint32_t maxThreads) : _maxThreads(maxThreads)
{
	
	_profiles = new ThreadData[maxThreads];
}


Profiler::~Profiler()
{

	for (size_t i = 0; i < _maxThreads; i++)
	{
		if (_profiles[i].profile)
		{
			delete _profiles[i].profile;
		}
	}

	delete[] _profiles;
}



void Profiler::Init(uint32_t maxThreads)
{
	if (!_instance)
		_instance = new Profiler(maxThreads);
}

void Profiler::Shutdown()
{
	delete _instance;
	_instance = nullptr;
}

Profiler & Profiler::GetInstance()
{
	return *_instance;
}

const void Profiler::StopProfileF(uint32_t threadid)
{
	std::chrono::high_resolution_clock::time_point time = std::chrono::high_resolution_clock::now();
	auto& currentFunc = _profiles[threadid].current;
	std::chrono::duration<double> diff = time - currentFunc->timeStart;
	currentFunc->timeSpent += diff.count();
	currentFunc = currentFunc->parent;
}
