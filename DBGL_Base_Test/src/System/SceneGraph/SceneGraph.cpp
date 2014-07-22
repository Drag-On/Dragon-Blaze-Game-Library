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
#include "DBGL/System/SceneGraph/SceneGraph.h"

using namespace dbgl;

class SceneGraphPrintVisitor
{
    public:
	void visit(SceneGraph& graph)
	{
	    LOG.info("Visiting scenegraph");// with % elements.", tree.size());
	}
	void visit(SceneGraph::SceneNode& node)
	{
	    LOG.info("Visiting node %.", node.getEntity()->getName());
	}
};

void visitAll(SceneGraph& sg)
{
    SceneGraphPrintVisitor visitor{};
    sg.accept(visitor);
}

int testSceneGraph()
{
    LOG.info("Starting SceneGraph test suite...");
    LOG.info("Constructors... ");
    SceneGraph sg{};
    ASSERT_EQUAL(sg.getRoot(), nullptr);
    ASSERT_EQUAL(sg.getRootEntity(), nullptr);
    LOG.info("OK!");
    LOG.info("Methods... ");
    // Print all nodes (should be zero)
    visitAll(sg);
    // Add a root node
    Entity entity1{"1"};
    SceneGraph::SceneNode rootNode{&entity1};
    sg.setRoot(&rootNode);
    visitAll(sg);
    LOG.info("OK!");
    LOG.info("Operators... ");

    LOG.info("OK!");
    LOG.info("Done!");
    return 0;
}
