#include "Mesh.h"

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
    Vertex vertices[] = {
        //                      cordinate               colori                          normals                 coordinate texture
        Vertex{glm::vec3(-5.0f, -5.0f, -5.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3( 5.0f, -5.0f, -5.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(1.0f, 0.0f)},
        Vertex{glm::vec3( 5.0f,  5.0f, -5.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(1.0f, 1.0f)},
        Vertex{glm::vec3(-5.0f,  5.0f, -5.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(0.0f, 1.0f)},

        Vertex{glm::vec3(-5.0f, -5.0f,  5.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3( 5.0f, -5.0f,  5.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(1.0f, 0.0f)},
        Vertex{glm::vec3( 5.0f,  5.0f,  5.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(1.0f, 1.0f)},
        Vertex{glm::vec3(-5.0f,  5.0f,  5.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(0.0f, 1.0f)},

        Vertex{glm::vec3(-5.0f,  5.0f,  5.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(1.0f, 0.0f)},
        Vertex{glm::vec3(-5.0f,  5.0f, -5.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(1.0f, 1.0f)},
        Vertex{glm::vec3(-5.0f, -5.0f, -5.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 1.0f)},
        Vertex{glm::vec3(-5.0f, -5.0f,  5.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 0.0f)},

        Vertex{glm::vec3( 5.0f,  5.0f,  5.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(1.0f, 0.0f)},
        Vertex{glm::vec3( 5.0f,  5.0f, -5.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(1.0f, 1.0f)},
        Vertex{glm::vec3( 5.0f, -5.0f, -5.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 1.0f)},
        Vertex{glm::vec3( 5.0f, -5.0f,  5.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 0.0f)},

        Vertex{glm::vec3(-5.0f, -5.0f, -5.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(0.0f, 1.0f)},
        Vertex{glm::vec3( 5.0f, -5.0f, -5.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(1.0f, 1.0f)},
        Vertex{glm::vec3( 5.0f, -5.0f,  5.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(1.0f, 0.0f)},
        Vertex{glm::vec3(-5.0f, -5.0f,  5.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(0.0f, 0.0f)},

        Vertex{glm::vec3(-5.0f,  5.0f, -5.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec2(0.0f, 1.0f)},
        Vertex{glm::vec3( 5.0f,  5.0f, -5.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec2(1.0f, 1.0f)},
        Vertex{glm::vec3( 5.0f,  5.0f,  5.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec2(1.0f, 0.0f)},
        Vertex{glm::vec3(-5.0f,  5.0f,  5.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec2(0.0f, 0.0f)}
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
    Vertex lightVertices[] = {
        Vertex{glm::vec3(-1.0f, -1.0f,  1.0f)},
        Vertex{glm::vec3(-1.0f, -1.0f, -1.0f)},
        Vertex{glm::vec3( 1.0f, -1.0f, -1.0f)},
        Vertex{glm::vec3( 1.0f, -1.0f,  1.0f)},
        Vertex{glm::vec3(-1.0f,  1.0f,  1.0f)},
        Vertex{glm::vec3(-1.0f,  1.0f, -1.0f)},
        Vertex{glm::vec3( 1.0f,  1.0f, -1.0f)},
        Vertex{glm::vec3( 1.0f,  1.0f,  1.0f)}
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

    Texture textures[]{
        Texture("slizar.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
        Texture("grass.png", "diffuse", 1, GL_RGBA, GL_UNSIGNED_BYTE),
        Texture("Grass_specular.png","specular",2,GL_RED,GL_UNSIGNED_BYTE)
    };

    //crea un shader program con vertex shader e fragment shader
    Shader shaderProgram("default.vert", "default.frag");
    //dati per creare il mesh
    std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
    std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
    std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
    //crea il mesh del cubo
    Mesh cubo(verts, ind, tex);

    //shadre per il blocco di luce
    Shader lightShader("light.vert", "light.frag");
    //stesso procedimento:
    //dati per crare il mesh
    std::vector <Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
    std::vector <GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
    //mesh del blocco di luce
    Mesh light(lightVerts, lightInd, tex);

    //colore della luce
    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    //posizione del blocco di luce
    glm::vec3 lightPos = glm::vec3(2.5f, 8.0f, 10.0f);
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
        //disegna i mesh
        cubo.Draw(shaderProgram, camera);
        light.Draw(lightShader, camera);
        
        //cambia i buffer
        glfwSwapBuffers(window);
        //controlla per degli eventi
        glfwPollEvents();
    }

    //cancella tutti gli oggetti creati
    shaderProgram.Delete();
    lightShader.Delete();
    //distrugge il programma
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
