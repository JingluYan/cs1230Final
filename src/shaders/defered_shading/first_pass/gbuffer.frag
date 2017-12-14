#version 330 core
layout (location = 0) out vec4 gPosition;
layout (location = 1) out vec4 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;

//vec3 gNormal;
//vec3 gPosition;
//vec4 gAlbedoSpec;

in vec4 pos_cam;
in vec4 normal_cam;
in vec4 pos_world;
in vec4 normal_world;
in vec2 texc;
in vec3 color;

// Material data
uniform float shininess;

//texture data
uniform int useTexture = 0;
uniform sampler2D tex;
uniform vec2 repeatUV;


//out vec4 fragColor;

vec3 pack( vec3 v )
{
    return 0.5 * v + vec3( 0.5 );
}

void main()
{
    vec3 texColor = texture(tex, texc*repeatUV).rgb;
    texColor = clamp(texColor + vec3(1-useTexture), vec3(0), vec3(1));
//    fragColor = vec4(color * texColor, 1);


    // USE CAM space
    // store the fragment position vector in the first gbuffer texture
    gPosition = pos_cam;
    // also store the per-fragment normals into the gbuffer
    gNormal = normalize(normal_cam);

    // USE WORLD space
//    gPosition = pos_world;
//    gNormal = normalize(normal_world);

    // and the diffuse per-fragment color
    gAlbedoSpec.rgb = color * texColor;
    // store specular intensity in gAlbedoSpec's alpha component
//    gAlbedoSpec.a = texture(texture_specular1, TexCoords).r;
    gAlbedoSpec.a = shininess;

}
