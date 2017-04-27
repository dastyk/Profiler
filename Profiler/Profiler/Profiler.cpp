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
	_current->timeSpent += std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
	_current = _current->parent;
}

#include <Windows.h>

const void Profiler::_dumpToFile()
{
	ofstream out;

	auto end = std::chrono::system_clock::now();
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	// std::ctime(&end_time)

	
	
	std::stringstream ss;
	

	ss << "digraph \"" << this_thread::get_id() << "\" { node[shape = \"record\"];\n";
	ss << "graph [ rankdir = \"LR\"];\n";

	auto& p = _profile;
	if (p)
	{
		p->dump(ss);
	}




	ss << "\n}\n\n";


	HANDLE f;

	do
	{
		f = CreateFile("profile.dot", FILE_APPEND_DATA, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	} while (f == INVALID_HANDLE_VALUE);

	WriteFile(f, ss.str().c_str(), ss.str().size(), NULL, NULL);

	CloseHandle(f);

	return void();
}

const void Profiler::Data::dump(std::stringstream & out)
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
