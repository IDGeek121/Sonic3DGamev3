#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "renderEngine.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void window_close_callback(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

extern int gameState;

GLFWwindow* window;

int createDisplay()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
	#endif

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	monitor = NULL; //comment this out to go fullscreen

					// glfw window creation
					// --------------------
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", monitor, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetWindowCloseCallback(window, window_close_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	std::fprintf(stdout, "Renderer:       %s\n", glGetString(GL_RENDERER));
	std::fprintf(stdout, "OpenGL version: %s\n", glGetString(GL_VERSION));
	std::fprintf(stdout, "GLSL version:   %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	glfwSwapInterval(1); //1 = vsync. 0 = off. 2 = half monitor refresh rate
	//glEnable(GL_MULTISAMPLE);

	return 0;
}

void updateDisplay()
{
	// glfw: swap buffers
	// -------------------------------------------------------------------------------
	glfwSwapBuffers(window);
}

void closeDisplay()
{
	glfwDestroyWindow(window);
	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
}

int displayWantsToClose()
{
	return glfwWindowShouldClose(window);
}

GLFWwindow* getWindow()
{
	return window;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void window_close_callback(GLFWwindow* window)
{
	gameState = 1;
}