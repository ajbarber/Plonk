#include "World.h"
#include "Camera.h"
#include "structs.h"
#include "drawing.h"
#include "AssimpConverter.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
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
#include "herobodypart.h"
#include "hero.h"



using namespace std;

World *World::instance = 0;

World::World()
{
	setup();
}

World::~World()
{
	
}

World *World::init()
{
	if(!World::instance)
	{
		World::instance = new World;						
	}
	else
	{
		fprintf(stderr, "WARNING: World::init() has already been called.\n");
	}
	return World::instance;
}

//----------------------------------------------------------
World *World::getInstance()
{
	if(!instance)
    {
		return World::init();
	}
	else
		return World::instance;
}

//----------------------------------------------------------
void World::destroy()
{	   
	delete World::instance;
	World::instance = 0;
}

void World::loadModel()
{
    Assimp::Importer importer;
    const aiScene *sceneRaw = importer.ReadFile("boblampclean.md5mesh",
        aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

    aiScene* sceneRawnc = const_cast<aiScene*>(sceneRaw);
    scene = std::shared_ptr<aiScene>(sceneRawnc);

    if(!scene)
    {
       fprintf(stderr, importer.GetErrorString());
       return;
    }

    Hero* heroRaw = new Hero(scene);
    hero = shared_ptr<Hero>(heroRaw);


}

void World::setup()
{
    t_start = std::chrono::high_resolution_clock::now();

    World::loadModel();

	World::buildMesh();
}

void World::buildMesh()
{
		
    //load the flat shader
        flatshader.LoadFromFile(GL_VERTEX_SHADER, "shaders/shader.vert");
        flatshader.LoadFromFile(GL_FRAGMENT_SHADER, "shaders/shader.frag");
        //compile and link shader
        flatshader.CreateAndLinkProgram();
        flatshader.Use();
            //add attributes and uniforms
            flatshader.AddAttribute("vVertex");
            flatshader.AddUniform("MVP");
        flatshader.UnUse();

        //load the shadow mapping shader
        shader.LoadFromFile(GL_VERTEX_SHADER, "shaders/PointLightShadowMapped.vert");
        shader.LoadFromFile(GL_FRAGMENT_SHADER, "shaders/PointLightShadowMapped.frag");
        //compile and link shader
        shader.CreateAndLinkProgram();
        shader.Use();
            //add attributes and uniforms
            shader.AddAttribute("vVertex");
            shader.AddAttribute("vNormal");
            shader.AddUniform("MVP");
            shader.AddUniform("MV");
            shader.AddUniform("M");
            shader.AddUniform("N");
            shader.AddUniform("S");
            shader.AddUniform("light_position");
            shader.AddUniform("diffuse_color");
            shader.AddUniform("bIsLightPass");
            shader.AddUniform("shadowMap");
            shader.AddUniform("tex");
            //pass value of constant uniforms at initialization
            glUniform1i(shader("shadowMap"),0);
        shader.UnUse();

        GL_CHECK_ERRORS

        shared_ptr<Drawing> sphere(new Sphere(1.0f,10,10));
        sphereDrawable = shared_ptr<GLDrawable>(new SphereDrawable(*sphere));
        int err = sphereDrawable->bindDrawing();

        shared_ptr<Drawing> cube(new Cube(2.0f));
        cubeDrawable = shared_ptr<GLDrawable>(new CubeDrawable(*cube));
        err = cubeDrawable->bindDrawing();

        shared_ptr<Drawing> floor(new Floor(100,100));
        floorDrawable = shared_ptr<GLDrawable>(new FloorDrawable(*floor));
        err = floorDrawable->bindDrawing();

        shared_ptr<Drawing> crossHair(new CrossHair());
        crossHairDrawable = shared_ptr<GLDrawable>(new CrossHairDrawable(*crossHair));
        err = crossHairDrawable->bindDrawing();
        unsigned int i = 0;

        for (int idx = 0; idx< hero->getBodyParts().size(); idx ++)
        {
            HeroBodyPartDrawable* hbpd = new HeroBodyPartDrawable(*hero->getBodyParts()[idx]);
            heroDrawables.push_back(std::unique_ptr<GLDrawable>(hbpd));
            err = heroDrawables[idx]->bindDrawing();
        }

        //get light position from spherical coordinates
        lightPosOS.x = radius * cos(theta)*sin(phi);
        lightPosOS.y = radius * cos(phi);
        lightPosOS.z = radius * sin(theta)*sin(phi);

        //setup the shadowmap texture
        glGenTextures(1, &shadowMapTexID);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, shadowMapTexID);

        //set texture parameters
        GLfloat border[4]={1,0,0,0};
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_MODE,GL_COMPARE_REF_TO_TEXTURE);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_FUNC,GL_LEQUAL);
        glTexParameterfv(GL_TEXTURE_2D,GL_TEXTURE_BORDER_COLOR,border);
        glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT24,SHADOWMAP_WIDTH,SHADOWMAP_HEIGHT,0,GL_DEPTH_COMPONENT,GL_UNSIGNED_BYTE,NULL);

        //set up FBO to get the depth component
        glGenFramebuffers(1,&fboID);
        glBindFramebuffer(GL_FRAMEBUFFER,fboID);
        glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D,shadowMapTexID,0);

        //check framebuffer completeness status
        GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if(status == GL_FRAMEBUFFER_COMPLETE) {
            cout<<"FBO setup successful."<<endl;
        } else {
            cout<<"Problem in FBO setup."<<endl;
        }

        //unbind FBO
        glBindFramebuffer(GL_FRAMEBUFFER,0);


        //set the light MV, P and bias matrices
        MV_L = glm::lookAt(lightPosOS,glm::vec3(0,0,0),glm::vec3(0,1,0));
        P_L  = glm::perspective(50.0f,1.0f,1.0f, 25.0f);
        B    = glm::scale(glm::translate(glm::mat4(1),glm::vec3(0.5,0.5,0.5)), glm::vec3(0.5,0.5,0.5));
        BP   = B*P_L;
        S    = BP*MV_L;

        //enable depth testing and culling
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);

        cout<<"Initialization successfull"<<endl;

	
}


