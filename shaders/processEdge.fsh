#version 330 core
in vec2 TexCoords[25];
out vec4 color;

uniform sampler2D material;

const vec3 vY = vec3(0.2126, 0.7152, 0.0722);

void main()
{
    float weight[25] = float[](
        -2.0,-4.0,-4.0,-4.0,-2.0,
        -4.0, 0.0, 8.0, 0.0,-4.0,
        -4.0, 8.0,24.0, 8.0,-4.0,
        -4.0, 0.0, 8.0, 0.0,-4.0,
        -2.0,-4.0,-4.0,-4.0,-2.0
    );
    float alpha = 0.0;
    for (int i=0; i < 25; ++i){
        alpha += dot(texture(material, TexCoords[i]).rgb, vY) * weight[i];
    }

    color = vec4(texture(material, TexCoords[11]).rgb * alpha, 1.0);
}
