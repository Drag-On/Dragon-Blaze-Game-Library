//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "IAdvancedModule.h"

extern "C" int gimmeZero()
{
    return 0;
}

class ModImpl : public IAdvancedModule
{
    public:
	virtual float add(float a, float b)
	{
	    return a + b;
	}
};

extern "C" IAdvancedModule* create()
{
    return new ModImpl();
}

extern "C" void destroy(IAdvancedModule* mod)
{
    delete mod;
}
