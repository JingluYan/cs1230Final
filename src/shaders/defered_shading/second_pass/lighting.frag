#version 330 core
out vec4 FragColor;

in vec2 texc;

uniform sampler2D gPosition;   // cam space
uniform sampler2D gNormal;     // cam space
uniform sampler2D gAlbedoSpec; // cam space
uniform sampler2D gTangent;    // obj space
uniform sampler2D gBinormal;   // obj space
uniform sampler2D gBumpNormal;   // obj space
uniform sampler2D ssaoColor;

uniform mat4 v;

// Bump Map
uniform bool useBumpTexture;

// Light data
const int MAX_LIGHTS = 30;
uniform int lightTypes[MAX_LIGHTS];         // 0 for point, 1 for directional
uniform vec3 lightPositions[MAX_LIGHTS];    // For point lights
uniform vec3 lightDirections[MAX_LIGHTS];   // For directional lights
uniform vec3 lightAttenuations[MAX_LIGHTS]; // Constant, linear, and quadratic term
uniform vec3 lightColors[MAX_LIGHTS];
uniform int lightCount = 0;

// Material data
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
    vec3 Tangent = texture(gTangent, texc).rgb;
    vec3 BiNormal = texture(gBinormal, texc).rgb;
//    float AmbientOcclusion = 1.0f;
    // this is for no texture mode
//    vec3 Albedo = vec3(1);
    float shininess = texture(gAlbedoSpec, texc).a;

    // then calculate lighting as usual
    vec3 lighting = Albedo*ambient; // hard-coded ambient component

    // matrix to convery camera space to tangent space
    mat3 TBN = transpose(mat3(Tangent,
                              BiNormal,
                              Normal
                             ));
    if (useLighting) {
        for (int i = 0; i < lightCount; i++) {
            // Without bump texture (camera Space )
            vec3 usingLightDirection = -lightDirections[i];
            vec3 usingEyeDirection = normalize(vec3(0) - FragPos);
            vec3 usingNormal = Normal;

            // With Bump texture (convert to tangent space)
            if (useBumpTexture && length(texture(gBumpNormal, texc)) > 0.01){
                usingLightDirection = TBN * usingLightDirection;
                usingEyeDirection = TBN * usingEyeDirection;
                usingNormal = normalize(texture( gBumpNormal, texc ).rgb*2.0 - 1.0);
            }

            vec3 vertexToLight = vec3(0);
            // Point Light
            if (lightTypes[i] == 0) {
                vertexToLight = normalize( (v*vec4(lightPositions[i],1.0) - vec4(FragPos, 1.0)).xyz );
            } else if (lightTypes[i] == 1) { // Dir Light
                vertexToLight = normalize( (v * vec4(usingLightDirection, 0)).xyz );
            }

            float distance = length((v*vec4(lightPositions[i], 1.0)).xyz - FragPos);
            float atten = min(1 / (lightAttenuations[i].x
                                   + lightAttenuations[i].y * distance
                                   + lightAttenuations[i].y * pow(distance, 2)), 1);
            // Add diffuse component
            float diffuseIntensity = max(0.0, dot(vertexToLight, usingNormal));
            if (lightTypes[i] == 0) { // only attenuates point lights
                diffuseIntensity = diffuseIntensity * atten;
            }
            lighting += max(vec3(0), lightColors[i] * Albedo * diffuseIntensity);

            // Add specular component
            vec3 lightReflection = normalize(reflect(-vertexToLight, normalize(usingNormal)));
            vec3 eyeDirection = normalize((vec3(0) - FragPos).xyz);
            float specIntensity = 0.3 * pow(max(0.0, dot(usingEyeDirection, lightReflection)), shininess);
            if (lightTypes[i] == 0) { // only attenuates point lights
                specIntensity = specIntensity * atten;
            }
            lighting += max (vec3(0), lightColors[i] * Albedo * specIntensity);
        }
    }
    lighting = clamp(lighting, vec3(0), vec3(1));

    if (AmbientOcclusion < 0.9) {
        AmbientOcclusion *= AmbientOcclusion*AmbientOcclusion/2.0;
    }

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
