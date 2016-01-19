
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>

// GLEW
#define GLEW_STATIC
#include <glew.h>
// GLFW
#include <glfw3.h>


/** Variables globales et constantes **/
const GLuint WIDTH = 800, HEIGHT = 600;
const std::string path_to_shaders = "./shaders/" ;

GLfloat quad_vertices[] = {
    -1.f, -1.f, 0.0f,
    -1.f,  1.f, 0.0f,
     1.f,  1.f, 0.0f,
     1.f, -1.f, 0.0f
};
GLuint quad_indices[] = {
    0, 1, 2,  // First Triangle
    0, 2, 3   // Second Triangle
};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Simple wrapper to read shader code in file
std::string readShaderFile(const std::string & filename) {
    std::ifstream file(filename, std::ios::in);

    if (!file.is_open()) {
        std::cout << "Erreur : Impossible d'ouvrir '" << filename << "'" << std::endl ;
        return nullptr ;
    }

    std::string code((std::istreambuf_iterator<char>(file)),
                     std::istreambuf_iterator<char>());

    return code ;
}


int main()
{
    /** Initialisation de GLFW
     *  Ouverture de la fenêtre principale **/
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "M1 IG3D - Tutoriel", nullptr, nullptr);
    if (window == nullptr) {

        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();

        return -1;
    }
    glfwMakeContextCurrent(window);


    /** Vérification de la version GLEW **/
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    glViewport(0, 0, WIDTH, HEIGHT);

    /** Définition des fonctions de callbacks **/
    glfwSetKeyCallback(window, key_callback);

    /** Définition des gestionnaires de rendu (shader, program) **/
    // Vertex shader
    GLuint baseVertexShader = glCreateShader(GL_VERTEX_SHADER);
    std::string buff = readShaderFile(path_to_shaders+"base.vert") ;
    const char * vertexShaderSource = buff.c_str();
    glShaderSource(baseVertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(baseVertexShader);
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(baseVertexShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(baseVertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // Fragment shader
    GLuint baseFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    buff = readShaderFile(path_to_shaders+"base.frag") ;
    const char * fragmentShaderSource = buff.c_str();
    glShaderSource(baseFragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(baseFragmentShader);
    glGetShaderiv(baseFragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(baseFragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // Shader program
    GLuint baseShaderProgram = glCreateProgram();
    glAttachShader(baseShaderProgram, baseVertexShader);
    glAttachShader(baseShaderProgram, baseFragmentShader);
    glLinkProgram(baseShaderProgram);
    glGetProgramiv(baseShaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(baseShaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        // WARNING : Si erreur ici, vérifiez que les shaders sont au bon endroit.
    }
    glDeleteShader(baseVertexShader);
    glDeleteShader(baseFragmentShader);


    /** Définition des gestionnaires de mémoire GPU (VAO, VBO) **/
    // VAO
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    // VBO
    GLuint vbos[2] ;
    glGenBuffers(2, vbos);
    glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices), (quad_vertices), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quad_indices), (quad_indices), GL_STATIC_DRAW);
    glBindVertexArray(0);


    /** Boucle de calcul (rendu, physique, etc.) **/
    while(!glfwWindowShouldClose(window)) {

        /** Récupération des évènements et appels de fonctions équivalents **/
        glfwPollEvents();

        /** Effacement de la fenêtre : chaque pixel reçoit la couleur précisée **/
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        /** Utilisation du shader et envoi des données **/
        glUseProgram(baseShaderProgram);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        /** Interversion des tampons mémoire
         *      Image précèdemment affichée (front buffer)
         *      Nouvelle image calculée (back buffer) **/
        glfwSwapBuffers(window);
    }


    /** Fermeture de l'application **/
    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    // When a user presses the escape key, we set the WindowShouldClose property to true,
    // closing the application
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}
