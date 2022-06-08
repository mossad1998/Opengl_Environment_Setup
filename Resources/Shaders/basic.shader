#shader vertex
#version 330 core

layout(location = 0) in vec2 position;

uniform vec4 u_transformation_matrix;
void main()
{
	vec4 position_4 = vec4(position, 0.0, 1.0);
	gl_Position = u_transformation_matrix + position_4;
};



#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_color;
void main()
{
	color = u_color;
};
