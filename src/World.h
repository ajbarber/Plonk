#ifndef World_h
#define World_h

#include "gl.h"
#include <cstdio>
#include <list>
#include <iostream>
#include <chrono>
#include <memory>

#include "Camera.h"
#include "GLSLShader.h"
#include "structs.h"
#include "drawing.h"
#include "AssimpConverter.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "SkeletalModel.h"
#include "SkeletalModelSerializer.h"
#include "drawing.h"
#include "sphere.h"
#include "spheredrawable.h"
#include "cube.h"
#include "cubedrawable.h"
#include "floor.h"
#include "floordrawable.h"
#include "crosshairs.h"
#include "crosshairdrawable.h"
#include "herodrawable.h"
#include "hero.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>


//screen dimensions
const int WIDTH  = 1024;
const int HEIGHT = 768;

//shadowmap texture dimensions
const int SHADOWMAP_WIDTH = 512;
const int SHADOWMAP_HEIGHT = 512;




using namespace std;


class World
{
public: 

	~World();
	
	static World	*init();
	static World	*getInstance();
	static void		destroy();	
    void render();
    void renderAnimation();
    void resize(int w, int h);
    void mouseMove(int x, int y);
    void mouseClick(bool left, bool right, bool down, int x, int y);
    void onMouseWheel(int dir);
	void update();	
	
private:

    std::chrono::system_clock::time_point t_start;

    bool checkErrors();

	static World	*instance;

    //shadowmapping and flat shader
    GLSLShader shader, flatshader;

    std::shared_ptr<GLDrawable> sphereDrawable;
    std::shared_ptr<GLDrawable> cubeDrawable;
    std::shared_ptr<GLDrawable> floorDrawable;
    std::shared_ptr<GLDrawable> crossHairDrawable;
    std::shared_ptr<GLDrawable> heroDrawable;

    //projection, modelview matrices
    glm::mat4  P = glm::mat4(1);
    glm::mat4  MV = glm::mat4(1);

    //camera transformation variables
    int state = 0, oldX=0, oldY=0;
    float rX=25, rY=-40, dist = -10;

    glm::vec3 lightPosOS=glm::vec3(0,2,0); //objectspace light position

    //spherical coordinates for storing the light position
    float theta = -7;
    float phi = -0.77f;
    float radius = 5;

    //shadow map texture ID
    GLuint shadowMapTexID;

    //FBO ID
    GLuint fboID;

    glm::mat4 MV_L; //light modelview matrix
    glm::mat4 P_L;	//light projection matrix
    glm::mat4 B;    //light bias matrix
    glm::mat4 BP;   //light bias and projection matrix combined
    glm::mat4 S;    //light's combined MVPB matrix

    void setup();
    void loadModel();
    World();
    void buildMesh();
    void fillSphereData(float radius, unsigned int slices, unsigned int stacks, std::vector<Vertex>& vertices, std::vector<GLushort>& indices);
    void fillPlaneData(const float width, const float depth, std::vector<Vertex>& vertices, std::vector<GLushort>& indices);
    void drawScene(glm::mat4 View, glm::mat4 Proj, int isLightPass = 1);
    void fillCubeData(const float& size, std::vector<Vertex>& vertices, std::vector<GLushort>& indices);
	
		
		
};

#endif // Game_h
