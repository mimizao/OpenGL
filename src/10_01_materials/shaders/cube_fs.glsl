#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;

uniform vec3 lampColor;
uniform vec3 lampPos;
uniform vec3 viewPos;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;

void main()
{
    //! ambient
    vec3 ambient = lampColor * material.ambient;

    //! diffuse
    vec3 norm = normalize(Normal);
    vec3 lampDir = normalize(lampPos - FragPos);
    float diff = max(dot(norm, lampDir), 0.0);
    vec3 diffuse = lampColor * (diff * material.diffuse);

    //! specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lampDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = lampColor * (spec * material.specular);

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}