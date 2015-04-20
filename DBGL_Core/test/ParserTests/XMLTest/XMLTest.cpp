//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "DBGL/Core/Parsers/XML.h"
#include "DBGL/Core/Test/Test.h"

using namespace dbgl;
using namespace std;

TEST(XML, constructor)
{
    std::stringstream contents;
    contents << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
    contents << "<Main>" << std::endl;
    contents << "  <Foo val=\"42\">Hello World</Foo>" << std::endl;
    contents << "  <Foo bar=\"baz\" />" << std::endl;
    contents << "  <!-- Comment -->" << std::endl;
    contents << "</Main>" << std::endl;

    XML xml1(contents);
    ASSERT_NEQ(xml1.declaration(), nullptr);
    ASSERT_NEQ(xml1.root(), nullptr);
    ASSERT_EQ(xml1.declaration()->name(), "?xml");
    ASSERT_EQ(xml1.declaration()->attributes().size(), 2);
    ASSERT_EQ(xml1.declaration()->attributes()[0].key(), "version");
    ASSERT_EQ(xml1.declaration()->attributes()[0].value(), "1.0");
    ASSERT_EQ(xml1.declaration()->attributes()[1].key(), "encoding");
    ASSERT_EQ(xml1.declaration()->attributes()[1].value(), "UTF-8");
    ASSERT_EQ(xml1.declaration()->type(), XML::ElementType::ProcInstruction);
    ASSERT_EQ(xml1.root()->name(), "Main");
    ASSERT_EQ(xml1.root()->attributes().size(), 0);
    ASSERT_EQ(xml1.root()->type(), XML::ElementType::Element);
    ASSERT_EQ(xml1.root()->children().size(), 3);
    ASSERT_EQ(xml1.root()->children()[0]->name(), "Foo");
    ASSERT_EQ(xml1.root()->children()[0]->attributes().size(), 1);
    ASSERT_EQ(xml1.root()->children()[0]->attributes()[0].key(), "val");
    ASSERT_EQ(xml1.root()->children()[0]->attributes()[0].value(), "42");
    ASSERT_EQ(xml1.root()->children()[0]->type(), XML::ElementType::Element);
    ASSERT_EQ(xml1.root()->children()[0]->content(), "Hello World");
    ASSERT_EQ(xml1.root()->children()[1]->name(), "Foo");
    ASSERT_EQ(xml1.root()->children()[1]->attributes().size(), 1);
    ASSERT_EQ(xml1.root()->children()[1]->attributes()[0].key(), "bar");
    ASSERT_EQ(xml1.root()->children()[1]->attributes()[0].value(), "baz");
    ASSERT_EQ(xml1.root()->children()[1]->type(), XML::ElementType::Element);
    ASSERT_EQ(xml1.root()->children()[1]->content().size(), 0);
    ASSERT_EQ(xml1.root()->children()[2]->type(), XML::ElementType::Comment);
    ASSERT_EQ(xml1.root()->children()[2]->content(), "Comment");
}

TEST(XML, modify)
{
    std::stringstream contents;
    contents << "<Main>" << std::endl;
    contents << "</Main>" << std::endl;

    XML xml(contents);
    xml.root()->name() = "Marvin";
    xml.root()->content() = "FooBar";
    xml.root()->attributes().emplace_back("Brick", "Wall");
    xml.root()->createChild("Enemy", XML::ElementType::Element)->attributes().emplace_back("race", "Vogon");
    xml.root()->createChild("Friend", XML::ElementType::Element)->attributes().emplace_back("key", "Ford Prefect");
    xml.root()->children()[1]->content() = "42";
    ASSERT_EQ(xml.root()->name(), "Marvin");
    ASSERT_EQ(xml.root()->content(), "FooBar");
    ASSERT_EQ(xml.root()->attributes().size(), 1);
    ASSERT_EQ(xml.root()->attributes()[0].key(), "Brick");
    ASSERT_EQ(xml.root()->attributes()[0].value(), "Wall");
    ASSERT_EQ(xml.root()->children().size(), 2);
    ASSERT_EQ(xml.root()->children()[0]->name(), "Enemy");
    ASSERT_EQ(xml.root()->children()[0]->parent(), xml.root());
    ASSERT_EQ(xml.root()->children()[1]->name(), "Friend");
    ASSERT_EQ(xml.root()->children()[1]->parent(), xml.root());

    xml.root()->removeChild(0);
    ASSERT_EQ(xml.root()->children().size(), 1);
    ASSERT_EQ(xml.root()->children()[0]->name(), "Friend");
    ASSERT_EQ(xml.root()->children()[0]->parent(), xml.root());

    ASSERT_EQ(xml.declaration(), nullptr);
    xml.replaceDeclaration();
    ASSERT_NEQ(xml.declaration(), nullptr);
    ASSERT_EQ(xml.declaration()->name(), "?xml");
    ASSERT_EQ(xml.declaration()->type(), XML::ElementType::ProcInstruction);
}

TEST(XML, write)
{
    XML xml;

    std::stringstream ss;

    ASSERT_NOTHROW(xml.write(ss));
    ASSERT_EQ(ss.str().length(), 0);

    xml.replaceDeclaration();
    xml.declaration()->attributes().emplace_back("Foo", "Bar");
    xml.replaceRoot("Foo");
    xml.root()->attributes().emplace_back("Bar", "Baz");
    xml.root()->createChild("Bacon", XML::ElementType::Comment)->content() = "This is a comment";
    xml.root()->createChild("Bacon", XML::ElementType::Element);
    xml.root()->children()[1]->content() = "This is the element content";
    xml.root()->children()[1]->createChild("Egg", XML::ElementType::Element);
    xml.root()->createChild("Bacon", XML::ElementType::ProcInstruction)->attributes().emplace_back("Nope", "Yup");

    ASSERT_NOTHROW(xml.write(ss));

    ss.seekg(std::ios::beg);
    ss.seekp(std::ios::beg);
    XML xml2(ss);
    ASSERT_EQ(xml.declaration()->name(), xml2.declaration()->name());
    ASSERT_EQ(xml.declaration()->type(), xml2.declaration()->type());
    ASSERT_EQ(xml.declaration()->attributes().size(), xml2.declaration()->attributes().size());
    ASSERT_EQ(xml.declaration()->attributes()[0].key(), xml2.declaration()->attributes()[0].key());
    ASSERT_EQ(xml.declaration()->attributes()[0].value(), xml2.declaration()->attributes()[0].value());
    ASSERT_EQ(xml.root()->name(), xml2.root()->name());
    ASSERT_EQ(xml.root()->type(), xml2.root()->type());
    ASSERT_EQ(xml.root()->attributes().size(), xml2.root()->attributes().size());
    ASSERT_EQ(xml.root()->attributes()[0].key(), xml2.root()->attributes()[0].key());
    ASSERT_EQ(xml.root()->attributes()[0].value(), xml2.root()->attributes()[0].value());
    ASSERT_EQ(xml.root()->children().size(), xml2.root()->children().size());
    for(unsigned int i = 0; i < xml.root()->children().size(); i++)
    {
        ASSERT_EQ(xml.root()->children()[i]->type(), xml2.root()->children()[i]->type());
        ASSERT_EQ(xml.root()->children()[i]->attributes().size(), xml2.root()->children()[i]->attributes().size());
        ASSERT_EQ(xml.root()->children()[i]->children().size(), xml2.root()->children()[i]->children().size());
    }
}
