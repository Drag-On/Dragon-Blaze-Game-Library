//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef IADVANCEDMODULE_H_
#define IADVANCEDMODULE_H_

class IAdvancedModule
{
    public:
	virtual ~IAdvancedModule(){};
	virtual float add(float a, float b) = 0;
};

#endif /* IADVANCEDMODULE_H_ */
