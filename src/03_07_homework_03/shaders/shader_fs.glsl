#version 330 core
out vec4 fragColor;
in vec3 ourPos;

void main()
{
    fragColor = vec4(ourPos,1.0);
}