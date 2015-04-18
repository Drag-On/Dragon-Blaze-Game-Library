//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include <cstring>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>

#include "DBGL/Resources/Mesh/IMeshFormatLibrary.h"
#include "DBGL/Core/Math/Vector3.h"
#include "DBGL/Core/Math/Vector2.h"
#include "DBGL/Core/Math/Utility.h"
#include "DBGL/Platform/Platform.h"

namespace dbgl
{
    /**
     * @brief Loads mesh files in obj format
     */
    class OBJModule : public IMeshFormatLibrary
    {
    private:
        /**
         * @brief Every OBJ face consists of three vertices having a position and (possibly)
         * 	      a UV and/or normal.
         */
        struct FaceComponent
        {
        public:
            /**
             * @brief Index of the vertex (coordinate)
             */
            unsigned short vertexIndex = std::numeric_limits<unsigned short>::max();
            /**
             * @brief Index of the UV
             */
            unsigned short uvIndex = std::numeric_limits<unsigned short>::max();
            /**
             * @brief Index of the normal
             */
            unsigned short normalIndex = std::numeric_limits<unsigned short>::max();
        };
        /**
         * @brief One face (i.e. polygon)
         */
        struct Face
        {
        public:
            /**
             * @brief Components of a face. Currently only polygons with 3 vertices are allowed.
             */
            FaceComponent components[3]{};
        };

        template<typename T>
        T to(std::string const& val) const
        {
            std::istringstream lineStream{};
            lineStream.str(val);
            T ret = 0;
            lineStream >> ret;
            return ret;
        }

        /**
         * @brief Extracts data a string
         * @param line String to tokenize
         * @param[out] first First token as string
         * @param[out] container Other tokens as T
         */
        template<typename T>
        void extract(std::string const& line, std::string& first, std::vector<T>& container) const
        {
            std::istringstream lineStream{};
            lineStream.str(line);
            lineStream >> first;
            T curCoord{};
            while (lineStream >> curCoord)
                container.push_back(curCoord);
        }

        /**
         * @brief Tokenizes a string
         * @param line Line to tokenize
         * @param delim Delimiter
         * @param container Container to append tokens to
         */
        void tokenize(std::string const& line, char delim, std::vector<std::string>& container) const
        {
            std::string curElement{};
            std::stringstream tokenStream{};
            tokenStream.str(line);
            while (std::getline(tokenStream, curElement, delim))
            {
                if (curElement.empty())
                    continue;
                container.push_back(curElement);
            }
        }

        /**
         * @brief Merges the raw data into a single index
         * @param[out] mesh Mesh to store to
         * @param faces Original faces
         * @param vertices Original vertices
         * @param normals Original normals
         * @param uvs Original uvs
         */
        void interpret(IMesh* mesh, std::vector<Face> const& faces, std::vector<Vec3f> const& vertices,
                       std::vector<Vec3f> const& normals, std::vector<Vec2f> const& uvs) const
        {
            // Iterate over all faces
            for (unsigned int i = 0; i < faces.size(); i++)
            {
                auto curFace = faces[i];
                // Iterate over all 3 vertices in a face
                for (unsigned int j = 0; j < 3; j++)
                {
                    Vec3f vertex, normal;
                    Vec2f uv;
                    // Get vertex
                    if (vertices.size() > curFace.components[j].vertexIndex)
                        vertex = vertices[curFace.components[j].vertexIndex];
                    else
                    {
                        // This should never happen TODO: Error handling
                        return;
                    }
                    // Get UV
                    bool useUv = true;
                    if (uvs.size() > curFace.components[j].uvIndex)
                        uv = uvs[curFace.components[j].uvIndex];
                    else
                        useUv = false;
                    // Get normal
                    bool useNormal = true;
                    if (normals.size() > curFace.components[j].normalIndex)
                        normal = normals[curFace.components[j].normalIndex];
                    else
                        useNormal = false;
                    // Add new vertex, normal and uv.
                    auto vertIndex = mesh->vertices().size();
                    mesh->vertices().push_back(vertex);
                    if (useUv)
                        mesh->uvs().push_back(uv);
                    if (useNormal)
                        mesh->normals().push_back(normal);
                    // Add the index
                    mesh->indices().push_back(vertIndex);
                }
            }
        }

