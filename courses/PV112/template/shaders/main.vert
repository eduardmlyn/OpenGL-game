#version 450

layout(binding = 0, std140) uniform Camera {
	mat4 projection;
	mat4 view;
	vec3 position;
} camera;

layout(binding = 1, std140) uniform Light {
	vec4 position;
	vec4 ambient_color;
	vec4 diffuse_color;
	vec4 specular_color;
} light;

layout(binding = 2, std140) uniform Object {
	mat4 model_matrix;
	vec4 ambient_color;
	vec4 diffuse_color;
	vec4 specular_color;
} object;

layout(binding = 5, std140) uniform Fog {
	vec4 color;
	float density;
	// float start;
	// float end;
	// float scale;
} fog;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texture_coordinate;
layout(location = 5) in vec3 color;

layout(location = 0) out vec3 fs_position;
layout(location = 1) out vec3 fs_normal;
layout(location = 2) out vec2 fs_texture_coordinate;
layout(location = 4) out float fog_factor;
layout(location = 5) out vec3 fs_color;

void main()
{
	fs_position = vec3(object.model_matrix * vec4(position, 1.0));
	fs_normal = transpose(inverse(mat3(object.model_matrix))) * normal;
	fs_texture_coordinate = texture_coordinate;
	fs_color = color;

	float LOG2 = 1.442695;
	float fog_frag_coord = length(normalize(position - camera.position)); // TODO change this
	float density_square = fog.density * fog.density;
	float distance_square = fog_frag_coord * fog_frag_coord;
	fog_factor = exp2(-density_square * distance_square * LOG2);
	fog_factor = clamp(fog_factor, 0.0, 1.0);

 	gl_Position = camera.projection * camera.view * object.model_matrix * vec4(position, 1.0);
}
