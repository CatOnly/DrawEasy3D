#version 330 core

uniform float radio;
uniform sampler2D material;

in vec2 TexCoords[9];
out vec4 color;

const float PI = 3.14159;
const vec3 vDefault0 = vec3(0.0);
const vec3 vY = vec3(0.2126, 0.7152, 0.0722);

vec3 HSVToRGB(vec3 color) {
    if (color.y == 0.0) return vec3(color.z); // Luminance

    float hue = color.x;
    hue *= 6.0; 			     // Hue 默认范围是 [0, 1]
    float chroma = color.z * color.y;
    float m = color.z - chroma;  // Lightness
    float x = (1.0 - abs(mod(hue, 2.0) - 1.0)) * chroma;

    if (hue < 1.0){
        return vec3(chroma + m, x + m, m);
    } else if (hue < 2.0){
        return vec3(x + m, chroma + m, m);
    } else if (hue < 3.0){
        return vec3(m, chroma + m, x + m);
    } else if (hue < 4.0){
        return vec3(m, x + m, chroma + m);
    } else if (hue < 5.0){
        return vec3(x + m, m, chroma + m);
    } else {
        return vec3(chroma + m, m, x + m);
    }
}

vec3 RGBToHSV(vec3 color) {
        float minRGB = min(min(color.r, color.g), color.b);
    float maxRGB = max(max(color.r, color.g), color.b);
    float sum = maxRGB + minRGB;
    float chroma = maxRGB - minRGB;

    // V = maxRGB;
    vec3 hsv = vec3(0.0, 0.0, maxRGB);
    if (chroma == 0.0) return hsv;

    // Saturation
    hsv.y = maxRGB == 0.0 ? 0.0 : chroma / maxRGB;

    // Hue 原来范围是 [0, 360), 这里默认输入的范围是 [0, 1]
    if (color.r == maxRGB) {
        hsv.x =  (color.g - color.b) / chroma / 6.0;
    } else if (color.g == maxRGB) {
        hsv.x = ((color.b - color.r) / chroma + 2.0) / 6.0;
    } else {
        hsv.x = ((color.r - color.g) / chroma + 4.0) / 6.0;
    }

    // Optimize
    // hsv.x += 1.0 - step(0.0, hsv.x);
    if (hsv.x < 0.0) hsv.x += 1.0;

    return hsv;
}

void main(void)
{
    float x = 0.0;
    vec3 colors[9];
    float greys[9];
    float weightX[9] = float[](
       -1.0, -2.0, -1.0,
        0.0,  0.0,  0.0,
       -1.0, -2.0, -1.0
    );
    for (int i=0; i < 9; ++i){
        colors[i] = texture(material, TexCoords[i]).rgb;
        greys[i] = dot(colors[i], vY);
        x += greys[i] * weightX[i];
    }

    float y = 0.0;
    float weightY[9] = float[](
       -1.0, 0.0, -1.0,
       -2.0, 0.0, -2.0,
       -1.0, 0.0, -1.0
    );

    vec3 vWeight;
    vec3 vWeightTotal = vDefault0;
    vec3 colorSum = vDefault0;
    vec3 colorCenter = colors[4];
    for (int i=0; i < 9; ++i){
        vec3 color = colors[i];
        y += greys[i] * weightY[i];
        vWeight = 0.8 * max(vDefault0, 1.0 - radio * abs(colorCenter - color));
        vWeightTotal += vWeight;
        colorSum += vWeight * color;
    }

    mat2 T = mat2(x*x, x*y, x*y, y*y);
    float K = x*x * y*y - x*y * x*y;
    float H = x*x + y*y;
//    float gradient = sqrt(x*x + y*y);
//    float degree = (atan(y/x) + 0.5 * PI) * 180.0 / PI;
//    float greyCenter = greys[4];
//    bool isLower = false;
//    if (degree >= 0.0 && degree < 22.5) {
//        isLower = greyCenter < greys[5] || greyCenter < greys[3];
//    } else if (degree >= 22.5 && degree < 67.5){
//        isLower = greyCenter < greys[2] || greyCenter < greys[0];
//    } else if (degree >= 67.5 && degree < 112.5){
//        isLower = greyCenter < greys[1] || greyCenter < greys[7];
//    } else if (degree >= 112.5 && degree < 157.5){
//        isLower = greyCenter < greys[0] || greyCenter < greys[8];
//    } else if (degree >= 157.5) {
//        isLower = greyCenter < greys[5] || greyCenter < greys[3];
//    }

//    if (isLower){
//        degree = 0.0;
//    }

    colorSum /= vWeightTotal;
//    colorSum = alpha > 0.3 ? vec3(0.0,0.0,0.0) : colorSum;

    vec3 colorHSV = RGBToHSV(colorSum);
    colorHSV.b = pow(colorHSV.b, 0.6);
    colorSum = HSVToRGB(colorHSV);

    color = vec4(colorSum, 1.0);
}
