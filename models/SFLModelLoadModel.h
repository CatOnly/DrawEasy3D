#ifndef SFLMODELLOADMODEL_H
#define SFLMODELLOADMODEL_H

#include "../common/SFLModelAbstract.h"
#include "../views/SFLViewLoadModel.h"
#include "../renders/SFLShaderProgram.h"
#include "../renders/SFLModel.h"

class SFLModelLoadModel: public SFLModelAbstract
{
public:
    SFLModelLoadModel():SFLModelAbstract(){
        _btn->setText("模型加载");
        _view = new SFLViewLoadModel(this);
        _program = new SFLShaderProgram();
        _model = new SFLModel();
        _isLoadModel = false;
    }
    ~SFLModelLoadModel(){
        DELETE_SAFE(_program)
        DELETE_SAFE(_model)
    }

    void initializeOpenGL() override {
        _program->initializeOpenGLFunctions();
        _program->loadFromStr("\
                      #version 330 core\
                      layout (location = 0) in vec3 aPos;\
                      layout (location = 1) in vec3 aNormal;\
                      layout (location = 2) in vec2 aTexCoords;\
                      out vec2 TexCoord;\
                      out vec3 Normal;\
                      out vec4 WorldPos;\
                      \
                      uniform mat4 model;\
                      uniform mat4 view;\
                      uniform mat4 projection;\
                      void main() {\
                          TexCoord = aTexCoords;\
                          Normal = mat3(transpose(inverse(model))) * aNormal;\
                          WorldPos = model * vec4(aPos, 1.0f);\
                          gl_Position = projection * view * WorldPos;\
                      }",
                      "#version 330 core\
                      in vec2 TexCoord;\
                      in vec3 Normal;\
                      in vec4 WorldPos;\
                      out vec4 color;\
                      struct Material {\
                          sampler2D diffuse1; \
                          sampler2D specular1;\
                      };\
                      uniform Material material;\
                      uniform vec3 lightPosition;\
                      uniform vec3 viewPos;\
                      void main() {\
                          vec3 norm = normalize(Normal);\
                          vec3 lightDir = normalize(lightPosition - WorldPos.xyz);\
                          float diff = max(dot(norm, lightDir), 0.0);\
                          vec3 viewDir = normalize(viewPos - WorldPos.xyz);\
                          vec3 reflectDir = reflect(-lightDir, norm);\
                          float spec = pow( max( dot(viewDir, reflectDir), 0.0 ), 32.0 );\
                          vec3 diffuseColor = texture(material.diffuse1, TexCoord).rgb;\
                          vec3 ambient =  0.2  * diffuseColor; \
                          vec3 diffuse =  0.5  * diff * diffuseColor;\
                          vec3 specular = spec * texture(material.specular1, TexCoord).rgb;\
                          color = vec4(ambient + diffuse + specular, 1.0);\
                      }"
                  );
        _program->bind();
        _program->setUniform3f("lightPosition", gm::vec3(1.0f, 0.3f, 2.0f));
        _program->setUniformMatrix4fv("projection", gm::valuePtrFrom(gm::perspective(45.0f, 1.0f, 0.1f, 100.0f)));
        gm::mat4 model(1.0);
        model = gm::translate(model, gm::vec3(0.0f, -1.75f, 0.0f));
        model = gm::scale(model, gm::vec3(0.2f, 0.2f, 0.2f));
        _program->setUniformMatrix4fv("model", gm::valuePtrFrom(model));

        _model->initializeOpenGLFunctions();
    }

    void render() override {
        glClearColor(0.3, 0.3, 0.3, 1.0f);
        if (!_isLoadModel) return;

        glEnable(GL_DEPTH_TEST);
        glClearColor(0.1, 0.1, 0.1, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        _program->bind();
        _program->setUniform3f("viewPos", _delegateCamaera->position);
        _program->setUniformMatrix4fv("view", gm::valuePtrFrom(_delegateCamaera->viewMatrix()));

        _model->draw(*_program);
    }

    bool loadModel(const char *path){
        _isLoadModel = false;
        _model->loadModel(path);
        _isLoadModel = true;

        return _isLoadModel;
    }

private:
    bool _isLoadModel;
    SFLModel *_model;
    SFLShaderProgram *_program;
};
#endif // SFLMODELLOADMODEL_H
