#ifndef SFLMODELPOSTPROCESSING_H
#define SFLMODELPOSTPROCESSING_H

#include "../common/SFLModelAbstract.h"
#include "../views/SFLViewPostprocessing.h"
#include "../renders/SFLShaderProgram.h"
#include "../renders/SFLVertexArray.h"
#include "../renders/SFLTexture.h"
#include "../library/sfl/SFLPostProcessing.h"

class SFLModelPostprocessing: public SFLModelAbstract
{
public:
    enum ProcessType{
        TypeNoProcess,
        TypeEdge,
        TypeFaceBeautify,
        TypeCartoon,
        TypeSizeTAG
    };

    ProcessType type;
    GLfloat radius;
    GLfloat param;

    SFLModelPostprocessing():SFLModelAbstract(){
        _btn->setText("后处理图像");
        _view = new SFLViewPostprocessing(this);
        _vao = new SFLVertexArray();
        _texImage = new SFLTexture();
        _postProcessing = new SFLPostProcessing();

        for(int i = 0; i < static_cast<int>(ProcessType::TypeSizeTAG); ++i){
            _programs.push_back(new SFLShaderProgram());
        }

        type = TypeNoProcess;
        radius = 1.0;
        param = 5.0;
    }

    ~SFLModelPostprocessing(){
        if (_hasInitialized){

        }
        _programs.clear();
        DELETE_SAFE(_vao)
        DELETE_SAFE(_texImage)
        DELETE_SAFE(_postProcessing)
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

        SFLShaderProgram *program = _programs[static_cast<int>(TypeNoProcess)];
        program->initializeOpenGLFunctions();
        program->loadFromStr(
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
        program->bind();
        program->setUniform1i("material", 0);

        program = _programs[static_cast<int>(TypeEdge)];
        program->initializeOpenGLFunctions();
        program->loadFromPath(":/processEdge.vsh",":/processEdge.fsh");
        program->bind();
        program->setUniform1i("material", 0);

        program = _programs[static_cast<int>(TypeCartoon)];
        program->initializeOpenGLFunctions();
        program->loadFromPath(":/cartoon.vsh",":/cartoon.fsh");
        program->bind();
        program->setUniform1i("material", 0);

        _postProcessing->initializeOpenGLFunctions();
    }

    void render() override {
        glClearColor(0.984f, 0.306f, 0.56f, 1.0f);

        GLfloat width = 700.0f;
        GLfloat height = 700.0f;
        GLfloat stepX = 1.0f / 700.0f;
        GLfloat stepY = 1.0f / (height / width * 700.0f);

        _texImage->active();
        _texImage->bind();

        switch(type){
        case TypeNoProcess:
            _programs[static_cast<int>(type)]->bind();
            break;
        case TypeEdge:{
            SFLShaderProgram *program = _programs[static_cast<int>(type)];
            program->bind();
            program->setUniform2f("offsetSteps", stepX * radius, stepY * radius);
            break;
        }
        case TypeFaceBeautify:
            _postProcessing->setParams(SFLPostProcessing::typeFaceBeautify, param, stepX * radius, stepY * radius);
            break;
        case TypeCartoon:{
            SFLShaderProgram *program = _programs[static_cast<int>(type)];
            program->bind();
            program->setUniform1f("radio", param);
            program->setUniform2f("offsetSteps", stepX * radius, stepY * radius);
            break;
        }
        default:
            _programs[static_cast<int>(TypeNoProcess)]->bind();
        }

        _vao->bind();
        _vao->draw();
    }

private:
    SFLVertexArray *_vao;
    SFLTexture *_texImage;

    std::vector<SFLShaderProgram *> _programs;
    SFLPostProcessing *_postProcessing;
};

#endif // SFLMODELPOSTPROCESSING_H
