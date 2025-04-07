#version 330 core
in vec4 ourColor;
out vec4 color;
uniform vec4 m_Color;
void main(){
   color = ourColor;
}