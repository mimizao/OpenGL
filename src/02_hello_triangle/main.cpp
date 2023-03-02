/*
顶点数组对象：Vertex Array Object，VAO
顶点缓冲对象：Vertex Buffer Object，VBO
元素缓冲对象：Element Buffer Object，EBO 或 索引缓冲对象 Index Buffer Object，IBO
 */

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

//! settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\n\0";

int main()
{
    //! 初始化和配置GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //! 创建GLFW WINDOW
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "hello_triangle", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //! 通过加载所有OpenGL函数指针
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //! 构建和编译我们的着色器程序
    //! 顶点着色器
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    //! 检查着色器是否编译错误
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //! 片段着色器
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    //! 检查着色器是否编译错误
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //! 链接着色器
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    //! 检查着色器是否链接错误
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //! 设置顶点数据（和缓冲区）并配置顶点属性
    //! 设置顶点数据
    float vertices[] = {
            0.5f, 0.5f, 0.0f,   // 右上角
            0.5f, -0.5f, 0.0f,  // 右下角
            -0.5f, -0.5f, 0.0f, // 左下角
            -0.5f, 0.5f, 0.0f  // 左上角
    };
    //! 设置顶点的索引数据，从0开始
    unsigned int indices[] = {
            0, 1, 3,  // 第一个三角形
            1, 2, 3   // 第二个三角形
    };

    unsigned int VBO, VAO, EBO;
    //! 生成顶点数组对象
    glGenVertexArrays(1, &VAO);
    //! 结合缓冲ID生成顶点缓冲对象
    glGenBuffers(1, &VBO);
    //! 结合缓冲ID生成元素缓冲对象
    glGenBuffers(1, &EBO);

    //! 1 绑定顶点数组对象
    glBindVertexArray(VAO);

    //! 2.1 绑定并设置顶点缓冲对象。OpenGL允许我们同时绑定多个缓冲，只要它们是不同的缓冲类型。这里的VBO的对象为GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //! 将之前定义的顶点数据复制到缓冲的内存中
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //! 2.2 绑定并设置元素缓冲对象，这里的EBO的对象为GL_ELEMENT_ARRAY_BUFFER
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //! 将之前定义的元素索引数据复制到缓冲的内存中
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //! 3 配置顶点属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);

    //! 注意：因为上边通过对函数glVertexAttribPointer()的调用已经将VBO注册为了顶点属性所绑定的顶点换成对象，所以之后我们可以安全的解绑
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //! 注意：不要在VAO处于活动状态时解除绑定EBO，因为绑定的元素缓冲区对象存储在VAO中
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //! 之后您可以取消绑定VAO，这样其他VAO调用就不会意外修改此VAO，但这种情况很少发生。修改其他VAO无论如何都需要调用glBindVertexArray，所以我们通常不会在没有直接必要时解除绑定VAO（也不是 VBO）。
    glBindVertexArray(0);


    //! uncomment this call to draw in wireframe polygons.
    //!glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //! render loop
    while (!glfwWindowShouldClose(window))
    {
        //! input
        processInput(window);

        //! render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //! draw our first triangle
        glUseProgram(shaderProgram);
        //! seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to
        //! keep things a bit more organized
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        //! glBindVertexArray(0); //! no need to unbind it every time

        //! glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //! optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    //! glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

//! process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

//! glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    //! make sure the viewport matches the new window dimensions; note that width and
    //! height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}