//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include <vector>
#include "cute.h"
#include "DBGL/System/Log/Log.h"
#include "DBGL/System/ResourceManager/ResourceManager.h"
#include "DBGL/System/ResourceManager/IResource.h"

using namespace dbgl;

namespace ResourceManagerTest
{
    class FakeResource : public IResource
    {
	public:
	    FakeResource(std::string filename) : IResource(filename)
	    {
	    }
	    virtual ~FakeResource()
	    {
	    }
	    virtual void load()
	    {
		IResource::load();
	    }
	    virtual void unload()
	    {
		IResource::unload();
	    }

	    friend class ResourceManager<FakeResource>;
    };

    void testConstructor()
    {
	ResourceManager<FakeResource> manager{};
	ASSERT(manager.size() == 0);
	ASSERT(manager.needLoad() == false);
    }

    void testAdd()
    {
	ResourceManager<FakeResource> manager{};
	ResourceHandle handle = manager.add("Some/File.res");
	ASSERT(manager.size() == 1);
	ASSERT(manager.needLoad() == false);
	ASSERT(manager.checkExist("Some/File.res"));
	ASSERT(manager.checkExist(handle));
	std::vector<std::string> filenames { "Another/File.res", "Super/Important.res" };
	manager.add(filenames.begin(), filenames.end());
	ASSERT(manager.size() == 3);
	ASSERT(manager.needLoad() == false);
	for(std::string s : filenames)
	{
	    ASSERT(manager.checkExist(s));
	    ASSERT(manager.checkExist(manager.getHandle(s)));
	}
    }

    void testRequestRelease()
    {
	ResourceManager<FakeResource> manager{};
	std::vector<std::string> filenames { "File/One.res", "File/Two.res" };
	manager.add(filenames.begin(), filenames.end());
	ASSERT(manager.size() == filenames.size());
	ASSERT(manager.needLoad() == false);
	for(std::string s : filenames)
	{
	    ASSERT(manager.checkExist(s));
	    ASSERT(manager.checkExist(manager.getHandle(s)));
	}
	// Request without force load
	FakeResource* res1 = manager.request(filenames[0], false);
	ASSERT(manager.size() == filenames.size());
	ASSERT(manager.needLoad() == true);
	for(std::string s : filenames)
	{
	    ASSERT(manager.checkExist(s));
	    ASSERT(manager.checkExist(manager.getHandle(s)));
	}
	ASSERT(res1->isLoaded() == false);
	ASSERT(res1->getFilename() == filenames[0]);
	ASSERT(res1->getHandle() == manager.getHandle(filenames[0]));
	manager.loadNext();
	ASSERT(manager.needLoad() == false);
	ASSERT(res1->isLoaded() == true);
	// Request with force load
	FakeResource* res2 = manager.request(filenames[1], true);
	ASSERT(manager.size() == filenames.size());
	ASSERT(manager.needLoad() == false);
	for(std::string s : filenames)
	{
	    ASSERT(manager.checkExist(s));
	    ASSERT(manager.checkExist(manager.getHandle(s)));
	}
	ASSERT(res2->isLoaded() == true);
	ASSERT(res2->getFilename() == filenames[1]);
	ASSERT(res2->getHandle() == manager.getHandle(filenames[1]));
	manager.loadNext();
	ASSERT(manager.needLoad() == false);
	ASSERT(res2->isLoaded() == true);
	// Release res1
	manager.release(filenames[0]);
	ASSERT(manager.size() == filenames.size());
	ASSERT(manager.needLoad() == true);
	ASSERT(res2->isLoaded() == true);
	manager.request(filenames[0]);
	manager.loadNext();
	ASSERT(manager.needLoad() == false);
	manager.release(filenames[0]);
	manager.release(filenames[0]);
	ASSERT(manager.needLoad() == true);
	manager.loadNext();
	ASSERT(manager.needLoad() == false);
    }

    void testRemove()
    {
	ResourceManager<FakeResource> manager{};
	std::vector<std::string> filenames { "File/One.res", "File/Two.res" };
	manager.add(filenames.begin(), filenames.end());
	ASSERT(manager.size() == filenames.size());
	ASSERT(manager.needLoad() == false);
	manager.request(filenames[0]);
	ASSERT(manager.needLoad() == true);
	manager.remove(filenames[0]);
	ASSERT(manager.size() == filenames.size() - 1);
	ASSERT(manager.needLoad() == false);
	ASSERT(manager.getHandle(filenames[0]) == InvalidHandle);
	ASSERT(manager.request(filenames[0]) == nullptr);
	manager.add("File/Three.res");
	ASSERT(manager.size() == filenames.size());
	ASSERT(manager.needLoad() == false);
    }
}

using namespace ResourceManagerTest;

cute::suite testResourceManager()
{
    cute::suite s{};
    s.push_back(CUTE(testConstructor));
    s.push_back(CUTE(testAdd));
    s.push_back(CUTE(testRequestRelease));
    s.push_back(CUTE(testRemove));
    return s;
}
