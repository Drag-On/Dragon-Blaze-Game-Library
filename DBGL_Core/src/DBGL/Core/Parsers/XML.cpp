//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include <fstream>
#include <stdexcept>
#include <sstream>
#include <string>
#include "DBGL/Core/Parsers/XML.h"
#include "DBGL/Core/Utility/StringUtility.h"

namespace dbgl
{
    XML::XML(std::string const& file)
    {
        std::ifstream inStream;
        inStream.open(file.c_str(), std::ios::in);
        if (inStream.is_open())
        {
            readFromStream(inStream);
            inStream.close();
        }
        else
            throw std::runtime_error("Couldn't open file " + file + ".");
    }

    XML::XML(std::istream& in)
    {
        readFromStream(in);
    }

    XML::~XML()
    {
        free(m_pRoot);
        delete m_pDeclaration;
    }

    void XML::readFromStream(std::istream& in)
    {
        // Read in whole file
        std::stringstream contents;
        contents << in.rdbuf();
        // Interpret contents
        interpret(contents);
    }

    void XML::interpret(std::stringstream& content)
    {
        while (content.good())
        {
            auto e = tryReadElement(content);
            if (e != nullptr && e->m_type == ElementType::ProcInstruction && m_pDeclaration == nullptr)
                m_pDeclaration = e;
            else if (m_pRoot == nullptr && e->m_type == ElementType::Element)
                m_pRoot = e;
            else
                delete e; // Discard anything on root level which is not the root node or the xml declaration
        }
    }

    auto XML::tryReadElement(std::stringstream& content) -> Element*
    {
        char curCharacter;
        // Check for correct tag
        while (content.good())
        {
            content.read(&curCharacter, 1);
            if (curCharacter != '<' && !std::isspace(curCharacter))
                throw std::runtime_error(
                        "XML file is misformatted! Expected < but got " + std::to_string(curCharacter) + ".");
            else if (curCharacter == '<')
                break;
        }
        if (!content.good())
            return nullptr;
        // Check if this actually is a closing tag
        if (content.peek() == '/')
            return nullptr;
        // Read in name
        Element* e = new Element;
        while (content.good())
        {
            content.read(&curCharacter, 1);
            if (!isspace(curCharacter) && curCharacter != '>')
                e->m_name += curCharacter;
            else break;
        }
        // Check type
        if (e->m_name[0] == '?')
            e->m_type = ElementType::ProcInstruction;
        else if (e->m_name[0] == '!')
            e->m_type = ElementType::Comment;
        else
            e->m_type = ElementType::Element;
        bool isEmptyElement = false;
        // Read attributes
        if (curCharacter != '>' && e->m_type != ElementType::Comment)
            isEmptyElement = tryReadAttributes(content, e->m_attributes);
        // Read content
        if (e->m_type == ElementType::Element && !isEmptyElement)
        {
            tryReadContent(content, e);
            StringUtility::trim(e->m_content);
        }
        // Read comment
        if(e->m_type == ElementType::Comment)
            tryReadComment(content, e);

        return e;
    }

    bool XML::tryReadAttributes(std::stringstream& content, std::vector<Attribute>& attributes)
    {
        char curCharacter;
        std::string name, value;
        bool readValue = false;
        while (content.good())
        {
            content.read(&curCharacter, 1);
            if (curCharacter == '>')
                break;
            if (curCharacter == '=')
            {
                content.read(&curCharacter, 1);
                if (curCharacter != '"')
                    throw std::runtime_error(
                            "XML file is misformatted! Expected \" but got " + std::to_string(curCharacter) + ".");
                readValue = true;
                continue;
            }
            if (readValue)
            {
                if (curCharacter == '"')
                {
                    readValue = false;
                    StringUtility::trim(name);
                    StringUtility::trim(value);
                    attributes.emplace_back(name, value);
                    name.clear();
                    value.clear();
                }
                else
                    value += curCharacter;
            }
            else
            {
                name += curCharacter;
            }
        }
        return !name.empty();
    }

