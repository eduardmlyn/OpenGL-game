#version 450

layout(binding = 0, std140) uniform Camera {
    mat4 projection;
    mat4 view;
    vec3 position;
}
camera;

struct LightS {
    vec4 position;
    vec4 ambient_color;
    vec4 diffuse_color;
    vec4 specular_color;
};

layout(binding = 1, std140) uniform Light {
    vec4 position;
    vec4 ambient_color;
    vec4 diffuse_color;
    vec4 specular_color;
}
light;

layout(binding = 2, std140) uniform Object {
    mat4 model_matrix;

    vec4 ambient_color;
    vec4 diffuse_color;
    vec4 specular_color;
}
object;

struct ConeLightS {
    vec4 position;
    vec4 ambient_color;
    vec4 diffuse_color;
    vec4 specular_color;
    vec4 direction;
    float angle;
    float attenuation;
    float p1; float p2;
};

layout(binding = 4, std430) buffer ConeLight {
    ConeLightS lights[];
}
coneLight;

layout(binding = 5, std140) uniform Fog {
	vec4 color;
	float density;
	// float start;
	// float end;
	// float scale;
} fog;


layout(binding = 3) uniform sampler2D healer_texture;
layout(binding = 6) uniform sampler3D ogreTexture;

layout(location = 0) in vec3 fs_position;
layout(location = 1) in vec3 fs_normal;
layout(location = 2) in vec2 fs_texture_coordinate;
layout(location = 3) uniform bool has_texture = false;
layout(location = 4) in float fog_factor;
layout(location = 5) in vec3 color;

layout(location = 0) out vec4 final_color;

vec3 CalcLight(LightS light) {
    vec3 light_vector = light.position.xyz - fs_position * light.position.w;
    vec3 L = normalize(light_vector);
    vec3 N = normalize(fs_normal);
    vec3 E = normalize(camera.position - fs_position);
    vec3 H = normalize(L + E);

    float NdotL = max(dot(N, L), 0.0);
    float NdotH = max(dot(N, H), 0.0001);

    vec3 ambient = object.ambient_color.rgb * light.ambient_color.rgb;
    // TODO *color?
    vec3 diffuse = object.diffuse_color.rgb * color *
                   light.diffuse_color.rgb;
    vec3 specular = object.specular_color.rgb * light.specular_color.rgb;

    return NdotL * diffuse.rgb + pow(NdotH, object.specular_color.w) * specular;
}

vec3 CalcConeLight(ConeLightS light) {
    vec3 lightToPixel = normalize(fs_position - light.position.xyz) ;    
    float spot = dot(lightToPixel, light.direction.xyz);
    if (spot > light.angle) {
        LightS l = LightS(light.position, light.ambient_color, light.diffuse_color, light.specular_color);
        // TODO calculate normal light but without the camera's position to make it similar like in swgoh when char is highlited
        vec3 color = CalcLight(l) / light.attenuation;
        float spotIntensity = (1.0 - (1.0 - spot)/(1.0 - light.angle));
        // color = vec3(0, 0, 0);
        return color * spotIntensity;
    }
    else {
        return vec3(0.0);
    }
}

void main() {
    vec3 light_vector = light.position.xyz - fs_position * light.position.w;
    // vec3 color2 = vec3(0);
    
    vec3 color2 = CalcLight(LightS(light.position, light.ambient_color, light.diffuse_color, light.specular_color));
    if (light.position.w == 1.0) {
       color2 /= (dot(light_vector, light_vector));
    }

    for(int i = 0; i < coneLight.lights.length(); i++)
    {
        vec3 coneColor = CalcConeLight(coneLight.lights[i]);
        color2 += coneColor;
    }
    color2 += color;
    

    color2 = color2 / (color2 + 1.0);       // tone mapping
    color2 = pow(color2, vec3(1.0 / 2.2)); // gamma correction

    final_color = mix(fog.color, vec4(color2, 1.0), fog_factor);
    // final_color = vec4(color, 1.0);
}