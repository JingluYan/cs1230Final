#version 330 core

in vec3 pos_cam;
in vec3 normal_cam;

// Material data
uniform float shininess;

out vec4 out_normal_cam; // w is shininess
out vec3 out_pos_cam;

//out vec4 fragColor;

vec3 pack( vec3 v )
{
    return 0.5 * v + vec3( 0.5 );
}

void main()
{
//    out_pos_cam = pack( pos_cam );
    out_normal_cam = vec4( pack( normal_cam ), 1.0 );//shininess set to 1 for now;
//    fragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
