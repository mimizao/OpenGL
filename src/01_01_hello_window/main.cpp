//! 注意：在包含GLFW的头文件之前包含了GLAD的头文件。GLAD的头文件包含了正确的OpenGL头文件（例如GL/gl.h），所以需要在其它依赖于OpenGL的头文件之前包含GLAD。
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

//! 设置
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    //! 初始化GLFW
    glfwInit();
    //! 配置GLFW，GLFW_CONTEXT_VERSION_MAJOR代表选项的名称，可以从很多以GLFW_开头的枚举值中选择;第二个参数接受一个整型，用来设置这个选项的值，详细可见GLFW’s window handling这篇文档。
    //! 本次学习是基于OpenGL3.3版本，所以主版本和小版本都为3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //! 使用的是核心模式
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //! 创建一个窗口对象，这个窗口对象存放了所有和窗口相关的数据
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "hello window", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    //! 通知GLFW将此窗口的上下文设置为当前线程的主上下文
    glfwMakeContextCurrent(window);

    //! 注册回调函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //! 初始化GLAD，给GLAD传入了用来加载系统相关的OpenGL函数指针地址的函数，这里就是GLFW给我们的glfwGetProcAddress函数
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //! 循环渲染
    while (!glfwWindowShouldClose(window))
    {
        //! 在渲染循环的每一个迭代中调用processInput检测输入
        processInput(window);

        //! 渲染指令
        //! 设置清除缓冲的颜色
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        //! 清除颜色缓冲，整个颜色缓冲都会被填充为glClearColor里所设置的颜色
        glClear(GL_COLOR_BUFFER_BIT);

        //!  检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置），就是上面的glfwSetFramebufferSizeCallback->framebuffer_size_callback->glViewport这一套流程
        glfwPollEvents();
        //! 交换颜色缓冲（这是一个储存着GLFW窗口每一个像素颜色值的大缓冲），在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上
        glfwSwapBuffers(window);
    }

    //! 当渲染循环结束后需要正确释放/删除之前的分配的所有资源
    glfwTerminate();
    return 0;
}

//! 处理所有输入，查询 GLFW 相关键是否在这一帧按下并释放并做出相应反应
void processInput(GLFWwindow *window)
{
    //! glfwGetKey入参为一个窗口和一个按键，返回这个按键是否正在被按下
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        //! 把WindowShouldClose属性设置为true的方法关闭GLFW
        glfwSetWindowShouldClose(window, true);
    }
}

//! 注册以下回调函数，设置GLFW每当窗口调整大小的时候调用
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    //! 设置OpenGL渲染窗口的尺寸大小，即视口(Viewport)；之后OpenGL根据设置显示数据和坐标
    glViewport(0, 0, width, height);
}