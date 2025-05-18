#version 330 core
//darà in output il colore impostato
out vec4 FragColor;

//ottiene la posizione dal vertex shader
in vec3 crntPos;
//ottiene i normal, che servono per l'illuminazione, dal vertex shader
in vec3 Normal;
//riceve il colore dal vertex shader
in vec3 color;
//riceve le coordinate della texture dal vertex shader
in vec2 TexCoord;
//ottiene l'unsigned int della texture dal main
uniform sampler2D diffuse0;
uniform sampler2D diffuse1;
uniform sampler2D specular0;
//ottiene il colore della luce
uniform vec4 lightColor;
//ottiene la posizione della luce
uniform vec3 lightPos;
//ottiene la posizione della camera
uniform vec3 camPos;

vec4 pointLight()
{
	vec3 lightVec = lightPos - crntPos;

	//intensità della luce in base alla distanza
	float dist = length(lightVec);
	float a = 0.02;
	float b = 0.01;
	float inten = 1.5f / (a * dist * dist + b * dist + 1.0f);

	//luce d'ambiente
	float ambient = 0.1f;
	//calcola la luce diffusa
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	//calcola l'illuminazione speculare
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;
	return ((texture(diffuse0, TexCoord) + texture(diffuse1, TexCoord) + vec4(color, 1.0f)) * (diffuse * inten + ambient) + texture(specular0, TexCoord).r * specular * inten) * lightColor;
}

vec4 direcLight()
{
	//luce d'ambiente
	float ambient = 0.20f;

	//calcola la luce diffusa
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(vec3(0.0f, 1.0f, 0.0f));
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	//calcola l'illuminazione speculare
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return ((texture(diffuse0, TexCoord) + texture(diffuse1, TexCoord) + vec4(color, 1.0f)) * (diffuse + ambient) + texture(specular0, TexCoord).r * specular) * lightColor;
}

vec4 spotLight()
{
	//controlla quanto è grande l'area d'illuminazione
	float outerCone = 0.90f;
	float innerCone = 0.95f;

	//luce d'ambiente
	float ambient = 0.20f;

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

	// calculates the intensity of the crntPos based on its angle to the center of the light cone
	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
	float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	return ((texture(diffuse0, TexCoord) + texture(diffuse1, TexCoord) + vec4(color, 1.0f)) * (diffuse * inten + ambient) + texture(specular0, TexCoord).r * specular * inten) * lightColor;
}

void main()
{
	//texture imposta la texture ricevuta nelle coordinate
	//FragColor imposta il colore del verticè
	FragColor = pointLight();
}