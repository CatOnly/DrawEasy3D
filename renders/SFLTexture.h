#ifndef SFLTEXTURE_H
#define SFLTEXTURE_H
#include <QOpenGLFunctions>
#include <iostream>
#include <QImage>

class SFLTexture : public QOpenGLFunctions
{
public:
    SFLTexture(bool isUseMipMap = false):QOpenGLFunctions() {
        _isUseMipMap = isUseMipMap;
    }
    ~SFLTexture() {
        if (!_isInitialized || !_isCreateBySelf || !_texRef) return;

        glDeleteTextures(1, &_texRef);
    }
    void initializeOpenGLFunctions(){
        _isInitialized = true;
        QOpenGLFunctions::initializeOpenGLFunctions();
    }

    void creat(GLuint texID){
        _isCreateBySelf = true;

        glGenTextures(1, &_texRef);
        _texID = texID;
    }
    void setRef(GLuint ref, GLuint texID){
        _isCreateBySelf = false;

        _texRef = ref;
        _texID = texID;
    }

    void active(){
        if (!_texRef) return;

        glActiveTexture(_texID);
    }

    void bind(GLenum target = GL_TEXTURE_2D){
        if (!_texRef) return;

        glBindTexture(target, _texRef);
    }

    void unBind(){
        if (!_texRef) return;

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void setWrap(GLint s = GL_CLAMP_TO_EDGE, GLint t = GL_CLAMP_TO_EDGE){
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t);
    }

    void setFilter(GLint min = GL_NEAREST, GLint max = GL_LINEAR){
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, max);
    }
    void setFilterMipMap(GLint min = GL_LINEAR_MIPMAP_NEAREST, GLint max = GL_LINEAR_MIPMAP_LINEAR){
        // 采用多级渐远纹理，的过滤方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, max);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    void loadTexture2DFromPath(const char * imgPath, GLint format = GL_RGBA, GLint warp = GL_CLAMP_TO_EDGE){
        QImage qImage(imgPath);

        bind();
        glTexImage2D(GL_TEXTURE_2D, 0, format, qImage.width(), qImage.height(), 0, GL_BGRA, GL_UNSIGNED_BYTE, qImage.bits());

        // 设定当前纹理，开始设置纹理属性
        // 纹理环绕方式
        setWrap(warp, warp);
        // 纹理过滤方式
        if (_isUseMipMap){
            setFilterMipMap();
        } else {
            setFilter();
        }
        unBind();
    }

    void loadCubeMap(std::vector<std::string> &faces, GLint format = GL_RGBA) {
        bind(GL_TEXTURE_CUBE_MAP);

        for (unsigned int i = 0; i < faces.size(); i++)
        {
            QImage qImage(faces[i].c_str());
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, qImage.width(), qImage.height(), 0, GL_BGRA, GL_UNSIGNED_BYTE, qImage.bits());
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        unBind();
    }

    void loadDepthMap(unsigned int fbo, unsigned int width, unsigned int height) {
        bind();

        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _texRef, 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

private:
    bool _isUseMipMap;
    bool _isInitialized = false;
    bool _isCreateBySelf = false;
    GLuint _texRef = 0;
    GLuint _texID = 0;
};
#endif // SFLTEXTURE_H
