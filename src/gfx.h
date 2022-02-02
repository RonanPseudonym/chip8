#include <iostream>
#include <GLFW/glfw3.h>

class GFXWindow {
	private:
		GLFWwindow* window;

	public:
		GFXWindow() {
			GLFWwindow* window = glfwCreateWindow(640, 480, "Chip-8", NULL, NULL);
		}
};