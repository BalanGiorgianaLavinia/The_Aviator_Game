#version 330

layout(location = 0) in vec3 v_position;
layout(location = 3) in vec3 v_color;

out vec3 f_color;
out vec3 frag_normal;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float time;

uniform vec3 color;

float rand(vec2 co)
{
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{

	vec3 pos = v_position;
	
	float x = rand(vec2(pos.x));
	float y = rand(vec2(pos.y));

	pos.x += x * 0.3;
	pos.y += y * 0.3;

	gl_Position = Projection * View * Model * vec4(pos, 1);
	f_color = color;

	if(x > 0.3)
		f_color += vec3(0.1, 0, 0);
	else 
		f_color -= vec3(0.1, 0, 0);
}
