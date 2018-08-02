#version 330 core
in vec2 TexCoord;
in vec3 Normal;
in vec4 WorldPos;

out vec4 color;

struct Material
{
    sampler2D diffuse;  //漫反射贴图
    sampler2D specular; //镜面贴图
    sampler2D emission; //放射光贴图

    float shininess; //镜面反射强度
    float emitIntensity;//放射光强度
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

// 冯氏着色 = 环境光 + 漫反射 + 点光源，在片源着色器做
// Gouraud着色，定点坐标的冯氏光照版本
void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - WorldPos.xyz);
    float diff = max(dot(norm, lightDir), 0.0);

    vec3 viewDir = normalize(viewPos - WorldPos.xyz);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow( max( dot(viewDir, reflectDir), 0.0 ), material.shininess );

    vec3 diffuseColor = texture(material.diffuse, TexCoord).rgb;
    vec3 ambient =  light.ambient  * diffuseColor; // 材质环境光颜色 大多数情况 == diffus（材质漫反射光）
    vec3 diffuse =  light.diffuse  * diff * diffuseColor;
    vec3 specular = light.specular * spec * texture(material.specular, TexCoord).rgb;

    //  自发光：放射光贴图，不受其他光的影响
    vec3 emission = vec3(texture(material.emission, TexCoord)) * material.emitIntensity;
    color = vec4(ambient + diffuse + specular + emission, 1.0f);
}
