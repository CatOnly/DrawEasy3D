#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    TexCoords = aPos;
    vec4 pos = projection * view * model * vec4(aPos, 1.0);
    gl_Position = pos.xyww; // 用 w 替换 z，让天空盒的深度值在进行深度除法后始终保持 1.0 的最大值，确保天空盒在最后绘制
}
