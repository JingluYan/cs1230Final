#version 330 core
out vec4 FragColor;

in vec2 texc;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;

struct Light {
    vec3 Position;
    vec3 Color;
};
const int NR_LIGHTS = 32;
uniform Light lights[NR_LIGHTS];
uniform mat4 v;

// Light data
const int MAX_LIGHTS = 30;
uniform int lightTypes[MAX_LIGHTS];         // 0 for point, 1 for directional
uniform vec3 lightPositions[MAX_LIGHTS];    // For point lights
uniform vec3 lightDirections[MAX_LIGHTS];   // For directional lights
//uniform vec3 lightAttenuations[MAX_LIGHTS]; // Constant, linear, and quadratic term
uniform vec3 lightColors[MAX_LIGHTS];

// Material data
uniform float shininess;
uniform vec2 repeatUV;

uniform bool useLighting;     // Whether to calculate lighting using lighting equation


void main()
{
    // retrieve data from G-buffer
    vec3 FragPos = texture(gPosition, texc).rgb;
    vec3 Normal = texture(gNormal, texc).rgb;
    vec3 Albedo = texture(gAlbedoSpec, texc).rgb;
    float Specular = texture(gAlbedoSpec, texc).a;

    // then calculate lighting as usual
    vec3 lighting = Albedo * 0.08; // hard-coded ambient component
    //transform the viewPos from cam space to world space
//    vec3 viewPos = (inverse(v) * vec4(0.0, 0.0, 0.0, 1.0)).xyz;
//    vec3 viewDir = normalize(viewPos - FragPos);
//    for(int i = 0; i < NR_LIGHTS; ++i)
//    {
//        // diffuse
//        vec3 lightDir = normalize(lights[i].Position - FragPos);
//        vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Albedo * lights[i].Color;
//        lighting += diffuse;
//    }

    vec4 normal_cam = v*vec4(Normal, 0);
    vec4 pos_cam = v*vec4(FragPos, 1);
    if (useLighting) {
//        FragColor = vec4(1.0, 0.0, 0.0, 0.0);
        for (int i = 0; i < MAX_LIGHTS; i++) {
            vec4 vertexToLight = vec4(0);
            // Point Light
            if (lightTypes[i] == 0) {
                vertexToLight = normalize(v * vec4(lightPositions[i], 1) - pos_cam);
            } else if (lightTypes[i] == 1) { // Dir Light
                vertexToLight = normalize(v * vec4(-lightDirections[i], 0));
            }

            // Add diffuse component
            float diffuseIntensity = max(0.0, dot(vertexToLight, normal_cam));
            lighting += max(vec3(0), lightColors[i] * Albedo * diffuseIntensity);

//            // Add specular component
//            vec4 lightReflection = normalize(-reflect(vertexToLight, normal_cam));
//            vec4 eyeDirection = normalize(vec4(0,0,0,1) - pos_cam);
//            float specIntensity = pow(max(0.0, dot(eyeDirection, lightReflection)), shininess);
//            lighting += max (vec3(0), lightColors[i] * specular_color * specIntensity);
        }
    }

    FragColor = vec4(lighting, 1.0);
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
