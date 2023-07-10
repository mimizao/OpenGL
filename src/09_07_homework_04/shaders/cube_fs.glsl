#version 330 core
out vec4 FragColor;

in vec3 LightingColor;

uniform vec3 cubeColor;

void main()
{
    FragColor = vec4(LightingColor * cubeColor, 1.0f);
}