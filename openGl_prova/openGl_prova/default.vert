#version 330 core
//i primi 3 valori in una riga dei vertici verranno usati per le cordinate
layout (location = 0) in vec3 aPos;
//i 3 volari che vengono dopo verranno usati per il colore rilasciato dal vertice
layout (location = 1) in vec3 aColor;
//i 2 valori che vengono dopo verranno usati per collocare le coordinate della texture
layout (location = 2) in vec2 aTexCoord;
//gli altri 3 valori verranno usati per i riflessi della luce
layout (location = 3) in vec3 aNormal;

//output dei colori così il frgment shader li può ricervere
out vec3 color;
//output delle coordinate della texture
out vec2 TexCoord;
//output del normal per le superfici da illuminare
out vec3 Normal;
//output della posizione del fragment shader
out vec3 crntPos;
//uniform sono variabili globali che possono essere modificate pure dal main
uniform mat4 camMatrix;
uniform mat4 model;

void main()
{
	//ottiene la posizione del fragment shader
	crntPos = vec3(model * vec4(aPos,1.0f));
	//imposta la posizione del vertice
	gl_Position = camMatrix * vec4(crntPos, 1.0f);
	//il colore che verrà mandato al fragment shader è l'insieme dei dati RGB presi in riferimento
	color = aColor;
	//le coordinate verranno inviate al fragment shader
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	//i normal raccolti dagli indici vengono inviati al fragment shader
	Normal = aNormal;
};