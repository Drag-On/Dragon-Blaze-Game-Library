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
#include "DBGL/System/SceneGraph/SceneGraph.h"

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
        ASSERT_EQUAL(sg.getRoot(), nullptr);
        ASSERT_EQUAL(sg.getRootEntity(), nullptr);
        // Print all nodes (should be zero)
        visitAll(sg);
    }

    void testTraversal()
    {
        SceneGraph<Entity> sg{};
        // Add a root node
        Entity entity1{"1"};
        SceneGraph<Entity>::Node rootNode{&entity1};
        sg.setRoot(&rootNode);
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
	SceneGraph<Entity>::Node rootNode{&entity1};
	ASSERT_EQUAL(nullptr, rootNode.getParent());
	ASSERT_EQUAL(0, rootNode.getChildren().size());

	SceneGraph<Entity>::Node childNode1{&entity2};
	rootNode.addChild(&childNode1);
	ASSERT_EQUAL(nullptr, rootNode.getParent());
	ASSERT_EQUAL(1, rootNode.getChildren().size());
	ASSERT_EQUAL(&rootNode, childNode1.getParent());
	ASSERT_EQUAL(0, childNode1.getChildren().size());

	SceneGraph<Entity>::Node childNode2{&entity3};
	rootNode.addChild(&childNode2);
	ASSERT_EQUAL(nullptr, rootNode.getParent());
	ASSERT_EQUAL(2, rootNode.getChildren().size());
	ASSERT_EQUAL(&rootNode, childNode2.getParent());
	ASSERT_EQUAL(0, childNode2.getChildren().size());

	SceneGraph<Entity>::Node childNode3{&entity4};
	childNode2.addChild(&childNode3);
	ASSERT_EQUAL(nullptr, rootNode.getParent());
	ASSERT_EQUAL(2, rootNode.getChildren().size());
	ASSERT_EQUAL(&rootNode, childNode2.getParent());
	ASSERT_EQUAL(1, childNode2.getChildren().size());
	ASSERT_EQUAL(&childNode2, childNode3.getParent());
	ASSERT_EQUAL(0, childNode3.getChildren().size());

	SceneGraph<Entity>::Node childNode4{&entity5};
	childNode4.setParent(&childNode2);
	ASSERT_EQUAL(nullptr, rootNode.getParent());
	ASSERT_EQUAL(2, rootNode.getChildren().size());
	ASSERT_EQUAL(&rootNode, childNode2.getParent());
	ASSERT_EQUAL(2, childNode2.getChildren().size());
	ASSERT_EQUAL(&childNode2, childNode3.getParent());
	ASSERT_EQUAL(0, childNode3.getChildren().size());
	ASSERT_EQUAL(&childNode2, childNode4.getParent());
	ASSERT_EQUAL(0, childNode4.getChildren().size());

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
