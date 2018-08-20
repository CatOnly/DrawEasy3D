#ifndef SFLSHADERPROGRAM_H
#define SFLSHADERPROGRAM_H

#include <sstream>
#include <fstream>
#include <QOpenGLFunctions>
#include <QCoreApplication>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QDebug>

#include <gtc/type_ptr.hpp>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

using namespace std;

class SFLShaderProgram: public QOpenGLFunctions
{
public:
    SFLShaderProgram(){ }
    ~SFLShaderProgram(){
        if (!_programID || !_isInitialized) return;

        glDeleteProgram(_programID);
    }
    void initializeOpenGLFunctions(){
        _isInitialized = true;
        QOpenGLFunctions::initializeOpenGLFunctions();
    }

    void loadFromStr(const char *strVertex, const char *strFragment){
        GLuint shaderVertex = loadFromStr(GL_VERTEX_SHADER, strVertex);
        GLuint shaderFragment = loadFromStr(GL_FRAGMENT_SHADER, strFragment);

        create(shaderVertex, shaderFragment);
    }
    void loadFromPath(const char *pathVertex, const char *pathFragment){
        GLuint shaderVertex = loadFromPath(GL_VERTEX_SHADER, pathVertex);
        GLuint shaderFragment = loadFromPath(GL_FRAGMENT_SHADER, pathFragment);

        create(shaderVertex, shaderFragment);
    }

    void create(GLuint &shaderVertex, GLuint &shaderFragment){
        _programID = glCreateProgram();
        glAttachShader(_programID, shaderVertex);
        glAttachShader(_programID, shaderFragment);
        glLinkProgram(_programID);

        GLint success;
        const GLsizei bufferSize = 512;
        GLchar inforLog[bufferSize];
        glGetProgramiv(_programID, GL_LINK_STATUS, &success);
        if (!success){
            glGetProgramInfoLog(_programID, bufferSize, NULL, inforLog);
            qDebug() << "Error: Shader program link " << inforLog << endl;
        }

        glDeleteShader(shaderVertex);
        glDeleteShader(shaderFragment);
    }

    void bind(){
        glUseProgram(_programID);
    }
    void unBind(){
        glUseProgram(0);
    }

    GLuint programID(){
        return _programID;
    }

    void setUniform1i(const char* nameAttr, GLint x){
        glUniform1i(glGetUniformLocation(_programID, nameAttr), x);        
    }

    void setUniform1f(const char* nameAttr, GLfloat x){
        glUniform1f(glGetUniformLocation(_programID, nameAttr), x);
    }

    void setUniform2f(const char* nameAttr, GLfloat x, GLfloat y){
        glUniform2f(glGetUniformLocation(_programID, nameAttr), x, y);
    }

    void setUniform3f(const char* nameAttr, GLfloat x, GLfloat y, GLfloat z){
        glUniform3f(glGetUniformLocation(_programID, nameAttr), x, y, z);
    }
    void setUniform3f(const char* nameAttr, glm::vec3 vector){
         setUniform3f(nameAttr, vector.x, vector.y, vector.z);
    }

    void setUniform4f(const char* nameAttr, GLfloat x, GLfloat y, GLfloat z, GLfloat w){
        glUniform4f(glGetUniformLocation(_programID, nameAttr), x, y, z, w);
    }

    void setUniformMatrix4fv(const char* nameAttr, const GLfloat* value){
        glUniformMatrix4fv(glGetUniformLocation(_programID, nameAttr), 1, GL_FALSE, value);
    }

private:
    bool _isInitialized = false;
    GLuint _programID = 0;

    SFLShaderProgram(const SFLShaderProgram &);
    SFLShaderProgram &operator = (const SFLShaderProgram &);

    GLuint loadFromStr(GLenum type, const char *shaderSrc) {
//        qDebug()  << __func__ << endl << shaderSrc;
        GLuint shader = glCreateShader(type);
        glShaderSource(shader, 1, &shaderSrc, NULL);
        glCompileShader(shader);

        GLint success;
        const GLsizei bufferSize = 512;
        GLchar inforLog[bufferSize];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success){
            glGetShaderInfoLog(shader, bufferSize, NULL, inforLog);
            qDebug() << "Error: Shader compile " << (type == GL_VERTEX_SHADER ? "vertex" :"fragment") << inforLog << endl;
        }

        return shader;
    }
    GLuint loadFromPath(GLenum type, const char *filePath) {
        QFile inputFile(filePath);
        inputFile.open(QIODevice::ReadOnly);
        QTextStream in(&inputFile);
        QString code = in.readAll();
        inputFile.close();

//        QString basePath = QCoreApplication::applicationDirPath();

//        string path = basePath.toStdString() + string(filePath);
//        // 从文件路径中获取顶点/片段着色器
//        string code;
//        ifstream file;
//        // 保证ifstream对象可以抛出异常：
//        file.exceptions(ifstream::badbit);
//        try {
//            // 打开文件
//            file.open(path);
//            stringstream fileStrStream;
//            // 读取文件的缓冲内容到流中
//            fileStrStream << file.rdbuf();
//            // 关闭文件
//            file.close();
//            // 转换流至GLchar数组
//            code = fileStrStream.str();
//        } catch(ifstream::failure e) {
//            qDebug() << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
//        }

//        if (code.empty()){
//            qDebug() << "ERROR: NO shader code create!" << endl
//                     << "Shader Path: "<< path.c_str();
//        }
//        qDebug() << code;

        return loadFromStr(type, code.toStdString().c_str());
    }
};

#endif // SFLSHADERPROGRAM_H