    void XML::tryReadContent(std::stringstream& content, XML::Element* elem)
    {
        char curCharacter;
        while (content.good())
        {
            if (content.peek() != '<')
            {
                // Add as free content
                content.read(&curCharacter, 1);
                elem->m_content += curCharacter;
            }
            else
            {
                // More markup, try to read a child element
                auto child = tryReadElement(content);
                if (child != nullptr)
                {
                    child->m_pParent = elem;
                    elem->m_children.push_back(child);
                }
                else // Was a closing tag
                {
                    content.read(&curCharacter, 1);
                    if (curCharacter == '/')
                    {
                        char* closingTag = new char[elem->m_name.size() + 1];
                        content.read(closingTag, elem->m_name.size());
                        closingTag[elem->m_name.size()] = '\0';
                        std::string closingString(closingTag);
                        content.read(&curCharacter, 1);
                        if (closingString != elem->m_name || curCharacter != '>')
                            throw std::runtime_error(
                                    "XML file is misformatted! Expected </" + elem->m_name + ">" + " but got </" +
                                    closingString + curCharacter + ".");
                        delete[] closingTag;
                        return;
                    }
                    else
                    {
                        throw std::runtime_error("XML file is misformatted! Expected closing tag, but got " +
                                                 std::to_string(curCharacter) + ".");
                    }

                }
            }
        }
    }

    void XML::tryReadComment(std::stringstream& content, XML::Element* pElement)
    {
        char curCharacter;
        std::string comment;
        while (content.good())
        {
            content.read(&curCharacter, 1);
            comment += curCharacter;

            if(comment.size() >= 3)
            {
                std::string substr = comment.substr(comment.size()-3);
                if(substr == "-->")
                {
                    substr = comment.substr(0, comment.size()-3);
                    pElement->m_content = StringUtility::trim(substr);
                    return;
                }
            }
        }
    }

    void XML::free(Element* elem)
    {
        if (elem != nullptr)
        {
            for (auto e : elem->m_children)
                free(e);
            delete elem;
        }
    }

    XML::Attribute::Attribute(std::string const& name, std::string const& value) : m_name{name}, m_value{value}
    {
    }

    std::string& XML::Attribute::name()
    {
        return m_name;
    }

    std::string const& XML::Attribute::name() const
    {
        return m_name;
    }

    std::string& XML::Attribute::value()
    {
        return m_value;
    }

    std::string const& XML::Attribute::value() const
    {
        return m_value;
    }

    std::string& XML::Element::name()
    {
        return m_name;
    }

    std::string const& XML::Element::name() const
    {
        return m_name;
    }

    std::string& XML::Element::content()
    {
        return m_content;
    }

    std::string const& XML::Element::content() const
    {
        return m_content;
    }

    XML::ElementType& XML::Element::type()
    {
        return m_type;
    }

    XML::ElementType const& XML::Element::type() const
    {
        return m_type;
    }

    std::vector<XML::Attribute>& XML::Element::attributes()
    {
        return m_attributes;
    }

    std::vector<XML::Attribute> const& XML::Element::attributes() const
    {
        return m_attributes;
    }

    XML::Element* XML::Element::parent() const
    {
        return m_pParent;
    }

    std::vector<XML::Element*> const& XML::Element::children() const
    {
        return m_children;
    }

    auto XML::Element::createChild(std::string const& name, ElementType type) -> Element*
    {
        Element* e = new Element;
        e->m_name = name;
        e->m_pParent = this;
        e->m_type = type;
        m_children.push_back(e);
        return e;
    }

    void XML::Element::removeChild(unsigned int num)
    {
        auto e = m_children[num];
        m_children.erase(m_children.begin() + num);
        XML::free(e);
    }

    XML::Element* XML::declaration()
    {
        return m_pDeclaration;
    }

    XML::Element const* XML::declaration() const
    {
        return m_pDeclaration;
    }

    XML::Element* XML::root()
    {
        return m_pRoot;
    }

    XML::Element const* XML::root() const
    {
        return m_pRoot;
    }

    void XML::replaceDeclaration()
    {
        free(m_pDeclaration);
        m_pDeclaration = new Element;
        m_pDeclaration->m_name = "?xml";
        m_pDeclaration->m_type = ElementType::ProcInstruction;
    }

    void XML::replaceRoot(std::string const& name)
    {
        free(m_pRoot);
        m_pRoot = new Element;
        m_pRoot->m_name = name;
        m_pRoot->m_type = ElementType::Element;
    }
}


