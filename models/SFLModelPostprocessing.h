#ifndef SFLMODELPOSTPROCESSING_H
#define SFLMODELPOSTPROCESSING_H

#include "../common/SFLModelAbstract.h"
#include "../views/SFLViewPostprocessing.h"
#include "../renders/SFLShaderProgram.h"
#include "../renders/SFLVertexArray.h"
#include "../renders/SFLTexture.h"
#include "../library/sfl/FaceBeautify.h"

class SFLModelPostprocessing: public SFLModelAbstract
{
public:
    enum ProcessType{
        TypeNoProcess,
        TypeEdge,
        TypeFaceBeautify
    };

    ProcessType type;
    GLfloat radius;
    GLfloat param;

    SFLModelPostprocessing():SFLModelAbstract(){
        _btn->setText("后处理图像");
        _view = new SFLViewPostprocessing(this);
        _vao = new SFLVertexArray();
        _texImage = new SFLTexture();
        _programFaceBeautify = new FaceBeautify();
        _programOrigin = new SFLShaderProgram();
        _programEdge = new SFLShaderProgram();

        type = TypeNoProcess;
        radius = 1.0;
        param = 5.0;
    }

    ~SFLModelPostprocessing(){
        if (_hasInitialized){

        }
        DELETE_SAFE(_vao)
        DELETE_SAFE(_texImage)
        DELETE_SAFE(_programOrigin)
        DELETE_SAFE(_programEdge)
        DELETE_SAFE(_programFaceBeautify)
    }

    void initializeOpenGL() override {
        // b c
        // a d
        GLfloat vertices[] = {
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // a
            -1.0f,  1.0f, 0.0f, 0.0f, 1.0f, // b
             1.0f,  1.0f, 0.0f, 1.0f, 1.0f, // c
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // a
             1.0f,  1.0f, 0.0f, 1.0f, 1.0f, // c
             1.0f, -1.0f, 0.0f, 1.0f, 0.0f  // d
        };
        _vao->initializeOpenGLFunctions();
        _vao->create();
        _vao->bind();
        _vao->setData(vertices, 5 * 6, 6, {3, 2});

        _texImage->initializeOpenGLFunctions();
        _texImage->creat(GL_TEXTURE0);
        _texImage->loadTexture2DFromPath(":/woman.png");
        _texImage->bind();

        _programOrigin->initializeOpenGLFunctions();
        _programOrigin->loadFromStr(
                    "#version 330 core\
                    layout (location = 0) in vec3 position;\
                    layout (location = 1) in vec2 texCoord;\
                    out vec2 TexCoord;\
                    void main(){\
                        gl_Position = vec4(position, 1.0);\
                        TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);\n\
                    }",
                    "#version 330 core\
                    in vec2 TexCoord;\
                    out vec4 color;\
                    uniform sampler2D material;\
                    void main() {\
                        color = texture(material, TexCoord);\
                    }"
                    );
        _programOrigin->bind();
        _programOrigin->setUniform1i("material", 0);

        _programEdge->initializeOpenGLFunctions();
        _programEdge->loadFromPath(":/processEdge.vsh",":/processEdge.fsh");
        _programEdge->bind();
        _programEdge->setUniform1i("material", 0);

        _programFaceBeautify->initializeOpenGLFunctions();
    }

    void render() override {
        glClearColor(0.984f, 0.306f, 0.56f, 1.0f);

        GLfloat width = 700.0f;
        GLfloat height = 700.0f;
        GLfloat stepX = 1.0f / 700.0f;
        GLfloat stepY = 1.0f / (height / width * 700.0f);

        _texImage->active();
        _texImage->bind();

        _programOrigin->unBind();

        switch(type){
        case TypeNoProcess:
            _programOrigin->bind();
            break;
        case TypeEdge:
            _programEdge->bind();
            _programEdge->setUniform2f("offsetSteps", stepX * radius, stepY * radius);
            break;
        case TypeFaceBeautify:
            _programFaceBeautify->setParams(param, stepX * radius, stepY * radius);
            break;
        }

        _vao->bind();
        _vao->draw();
    }

private:
    SFLVertexArray *_vao;
    SFLTexture *_texImage;
    SFLShaderProgram *_programOrigin;
    SFLShaderProgram *_programEdge;
    FaceBeautify *_programFaceBeautify;
};

#endif // SFLMODELPOSTPROCESSING_H
