#include "targetver.h"
#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers.

#include <windows.h>
#include <vector>
#include <memory>

#include "population.h"
#include "neural_networks_dll.h"


static std::vector<std::shared_ptr<Neural_networks::Member>> p_members;
static Neural_networks::Population population(p_members);


NEURAL_NETWORKS_DLL_PROJECT_API char* initialize(void)
{
	return nullptr;
}


// This is an example of an exported function.
NEURAL_NETWORKS_DLL_PROJECT_API int fnneural_networks_dll_project(void)
{
	return 42;
}
