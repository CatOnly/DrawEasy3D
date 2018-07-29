#ifndef SFLMODELMAPPING_H
#define SFLMODELMAPPING_H

#include "../common/SFLModelAbstract.h"
#include "../views/SFLViewMapping.h"
#include "../renders/SFLShaderProgram.h"
#include "../renders/SFLVertexArray.h"
#include "../renders/SFLTexture.h"

class SFLModelMapping: public SFLModelAbstract
{
public:
    enum MappingType{
        typeTex,
        typeLightDir,
        typeLightPoint,
        typeLightSpot,
        typeLightMulti
    };

    SFLModelMapping():SFLModelAbstract(){
        _btn->setText("贴图");
        _view = new SFLViewMapping(this);

        _vao = new SFLVertexArray();

        _programLight = new SFLShaderProgram();
        _programTex = new SFLShaderProgram();
        _programDir = new SFLShaderProgram();
        _programPoint = new SFLShaderProgram();
        _programSpot = new SFLShaderProgram();
        _programMulti = new SFLShaderProgram();

        _texDiffuse = new SFLTexture(true);
        _texSpecular = new SFLTexture(true);
        _texEmission = new SFLTexture(true);
    }
    ~SFLModelMapping(){
        DELETE_SAFE(_vao)

        DELETE_SAFE(_programLight)
        DELETE_SAFE(_programTex)
        DELETE_SAFE(_programDir)
        DELETE_SAFE(_programPoint)
        DELETE_SAFE(_programSpot)
        DELETE_SAFE(_programMulti)

        DELETE_SAFE(_texDiffuse)
        DELETE_SAFE(_texSpecular)
        DELETE_SAFE(_texEmission)
    }

    void initializeOpenGL() override {
        float vertices[] = {
            // positions          // normals           // texture coords
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
        };
        _vao->initializeOpenGLFunctions();
        _vao->create();
        _vao->bind();
        _vao->setData(vertices, 8 * 6 * 6, 36, {3,3,2});

        glm::vec3 lightPosition(1.0f, 0.3f, 2.0f);
        glm::mat4 projection = glm::perspective(45.0, 1.0, 0.1, 100.0);
        GLfloat *projectonMatPtr = glm::value_ptr(projection);

        _texDiffuse->initializeOpenGLFunctions();
        _texDiffuse->creat(GL_TEXTURE0);
        _texDiffuse->loadTexture2DFromPath(":/container2.png");

        _texSpecular->initializeOpenGLFunctions();
        _texSpecular->creat(GL_TEXTURE1);
        _texSpecular->loadTexture2DFromPath(":/container2_specular.png");

        _texEmission->initializeOpenGLFunctions();
        _texEmission->creat(GL_TEXTURE2);
        _texEmission->loadTexture2DFromPath(":/magic.jpeg");

        glm::mat4 model = glm::translate(glm::mat4(1.0f), lightPosition);
        model = glm::scale(model, glm::vec3(0.2f));
        _programLight->initializeOpenGLFunctions();
        _programLight->loadFromPath(":/color.vsh",":/color.fsh");
        _programLight->bind();
        _programLight->setUniformMatrix4fv("projection", projectonMatPtr);
        _programLight->setUniformMatrix4fv("model", glm::value_ptr(model));

        _programTex->initializeOpenGLFunctions();
        _programTex->loadFromPath(":/texture.vsh",":/texture.fsh");
        _programTex->bind();
        _programTex->setUniform3f("light.position", lightPosition);
        _programTex->setUniformMatrix4fv("projection", projectonMatPtr);
        _texDiffuse->bind();
        _programTex->setUniform1i("material", 0);

        _programDir->initializeOpenGLFunctions();
        _programDir->loadFromPath(":/lightDir.vsh",":/lightDir.fsh");
        _programDir->bind();
        _programDir->setUniform3f("light.direction", -lightPosition);
        setBaseParam(_programDir, lightPosition, projectonMatPtr);

        _programPoint->initializeOpenGLFunctions();
        _programPoint->loadFromPath(":/lightPoint.vsh",":/lightPoint.fsh");
        _programPoint->bind();
        setBaseParam(_programPoint, lightPosition, projectonMatPtr);

        _programSpot->initializeOpenGLFunctions();
        _programSpot->loadFromPath(":/lightSpot.vsh",":/lightSpot.fsh");
        _programSpot->bind();
        setBaseParam(_programSpot, lightPosition, projectonMatPtr);

        return;

        _programMulti->initializeOpenGLFunctions();
        _programMulti->loadFromPath(":/lightMulti.vsh",":/lightMulti.fsh");
        _programMulti->bind();
        _programMulti->setUniform3f("light.position", lightPosition);
        _programMulti->setUniformMatrix4fv("projection", projectonMatPtr);

    }

