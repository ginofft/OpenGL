#version 330
in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

out vec4 color;

struct DirectionalLight{
    vec3 color;
    float ambientIntensity;

    vec3 direction;
    float diffuseIntensity;
};

struct Material{
    float sIntensity;
    float shininess;
};

uniform sampler2D theTexture;
uniform DirectionalLight directionalLight;
uniform Material material;

uniform vec3 eyePos;

void main()
{   
    vec4 ambientColor = vec4(directionalLight.color, 1.0f) * directionalLight.ambientIntensity;
    
    float diffuseFactor = max(dot(normalize(normal), normalize(directionalLight.direction)), 0.0f);
    vec4 diffuseColor = vec4(directionalLight.color, 1.0f) * directionalLight.diffuseIntensity * diffuseFactor;

    vec4 specularColor = vec4(0,0,0,0);
    if (diffuseFactor>0.0f)
    {
        vec3 fragToEye = normalize(eyePos - fragPos);
        vec3 reflectedVertex = normalize(reflect(directionalLight.direction,
                                 normalize(normal)));
        float specularFactor = dot(fragToEye, reflectedVertex);
        if (specularFactor>0.0f)
        {
            specularFactor = pow(specularFactor, material.shininess);
            specularColor = vec4(directionalLight.color*material.sIntensity*specularFactor, 1.0f);
        }

    }

    color = texture(theTexture, texCoord) * (ambientColor + diffuseColor + specularColor);
}