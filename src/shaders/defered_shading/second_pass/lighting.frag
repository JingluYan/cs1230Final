#version 330 core
out vec4 FragColor;

in vec2 texc;

uniform sampler2D gPosition;   // cam space
uniform sampler2D gNormal;     // cam space
uniform sampler2D gAlbedoSpec; // cam space

uniform sampler2D ssaoColor;

uniform mat4 v;

// Light data
const int MAX_LIGHTS = 30;
uniform int lightTypes[MAX_LIGHTS];         // 0 for point, 1 for directional
uniform vec3 lightPositions[MAX_LIGHTS];    // For point lights
uniform vec3 lightDirections[MAX_LIGHTS];   // For directional lights
uniform vec3 lightAttenuations[MAX_LIGHTS]; // Constant, linear, and quadratic term
uniform vec3 lightColors[MAX_LIGHTS];
uniform int lightCount = 0;

// Material data
uniform vec2 repeatUV;

uniform bool useLighting;     // Whether to calculate lighting using lighting equation
uniform bool visualizeSSAO = false;
uniform bool useSSAO = true;
uniform float ambient = 0.3;

void main()
{
    // retrieve data from G-buffer
    vec3 FragPos = texture(gPosition, texc).rgb;
    vec3 Normal = texture(gNormal, texc).rgb;
    vec3 Albedo = texture(gAlbedoSpec, texc).rgb;
    float AmbientOcclusion = texture(ssaoColor, texc).r;
//    float AmbientOcclusion = 1.0f;
    // this is for no texture mode
//    vec3 Albedo = vec3(1);
    float shininess = texture(gAlbedoSpec, texc).a;

    // then calculate lighting as usual
    vec3 lighting = Albedo*ambient; // hard-coded ambient component

    if (useLighting) {
        for (int i = 0; i < lightCount; i++) {
            vec3 vertexToLight = vec3(0);
            // Point Light
            if (lightTypes[i] == 0) {
                vertexToLight = normalize( (v*vec4(lightPositions[i],1.0) - vec4(FragPos, 1.0)).xyz );
            } else if (lightTypes[i] == 1) { // Dir Light
                vertexToLight = normalize( (-v*vec4(lightDirections[i], 0.0)).xyz);
            }

            float distance = length((v*vec4(lightPositions[i], 1.0)).xyz - FragPos);
            float atten = min(1 / (lightAttenuations[i].x
                                   + lightAttenuations[i].y * distance
                                   + lightAttenuations[i].y * pow(distance, 2)), 1);
            // Add diffuse component
            float diffuseIntensity = max(0.0, dot(vertexToLight, Normal));
            if (lightTypes[i] == 0) { // only attenuates point lights
                diffuseIntensity = diffuseIntensity * atten;
            }
            lighting += max(vec3(0), lightColors[i] * Albedo * diffuseIntensity);

            // Add specular component
            vec3 lightReflection = normalize(reflect(-vertexToLight, normalize(Normal)));
            vec3 eyeDirection = normalize((vec3(0) - FragPos).xyz);
            float specIntensity = 0.3 * pow(max(0.0, dot(eyeDirection, lightReflection)), shininess);
            if (lightTypes[i] == 0) { // only attenuates point lights
                specIntensity = specIntensity * atten;
            }
            lighting += max (vec3(0), lightColors[i] * Albedo * specIntensity);
        }
    }
    lighting = clamp(lighting, vec3(0), vec3(1));

    if (visualizeSSAO) {
        FragColor = vec4(AmbientOcclusion);
    } else {
        if (useSSAO) {
            FragColor = vec4(lighting * AmbientOcclusion, 1.0);
        } else {
            FragColor = vec4(lighting, 1.0);
        }
    }
}
