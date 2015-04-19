//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef DBGL_XML_H
#define DBGL_XML_H

#include <string>
#include <istream>
#include <vector>

namespace dbgl
{
    /**
     * @brief Limited parser for xml-like files.
     * @details The files must have the following form:
     *           * Zero or one xml declaration: "<?xml attributes ?>"
     *           * Zero or one root element: "<tag attributes>Content</tag>" or "<tag attributes />"
     *           * Attributes have the form "key=value". Each element may have an arbitrary amount of attributes.
     *           * Content may consist of text and/or further elements.
     * @note This parser does not comply with xml standards. It does not have unicode support. Generally, it does not
     *       have any of the more fancy features of real xml. Its main purpose is to quickly read in structured
     *       configuration files.
     */
    class XML
    {
    public:
        /**
         * @brief Type of an xml element
         * @details "Element" has the form "<tag attributes>Content</tag>" or "<tag attributes />"
         *          "ProcInstruction" has the form "<?target attributes ?>"
         *          "Comment" has the form "<!-- Comment -->"
         */
        enum class ElementType
        {
            Element,
            ProcInstruction,
            Comment,
        };

        /**
         * @brief An attribute of an element, has the form "key=value"
         */
        class Attribute
        {
        public:
            /**
             * @brief Constructor
             * @param name Attribute name (key)
             * @param value Attribute value
             */
            Attribute(std::string const& name, std::string const& value);
            /**
             * @brief Attribute name
             */
            std::string& name();
            /**
             * @brief Attribute name
             */
            std::string const& name() const;
            /**
             * @brief Attribute value
             */
            std::string& value();
            /**
             * @brief Attribute value
             */
            std::string const& value() const;

        private:
            std::string m_name;
            std::string m_value;

            friend class XML;
        };

        /**
         * @brief An xml element.
         * @copydoc ElementType
         */
        class Element
        {
        public:
            /**
             * @brief Element tag name
             */
            std::string& name();
            /**
             * @brief Element tag name
             */
            std::string const& name() const;
            /**
             * @brief Element content
             */
            std::string& content();
            /**
             * @brief Element content
             */
            std::string const& content() const;
            /**
             * @brief Element type
             */
            ElementType& type();
            /**
             * @brief Element type
             */
            ElementType const& type() const;
            /**
             * @brief Element attributes
             */
            std::vector<Attribute>& attributes();
            /**
             * @brief Element attributes
             */
            std::vector<Attribute> const& attributes() const;
            /**
             * @brief Parent element (if any)
             */
            Element* parent() const;
            /**
             * @brief Child elements (if any)
             */
            std::vector<Element*> const& children() const;
            /**
             * @brief Create a new child element
             * @param name Tag name
             * @param type Type of element to create
             * @returns Pointer to the created element
             */
            Element* createChild(std::string const& name, ElementType type);
            /**
             * @brief Removes a child element
             * @param num Position of child in children vector.
             */
            void removeChild(unsigned int num);
        private:
            std::string m_name;
            std::string m_content;
            ElementType m_type;
            std::vector<Attribute> m_attributes;
            Element* m_pParent = nullptr;
            std::vector<Element*> m_children;

            friend class XML;
        };

        /**
         * @brief Construct by reading in a file
         * @param file File to read from
         */
        XML(std::string const& file);
        /**
         * @brief Construct by reading from any stream
         * @param in Input stream to read from
         */
        XML(std::istream& in);
        /**
         * @brief Destructor
         */
        ~XML();
        /**
         * @brief XML declaration (might be nullptr if not contained in file)
         */
        Element* declaration();
        /**
         * @brief XML declaration (might be nullptr if not contained in file)
         */
        Element const* declaration() const;
        /**
         * @brief Root node (might be nullptr if file is empty)
         */
        Element* root();
        /**
         * @brief Root node (might be nullptr if file is empty)
         */
        Element const* root() const;
        /**
         * @brief Removes any current xml declaration and creates a new one
         */
        void replaceDeclaration();
        /**
         * @brief Removes all nodes and creates an empty root node
         * @param name Tag name
         */
        void replaceRoot(std::string const& name);

    private:
        void readFromStream(std::istream& in);
        void interpret(std::stringstream& content);
        Element* tryReadElement(std::stringstream& content);
        bool tryReadAttributes(std::stringstream& content, std::vector<Attribute>& attributes);
        void tryReadContent(std::stringstream& content, Element* elem);
        static void free(Element* elem);

        Element* m_pRoot = nullptr;
        Element* m_pDeclaration = nullptr;
        void tryReadComment(std::stringstream& stringstream, Element* pElement);
    };
}

#endif //DBGL_XML_H
