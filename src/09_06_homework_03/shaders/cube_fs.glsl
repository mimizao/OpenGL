#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec3 LampPos;

uniform vec3 cubeColor;
uniform vec3 lampColor;

void main()
{
    //! ambient
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lampColor;

    //! diffuse
    vec3 norm = normalize(Normal);
    vec3 lampDir = normalize(LampPos - FragPos);
    float diff = max(dot(norm, lampDir), 0.0);
    vec3 diffuse = diff * lampColor;

    //! specular
    float specularStrength = 0.5f;
    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lampDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
    vec3 specular = specularStrength * spec * lampColor;

    vec3 result = (ambient + diffuse + specular) * cubeColor;
    FragColor = vec4(result, 1.0);
}