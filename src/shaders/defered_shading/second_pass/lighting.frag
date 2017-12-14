#version 330 core
out vec4 FragColor;

in vec2 texc;

uniform sampler2D gPosition;   // world space
uniform sampler2D gNormal;     // world space
uniform sampler2D gAlbedoSpec; // world space

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

vec3 unpack(vec3 v) {
    return v*vec3(2.0) - vec3(1.0);
}

void main()
{
    // retrieve data from G-buffer
    vec3 FragPos = texture(gPosition, texc).rgb;
    vec3 Normal = texture(gNormal, texc).rgb;
    vec3 Albedo = texture(gAlbedoSpec, texc).rgb;
//    float AmbientOcclusion = texture(ssaoColor, texc).r;
    float AmbientOcclusion = 1.0f;
    // this is for no texture mode
//    vec3 Albedo = vec3(1);
    float shininess = texture(gAlbedoSpec, texc).a;

    // then calculate lighting as usual
    vec3 lighting = Albedo*0.2*AmbientOcclusion; // hard-coded ambient component

    if (useLighting) {
        for (int i = 0; i < lightCount; i++) {
            vec3 vertexToLight = vec3(0);
            // Point Light
            if (lightTypes[i] == 0) {
                vertexToLight = normalize(lightPositions[i] - FragPos);
            } else if (lightTypes[i] == 1) { // Dir Light
                vertexToLight = normalize(-lightDirections[i]);
            }

            float distance = length(lightPositions[i] - FragPos);
            float atten = min(1 / (lightAttenuations[i].x
                                   + lightAttenuations[i].y * distance
                                   + lightAttenuations[i].y * pow(distance, 2)), 1);
//            float atten = min(1, 1 / distance);
            // Add diffuse component
            float diffuseIntensity = max(0.0, dot(vertexToLight, Normal));
            if (lightTypes[i] == 0) { // only attenuates point lights
                diffuseIntensity = diffuseIntensity * atten;
            }
            lighting += max(vec3(0), lightColors[i] * Albedo * diffuseIntensity);

            // Add specular component
            vec3 lightReflection = normalize(reflect(-vertexToLight, normalize(Normal)));
            vec3 eyeDirection = normalize((inverse(v) * vec4(0,0,0,1) - vec4(FragPos, 1.0)).xyz);
            float specIntensity = 0.3 * pow(max(0.0, dot(eyeDirection, lightReflection)), shininess);
            if (lightTypes[i] == 0) { // only attenuates point lights
                specIntensity = specIntensity * atten;
            }
            lighting += max (vec3(0), lightColors[i] * Albedo * specIntensity);
        }
    }
    lighting = clamp(lighting, vec3(0), vec3(1));
    FragColor = vec4(lighting, 1.0);
//    FragColor = vec4(AmbientOcclusion);

}



//#version 330 core

//in vec2 texCoord;

//uniform sampler2D positionBuffer;
//uniform sampler2D normalBuffer;

//uniform vec3 lightDir = normalize( vec3( -1.0, -1.0, -1.0 ) );

//out vec3 out_diffuse;
//out vec3 out_specular;

//vec3 unpack( vec3 v )
//{
//    return v*vec3( 2.0 ) - vec3( 1.0 );
//}

//void main()
//{
//    vec3 geometryCameraSpacePosition = unpack( texture2D( positionBuffer, texCoord ).xyz );
//    vec4 geometryCameraSpaceNormal4 = texture2D( normalBuffer, texCoord );

//    vec3 csNormal = unpack( geometryCameraSpaceNormal4.xyz );
//    vec3 csPosition = unpack( geometryCameraSpacePosition );
//    float shininess = geometryCameraSpaceNormal4.w;

//    // Render diffuse

//    float ndotl = max( dot( -lightDir, csNormal ), 0.0 );
////    out_diffuse = vec3(  ndotl );

//    vec3 r = reflect( -lightDir, csNormal );
//    vec3 v = normalize( csPosition );
//    float rdotv = dot( r, v );

//    out_specular = vec3( pow( rdotv, shininess ) );
//    out_diffuse = out_specular;
//    // Render specular


//}
