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

TEST(ResourceManager,remove)
{
    ResourceManager<TestResource> manager;
    auto handle0 = manager.add(0, "0");
    auto handle1 = manager.add(1, "1");
    auto handle2 = manager.add(2, "2");
    auto handle3 = manager.add(3, "3");
    auto handle1Copy = handle1;
    auto pRes1 = manager.request(handle1, true);
    ASSERT_NEQ(pRes1, nullptr);
    ASSERT_EQ(pRes1->m_int, 1);
    ASSERT_EQ(pRes1->m_string, "1");
    ASSERT(pRes1->isLoaded());
    bool removed = manager.remove(handle1, false);
    ASSERT(removed == false);
    handle1Copy = TestResource::ResourceHandle{};
    removed = manager.remove(handle1, false);
    ASSERT(removed == true);
    auto handle5 = manager.add(5, "5");
    auto handle5Copy = handle5;
    auto handle5Ident = manager.identify(5, "5");
    ASSERT_EQ(handle5, handle5Ident);
    removed = manager.remove(handle5, false);
    ASSERT(removed == false);
    removed = manager.remove(handle5, true);
    ASSERT(removed == true);
}

TEST(ResourceManager,needLoad)
{
    ResourceManager<TestResource> manager;
    auto handle0 = manager.add(0, "0");
    auto handle1 = manager.add(1, "1");
    auto handle2 = manager.add(2, "2");
    auto handle3 = manager.add(3, "3");
    ASSERT_EQ(manager.needLoad(), false);
    manager.request(handle1, false);
    ASSERT_EQ(manager.needLoad(), true);
    manager.loadNext();
    ASSERT_EQ(manager.needLoad(), false);
}

TEST(ResourceManager,getLoadQueueSize)
{
    ResourceManager<TestResource> manager;
    auto handle0 = manager.add(0, "0");
    auto handle1 = manager.add(1, "1");
    auto handle2 = manager.add(2, "2");
    auto handle3 = manager.add(3, "3");
    ASSERT_EQ(manager.getLoadQueueSize(), 0);
    auto pRes1 = manager.request(handle1, false);
    ASSERT_EQ(manager.getLoadQueueSize(), 1);
    auto pRes2 = manager.request(handle2, false);
    ASSERT_EQ(manager.getLoadQueueSize(), 2);
    manager.loadNext();
    ASSERT_EQ(manager.getLoadQueueSize(), 1);
    manager.loadNext();
    ASSERT_EQ(manager.getLoadQueueSize(), 0);
    ASSERT_EQ(pRes1->isLoaded(), true);
    ASSERT_EQ(pRes2->isLoaded(), true);
}

TEST(ResourceManager,size)
{
    ResourceManager<TestResource> manager;
    ASSERT_EQ(manager.size(), 0);
    auto handle0 = manager.add(0, "0");
    auto handle1 = manager.add(1, "1");
    auto handle2 = manager.add(2, "2");
    auto handle3 = manager.add(3, "3");
    ASSERT_EQ(manager.size(), 4);
    manager.remove(handle2);
    ASSERT_EQ(manager.size(), 3);
    auto handle4 = manager.add(4, "4");
    ASSERT_EQ(manager.size(), 4);
    manager.remove(handle0);
    manager.remove(handle1);
    manager.remove(handle3);
    manager.remove(handle4);
    ASSERT_EQ(manager.size(), 0);
}

TEST(ResourceManager,loadNext)
{
    ResourceManager<TestResource> manager;
    {
	auto handle0 = manager.add(0, "0");
	auto handle1 = manager.add(1, "1");
	auto handle2 = manager.add(2, "2");
	auto handle3 = manager.add(3, "3");
	auto pRes1 = manager.request(handle1, false);
	auto pRes2 = manager.request(handle2, false);
	while (manager.needLoad())
	    manager.loadNext();
	ASSERT_EQ(pRes1->isLoaded(), true);
	ASSERT_EQ(pRes2->isLoaded(), true);
	ASSERT_NOTHROW(manager.loadNext());
    }
    // Let it unload the resources
    for(unsigned int i = 0; i < manager.size(); i++)
	manager.loadNext();
    ASSERT_EQ(manager.request(manager.identify(1, "1"), false)->isLoaded(), false);
    ASSERT_EQ(manager.request(manager.identify(2, "2"), false)->isLoaded(), false);
}
