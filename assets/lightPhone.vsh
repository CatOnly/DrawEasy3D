#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 Normal;
out vec4 WorldPos;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

void main()
{
//    Normal = mat3(transpose(inverse(model))) * normal;
    Normal = normal;

    WorldPos = model * vec4(position, 1.0f);

    gl_Position = projection * view * WorldPos;
}
