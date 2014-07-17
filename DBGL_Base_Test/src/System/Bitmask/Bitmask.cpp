//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "cute.h"
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
    LOG.info("Starting Bitmask test suite...");
    LOG.info("Constructors... ");
    Bitmask<> bitfield1;
    ASSERT(bitfield1.getSize() == sizeof(int) * CHAR_BIT);
    ASSERT(!bitfield1.isSet(needCake));
    ASSERT(!bitfield1.isSet(needCookies));
    ASSERT(!bitfield1.isSet(needChocolate));
    Bitmask<> bitfield2(needCookies);
    ASSERT(bitfield2.getSize() == sizeof(int) * CHAR_BIT);
    ASSERT(bitfield2.isSet(needCookies));
    ASSERT(!bitfield2.isSet(needCake));
    ASSERT(!bitfield2.isSet(needChocolate));
    Bitmask<> bitfield3(bitfield2);
    ASSERT(bitfield3.getSize() == bitfield2.getSize());
    ASSERT(bitfield3.isSet(bitfield2));
    ASSERT(reallyNeedCake(needCake | needChocolate));
    Bitmask<char> bitfieldSmall;
    LOG.info("OK!");
    LOG.info("Methods... ");
    // getSize
    ASSERT(bitfield2.getSize() == sizeof(int) * CHAR_BIT);
    ASSERT(bitfieldSmall.getSize() == CHAR_BIT);
    // set
    bitfield1.set(needChocolate | needCake);
    ASSERT(bitfield1.isSet(needChocolate | needCake));
    bitfieldSmall.set(important | veryImportant | forgetThis);
    ASSERT(bitfieldSmall.isSet(important | veryImportant | forgetThis));
    bitfieldSmall.set(1 << 5);
    ASSERT(bitfieldSmall.isSet(1 << 5));
    bitfieldSmall.set(needChocolate); // Implicit conversion works as long as it fits
    ASSERT(bitfieldSmall.isSet(needChocolate));
    // clear
    bitfield1.clear(needChocolate);
    ASSERT(!bitfield1.isSet(needChocolate));
    bitfieldSmall.clear(forgetThis);
    ASSERT(!bitfieldSmall.isSet(forgetThis));
    // toggle
    bitfield1.toggle(needChocolate | needCookies);
    ASSERT(bitfield1.isSet(needChocolate | needCookies));
    bitfield1.toggle(needChocolate | needCookies);
    ASSERT(!bitfield1.isSet(needChocolate | needCookies));
    bitfieldSmall.toggle(forgetThis);
    ASSERT(bitfieldSmall.isSet(forgetThis));
    // toString
    LOG.info("bitfield1: %", bitfield1.toString());
    LOG.info("bitfield2: %", bitfield2.toString());
    LOG.info("bitfield3: %", bitfield3.toString());
    LOG.info("bitfieldSmall: %", bitfieldSmall.toString());
    LOG.info("OK!");
    LOG.info("Operators... ");
    unsigned int foo = bitfield1;
    ASSERT(foo | bitfield1);
    LOG.info("OK!");
    LOG.info("Done!");
    return 0;
}

bool reallyNeedCake(Bitmask<> flags)
{
    return flags.isSet(needCake);
}
