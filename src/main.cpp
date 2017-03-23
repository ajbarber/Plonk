#include "MainGL.h"

static MainGL *toolkit;



int main(int argc, char **argv)
{
	//update();
    toolkit = new MainGL(argc, argv);
    toolkit->run();  
    delete toolkit;
    return 0;
}



