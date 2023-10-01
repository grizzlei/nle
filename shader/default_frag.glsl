#version 330

in vec4 io_vertex_color;
in vec2 io_texture_coordinates;
in vec3 io_normal;
in vec3 io_frag_position;

out vec4 io_color;

struct DirectionalLight
{
    vec3 color;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 direction;
};

struct Material
{
    float shininess;
    float dissolve;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Sky
{
    int distance_fog_enabled;
    float distance_fog_near;
    float distance_fog_far;
};

uniform int u_lighting_enabled = 1;
uniform int u_texture_enabled = 1;
uniform int u_fog_enabled = 1;
uniform sampler2D u_texture_0;
uniform DirectionalLight u_directional_light;
uniform Material u_material;
uniform Sky u_sky;
uniform vec3 u_eye_position;

float map(float value, float min1, float max1, float min2, float max2) {
  return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

vec4 fog_factor() {
    vec3 dist = u_eye_position - io_frag_position;
    float fog_factor = (distance(u_eye_position, io_frag_position) - u_sky.distance_fog_near) / (u_sky.distance_fog_far - u_sky.distance_fog_near);
    fog_factor = clamp(fog_factor, 0.0, 1.0);
    return vec4(fog_factor);
}

void main() {

    vec4 light_factor = vec4(1.f);
    vec3 view_direction = normalize(u_eye_position - io_frag_position);
    vec3 refl = reflect(view_direction, normalize(io_normal));
    // io_color = vec4(texture(u_sky_sampler, refl).rgb, 1.0);

    if(u_lighting_enabled == 1)
    {
        vec3 norm = normalize(io_normal);
        // ambient
        vec3 ambient = u_directional_light.color * u_material.ambient;
        // diffuse
        float diffuse_factor = max(dot(norm, u_directional_light.direction), 0.0f);
        vec3 diffuse = u_material.diffuse * u_directional_light.diffuse * diffuse_factor;
        // specular
        vec3 reflect_direction = reflect(-u_directional_light.direction, norm);
        float specular_factor = pow(max(dot(view_direction, reflect_direction), 0.0f), u_material.shininess);
        vec3 specular = u_material.specular * u_directional_light.specular * specular_factor;
        

        light_factor = vec4((ambient + diffuse + specular), 1.0f);
    }

    if(u_texture_enabled == 1)
    {
        io_color = texture(u_texture_0, io_texture_coordinates) * light_factor;
    }
    else
    {
        io_color = io_vertex_color * light_factor;
    }

    // io_color = gl_FragColor * (1.0 - u_material.dissolve) + io_color * (u_material.dissolve);
    if(u_sky.distance_fog_enabled == 1)
    {
        io_color.a = u_material.dissolve;
        io_color += fog_factor();
    }
}