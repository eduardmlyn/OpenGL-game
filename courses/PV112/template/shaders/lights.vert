#version 450

// ----------------------------------------------------------------------------
// Input Variables
// ----------------------------------------------------------------------------

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
}

// The buffer with data about all lights.
layout(binding = 4, std430) buffer ConeLights {
	ConeLight lights[];
};

// The position of the current vertex that is being processed.
layout(location = 0) in vec3 position;

// ----------------------------------------------------------------------------
// Output Variables
// ----------------------------------------------------------------------------

layout(location = 0) out vec3 fs_position;
layout(location = 1) out vec3 fs_color;
layout(location = 2) out vec3 fs_light_direction;

// ----------------------------------------------------------------------------
// Main Method
// ----------------------------------------------------------------------------
void main()
{
	vec3 light_position = lights[gl_InstanceID].light.position.xyz;

	fs_position = position * 0.5 + light_position;
	fs_color = lights[gl_InstanceID].light.diffuse_color.rgb;

    vec4 light_direction_view = camera.view * lights[gl_InstanceID].direction;
    fs_light_direction = light_direction_view.xyz;
    gl_Position = camera.projection * camera.view * vec4(fs_position, 1.0);
}
