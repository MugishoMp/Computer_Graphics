// On linux compile with:
// g++ -std=c++17 main.cpp glad/src/glad.c -I./glad/include -o prog -lSDL2 -ldl
// On windows compile with (if using mingw)
// g++ main.cpp ./glad/src/glad.c -I./glad/include -o prog.exe -lmingw32 -lSDL2main -lSDL2

// C++ Standard Libraries
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

// Third-party library
#include <SDL2/SDL.h>
// Include GLAD
#include <glad/glad.h>
// Include GLM
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>




// VVVVVVVVVVVVVVVVVVVV Globals                 VVVVVVVVVVVVVVVVVVVV
int G_HEIGHT = 480;
int G_WIDTH = 640;

SDL_Window * G_GRAPHICS_APPLICATION_WINDOW = nullptr;
SDL_GLContext G_OPENGL_CONTEXT = nullptr;

bool G_QUIT = false;

// VAO
GLuint G_VERTEX_ARRAY_OBJECT = 0;
// VBO
GLuint G_VERTEX_BUFFER_OBJECT = 0;
//IBO
GLuint G_INDEX_BUFFER_OBJECT = 0;

// Program Object (for our shaders)
GLuint G_GRAPHICS_PIPELINE_SHADER_PROGRAM = 0;

float G_U_OFFSET_X = 0.0f;
float G_U_OFFSET_Y = 0.0f;
// ^^^^^^^^^^^^^^^^^^^^ Globals                 ^^^^^^^^^^^^^^^^^^^^



// VVVVVVVVVVVVVVVVVVVV Error handling Routines VVVVVVVVVVVVVVVVVVVV

static void GLClearAllErrors() {
    while(glGetError() != GL_NO_ERROR) {

    }
}

// Returns true if we have an error
static bool GLCheckErrorStatus(const char* function, int line) {
    while(GLenum error = glGetError()) {
        std::cout << "OpenGl Error: " << error 
                  << "\t Line: " << line
                  << "\t function: " << function 
                  << std::endl;
        return true;
    }
    return false;
}

// google opengl error enumeration codes 
#define GLCheck(x) GLClearAllErrors(); x; GLCheckErrorStatus(#x, __LINE__);
// ^^^^^^^^^^^^^^^^^^^^ Error handling Routines ^^^^^^^^^^^^^^^^^^^^




std::string LoadShaderAsString(const std::string& filename) {
    // resulting shader program as string
    std::string result = "";

    std::string line = "";

    std::ifstream shaderFile(filename.c_str());

    if(shaderFile.is_open()) {
        while(std::getline(shaderFile, line)) {
            result += line + '\n';
        }
        shaderFile.close();
    }

    return result;

}

