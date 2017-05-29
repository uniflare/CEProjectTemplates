#include <windows.h>
#include "PublicInterface.h"

// Global static struct
static CPublicInterface * gPubInterface = nullptr;

// EXPORTED FUNCTIONS
extern "C" 
{
	__declspec(dllexport) void CreatePublicInterface()
	{
	 	if (!gPubInterface)
			gPubInterface = new CPublicInterface();
	}

	__declspec(dllexport) IPublicInterface * GetPublicInterface()
	{
		return gPubInterface;
	}

	__declspec(dllexport) void DestroyPublicInterface()
	{
		if (gPubInterface)
			delete gPubInterface;
	}
}