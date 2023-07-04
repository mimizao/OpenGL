#version 330 core
out vec4 FragColor;

uniform vec3 cubeColor;
uniform vec3 lampColor;

void main()
{
    FragColor = vec4(lampColor * cubeColor, 1.0);
}