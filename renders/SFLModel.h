#ifndef SFLMODEL_H
#define SFLMODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <QDir>
#include <QImage>
#include <iostream>
#include <GMath.hpp>
#include "SFLMesh.h"

using namespace std;

class SFLModel: public QOpenGLFunctions
{

public:
    SFLModel():QOpenGLFunctions(){
        _isInitOpenGL = false;
    }

    void draw(SFLShaderProgram &shader){
        for(GLuint i = 0; i < _meshes.size(); ++i){
            _meshes[i].draw(shader);
        }
    }

    void initializeOpenGLFunctions(){
        QOpenGLFunctions::initializeOpenGLFunctions();
        _isInitOpenGL = true;
    }

    void loadModel(string path) {
        Assimp::Importer import;
        const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

        if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
            return;
        }
        _directory = path.substr(0, path.find_last_of(QDir::separator().toLatin1()));

        processNode(scene->mRootNode, scene);
    }

private:
    bool _isInitOpenGL;
    string _directory;
    vector<SFLMesh> _meshes;
    vector<SFL::Texture> _textureLoaded;

    void processNode(aiNode* node, const aiScene* scene) {
        // 添加当前节点中的所有Mesh
        for(GLuint i = 0; i < node->mNumMeshes; i++) {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            _meshes.push_back(processMesh(mesh, scene));
        }
        // 递归处理该节点的子孙节点
        for(GLuint i = 0; i < node->mNumChildren; i++) {
            processNode(node->mChildren[i], scene);
        }
    }

    SFLMesh processMesh(aiMesh* mesh, const aiScene* scene) {
        vector<SFL::Vertex> vertices;
        vector<GLuint> indices;
        vector<SFL::Texture> textures;

        for (int i = 0; i < mesh->mNumVertices; ++i){
            gm::vec3 position;
            position.x = mesh->mVertices[i].x;
            position.y = mesh->mVertices[i].y;
            position.z = mesh->mVertices[i].z;

            gm::vec3 normal;
            normal.x = mesh->mNormals[i].x;
            normal.y = mesh->mNormals[i].y;
            normal.z = mesh->mNormals[i].z;

            gm::vec2 texCoords(0.0f, 0.0f);
            if(mesh->mTextureCoords[0]) {
                texCoords.x = mesh->mTextureCoords[0][i].x;
                texCoords.y = mesh->mTextureCoords[0][i].y;
            }

            SFL::Vertex vertex;
            vertex.Position = position;
            vertex.Normal = normal;
            vertex.TexCoords = texCoords;

            vertices.push_back(vertex);
        }

        for(GLuint i = 0; i < mesh->mNumFaces; ++i) {
            aiFace face = mesh->mFaces[i];
            for(GLuint j = 0; j < face.mNumIndices; ++j) {
                indices.push_back(face.mIndices[j]);
            }
        }

        if (mesh->mMaterialIndex >= 0){
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
            vector<SFL::Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, SFL::TexDiffuse);
            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
            vector<SFL::Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, SFL::TexSpecular);
            textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        }

        SFLMesh sflMesh(vertices, indices, textures);
        sflMesh.initializeOpenGLFunctions();

        return sflMesh;
    }

    vector<SFL::Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType typeAssimp, SFL::TextureType type) {
        vector<SFL::Texture> textures;
        for(GLuint i = 0; i < mat->GetTextureCount(typeAssimp); ++i) {
            aiString str;
            mat->GetTexture(typeAssimp, i, &str);
            GLboolean isSkip = false;
            for (GLuint j = 0; j < _textureLoaded.size(); ++j){
                if (_textureLoaded[j].idPath == str) {
                    textures.push_back(_textureLoaded[j]);
                    isSkip = true;
                    break;
                }
            }
            if (!isSkip){
                SFL::Texture texture;
                texture.id = TextureFromFile(QDir::toNativeSeparators((_directory + "/" + string(str.C_Str())).c_str()).toStdString().c_str());
                texture.idPath = str;
                texture.type = type;
                textures.push_back(texture);
                _textureLoaded.push_back(texture);
            }
        }

        return textures;
    }

    GLuint TextureFromFile(const char *path){
        if (!_isInitOpenGL) return 0;

        QImage qImage(path);

        unsigned int textureID;
        glGenTextures(1, &textureID);

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, qImage.width(), qImage.height(), 0, GL_BGRA, GL_UNSIGNED_BYTE, qImage.bits());
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        return textureID;
    }
};

#endif // SFLMODEL_H
