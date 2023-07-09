#version 330 core
out vec4 FragColor;

uniform vec3 cubeColor;
uniform vec3 lampColor;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lampColor;
    vec3 result = ambient * cubeColor;

    FragColor = vec4(result, 1.0);
}