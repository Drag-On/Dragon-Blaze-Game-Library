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
#include <cassert>
#include "DBGL/System/Log/Log.h"
#include "DBGL/System/Properties/Properties.h"

using namespace dbgl;

int testProperties()
{
    LOG.info("Starting Properties test suite...");
    LOG.info("Constructors... ");
    Properties prop;
    LOG.info("OK!");
    LOG.info("Methods... ");
    // Test if it works without content
    assert(prop.getStringValue("test") == "");
    // Load file
    prop.read("TestProperties.txt");
    // Access methods
    assert(prop.getStringValue("string") == "foo");
    assert(prop.getStringValue("string2") == "double declaration   ");
    assert(prop.getIntValue("int") == 1);
    assert(prop.getIntValue("int2") == 42);
    assert(prop.getFloatValue("float") == 3.141f);
    assert(prop.getFloatValue("float2") == 13.0f);
    assert(prop.getBoolValue("bool") == true);
    assert(prop.getBoolValue("bool2") == false);
    assert(prop.getStringValue("foobar") == "");
    // interpret
    prop.interpret("-foo true -bar string-bar -baz -barbaz -string SURPRISE! error");
    assert(prop.getBoolValue("foo") == true);
    assert(prop.getStringValue("bar") == "string-bar");
    assert(prop.getStringValue("baz") == "-barbaz");
    assert(prop.getStringValue("string") == "SURPRISE!");
    // write
    prop.write("TestPropertiesCopy.txt");
    LOG.info("OK!");
    LOG.info("Operators... ");
    assert(prop["string"] == "SURPRISE!");
    LOG.info("OK!");
    LOG.info("Done!");
    return 0;
}

#endif // PROPERTIES_CPP_
