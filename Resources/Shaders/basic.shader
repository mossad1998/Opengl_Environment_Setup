#shader vertex
#version 330 core

layout(location = 0) in vec2 position;

uniform vec4 u_position;
void main()
{
	vec4 position_4 = vec4(position, 0.0f, 1.0f);
	gl_Position = position_4 + u_position;
};



#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_color;
void main()
{
	color = u_color;
};
