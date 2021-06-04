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

        glDeleteVertexArrays(1, &_vertexArrayRef);
        glDeleteBuffers(1, &_vertexBufferRef);
    }

    void initializeOpenGLFunctions(){
        _isInitialized = true;
        QOpenGLFunctions::initializeOpenGLFunctions();
    }

    void create(){
        _isCreateBySelf = true;

        glGenVertexArrays(1, &_vertexArrayRef);
        glGenBuffers(1, &_vertexBufferRef);
    }

    void setRef(GLuint vao, GLuint vbo = 0){
        _isCreateBySelf = false;

        _vertexArrayRef = vao;
        _vertexBufferRef = vbo;
    }

    void bind(){
        glBindVertexArray(_vertexArrayRef);
    }
    void unBind(){
        glBindVertexArray(0);
    }

    void setData(GLfloat *array, GLsizei size, GLsizei pointsCount, vector<int> format, GLenum draw = GL_STATIC_DRAW) {
        _count = pointsCount;

        glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferRef);
        glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), array, draw);

        // 告诉 OpenGL 如何解析传入的顶点数据
        int total = 0;
        for (size_t i = 0; i < format.size(); ++i){
            total += format.at(i);
        }
        int offset = 0;
        for (size_t i = 0; i < format.size(); ++i){
            offset += i > 0 ? format.at(i - 1) * sizeof(GLfloat) : 0;
            glVertexAttribPointer(i, format.at(i), GL_FLOAT, GL_FALSE, total * sizeof(GLfloat),  (GLvoid *)offset);
            glEnableVertexAttribArray(i);
        }
    }

    void draw(GLenum type = GL_TRIANGLES, GLint beginIdx = 0, GLsizei count = 0){
        if (count) _count = count;

        glDrawArrays(type, beginIdx, _count);
    }

private:
    bool _isInitialized = false;
    bool _isCreateBySelf = false;
    GLuint _vertexArrayRef = 0;
    GLuint _vertexBufferRef = 0;
    GLsizei _count = 0;
};
#endif // SFLVERTEXARRAY_H
