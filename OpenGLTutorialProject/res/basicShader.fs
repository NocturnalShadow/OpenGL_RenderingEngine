#version 120

varying vec2 texCoord0;
varying vec3 normal0;

uniform sampler2D diffuse;

void main()
{
	if(normal0 != vec3(0, 0, 0)) {
		gl_FragColor =  texture2D(diffuse, texCoord0) 
			* clamp(dot(-vec3(0, 0, 1), normal0), 0.0, 1.0);				// dot product of two normalized vectors is cos between them
	}
	else {
		gl_FragColor =  texture2D(diffuse, texCoord0);						// if normal is undefined no lightning effects applied
	}
}