#ifndef SFLMESH_H
#define SFLMESH_H

#include "SFLShaderProgram.h"
#include <string>
#include <GMath.hpp>

namespace SFL {
    struct Vertex{
        gm::vec3 Position;
        gm::vec3 Normal;
        gm::vec2 TexCoords;
    };

    enum TextureType{
        TexDiffuse,
        TexSpecular
    };

    struct Texture{
        GLuint id;
        TextureType type;
        aiString idPath;
    };
}

using namespace std;
using namespace SFL;

class SFLMesh: public QOpenGLFunctions {


public:
    vector<GLuint> indices;
    vector<Vertex> vertices;
    vector<Texture> textures;

    SFLMesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures):QOpenGLFunctions(){
        _isInitOpenGL = false;
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;
    }
    ~SFLMesh(){
        if (_isInitOpenGL){
            glDeleteBuffers(1, &_vertexArrayObj);
            glDeleteBuffers(1, &_vertexBufferObj);
            glDeleteBuffers(1, &_elementsBufferObj);
        }
    }

    void initializeOpenGLFunctions(){
        QOpenGLFunctions::initializeOpenGLFunctions();
        _isInitOpenGL = true;

        setup();
    }

    void draw(SFLShaderProgram &shaderProgram){
        map<TextureType, string> nameMap = {
            make_pair(TextureType::TexDiffuse, "diffuse"),
            make_pair(TextureType::TexSpecular,"specular")
        };

        GLuint countTexDiffuse = 0;
        GLuint countTexSpecular = 0;
        for (GLuint i = 0; i < textures.size(); ++i) {
            stringstream ss;
            TextureType type = textures[i].type;
            if (type == TextureType::TexDiffuse){
                ss << ++countTexDiffuse;
            } else if (type == TextureType::TexSpecular){
                ss << ++countTexSpecular;
            }
            string number = ss.str();

            shaderProgram.setUniform1i(("material."+ nameMap[type] + number).c_str(), i);
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
        }
        glActiveTexture(GL_TEXTURE0);

        glBindVertexArray(_vertexArrayObj);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

private:
    bool _isInitOpenGL;
    GLuint _vertexArrayObj;
    GLuint _vertexBufferObj;
    GLuint _elementsBufferObj;

    void setup(){
        glGenVertexArrays(1, &_vertexArrayObj);
        glGenBuffers(1, &_vertexBufferObj);
        glGenBuffers(1, &_elementsBufferObj);

        glBindVertexArray(_vertexArrayObj);

        glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObj);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW); // 结构体内存连续

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementsBufferObj);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
        // 顶点坐标指针
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)0);
        // 法线坐标指针
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
        // 顶点纹理坐标
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));

        glBindVertexArray(0);
    }
};

#endif // SFLMESH_H
