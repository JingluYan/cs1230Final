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
uniform vec3 viewPos;

void main()
{
    // retrieve data from G-buffer
    vec3 FragPos = texture(gPosition, texc).rgb;
    vec3 Normal = texture(gNormal, texc).rgb;
    vec3 Albedo = texture(gAlbedoSpec, texc).rgb;
    float Specular = texture(gAlbedoSpec, texc).a;

    // then calculate lighting as usual
    vec3 lighting = Albedo * 0.1; // hard-coded ambient component
    vec3 viewDir = normalize(viewPos - FragPos);
    for(int i = 0; i < NR_LIGHTS; ++i)
    {
        // diffuse
        vec3 lightDir = normalize(lights[i].Position - FragPos);
        vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Albedo * lights[i].Color;
        lighting += diffuse;
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