void VertexSpecifiation() {

    // lives on the cpu
    const std::vector<GLfloat> vertexData {
        // x, y, z

        // 0 - vertex
        -0.5f, -0.5f, 0.0f, // left vertex 1 position
        1.0f, 0.0f, 0.0f, // vertex 1 color
        // 1 - vertex
        0.5f,  -0.5f, 0.0f, // right vertex 2 position
        0.0f, 1.0f, 0.0f, // vertex 2 color
        // 2 - vertex
        -0.5f,   0.5f, 0.0f, // top vertex 3 position
        0.0f, 0.0f, 1.0f, // vertex 3 color
        // 3 - vertex
        0.5f, 0.5f, 0.0f, // top right vertex 1 position
        1.0f, 0.0f, 0.0f, // vertex 1 color

    };

    // now is the question, how do we get this vertex onto 
    // our gpu, in the gpu memory

    // we start setting things up in the cpu
    // in order to create the vertex array object we use
    // glGenVertexArrays.
    // 1 specifies how many VAO's we want 
    // We also need a location where we want to place this
    // VAO, and a common way that OpenGL works with this 
    // is by using an integer that is sortof a handle to 
    // some object.
    glGenVertexArrays(1, &G_VERTEX_ARRAY_OBJECT);
    // once we have one of these objects the next step is
    // to bind to it, (bind is like select, it says like
    // "hey use this one that we just created here")
    glBindVertexArray(G_VERTEX_ARRAY_OBJECT);

    // start generating our vertex buffer object
    // these functions work similart to the previous 
    // previous functions above
    glGenBuffers(1, &G_VERTEX_BUFFER_OBJECT);
    // select that buffer to do things with it
    glBindBuffer(GL_ARRAY_BUFFER, G_VERTEX_BUFFER_OBJECT);
    // put the actual data into the buffer
    glBufferData(GL_ARRAY_BUFFER, 
                vertexData.size() * sizeof(GLfloat),
                vertexData.data(),
                GL_STATIC_DRAW);


    const std::vector<GLuint> indexBufferData {
        // triangle 1
        2,0,1,
        // triangle 2
        3,2,1
    };
    // setup the index buffer object
    glGenBuffers(1, &G_INDEX_BUFFER_OBJECT);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, G_INDEX_BUFFER_OBJECT);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
                indexBufferData.size() * sizeof(GLuint),
                indexBufferData.data(),
                GL_STATIC_DRAW);

    // think of the following
    /**
     * class foo{
     *   public:
     *      Foo();
     *   private:
     *      int height
     * }
    */
    //
    // here we are going to enable an attribute
    // specifically the 0th attribute,
    // this is synonymus with adding an (public 
    // or private) attribute to a class that you
    // just made
    // the "height" part of the statement
    glEnableVertexAttribArray(0);
    // this is similar to specifying the type of 
    // the attribute 
    // the "int" part of the statement, but in this case 
    // a bit more complex function
    glVertexAttribPointer(
        0,
        3, // x,y,z
        GL_FLOAT,
        GL_FALSE,
        sizeof(GL_FLOAT) * 6, // the stride, 
        (void*)0 // starting point
    );

    // settup VAO for second attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1,
        3, // r,g,b
        GL_FLOAT,
        GL_FALSE,
        sizeof(GL_FLOAT) * 6,
        (GLvoid*)(sizeof(GL_FLOAT) * 3)
    );


    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

}

GLuint CompileShader(GLuint type, const std::string& source) {
    GLuint shaderObject;

    // create the shader
    if(type == GL_VERTEX_SHADER){
        shaderObject = glCreateShader(GL_VERTEX_SHADER);
    } else if (type == GL_FRAGMENT_SHADER) {
        shaderObject = glCreateShader(GL_FRAGMENT_SHADER);
    }

    // setup the source code
    const char * src = source.c_str();
    glShaderSource(shaderObject, 1, &src, nullptr);
    // compile it
    glCompileShader(shaderObject);

    // return the shader object
    return shaderObject;
}

GLuint CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {
    GLuint programObject = glCreateProgram();

    GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    // we are basically adding all the components of the pipeline together
    glAttachShader(programObject, vertexShader);
    glAttachShader(programObject, fragmentShader);
    glLinkProgram(programObject);

    // validate our program (pipeline)
    glValidateProgram(programObject);
    //glDetachShader, glDeleteShader
    
    return programObject;

}

void CreateGraphicsPipeline() {
    std::string vertexShaderSource      = LoadShaderAsString("./shaders/vert.glsl");
    std::string fragmentShaderSource    = LoadShaderAsString("./shaders/frag.glsl");

    G_GRAPHICS_PIPELINE_SHADER_PROGRAM = CreateShaderProgram(vertexShaderSource, fragmentShaderSource);
}

