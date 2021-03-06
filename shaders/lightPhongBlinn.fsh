#version 330 core
in vec3 Normal;
in vec4 WorldPos;

out vec4 color;

struct Material
{
    vec3 ambient; // 材质环境光颜色 大多数情况 == diffus（材质漫反射光）
    vec3 diffuse;
    vec3 specular; //镜面反射

    float shininess; //镜面反射强度
};
uniform Material material; // 材质

struct Light
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    vec3 position;
};
uniform Light light; // 光照

uniform vec3 viewPos;

const float blinnWeight = 2.0;
void main(void)
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - WorldPos.xyz);
    float diff = max(dot(norm, lightDir), 0.0);

    vec3 viewDir = normalize(viewPos - WorldPos.xyz);
    vec3 halfwapDir = normalize(lightDir + viewDir);
    float spec = pow( max( dot(viewDir, halfwapDir), 0.0 ), material.shininess );

    vec3 ambient = light.ambient * material.ambient;
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    vec3 specular = light.specular * (spec * material.specular) * blinnWeight;

    color = vec4(ambient + diffuse + specular, 1.0);
}
