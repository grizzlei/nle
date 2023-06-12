#version 330

in vec4 vertexColor;
in vec2 textureCoordinates;
in vec3 normal;

out vec4 color;

struct DirectionalLight
{
    vec3 color;
    float ambientIntensity;
    vec3 direction;
    float diffuseIntensity;
};

uniform int lightingEnabled = 1;
uniform int textureEnabled = 1;
uniform int fogEnabled = 1;
uniform sampler2D texture0;
uniform DirectionalLight directionalLight;

void main() {

    vec4 lightFactor = vec4(1.f);

    if(lightingEnabled == 1)
    {
        vec4 ambientColor = vec4(directionalLight.color, 1.f) * directionalLight.ambientIntensity;
        float diffuseFactor = max(dot(normalize(normal), normalize(directionalLight.direction)), 0.f);
        vec4 diffuseColor = vec4(directionalLight.color, 1.f) * directionalLight.diffuseIntensity * diffuseFactor * 1.f;
        lightFactor = ambientColor + diffuseColor;
    }

    if(textureEnabled == 1)
    {
        color = texture(texture0, textureCoordinates) * lightFactor;
    }
    else
    {
        color = vertexColor * lightFactor;
    }
}