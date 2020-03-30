
#include "gl_framework.hpp"
#include "shader_util.hpp"
#include<stdlib.h>
#include<math.h>

float pi=3.141592;

GLuint shaderProgramblack,shaderProgramwhite;
GLuint vbo, vao;

void initShadersGLBlack(void)
{
  std::string vertex_shader_file("simple_vs.glsl");
  std::string fragment_shader_file("simple_fsb.glsl");

  std::vector<GLuint> shaderList;
  shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  shaderProgramblack = csX75::CreateProgramGL(shaderList);

}
void initShadersGLWhite(void)
{
  std::string vertex_shader_file("simple_vs.glsl");
  std::string fragment_shader_file("simple_fsw.glsl");

  std::vector<GLuint> shaderList;
  shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  shaderProgramwhite = csX75::CreateProgramGL(shaderList);

}





int main(int argc, char** argv)
{
  //! The pointer to the GLFW window
  GLFWwindow* window;

  //! Setting up the GLFW Error callback
  glfwSetErrorCallback(csX75::error_callback);

  //! Initialize GLFW
  if (!glfwInit())
    return -1;

  //We want OpenGL 4.0
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  //This is for MacOSX - can be omitted otherwise
 // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  //We don't want the old OpenGL
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  //! Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(640, 480, "CS475/CS675 OpenGL Framework", NULL, NULL);
  if (!window)
    {
      glfwTerminate();
      return -1;
    }

  //! Make the window's context current
  glfwMakeContextCurrent(window);

  //Initialize GLEW
  //Turn this on to get Shader based OpenGL
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (GLEW_OK != err)
    {
      //Problem: glewInit failed, something is seriously wrong.
      std::cerr<<"GLEW Init Failed : %s"<<std::endl;
    }

  //Print and see what context got enabled
  std::cout<<"Vendor: "<<glGetString (GL_VENDOR)<<std::endl;
  std::cout<<"Renderer: "<<glGetString (GL_RENDERER)<<std::endl;
  std::cout<<"Version: "<<glGetString (GL_VERSION)<<std::endl;
  std::cout<<"GLSL Version: "<<glGetString (GL_SHADING_LANGUAGE_VERSION)<<std::endl;

  //Keyboard Callback
  glfwSetKeyCallback(window, csX75::key_callback);
  //Framebuffer resize callback
  glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  //Initialize GL state
  csX75::initGL();
  initShadersGLBlack();
  initShadersGLWhite();

unsigned int vbo[64],vao[64];
    glGenBuffers(64,vbo);
    glGenVertexArrays(64,vao);

    float vertices[12];
    int k=0;

while(glfwWindowShouldClose(window)==0)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            for(int i=0;i<8;i++)
            {
                for(int j=0;j<8;j++)
                {
                  vertices[0]=-1.0f+i*0.25f;
                  vertices[1]=-1.0f+j*0.25f;
                  vertices[2]=0.0f;
                  vertices[3]=-1.0f+(i+1)*0.25f;
                  vertices[4]=-1.0f+j*0.25f;
                  vertices[5]=0.0f;
                  vertices[6]=-1.0f+i*0.25f;
                  vertices[7]=-1.0f+(j+1)*0.25f;
                  vertices[8]=0.0f;
                  vertices[9]=-1.0f+(i+1)*0.25f;
                  vertices[10]=-1.0f+(j+1)*0.25f;
                  vertices[11]=0.0f;

                 glBindBuffer(GL_ARRAY_BUFFER,vbo[k]);
                 glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
                 glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);
                 glEnableVertexAttribArray(0);

                 if(i+j%2==0)
		    glUseProgram(shaderProgramwhite);
                 else
                     glUseProgram(shaderProgramblack);

                 glBindVertexArray(vao[k]);
                 glDrawArrays(GL_QUADS,0,4);
                 k++;


                }
            }

        }

  glfwTerminate();
  return 0;
}