// we print this out just so we can see that opengl is working
void GetOpenGLVersionInfo() {
    // glad: header file that will setup opengl functions

    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Shading Language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

void InitializeProgram() {

    // we initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL2 Could not initialize fideo subsystem"
                  << std::endl;
        exit(1);
    }

    // we setup some attributes for the opengl version
    // Before we create our window, specify OpenGL version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    // context that we want to set up for opengl
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,24);

    // created the window
    G_GRAPHICS_APPLICATION_WINDOW = SDL_CreateWindow(
        "OpenGL Window",
        0,
        0,
        G_WIDTH,
        G_HEIGHT,
        SDL_WINDOW_OPENGL);

    if (G_GRAPHICS_APPLICATION_WINDOW == nullptr) {
        std::cout << "SDL_Window was not able to be created"
                  << std::endl;
        exit(1);
    }

    // created the opengl context
    G_OPENGL_CONTEXT = SDL_GL_CreateContext(G_GRAPHICS_APPLICATION_WINDOW);

    if (G_OPENGL_CONTEXT == nullptr) {
        std::cout << "OpenGL context not available"
                  << std::endl;
        exit(1);
    }

    // we set up using the glad library a way have all of those
    // OpenGL functions available to us
    if(!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        std::cout << "glad was not initialized" << std::endl;
        exit(1);
    }

    GetOpenGLVersionInfo();
}

void Input() {
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            std::cout << "Goodbye!" << std::endl;
            G_QUIT = true;
        }
    }

    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_RIGHT]) {
        G_U_OFFSET_X += 0.001f;
        std::cout << "offset x: " << G_U_OFFSET_X << std::endl;
    }
    if (state[SDL_SCANCODE_LEFT]) {
        G_U_OFFSET_X -= 0.001f;
        std::cout << "offset x: " << G_U_OFFSET_X << std::endl;
    }
    if (state[SDL_SCANCODE_UP]) {
        G_U_OFFSET_Y += 0.001f;
        std::cout << "offset y: " << G_U_OFFSET_Y << std::endl;
    }
    if (state[SDL_SCANCODE_DOWN]) {
        G_U_OFFSET_Y -= 0.001f;
        std::cout << "offset y: " << G_U_OFFSET_Y << std::endl;
    }
}

void PreDraw() {
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glViewport(0,0,G_WIDTH, G_HEIGHT);
    glClearColor(1.f, 1.f, 0.f, 1.f);

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glUseProgram(G_GRAPHICS_PIPELINE_SHADER_PROGRAM);

    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(G_U_OFFSET_X, G_U_OFFSET_Y, 0.0f));
    GLint model_matrix_location = glGetUniformLocation(G_GRAPHICS_PIPELINE_SHADER_PROGRAM, "u_model_matrix");

    if (model_matrix_location >= 0) {
        glUniformMatrix4fv(
            model_matrix_location,
            1,
            GL_FALSE,
            &translate[0][0]
        );
    } else {
        std::cout << "Could nt find u_model_matrix" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Draw() {

    GLCheck(glBindVertexArray(G_VERTEX_ARRAY_OBJECT);)
    GLCheck(glBindBuffer(GL_ARRAY_BUFFER, G_VERTEX_BUFFER_OBJECT);)
    // GL_TRIANGLES implies basicaly to sample three element sat a time
    GLCheck(glDrawElements(GL_TRIANGLES, 
                    6, 
                    GL_UNSIGNED_INT, 
                    0);)
    glUseProgram(0);

}

void MainLoop() {

    while (!G_QUIT) {

        // we are handeling input
        Input();

        PreDraw();

        Draw();

        // this is going to update the window, We draw at the back of the screen,
        // and as soon as we finish drawing we send that information to the front 
        // or front buffer then we start drawing something else on the back while
        // the front is displayed to the user and we just keep flipping
        SDL_GL_SwapWindow(G_GRAPHICS_APPLICATION_WINDOW);
    }

}

void CleanUp() {
    SDL_DestroyWindow(G_GRAPHICS_APPLICATION_WINDOW);

    SDL_Quit();
}

int main() {

    // sets up our sdl window and opengl
    InitializeProgram();

    // this is responsible for getting some vertex data on 
    // our gpu
    VertexSpecifiation();

    CreateGraphicsPipeline();

    MainLoop();

    CleanUp();

    return 0;
}