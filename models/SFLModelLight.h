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
        typeModelPhone,
        typeModelBlinnPhone
    };

    SFLModelLight():SFLModelAbstract() {
        _btn->setText("光照模型");
        _view = new SFLViewLight(this);
        _vao = new SFLVertexArray();
        _programColor = new SFLShaderProgram();
        _programLight = new SFLShaderProgram();
        _programModelGouraud = new SFLShaderProgram();
        _programModelPhone = new SFLShaderProgram();
        _programModelPhoneBlinn = new SFLShaderProgram();

        type = typeColor;
        isRotateLight = false;
        lightColor = gm::vec3(1.0);
        lightAmbient = gm::vec3(0.2);
        lightDiffuse = gm::vec3(0.5);
        lightSpecular = gm::vec3(1.0);

        isRotateModel = false;
        materialColor = gm::vec3(1.0, 0.5, 0.3);
        materialAmbient = gm::vec3(1.0, 0.5, 0.3);
        materialDiffuse = gm::vec3(1.0, 0.5, 0.3);
        materialSpecular = gm::vec3(0.5);

        gm::mat3 m;
        printf("mat3: %.1f %.1f %.1f\n", m[0][0], m[1][1], m[2][2]);
    }

    ~SFLModelLight() {
        DELETE_SAFE(_vao)
        DELETE_SAFE(_programColor)
        DELETE_SAFE(_programLight)
        DELETE_SAFE(_programModelGouraud)
        DELETE_SAFE(_programModelPhone)
        DELETE_SAFE(_programModelPhoneBlinn)
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

        gm::mat4 projection = gm::perspective(45.0f, 1.0f, 0.1f, 100.0f);

        _programColor->initializeOpenGLFunctions();
        _programColor->loadFromPath(":/color.vsh",":/color.fsh");
        _programColor->bind();
        _programColor->setUniformMatrix4fv("projection", gm::valuePtrFrom(projection));

        _programLight->initializeOpenGLFunctions();
        _programLight->loadFromPath(":/color.vsh",":/colorLight.fsh");
        _programLight->bind();
        _programLight->setUniformMatrix4fv("projection", gm::valuePtrFrom(projection));

        _programModelGouraud->initializeOpenGLFunctions();
        _programModelGouraud->loadFromPath(":/lightGouraud.vsh",":/lightGouraud.fsh");
        _programModelGouraud->bind();
        _programModelGouraud->setUniformMatrix4fv("projection", gm::valuePtrFrom(projection));

        _programModelPhone->initializeOpenGLFunctions();
        _programModelPhone->loadFromPath(":/lightPhong.vsh", ":/lightPhong.fsh");
        _programModelPhone->bind();
        _programModelPhone->setUniformMatrix4fv("projection", gm::valuePtrFrom(projection));

        _programModelPhoneBlinn->initializeOpenGLFunctions();
        _programModelPhoneBlinn->loadFromPath(":/lightPhong.vsh", ":/lightPhongBlinn.fsh");
        _programModelPhoneBlinn->bind();
        _programModelPhoneBlinn->setUniformMatrix4fv("projection", gm::valuePtrFrom(projection));
    }

    void render(int viewPortW, int viewPortH) override {
        ++_times;
//        glEnable(GL_MULTISAMPLE);
        glDisable(GL_MULTISAMPLE);
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.1, 0.1, 0.1, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        gm::vec3 lightPosition(1.0, 0.3, 2.0);

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
        case typeModelBlinnPhone:
            renderModel(_programModelPhoneBlinn, lightPosition);
            break;
        }

        _programColor->bind();
        gm::mat4 model = gm::translate(gm::mat4(1.0f), lightPosition);
        model = gm::scale(model, gm::vec3(0.2f));
        _programColor->setUniform3f("materialColor", lightColor);
        _programColor->setUniformMatrix4fv("model", gm::valuePtrFrom(model));
        _programColor->setUniformMatrix4fv("view", gm::valuePtrFrom(_delegateCamaera->viewMatrix()));

        _vao->bind();
        _vao->draw();
    }

    ShaderType type;

    bool isRotateLight;
    bool isRotateModel;
    gm::vec3 lightColor;
    gm::vec3 lightAmbient;
    gm::vec3 lightDiffuse;
    gm::vec3 lightSpecular;

    gm::vec3 materialColor;
    gm::vec3 materialAmbient;
    gm::vec3 materialDiffuse;
    gm::vec3 materialSpecular;
    float materialShininess;

protected:
    SFLVertexArray *_vao;
    SFLShaderProgram *_programColor;
    SFLShaderProgram *_programLight;
    SFLShaderProgram *_programModelGouraud;
    SFLShaderProgram *_programModelPhone;
    SFLShaderProgram *_programModelPhoneBlinn;

    void renderColor(){
        _programColor->bind();
        _programColor->setUniform3f("materialColor", materialColor);

        gm::mat4 model(1.0);
        _programColor->setUniformMatrix4fv("model", gm::valuePtrFrom(model));
        _programColor->setUniformMatrix4fv("view", gm::valuePtrFrom(_delegateCamaera->viewMatrix()));

        _vao->bind();
        _vao->draw();
    }
    void renderLight(){
        _programLight->bind();
        _programLight->setUniform3f("lightColor", lightColor);
        _programLight->setUniform3f("materialColor", materialColor);

        gm::mat4 model(1.0);
        _programLight->setUniformMatrix4fv("model", gm::valuePtrFrom(model));
        _programLight->setUniformMatrix4fv("view", gm::valuePtrFrom(_delegateCamaera->viewMatrix()));

        _vao->bind();
        _vao->draw();
    }
    void renderModel(SFLShaderProgram *program, gm::vec3 &lightPosition){
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

        gm::mat4 model(1.0);
        if (isRotateModel){
            model = gm::rotate(model, _times * speed, gm::vec3(1.0f, 0.3f, 0.5f));
        }
        program->setUniformMatrix4fv("model", gm::valuePtrFrom(model));
        program->setUniformMatrix4fv("view", gm::valuePtrFrom(_delegateCamaera->viewMatrix()));

        _vao->bind();
        _vao->draw();
    }
};

#endif // SFLMODELLIGHT_H
