#version 330 core

in vec2 texCoord;

uniform sampler2D positionBuffer;
uniform sampler2D normalBuffer;

uniform vec3 lightDir = normalize( vec3( -1.0, -1.0, -1.0 ) );

out vec3 out_diffuse;
out vec3 out_specular;

vec3 unpack( vec3 v )
{
    return v*vec3( 2.0 ) - vec3( 1.0 );
}

void main()
{
    vec3 geometryCameraSpacePosition = unpack( texture2D( positionBuffer, texCoord ).xyz );
    vec4 geometryCameraSpaceNormal4 = texture2D( normalBuffer, texCoord );

    vec3 csNormal = unpack( geometryCameraSpaceNormal4.xyz );
    vec3 csPosition = unpack( geometryCameraSpacePosition );
    float shininess = geometryCameraSpaceNormal4.w;

    // Render diffuse

    float ndotl = max( dot( -lightDir, csNormal ), 0.0 );
//    out_diffuse = vec3(  ndotl );

    vec3 r = reflect( -lightDir, csNormal );
    vec3 v = normalize( csPosition );
    float rdotv = dot( r, v );

    out_specular = vec3( pow( rdotv, shininess ) );
    out_diffuse = out_specular;
    // Render specular


}
