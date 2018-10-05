#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

uniform vec2 offsetSteps;

out vec2 TexCoords[9];

void main(void)
{
    gl_Position = vec4(position, 1.0);

    vec2 texOffsets[9] = vec2[](
        vec2(-1,-1), vec2( 0,-1), vec2( 1,-1),
        vec2(-1, 0), vec2( 0, 0), vec2( 1, 0),
        vec2(-1, 1), vec2( 0, 1), vec2( 1, 1)
    );
    vec2 TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
    for (int i = 0; i < 25; ++i){
        TexCoords[i] = TexCoord + offsetSteps * texOffsets[i];
    }
}
