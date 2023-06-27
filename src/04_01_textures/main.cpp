#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif

#include <stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

void framebuffer_size_callback([[maybe_unused]] GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	auto window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "04_01_textures", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	Shader ourShader("../shaders/shader_vs.glsl", "../shaders/shader_fs.glsl");

	float vertices[] = {
			// positions                    // colors                   // texture0 coords
			0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // top right
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // bottom right
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   // bottom left
			-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f    // top left
	};
	unsigned int indices[] = {
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
	};
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) nullptr);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture0 coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// load and create a texture0
	unsigned int texture0;
	glGenTextures(1, &texture0);
	// all upcoming GL_TEXTURE_2D operations now have effect on this texture0 object
	glBindTexture(GL_TEXTURE_2D, texture0);

	/**
	 * @brief 设置纹理坐标轴
	 *
	 * @param GL_TEXTURE_2D 指定纹理目标；
	 * @param GL_TEXTURE_WRAP_S 指定设置的选项与应用的纹理轴，这里配置的是WRAP选项，并且指定S轴；
	 * @param GL_REPEAT 环绕方式
	 */
	// set texture0 wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture0 filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture0 and generate mipmaps
	int width, height, nrChannels;
	/**
	 * @brief 加载图片
	 *
	 * @param filename 文件位置
	 * @param x 图像的宽度
	 * @param y 图像的高度
	 * @param comp 颜色通道的个数
	 */
	stbi_uc *data = stbi_load("../resources/textures/container.jpg",
	                          &width,
	                          &height,
	                          &nrChannels,
	                          0);
	if (data)
	{
		/**
		 * @brief 生成纹理
		 *
		 * @param target GL_TEXTURE_2D纹理目标，与当前绑定的纹理对象的在同一个目标，1D&3D不受影响
		 * @param level 0 多级渐远纹理的级别，这里填0，即基本级别
		 * @param internalformat GL_RGB 希望把纹理储存为何种格式，这里的图片只有RGB，所以设置为RGB
		 * @param width width 最终的纹理宽度
		 * @param height height 最终的纹理高度
		 * @param border 0 历史遗留，直接设置成0即可
		 * @param format GL_RGB 原图的格式，使用RGB值加载这个图像
		 * @param type GL_UNSIGNED_BYTE 原图的数据类型，储存为char(byte)数组
		 * @param pixels data void*类型，真正的图像数据
		 */
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture0" << std::endl;
	}
	stbi_image_free(data);

	/*auto data1 = stbi_load("../resources/textures/awesomeface.png",
						   &width,
						   &height,
						   &nrChannels,
						   0);

	stbi_uc *data2 = stbi_load("../resources/textures/awesomeface.png",
							   &width,
							   &height,
							   &nrChannels,
							   0);

	stbi_image_free(data1);
	stbi_image_free(data2);*/

	// load and create a texture1
	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load("../resources/textures/awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	stbi_image_free(data);
	ourShader.use();
	// 这里的0和1是给采样器设置值，从而确定对应哪个纹理单元，
	// 0的话就对应纹理单元GL_TEXTURE0，1就对应纹理单元GL_TEXTURE1
	glUniform1i(glGetUniformLocation(ourShader.ID, "texture0"), 0);
	ourShader.setInt("texture1", 1);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// bind Texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture1);

		ourShader.use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void framebuffer_size_callback([[maybe_unused]] GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

