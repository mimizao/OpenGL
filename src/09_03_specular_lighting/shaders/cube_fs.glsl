#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;

uniform vec3 cubeColor;
uniform vec3 lampColor;
uniform vec3 lampPos;
uniform vec3 viewPos;

void main()
{
    //! ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lampColor;

    //! diffuse
    vec3 norm = normalize(Normal);
    vec3 lampDir = normalize(lampPos - FragPos);
    float diff = max(dot(norm, lampDir), 0.0);
    vec3 diffuse = diff * lampColor;

    //! specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lampDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
    vec3 specular = specularStrength * spec * lampColor;

    vec3 result = (ambient + diffuse + specular) * cubeColor;
    FragColor = vec4(result, 1.0);
}