//scene rendering function
void World::drawScene(glm::mat4 View, glm::mat4 Proj, int isLightPass) {

    GL_CHECK_ERRORS

    //bind the current shader
    shader.Use();
    //render plane first
    glBindVertexArray(floorDrawable->getVaoID()); {
        //set the shader uniforms
        glUniform3fv(shader("light_position"),1, &(lightPosOS.x));
        glUniformMatrix4fv(shader("S"), 1, GL_FALSE, glm::value_ptr(S));
        glUniformMatrix4fv(shader("M"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1)));
        glUniform1i(shader("bIsLightPass"), isLightPass);
        glUniformMatrix4fv(shader("MVP"), 1, GL_FALSE, glm::value_ptr(Proj*View));
        glUniformMatrix4fv(shader("MV"), 1, GL_FALSE, glm::value_ptr(View));
        glUniformMatrix3fv(shader("N"), 1, GL_FALSE, glm::value_ptr(glm::inverseTranspose(glm::mat3(View))));
        glUniform3f(shader("diffuse_color"), 1.0f,1.0f,1.0f);
            //draw plane triangles
            glDrawElements(GL_TRIANGLES, floorDrawable->getNumTriangles(), GL_UNSIGNED_SHORT, 0);
    }

    //render the cube
    glBindVertexArray(cubeDrawable->getVaoID()); {
        //set the cube's transform
        glm::mat4 T = glm::translate(glm::mat4(1),  glm::vec3(-1,1,0));
        glm::mat4 M = T;
        glm::mat4 MV = View*M;
        glm::mat4 MVP = Proj*MV;
        //pass shader uniforms
        glUniformMatrix4fv(shader("S"), 1, GL_FALSE, glm::value_ptr(S));
        glUniformMatrix4fv(shader("M"), 1, GL_FALSE, glm::value_ptr(M));
        glUniformMatrix4fv(shader("MVP"), 1, GL_FALSE, glm::value_ptr(MVP));
        glUniformMatrix4fv(shader("MV"), 1, GL_FALSE, glm::value_ptr(MV));
        glUniformMatrix3fv(shader("N"), 1, GL_FALSE, glm::value_ptr(glm::inverseTranspose(glm::mat3(MV))));
        glUniform3f(shader("diffuse_color"), 1.0f,0.0f,0.0f);
            //draw cube triangles
            glDrawElements(GL_TRIANGLES, cubeDrawable->getNumTriangles(), GL_UNSIGNED_SHORT, 0);
    }
    //render the sphere
    glBindVertexArray(sphereDrawable->getVaoID()); {
        //set the sphere's transform
        glm::mat4 T = glm::translate(glm::mat4(1), glm::vec3(1,1,0));
        glm::mat4 M = T;
        glm::mat4 MV = View*M;
        glm::mat4 MVP = Proj*MV;
        //set the shader uniforms
        glUniformMatrix4fv(shader("S"), 1, GL_FALSE, glm::value_ptr(S));
        glUniformMatrix4fv(shader("M"), 1, GL_FALSE, glm::value_ptr(M));
        glUniformMatrix4fv(shader("MVP"), 1, GL_FALSE, glm::value_ptr(MVP));
        glUniformMatrix4fv(shader("MV"), 1, GL_FALSE, glm::value_ptr(MV));
        glUniformMatrix3fv(shader("N"), 1, GL_FALSE, glm::value_ptr(glm::inverseTranspose(glm::mat3(MV))));
        glUniform3f(shader("diffuse_color"), 0.0f, 0.0f, 1.0f);
            //draw sphere triangles
            glDrawElements(GL_TRIANGLES, sphereDrawable->getNumTriangles(), GL_UNSIGNED_SHORT, 0);
    }

    //render the hero

    for (int idx =0 ; idx< heroDrawables.size(); idx++)
    {

        glBindVertexArray(heroDrawables[idx]->getVaoID()); {
            //set the sphere's transform
            glm::mat4 T = glm::translate(glm::mat4(1), glm::vec3(1,1,0));
            glm::mat4 M = T;
            glm::mat4 MV = View*M;
            glm::mat4 MVP = Proj*MV;
            //set the shader uniforms
            glUniformMatrix4fv(shader("S"), 1, GL_FALSE, glm::value_ptr(S));
            glUniformMatrix4fv(shader("M"), 1, GL_FALSE, glm::value_ptr(M));
            glUniformMatrix4fv(shader("MVP"), 1, GL_FALSE, glm::value_ptr(MVP));
            glUniformMatrix4fv(shader("MV"), 1, GL_FALSE, glm::value_ptr(MV));
            glUniformMatrix3fv(shader("N"), 1, GL_FALSE, glm::value_ptr(glm::inverseTranspose(glm::mat3(MV))));
            glUniform3f(shader("diffuse_color"), 1.0f, 1.0f, 1.0f);
            glUniform1i(shader("tex"), 0);
            //draw sphere triangles
            heroDrawables[idx]->bindTexture();
            glDrawElements(GL_TRIANGLES, heroDrawables[idx]->getNumTriangles(), GL_UNSIGNED_SHORT, 0);
        }
    }


    //unbind shader
    shader.UnUse();

    checkErrors();

    GL_CHECK_ERRORS
}


