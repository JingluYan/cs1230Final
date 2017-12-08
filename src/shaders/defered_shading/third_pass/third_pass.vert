#version 330 core

layout(location = 0) in vec3 position; // Position of the vertex
layout(location = 4) in vec2 texCoord; // UV texture coordinates


// Transformation matrices
uniform mat4 p;
uniform mat4 v;
uniform mat4 m;

out vec2 texc;

void main()
{
    texc = texCoord;

    vec4 position_cameraSpace = v * m * vec4(position, 1.0);
    vec4 position_worldSpace = m * vec4(position, 1.0);

    gl_Position = p * position_cameraSpace;
}
