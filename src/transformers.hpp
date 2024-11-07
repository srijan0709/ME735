/*
  A program which opens a window and draws the "color cube."

  Use the arrow keys and PgUp,PgDn, 
  keys to make the cube move.

 
*/
#ifndef _COLORCUBE_HPP_
#define _COLORCUBE_HPP_

// Defining the ESCAPE Key Code
#define ESCAPE 27
// Defining the DELETE Key Code
#define DELETE 127

#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

// Rotation Parameters
GLfloat xrot=0.0, yrot=0.0;
// Camera position and rotation Parameters
GLfloat c_xpos = 0.0, c_ypos = 0.0, c_zpos = 30.0;
GLfloat c_xrot=0.0, c_yrot=0.0, c_zrot=0.0;

GLint width = 700, height = 700;
GLfloat scale = 1.0f;
GLint transformer=0;

//lights and camera parameters
uint lights_cam = 0b00001101;


//------------------------------------------------------------------------

glm::mat4 rotation_matrix;
glm::mat4 projection_matrix;
glm::mat4 c_rotation_matrix;
glm::mat4 lookat_matrix;

glm::mat4 model_matrix;
glm::mat4 view_matrix;


// glm::mat4 modelview_matrix;
glm::mat3 normal_matrix;

GLuint uModelViewMatrix;
GLuint viewMatrix;
GLuint normalMatrix;

GLuint diffuse;
GLuint ambient;
GLuint specular;
GLuint shininess;

int keyframe_status = 0;

//-------------------------------------------------------------------------

#endif
