#version 330 core

in vec2 texc;

uniform vec2 screenResolution;

// Light data
uniform sampler2D diffuseLightTexture;
uniform sampler2D specularLightTexture;

// Material data
uniform vec3 ambient_color;
uniform vec3 diffuse_color;
uniform vec3 specular_color;
uniform sampler2D tex;
uniform int useTexture = 0;

out vec4 fragColor;

void main()
{
    vec2 screenCoord = ( gl_FragCoord.xy / screenResolution.xy );

    float diffuseLight = texture2D( diffuseLightTexture, screenCoord ).x;
    float specularLight = texture2D( specularLightTexture, screenCoord ).x;

    vec3 texColor = vec3( 1.0 );
//    if( useTexture == 1 )
//    {
//        texColor = texture2D( tex, texc ).xyz;
//        texColor = clamp( texColor + vec3( 1 - useTexture ), vec3( 0 ), vec3( 1 ) );
//    }

    vec3 color = diffuseLight*diffuse_color + specularLight*specular_color + ambient_color;

    fragColor = vec4(color, 1);
}
