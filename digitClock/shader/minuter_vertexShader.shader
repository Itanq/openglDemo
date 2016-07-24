#version 330 core
layout(location=0) in vec3 position;

uniform mat4 trans_minuter;
void main()
{
    gl_Position = trans_minuter * vec4(position, 1.0f);
}
