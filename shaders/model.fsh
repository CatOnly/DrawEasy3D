#version 330 core
in vec2 TexCoord;
in vec3 Normal;
in vec4 WorldPos;
out vec4 color;
struct Material {
    sampler2D diffuse1;
    sampler2D specular1;
};
uniform Material material;
uniform vec3 lightPosition;
uniform vec3 viewPos;
uniform float isUseWhiteColor;

const vec3 lightWeight = vec3(0.2, 0.5, 32.0);
void main() {
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPosition - WorldPos.xyz);

    vec3 viewDir = normalize(viewPos - WorldPos.xyz);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow( max( dot(viewDir, reflectDir), 0.0 ), lightWeight.z );

    vec3 diffuseColor = texture(material.diffuse1, TexCoord).rgb;
    vec3 ambient = lightWeight.x * diffuseColor;

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = lightWeight.y * diff * diffuseColor;
    vec3 specular = spec * texture(material.specular1, TexCoord).rgb;

    if (isUseWhiteColor == 1.0){
        color = vec4(vec3(lightWeight.x + lightWeight.y * diff + spec), 1.0);
        return;
    }
    color = vec4(ambient + diffuse + specular, 1.0);
}
