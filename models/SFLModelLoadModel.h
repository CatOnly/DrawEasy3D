#ifndef SFLMODELLOADMODEL_H
#define SFLMODELLOADMODEL_H

#include "../common/SFLModelAbstract.h"
#include "../views/SFLViewLoadModel.h"
#include "../renders/SFLShaderProgram.h"
#include "../renders/SFLModel.h"

#define IS_USE_WHITECOlOR "isUseWhiteColor"

class SFLModelLoadModel: public SFLModelAbstract
{
public:
    enum Effect{
        effectOrigin,
        effectWhite,
        effectBlow,
        effectNormalVec
    };

    enum LoadType{
        LoadTypeNone,
        LoadTypeMesh,
        LoadTypeModel
    };

    SFLModelLoadModel():SFLModelAbstract(){
        _btn->setText("模型加载");
        _view = new SFLViewLoadModel(this);
        _program = new SFLShaderProgram();
        _model = new SFLModel();
        _loadType = LoadTypeNone;
        _isOnlyDrawLine = false;
        _isUseFaceCulling = false;
    }
    ~SFLModelLoadModel(){
        DELETE_SAFE(_program)
        DELETE_SAFE(_model)
    }

    void initializeOpenGL() override {
        _program->initializeOpenGLFunctions();
        _program->loadFromPath("://model.vsh","://model.fsh");
        _program->bind();
        _program->setUniform3f("lightPosition", gm::vec3(1.0f, 0.3f, 2.0f));
        _program->setUniformMatrix4fv("projection", gm::valuePtrFrom(gm::perspective(45.0f, 1.0f, 0.1f, 100.0f)));
        gm::mat4 model(1.0);
        model = gm::translate(model, gm::vec3(0.0f, -1.75f, 0.0f));
        model = gm::scale(model, gm::vec3(0.2f, 0.2f, 0.2f));
        _program->setUniformMatrix4fv("model", gm::valuePtrFrom(model));
        _program->setUniform1f(IS_USE_WHITECOlOR, 0.0f);

        _model->initializeOpenGLFunctions();
    }

    void render() override {
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.2, 0.2, 0.2, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (_loadType == LoadTypeNone) return;

        glPolygonMode(GL_FRONT_AND_BACK, _isOnlyDrawLine ? GL_LINE : GL_FILL);
        // 背面剔除
        if (_isUseFaceCulling){
            glEnable(GL_CULL_FACE);
            glFrontFace(GL_CCW);// 正面是 Counter Clockwise，逆时针
            glCullFace(GL_BACK);// 剔除背面
        } else {
            glDisable(GL_CULL_FACE);
        }

        _program->bind();

        if (_loadType != LoadTypeMesh){
            glEnable(GL_PROGRAM_POINT_SIZE);
        } else {
            glDisable(GL_PROGRAM_POINT_SIZE);
        }

        _program->setUniform3f("viewPos", _delegateCamaera->position);
        _program->setUniformMatrix4fv("view", gm::valuePtrFrom(_delegateCamaera->viewMatrix()));
        _attachEffect();

        _model->draw(*_program);
    }

    bool loadModel(const char *path){
        bool isSuccess = false;
        _model->loadModel(path);
        isSuccess = true;
        _loadType = LoadTypeModel;

        return isSuccess;
    }

    bool loadMeshJson(const char *path){
        bool isSuccess = false;
        _model->loadMesh(path);
        isSuccess = true;
        _loadType = LoadTypeMesh;

        return isSuccess;
    }

    void enableDrawLine(bool isDraw){
        _isOnlyDrawLine = isDraw;
    }

    void enableFaceCulling(bool isCulling){
        _isUseFaceCulling = isCulling;
    }

    void setAttachEffectType(int type){
        _attachEffectType = Effect(type);
    }

private:
    bool _isOnlyDrawLine;
    bool _isUseFaceCulling;
    SFLModel *_model;
    SFLShaderProgram *_program;
    Effect _attachEffectType;
    LoadType _loadType;


    void _attachEffect(){
        switch (_attachEffectType) {
        case effectOrigin:
            _program->setUniform1f(IS_USE_WHITECOlOR, 0.0f);
            break;
        case effectWhite:
            _program->setUniform1f(IS_USE_WHITECOlOR, 1.0f);
            break;
        case effectBlow:
            break;
        case effectNormalVec:
            break;
        default:
            break;
        }
    }
};
#endif // SFLMODELLOADMODEL_H
