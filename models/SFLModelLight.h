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
        typeModelGouraud,
        typeModelPhone
    };

    SFLModelLight():SFLModelAbstract() {
        _btn->setText("光照模型");
        _view = new SFLViewLight(this);
        _vao = new SFLVertexArray();
        _programColor = new SFLShaderProgram();
        _programLight = new SFLShaderProgram();
        _programModelGouraud = new SFLShaderProgram();
        _programModelPhone = new SFLShaderProgram();

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

        glm::mat3 m;
        printf("mat3: %.1f %.1f %.1f\n", m[0][0], m[1][1], m[2][2]);
    }

    ~SFLModelLight() {
        DELETE_SAFE(_vao)
        DELETE_SAFE(_programColor)
        DELETE_SAFE(_programLight)
        DELETE_SAFE(_programModelGouraud)
        DELETE_SAFE(_programModelPhone)
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

        _programModelGouraud->initializeOpenGLFunctions();
        _programModelGouraud->loadFromPath(":/lightGouraud.vsh",":/lightGouraud.fsh");
        _programModelGouraud->bind();
        _programModelGouraud->setUniformMatrix4fv("projection", glm::value_ptr(projection));

        _programModelPhone->initializeOpenGLFunctions();
        _programModelPhone->loadFromPath(":/lightPhong.vsh", ":/lightPhong.fsh");
        _programModelPhone->bind();
        _programModelPhone->setUniformMatrix4fv("projection", glm::value_ptr(projection));
    }

    void render() override {
        ++_times;
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.1, 0.1, 0.1, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::vec3 lightPosition(1.0, 0.3, 2.0);

        switch(type){
        case typeColor:
            renderColor();
            break;
        case typeLight:
            renderLight();
            break;
        case typeModelGouraud:
            renderModel(_programModelGouraud, lightPosition);
            break;
        case typeModelPhone:
            renderModel(_programModelPhone, lightPosition);
            break;
        }

        _programColor->bind();
        glm::mat4 model = glm::translate(glm::mat4(1.0f), lightPosition);
        model = glm::scale(model, glm::vec3(0.2f));
        _programColor->setUniform3f("materialColor", lightColor);
        _programColor->setUniformMatrix4fv("model", glm::value_ptr(model));
        _programColor->setUniformMatrix4fv("view", glm::value_ptr(_delegateCamaera->viewMatrix()));

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
    SFLShaderProgram *_programModelGouraud;
    SFLShaderProgram *_programModelPhone;

    void renderColor(){
        _programColor->bind();
        _programColor->setUniform3f("materialColor", materialColor);

        glm::mat4 model(1.0);
        _programColor->setUniformMatrix4fv("model", glm::value_ptr(model));
        _programColor->setUniformMatrix4fv("view", glm::value_ptr(_delegateCamaera->viewMatrix()));

        _vao->bind();
        _vao->draw();
    }
    void renderLight(){
        _programLight->bind();
        _programLight->setUniform3f("lightColor", lightColor);
        _programLight->setUniform3f("materialColor", materialColor);

        glm::mat4 model(1.0);
        _programLight->setUniformMatrix4fv("model", glm::value_ptr(model));
        _programLight->setUniformMatrix4fv("view", glm::value_ptr(_delegateCamaera->viewMatrix()));

        _vao->bind();
        _vao->draw();
    }
    void renderModel(SFLShaderProgram *program, glm::vec3 &lightPosition){
        program->bind();

        GLfloat radius = 2.0;
        GLfloat speed = 0.02;
        if (isRotateLight){
            lightPosition.x += sin(_times * speed) * radius;
            lightPosition.z += cos(_times * speed) * radius;
        }
        program->setUniform3f("light.position", lightPosition);
        program->setUniform3f("light.ambient",lightAmbient);
        program->setUniform3f("light.diffuse",lightDiffuse);
        program->setUniform3f("light.specular",lightSpecular);

        program->setUniform1f("material.shininess", materialShininess);
        program->setUniform3f("material.ambient", materialAmbient);
        program->setUniform3f("material.diffuse", materialDiffuse);
        program->setUniform3f("material.specular",materialSpecular);

        program->setUniform3f("viewPos", _delegateCamaera->position);

        glm::mat4 model(1.0);
        if (isRotateModel){
            model = glm::rotate(model, _times * speed, glm::vec3(1.0f, 0.3f, 0.5f));
        }
        program->setUniformMatrix4fv("model", glm::value_ptr(model));
        program->setUniformMatrix4fv("view", glm::value_ptr(_delegateCamaera->viewMatrix()));

        _vao->bind();
        _vao->draw();
    }
};

#endif // SFLMODELLIGHT_H
