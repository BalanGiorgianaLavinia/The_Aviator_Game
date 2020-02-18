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

void main()
{

	vec3 pos = v_position;
	// pos.y += sin(time) * 0.2;
	gl_Position = Projection * View * Model * vec4(pos, 1);
	f_color = color;
}
