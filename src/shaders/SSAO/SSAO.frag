#version 330 core

out float FragColor;

in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D texNoise;

uniform vec3 samples[25];
uniform int width;
uniform int height;

// parameters (you'd probably want to use them as uniforms to more easily tweak the effect)
int kernelSize = 25;
uniform float radius = 1.0;
uniform float bias = 0.025;


// tile noise texture over screen based on screen dimensions divided by noise size
vec2 noiseScale = vec2(width/4.0, height/4.0);

uniform mat4 projection;
uniform mat4 v;

void main()
{
    // get input for SSAO algorithm
    vec3 fragPos = texture(gPosition, TexCoords).xyz;
    vec3 normal = normalize(texture(gNormal, TexCoords).rgb);
    vec3 randomVec = normalize(texture(texNoise, TexCoords * noiseScale).xyz);
    // create TBN change-of-basis matrix: from tangent-space to view-space
    vec3 tangent = normalize(randomVec - normal * dot(randomVec, normal));
    vec3 bitangent = cross(normal, tangent);
    mat3 TBN = mat3(tangent, bitangent, normal);
    // iterate over the sample kernel and calculate occlusion factor
    float occlusion = 0.0;
    for(int i = 0; i < kernelSize; ++i)
    {
        // get sample position
        vec3 sample_pos_view = TBN * samples[i]; // from tangent to view-space
        sample_pos_view = fragPos + sample_pos_view * radius;

        // project sample position (to sample texture) (to get position on screen/texture)
        vec4 offset = vec4(sample_pos_view, 1.0);
        offset = projection * offset; // from view to clip-space
        offset.xyz /= offset.w; // perspective divide
        offset.xyz = offset.xyz * 0.5 + 0.5; // transform to range 0.0 - 1.0

        // get sample depth
        float sampleDepth = texture(gPosition, offset.xy).z; // get depth value of kernel sample

        // range check & accumulate
        float rangeCheck = smoothstep(0.0, 1.0, radius / abs(fragPos.z - sampleDepth));
        occlusion += (sampleDepth >= sample_pos_view.z + bias ? 1.0 : 0.0) * rangeCheck;
    }
    occlusion = 1.0 - (occlusion / kernelSize);

    // best parameters: radius 0.4, bias 0.05
    // raise occlussion to an arbitrary power
    if (occlusion < 0.90) {
        occlusion = pow(occlusion, 2);
    }
    FragColor = occlusion;
}
