#version 330 core
  
layout(location=0) in vec3 vVertex;		//per-vertex position
layout(location=1) in vec3 vNormal;		//per-vertex normal
layout(location=2) in vec2 texcoord;
layout(location=3) in vec4 blendWeights;
layout(location=4) in vec4 blendIndices;
 
//uniforms
uniform mat4 MVP;	//modelview projection matrix
uniform mat4 MV;	//modelview matrix
uniform mat4 M;		//model matrix
uniform mat3 N;		//normal matrix
uniform mat4 S;		//shadow matrix
uniform mat4 TX[100];   //transformation matrix


//shader outputs to the fragment shader
smooth out vec3 vEyeSpaceNormal;		//eye space normal
smooth out vec3 vEyeSpacePosition;		//eye space position
smooth out vec4 vShadowCoords;			//shadow coordinates
out vec2 Texcoord;

void main()
{ 	
        vec4 newVertex;
        vec4 newNormal;

        //apply transform
        int index = int(blendIndices.x);

        newVertex = (TX[index] * vec4(vVertex,1.0)) * blendWeights.x;
        newNormal = (TX[index] * vec4(vNormal,0.0)) * blendWeights.x;

        index = int(blendIndices.y);

        newVertex = newVertex + (TX[index] * vec4(vVertex,1.0)) * blendWeights.y;
        newNormal = newNormal + (TX[index] * vec4(vNormal,0.0)) * blendWeights.y;

        index = int(blendIndices.z);

        newVertex = newVertex + (TX[index] * vec4(vVertex,1.0)) * blendWeights.z;
        newNormal = newNormal + (TX[index] * vec4(vNormal,0.0)) * blendWeights.z;

        index = int(blendIndices.w);

        newVertex = newVertex + (TX[index] * vec4(vVertex,1.0)) * blendWeights.w;
        newNormal = newNormal + (TX[index] * vec4(vNormal,0.0)) * blendWeights.w;

	//multiply the object space vertex position with the modelview matrix 
	//to get the eye space vertex position
        vEyeSpacePosition = (MV*vec4(newVertex.xyz,1)).xyz;

	//multiply the object space normal with the normal matrix 
	//to get the eye space normal
        vEyeSpaceNormal   = normalize(N*newNormal.xyz);

	//multiply the world space vertex position with the shadow matrix 
	//to get the shadow coordinates
        vShadowCoords     = S*(M*vec4(newVertex.xyz,1));

        Texcoord = texcoord;

	//multiply the combined modelview projection matrix with the object space vertex
	//position to get the clip space position
    gl_Position       = MVP*newVertex;
}
 
