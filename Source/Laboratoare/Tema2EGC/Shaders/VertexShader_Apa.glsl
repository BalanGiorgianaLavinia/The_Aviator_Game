#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 3) in vec3 v_color;

out vec3 f_color;
out vec3 frag_normal;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float time;

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{

	vec3 pos = v_position;
	f_color = vec3(0.1, 0.7, 0.9);

	pos += v_normal * 0.065;
	if(pos.y > 1.3)	pos.y -= 0.1;
	//if(pos.x > 1)	pos.x -= 0.1;

	if(v_normal.x > 0.5 && v_normal.y > 0.5) f_color = vec3(0.1, 0.75, 0.9); 

	if(pos.z > 2 && (pos.x > 0.6 || pos.y > 0.6)) {pos.x = pos.x * 0.5; pos.y *= 0.5;}

	gl_Position = Projection * View * Model * vec4(pos, 1);


	frag_normal = v_normal;
}
