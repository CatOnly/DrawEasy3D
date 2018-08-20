#ifndef FACEBEAUTIFY_H
#define FACEBEAUTIFY_H

class SFLShaderProgram;
class FaceBeautify
{
public:
    FaceBeautify();
    ~FaceBeautify();

    void initializeOpenGLFunctions();
    void setParams(float radio, float stepX, float stepY);


private:
    SFLShaderProgram *_program = nullptr;
};

#endif // FACEBEAUTIFY_H
