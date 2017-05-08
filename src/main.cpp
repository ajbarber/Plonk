#include "gl.h"
#include <SFML/Window.hpp>
#include <chrono>

// Shader sources
/// GLSL vertex shader//////
//	output the final vertex position in device coordinates
/// GLSL //////
const GLchar* vertexSource = R"glsl(
    #version 130
    in vec2 position;
    void main()
    {
        gl_Position = vec4(position, 0.0, 1.0);
    }
)glsl";

/// GLSL vertex shader//////
//	output the final vertex position in device coordinates
/// GLSL //////
const GLchar* unifSource = R"glsl(
    #version 130
	out vec4 outColor;
	uniform vec3 triangleColor;	
	void main()
	{
		outColor = vec4(triangleColor, 1.0);
	}		
)glsl";

/// GLSL fragment shader////// 
//- its mandate is to derive the final colour of a fragment
// by interpolating pixels in a primitive ( these pixels requiring 
// interpolation are called fragments. Here just outputs white all the time
const GLchar* fragmentSource = R"glsl(
    #version 130
    out vec4 outColor;
    void main()
    {
        outColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
)glsl";


int main(int argx, char **argv)
{
	auto t_start = std::chrono::high_resolution_clock::now();
	//sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    //sf::CircleShape shape(100.f);
    //shape.setFillColor(sf::Color::Green);
	sf::ContextSettings settings;
	
	settings.depthBits = 24;
	settings.stencilBits = 8;
	//settings.antialiasingLevel = 2; // Optional

    sf::Window window(sf::VideoMode(800, 600, 32), "OpenGL", sf::Style::Titlebar | sf::Style::Close, settings);
	//sf::Window window(sf::VideoMode(800, 600,32), "OpenGL", sf::Style::Close, settings);
	
	glewExperimental = GL_TRUE;
	glewInit();
	
	
	//Create VAO	
	GLuint vao;
	glGenVertexArrays(1, &vao);	
	glBindVertexArray(vao);
	
	//Create VBO
	GLuint vbo; //pointer to vbo - required to release resource later
	glGenBuffers(1, &vbo); // Generate 1 buffer
		
	float vertices[] = {
		 0.0f,  0.5f, // Vertex 1 (X, Y)
		 0.5f, -0.5f, // Vertex 2 (X, Y)
		-0.5f, -0.5f  // Vertex 3 (X, Y)
	};
	
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo); //make vbo active
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //copy vertex data to buffer
		
	//Create and compile vertex shader	
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);	
	glCompileShader(vertexShader);
	
	/// Logging
	GLint status;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	char buffer[512];
	glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
    fprintf(stderr,buffer);
	
	//Create and compile fragment shader	
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &unifSource, NULL);
	glCompileShader(fragmentShader);
		
	
	//compile shaders into one program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
		
	//specify which output is written to which buffer
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);
		
	//linking vertex data and attributes:
    //about specofying the layout of the vertex data
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");	
	glEnableVertexAttribArray(posAttrib);
	// Specify position is a pair of floats, normalise to -1 - 1 = false,
	// stride: bytes between each position attribute, 
	// offsetL bytes from the start of the array the position attribute occurs;  
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
		
	GLint uniColor = glGetUniformLocation(shaderProgram, "triangleColor");
	//glUniform3f(uniColor, 1.0f, 0.0f, 0.0f);
	
		
	//fprintf(stderr,"%u\n", vbo);
	

    bool running = true;
	while (running)
	{
		sf::Event windowEvent;
		while (window.pollEvent(windowEvent))
		{
			switch (windowEvent.type)
			{
				case sf::Event::Closed:
					running = false;
					break;
				
//				case sf::Event::KeyPressed:
//				if (windowEvent.key.code == sf::Keyboard::Escape)
//					running = false;
//				break;
			}
		}
								
		auto t_now = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
		
		glUniform3f(uniColor, (sin(time * 4.0f) + 1.0f) / 2.0f, 0.0f, 0.0f);
		
		// clear the screen to black
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//t res =glGetError();
		//window.clear();
		
		glDrawArrays(GL_TRIANGLES, 0, 3);
		window.display();

		
					
	}
	glDeleteProgram(shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	glDeleteBuffers(1, &vbo);

	glDeleteVertexArrays(1, &vao);
	
	window.close();

	return 0;

 

	


}


//int main(int argc, char **argv)
//{
//	//update();
//    toolkit = new MainGL(argc, argv);
//    toolkit->run();  
//    delete toolkit;
//    return 0;
//}



