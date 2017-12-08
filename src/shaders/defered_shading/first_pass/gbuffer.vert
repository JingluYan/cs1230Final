#version 330 core

layout(location = 0) in vec3 position; // Position of the vertex
layout(location = 1) in vec3 normal;   // Normal of the vertex

// Transformation matrices
uniform mat4 p;
uniform mat4 v;
uniform mat4 m;
uniform mat3 normalMatrix;

out vec3 pos_cam;
out vec3 normal_cam;

void main()
{
    gl_Position = p * v * m * vec4( position, 1.0 );

    normal_cam = normalMatrix * normal;
    pos_cam = (v * m * vec4( position, 1.0 )).xyz;
}
