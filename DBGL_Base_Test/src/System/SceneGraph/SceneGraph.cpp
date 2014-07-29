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
#include "cute.h"
#include "DBGL/System/Log/Log.h"
#include "DBGL/System/Entity/Entity.h"
#include "DBGL/System/Scene/SceneGraph.h"

using namespace dbgl;

namespace SceneGraphTest
{
    class SceneGraphPrintVisitor
    {
        public:
    	void visit(SceneGraph<Entity>& graph)
    	{
    	    LOG.info("Visiting scenegraph");// with % elements.", tree.size());
    	}
    	void visit(SceneGraph<Entity>::Node& node)
    	{
    	    LOG.info("Visiting node %.", node.getEntity()->getName());
    	}
    };

    void visitAll(SceneGraph<Entity>& sg)
    {
        SceneGraphPrintVisitor visitor{};
        sg.accept(visitor);
    }

    void testConstructor()
    {
        SceneGraph<Entity> sg{};
        ASSERT_EQUAL(sg.getNodes().size(), 0);
        // Print all nodes (should be zero)
        visitAll(sg);
    }

    void testTraversal()
    {
        SceneGraph<Entity> sg{};
        // Add a root node
        Entity entity1{"1"};
        sg.addNode(&entity1);
        visitAll(sg);
//        Entity entity2{"2"};
//        Entity entity3{"3"};
//        Entity entity4{"4"};

    }

    void testNodeConnection()
    {
	SceneGraph<Entity> sg{};
	Entity entity1{"1"};
	Entity entity2{"2"};
	Entity entity3{"3"};
	Entity entity4{"4"};
	Entity entity5{"5"};

	auto node = sg.addNode(&entity1);
	ASSERT_EQUAL(nullptr, node->getParent());
	ASSERT_EQUAL(0, node->getChildren().size());

	auto child = node->addChild(&entity3);
	ASSERT_EQUAL(node, child->getParent());
	ASSERT_EQUAL(0, child->getChildren().size());
	ASSERT_EQUAL(nullptr, node->getParent());
	ASSERT_EQUAL(1, node->getChildren().size());
    }
}


cute::suite testSceneGraph()
{
    LOG.info("Starting SceneGraph test suite...");

    cute::suite s {};
    s.push_back(CUTE(SceneGraphTest::testConstructor));
    s.push_back(CUTE(SceneGraphTest::testTraversal));
    s.push_back(CUTE(SceneGraphTest::testNodeConnection));

    return s;
}
