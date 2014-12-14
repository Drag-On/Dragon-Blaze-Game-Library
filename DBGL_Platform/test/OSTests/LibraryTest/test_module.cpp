//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "ISimpleLibrary.h"

extern "C" int gimmeZero()
{
    return 0;
}

class ModImpl : public ISimpleLibrary
{
    public:
	virtual float add(float a, float b)
	{
	    return a + b;
	}
};

extern "C" ISimpleLibrary* create()
{
    return new ModImpl();
}

extern "C" void destroy(ISimpleLibrary* mod)
{
    delete mod;
}
