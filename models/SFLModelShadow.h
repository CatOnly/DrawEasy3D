#ifndef SFLMODELSHADOW_H
#define SFLMODELSHADOW_H

#include "../common/SFLModelAbstract.h"
#include "../views/SFLViewShadow.h"
#include "../renders/SFLShaderProgram.h"
#include "../renders/SFLVertexArray.h"
#include "../renders/SFLTexture.h"

class SFLModelShadow: public SFLModelAbstract
{
public:
    enum ShadowType{
        TypeShadow,
        TypeShadowPoint,
        TypeShadowCSM,
        TypeShadowSSAO,
    };

    ShadowType type;

    SFLModelShadow():SFLModelAbstract(){
        _btn->setText("阴影");
        _view = new SFLViewShadow(this);
        _vao = new SFLVertexArray();
        _vaoCube = new SFLVertexArray();
        _vaoFloor = new SFLVertexArray();
        _programDepth = new SFLShaderProgram();
        _programShadow = new SFLShaderProgram();
        _programFloor = new SFLShaderProgram();

        type = TypeShadow;
        _shadowWidth = 1024;
        _shadowHeight = 1024;
        _fboDepth = 0;
        _texDepth = new SFLTexture();
        _texFloor = new SFLTexture();
    }

    ~SFLModelShadow(){
        DELETE_SAFE(_vao)
        DELETE_SAFE(_vaoCube)
        DELETE_SAFE(_vaoFloor)
        DELETE_SAFE(_programFloor)
        DELETE_SAFE(_programDepth)
        DELETE_SAFE(_programShadow)
        DELETE_SAFE(_texDepth)
        DELETE_SAFE(_texFloor)

        glDeleteFramebuffers(1, &_fboDepth);
    }

    void initializeOpenGL() override {
        GLfloat vertices[] = {
            // positions            // normals         // texcoords
             25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
            -25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
            -25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,

             25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
            -25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
             25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 10.0f
        };
        _vao->initializeOpenGLFunctions();
        _vao->create();
        _vao->bind();
        _vao->setData(vertices, 8 * 6, 6, {3, 3, 2});

        glGenFramebuffers(1, &_fboDepth);
        _texDepth->initializeOpenGLFunctions();
        _texDepth->creat(GL_TEXTURE0);
        _texDepth->loadDepthMap(_fboDepth, _shadowWidth, _shadowHeight);
        _texDepth->bind();

        gm::vec3 lightPos(-2.0f, 4.0f, -1.0f);
        gm::mat4 lightProjection, lightView;
        gm::mat4 lightSpaceMatrix;
        float near_plane = 1.0f, far_plane = 7.5f;
        lightProjection = gm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
        lightView = gm::lookAt(lightPos, gm::vec3(0.0f), gm::vec3(0.0, 1.0, 0.0));
        lightSpaceMatrix = lightProjection * lightView;

        _programDepth->initializeOpenGLFunctions();
        _programDepth->loadFromPath(":/shadowDepth.vsh",":/shadowDepth.fsh");
        _programDepth->bind();
        _programDepth->setUniformMatrix4fv("lightSpaceMatrix", gm::valuePtrFrom(lightSpaceMatrix));

        _programShadow->initializeOpenGLFunctions();
        _programShadow->loadFromPath(":/shadow.vsh",":/shadow.fsh");
        _programShadow->bind();
        _programShadow->setUniformMatrix4fv("lightSpaceMatrix", gm::valuePtrFrom(lightSpaceMatrix));
        _programShadow->setUniform3f("lightPos", lightPos);

        initFloor(near_plane, far_plane);
    }


    void render(int viewPortW, int viewPortH) override {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        switch(type){
            case TypeShadow:
                renderShadow(viewPortW, viewPortH);
                break;
            case TypeShadowPoint:
                renderShadowPoint(viewPortW, viewPortH);
                break;
            case TypeShadowCSM:
                renderShadowCSM(viewPortW, viewPortH);
                break;
            case TypeShadowSSAO:
                renderShadowSSAO(viewPortW, viewPortH);
                break;
        }
    }

