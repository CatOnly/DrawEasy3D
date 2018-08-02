#version 330 core
out vec4 color;

uniform vec3 lightColor;
uniform vec3 materialColor;

void main()
{
    color = vec4(lightColor * materialColor, 1.0f);
}
