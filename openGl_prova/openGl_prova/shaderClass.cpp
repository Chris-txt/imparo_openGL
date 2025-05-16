#include "shaderClass.h"

std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

    //crea un oggetto vertex shader e usa l'unsigned int come riferimento
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //attacca il source code del vertex shader all'oggetto vertex shader
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    //compila il vertex shader subito erchè il compilatore di c++ non può
    glCompileShader(vertexShader);

    //crea un oggetto fragment shader e usa l'unsigned int come riferimento
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    //attacca il source code del fragment shader all'oggetto vertex shader
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    //compila il fragment shader subito erchè il compilatore di c++ non può
    glCompileShader(fragmentShader);

    //crea un programma unico per le shader e usa l'unsigned int come riferimento
    ID = glCreateProgram();
    //incolla il vertex e fragment shader al programma shader
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);

    //linka tutte le shader insieme in questo programma
    glLinkProgram(ID);

    //ora gli oggetti creati per le vertex e fragment shader sono inutili qundi possono essere cancellati
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
    glUseProgram(ID);
}

void Shader::Delete()
{
    glDeleteProgram(ID);
}
