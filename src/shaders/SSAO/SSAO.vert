#version 330 core

layout(location = 0) in vec2 in_position;
layout(location = 5) in vec2 in_texCoord;

out vec2 TexCoords;


// this is identical to a full screen quad vert shader
void main()
{
    TexCoords = in_texCoord;
    gl_Position = vec4( in_position, 0.0, 1.0 );

}
