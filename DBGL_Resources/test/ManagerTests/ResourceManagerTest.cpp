//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Core/Test/Test.h"
#include "DBGL/Resources/Manager/ResourceManager.h"
#include "DBGL/Resources/Manager/AbstractResource.h"

using namespace dbgl;
using namespace std;

namespace dbgl_test_ResourceManager
{
    void noop()
    {
    }

    class TestResource : public AbstractResource
    {
	public:
	    TestResource(ResourceHandle h, int i, std::string s) : AbstractResource(h), m_int{i}, m_string{s}
	    {
	    }
	    bool identify(int i, std::string const& string) const
	    {
		return m_int == i && string == m_string;
	    }
	    bool identify(std::string const& string) const
	    {
		return string == m_string;
	    }
	    bool identify(void(*func)(void)) const
	    {
		return func == dbgl_test_ResourceManager::noop;
	    }
	    bool identify(void(TestResource::*func)(void)) const
	    {
		return func == &TestResource::noop;
	    }
	    void noop()
	    {
	    }
	    int m_int = 0;
	    std::string m_string = "";
    };
}

using namespace dbgl_test_ResourceManager;

TEST(ResourceManager,add)
{
    ResourceManager<TestResource> manager;
    auto handle1 = manager.add(42, std::string("Hello World"));
    ASSERT(handle1.isValid());
    auto pRes1 = manager.request(handle1);
    ASSERT_NEQ(pRes1, nullptr);
    ASSERT_EQ(pRes1->m_int, 42);
    ASSERT_EQ(pRes1->m_string, "Hello World");

    auto handle2 = manager.add(23, "Foo");
    ASSERT(handle2.isValid());
    auto pRes2 = manager.request(handle2);
    ASSERT_NEQ(pRes2, nullptr);
    ASSERT_EQ(pRes2->m_int, 23);
    ASSERT_EQ(pRes2->m_string, "Foo");
}

TEST(ResourceManager,identify)
{
    ResourceManager<TestResource> manager;
    manager.add(0, "");
    manager.add(42, "");
    auto handle1 = manager.add(42, std::string("Hello World"));
    ASSERT(handle1.isValid());
    manager.add(1, "Hello World");
    auto handle1_o = manager.identify("Hello World");
    ASSERT(handle1_o.isValid());
    ASSERT_EQ(handle1_o, handle1);
    auto handle1_o2 = manager.identify(42, "Hello World");
    ASSERT(handle1_o2.isValid());
    ASSERT_EQ(handle1_o2, handle1);
    auto handle1_o22 = manager.identify(42, "Hello World");
    ASSERT(handle1_o22.isValid());
    ASSERT_EQ(handle1_o22, handle1);
    auto handle1_o23 = manager.identify(&noop);
    ASSERT(handle1_o23.isValid());
    auto handle1_o24 = manager.identify(&noop);
    ASSERT_EQ(handle1_o23, handle1_o24);
    auto handle2 = manager.identify(&TestResource::noop);
    ASSERT(handle2.isValid());

    auto handle2_o = manager.identify("Hello");
    ASSERT(!handle2_o.isValid());
    ASSERT_NEQ(handle2_o, handle1);
}

TEST(ResourceManager,request)
{
    ResourceManager<TestResource> manager;
    auto handle1 = manager.add(42, std::string("Hello World"));
    ASSERT(handle1.isValid());
    auto pRes1 = manager.request(handle1);
    ASSERT_NEQ(pRes1, nullptr);
    ASSERT_EQ(pRes1->m_int, 42);
    ASSERT_EQ(pRes1->m_string, "Hello World");
}

