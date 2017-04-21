#include "Profiler.h"


#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <thread>

using namespace std;

Profiler::Profiler() 
{

}


Profiler::~Profiler()
{
	_dumpToFile();

	if (_profile)
	{
		delete _profile;
	}

}



//void Profiler::Init(uint32_t maxThreads)
//{
//	if (!_instance)
//		_instance = new Profiler(maxThreads);
//}
//
//void Profiler::Shutdown()
//{
//	delete _instance;
//	_instance = nullptr;
//}

Profiler & Profiler::GetInstance()
{
	static thread_local Profiler inst;
	return inst;
}

const void Profiler::StopProfileF(uint32_t threadid)
{
	std::chrono::high_resolution_clock::time_point time = std::chrono::high_resolution_clock::now();
	//std::chrono::duration<double> diff = time - currentFunc->timeStart;
	auto diff = time - _current->timeStart;
	_current->timeSpent += std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count();
	_current = _current->parent;
}
#include <sstream>

const void Profiler::_dumpToFile()
{
	ofstream out;

	auto end = std::chrono::system_clock::now();
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	// std::ctime(&end_time)

	std::ostringstream ss;

	ss << std::this_thread::get_id();

	std::string idstr = ss.str();
	out.open("thread" + ss.str() + ".dot", ios::trunc);
	if (!out.is_open())
		throw std::runtime_error("Failed to create profile dot file.");

	out << "digraph prof { node[shape = \"record\"];\n";
	out << "graph [ rankdir = \"LR\"];\n";

	auto& p = _profile;
	if (p)
	{
		p->dump(out);
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
	if (parent)
		out << ", " << (float)timeSpent / parent->timeSpent << " % of parents.";
	if (children.size())
	{
		auto temp = timeSpent;
		for (auto& c : children)
			temp -= c.second->timeSpent;
		out << " | Time Spent(EC): " << temp << "ns";

	}
			out << "\"];\n";
	for (auto& c : children)
	{
		c.second->dump(out);
		out << "\"" << this << "\":f0 -> \"" << c.second << "\":f0\n";
	}
	out << "\n";
	return void();
}
