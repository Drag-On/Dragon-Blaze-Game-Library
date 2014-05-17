//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include <cassert>
#include "DBGL/System/Log/Log.h"
#include "DBGL/System/Bitmask/Bitmask.h"

using namespace dbgl;

bool reallyNeedCake(Bitmask<> flags);
const int needCake = 1<<0;
const int needCookies = 1<<1;
const int needChocolate = 1<<2;

const char important = 1 << 0;
const char veryImportant = 1 << 4;
const char forgetThis = 1 << 7;

int testBitmask()
{
    LOG->info("Starting Bitmask test suite...");
    LOG->info("Constructors... ");
    Bitmask<> bitfield1;
    assert(bitfield1.getSize() == sizeof(int) * CHAR_BIT);
    assert(!bitfield1.isSet(needCake));
    assert(!bitfield1.isSet(needCookies));
    assert(!bitfield1.isSet(needChocolate));
    Bitmask<> bitfield2(needCookies);
    assert(bitfield2.getSize() == sizeof(int) * CHAR_BIT);
    assert(bitfield2.isSet(needCookies));
    assert(!bitfield2.isSet(needCake));
    assert(!bitfield2.isSet(needChocolate));
    Bitmask<> bitfield3(bitfield2);
    assert(bitfield3.getSize() == bitfield2.getSize());
    assert(bitfield3.isSet(bitfield2));
    assert(reallyNeedCake(needCake | needChocolate));
    Bitmask<char> bitfieldSmall;
    LOG->info("OK!");
    LOG->info("Methods... ");
    // getSize
    assert(bitfield2.getSize() == sizeof(int) * CHAR_BIT);
    assert(bitfieldSmall.getSize() == CHAR_BIT);
    // set
    bitfield1.set(needChocolate | needCake);
    assert(bitfield1.isSet(needChocolate | needCake));
    bitfieldSmall.set(important | veryImportant | forgetThis);
    assert(bitfieldSmall.isSet(important | veryImportant | forgetThis));
    bitfieldSmall.set(1 << 5);
    assert(bitfieldSmall.isSet(1 << 5));
    bitfieldSmall.set(needChocolate); // Implicit conversion works as long as it fits
    assert(bitfieldSmall.isSet(needChocolate));
    // clear
    bitfield1.clear(needChocolate);
    assert(!bitfield1.isSet(needChocolate));
    bitfieldSmall.clear(forgetThis);
    assert(!bitfieldSmall.isSet(forgetThis));
    // toggle
    bitfield1.toggle(needChocolate | needCookies);
    assert(bitfield1.isSet(needChocolate | needCookies));
    bitfield1.toggle(needChocolate | needCookies);
    assert(!bitfield1.isSet(needChocolate | needCookies));
    bitfieldSmall.toggle(forgetThis);
    assert(bitfieldSmall.isSet(forgetThis));
    // toString
    LOG->info("bitfield1: %", bitfield1.toString());
    LOG->info("bitfield2: %", bitfield2.toString());
    LOG->info("bitfield3: %", bitfield3.toString());
    LOG->info("bitfieldSmall: %", bitfieldSmall.toString());
    LOG->info("OK!");
    LOG->info("Operators... ");
    unsigned int foo = bitfield1;
    assert(foo | bitfield1);
    LOG->info("OK!");
    LOG->info("Done!");
    return 0;
}

bool reallyNeedCake(Bitmask<> flags)
{
    return flags.isSet(needCake);
}
