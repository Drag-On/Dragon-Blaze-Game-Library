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
#include "System/Log/Log.h"

int testVector2();
int testVector3();
int testVector4();
int testVector();
int testMatrix2x2();
int testMatrix3x3();
int testMatrix4x4();
int testMatrix();
int testQuaternion();
int testWindow();
int testProperties();

int main()
{
	LOG->setLogLevel((int)dbgl::LOGLEVEL::DBG);
	LOG->info("DBGL Version %s", DBGL_VERSION_FULL);

	testVector2();
	testVector3();
	testVector4();
	testVector();
	testMatrix2x2();
	testMatrix3x3();
	testMatrix4x4();
	testMatrix();
	testQuaternion();
	//testWindow();
	testProperties();

	LOG->info("Tests done!");
	LOG->del();
	return 0;
}
