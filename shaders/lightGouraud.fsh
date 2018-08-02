#version 330 core
in vec3 pointColor;
out vec4 color;

void main()
{
    color = vec4(pointColor, 1.0);
}
