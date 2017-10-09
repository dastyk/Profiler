#include "IBackend.h"
#include "Backend.h"
DLLE IBackend * CreateBackend()
{
	return new Backend;
}