        /**
         * @brief Analyzes the obj code
         * @param contents
         * @return
         */
        IMesh* analyze(std::string const& contents) const
        {
            std::vector<Face> origFaces{};
            std::vector<Vec3f> origVertices{};
            std::vector<Vec3f> origNormals{};
            std::vector<Vec2f> origUvs{};
            std::istringstream lineStream{};
            lineStream.str(contents);
            std::string line{};
            std::string type{};
            std::vector<std::string> params;
            while (std::getline(lineStream, line))
            {
                if (line.length() == 0) // Skip empty lines
                    continue;
                params.clear();
                type.clear();
                extract(line, type, params);
                if (type == "v") // Vertex
                {
                    if (params.size() < 3)
                        return nullptr; // TODO: Better handling of misformatted files
                    if (params.size() > 3)
                        return nullptr;
                    origVertices.push_back({to<float>(params[0]), to<float>(params[1]), to<float>(params[2])});
                }
                else if (type == "vt") // UV
                {
                    if (params.size() < 2)
                        return nullptr;
                    if (params.size() > 3) // There may be a w coordinate (ignored here)
                        return nullptr;
                    origUvs.push_back({to<float>(params[0]), to<float>(params[1])});
                }
                else if (type == "vn") // Normal
                {
                    if (params.size() < 3)
                        return nullptr;
                    if (params.size() > 3)
                        return nullptr;
                    origNormals.push_back({to<float>(params[0]), to<float>(params[1]), to<float>(params[2])});
                }
                else if (type == "f") // Face
                {
                    Face curFace{};
                    for (unsigned int i = 0; i < params.size(); i++)
                    {
                        FaceComponent curFaceComponent{};
                        std::vector<std::string> tokens{};
                        tokenize(params[i], '/', tokens);
                        for (unsigned int j = 0; j < tokens.size(); j++)
                        {
                            unsigned int curIndex = to<unsigned int>(tokens[j]);
                            switch (j)
                            {
                                case 0:
                                    curFaceComponent.vertexIndex = curIndex - 1; // OBJ indices start with 1
                                    break;
                                case 1:
                                    curFaceComponent.uvIndex = curIndex - 1;
                                    break;
                                case 2:
                                    curFaceComponent.normalIndex = curIndex - 1;
                                    break;
                                default:
                                    // TODO: Issue warning
                                    break;
                            }
                        }
                        curFace.components[i] = curFaceComponent;
                    }
                    origFaces.push_back(curFace);
                }
                else
                    // Might be a comment or some other line we can skip
                    continue;
            }
            if (lineStream.bad())
            {
                // TODO: Error handling
                return nullptr;
            }
            // Create mesh
            auto mesh = Platform::get()->createMesh();
            interpret(mesh, origFaces, origVertices, origNormals, origUvs);
            return mesh;
        }

    public:
        /**
         * @brief Destructor
         */
        virtual ~OBJModule() = default;

        /**
         * @copydoc IMeshFormatLibrary::canLoad()
         */
        virtual bool canLoad() const
        {
            return true;
        }

        /**
         * @copydoc IMeshFormatLibrary::canWrite()
         */
        virtual bool canWrite() const
        {
            return false;
        }

        /**
         * @copydoc IMeshFormatLibrary::matchExtension()
         */
        virtual bool matchExtension(std::string const& extension) const
        {
            std::string lowercaseExt{};
            std::transform(extension.begin(), extension.end(), std::back_inserter(lowercaseExt), ::tolower);
            return lowercaseExt == ".obj" || lowercaseExt == "obj";
        }

        /**
         * @copydoc IMeshFormatLibrary::load()
         */
        virtual IMesh* load(std::string const& path) const
        {
            return load(Filename{path});
        }

        /**
         * @copydoc IMeshFormatLibrary::load()
         */
        virtual IMesh* load(Filename const& path) const
        {
            // Read file
            std::ifstream file;
            file.open(path.get().c_str(), std::ios::in);
            std::string contents;
            if (file.is_open())
            {
                file.seekg(0, std::ios::end);
                unsigned int size = file.tellg();
                contents.resize(size);
                file.seekg(0, std::ios::beg);
//		    file.read(&contents[0], size);

                char buffer[4096];
                while (file.read(buffer, sizeof(buffer)))
                    contents.append(buffer, sizeof(buffer));
                contents.append(buffer, file.gcount());
            }
            // Close file
            file.close();

            // Analyze contents
            auto mesh = analyze(contents);

            return mesh;
        }

        /**
         * @copydoc IMeshFormatLibrary::write()
         */
        virtual bool write(IMesh* data, std::string const& path) const
        {
            return write(data, Filename{path});
        }

        /**
         * @copydoc IMeshFormatLibrary::write()
         */
        virtual bool write(IMesh* /* data */, Filename const& /* path */) const
        {
            return false;
        }
    };
}

/**
 * @brief Create obj loader object
 */
extern "C" dbgl::IMeshFormatLibrary* create()
{
    return new dbgl::OBJModule{};
}

/**
 * @brief Destroy obj loader object
 */
extern "C" void destroy(dbgl::IMeshFormatLibrary* mod)
{
    delete mod;
}
