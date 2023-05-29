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

/**
 * @brief 使用GLSL编写着色器
 *
 * @param version 每个着色器都起始于一个版本声明
 * @param core 声明使用核心模式
 * @param in 在顶点着色器中声明所有的输入顶点属性(Input Vertex Attribute)
 * @param Position 目前只关心位置(Position)数据，所以只需要一个顶点属性；
 * @param layout (location = 0) 设定了输入变量的位置值(Location)
 * @param gl_Position 设置顶点着色器的输出，将位置数据赋值给预定义的gl_Position变量，它是vec4类型的；
 * @param vec4 GLSL有一个向量数据类型，它包含1到4个float分量，包含的数量可以从它的后缀数字看出；
 *
 * @note 因为我们输入的是一个3分量的向量，需要把它转换为4分量；可以把vec3的数据作为vec4构造器的参数，同时把w分量设置为1.0f。
 */
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
    /**
     * @brief 将着色器源码附加到着色器对象上，然后编译
     *
     * @param vertexShader 要编译的着色器对象
     * @param int 即这里的1，传递的源码字符串数量
     * @param vertexShaderSource 顶点着色器真正的源码
     * @param nullptr 第四个参数暂时先设置为nullptr
     */
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
    /**
     * @brief 将着色器源码附加到着色器对象上，然后编译
     *
     * @param fragmentShader 要编译的着色器对象
     * @param int 1 传递的源码字符串数量
     * @param fragmentShaderSource 顶点着色器真正的源码
     * @param nullptr 第四个参数暂时先设置为nullptr
     */
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
    //! 在着色器对象链接到程序对象以后就可以删除着色器对象
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

    /**
     * @brief 3.1 配置顶点属性
     *
     * @param int  即这里的'0'，要配置的顶点属性。顶点着色器中使用`layout(location = 0)`定义了position顶点属性的位置值(Location)，它可以把顶点属性的位置值设置为`0`。因为希望把数据传递到这一个顶点属性中，所以这里传入`0`；
     * @param int 即这里的'3'，指定顶点属性的大小。顶点属性是一个`vec3`，它由3个值组成，所以大小是3；
     * @param GL_FLOAT 指定数据的类型，这里是GL_FLOAT(GLSL中`vec*`都是由浮点数值组成的)；
     * @param GL_FALSE 是否希望数据被标准化(Normalize)，如果设置为GL_TRUE，所有数据都会被映射到0（对于有符号型signed数据是-1）到1之间；
     * @param size_t 即这里3 * sizeof(float)，这个参数叫做步长(Stride)，为连续的顶点属性组之间的间隔。由于下个组位置数据在3个float之后，这里步长设置为3 * sizeof(float)；
     * @param nullptr 因为参数类型是void*，所以需要进行强制类型转换，它表示位置数据在缓冲中起始位置的偏移量(Offset)。由于位置数据在数组的开头，所以这里是0.
     *
     * @note 关于步长参数，如果知道这个数组是紧密排列的（在两个顶点属性之间没有空隙）也可以设置为0来让OpenGL决定具体步长是多少（只有当数值是紧密排列时才可用）。
     */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) nullptr);
    //! 3.2 将顶点属性位置值作为参数，启用顶点属性
    glEnableVertexAttribArray(0);

    //! 注意：因为上边通过对函数glVertexAttribPointer()的调用已经将VBO注册为了顶点属性所绑定的顶点换成对象，所以之后可以安全的解绑
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //! 注意：不要在VAO处于活动状态时解除绑定EBO，因为绑定的元素缓冲区对象存储在VAO中
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //! 之后可以取消绑定VAO，这样其他VAO调用就不会意外修改此VAO，但这种情况很少发生。修改其他VAO无论如何都需要调用glBindVertexArray，所以通常不会在没有直接必要时解除绑定VAO。
    glBindVertexArray(0);


    /**
     * @brief 通过glPolygonMode函数配置OpenGL如何绘制图元
     *
     * @param GL_FRONT_AND_BACK 应用到所有的三角形的正面和背面
     * @param GL_LINE 使用线框模式
     */
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //! 循环渲染
    while (!glfwWindowShouldClose(window))
    {
        //! 输入
        processInput(window);

        //! 着色器
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //!画第一个三角形
        glUseProgram(shaderProgram);
        //! 其实目前只有一个VAO，实际上是不用每次都绑定的，不过这样做的显然更好
        glBindVertexArray(VAO);
        /**
         * @brief OpenGL所提供的函数，它使用当前激活的着色器，之前定义的顶点属性配置，和VBO的顶点数据(通过VAO间接绑定)来绘制图
         *
         * @param GL_TRIANGLES 准备绘制的OpenGL图元类型，这里准备绘制三角形，所以传递GL_TRIANGLES
         * @param int 即这里的`0`，该参数指定了顶点数组的起始索引
         * @param int 即这里的'3'，该参数指定了准备绘制的顶点数量
         */
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        /**
         * @brief 使用`glDrawElements`函数替换`glDrawArrays`函数进行绘制，当使用`glDrawElements`函数时表示要从索引缓冲区渲染。
         *
         * @param GL_TRIANGLES 准备绘制的OpenGL图元类型，这里准备绘制三角形，所以传递GL_TRIANGLES
         * @param int 即这里的'6'，表示要绘制的顶点的个数，因为这里是把两个三角形都渲染了，所以是6
         * @param GL_UNSIGNED_INT 索引的类型
         * @param nullptr EBO中的偏移量
         */
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        // glBindVertexArray(0); //这里也不需要每次都解绑

        //! glfw：交换缓冲区和轮询 IO 事件（按下释放的键、移动鼠标等）
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //! 可选：一旦资源超出其用途，就取消分配所有资源
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    //! glfw: 终止，清除所有先前分配的 GLFW 资源。
    glfwTerminate();
    return 0;
}

//! 处理所有输入：查询 GLFW 相关键是否在这一帧按下并释放并做出相应反应
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

//! glfw：每当窗口大小发生变化（通过操作系统或用户调整大小）时，此回调函数就会执行
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    //! 确保视口与新窗口尺寸匹配; 注意：在视网膜显示上，宽和高将明显大于所指定值
    glViewport(0, 0, width, height);
}