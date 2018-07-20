#ifndef SFLMODELLIGHT_H
#define SFLMODELLIGHT_H

#include "../common/SFLModelAbstract.h"
#include "../views/SFLViewLight.h"
#include <QImage>

#define SIZE_VAO 5
#define SIZE_VBO 5
#define SIZE_EBO 5
#define SIZE_TEX 5

class SFLModelLight: public SFLModelAbstract
{
public:
    SFLModelLight():SFLModelAbstract() {
        _view = new SFLViewLight();
        _btn->setText("有光照");

        // 在 GPU 开辟缓存空间
//        glGenVertexArrays(SIZE_VAO, _vertexArrayObjects);
//        glGenBuffers(SIZE_VBO, _vertexBufferObjects);
//        glGenBuffers(SIZE_EBO, _elementBufferObjects);
//        glGenTextures(SIZE_TEX, _textures);
    }
    ~SFLModelLight(){
//        glDeleteVertexArrays(SIZE_VAO, _vertexArrayObjects);
//        glDeleteBuffers(SIZE_VBO, _vertexBufferObjects);
//        glDeleteBuffers(SIZE_EBO, _elementBufferObjects);
//        glDeleteTextures(SIZE_TEX, _textures);
    }

    void render(){

    }

protected:
//    GLuint _vertexArrayObjects[SIZE_VAO];
//    GLuint _vertexBufferObjects[SIZE_VBO];
//    GLuint _elementBufferObjects[SIZE_EBO];
//    GLuint _textures[SIZE_TEX];
    uint _texID = 0;

    uint addTexture(QString texPath) {
        QImage qImage(texPath);
        int width = qImage.width();
        int height = qImage.height();

        // 设定当前纹理，开始设置纹理属性
        uint textureID;
        uint currentTexID = 0;//_textures[_texID];
//        switch (_texID) {
//            case 0: textureID = GL_TEXTURE0; break;
//            case 1: textureID = GL_TEXTURE1; break;
//            case 2: textureID = GL_TEXTURE2; break;
//            case 3: textureID = GL_TEXTURE3; break;
//            case 4: textureID = GL_TEXTURE4; break;
//            case 5: textureID = GL_TEXTURE5; break;
//        }
//        glActiveTexture(textureID);
//        glBindTexture(GL_TEXTURE_2D, currentTexID);
//        ++_texID;

//        // 纹理环绕方式
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//        // 纹理过滤方式(普通过滤算法)
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, qImage.bits());

        return currentTexID;
    }

    uint addTextureUseMipmap(QString texPath){
        uint texID = addTexture(texPath);
        // 纹理过滤方式(多级渐远纹理压缩)
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

//        glGenerateMipmap(GL_TEXTURE_2D);

        return texID;
    }
};

#endif // SFLMODELLIGHT_H
