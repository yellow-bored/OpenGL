#version 330 core
layout(location = 0) in vec3 position;
uniform ivec3 m_Pos_sgn;
out vec4 ourColor;
void main(){
    ourColor = vec4(position, 1.0f);
    gl_Position = vec4(position*m_Pos_sgn ,1.0);
}