void World::render() 
{ 
    //get the elapsed time
    GL_CHECK_ERRORS

        //clear colour and depth buffers
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        //set the camera transform
        glm::mat4 T		= glm::translate(glm::mat4(1.0f),glm::vec3(0.0f, 0.0f, dist));
        glm::mat4 Rx	= glm::rotate(T,  rX, glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 MV    = glm::rotate(Rx, rY, glm::vec3(0.0f, 1.0f, 0.0f));

        //1) Render scene from the light's POV
        //enable rendering to FBO
        glBindFramebuffer(GL_FRAMEBUFFER,fboID);
        //clear depth buffer
        glClear(GL_DEPTH_BUFFER_BIT);
        //reset viewport to the shadow map texture size
        glViewport(0,0,SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT);

        //enable front face culling
        glCullFace(GL_FRONT);
        //draw scene from the point of view of light
        drawScene(MV_L, P_L);
        //enable back face culling
        glCullFace(GL_BACK);

        //restore normal rendering path
        //unbind FBO, set the default back buffer and reset the viewport to screen size
        glBindFramebuffer(GL_FRAMEBUFFER,0);
        glDrawBuffer(GL_BACK_LEFT);
        glViewport(0,0,WIDTH, HEIGHT);

        //2) Render scene from point of view of eye
        drawScene(MV, P, 0 );

        //bind light gizmo vertex array object
        glBindVertexArray(crossHairDrawable->getVaoID()); {
            //set the flat shader
            flatshader.Use();
                //set the light's transform and render 3 lines
                glm::mat4 T = glm::translate(glm::mat4(1), lightPosOS);
                glUniformMatrix4fv(flatshader("MVP"), 1, GL_FALSE, glm::value_ptr(P*MV*T));
                    glDrawArrays(GL_LINES, 0, 6);
            //unbind shader
            flatshader.UnUse();
        }

        //unbind the vertex array object
        glBindVertexArray(0);


}

void World::resize(int w, int h)
{
    //set the viewport
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    //setup the projection matrix
    P = glm::perspective(45.0f, (GLfloat)w/h, 0.1f, 1000.f);
}

void World::mouseMove(int x, int y)
{
    if (state == 0)
        dist *= (1 + (y - oldY)/60.0f);
    else if(state ==2) {
        theta += (oldX - x)/60.0f;
        phi += (y - oldY)/60.0f;

        //update the light position
        lightPosOS.x = radius * cos(theta)*sin(phi);
        lightPosOS.y = radius * cos(phi);
        lightPosOS.z = radius * sin(theta)*sin(phi);

        //update light's MV matrix
        MV_L = glm::lookAt(lightPosOS,glm::vec3(0,0,0),glm::vec3(0,1,0));
        S = BP*MV_L;
    } else {
        rY += (x - oldX)/5.0f;
        rX += (y - oldY)/5.0f;
    }
    oldX = x;
    oldY = y;

}


//mouse click handler
void World::mouseClick(bool middle, bool right, bool down, int x, int y)
{
    if (down)
    {
        oldX = x;
        oldY = y;
    }

    if(middle)
       state = 0;
    else if(right)
       state = 2;
    else
       state = 1;

}

//mouse wheel scroll handler which changes the radius of the light source
//since the position is given in spherical coordinates, the radius contols
//how far from the center the light source is.
void World::onMouseWheel(int dir) {

    if (dir > 0)
    {
        radius += 0.1f;
    }
    else
    {
        radius -= 0.1f;
    }

    radius = max(radius,0.0f);

    //get the new light position
    lightPosOS.x = radius * cos(theta)*sin(phi);
    lightPosOS.y = radius * cos(phi);
    lightPosOS.z = radius * sin(theta)*sin(phi);

    //update light's MV matrix
    MV_L = glm::lookAt(lightPosOS,glm::vec3(0,0,0),glm::vec3(0,1,0));
    S = BP*MV_L;

}


bool World::checkErrors()
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


void World::renderAnimation()
{

    //mesh.Render();
   // checkErrors();

    // clear the screen to blackGL_CHECK_ERRORS;
//    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//    glClear(GL_COLOR_BUFFER_BIT);
//    for (unsigned int i = 0; i < animatedModel->GetNumMeshes(); ++i)
//    {
//        const SA::sAnimatedMesh& animMesh = animatedModel->GetMesh(i);

//        glBegin(GL_TRIANGLES);
//        for (unsigned int i = 0; i < animMesh.NumIndices; ++i)
//        {
//            unsigned int index = animMesh.pIndices[i];
//            glm::vec3 n = animMesh.pNormals[index];
//            glm::vec3 v = animMesh.pTransformedVertices[index];

//            glColor4f(n.x, n.y, n.z, 1);
//            glVertex3f(v.x, v.y, v.z);
//        }
//        glEnd();
//        checkErrors();
//    }
}




void World::update() 
{	
    std::chrono::system_clock::time_point t_now = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
    //t_start = t_now;   

    //mesh.BoneTransform(time, transforms );

//    for (uint i = 0 ; i < Transforms.size() ; i++) {
//               m_pEffect->SetBoneTransform(i, Transforms[i]);
//           }

    //animatedModel->Update(time/1000.0);

	//camera.update()
	//call in hero + npc update methods here	
}






