#version 330 core

out vec4 color;

in vec3 ourColor;
in vec2 ourTexcor;

uniform sampler2D texture1;
uniform sampler2D texture2;


void main(){
	color = mix(texture(texture1,vec2(ourTexcor.x,ourTexcor.y)),texture(texture2,vec2(ourTexcor.x,ourTexcor.y)*5.0),0.0f) ;
}