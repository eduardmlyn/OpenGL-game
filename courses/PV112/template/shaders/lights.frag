#version 450

layout(binding = 0, std140) uniform Camera {
	mat4 projection;
	mat4 view;
	vec3 position;
} camera;

struct Light {
	vec4 position;
	vec4 ambient_color;
	vec4 diffuse_color;
	vec4 specular_color;
};

struct ConeLight {
    Light light;
    vec4 direction;
    float angle;
    float attenuation;
};

// The buffer with data about all lights.
layout(binding = 4, std430) buffer ConeLights {
	ConeLight lights[];
};
// ----------------------------------------------------------------------------
// Input Variables
// ----------------------------------------------------------------------------
layout(location = 0) in vec3 fs_position;
layout(location = 1) in vec3 fs_color;
layout(location = 2) in vec3 fs_light_direction;
layout(location = 3) in flat int instanceID;

// ----------------------------------------------------------------------------
// Output Variables
// ----------------------------------------------------------------------------

// The final output color.
layout(location = 0) out vec4 final_color;

// ----------------------------------------------------------------------------
// Main Method
// ----------------------------------------------------------------------------
void main()
{
    vec3 light_direction = normalize(fs_light_direction);
    vec3 vertex_to_light = normalize(fs_position - camera.position);
    float angle_cosine = dot(-light_direction, vertex_to_light);
    float cone_factor = smoothstep(lights[instanceID].angle, lights[instanceID].angle + 0.1, angle_cosine);

    vec3 diffuse_color = fs_color * cone_factor;

    vec3 result = diffuse_color / (diffuse_color + 1.0); // tone mapping
    result = pow(result, vec3(1.0 / 2.2));     // gamma correction
	final_color = vec4(result, 1.0);
}
