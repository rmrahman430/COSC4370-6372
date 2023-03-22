
#version 330 core
out vec4 color;

in vec3 FragPos;  
in vec3 Normal;  
  
uniform vec3 lightPos; 
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
    // TODO: Replace with your code...
    // If gl_Position was set correctly, this gives a totally red cube
    color = vec4(vec3(1.f,0.f,0.f), 1.0f);

  vec3 ambient = 0.1 * objectColor;

    // Calculate the diffuse color
  vec3 lightDir = normalize(lightPos - FragPos);
  float diff = max(dot(Normal, lightDir), 0.0);
  vec3 diffuse = diff * lightColor;

    // Calculate the specular color
  vec3 viewDir = normalize(viewPos - FragPos);
  vec3 reflectDir = reflect(-lightDir, Normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
  vec3 specular = spec * lightColor;

    // Combine the ambient, diffuse, and specular colors
  vec3 result = (ambient + diffuse + specular) * objectColor;

    // Set the output color
  color = vec4(result, 1.0);

} 
