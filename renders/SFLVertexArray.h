#ifndef SFLVERTEXARRAY_H
#define SFLVERTEXARRAY_H

#include <QOpenGLFunctions>

using namespace std;

class SFLVertexArray : public QOpenGLFunctions
{
public:
    SFLVertexArray() {}
    ~SFLVertexArray() {
        if (!_isInitialized || !_isCreateBySelf || !_vertexArrayRef) return;

        glDeleteVertexArrays(1, _vertexArrayRef);
        glDeleteBuffers(1, _vertexBufferRef);
    }

    void initializeOpenGLFunctions(){
        _isInitialized = true;
        QOpenGLFunctions::initializeOpenGLFunctions();
    }

    void create(){
        _isCreateBySelf = true;

        glGenVertexArrays(1, _vertexArrayRef);
        glGenBuffers(1, _vertexBufferRef);
    }

    void setRef(GLuint vao, GLuint vbo = 0){
        _isCreateBySelf = false;

        _vertexArrayRef = vao;
        _vertexBufferRef = vbo;
    }

    void bind(){
        glBindVertexArray(_vertexArrayRef);
        glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferRef);
    }
    void unBind(){
        glBindVertexArray(0);
    }

    void setDataFormate(vector<int> &format){
        _format = format;
    }

    void setData(GLfloat *array, GLenum draw = GL_STATIC_DRAW) {
        glBufferData(GL_ARRAY_BUFFER, sizeof(array), array, draw);
        // 告诉 OpenGL 如何解析传入的顶点数据
        int total = 0;
        for (int i = 0; i < _format.size(); ++i){
            total += _format.at(i);
        }
        int offset = 0;
        for (int i = 0; i < _format.size(); ++i){
            offset += i > 0 ? _format.at(i - 1) * sizeof(GLfloat) : 0;
            glVertexAttribPointer(i, _format.at(i), GL_FLOAT, GL_FALSE, total * sizeof(GLfloat),  (void *)offset);
            glEnableVertexAttribArray(i);
        }
    }

private:
    bool _isInitialized = false;
    bool _isCreateBySelf = false;
    GLuint _vertexArrayRef = 0;
    GLuint _vertexBufferRef = 0;
    vector<int> _format;
};
#endif // SFLVERTEXARRAY_H
