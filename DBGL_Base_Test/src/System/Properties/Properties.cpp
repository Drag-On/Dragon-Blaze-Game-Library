//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef PROPERTIES_CPP_
#define PROPERTIES_CPP_

#include <cstdio>
#include "cute.h"
#include "DBGL/System/Log/Log.h"
#include "DBGL/System/Properties/Properties.h"

using namespace dbgl;

void testProp(Properties& prop)
{
    ASSERT(prop.getStringValue("string") == "foo");
    ASSERT(prop.getStringValue("string2") == "double declaration   ");
    ASSERT(prop.getIntValue("int") == 1);
    ASSERT(prop.getIntValue("int2") == 42);
    ASSERT(prop.getFloatValue("float") == 3.141f);
    ASSERT(prop.getFloatValue("float2") == 13.0f);
    ASSERT(prop.getBoolValue("bool") == true);
    ASSERT(prop.getBoolValue("bool2") == false);
    ASSERT(prop.getStringValue("foobar") == "");
}

int testProperties()
{
    LOG.info("Starting Properties test suite...");
    LOG.info("Constructors... ");
    Properties prop;
    LOG.info("OK!");
    LOG.info("Methods... ");
    // Test if it works without content
    ASSERT(prop.getStringValue("test") == "");
    // Load file
    prop.read("TestProperties.txt");
    // Access methods
    testProp(prop);
    // write
    prop.write("TestPropertiesCopy.txt");
    Properties copy;
    copy.read("TestPropertiesCopy.txt");
    testProp(copy);
    prop.write();
    // interpret
    prop.interpret("-foo true -bar string-bar -baz -barbaz -string SURPRISE! error");
    ASSERT(prop.getBoolValue("foo") == true);
    ASSERT(prop.getStringValue("bar") == "string-bar");
    ASSERT(prop.getStringValue("baz") == "-barbaz");
    ASSERT(prop.getStringValue("string") == "SURPRISE!");
    LOG.info("OK!");
    LOG.info("Operators... ");
    ASSERT(prop["string"] == "SURPRISE!");
    LOG.info("OK!");
    LOG.info("Done!");
    return 0;
}

#endif // PROPERTIES_CPP_
