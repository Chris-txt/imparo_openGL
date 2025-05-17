#include "Texture.h"

Texture::Texture(const char* image, GLenum texType, GLuint slot, GLenum format, GLenum pixelType)
{
    //salva il tipo di texture nell'attributo della classe
	type = texType;
    this->unit = slot;
    //crea l'altezza, la larghezza e canali di colori dell'immagine
    int widthImg, heightImg, numColorCh;
    //se non viene messa true l'immagine sarà al contrario perchè openGL la legge dal basso all'alto quando è salvata dall'alto al basso
    stbi_set_flip_vertically_on_load(true);
    //carica l'immagine
    unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColorCh, 0);

    //genera un oggetto texture
    glGenTextures(1, &ID);
    //assegna la texture a un texture unsigned int
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(texType, ID);

    //imposta come verrà disegnata l'immagine: GL_NEAREST=si vedono i pixel, GL_LINEAR=si generano pixel extra e si ha un effetto sfuocato
    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //imposta il modo in cui la texture varrà duplicata se è troppo piccola; vedi tutte le scelta->(https://learnopengl.com/Getting-started/Textures)
    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    //assegna l'immagine all'oggetto texture
    glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
    glGenerateMipmap(texType);

    //cancella i dati dell'immagine siccome è già nell'oggetto
    stbi_image_free(bytes);
    glBindTexture(texType, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
    GLuint texUni = glGetUniformLocation(shader.ID, uniform);
    shader.Activate();
    glUniform1i(texUni, unit);
}

void Texture::Bind()
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(type, ID);
}

void Texture::UnBind()
{
    glBindTexture(type, 0);
}

void Texture::Delete()
{
    glDeleteTextures(1, &ID);
}
