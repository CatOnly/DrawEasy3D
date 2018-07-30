#version 330 core

#define LIGHT_POINTS 4
#define LIGHT_ATTR_COMMON vec3 ambient; vec3 diffuse; vec3 specular;

#define DIFF(light) max(dot(Normal, light), 0.0)
#define SPEC(light) pow(max(dot( viewDir, reflect(light, Normal) ), 0.0), material.shininess)

#define Ambient(light) light.ambient  * vec3(texture(material.diffuse,  TexCoord))
#define Diffuse(light, lightDir, diff) light.diffuse  * vec3(texture(material.diffuse,  TexCoord)) * diff( lightDir)
#define Specular(light,lightDir, spec) light.specular * vec3(texture(material.specular, TexCoord)) * spec(-lightDir)

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;

    float shininess;
    float emitIntensity;
};

struct LightDir {
    LIGHT_ATTR_COMMON

    vec3 direction;
};

struct LightPoint {
    LIGHT_ATTR_COMMON

    vec3 position;

    float wConstant;
    float wLinear;
    float wQuadratic;
};

struct LightSpot {
    LIGHT_ATTR_COMMON

    vec3 position;
    vec3 direction;

    float wConstant;
    float wLinear;
    float wQuadratic;

    float radiusInner;
    float radiusOuter;
};

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 color;

uniform Material material;
uniform LightDir lightDirect;
uniform LightPoint pointLights[LIGHT_POINTS];
uniform LightSpot spotlight;

vec3 CalcDirLight(LightDir light, vec3 viewDir);
vec3 CalcPointLight(LightPoint light, vec3 viewDir);
vec3 CalcSpotLight(LightSpot light, vec3 viewDir);

void main() {
    // 一些属性
    vec3 viewDir = normalize(-FragPos);
    // 1. 计算平行光照
    vec3 result = CalcDirLight(lightDirect, viewDir);
    // 2. 计算顶点光照
    for(int i = 0; i < LIGHT_POINTS; ++i)
        result += CalcPointLight(pointLights[i], viewDir);
    // 3. 计算 Spotlight
    result += CalcSpotLight(spotlight, viewDir);
    // 4. 计算 放射光贴图，不受其他光的影响
    result += vec3(texture(material.emission, TexCoord)) * material.emitIntensity;

    color = vec4(result, 1.0);
}

vec3 CalcDirLight(LightDir light, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);

    return (Ambient(light) + Diffuse(light, lightDir, DIFF) + Specular(light, lightDir, SPEC));
}

vec3 CalcPointLight(LightPoint light, vec3 viewDir){
    vec3 lightDir = normalize(light.position - FragPos);

    // 计算衰减
    float distance    = length(light.position - FragPos);
    float attenuation = 1.0f / (light.wConstant + light.wLinear * distance + light.wQuadratic * (distance * distance));

    return ( Ambient(light) + Diffuse(light, lightDir, DIFF) + Specular(light, lightDir, SPEC) ) * attenuation;
}

vec3 CalcSpotLight(LightSpot light, vec3 viewDir){
    vec3 lightDir = normalize(light.position - FragPos);

    // 计算衰减
    float distance    = length(light.position - FragPos);
    float attenuation = 1.0f / (light.wConstant + light.wLinear * distance + light.wQuadratic * (distance * distance));

    float theta = max(dot(-lightDir, light.direction), 0.0f);
    // 限定范围
    float intensity = clamp((theta - light.radiusOuter) / (light.radiusInner - light.radiusOuter), 0.0f, 1.0f);

    return ( Ambient(light) + Diffuse(light, lightDir, DIFF) + Specular(light, lightDir, SPEC) ) * intensity;//* attenuation
}
