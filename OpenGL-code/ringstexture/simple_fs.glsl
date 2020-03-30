#version 400
in vec2 TexCoord;
out vec4 frag_colour;
uniform sampler2D TheTexture;
void main () 
{
  frag_colour = texture(TheTexture,TexCoord);
}
