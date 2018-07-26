#ifndef SFLMODELLIGHT_H
#define SFLMODELLIGHT_H

#include "../common/SFLModelAbstract.h"
#include "../views/SFLViewLight.h"
#include "../renders/SFLShaderProgram.h"
#include "../renders/SFLVertexArray.h"

class SFLModelLight: public SFLModelAbstract
{
public:
    enum ShaderType {
        typeColor,
        typeLight,
        typeLightModel
    };

    SFLModelLight():SFLModelAbstract() {
        _btn->setText("光照模型");
        _view = new SFLViewLight(this);
        _vao = new SFLVertexArray();
        _programColor = new SFLShaderProgram();
        _programLight = new SFLShaderProgram();
        _programLightModel = new SFLShaderProgram();

        type = typeColor;
        isRotateLight = false;
        lightColor = glm::vec3(1.0);
        lightAmbient = glm::vec3(0.2);
        lightDiffuse = glm::vec3(0.5);
        lightSpecular = glm::vec3(1.0);

        isRotateModel = false;
        materialColor = glm::vec3(1.0, 0.5, 0.3);
        materialAmbient = glm::vec3(1.0, 0.5, 0.3);
        materialDiffuse = glm::vec3(1.0, 0.5, 0.3);
        materialSpecular = glm::vec3(0.5);
    }
    ~SFLModelLight(){

    }

    void initializeOpenGL() override {
        GLfloat vertices[] = {
                                -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
                                 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
                                 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
                                 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
                                -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
                                -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

                                -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
                                 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
                                 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
                                 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
                                -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
                                -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

                                -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
                                -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
                                -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
                                -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
                                -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
                                -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

                                 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
                                 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
                                 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
                                 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
                                 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
                                 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

                                -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
                                 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
                                 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
                                 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
                                -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
                                -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

                                -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
                                 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
                                 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
                                 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
                                -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
                                -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
                              };
        _vao->initializeOpenGLFunctions();
        _vao->create();
        _vao->bind();
        _vao->setData(vertices, 6 * 6 * 6, 36, {3,3});

        glm::mat4 projection = glm::perspective(45.0, 1.0, 0.1, 100.0);

        _programColor->initializeOpenGLFunctions();
        _programColor->loadFromPath(":/color.vsh",":/color.fsh");
        _programColor->bind();
        _programColor->setUniformMatrix4fv("projection", glm::value_ptr(projection));

        _programLight->initializeOpenGLFunctions();
        _programLight->loadFromPath(":/color.vsh",":/colorLight.fsh");
        _programLight->bind();
        _programLight->setUniformMatrix4fv("projection", glm::value_ptr(projection));

        _programLightModel->initializeOpenGLFunctions();
        _programLightModel->loadFromPath(":/lightPhone.vsh", ":/lightPhone.fsh");
        _programLightModel->bind();
        _programLightModel->setUniformMatrix4fv("projection", glm::value_ptr(projection));
    }

    void render() override {
        ++_times;
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.1, 0.1, 0.1, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderModel();

        _vao->bind();
        _vao->draw();
    }

    ShaderType type;

    bool isRotateLight;
    bool isRotateModel;
    glm::vec3 lightColor;
    glm::vec3 lightAmbient;
    glm::vec3 lightDiffuse;
    glm::vec3 lightSpecular;

    glm::vec3 materialColor;
    glm::vec3 materialAmbient;
    glm::vec3 materialDiffuse;
    glm::vec3 materialSpecular;
    float materialShininess;

protected:
    SFLVertexArray *_vao;
    SFLShaderProgram *_programColor;
    SFLShaderProgram *_programLight;
    SFLShaderProgram *_programLightModel;

    void renderColor(){

    }

    void renderLight(){

    }

    glm::vec3 renderModel(){
        _programLightModel->bind();
        qDebug() << "Program ID: "<< _programLightModel->programID();

        GLfloat radius = 2.0;
        GLfloat speed = 0.02;
        glm::vec3 lightPosition(1.0, 0.3, 2.0);
        if (isRotateLight){
            lightPosition.x += sin(_times * speed) * radius;
            lightPosition.z += cos(_times * speed) * radius;
        }
        _programLightModel->setUniform3f("light.position", lightPosition);
        _programLightModel->setUniform3f("light.ambient",lightAmbient);
        _programLightModel->setUniform3f("light.diffuse",lightDiffuse);
        _programLightModel->setUniform3f("light.specular",lightSpecular);

        _programLightModel->setUniform1f("material.shininess", materialShininess);
        _programLightModel->setUniform3f("material.ambient", materialAmbient);
        _programLightModel->setUniform3f("material.diffuse", materialDiffuse);
        _programLightModel->setUniform3f("material.specular",materialSpecular);

        _programLightModel->setUniform3f("viewPos", glm::vec3(0.0, 0.0, 3.0));

        setProgramMV(_programLightModel, speed);

        return lightPosition;
    }

    void setProgramMV(SFLShaderProgram *program, GLfloat speed){
        glm::mat4 model(1.0);
        if (isRotateModel){
            model = glm::rotate(model, _times * speed, glm::vec3(1.0f, 0.3f, 0.5f));
        }
        program->setUniformMatrix4fv("model", glm::value_ptr(model));
        program->setUniformMatrix4fv("view", glm::value_ptr(_delegateCamaera->viewMatrix()));
    }
};

#endif // SFLMODELLIGHT_H
