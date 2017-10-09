#pragma once
#include "IBackend.h"

class Backend : public IBackend
{
public:
	Backend();
	~Backend();

	int DoSomething(int asd);
	void DoSomethingMore();
};