    void render() override {
        ++_times;
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.1, 0.1, 0.1, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        _texDiffuse->bind();
        _texSpecular->bind();
        _texEmission->bind();

        switch (type) {
            case typeTex:
                setProgramTexture();
                break;
            case typeLightDir:
                setProgramDir();
                break;
            case typeLightPoint:
                setProgramPoint();
                break;
            case typeLightSpot:
                setProgramSpot();
                break;
            case typeLightMulti:
                setProgramMulti();
                break;
        }

        _vao->bind();
        _vao->draw();

        _programLight->bind();
        _programLight->setUniform3f("materialColor", lightColor);
        _programLight->setUniformMatrix4fv("view", glm::value_ptr(_delegateCamaera->viewMatrix()));

        _vao->bind();
        _vao->draw();
    }

    MappingType type;

    glm::vec3 lightColor;
    GLfloat spotAngleInner;
    GLfloat spotAngleOuter;
    GLfloat emissionIntensity;

private:
    SFLVertexArray *_vao;
    SFLTexture *_texDiffuse;  //漫反射贴图
    SFLTexture *_texSpecular; //镜面贴图
    SFLTexture *_texEmission; //放射贴图
    SFLShaderProgram *_programTex;
    SFLShaderProgram *_programDir;
    SFLShaderProgram *_programPoint;
    SFLShaderProgram *_programSpot;
    SFLShaderProgram *_programMulti;
    SFLShaderProgram *_programLight;

    void setBaseParam(SFLShaderProgram *program, glm::vec3 &lightPosition, GLfloat *projectonMatPtr){
        program->setUniform3f("light.position", lightPosition);
        program->setUniformMatrix4fv("projection", projectonMatPtr);
        program->setUniform1f("material.shininess", 32.0);
        program->setUniform1i("material.diffuse",  0);
        program->setUniform1i("material.specular", 1);
        program->setUniform1i("material.emission", 2);
    }

    void setProgramTexture(){
        _programTex->bind();

        glm::mat4 model(1.0);
        _programTex->setUniformMatrix4fv("model", glm::value_ptr(model));
        _programTex->setUniformMatrix4fv("view", glm::value_ptr(_delegateCamaera->viewMatrix()));
    }

    void setProgramDir(){
        _programDir->bind();
        _programDir->setUniform3f("light.ambient", lightColor * float(0.2));
        _programDir->setUniform3f("light.diffuse",lightColor * 0.5f);
        _programDir->setUniform3f("light.specular",lightColor);
        _programDir->setUniform1f("material.emitIntensity", emissionIntensity);

        glm::mat4 model(1.0);
        _programDir->setUniformMatrix4fv("model", glm::value_ptr(model));
        _programDir->setUniformMatrix4fv("view", glm::value_ptr(_delegateCamaera->viewMatrix()));
        _programDir->setUniform3f("viewPos", _delegateCamaera->position);
    }

    void setProgramPoint(){
        _programPoint->bind();
        _programPoint->setUniform3f("light.ambient", lightColor * float(0.2));
        _programPoint->setUniform3f("light.diffuse",lightColor * 0.5f);
        _programPoint->setUniform3f("light.specular",lightColor);
        _programPoint->setUniform1f("material.emitIntensity", emissionIntensity);

        glm::mat4 model(1.0);
        _programPoint->setUniformMatrix4fv("model", glm::value_ptr(model));
        _programPoint->setUniformMatrix4fv("view", glm::value_ptr(_delegateCamaera->viewMatrix()));
        _programPoint->setUniform3f("viewPos", _delegateCamaera->position);
    }

    void setProgramSpot(){
        _programSpot->bind();
        _programSpot->setUniform3f("light.ambient", lightColor * float(0.2));
        _programSpot->setUniform3f("light.diffuse",lightColor * 0.5f);
        _programSpot->setUniform3f("light.specular",lightColor);
        _programSpot->setUniform1f("light.radiusInner", cos(glm::radians(spotAngleInner)));
        _programSpot->setUniform1f("light.radiusOuter", cos(glm::radians(spotAngleOuter)));
        _programSpot->setUniform3f("light.direction", _delegateCamaera->axisFront);
        _programSpot->setUniform3f("light.position", _delegateCamaera->position);
        _programSpot->setUniform1f("material.emitIntensity", emissionIntensity);

        glm::mat4 model(1.0);
        _programSpot->setUniformMatrix4fv("model", glm::value_ptr(model));
        _programSpot->setUniformMatrix4fv("view", glm::value_ptr(_delegateCamaera->viewMatrix()));
        _programSpot->setUniform3f("viewPos", _delegateCamaera->position);
    }

    void setProgramMulti(){

    }
};

#endif // SFLMODELMAPPING_H
