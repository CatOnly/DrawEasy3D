#ifndef POSTPROCESSING_FACEBEAUTIFY_H
#define POSTPROCESSING_FACEBEAUTIFY_H

#include <vector>

class SFLShaderProgram;
class SFLPostProcessing
{

public:
    enum Type{
        typeFaceBeautify,
        typeCartoon,
        typeSizeTag
    };

    SFLPostProcessing();
    ~SFLPostProcessing();

    void initializeOpenGLFunctions();
    void setParams(Type type, float radio, float stepX, float stepY);
    SFLShaderProgram *program(int index);

private:
    std::vector<SFLShaderProgram *> _programs;
};

#endif // POSTPROCESSING_FACEBEAUTIFY_H
