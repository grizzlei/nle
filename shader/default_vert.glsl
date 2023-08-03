#version 330

out vec4 vertexColor;
out vec2 textureCoordinates;
out vec3 normal;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

uniform int instanced = 0;
uniform vec3 inst_positions[65536];
uniform vec3 inst_rotations[65536];
uniform vec3 inst_scales[65536];

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 norm;
layout (location = 2) in vec2 tex;

void main() {
    if(instanced == 1)
    {
        gl_Position = projection * view * model * vec4(inst_positions[gl_InstanceID], 1);
    }
    else
    {
        gl_Position = projection * view * model * vec4(pos, 1);
    }
    // vertexColor = vec4(0.6f, 0.6f, 0.6f, 1.f);
    vertexColor = vec4(clamp(pos, 0.f, 1.f), 1.f);
    textureCoordinates = tex;
    normal = mat3(transpose(inverse(model))) * norm;
}