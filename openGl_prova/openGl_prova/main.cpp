#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaderClass.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "Texture.h"
#include "Camera.h"

const unsigned int width = 900;
const unsigned int height = 700;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main() {
    //inizializza GLFW
    glfwInit();
    //dire la versione di GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//usare le funzionalità moderne

    //i vertici sono i punti che servono a openGL per creare un punto(pixel)
    //i punti creati verranno usati come per tracciare i lati del triangolo
    //ogni riga contiene i dati di un vertice, i dati vengono definiti dal vertex shader
    //le coordinate di openGL vanno da -1 a 1, lo 0 è il centro della finestra
    GLfloat vertices[] = {
        //cordinate             colori          coordinate texture  riflessi dei raggi
        -5.0f, -5.0f, -5.0f,  1.0f, 0.0f, 0.0f,     0.0f, 0.0f,    0.0f,  0.0f, -1.0f,
         5.0f, -5.0f, -5.0f,  0.0f, 1.0f, 0.0f,     1.0f, 0.0f,    0.0f,  0.0f, -1.0f,
         5.0f,  5.0f, -5.0f,  0.0f, 0.0f, 1.0f,     1.0f, 1.0f,    0.0f,  0.0f, -1.0f,
        -5.0f,  5.0f, -5.0f,  1.0f, 1.0f, 1.0f,     0.0f, 1.0f,    0.0f,  0.0f, -1.0f,

        -5.0f, -5.0f,  5.0f,  1.0f, 0.0f, 0.0f,     0.0f, 0.0f,    0.0f,  0.0f,  1.0f,
         5.0f, -5.0f,  5.0f,  0.0f, 1.0f, 0.0f,     1.0f, 0.0f,    0.0f,  0.0f,  1.0f,
         5.0f,  5.0f,  5.0f,  0.0f, 0.0f, 1.0f,     1.0f, 1.0f,    0.0f,  0.0f,  1.0f,
        -5.0f,  5.0f,  5.0f,  1.0f, 1.0f, 1.0f,     0.0f, 1.0f,    0.0f,  0.0f,  1.0f,

        -5.0f,  5.0f,  5.0f,  1.0f, 0.0f, 0.0f,     1.0f, 0.0f,   -1.0f,  0.0f,  0.0f,
        -5.0f,  5.0f, -5.0f,  0.0f, 1.0f, 0.0f,     1.0f, 1.0f,   -1.0f,  0.0f,  0.0f,
        -5.0f, -5.0f, -5.0f,  0.0f, 0.0f, 1.0f,     0.0f, 1.0f,   -1.0f,  0.0f,  0.0f,
        -5.0f, -5.0f,  5.0f,  1.0f, 1.0f, 1.0f,     0.0f, 0.0f,   -1.0f,  0.0f,  0.0f,

         5.0f,  5.0f,  5.0f,  1.0f, 0.0f, 0.0f,     1.0f, 0.0f,    1.0f,  0.0f,  0.0f,
         5.0f,  5.0f, -5.0f,  0.0f, 1.0f, 0.0f,     1.0f, 1.0f,    1.0f,  0.0f,  0.0f,
         5.0f, -5.0f, -5.0f,  0.0f, 0.0f, 1.0f,     0.0f, 1.0f,    1.0f,  0.0f,  0.0f,
         5.0f, -5.0f,  5.0f,  1.0f, 1.0f, 1.0f,     0.0f, 0.0f,    1.0f,  0.0f,  0.0f,

        -5.0f, -5.0f, -5.0f,  1.0f, 0.0f, 0.0f,     0.0f, 1.0f,    0.0f, -1.0f,  0.0f,
         5.0f, -5.0f, -5.0f,  0.0f, 1.0f, 0.0f,     1.0f, 1.0f,    0.0f, -1.0f,  0.0f,
         5.0f, -5.0f,  5.0f,  0.0f, 0.0f, 1.0f,     1.0f, 0.0f,    0.0f, -1.0f,  0.0f,
        -5.0f, -5.0f,  5.0f,  1.0f, 1.0f, 1.0f,     0.0f, 0.0f,    0.0f, -1.0f,  0.0f,

        -5.0f,  5.0f, -5.0f,  1.0f, 0.0f, 0.0f,     0.0f, 1.0f,    0.0f,  1.0f,  0.0f,
         5.0f,  5.0f, -5.0f,  0.0f, 1.0f, 0.0f,     1.0f, 1.0f,    0.0f,  1.0f,  0.0f,
         5.0f,  5.0f,  5.0f,  0.0f, 0.0f, 1.0f,     1.0f, 0.0f,    0.0f,  1.0f,  0.0f,
        -5.0f,  5.0f,  5.0f,  1.0f, 1.0f, 1.0f,     0.0f, 0.0f,    0.0f,  1.0f,  0.0f
    };

    //se voglio afre 2 triangoli attaccati dovro usare più vertici uguali che sprecano memoria
    //con gli indici posso riutilizzare più vertici per più triagoli
    //i numeri rappresentano la riga del vertice in 'vertices'
    GLuint indices[] = {
        0,1,2,      //primo triangolo
        2,3,0,      //secondo triangolo
        4,5,6,
        6,7,4,
        8,9,10,
        10,11,8,
        12,13,14,
        14,15,12,
        16,17,18,
        18,19,16,
        20,21,22,
        22,23,20
    };

    //coordinate per il blocco di luce
    GLfloat lightVertices[] = {
        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f
    };
    //indici per il blocco di luce
    GLuint lightIndices[] = {
        0, 1, 2,
        0, 2, 3,
        0, 4, 7,
        0, 7, 3,
        3, 7, 6,
        3, 6, 2,
        2, 6, 5,
        2, 5, 1,
        1, 5, 4,
        1, 4, 0,
        4, 5, 6,
        4, 6, 7
    };

    //creare una finestra; largehezza 800, lunghezza 600, e poi il nome
    GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);
    
    if (window == NULL)
    {//chiudi se non riesce a creare la finestra
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    //sputa fuori la finestra
    glfwMakeContextCurrent(window);
    //fa in modo che puoi cambiare la grandezza della finestra
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //carica GLAD
    gladLoadGL();
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {//si ferma se non riesce a caricare GLAD
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    //crea un shader program con vertex shader e fragment shader
    Shader shaderProgram("default.vert", "default.frag");

    //genera un vertex array object e fa il bind
    VAO VAO1;
    VAO1.Bind();
    //genera vertex buffer object a cui dare i vertici
    VBO VBO1(vertices, sizeof(vertices));
    //genera element buffer object a cui dare gli indici
    EBO EBO1(indices, sizeof(indices));

    //collega gli attributi del VBO con VAO
    VAO1.linkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);//posizione
    VAO1.linkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));//colori
    VAO1.linkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));//texture
    VAO1.linkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));//riflessi
    //unbind degli oggetti per evitare di cambiare valore per sbaglio
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    //shadre per il blocco di luce
    Shader lightShader("light.vert", "light.frag");
    //stesso procedimento:
    VAO lightVAO;
    lightVAO.Bind();
    VBO lightVBO(lightVertices, sizeof(lightVertices));
    EBO lightEBO(lightIndices, sizeof(lightIndices));
    lightVAO.linkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);//posizione blocco
    lightVAO.Unbind();
    lightVBO.Unbind();
    lightEBO.Unbind();

    //colore della luce
    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    //posizione del blocco di luce
    glm::vec3 lightPos = glm::vec3(8.0f, 7.0f, 9.0f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);
    //posizione del cubo
    glm::vec3 cubePos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 cubeModel = glm::mat4(1.0f);
    cubeModel = glm::translate(cubeModel, cubePos);
    //usa gli shader della luce
    lightShader.Activate();
    //imposta le uniforme negli shader della luce
    glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    //usa lo shader globale
    shaderProgram.Activate();
    //imposta le uniforme:
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(cubeModel));
    //colore della luce
    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    //posizione del blocco di luce
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

    //Texture:
    Texture slizar("slizar.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture grass("grass.png", GL_TEXTURE_2D, 1, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture grassSpec("Grass_specular.png", 2, GL_TEXTURE2, GL_RED, GL_UNSIGNED_BYTE);
    //invia la texture al shader program e all'unifoem nel fragment shader
    slizar.texUnit(shaderProgram, "texture0", 0);
    grass.texUnit(shaderProgram, "texture1", 1);
    grassSpec.texUnit(shaderProgram, "texture2", 2);

    //fa in modo che openGL renderizzi forme 3d con la loro profondità
    glEnable(GL_DEPTH_TEST);
    //inizializzo l'oggetto per la camera
    Camera camera(width, height, glm::vec3(0.0f, 2.0f, 25.0f));

    //loop di funzioni nel mentre che è aperta la finestra
    while (!glfwWindowShouldClose(window))
    {
        //pulisci lo schermo con un colore nella scala R,G,B e l'ultimo è l'opacità 
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        //pulisce il buffer nascosto e assegna un nuovo colore
        glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);
        //la camera prende in input  la tastiera e si muove in base ai tasti premuti
        camera.Input(window);
        //aggiorna e esporta la matrice della camera al vertex shader
        camera.updateMatrix(50.0f, 0.1f, 200.0f);
        //dì a openGL quale shader program usare
        shaderProgram.Activate();
        //esporta la posizione della camera al fragment shader per l'illuminazione
        glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
        //esporta la matrice della camera al vertex shader del cubo
        camera.Matrix(shaderProgram, "camMatrix");
        //attiva e fa il bind delle texture così si renderizzano
        slizar.Bind();
        grass.Bind();
        grassSpec.Bind();
        //bind del VAO così openGl sa di doverlo usare
        VAO1.Bind();
        //disegna il triangolo con GL_TRIANGLE e specificando quali vertici
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
        //ora usiamo il shader program della luce
        lightShader.Activate();
        //esporta la matrice della camera al vertex shader della luce
        camera.Matrix(lightShader, "camMatrix");
        //Bind del VAO della luce così openGl sa di doverlo usare
        lightVAO.Bind();
        //disegna il cubo che emette luce
        glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
        
        //cambia i buffer
        glfwSwapBuffers(window);
        //controlla per degli eventi
        glfwPollEvents();
    }

    //cancella tutti gli oggetti creati
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    slizar.Delete();
    grass.Delete();
    shaderProgram.Delete();
    //distrugge il programma
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
