#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <GL/glew.h> // Use GLEW for OpenGL extensions

class ShaderManager {
public:
    // Function to read a shader file
    std::string readShaderFile(const std::string& filePath) {
        std::ifstream file(filePath);
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    // Function to compile a shader from source code
    GLuint compileShader(const std::string& shaderCode, GLenum shaderType) {
        GLuint shader = glCreateShader(shaderType);
        const char* code = shaderCode.c_str();
        glShaderSource(shader, 1, &code, nullptr);
        glCompileShader(shader);

        // Check for compilation errors
        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            GLint logLength;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
            char* log = new char[logLength];
            glGetShaderInfoLog(shader, logLength, &logLength, log);
            std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << log << std::endl;
            delete[] log;
        }

        return shader;
    }

    // Function to create and link a shader program
    GLuint createShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
        // Read shader files
        std::string vertexCode = readShaderFile(vertexShaderPath);
        std::string fragmentCode = readShaderFile(fragmentShaderPath);

        // Compile shaders
        GLuint vertexShader = compileShader(vertexCode, GL_VERTEX_SHADER);
        GLuint fragmentShader = compileShader(fragmentCode, GL_FRAGMENT_SHADER);

        // Create shader program
        GLuint shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        // Check for linking errors
        GLint success;
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            GLint logLength;
            glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &logLength);
            char* log = new char[logLength];
            glGetProgramInfoLog(shaderProgram, logLength, &logLength, log);
            std::cerr << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << log << std::endl;
            delete[] log;
        }

        return shaderProgram;
    }
};

int main() {
    ShaderManager shaderManager;

    // Create shader program
    GLuint shaderProgram = shaderManager.createShaderProgram("assets/shaders/vertex/basic.vert", 
                                                            "assets/shaders/fragment/basic.frag");

    // Use the shader program in the render loop
    glUseProgram(shaderProgram);

    return 0;
}