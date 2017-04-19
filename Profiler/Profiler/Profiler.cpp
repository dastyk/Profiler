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
	_dumpToFile();
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
	//std::chrono::duration<double> diff = time - currentFunc->timeStart;
	auto diff = time - currentFunc->timeStart;
	currentFunc->timeSpent += std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count();
	currentFunc = currentFunc->parent;
}

const void Profiler::_dumpToFile()
{
	ofstream out;

	auto end = std::chrono::system_clock::now();
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	// std::ctime(&end_time)
	out.open("temp.dot");
	if (!out.is_open())
		throw std::runtime_error("Failed to create profile dot file.");
	
	out << "digraph prof { node[shape = \"record\"];\n";
	out << "graph [ rankdir = \"LR\"];\n";
	for (size_t i = 0; i < _maxThreads; i++)
	{
		auto& p = _profiles[i].profile;
		if (p)
		{
			p->dump(out);
		}
	}

	out << "\n}";
	out.close();


	return void();
}

const void Profiler::Data::dump(std::ofstream & out)
{
	out << "\"" << this << "\"" << "[\n";
	out << "label = \"";
	out << "<f0> " << functionName;
	out << " | <f1> Times Called: " << timesCalled;
	out << " | <f2> Time Spent(IC): " << timeSpent << "ns";
	out << "\"];";
	for (auto& c : children)
	{
		c.second->dump(out);
		out << "\"" << this << "\":f0 -> \"" << c.second << "\":f0\n";
	}
	out << "\n";
	return void();
}
