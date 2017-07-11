#include "MainGL.h"

MainGL::MainGL(int argc, char **argv)
{
    	
}

MainGL::~MainGL()
{	
}

int main(int argx, char **argv)
{
	
    sf::ContextSettings settings;
	
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.majorVersion = 3;
    settings.minorVersion = 3;

    //settings.antialiasingLevel = 2; // Optional

    sf::Window window(sf::VideoMode(1024, 768, 32), "OpenGL", sf::Style::Titlebar | sf::Style::Close, settings);
    //sf::Window window(sf::VideoMode(800, 600,32), "OpenGL", sf::Style::Close, settings);


    glViewport (0, 0, (GLsizei) 1024, (GLsizei) 768);
    glewExperimental = GL_TRUE;

    GLenum err = glewInit();

        if (GLEW_OK != err)	{
            cerr<<"Error: "<<glewGetErrorString(err)<<endl;
        } else {
            if (GLEW_VERSION_3_3)
            {
                cout<<"Driver supports OpenGL 3.3\nDetails:"<<endl;
            }
        }
        err = glGetError(); //this is to ignore INVALID ENUM error 1282
        GL_CHECK_ERRORS



				

	
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

                case sf::Event::Resized:
                    World::getInstance()->resize(windowEvent.size.width, windowEvent.size.height);
                    break;

                case sf::Event::MouseMoved:
                    World::getInstance()->mouseMove(windowEvent.mouseMove.x, windowEvent.mouseMove.y);
                    break;

               case sf::Event::MouseButtonPressed:
                    World::getInstance()->mouseClick(windowEvent.mouseButton.button == sf::Mouse::Middle,
                                                     windowEvent.mouseButton.button == sf::Mouse::Right,
                                                     true,
                                                     windowEvent.mouseButton.x,
                                                     windowEvent.mouseButton.y);
                    break;
                case sf::Event::MouseButtonReleased:
                    World::getInstance()->mouseClick(windowEvent.mouseButton.button == sf::Mouse::Middle,
                                                  windowEvent.mouseButton.button == sf::Mouse::Right,
                                                  false,
                                                  windowEvent.mouseButton.x,
                                                  windowEvent.mouseButton.y);
                    break;
                case sf::Event::MouseWheelMoved:
                    World::getInstance()->onMouseWheel(windowEvent.mouseWheel.delta>0 ? 1 :0 );
                case sf::Event::KeyPressed:
                if (windowEvent.key.code == sf::Keyboard::Escape)
                    running = false;
                break;
            }
        }

        float time = World::getInstance()->getTime();

        World::getInstance()->render(time);

        //World::getInstance()->renderAnimation();

        window.display();
    }
}




bool MainGL::checkErrors()
{
	bool retVal = false;
	GLenum	gl_error;

	//-- Check for GL errors
	gl_error = glGetError( );
	if( gl_error != GL_NO_ERROR )
	{
		fprintf(stderr, "ERROR!!! OpenGL error: %s\n", gluErrorString(gl_error) );
		retVal = true;
	}        

	return retVal;
}










