#version 330 core
out vec4 color;

uniform vec3 uniformColor;

void main()
{
    color = vec4(uniformColor, 1.0f);
}
