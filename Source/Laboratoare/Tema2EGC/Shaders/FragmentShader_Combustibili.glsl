#version 330

// TODO: get values from fragment shader
in vec3 f_color;

layout(location = 0) out vec4 out_color;

void main()
{
	out_color = vec4(f_color, 1);
}