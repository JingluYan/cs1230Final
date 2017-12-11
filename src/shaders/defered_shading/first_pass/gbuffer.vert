#version 330 core

layout(location = 0) in vec3 position; // Position of the vertex
layout(location = 1) in vec3 normal;   // Normal of the vertex
layout(location = 5) in vec2 texCoord; // UV texture coordinates

// Transformation matrices
uniform mat4 p;
uniform mat4 v;
uniform mat4 m;
//uniform mat3 normalMatrix;

uniform vec2 repeatUV;

uniform vec3 ambient_color;
uniform vec3 diffuse_color;
uniform vec3 specular_color;

out vec3 pos_cam;
out vec3 normal_cam;
out vec3 pos_world;
out vec3 normal_world;
out vec2 texc;
out vec3 color;

void main()
{
    texc = texCoord * repeatUV;

    vec4 pos_cam_vec4 = v * m * vec4( position, 1.0 );
    gl_Position = p * pos_cam_vec4;

    //cam space pos and normal
    normal_cam = normalize(mat3(transpose(inverse(v * m))) * normal);
    pos_cam = pos_cam_vec4.xyz;

    //world space pos and normal
    vec4 pos_world_vec4 = m * vec4(position, 1.0);
    pos_world = pos_world_vec4.xyz;
    normal_world = normalize(mat3(transpose(inverse(m))) * normal);

    color = ambient_color + diffuse_color;
}
