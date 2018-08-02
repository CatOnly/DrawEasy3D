#version 330 core
out vec4 color;

uniform vec3 materialColor;

void main()
{
    color = vec4(materialColor, 1.0f);
}