    void initFloor(float near_plane, float far_plane) {
        GLfloat vertices[] = {
            // positions        // texture Coords
            -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
             1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
             1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
        _vaoFloor->initializeOpenGLFunctions();
        _vaoFloor->create();
        _vaoFloor->bind();
        _vaoFloor->setData(vertices, 5 * 4, 4, {3, 2});

        GLfloat verticesCube[] = {
            // back face
            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
             1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
             1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right
             1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
            -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
            // front face
            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
             1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
             1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
             1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
            -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
            // left face
            -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
            -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
            -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
            -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
            -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
            -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
            // right face
             1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
             1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
             1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right
             1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
             1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
             1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left
            // bottom face
            -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
             1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
             1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
             1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
            -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
            -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
            // top face
            -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
             1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
             1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right
             1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
            -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
            -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left
        };
        _vaoCube->initializeOpenGLFunctions();
        _vaoCube->create();
        _vaoCube->bind();
        _vaoCube->setData(verticesCube, 8 * 6 * 6, 36, {3,3,2});

        _texFloor->initializeOpenGLFunctions();
        _texFloor->creat(GL_TEXTURE1);
        _texFloor->loadTexture2DFromPath(":/wood.png", GL_RGBA, GL_REPEAT);
        _texFloor->bind();

        _programFloor->initializeOpenGLFunctions();
        _programFloor->loadFromPath(":/shadowFloor.vsh",":/shadowFloor.fsh");
        _programFloor->bind();
        _programFloor->setUniform1f("near_plane", near_plane);
        _programFloor->setUniform1f("far_plane", far_plane);
    }

    void renderScene(SFLShaderProgram* program) {
        // floor
        gm::mat4 model = gm::mat4(1.0f);
        model = gm::scale(model, gm::vec3(100.0f));
        program->setUniformMatrix4fv("model", gm::valuePtrFrom(model));
        _vaoFloor->bind();
        _vaoFloor->draw(GL_TRIANGLE_STRIP);

        // cubes
        model = gm::mat4(1.0f);
        model = gm::translate(model, gm::vec3(0.0f, 1.5f, 0.0));
        model = gm::scale(model, gm::vec3(0.5f));
        program->setUniformMatrix4fv("model", gm::valuePtrFrom(model));
        _vaoCube->bind();
        _vaoCube->draw();

        model = gm::mat4(1.0f);
        model = gm::translate(model, gm::vec3(2.0f, 0.0f, 1.0));
        model = gm::scale(model, gm::vec3(0.5f));
        program->setUniformMatrix4fv("model", gm::valuePtrFrom(model));
        _vaoCube->bind();
        _vaoCube->draw();

        model = gm::mat4(1.0f);
        model = gm::translate(model, gm::vec3(-1.0f, 0.0f, 2.0));
        model = gm::rotate(model, gm::radians(60.0f), gm::normalize(gm::vec3(1.0, 0.0, 1.0)));
        model = gm::scale(model, gm::vec3(0.25));
        program->setUniformMatrix4fv("model", gm::valuePtrFrom(model));
        _vaoCube->bind();
        _vaoCube->draw();
    }
    void renderShadow(int viewPortW, int viewPortH) {
        glEnable(GL_DEPTH_TEST);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        glViewport(0, 0, _shadowWidth, _shadowHeight);
        glBindFramebuffer(GL_FRAMEBUFFER, _fboDepth);
        glClear(GL_DEPTH_BUFFER_BIT);

        _texFloor->active();
        _texFloor->bind();
        _programDepth->bind();
        renderScene(_programDepth);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glViewport(0, 0, viewPortW, viewPortH);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        _texDepth->active();
        _texDepth->bind();
        _texFloor->active();
        _texFloor->bind();

        gm::mat4 projection = gm::perspective(gm::radians(45.0f), (float)viewPortW / (float)viewPortH, 0.1f, 100.0f);
        _programShadow->bind();
        _programShadow->setUniformMatrix4fv("projection", gm::valuePtrFrom(projection));
        _programShadow->setUniformMatrix4fv("view", gm::valuePtrFrom(_delegateCamaera->viewMatrix()));
        _programShadow->setUniform3f("viewPos", _delegateCamaera->position);
        _programShadow->setUniform1i("shadowMap", 0);
        _programShadow->setUniform1i("diffuseTexture", 1);

//        renderScene(_programShadow);

        // debug show depth
        _programFloor->bind();
        _programFloor->setUniform1i("depthMap", 0);

        _vaoFloor->bind();
        _vaoFloor->draw(GL_TRIANGLE_STRIP);

        glDisable(GL_DEPTH_TEST);
    }

    void renderShadowPoint(int viewPortW, int viewPortH) {

    }

    void renderShadowCSM(int viewPortW, int viewPortH) {

    }

    void renderShadowSSAO(int viewPortW, int viewPortH) {

    }

private:
    unsigned int _shadowWidth;
    unsigned int _shadowHeight;
    unsigned int _fboDepth;
    SFLVertexArray *_vao;
    SFLVertexArray *_vaoCube;
    SFLVertexArray *_vaoFloor;
    SFLTexture* _texDepth;
    SFLTexture* _texFloor;

    SFLShaderProgram *_programDepth;
    SFLShaderProgram *_programShadow;
    SFLShaderProgram *_programFloor;
};

#endif // SFLMODELSHADOW_H
