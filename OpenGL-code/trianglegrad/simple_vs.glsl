#version 400

layout(location=0) in vec3 vp;
layout(location=1) in vec3 col;
out vec3 color;
void main () 
{
  gl_Position = vec4 (vp, 1.0);
  color=col;
}
