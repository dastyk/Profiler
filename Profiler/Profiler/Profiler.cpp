#include "Profiler.h"
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

Profiler* Profiler::_instance = nullptr;

Profiler::Profiler(const char* str) : _root(nullptr, str), _currentFunc(&_root)
{
	_currentFunc->timeStart = std::chrono::high_resolution_clock::now();
}


Profiler::~Profiler()
{
}

void Profiler::Start(const char * str)
{
	static Profiler inst(str);
	_instance = &inst;
}

Profiler & Profiler::GetInstance()
{
	return *_instance;
}

const void Profiler::StopProfile()
{
	std::chrono::high_resolution_clock::time_point time = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = time - _currentFunc->timeStart;
	_currentFunc->timeSpent += diff.count();
	_currentFunc = _currentFunc->parent;

	if (_currentFunc == nullptr)
	{
		Print(_root.timeSpent);



	}

}

const void PrintTab(ostream& out, uint32_t level)
{
	for (uint32_t i = 0; i < level; i++)
	{
		out << "*";
	}
}
const void PrintD(ostream& out, const Profiler::Data& tp, uint32_t level, double totalTime)
{




	PrintTab(out, level);
	out << "Function: " << tp.name << " # Times called: " << tp.timesCalled << ", Total time spent: " << tp.timeSpent << " s ( " << (tp.timeSpent / totalTime)*100.0f << "% of total";
	if (tp.parent != nullptr)
	{
		out << ", " << (tp.timeSpent/tp.parent->timeSpent)*100.0f << "% of parents time )";
	}
		
	if (tp.children.size())
	{
		double t = tp.timeSpent;
		for (auto& c : tp.children)
			t -= c.second.timeSpent;
		out << ", Time spent excluding children : " << t << " s ( " << (t / tp.timeSpent)*100.0f << "% of time )";
	}
	out << endl;
	for (auto& d : tp.children)
	{
		PrintD(out, d.second, level + 1, totalTime);
		out << endl;
	}
	PrintTab(out, level);
	for (uint32_t i = 0; i < 10; i++)
		out << "--";
	out << endl;
}

const void Profiler::Print(double totalTime)
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);
	ofstream file("profileDump" + to_string(now_c) + ".txt");
	PrintD(file, _root, 0, totalTime);
	file.close();
	return void();
}
