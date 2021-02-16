#version 120


//varying vec2 texCoordVarying;

void main()
{
	//texCoordVarying = gl_MultiTexCoord0.xy;
	//gl_Position = ftransform();
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}