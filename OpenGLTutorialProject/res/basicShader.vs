#version 430

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

varying vec2 texCoord0;
varying vec3 normal0;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(position, 1.0);
	texCoord0 = 1.0 - texCoord;
	normal0 = (transform * vec4(normal, 0.0)).xyz;
}