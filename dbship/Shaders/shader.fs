#version 330 core
out vec4 FragColor;

in vec3 ourColor;
//in vec3 Normal;  
in vec3 FragPos; 

//uniform vec3 lightPos; 
//uniform vec3 viewPos; 
uniform vec3 lightColor;
//uniform vec3 objectColor;

void main()
{
	float ambientStrength = 11.0;
    vec3 ambient = ambientStrength * vec3(0.1f,0.1f,0.1f);

    vec3 result = ambient * ourColor;
    FragColor = vec4(result, 1.0);
	
    //FragColor = vec4(ourColor, 1.0f);
}