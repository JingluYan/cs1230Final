#version 330 core

out vec4 fragColor;

in vec2 texc;
in vec4 normal_cameraSpace;
in vec4 tangent_cameraSpace;
in vec4 binormal_cameraSpace;
in vec4 position_cameraSpace;
in mat4 vMat;

uniform mat4 v;
uniform sampler2D tex;
uniform int useTexture = 0;

uniform sampler2D texBump;
uniform int useBumpTexture = 0;
uniform vec2 repeatBumpUV;

// Light data
const int MAX_LIGHTS = 10;
uniform int lightTypes[MAX_LIGHTS];         // 0 for point, 1 for directional
uniform vec3 lightPositions[MAX_LIGHTS];    // For point lights
uniform vec3 lightDirections[MAX_LIGHTS];   // For directional lights
//uniform vec3 lightAttenuations[MAX_LIGHTS]; // Constant, linear, and quadratic term
uniform vec3 lightColors[MAX_LIGHTS];

// Material data
uniform vec3 ambient_color;
uniform vec3 diffuse_color;
uniform vec3 specular_color;
uniform float shininess;

uniform bool useLighting;     // Whether to calculate lighting using lighting equation

void main(){
    mat4 TBN = transpose(mat4(tangent_cameraSpace,
                              binormal_cameraSpace,
                              normal_cameraSpace,
                              vec4(0)
                              ));
    vec3 color = vec3(0);
    if (useLighting) {
        color = ambient_color.xyz; // Add ambient component

        for (int i = 0; i < MAX_LIGHTS; i++) {
            // Without bump texture (camera Space )
            vec4 usingLightDirection = vec4(-lightDirections[i], 0);
            vec4 usingEyeDirection = normalize(vec4(0,0,0,1) - position_cameraSpace);
            vec4 usingNormal = normal_cameraSpace;

            // With Bump texture (convert to tangent space)
            if (useBumpTexture == 1){
                usingLightDirection = TBN * usingLightDirection;
                usingEyeDirection = TBN * usingEyeDirection;
                usingNormal = vec4(normalize(texture( texBump, texc ).rgb*2.0 - 1.0), 0);
            }
            vec4 vertexToLight = vec4(0);
            // Point Light
            if (lightTypes[i] == 0) {
                vertexToLight = normalize(v * vec4(lightPositions[i], 1) - position_cameraSpace);
            } else if (lightTypes[i] == 1) {
                // Dir Light
                vertexToLight = normalize(v * usingLightDirection);
            }

            // Add diffuse component
            float diffuseIntensity = max(0.0, dot(vertexToLight, usingNormal));
            color += max(vec3(0), lightColors[i] * diffuse_color * diffuseIntensity);

            // Add specular component
            vec4 lightReflection = normalize(-reflect(vertexToLight, usingNormal));
            vec4 eyeDirection = normalize(vec4(0,0,0,1) - position_cameraSpace);

            float specIntensity = pow(max(0.0, dot(usingEyeDirection, lightReflection)), shininess);
            color += max (vec3(0), lightColors[i] * specular_color * specIntensity);
        }
    } else {
        color = ambient_color + diffuse_color;
    }
    color = clamp(color, 0.0, 1.0);

    // Diffuse texture
    vec3 texColor = texture(tex, texc).rgb;
    texColor = clamp(texColor + vec3(1-useTexture), vec3(0), vec3(1));
    fragColor = vec4(color * texColor, 1);
}
