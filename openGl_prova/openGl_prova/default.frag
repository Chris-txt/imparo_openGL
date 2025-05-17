#version 330 core
//darà in output il colore impostato
out vec4 FragColor;

//riceve il colore dal vertex shader
in vec3 color;
//riceve le coordinate della texture dal vertex shader
in vec2 TexCoord;
//ottiene i normal, che servono per l'illuminazione, dal vertex shader
in vec3 Normal;
//ottiene la posizione dal vertex shader
in vec3 crntPos;
//ottiene l'unsigned int della texture dal main
uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;
//ottiene il colore della luce
uniform vec4 lightColor;
//ottiene la posizione della luce
uniform vec3 lightPos;
//ottiene la posizione della camera
uniform vec3 camPos;

void main()
{
	//luca d'ambiente
	float ambient = 0.10f;
	//calcola la luce diffusa
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	//calcola l'illuminazione speculare
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	//texture imposta la texture ricevuta nelle coordinate
	//FragColor imposta il colore del verticè in base a quello ricevuto e da opacità massima
	FragColor = ((texture(texture0, TexCoord) + texture(texture1, TexCoord) + vec4(color, 1.0f)) * (diffuse + ambient) + texture(texture2, TexCoord).r * specular) * lightColor;
}