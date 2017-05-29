#pragma once

#include "../include/IPublicInterface.h"


class CPublicInterface : public IPublicInterface
{
	const char * name = "ThirdPartyLibExample";
	const char * version = "1.0.0";

public:
	CPublicInterface() {}
	~CPublicInterface() {}

	// IPublicInterface
	virtual const char * GetName() override;
	virtual const char * GetVersion() override;
	// ~IPublicInterface
};