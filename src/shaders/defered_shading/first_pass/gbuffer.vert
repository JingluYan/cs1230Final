#version 330 core

layout(location = 0) in vec3 position; // Position of the vertex
layout(location = 1) in vec3 normal;   // Normal of the vertex
layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 binormal;
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

out vec4 pos_cam;
out vec4 normal_cam;
out vec4 tangent_cam;
out vec4 binormal_cam;
out vec4 pos_world;
out vec4 normal_world;
out vec2 texc;
out vec3 color;

void main()
{
    texc = texCoord;

    vec4 pos_cam_vec4 = v * m * vec4( position, 1.0 );
    gl_Position = p * pos_cam_vec4;

    //cam space pos and normal
    normal_cam = normalize( vec4(mat3(transpose(inverse(v * m))) * normal, 0.0) );
    pos_cam = pos_cam_vec4;
    tangent_cam = vec4(normalize(mat3(transpose(inverse(v * m))) * tangent), 0);
    binormal_cam = vec4(normalize(mat3(transpose(inverse(v * m))) * binormal), 0);

    //world space pos and normal
    pos_world = m * vec4(position, 1.0);
    normal_world = normalize( vec4( mat3(transpose(inverse(m)))*normal, 0.0) );

    color = ambient_color + diffuse_color;
    color = clamp(color, 0.0, 1.0);
}
