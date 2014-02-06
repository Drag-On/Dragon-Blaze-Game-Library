//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include <cstdio>
#include "DBGL_Base_Config.h"
#include "Log/Log.h"

int testVector2();
int testVector3();
int testVector4();
int testVector();
int testMatrix2x2();
int testMatrix3x3();
int testMatrix4x4();
int testMatrix();

int main()
{
	LOG->setLogLevel((int)dbgl::LOGLEVEL::INFO);
	LOG->info("DBGL Version %d.%d", DBGL_VERSION_MAJOR, DBGL_VERSION_MINOR);

	testVector2();
	testVector3();
	testVector4();
	testVector();
	testMatrix2x2();
	testMatrix3x3();
	testMatrix4x4();
	testMatrix();

	LOG->info("Tests done!");
	return 0;
}
