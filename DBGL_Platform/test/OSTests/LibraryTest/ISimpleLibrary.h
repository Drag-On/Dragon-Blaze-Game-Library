//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef ISIMPLELIBRARY_H_
#define ISIMPLELIBRARY_H_

class ISimpleLibrary
{
    public:
	virtual ~ISimpleLibrary(){};
	virtual float add(float a, float b) = 0;
};

#endif /* ISIMPLELIBRARY_H_ */
