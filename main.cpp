#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


void framebuffer_size_callback (GLFWwindow* window, int width, int height){
    glViewport (0,0,width,height);
}
/*void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
} */




//          SOURCE CODE FOR VERTEX AND FRAGMENT SHADERS             //

// Vertex Shader source code
const char* vertexShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
//Fragment Shader source code
const char* fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
        "}\n\0";
const char* BlackfragmentShaderSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);\n"
        "}\n\0";


//          Main Function / Entry Point           //

int main() {

    //          Initialize GLFW         //
    // Tell GLFW OpenGL 4.6 and Core Profile  (ModernFunctions)
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



    //          Vertex Data         //
    // Array of GLfloats that represent vertices
    GLfloat vertices[] = {
            -0.5f, -0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f,
            0.5f, 0.5f, 0.0f,

            0.5f, 0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,

    };
    //black line
    GLfloat linePoints[6] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, 0.5f, 0.0f
    };


    //          Create Window and OpenGL Context + Debug            //
    // GLFWwindow* window creates pointer variable window to GLFWwindow struct
    GLFWwindow* window = glfwCreateWindow(1000, 1000, "LearnOpenGL", nullptr, nullptr);

    // Error debug for window failure
    if (!window) {
        glfwTerminate();
        return -1;
    }
    // Introduce the window we created to the current context
    glfwMakeContextCurrent(window);

    // Load OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -2;
    }




    //          Vertex Buffer Object VBO, Vertex Array Object VAO, and Shaders          //
    //set up vertex shader source code, they do not come by default


    // VERTEX SHADER: Create int variable "vertexShader" of type GL_VERTEX_SHADER using glCreateShader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //connect vertexShader
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // FRAGMENT SHADER: do the same for the fragment Shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    ////////////////////////////////////////////////////////////

    // DUmb Black Line to test if I know my shit
    GLuint BlackfragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(BlackfragmentShader, 1, &BlackfragmentShaderSource, nullptr);
    glCompileShader(BlackfragmentShader);

    GLuint BlackProgram = glCreateProgram();
    glAttachShader(BlackProgram, BlackfragmentShader);
    glAttachShader(BlackProgram, vertexShader);
    glLinkProgram(BlackProgram);
    ///////////////////////////////////////////////////////////////////////////

    // SHADER PROGRAM: creates program object "shaderProgram" to which shaders can be attached
    GLuint shaderProgram = glCreateProgram();

    // Attach vertexShader and fragmentShader to shaderProgram
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // Link attached shaders to shaderProgram
    glLinkProgram(shaderProgram);
    // Delete shaders after attaching and linking
    //glDeleteShader(vertexShader);
    //glDeleteShader(fragmentShader);
    // Vertex Buffer Object


    /// contains buffer data and vertex attribute data which describes how vbo data is laid out
    /// VAO = VBO + VertAttrib
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);


    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(linePoints), nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBufferSubData(GL_ARRAY_BUFFER, 18*sizeof(float), sizeof(linePoints), linePoints);



    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindVertexArray(0);

    // Specify viewport in OpenGL
    //glViewport(0,0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
   // Main while loop
    while(!glfwWindowShouldClose(window))
    {
        //key input
        //processInput(window);

        // set clear color then clear the color buffer
        glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glUseProgram(shaderProgram);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        //glBufferData(GL_ARRAY_BUFFER, sizeof(linePoints), linePoints, GL_STATIC_DRAW);

        glUseProgram(BlackProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_LINES, 6, 2);


        glfwSwapBuffers(window);
        // check and call events
        glfwPollEvents();
    }
    /*
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    */
    glfwTerminate();

    return 0;
}
