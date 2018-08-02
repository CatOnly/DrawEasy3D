#ifndef SFLMODEL_H
#define SFLMODEL_H

#include <Importer.hpp>
#include <scene.h>
#include <postprocess.h>
#include "SFLMesh.h"

class SFLModel {
    using namespace std;

public:
    SFLModel(GLchar *path){
        loadModel(path);
    }

    void draw(SFLShaderProgram &shader){
        for(GLuint i = 0; i < _meshes.size(); ++i){
            _meshes[i].draw(shader);
        }
    }

private:
    vector<SFLMesh> _meshes;
    string _directory;

    void loadModel(string path) {
        Assimp::Importer import;
        const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

        if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
            return;
        }
        _directory = path.substr(0, path.find_last_of('/'));

        processNode(scene->mRootNode, scene);
    }

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

    }

    vector<SFL::Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName) {

    }
};

#endif // SFLMODEL_H
