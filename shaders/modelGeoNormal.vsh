#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 texCoord;

out vec2 TexCoord;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

void main()
{
    TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);

    gl_Position = projection * view * model * vec4(position, 1.0f);
}
