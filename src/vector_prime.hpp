#include "transformers.hpp"
#include <iostream>

#define transform_frames 200

GLfloat vp_ship_rotate=90.0f;
GLfloat vp_head_translate=0.0f, vp_head_x=0.0f, vp_head_y=0.0f, vp_head_z=0.0f; 
GLfloat vp_left_wing_torso_torso=90.0f, vp_left_wing_wing_torso=90.0f, vp_left_wing=0.0f, vp_right_wing_torso_torso=90.0f, vp_right_wing_wing_torso=90.0f, vp_right_wing=0.0f;
GLfloat vp_right_shoulder_pad=109.0, vp_left_shoulder_pad=109.0;
GLfloat vp_right_shoulder_translate=0.0f, vp_left_shoulder_translate=0.0f, vp_right_shoulder_x=0.0f, vp_right_shoulder_y=0.0f, vp_right_shoulder_z=0.0f, vp_left_shoulder_x=0.0f, vp_left_shoulder_y=0.0f, vp_left_shoulder_z=0.0f;
GLfloat vp_right_elbow_x=0.0f, vp_left_elbow_x=0.0f, vp_right_elbow_y=0.0f, vp_left_elbow_y=0.0f;
GLfloat vp_right_foot_x=0.0f, vp_right_foot_y=0.0f, vp_right_foot_z=0.0f, vp_left_foot_x=0.0f, vp_left_foot_y=0.0f, vp_left_foot_z=0.0f;
GLfloat vp_right_knee_x=0.0f, vp_left_knee_x=0.0f, vp_right_knee_y=0.0f, vp_left_knee_y=0.0f;
GLfloat vp_right_hip_x=0.0f, vp_right_hip_y=0.0f, vp_right_hip_z=0.0f, vp_left_hip_x=0.0f, vp_left_hip_y=0.0f, vp_left_hip_z=0.0f;
GLfloat vp_torso_x=0.0f, vp_torso_y=0.0f, vp_torso_z=0.0f;
GLfloat vp_right_hand_guard=1.0f, vp_left_hand_guard=1.0f;
GLint vp_transformation=0;
GLfloat vp_right_hand_x=0.0f, vp_right_hand_y=0.0f, vp_right_hand_z=0.0f, vp_left_hand_x=0.0f, vp_left_hand_y=0.0f, vp_left_hand_z=0.0f;
GLfloat vp_xpos=0.0f, vp_ypos=11.6f, vp_zpos=0.0f;

GLfloat vp_light_spread=0.55f;
glm::vec3 vp_light_pos;
glm::vec3 vp_light_dir;
glm::vec3 vp_eye;
glm::vec3 vp_cent;
glm::vec3 vp_up;

namespace vp{
const glm::vec4 light_pos = glm::vec4(0.0f, 3.6f, 1.9f, 1.0f);
const glm::vec4 light_dir = glm::vec4(glm::normalize(glm::vec3(0.0f, 0.5f, -1.0f)), 1.0f);

const glm::vec4 up = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
const glm::vec4 cent = glm::vec4(0.0f, 9.0f, 0.0f, 1.0f);
const glm::vec4 eye = glm::vec4(0.0f, 12.0f, -15.0f, 1.0f);

const glm::vec4 up_t = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
const glm::vec4 cent_t = glm::vec4(0.0f, 10.0f, 7.0f, 1.0f);
const glm::vec4 eye_t = glm::vec4(0.0f, -5.0f, 8.0f, 1.0f);

const GLfloat svp_ship_rotate=00.0f;
const GLfloat svp_head_translate=0.0f, svp_head_x=0.0f, svp_head_y=180.0f, svp_head_z=0.0f; 
const GLfloat svp_right_wing_wing_torso=0.0f, svp_right_wing_torso_torso=0.0f, svp_right_wing=90.0f, svp_left_wing_wing_torso=0.0f, svp_left_wing_torso_torso=0.0f, svp_left_wing=90.0f;
const GLfloat svp_right_shoulder_pad=0.0, svp_left_shoulder_pad=0.0;
const GLfloat svp_right_shoulder_translate=0.0f, svp_left_shoulder_translate=0.0f,  svp_right_shoulder_x=0.0f, svp_right_shoulder_y=0.0f, svp_right_shoulder_z=0.0f, svp_left_shoulder_x=0.0f, svp_left_shoulder_y=0.0f, svp_left_shoulder_z=0.0f;
const GLfloat svp_right_elbow_x=0.0f, svp_left_elbow_x=0.0f, svp_right_elbow_y=0.0f, svp_left_elbow_y=0.0f;
const GLfloat svp_right_foot_x=90.0f, svp_right_foot_y=0.0f, svp_right_foot_z=0.0f, svp_left_foot_x=90.0f, svp_left_foot_y=0.0f, svp_left_foot_z=0.0f;
const GLfloat svp_right_knee_x=0.0f, svp_left_knee_x=0.0f, svp_right_knee_y=90.0f, svp_left_knee_y=90.0f;
const GLfloat svp_right_hip_x=90.0f, svp_right_hip_y=0.0f, svp_right_hip_z=0.0f, svp_left_hip_x=90.0f, svp_left_hip_y=0.0f, svp_left_hip_z=0.0f;
const GLfloat svp_torso_x=90.0f, svp_torso_y=180.0f;
const GLfloat svp_right_hand_guard=0.0f, svp_left_hand_guard=0.0f;
const GLfloat svp_right_hand_x=0.0f, svp_right_hand_y=0.0f, svp_right_hand_z=0.0f, svp_left_hand_x=0.0f, svp_left_hand_y=0.0f, svp_left_hand_z=0.0f;

const GLfloat rvp_ship_rotate=90.0f;
const GLfloat rvp_head_translate=0.0f, rvp_head_x=0.0f, rvp_head_y=0.0f, rvp_head_z=0.0f; 
const GLfloat rvp_right_wing_wing_torso=90.0f, rvp_right_wing_torso_torso=90.0f, rvp_right_wing=0.0f, rvp_left_wing_wing_torso=90.0f, rvp_left_wing_torso_torso=90.0f, rvp_left_wing=0.0f;
const GLfloat rvp_right_shoulder_pad=109.0, rvp_left_shoulder_pad=109.0;
const GLfloat rvp_right_shoulder_translate=0.0f, rvp_left_shoulder_translate=0.0f,  rvp_right_shoulder_x=0.0f, rvp_right_shoulder_y=0.0f, rvp_right_shoulder_z=0.0f, rvp_left_shoulder_x=0.0f, rvp_left_shoulder_y=0.0f, rvp_left_shoulder_z=0.0f;
const GLfloat rvp_right_elbow_x=0.0f, rvp_left_elbow_x=0.0f, rvp_right_elbow_y=0.0f, rvp_left_elbow_y=0.0f;
const GLfloat rvp_right_foot_x=0.0f, rvp_right_foot_y=0.0f, rvp_right_foot_z=0.0f, rvp_left_foot_x=0.0f, rvp_left_foot_y=0.0f, rvp_left_foot_z=0.0f;
const GLfloat rvp_right_knee_x=0.0f, rvp_left_knee_x=0.0f, rvp_right_knee_y=0.0f, rvp_left_knee_y=0.0f;
const GLfloat rvp_right_hip_x=0.0f, rvp_right_hip_y=0.0f, rvp_right_hip_z=0.0f, rvp_left_hip_x=0.0f, rvp_left_hip_y=0.0f, rvp_left_hip_z=0.0f;
const GLfloat rvp_torso_x=0.0f, rvp_torso_y=0.0f;
const GLfloat rvp_right_hand_guard=1.0f, rvp_left_hand_guard=1.0f;
const GLfloat rvp_right_hand_x=0.0f, rvp_right_hand_y=0.0f, rvp_right_hand_z=0.0f, rvp_left_hand_x=0.0f, rvp_left_hand_y=0.0f, rvp_left_hand_z=0.0f;

GLint vp_count=0, vp_form=0;


const int buff_size = 16;
void copy_col_norm(int len,glm::vec3 v_norm[], glm::vec4 v_colors[], glm::vec4 v_positions[], glm::vec4 positions[],glm::vec4 base_col=glm::vec4(1.0f,1.0f,1.0f,1.0f), bool reflect=false, glm::mat4 reflect1=glm::mat4(1.0f), glm::mat3 reflect2=glm::mat3(1.0f)){
  if(reflect){
    for(int i=0;i<len;i+=3){
      v_colors[i] = base_col;
      v_colors[i+1] = base_col;
      v_colors[i+2] = base_col;
      v_colors[i+len] = base_col;
      v_colors[i+len+1] = base_col;
      v_colors[i+len+2] = base_col;

      v_positions[i] = positions[i];
      v_positions[i+1] = positions[i+1];
      v_positions[i+2] = positions[i+2];
      v_positions[i+len] = reflect1*positions[i];
      v_positions[i+len+1] = reflect1*positions[i+1];
      v_positions[i+len+2] = reflect1*positions[i+2];

      glm::vec3 norm = glm::cross(glm::vec3(positions[i+2]-positions[i]),glm::vec3(positions[i+1]-positions[i]));
      v_norm[i] = norm;
      v_norm[i+1] = norm;
      v_norm[i+2] = norm;
      norm=reflect2*norm;
      v_norm[i+len] = norm;
      v_norm[i+len+1] = norm;
      v_norm[i+len+2] = norm;
    }
  }
  else{
    for(int i=0;i<len;i+=3){
      v_colors[i] = base_col;
      v_colors[i+1] = base_col;
      v_colors[i+2] = base_col;

      v_positions[i] = positions[i];
      v_positions[i+1] = positions[i+1];
      v_positions[i+2] = positions[i+2];

      glm::vec3 norm = glm::cross(glm::vec3(positions[i+2]-positions[i]),glm::vec3(positions[i+1]-positions[i]));
      v_norm[i] = norm;
      v_norm[i+1] = norm;
      v_norm[i+2] = norm;
    }
  }
}

//************************************************************************************************************************************
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
//************************************************************************************************************************************

//Upper ship
const glm::mat4 ship_transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.6f, 0.0f));
const int ship_size = 2*(129+30);
void ship(glm::vec4 positions[ship_size], glm::vec3 normals[ship_size], glm::vec4 colors[ship_size])
{
glm::mat4 reflect = {glm::vec4(-1.0f, 0.0f, 0.0f, 0.0f),glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),};
glm::mat3 reflect2 = {glm::vec3(-1.0f, 0.0f, 0.0f),glm::vec3(0.0f, 1.0f, 0.0f),glm::vec3(0.0f, 0.0f, 1.0f)};
const float y = -0.8, z = 1.1; //To center the ship
glm::vec3 vertices[]={glm::vec3(0.0f, 16.25f+y, -0.2f+z),
                      glm::vec3(0.0f, 16.25f+y, 0.2f+z),
                      glm::vec3(1.4f, 15.5f+y, -0.2f+z),
                      glm::vec3(1.4f, 15.5f+y, 0.2f+z),//top 4 - 4
                      glm::vec3(0.0f, 15.3f+y, -0.7f+z),
                      glm::vec3(0.0f, 15.3f+y, 0.7f+z),
                      glm::vec3(1.5f, 15.0f+y, -0.4f+z),
                      glm::vec3(1.5f, 15.0f+y, 0.4f+z),//second 4 - 8
                      glm::vec3(0.0f, 1.3f+y, -1.6f+z),
                      glm::vec3(0.0f, 2.0f+y, 2.0f+z),
                      glm::vec3(3.0f, 2.2f+y, -0.6f+z),
                      glm::vec3(3.0f, 2.2f+y, 0.6f+z),//third 4 - 12
                      glm::vec3(0.7f, 1.3f+y, -1.5f+z),
                      glm::vec3(0.8f, 2.0f+y, 1.95f+z),
                      glm::vec3(0.6f, 2.0f+y, -0.4f+z),
                      glm::vec3(0.0f, 2.0f+y, -0.4f+z),//forth 4 - 16 
                      glm::vec3(1.1f, 0.0f+y, -0.4f+z),
                      glm::vec3(1.15f, 0.0f+y, 1.85f+z),
                      glm::vec3(0.0f, 0.0f+y, -0.4f+z),
                      glm::vec3(2.3f, 0.0f+y, 1.2f+z),// 5th 4 - 20
                      glm::vec3(0.0f, 1.3f+y, -0.6f+z),
                      glm::vec3(0.7f, 1.3f+y, -0.6f+z),
                      glm::vec3(0.0f, 0.0f+y, -0.6f+z),
                      glm::vec3(0.75f, 0.0f+y, -0.6f+z),// 6th - 24
                      glm::vec3(0.75f, 0.0f+y, -1.4f+z),
                      glm::vec3(2.3f, 0.0f+y, -1.05f+z),

                      //extra
                      glm::vec3(0.0f, 1.9f+y, 1.4f+z),
                      glm::vec3(0.55f, 1.9f+y, 1.4f+z),//7th 4 - 28

                      //extra2 
                      glm::vec3(0.0f, 6.7f+y, 2.0f+z),
                      glm::vec3(0.0f, 7.4f+y, 1.6f+z),
                      glm::vec3(1.6f, 4.6f+y, 1.25f+z),
                      glm::vec3(1.1f, 6.2f+y, 1.5f+z),//8th 4 - 32
                      glm::vec3(0.9f, 7.1f+y, 1.3f+z),
                      glm::vec3(1.5f, 6.5f+y, 1.2f+z),
                     };

glm::vec4 ship_positions[]={glm::vec4(vertices[1],1.0f),
                                     glm::vec4(vertices[0],1.0f),
                                     glm::vec4(vertices[3],1.0f),
                                     glm::vec4(vertices[0],1.0f),
                                     glm::vec4(vertices[2],1.0f),
                                     glm::vec4(vertices[3],1.0f),//first quad
                                     glm::vec4(vertices[5],1.0f),
                                     glm::vec4(vertices[1],1.0f),
                                     glm::vec4(vertices[7],1.0f),
                                     glm::vec4(vertices[1],1.0f),
                                     glm::vec4(vertices[3],1.0f),
                                     glm::vec4(vertices[7],1.0f),//second quad
                                     glm::vec4(vertices[6],1.0f),
                                     glm::vec4(vertices[2],1.0f),
                                     glm::vec4(vertices[4],1.0f),
                                     glm::vec4(vertices[2],1.0f),
                                     glm::vec4(vertices[0],1.0f),
                                     glm::vec4(vertices[4],1.0f),//third quad
                                     glm::vec4(vertices[7],1.0f),
                                     glm::vec4(vertices[3],1.0f),
                                     glm::vec4(vertices[6],1.0f),
                                     glm::vec4(vertices[3],1.0f),
                                     glm::vec4(vertices[2],1.0f),
                                     glm::vec4(vertices[6],1.0f),//forth quad
                                     // glm::vec4(vertices[9],1.0f),
                                     // glm::vec4(vertices[5],1.0f),
                                     // glm::vec4(vertices[11],1.0f),
                                     // glm::vec4(vertices[5],1.0f),
                                     // glm::vec4(vertices[7],1.0f),
                                     // glm::vec4(vertices[11],1.0f),//fifth quad
                                     glm::vec4(vertices[6],1.0f),
                                     glm::vec4(vertices[4],1.0f),
                                     glm::vec4(vertices[10],1.0f),
                                     glm::vec4(vertices[10],1.0f),
                                     glm::vec4(vertices[4],1.0f),
                                     glm::vec4(vertices[8],1.0f),//sixth quad
                                     glm::vec4(vertices[11],1.0f),
                                     glm::vec4(vertices[7],1.0f),
                                     glm::vec4(vertices[10],1.0f),
                                     glm::vec4(vertices[7],1.0f),
                                     glm::vec4(vertices[6],1.0f),
                                     glm::vec4(vertices[10],1.0f),//seventh quad
                                     // glm::vec4(vertices[13],1.0f),
                                     // glm::vec4(vertices[9],1.0f),
                                     // glm::vec4(vertices[11],1.0f),
                                     glm::vec4(vertices[12],1.0f),
                                     glm::vec4(vertices[10],1.0f),
                                     glm::vec4(vertices[8],1.0f),//fifth 2 triangles
                                     glm::vec4(vertices[15],1.0f),
                                     glm::vec4(vertices[26],1.0f),
                                     glm::vec4(vertices[14],1.0f),
                                     glm::vec4(vertices[14],1.0f),
                                     glm::vec4(vertices[26],1.0f),
                                     glm::vec4(vertices[27],1.0f),//sixth quad
                                     glm::vec4(vertices[18],1.0f),
                                     glm::vec4(vertices[15],1.0f),
                                     glm::vec4(vertices[16],1.0f),
                                     glm::vec4(vertices[16],1.0f),
                                     glm::vec4(vertices[15],1.0f),
                                     glm::vec4(vertices[14],1.0f),//seventh quad
                                     glm::vec4(vertices[16],1.0f),
                                     glm::vec4(vertices[14],1.0f),
                                     glm::vec4(vertices[17],1.0f),
                                     glm::vec4(vertices[17],1.0f),
                                     glm::vec4(vertices[14],1.0f),
                                     glm::vec4(vertices[27],1.0f),//8th quad
                                     glm::vec4(vertices[17],1.0f),
                                     glm::vec4(vertices[13],1.0f),
                                     glm::vec4(vertices[19],1.0f),
                                     glm::vec4(vertices[19],1.0f),
                                     glm::vec4(vertices[13],1.0f),
                                     glm::vec4(vertices[11],1.0f),//9th quad
                                     glm::vec4(vertices[20],1.0f),
                                     glm::vec4(vertices[21],1.0f),
                                     glm::vec4(vertices[8],1.0f),
                                     glm::vec4(vertices[21],1.0f),
                                     glm::vec4(vertices[12],1.0f),
                                     glm::vec4(vertices[8],1.0f),//10th quad
                                     glm::vec4(vertices[22],1.0f),
                                     glm::vec4(vertices[23],1.0f),
                                     glm::vec4(vertices[20],1.0f),
                                     glm::vec4(vertices[23],1.0f),
                                     glm::vec4(vertices[21],1.0f),
                                     glm::vec4(vertices[20],1.0f),//11th quad
                                     glm::vec4(vertices[23],1.0f),
                                     glm::vec4(vertices[24],1.0f),
                                     glm::vec4(vertices[12],1.0f),
                                     glm::vec4(vertices[23],1.0f),
                                     glm::vec4(vertices[12],1.0f),
                                     glm::vec4(vertices[21],1.0f),//12th quad
                                     glm::vec4(vertices[24],1.0f),
                                     glm::vec4(vertices[25],1.0f),
                                     glm::vec4(vertices[12],1.0f),
                                     glm::vec4(vertices[25],1.0f),
                                     glm::vec4(vertices[10],1.0f),
                                     glm::vec4(vertices[12],1.0f),//13th quad
                                     glm::vec4(vertices[19],1.0f),
                                     glm::vec4(vertices[11],1.0f),
                                     glm::vec4(vertices[25],1.0f),
                                     glm::vec4(vertices[25],1.0f),
                                     glm::vec4(vertices[11],1.0f),
                                     glm::vec4(vertices[10],1.0f),//14th quad
                                     glm::vec4(vertices[16],1.0f),
                                     glm::vec4(vertices[17],1.0f),
                                     glm::vec4(vertices[19],1.0f),
                                     glm::vec4(vertices[16],1.0f),
                                     glm::vec4(vertices[19],1.0f),
                                     glm::vec4(vertices[25],1.0f),//15th quad
                                     glm::vec4(vertices[16],1.0f),
                                     glm::vec4(vertices[25],1.0f),
                                     glm::vec4(vertices[24],1.0f),
                                     glm::vec4(vertices[16],1.0f),
                                     glm::vec4(vertices[24],1.0f),
                                     glm::vec4(vertices[23],1.0f),//16th quad
                                     glm::vec4(vertices[18],1.0f),
                                     glm::vec4(vertices[16],1.0f),
                                     glm::vec4(vertices[23],1.0f),
                                     glm::vec4(vertices[18],1.0f),
                                     glm::vec4(vertices[23],1.0f),
                                     glm::vec4(vertices[22],1.0f),//17th quad

                                     //extra
                                     glm::vec4(vertices[26],1.0f),
                                     glm::vec4(vertices[9],1.0f),
                                     glm::vec4(vertices[27],1.0f),
                                     glm::vec4(vertices[27],1.0f),
                                     glm::vec4(vertices[9],1.0f),
                                     glm::vec4(vertices[13],1.0f),//18th quad
                                     glm::vec4(vertices[17],1.0f),
                                     glm::vec4(vertices[27],1.0f),
                                     glm::vec4(vertices[13],1.0f),//1st triangle

                                     //extra2
                                     glm::vec4(vertices[28],1.0f),
                                     glm::vec4(vertices[29],1.0f),
                                     glm::vec4(vertices[32],1.0f),
                                     glm::vec4(vertices[28],1.0f),
                                     glm::vec4(vertices[32],1.0f),
                                     glm::vec4(vertices[31],1.0f),//3rd quad
                                     glm::vec4(vertices[31],1.0f),
                                     glm::vec4(vertices[32],1.0f),
                                     glm::vec4(vertices[33],1.0f),
                                     glm::vec4(vertices[31],1.0f),
                                     glm::vec4(vertices[33],1.0f),
                                     glm::vec4(vertices[30],1.0f),//19th quad
                                     glm::vec4(vertices[9],1.0f),
                                     glm::vec4(vertices[28],1.0f),
                                     glm::vec4(vertices[13],1.0f),
                                     glm::vec4(vertices[13],1.0f),
                                     glm::vec4(vertices[28],1.0f),
                                     glm::vec4(vertices[31],1.0f),//20th quad
                                     glm::vec4(vertices[29],1.0f),
                                     glm::vec4(vertices[5],1.0f),
                                     glm::vec4(vertices[32],1.0f),
                                     // glm::vec4(vertices[32],1.0f),
                                     // glm::vec4(vertices[5],1.0f),
                                     // glm::vec4(vertices[33],1.0f),//21th quad
                                     glm::vec4(vertices[13],1.0f),
                                     glm::vec4(vertices[31],1.0f),
                                     glm::vec4(vertices[30],1.0f),
                                     glm::vec4(vertices[11],1.0f),
                                     glm::vec4(vertices[13],1.0f),
                                     glm::vec4(vertices[30],1.0f),//22th quad
                                     glm::vec4(vertices[32],1.0f),
                                     glm::vec4(vertices[5],1.0f),
                                     glm::vec4(vertices[7],1.0f),
                                     glm::vec4(vertices[32],1.0f),
                                     glm::vec4(vertices[7],1.0f),
                                     glm::vec4(vertices[33],1.0f),//23th quad
                                     glm::vec4(vertices[11],1.0f),
                                     glm::vec4(vertices[33],1.0f),
                                     glm::vec4(vertices[7],1.0f),
                                     glm::vec4(vertices[30],1.0f),
                                     glm::vec4(vertices[33],1.0f),
                                     glm::vec4(vertices[11],1.0f),//24th quad
                                    };

int len = sizeof(ship_positions)/16;
copy_col_norm(len, normals, colors, positions, ship_positions, glm::vec4(1.0f), true, reflect, reflect2);

for(int i=ship_size-28; i>=ship_size-39; i--){
  colors[i] = glm::vec4(0.1f, 1.0f, 1.0f, 1.0f);
  colors[i-len] = glm::vec4(0.1f, 1.0f, 1.0f, 1.0f);
}
}


//upper ship - torso joint
const glm::mat4 ship_torso_transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 5.0f, -1.7f));
const int ship_torso_size = 36;
void ship_torso(glm::vec4 positions[ship_torso_size], glm::vec3 normals[ship_torso_size], glm::vec4 colors[ship_torso_size])
{
glm::vec3 vertices[]={glm::vec3(0.75f, 2.1f, 0.5f),
                      glm::vec3(-0.75f, 2.1f, 0.5f),
                      glm::vec3(-0.75f, -0.5f, 0.5f),
                      glm::vec3(0.75f, -0.5f, 0.5f),
                      glm::vec3(0.75f, 2.1f, -0.5f),
                      glm::vec3(-0.75f, 2.1f, -0.5f),
                      glm::vec3(-0.75f, -0.5f, -0.5f),
                      glm::vec3(0.75f, -0.5f, -0.5f),
                     };

glm::vec4 ship_torso_positions[]={glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[0],1.0f),//1th quad
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[5],1.0f),//2th quad
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[4],1.0f),//3th quad
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[5],1.0f),//4th quad
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[6],1.0f),//5th quad
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[7],1.0f),//6th quad
                         };

int len = sizeof(ship_torso_positions)/16;
copy_col_norm(len, normals, colors, positions, ship_torso_positions, glm::vec4(0.1f, 1.0f, 0.1f, 1.0f));

}

//flap extensions (flap - torso joint)
const glm::mat4 wing_torso_transform = glm::translate(glm::mat4(1.0f), glm::vec3(1.4f, 3.0f, -2.71f));
const int wing_torso_size = 192+48;
void wing_torso(glm::vec4 positions[wing_torso_size], glm::vec3 normals[wing_torso_size], glm::vec4 colors[wing_torso_size])
{
glm::vec3 vertices[]={glm::vec3(0.0f, -1.0f, 0.5f), //semi-circle
                      glm::vec3(-0.3827f, -0.9239f, 0.5f),
                      glm::vec3(-0.7071f, -0.7071f, 0.5f),
                      glm::vec3(-0.9239f, -0.3827f, 0.5f),//1th 4 - 4
                      glm::vec3(-1.0f, 0.0f, 0.5f),
                      glm::vec3(-0.9239f, 0.3827f, 0.5f),
                      glm::vec3(-0.7071f, 0.7071f, 0.5f),
                      glm::vec3(-0.3827f, 0.9239f, 0.5f),//2th 4 - 8
                      glm::vec3(0.0f, 1.0f, 0.5f),
                      glm::vec3(0.0f, 0.0f, 0.5f),

                      glm::vec3(0.0f, -1.0f, 0.0f),
                      glm::vec3(-0.3827f, -0.9239f, 0.0f),//3th 4 - 12
                      glm::vec3(-0.7071f, -0.7071f, 0.0f),
                      glm::vec3(-0.9239f, -0.3827f, 0.0f),
                      glm::vec3(-1.0f, 0.0f, 0.0f),
                      glm::vec3(-0.9239f, 0.3827f, 0.0f),//4th 4 - 16
                      glm::vec3(-0.7071f, 0.7071f, 0.0f),
                      glm::vec3(-0.3827f, 0.9239f, 0.0f),
                      glm::vec3(0.0f, 1.0f, 0.0f),
                      glm::vec3(0.0f, 0.0f, 0.0f),//5th 4 - 20

                      //semi-circle
                      glm::vec3(6.0f, 1.0f+0.4f, 0.5f),
                      glm::vec3(6.536f, 0.8934f+0.4f, 0.5f),
                      glm::vec3(6.99f, 0.59f+0.4f, 0.5f),
                      glm::vec3(7.293f, 0.1358f+0.4f, 0.5f),//6th 4 - 24
                      glm::vec3(7.4f, -0.4f+0.4f, 0.5f),
                      glm::vec3(7.293f, -0.9358f+0.4f, 0.5f),
                      glm::vec3(6.99f, -1.39f+0.4f, 0.5f),
                      glm::vec3(6.536f, -1.693f+0.4f, 0.5f),//7th 4 - 28
                      glm::vec3(6.0f, -1.8f+0.4f, 0.5f),
                      glm::vec3(6.0f, -0.4f+0.4f, 0.5f),

                      glm::vec3(6.0f, 1.0f+0.4f, 0.0f),
                      glm::vec3(6.536f, 0.8934f+0.4f, 0.0f),//8th 4 - 32
                      glm::vec3(6.99f, 0.59f+0.4f, 0.0f),
                      glm::vec3(7.293f, 0.1358f+0.4f, 0.0f),
                      glm::vec3(7.4f, -0.4f+0.4f, 0.0f),
                      glm::vec3(7.293f, -0.9358f+0.4f, 0.0f),//9th 4 - 36
                      glm::vec3(6.99f, -1.39f+0.4f, 0.0f),
                      glm::vec3(6.536f, -1.693f+0.4f, 0.0f),
                      glm::vec3(6.0f, -1.8f+0.4f, 0.0f),
                      glm::vec3(6.0f, -0.4f+0.4f, 0.0f),//10th 4 - 40

                      glm::vec3(0.6f, -1.4f, 0.0f),
                      glm::vec3(0.6f, -1.4f, 0.5f),
                      glm::vec3(4.0f, 1.0f, 0.0f),
                      glm::vec3(4.0f, 1.0f, 0.5f),//11th 4 - 44
                      // glm::vec3(7.4f, 1.0f, 0.0),
                      // glm::vec3(-1.0f, 1.0f, 0.0f),
                      // glm::vec3(-1.0f, -1.8f, 0.0f),
                      // glm::vec3(7.4f, -1.8f, 0.0f),//2nd 4 - 8
                     };

glm::vec4 wing_torso_positions[]={glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[1],1.0f),//17th triangle
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[2],1.0f),//18th triangle
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[3],1.0f),//19th triangle
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[4],1.0f),//20th triangle
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[5],1.0f),//21th triangle
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[6],1.0f),//22th triangle
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[7],1.0f),//23th triangle
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[8],1.0f),//24th triangle

                         glm::vec4(vertices[19],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[10],1.0f),//25th triangle
                         glm::vec4(vertices[19],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[11],1.0f),//26th triangle
                         glm::vec4(vertices[19],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[12],1.0f),//27th triangle
                         glm::vec4(vertices[19],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[13],1.0f),//28th triangle
                         glm::vec4(vertices[19],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[14],1.0f),//29th triangle
                         glm::vec4(vertices[19],1.0f),
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[15],1.0f),//30th triangle
                         glm::vec4(vertices[19],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[16],1.0f),//31th triangle
                         glm::vec4(vertices[19],1.0f),
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[17],1.0f),//32th triangle

                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[11],1.0f),//9th quad
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[12],1.0f),//10th quad
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[13],1.0f),//11th quad
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[14],1.0f),//12th quad
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[15],1.0f),//13th quad
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[16],1.0f),//14th quad
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[17],1.0f),//15th quad
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[18],1.0f),//16th quad

                         //semi-circle
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[20],1.0f),
                         glm::vec4(vertices[21],1.0f),//17th triangle
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[21],1.0f),
                         glm::vec4(vertices[22],1.0f),//18th triangle
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[23],1.0f),//19th triangle
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[24],1.0f),//20th triangle
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[24],1.0f),
                         glm::vec4(vertices[25],1.0f),//21th triangle
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[25],1.0f),
                         glm::vec4(vertices[26],1.0f),//22th triangle
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[26],1.0f),
                         glm::vec4(vertices[27],1.0f),//23th triangle
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[27],1.0f),
                         glm::vec4(vertices[28],1.0f),//24th triangle

                         glm::vec4(vertices[39],1.0f),
                         glm::vec4(vertices[31],1.0f),
                         glm::vec4(vertices[30],1.0f),//25th triangle
                         glm::vec4(vertices[39],1.0f),
                         glm::vec4(vertices[32],1.0f),
                         glm::vec4(vertices[31],1.0f),//26th triangle
                         glm::vec4(vertices[39],1.0f),
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[32],1.0f),//27th triangle
                         glm::vec4(vertices[39],1.0f),
                         glm::vec4(vertices[34],1.0f),
                         glm::vec4(vertices[33],1.0f),//28th triangle
                         glm::vec4(vertices[39],1.0f),
                         glm::vec4(vertices[35],1.0f),
                         glm::vec4(vertices[34],1.0f),//29th triangle
                         glm::vec4(vertices[39],1.0f),
                         glm::vec4(vertices[36],1.0f),
                         glm::vec4(vertices[35],1.0f),//30th triangle
                         glm::vec4(vertices[39],1.0f),
                         glm::vec4(vertices[37],1.0f),
                         glm::vec4(vertices[36],1.0f),//31th triangle
                         glm::vec4(vertices[39],1.0f),
                         glm::vec4(vertices[38],1.0f),
                         glm::vec4(vertices[37],1.0f),//32th triangle

                         glm::vec4(vertices[20],1.0f),
                         glm::vec4(vertices[30],1.0f),
                         glm::vec4(vertices[21],1.0f),
                         glm::vec4(vertices[21],1.0f),
                         glm::vec4(vertices[30],1.0f),
                         glm::vec4(vertices[31],1.0f),//9th quad
                         glm::vec4(vertices[21],1.0f),
                         glm::vec4(vertices[31],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[31],1.0f),
                         glm::vec4(vertices[32],1.0f),//10th quad
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[32],1.0f),
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[32],1.0f),
                         glm::vec4(vertices[33],1.0f),//11th quad
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[24],1.0f),
                         glm::vec4(vertices[24],1.0f),
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[34],1.0f),//12th quad
                         glm::vec4(vertices[24],1.0f),
                         glm::vec4(vertices[34],1.0f),
                         glm::vec4(vertices[25],1.0f),
                         glm::vec4(vertices[25],1.0f),
                         glm::vec4(vertices[34],1.0f),
                         glm::vec4(vertices[35],1.0f),//13th quad
                         glm::vec4(vertices[25],1.0f),
                         glm::vec4(vertices[35],1.0f),
                         glm::vec4(vertices[26],1.0f),
                         glm::vec4(vertices[26],1.0f),
                         glm::vec4(vertices[35],1.0f),
                         glm::vec4(vertices[36],1.0f),//14th quad
                         glm::vec4(vertices[26],1.0f),
                         glm::vec4(vertices[36],1.0f),
                         glm::vec4(vertices[27],1.0f),
                         glm::vec4(vertices[27],1.0f),
                         glm::vec4(vertices[36],1.0f),
                         glm::vec4(vertices[37],1.0f),//15th quad
                         glm::vec4(vertices[27],1.0f),
                         glm::vec4(vertices[37],1.0f),
                         glm::vec4(vertices[28],1.0f),
                         glm::vec4(vertices[28],1.0f),
                         glm::vec4(vertices[37],1.0f),
                         glm::vec4(vertices[38],1.0f),//16th quad


                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[42],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[42],1.0f),
                         glm::vec4(vertices[43],1.0f),//17th quad
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[40],1.0f),
                         glm::vec4(vertices[40],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[41],1.0f),//18th quad
                         glm::vec4(vertices[40],1.0f),
                         glm::vec4(vertices[41],1.0f),
                         glm::vec4(vertices[38],1.0f),
                         glm::vec4(vertices[38],1.0f),
                         glm::vec4(vertices[41],1.0f),
                         glm::vec4(vertices[28],1.0f),//19th quad
                         glm::vec4(vertices[42],1.0f),
                         glm::vec4(vertices[30],1.0f),
                         glm::vec4(vertices[43],1.0f),
                         glm::vec4(vertices[43],1.0f),
                         glm::vec4(vertices[30],1.0f),
                         glm::vec4(vertices[20],1.0f),//20th quad
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[42],1.0f),
                         glm::vec4(vertices[42],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[40],1.0f),//21th quad
                         glm::vec4(vertices[42],1.0f),
                         glm::vec4(vertices[40],1.0f),
                         glm::vec4(vertices[30],1.0f),
                         glm::vec4(vertices[30],1.0f),
                         glm::vec4(vertices[40],1.0f),
                         glm::vec4(vertices[38],1.0f),//22th quad
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[43],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[43],1.0f),
                         glm::vec4(vertices[41],1.0f),//23th quad
                         glm::vec4(vertices[41],1.0f),
                         glm::vec4(vertices[43],1.0f),
                         glm::vec4(vertices[28],1.0f),
                         glm::vec4(vertices[28],1.0f),
                         glm::vec4(vertices[43],1.0f),
                         glm::vec4(vertices[20],1.0f),//24th quad

                         };

int len = sizeof(wing_torso_positions)/16;
copy_col_norm(len, normals, colors, positions, wing_torso_positions, glm::vec4(0.1f, 1.0f, 0.1f, 1.0f));
}

//shoulder pads
const glm::mat4 shoulder_pad_transform = glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(3.4f, 4.89f, 0.0f)), glm::atan(-5.25f, 0.7f), glm::vec3(0.0f, 0.0f, 1.0f));
const int shoulder_pad_size = 2*(69);
void shoulder_pad(glm::vec4 positions[shoulder_pad_size], glm::vec3 normals[shoulder_pad_size], glm::vec4 colors[shoulder_pad_size])
{
glm::mat4 reflect = {glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),glm::vec4(0.0f, 0.0f, -1.0f, 0.0f),glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),};
glm::mat3 reflect2 = {glm::vec3(1.0f, 0.0f, 0.0f),glm::vec3(0.0f, 1.0f, 0.0f),glm::vec3(0.0f, 0.0f, -1.0f)};

glm::vec3 vertices[]={glm::vec3(0.0f-0.5f, 0.0f-0.866f, 1.1f),
                      glm::vec3(5.2f-0.5, 0.0f-0.866, 1.1f),
                      glm::vec3(-0.5f-0.5, 0.866f-0.866, 1.1f),
                      glm::vec3(-0.15f-0.5, 2.0f-0.866, 1.1f),//top4 - 4
                      glm::vec3(5.1f-0.5, 1.3f-0.866, 1.1f),
                      glm::vec3(0.5f-0.5, 2.9f-0.866, 0.0f),
                      glm::vec3(5.0f-0.5, 2.1f-0.866, 0.0f),

                      glm::vec3(0.0f-0.5, 0.0f-0.866, 1.0f),//2nd 4 - 8
                      glm::vec3(5.2f-0.5, 0.0f-0.866, 1.0f),
                      glm::vec3(-0.5f-0.5, 0.866f-0.866, 1.0f),
                      glm::vec3(-0.15f-0.5, 2.0f-0.866, 1.0f),
                      glm::vec3(5.1f-0.5, 1.2f-0.866, 1.0f),//3rd 4 - 12
                      glm::vec3(0.5f-0.5, 2.8f-0.866, 0.0f),
                      glm::vec3(5.0f-0.5, 2.0f-0.866, 0.0f),
                     };

glm::vec4 shoulder_pad_positions[]={glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[1],1.0f),//1th quad
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[4],1.0f),//2th quad
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[4],1.0f),

                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[10],1.0f),//3.5th quad
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[12],1.0f),//4.5th quad
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[13],1.0f),//5th quad

                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[8],1.0f),//6th quad
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[11],1.0f),//7th quad
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[13],1.0f),//8th quad
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[7],1.0f),//9th quad
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[9],1.0f),//10th quad
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[10],1.0f),//11th quad

                         glm::vec4(-0.65f, 1.134f, 0.0f, 1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[3],1.0f),//1st triangle
                         };

int len = sizeof(shoulder_pad_positions)/16;
copy_col_norm(len, normals, colors, positions, shoulder_pad_positions, glm::vec4(1.0f), true, reflect, reflect2);
}

//wings
const glm::mat4 wing_transform = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(-1.4f, 0.0f, 0.0f)), glm::vec3(-1.0f, 1.0f, 1.0f));
const int wing_size = 24;
void wing(glm::vec4 positions[wing_size], glm::vec3 normals[wing_size], glm::vec4 colors[wing_size])
{
glm::vec3 vertices[]={glm::vec3(3.3f, -4.0f, 0.0f),
                      glm::vec3(0.0f, -4.0f, 0.0f),
                      glm::vec3(0.0f, 8.4f, 0.0f),

                      glm::vec3(3.3f, -4.0f, 0.25f),
                      glm::vec3(0.0f, -4.0f, 0.25f),
                      glm::vec3(0.0f, 8.4f, 0.25f),
                     };

glm::vec4 wing_positions[]={glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[3],1.0f),//1st 2 triangles
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[0],1.0f),//2nd quad
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[2],1.0f),//3rd quad
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[1],1.0f),//4th quad
                         };

int len = sizeof(wing_positions)/16;
copy_col_norm(len, normals, colors, positions, wing_positions, glm::vec4(0.1f, 1.0f, 1.0f, 1.0f));
}

//foot
const glm::mat4 foot_transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -6.05f, -0.75f));
const int foot_size = 2*(84);
void foot(glm::vec4 positions[foot_size], glm::vec3 normals[foot_size], glm::vec4 colors[foot_size])
{
glm::mat4 reflect = {glm::vec4(-1.0f, 0.0f, 0.0f, 0.0f),glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),};
glm::mat3 reflect2 = {glm::vec3(-1.0f, 0.0f, 0.0f),glm::vec3(0.0f, 1.0f, 0.0f),glm::vec3(0.0f, 0.0f, 1.0f)};
const float z=1.75, y=0.75;
glm::vec3 vertices[]={glm::vec3(0.0f, 0.0f-y, 0.0f-z),
                      glm::vec3(0.9f, 0.0f-y, 0.2f-z),
                      glm::vec3(0.75f, 0.0f-y, 5.8f-z),
                      glm::vec3(0.0f, 0.0f-y, 6.2f-z),//top4 - 4
                      glm::vec3(0.0f, 1.05f-y, 5.8f-z),
                      glm::vec3(0.7f, 1.1f-y, 5.4f-z),
                      glm::vec3(0.0f, 0.7f-y, 0.2f-z),
                      glm::vec3(0.9f, 0.85f-y, 0.4f-z),//2nd 4 - 8
                      glm::vec3(0.9f, 1.25f-y, 1.0f-z),
                      glm::vec3(0.0f, 1.25f-y, 1.0f-z),
                      glm::vec3(0.8f, 1.9f-y, 1.0f-z),
                      glm::vec3(0.0f, 1.9f-y, 1.0f-z),//3rd 4 - 12
                      glm::vec3(0.9f, 1.95f-y, 3.3f-z),
                      glm::vec3(0.0f, 1.9f-y, 3.5f-z),
                      glm::vec3(0.9f, 2.5f-y, 1.5f-z),
                      glm::vec3(0.0f, 2.5f-y, 1.5f-z),//4th 4 - 16
                      glm::vec3(0.8f, 3.25f-y, 1.5f-z),
                      glm::vec3(0.0f, 3.25f-y, 1.5f-z),
                      glm::vec3(0.8f, 3.25f-y, 2.3f-z),
                      glm::vec3(0.0f, 3.25f-y, 2.8f-z),//5th - 20
                     };

glm::vec4 foot_positions[]={glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[1],1.0f),//1st quad
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[2],1.0f),//2nd quad
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[7],1.0f),//3rd quad
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[8],1.0f),//4th quad
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[10],1.0f),//5th quad
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[14],1.0f),//6th quad
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[16],1.0f),//7th quad
                         glm::vec4(vertices[19],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[17],1.0f),//8th quad
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[5],1.0f),//9th quad
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[19],1.0f),
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[18],1.0f),//10th quad
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[7],1.0f),//11th quad
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[12],1.0f),//12th quad
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[14],1.0f),//13th quad
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[16],1.0f),//14th quad
                         };

int len = sizeof(foot_positions)/16;
copy_col_norm(len, normals, colors, positions, foot_positions, glm::vec4(1.0f), true, reflect, reflect2);
}

//lower leg
const glm::mat4 lower_leg_transform = glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(-1.0f, 1.0f, 1.0f)), glm::vec3(0.0f, -1.0f, -0.3f));
const int lower_leg_size = 249;
void lower_leg(glm::vec4 positions[lower_leg_size], glm::vec3 normals[lower_leg_size], glm::vec4 colors[lower_leg_size])
{const float y = 0.2, x=y+0.3;
const float cent_y = 6.5, cent_z = 2-x;
glm::vec3 vertices[]={glm::vec3(-1.3f, 0.0f-cent_y, 0.0f-cent_z),
                      glm::vec3(-1.3f, 1.6f-cent_y, 0.0f-cent_z),
                      glm::vec3(-1.3f, 2.2f-cent_y, 0.5f-cent_z),
                      glm::vec3(-1.3f, 0.0f-cent_y, 0.5f-cent_z),//top4 - 4
                      glm::vec3(-1.3f, 0.0f-cent_y, 2.3f-cent_z),
                      glm::vec3(-1.1f, 0.0f-cent_y, 3.5f-cent_z),
                      glm::vec3(-1.1f, 2.9f-cent_y, 3.5f-cent_z),
                      glm::vec3(-1.3f, 3.2f-cent_y, 2.3f-cent_z),//2nd 4 - 8
                      glm::vec3(-1.3f, 7.5f-cent_y, 0.5f-cent_z),
                      glm::vec3(-1.3f, 7.5f-cent_y, 2.3f-cent_z-x),
                      glm::vec3(-1.8f, 6.4f-cent_y, 0.8f-cent_z-y),
                      glm::vec3(-1.8f, 6.4f-cent_y, 2.0f-cent_z-x),//3rd 4 - 12
                      glm::vec3(-1.8f, 0.5f-cent_y, 0.8f-cent_z),
                      glm::vec3(-1.8f, 0.5f-cent_y, 2.0f-cent_z),
                      glm::vec3(-1.3f, 7.5f-cent_y, 3.2f-cent_z-x),
                      glm::vec3(1.3f, 7.5f-cent_y, 3.2f-cent_z-x),//4th 4 - 16
                      glm::vec3(0.0f, 7.0f-cent_y, 3.9f-cent_z-x),
                      glm::vec3(0.0f, 3.0f-cent_y, 3.0f-cent_z),
                      glm::vec3(1.3f, 3.2f-cent_y, 2.3f-cent_z),
                      glm::vec3(1.1f, 2.9f-cent_y, 3.5f-cent_z),//5th 4 - 20
                      glm::vec3(1.3f, 7.5f-cent_y, 2.3f-cent_z-x),  //alternatively try 1.0 instead of 1.3
                      glm::vec3(1.3f, 7.5f-cent_y, 0.5f-cent_z),
                      glm::vec3(1.3f, 2.2f-cent_y, 0.5f-cent_z),
                      glm::vec3(1.3f, 1.6f-cent_y, 0.0f-cent_z),//6th 4 - 24
                      glm::vec3(1.3f, 0.0f-cent_y, 0.0f-cent_z),
                      glm::vec3(1.1f, 0.0f-cent_y, 3.5f-cent_z),
                      glm::vec3(0.9f, 0.0f-cent_y, 0.0f-cent_z),
                      glm::vec3(-0.9f, 0.0f-cent_y, 0.0f-cent_z),//7th 4 - 28
                      glm::vec3(0.9f, 1.6f-cent_y, 0.0f-cent_z),
                      glm::vec3(-0.9f, 1.6f-cent_y, 0.0f-cent_z),
                      glm::vec3(0.9f, 2.2f-cent_y, 0.5f-cent_z),
                      glm::vec3(-0.9f, 2.2f-cent_y, 0.5f-cent_z),//8th 4 - 32
                      glm::vec3(0.9f, 2.95f-cent_y, 0.5f-cent_z),
                      glm::vec3(-0.9f, 2.95f-cent_y, 0.5f-cent_z),
                      glm::vec3(0.8f, 5.5f-cent_y, 0.5f-cent_z),
                      glm::vec3(-0.8f, 5.5f-cent_y, 0.5f-cent_z),//9th 4 - 36
                      glm::vec3(0.8f, 7.5f-cent_y, 0.5f-cent_z),
                      glm::vec3(-0.8f, 7.5f-cent_y, 0.5f-cent_z),
                      glm::vec3(-0.9f, 0.0f-cent_y, 3.5f-cent_z),
                      glm::vec3(0.9f, 0.0f-cent_y, 3.5f-cent_z),//10th 4 - 40
                      glm::vec3(-0.9f, 2.7f-cent_y, 3.5f-cent_z),
                      glm::vec3(0.9f, 2.7f-cent_y, 3.5f-cent_z),
                      glm::vec3(0.8f, 5.85f-cent_y, 3.0f-cent_z-x),
                      glm::vec3(-0.8f, 5.85f-cent_y, 3.0f-cent_z-x),//11th 4 - 44
                      glm::vec3(0.8f, 7.5f-cent_y, 3.2f-cent_z-x),
                      glm::vec3(-0.8f, 7.5f-cent_y, 3.2f-cent_z-x),
                     };

glm::vec4 lower_leg_positions[]={glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[1],1.0f),//1st quad
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[7],1.0f),//2nd quad
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[8],1.0f),//3rd quad
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[13],1.0f),//4th quad
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[11],1.0f),//5th quad
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[10],1.0f),//6th quad
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[10],1.0f),//7th quad
                         glm::vec4(vertices[19],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[19],1.0f),//8th quad
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[15],1.0f),//9th quad
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[17],1.0f),//10th quad
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[9],1.0f),//11th quad   Alternatively, replace 9 by 7 nad 17 by 14
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[20],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[20],1.0f),
                         glm::vec4(vertices[18],1.0f),//12th quad
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[20],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[21],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[20],1.0f),//13th quad
                         glm::vec4(vertices[24],1.0f),
                         glm::vec4(vertices[25],1.0f),
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[25],1.0f),//14th quad
                         glm::vec4(vertices[19],1.0f),
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[25],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[25],1.0f),
                         glm::vec4(vertices[18],1.0f),//15th quad
                         glm::vec4(vertices[24],1.0f),
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[26],1.0f),
                         glm::vec4(vertices[26],1.0f),
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[28],1.0f),//16th quad
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[27],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[27],1.0f),
                         glm::vec4(vertices[29],1.0f),//17th quad
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[28],1.0f),
                         glm::vec4(vertices[28],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[30],1.0f),//18th quad
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[31],1.0f),//19th quad
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[32],1.0f),
                         glm::vec4(vertices[35],1.0f),
                         glm::vec4(vertices[35],1.0f),
                         glm::vec4(vertices[32],1.0f),
                         glm::vec4(vertices[34],1.0f),//20th quad
                         glm::vec4(vertices[30],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[32],1.0f),
                         glm::vec4(vertices[36],1.0f),
                         glm::vec4(vertices[34],1.0f),
                         glm::vec4(vertices[21],1.0f),//21th quad
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[21],1.0f),
                         glm::vec4(vertices[32],1.0f),
                         glm::vec4(vertices[32],1.0f),
                         glm::vec4(vertices[21],1.0f),
                         glm::vec4(vertices[34],1.0f),//22th quad
                         glm::vec4(vertices[31],1.0f),
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[37],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[35],1.0f),//23th quad
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[35],1.0f),//24th quad
                         glm::vec4(vertices[38],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[40],1.0f),
                         glm::vec4(vertices[40],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[6],1.0f),//25th quad
                         glm::vec4(vertices[40],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[41],1.0f),
                         glm::vec4(vertices[41],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[19],1.0f),//26th quad
                         glm::vec4(vertices[39],1.0f),
                         glm::vec4(vertices[41],1.0f),
                         glm::vec4(vertices[25],1.0f),
                         glm::vec4(vertices[25],1.0f),
                         glm::vec4(vertices[41],1.0f),
                         glm::vec4(vertices[19],1.0f),//27th quad
                         glm::vec4(vertices[40],1.0f),
                         glm::vec4(vertices[41],1.0f),
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[41],1.0f),
                         glm::vec4(vertices[32],1.0f),//28th quad
                         glm::vec4(vertices[38],1.0f),
                         glm::vec4(vertices[40],1.0f),
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[38],1.0f),
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[31],1.0f),//29th quad
                         glm::vec4(vertices[38],1.0f),
                         glm::vec4(vertices[31],1.0f),
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[38],1.0f),
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[27],1.0f),//30th quad
                         glm::vec4(vertices[39],1.0f),
                         glm::vec4(vertices[26],1.0f),
                         glm::vec4(vertices[28],1.0f),
                         glm::vec4(vertices[39],1.0f),
                         glm::vec4(vertices[28],1.0f),
                         glm::vec4(vertices[30],1.0f),//31th quad
                         glm::vec4(vertices[39],1.0f),
                         glm::vec4(vertices[30],1.0f),
                         glm::vec4(vertices[32],1.0f),
                         glm::vec4(vertices[39],1.0f),
                         glm::vec4(vertices[32],1.0f),
                         glm::vec4(vertices[41],1.0f),//32th quad
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[38],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[38],1.0f),
                         glm::vec4(vertices[27],1.0f),//33th quad
                         glm::vec4(vertices[39],1.0f),
                         glm::vec4(vertices[25],1.0f),
                         glm::vec4(vertices[26],1.0f),
                         glm::vec4(vertices[26],1.0f),
                         glm::vec4(vertices[25],1.0f),
                         glm::vec4(vertices[24],1.0f),//34th quad
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[45],1.0f),
                         glm::vec4(vertices[45],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[37],1.0f),//35th quad
                         glm::vec4(vertices[43],1.0f),
                         glm::vec4(vertices[35],1.0f),
                         glm::vec4(vertices[42],1.0f),
                         glm::vec4(vertices[42],1.0f),
                         glm::vec4(vertices[35],1.0f),
                         glm::vec4(vertices[34],1.0f),//36th quad
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[44],1.0f),
                         glm::vec4(vertices[21],1.0f),
                         glm::vec4(vertices[21],1.0f),
                         glm::vec4(vertices[44],1.0f),
                         glm::vec4(vertices[36],1.0f),//37th quad
                         glm::vec4(vertices[45],1.0f),
                         glm::vec4(vertices[37],1.0f),
                         glm::vec4(vertices[43],1.0f),
                         glm::vec4(vertices[43],1.0f),
                         glm::vec4(vertices[37],1.0f),
                         glm::vec4(vertices[35],1.0f),//38th quad
                         glm::vec4(vertices[45],1.0f),
                         glm::vec4(vertices[43],1.0f),
                         glm::vec4(vertices[44],1.0f),
                         glm::vec4(vertices[44],1.0f),
                         glm::vec4(vertices[43],1.0f),
                         glm::vec4(vertices[42],1.0f),//39th quad
                         glm::vec4(vertices[44],1.0f),
                         glm::vec4(vertices[42],1.0f),
                         glm::vec4(vertices[36],1.0f),
                         glm::vec4(vertices[36],1.0f),
                         glm::vec4(vertices[42],1.0f),
                         glm::vec4(vertices[34],1.0f),//40th quad

                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[9],1.0f),//1st triangle


                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[5],1.0f),//41th quad
                         };

int len = sizeof(lower_leg_positions)/16;
copy_col_norm(len, normals, colors, positions, lower_leg_positions, glm::vec4(1.0f));
}

//thigh updated (with circles)
const glm::mat4 thigh_transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
const int thigh_size = 288;
void thigh(glm::vec4 positions[thigh_size], glm::vec3 normals[thigh_size], glm::vec4 colors[thigh_size])
{
glm::vec3 vertices[]={glm::vec3(-0.9f, 0.0f, -1.0f),
                      glm::vec3(0.9f, 0.0f, -1.0f),
                      glm::vec3(0.9f, 0.0f, 1.0f),
                      glm::vec3(-0.9f, 0.0f, 1.0f),//top4 - 4
                      glm::vec3(-0.8f, -2.8f, -1.0f),
                      glm::vec3(0.8f, -2.8f, -1.0f),
                      glm::vec3(0.8f, -2.8f, 0.8f),
                      glm::vec3(-0.8f, -2.8f, 0.8f),//2nd 4 - 8
                      glm::vec3(-0.9f, 0.0f, -0.45f),
                      glm::vec3(0.9f, 0.0f, -0.45f),
                      glm::vec3(0.9f, 0.0f, 0.45f),
                      glm::vec3(-0.9f, 0.0f, 0.45f),//3rd 4 - 12
                      glm::vec3(-0.9f, -0.9f, -0.45f),
                      glm::vec3(0.9f, -0.9f, -0.45f),
                      glm::vec3(0.9f, -0.9f, 0.45f),
                      glm::vec3(-0.9f, -0.9f, 0.45f),//4th 4 - 16

                      //semi-circle 1
                      glm::vec3(-0.9f*0.7, 0.0f*0.7, 0.7f),
                      glm::vec3(-0.8315f*0.7, 0.3444f*0.7, 0.7f),
                      glm::vec3(-0.6364f*0.7, 0.6364f*0.7, 0.7f),
                      glm::vec3(-0.3444f*0.7, 0.8315f*0.7, 0.7f),//5th 4 - 20
                      glm::vec3(0.0f*0.7, 0.9f*0.7, 0.7f),
                      glm::vec3(0.3444f*0.7, 0.8315f*0.7, 0.7f),
                      glm::vec3(0.6364f*0.7, 0.6364f*0.7, 0.7f),
                      glm::vec3(0.8315f*0.7, 0.3444f*0.7, 0.7f),//6th 4 - 24
                      glm::vec3(0.9f*0.7, 0.0f*0.7, 0.7f),
                      glm::vec3(0.0f, 0.0f, 1.0f),

                      glm::vec3(-0.9f, 0.0f, 0.45f),
                      glm::vec3(-0.8315f, 0.3444f, 0.45f),//7th 4 - 28
                      glm::vec3(-0.6364f, 0.6364f, 0.45f),
                      glm::vec3(-0.3444f, 0.8315f, 0.45f),
                      glm::vec3(0.0f, 0.9f, 0.45f),
                      glm::vec3(0.3444f, 0.8315f, 0.45f),//8th 4 - 32
                      glm::vec3(0.6364f, 0.6364f, 0.45f),
                      glm::vec3(0.8315f, 0.3444f, 0.45f),
                      glm::vec3(0.9f, 0.0f, 0.45f),
                      glm::vec3(0.0f, 0.0f, 0.45f),//9th 4 - 36

                      //semi-circle 2
                      glm::vec3(-0.9f, 0.0f, -0.45f),
                      glm::vec3(-0.8315f, 0.3444f, -0.45f),
                      glm::vec3(-0.6364f, 0.6364f, -0.45f),
                      glm::vec3(-0.3444f, 0.8315f, -0.45f),//10th 4 - 40
                      glm::vec3(0.0f, 0.9f, -0.45f),
                      glm::vec3(0.3444f, 0.8315f, -0.45f),
                      glm::vec3(0.6364f, 0.6364f, -0.45f),
                      glm::vec3(0.8315f, 0.3444f, -0.45f),//11th 4 - 44
                      glm::vec3(0.9f, 0.0f, -0.45f),
                      glm::vec3(0.0f, 0.0f, -0.45f),

                      glm::vec3(-0.9f*0.7, 0.0f*0.7, -0.7f),
                      glm::vec3(-0.8315f*0.7, 0.3444f*0.7, -0.7f),//12th 4 - 48
                      glm::vec3(-0.6364f*0.7, 0.6364f*0.7, -0.7f),
                      glm::vec3(-0.3444f*0.7, 0.8315f*0.7, -0.7f),
                      glm::vec3(0.0f*0.7, 0.9f*0.7, -0.7f),
                      glm::vec3(0.3444f*0.7, 0.8315f*0.7, -0.7f),//13th 4 - 52
                      glm::vec3(0.6364f*0.7, 0.6364f*0.7, -0.7f),
                      glm::vec3(0.8315f*0.7, 0.3444f*0.7, -0.7f),
                      glm::vec3(0.9f*0.7, 0.0f*0.7, -0.7f),
                      glm::vec3(0.0f, 0.0f, -1.0f),//14th 4 - 56
                     };

glm::vec4 thigh_positions[]={glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[1],1.0f),//1st quad
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[2],1.0f),//2nd quad
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[13],1.0f),//3rd quad
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[12],1.0f),//4th quad
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[15],1.0f),//5th quad
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[15],1.0f),//5th quad
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[14],1.0f),//6th quad
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[13],1.0f),//7th quad
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[14],1.0f),//8th quad
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[25],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[25],1.0f),
                         glm::vec4(vertices[2],1.0f),//9th quad
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[55],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[55],1.0f),
                         glm::vec4(vertices[5],1.0f),//10th quad
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[5],1.0f),//11th quad
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[45],1.0f),
                         glm::vec4(vertices[45],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[13],1.0f),//12th quad
                         glm::vec4(vertices[35],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[35],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[10],1.0f),//13th quad

                         //semi-circle 1
                         glm::vec4(vertices[25],1.0f),
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[17],1.0f),//1st triangle
                         glm::vec4(vertices[25],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[18],1.0f),//2nd triangle
                         glm::vec4(vertices[25],1.0f),
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[19],1.0f),//3rd triangle
                         glm::vec4(vertices[25],1.0f),
                         glm::vec4(vertices[19],1.0f),
                         glm::vec4(vertices[20],1.0f),//4th triangle
                         glm::vec4(vertices[25],1.0f),
                         glm::vec4(vertices[20],1.0f),
                         glm::vec4(vertices[21],1.0f),//5th triangle
                         glm::vec4(vertices[25],1.0f),
                         glm::vec4(vertices[21],1.0f),
                         glm::vec4(vertices[22],1.0f),//6th triangle
                         glm::vec4(vertices[25],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[23],1.0f),//7th triangle
                         glm::vec4(vertices[25],1.0f),
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[24],1.0f),//8th triangle

                         glm::vec4(vertices[35],1.0f),
                         glm::vec4(vertices[27],1.0f),
                         glm::vec4(vertices[26],1.0f),//9th triangle
                         glm::vec4(vertices[35],1.0f),
                         glm::vec4(vertices[28],1.0f),
                         glm::vec4(vertices[27],1.0f),//10th triangle
                         glm::vec4(vertices[35],1.0f),
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[28],1.0f),//11th triangle
                         glm::vec4(vertices[35],1.0f),
                         glm::vec4(vertices[30],1.0f),
                         glm::vec4(vertices[29],1.0f),//12th triangle
                         glm::vec4(vertices[35],1.0f),
                         glm::vec4(vertices[31],1.0f),
                         glm::vec4(vertices[30],1.0f),//13th triangle
                         glm::vec4(vertices[35],1.0f),
                         glm::vec4(vertices[32],1.0f),
                         glm::vec4(vertices[31],1.0f),//14th triangle
                         glm::vec4(vertices[35],1.0f),
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[32],1.0f),//15th triangle
                         glm::vec4(vertices[35],1.0f),
                         glm::vec4(vertices[34],1.0f),
                         glm::vec4(vertices[33],1.0f),//16th triangle

                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[26],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[26],1.0f),
                         glm::vec4(vertices[27],1.0f),//14th quad
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[27],1.0f),
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[27],1.0f),
                         glm::vec4(vertices[28],1.0f),//15th quad
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[28],1.0f),
                         glm::vec4(vertices[19],1.0f),
                         glm::vec4(vertices[19],1.0f),
                         glm::vec4(vertices[28],1.0f),
                         glm::vec4(vertices[29],1.0f),//16th quad
                         glm::vec4(vertices[19],1.0f),
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[20],1.0f),
                         glm::vec4(vertices[20],1.0f),
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[30],1.0f),//17th quad
                         glm::vec4(vertices[20],1.0f),
                         glm::vec4(vertices[30],1.0f),
                         glm::vec4(vertices[21],1.0f),
                         glm::vec4(vertices[21],1.0f),
                         glm::vec4(vertices[30],1.0f),
                         glm::vec4(vertices[31],1.0f),//18th quad
                         glm::vec4(vertices[21],1.0f),
                         glm::vec4(vertices[31],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[31],1.0f),
                         glm::vec4(vertices[32],1.0f),//19th quad
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[32],1.0f),
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[32],1.0f),
                         glm::vec4(vertices[33],1.0f),//20th quad
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[24],1.0f),
                         glm::vec4(vertices[24],1.0f),
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[34],1.0f),//21th quad

                         //semi-circle 2
                         glm::vec4(vertices[45],1.0f),
                         glm::vec4(vertices[36],1.0f),
                         glm::vec4(vertices[37],1.0f),//17th triangle
                         glm::vec4(vertices[45],1.0f),
                         glm::vec4(vertices[37],1.0f),
                         glm::vec4(vertices[38],1.0f),//18th triangle
                         glm::vec4(vertices[45],1.0f),
                         glm::vec4(vertices[38],1.0f),
                         glm::vec4(vertices[39],1.0f),//19th triangle
                         glm::vec4(vertices[45],1.0f),
                         glm::vec4(vertices[39],1.0f),
                         glm::vec4(vertices[40],1.0f),//20th triangle
                         glm::vec4(vertices[45],1.0f),
                         glm::vec4(vertices[40],1.0f),
                         glm::vec4(vertices[41],1.0f),//21th triangle
                         glm::vec4(vertices[45],1.0f),
                         glm::vec4(vertices[41],1.0f),
                         glm::vec4(vertices[42],1.0f),//22th triangle
                         glm::vec4(vertices[45],1.0f),
                         glm::vec4(vertices[42],1.0f),
                         glm::vec4(vertices[43],1.0f),//23th triangle
                         glm::vec4(vertices[45],1.0f),
                         glm::vec4(vertices[43],1.0f),
                         glm::vec4(vertices[44],1.0f),//24th triangle

                         glm::vec4(vertices[55],1.0f),
                         glm::vec4(vertices[47],1.0f),
                         glm::vec4(vertices[46],1.0f),//25th triangle
                         glm::vec4(vertices[55],1.0f),
                         glm::vec4(vertices[48],1.0f),
                         glm::vec4(vertices[47],1.0f),//26th triangle
                         glm::vec4(vertices[55],1.0f),
                         glm::vec4(vertices[49],1.0f),
                         glm::vec4(vertices[48],1.0f),//27th triangle
                         glm::vec4(vertices[55],1.0f),
                         glm::vec4(vertices[50],1.0f),
                         glm::vec4(vertices[49],1.0f),//28th triangle
                         glm::vec4(vertices[55],1.0f),
                         glm::vec4(vertices[51],1.0f),
                         glm::vec4(vertices[50],1.0f),//29th triangle
                         glm::vec4(vertices[55],1.0f),
                         glm::vec4(vertices[52],1.0f),
                         glm::vec4(vertices[51],1.0f),//30th triangle
                         glm::vec4(vertices[55],1.0f),
                         glm::vec4(vertices[53],1.0f),
                         glm::vec4(vertices[52],1.0f),//31th triangle
                         glm::vec4(vertices[55],1.0f),
                         glm::vec4(vertices[54],1.0f),
                         glm::vec4(vertices[53],1.0f),//32th triangle

                         glm::vec4(vertices[36],1.0f),
                         glm::vec4(vertices[46],1.0f),
                         glm::vec4(vertices[37],1.0f),
                         glm::vec4(vertices[37],1.0f),
                         glm::vec4(vertices[46],1.0f),
                         glm::vec4(vertices[47],1.0f),//22th quad
                         glm::vec4(vertices[37],1.0f),
                         glm::vec4(vertices[47],1.0f),
                         glm::vec4(vertices[38],1.0f),
                         glm::vec4(vertices[38],1.0f),
                         glm::vec4(vertices[47],1.0f),
                         glm::vec4(vertices[48],1.0f),//23th quad
                         glm::vec4(vertices[38],1.0f),
                         glm::vec4(vertices[48],1.0f),
                         glm::vec4(vertices[39],1.0f),
                         glm::vec4(vertices[39],1.0f),
                         glm::vec4(vertices[48],1.0f),
                         glm::vec4(vertices[49],1.0f),//24th quad
                         glm::vec4(vertices[39],1.0f),
                         glm::vec4(vertices[49],1.0f),
                         glm::vec4(vertices[40],1.0f),
                         glm::vec4(vertices[40],1.0f),
                         glm::vec4(vertices[49],1.0f),
                         glm::vec4(vertices[50],1.0f),//25th quad
                         glm::vec4(vertices[40],1.0f),
                         glm::vec4(vertices[50],1.0f),
                         glm::vec4(vertices[41],1.0f),
                         glm::vec4(vertices[41],1.0f),
                         glm::vec4(vertices[50],1.0f),
                         glm::vec4(vertices[51],1.0f),//26th quad
                         glm::vec4(vertices[41],1.0f),
                         glm::vec4(vertices[51],1.0f),
                         glm::vec4(vertices[42],1.0f),
                         glm::vec4(vertices[42],1.0f),
                         glm::vec4(vertices[51],1.0f),
                         glm::vec4(vertices[52],1.0f),//27th quad
                         glm::vec4(vertices[42],1.0f),
                         glm::vec4(vertices[52],1.0f),
                         glm::vec4(vertices[43],1.0f),
                         glm::vec4(vertices[43],1.0f),
                         glm::vec4(vertices[52],1.0f),
                         glm::vec4(vertices[53],1.0f),//28th quad
                         glm::vec4(vertices[43],1.0f),
                         glm::vec4(vertices[53],1.0f),
                         glm::vec4(vertices[44],1.0f),
                         glm::vec4(vertices[44],1.0f),
                         glm::vec4(vertices[53],1.0f),
                         glm::vec4(vertices[54],1.0f),//29th quad

                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[45],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[35],1.0f),//30th quad
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[25],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[55],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[5],1.0f),//31th quad
                         };

int len = sizeof(thigh_positions)/16;
copy_col_norm(len, normals, colors, positions, thigh_positions, glm::vec4(1.0f));
}

//hip joint (thigh to torso)
const glm::mat4 hip_joint_transform = glm::translate(glm::mat4(1.0f), glm::vec3(1.6f, -1.0f, 0.0f));
const glm::mat4 elbow_joint_transform = glm::rotate(glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.4f, 0.0f)), glm::radians(-90.0f), glm::vec3(0.0f,1.0f,0.0f)), glm::radians(90.0f), glm::vec3(0.0f,0.0f,1.0f));
const glm::mat4 wing_joint_transform = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(6.0f, 0.0f, 0.75f)), glm::vec3(-1.0f, 1.0f, 1.0f));
const glm::mat4 wing_joint_scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.4/0.9f, 1.4/0.9f, 0.5/0.9f));
const glm::mat4 elbow_joint_scale = glm::scale(glm::mat4(1.0f), glm::vec3(2.0/3.0f, 2.0/3.0f, 2.0/3.0f));
const int joint_size = 132;
void joint(glm::vec4 positions[joint_size], glm::vec3 normals[joint_size], glm::vec4 colors[joint_size])
{
glm::vec3 vertices[]={glm::vec3(-0.9f, 0.9f, -0.45f),
                      glm::vec3(-0.9f, 0.9f, 0.45f),
                      glm::vec3(-0.9f, -0.9f, -0.45f),
                      glm::vec3(-0.9f, -0.9f, 0.45f),//top4 - 4

                      //semi-circle
                      glm::vec3(0.0f, 0.9f, 0.45f),
                      glm::vec3(0.3444f, 0.8315f, 0.45f),
                      glm::vec3(0.6364f, 0.6364f, 0.45f),
                      glm::vec3(0.8315f, 0.3444f, 0.45f),//2nd 4 - 8
                      glm::vec3(0.9f, 0.0f, 0.45f),
                      glm::vec3(0.8315f, -0.3444f, 0.45f),
                      glm::vec3(0.6364f, -0.6364f, 0.45f),
                      glm::vec3(0.3444f, -0.8315f, 0.45f),//3rd 4 - 12
                      glm::vec3(0.0f, -0.9f, 0.45f),
                      glm::vec3(0.0f, 0.0f, 0.45f),

                      glm::vec3(0.0f, 0.9f, -0.45f),
                      glm::vec3(0.3444f, 0.8315f, -0.45f),//4th 4 - 16
                      glm::vec3(0.6364f, 0.6364f, -0.45f),
                      glm::vec3(0.8315f, 0.3444f, -0.45f),
                      glm::vec3(0.9f, 0.0f, -0.45f),
                      glm::vec3(0.8315f, -0.3444f, -0.45f),//5th 4 - 20
                      glm::vec3(0.6364f, -0.6364f, -0.45f),
                      glm::vec3(0.3444f, -0.8315f, -0.45f),
                      glm::vec3(0.0f, -0.9f, -0.45f),
                      glm::vec3(0.0f, 0.0f, -0.45f),//6th 4 - 24
                     };

glm::vec4 joint_positions[]={glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[1],1.0f),//1st quad
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[4],1.0f),//2nd quad
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[12],1.0f),//3rd quad
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[13],1.0f),//4th quad
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[22],1.0f),//5th quad
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[1],1.0f),//6th quad

                         //semi-circle
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[5],1.0f),//1th triangle
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[6],1.0f),//2th triangle
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[7],1.0f),//3th triangle
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[8],1.0f),//4th triangle
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[9],1.0f),//5th triangle
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[10],1.0f),//6th triangle
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[11],1.0f),//7th triangle
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[12],1.0f),//8th triangle

                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[14],1.0f),//9th triangle
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[15],1.0f),//10th triangle
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[16],1.0f),//11th triangle
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[17],1.0f),//12th triangle
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[19],1.0f),
                         glm::vec4(vertices[18],1.0f),//13th triangle
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[20],1.0f),
                         glm::vec4(vertices[19],1.0f),//14th triangle
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[21],1.0f),
                         glm::vec4(vertices[20],1.0f),//15th triangle
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[21],1.0f),//16th triangle

                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[15],1.0f),//7th quad
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[16],1.0f),//8th quad
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[17],1.0f),//9th quad
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[18],1.0f),//10th quad
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[19],1.0f),//11th quad
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[19],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[19],1.0f),
                         glm::vec4(vertices[20],1.0f),//12th quad
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[20],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[20],1.0f),
                         glm::vec4(vertices[21],1.0f),//13th quad
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[21],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[21],1.0f),
                         glm::vec4(vertices[22],1.0f),//14th quad
                         };

int len = sizeof(joint_positions)/16;
copy_col_norm(len, normals, colors, positions, joint_positions, glm::vec4(0.1f, 1.0f, 0.1f, 1.0f));
}

//torso complete
const int torso_size = 2*(363+24+30+24+9);
void torso(glm::vec4 positions[torso_size], glm::vec3 normals[torso_size], glm::vec4 colors[torso_size])
{
glm::mat4 reflect = {glm::vec4(-1.0f, 0.0f, 0.0f, 0.0f),glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),};
glm::mat3 reflect2 = {glm::vec3(-1.0f, 0.0f, 0.0f),glm::vec3(0.0f, 1.0f, 0.0f),glm::vec3(0.0f, 0.0f, 1.0f)};

glm::vec3 vertices[]={glm::vec3(0.0f, -2.8f, 1.0f),
                      glm::vec3(0.7f, -2.0f, 1.0f),
                      glm::vec3(0.7f, 0.0f, 1.0f),
                      glm::vec3(2.4f, 0.0f, 1.0f),//top4 - 4
                      glm::vec3(2.4f, 1.65f, 1.0f),
                      glm::vec3(2.0f, 1.65f, 1.2f),
                      glm::vec3(1.8f, 2.5f, 1.2f),
                      glm::vec3(2.0f, 3.6f, 1.2f),//2nd 4 - 8
                      glm::vec3(2.55f, 3.6f, 1.0f),
                      glm::vec3(2.3f, 5.8f, 1.1f),
                      glm::vec3(0.0f, 5.8f, 1.4f),
                      glm::vec3(0.0f, -2.8f, -1.475),//3rd 4 - 12 //updated 11,12
                      glm::vec3(0.7f, -2.0f, -1.475f),
                      glm::vec3(0.7f, 0.0f, -2.2f),
                      glm::vec3(2.4f, 0.0f, -2.2f),
                      glm::vec3(2.4f, 1.65f, -2.2f),//4th 4 - 16
                      glm::vec3(2.0f, 1.65f, -2.2f),
                      glm::vec3(1.8f, 2.5f, -2.2f),
                      glm::vec3(2.0f, 3.6f, -2.2f),
                      glm::vec3(2.55f, 3.6f, -2.2f),//5th 4 - 20
                      glm::vec3(2.3f, 5.8f, -2.2f),
                      glm::vec3(0.0f, 4.5f, -2.2f),
                      glm::vec3(2.0f, 1.65f, 1.0f),
                      glm::vec3(1.15f, 1.65f, 1.65f),//6th 4 - 24
                      glm::vec3(1.25f, 2.4f, 1.475f),

                      //semi-circle
                      // glm::vec3(1.4f, 3.0f, 0.0f); center
                      glm::vec3(2.107f, 3.707f, 0.95f),
                      glm::vec3(2.324f, 3.383f, 0.95f),
                      glm::vec3(2.4f, 3.0f, 0.95f),//7th 4 - 28
                      glm::vec3(2.324f, 2.617f, 0.95f),
                      glm::vec3(2.107f, 2.293f, 0.95f),
                      glm::vec3(1.783f, 2.076f, 0.95f),
                      glm::vec3(1.4f, 3.0f, 0.95f),//8th 4 - 32

                      glm::vec3(2.107f, 3.707f, -2.21f),
                      glm::vec3(2.324f, 3.383f, -2.21f),
                      glm::vec3(2.4f, 3.0f, -2.21f),
                      glm::vec3(2.324f, 2.617f, -2.21f),//9th 4 - 36
                      glm::vec3(2.107f, 2.293f, -2.21f),
                      glm::vec3(1.783f, 2.076f, -2.21f),
                      glm::vec3(1.4f, 3.0f, -2.21f),

                      glm::vec3(0.0f, -2.8f, 1.0f),//10th 4 - 40
                      glm::vec3(0.0f, -1.6f, 2.15f),
                      glm::vec3(0.5f, -1.6f, 2.0f),
                      glm::vec3(0.7f, -1.6f, 1.0f),
                      glm::vec3(0.0f, -0.3f, 2.6f),//11th 4 - 44
                      glm::vec3(0.5f, -0.3f, 2.65f),
                      glm::vec3(0.7f, -0.3f, 1.0f),
                      glm::vec3(0.0f, 0.0f, 2.85f),
                      glm::vec3(0.8f, 0.0f, 2.8f),//12th 4 - 48
                      glm::vec3(1.0f, 0.0f, 1.0f),
                      glm::vec3(1.0f, 1.65f, 1.0f),
                      glm::vec3(0.85f, 0.8f, 2.95f),
                      glm::vec3(0.0f, 0.75f, 3.0f),//13th 4 - 52
                      glm::vec3(0.88f, 0.95f, 2.6f),
                      glm::vec3(0.0f, 0.95f, 2.6f),
                      glm::vec3(0.0f, 2.0f, 2.7f),
                      glm::vec3(0.88f, 2.0f, 2.7f),//14th 5 - 56

                      //chest-beam
                      glm::vec3(0.0f, 4.1f, 1.45f),
                      glm::vec3(0.1913f, 4.062f, 1.45f),
                      glm::vec3(0.3536f, 3.954f, 1.45f),
                      glm::vec3(0.4619f, 3.791f, 1.45f),//15th 4 - 60
                      glm::vec3(0.5f, 3.6f, 1.45f),
                      glm::vec3(0.4619f, 3.409f, 1.45f),
                      glm::vec3(0.3536f, 3.246f, 1.45f),
                      glm::vec3(0.1913f, 3.138f, 1.45f),//16th 4 - 64
                      glm::vec3(0.0f, 3.1f, 1.45f),
                      glm::vec3(0.0f, 3.6f, 1.75f),

                      glm::vec3(0.0f, 4.8f, 2.45f),
                      glm::vec3(0.4592f, 4.709f, 2.431f),//17th 4 - 68
                      glm::vec3(0.8485f, 4.449f, 2.377f),
                      glm::vec3(1.109f, 4.059f, 2.296f),
                      glm::vec3(1.2f, 3.6f, 2.2f),
                      glm::vec3(1.109f, 3.141f, 2.104f),//18th 4 - 72
                      glm::vec3(0.8485f, 2.751f, 2.023f),
                      glm::vec3(0.4592f, 2.491f, 1.969f),
                      glm::vec3(0.0f, 2.4f, 1.95f),


                      glm::vec3(1.15f, 5.8f, 1.25f),//19th 4 - 76
                      glm::vec3(2.425f, 4.7f, 1.05f),
                      glm::vec3(1.9f, 3.05f, 1.2f),

                      //extensions
                      glm::vec3(0.0f, 5.8f, 0.3f),
                      glm::vec3(0.0f, 5.8f, -0.1f),//20th 4 - 80
                      glm::vec3(0.2f, 5.8f, 0.3f),
                      glm::vec3(0.2f, 5.8f, -0.1f),

                      glm::vec3(0.0f, 6.5f, 0.3f),
                      glm::vec3(0.0f, 6.5f, -0.1f),//21th 4 - 84
                      glm::vec3(0.2f, 6.5f, 0.3f),
                      glm::vec3(0.2f, 6.5f, -0.1f),

                      //hole in the back
                      glm::vec3(0.75f, 5.8f, -2.2f),
                      glm::vec3(0.75f, 4.5f, -2.2f),//22th 4 - 88
                      glm::vec3(0.75f, 4.5f, -1.1f),
                      glm::vec3(0.75f, 5.8f, -1.1f),
                      glm::vec3(0.0f, 5.8f, -1.1f),
                      glm::vec3(0.0f, 4.5f, -1.1f),//23th 4 - 92

                      //shoulder joint
                      glm::vec3(2.39f, 5.0f, 0.2f),
                      glm::vec3(2.39f, 5.0f, -0.2f),
                      glm::vec3(2.43f, 4.6f, 0.2f),
                      glm::vec3(2.43f, 4.6f, -0.2f),//24th 4 - 96
                      glm::vec3(3.39f, 5.1f, 0.2f),
                      glm::vec3(3.39f, 5.1f, -0.2f),
                      glm::vec3(3.43f, 4.7f, 0.2f),
                      glm::vec3(3.43f, 4.7f, -0.2f),//25th 4 - 100

                      //base reduction
                      glm::vec3(0.7f, 0.0f, -1.475f),
                      glm::vec3(0.0f, 0.0f, -1.475f),
                      glm::vec3(0.0f, 0.0f, -2.2f),
                     };

glm::vec4 torso_positions[]={glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[12],1.0f),//1st quad
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[100],1.0f),//2nd quad
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[14],1.0f),//3rd quad
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[15],1.0f),//4th quad
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[16],1.0f),//5th quad
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[17],1.0f),//6th quad
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[18],1.0f),//7th quad
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[19],1.0f),//8th quad
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[19],1.0f),
                         glm::vec4(vertices[19],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[20],1.0f),//9th quad
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[90],1.0f),
                         glm::vec4(vertices[90],1.0f),
                         glm::vec4(vertices[89],1.0f),
                         glm::vec4(vertices[9],1.0f),//10th quad
                         //backside
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[15],1.0f),//11th quad
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[21],1.0f),
                         glm::vec4(vertices[21],1.0f),
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[17],1.0f),//12th quad
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[100],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[100],1.0f),
                         glm::vec4(vertices[101],1.0f),//13th quad
                         glm::vec4(vertices[19],1.0f),
                         glm::vec4(vertices[20],1.0f),
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[20],1.0f),
                         glm::vec4(vertices[86],1.0f),//14th quad
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[87],1.0f),
                         glm::vec4(vertices[21],1.0f),//1st triangle

                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[24],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[24],1.0f),
                         glm::vec4(vertices[6],1.0f),//15th quad

                         //semi-circle
                         glm::vec4(vertices[31],1.0f),
                         glm::vec4(vertices[25],1.0f),
                         glm::vec4(vertices[26],1.0f),//1st triangle
                         glm::vec4(vertices[31],1.0f),
                         glm::vec4(vertices[26],1.0f),
                         glm::vec4(vertices[27],1.0f),//2nd triangle
                         glm::vec4(vertices[31],1.0f),
                         glm::vec4(vertices[27],1.0f),
                         glm::vec4(vertices[28],1.0f),//3rd triangle
                         glm::vec4(vertices[31],1.0f),
                         glm::vec4(vertices[28],1.0f),
                         glm::vec4(vertices[29],1.0f),//4th triangle
                         glm::vec4(vertices[31],1.0f),
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[30],1.0f),//5th triangle

                         glm::vec4(vertices[38],1.0f),
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[32],1.0f),//6th triangle
                         glm::vec4(vertices[38],1.0f),
                         glm::vec4(vertices[34],1.0f),
                         glm::vec4(vertices[33],1.0f),//7th triangle
                         glm::vec4(vertices[38],1.0f),
                         glm::vec4(vertices[35],1.0f),
                         glm::vec4(vertices[34],1.0f),//8th triangle
                         glm::vec4(vertices[38],1.0f),
                         glm::vec4(vertices[36],1.0f),
                         glm::vec4(vertices[35],1.0f),//9th triangle
                         glm::vec4(vertices[38],1.0f),
                         glm::vec4(vertices[37],1.0f),
                         glm::vec4(vertices[36],1.0f),//10th triangle

                         glm::vec4(vertices[25],1.0f),
                         glm::vec4(vertices[32],1.0f),
                         glm::vec4(vertices[26],1.0f),
                         glm::vec4(vertices[26],1.0f),
                         glm::vec4(vertices[32],1.0f),
                         glm::vec4(vertices[33],1.0f),//16th quad
                         glm::vec4(vertices[26],1.0f),
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[27],1.0f),
                         glm::vec4(vertices[27],1.0f),
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[34],1.0f),//17th quad
                         glm::vec4(vertices[27],1.0f),
                         glm::vec4(vertices[34],1.0f),
                         glm::vec4(vertices[28],1.0f),
                         glm::vec4(vertices[28],1.0f),
                         glm::vec4(vertices[34],1.0f),
                         glm::vec4(vertices[35],1.0f),//18th quad
                         glm::vec4(vertices[28],1.0f),
                         glm::vec4(vertices[35],1.0f),
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[35],1.0f),
                         glm::vec4(vertices[36],1.0f),//19th quad
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[36],1.0f),
                         glm::vec4(vertices[30],1.0f),
                         glm::vec4(vertices[30],1.0f),
                         glm::vec4(vertices[36],1.0f),
                         glm::vec4(vertices[37],1.0f),//20th quad

                         //torso details
                         glm::vec4(vertices[39],1.0f),
                         glm::vec4(vertices[40],1.0f),
                         glm::vec4(vertices[41],1.0f),
                         glm::vec4(vertices[39],1.0f),
                         glm::vec4(vertices[41],1.0f),
                         glm::vec4(vertices[42],1.0f),//21th quad
                         glm::vec4(vertices[40],1.0f),
                         glm::vec4(vertices[43],1.0f),
                         glm::vec4(vertices[41],1.0f),
                         glm::vec4(vertices[41],1.0f),
                         glm::vec4(vertices[43],1.0f),
                         glm::vec4(vertices[44],1.0f),//22th quad
                         glm::vec4(vertices[41],1.0f),
                         glm::vec4(vertices[44],1.0f),
                         glm::vec4(vertices[42],1.0f),
                         glm::vec4(vertices[42],1.0f),
                         glm::vec4(vertices[44],1.0f),
                         glm::vec4(vertices[45],1.0f),//23th quad
                         glm::vec4(vertices[43],1.0f),
                         glm::vec4(vertices[46],1.0f),
                         glm::vec4(vertices[44],1.0f),
                         glm::vec4(vertices[44],1.0f),
                         glm::vec4(vertices[46],1.0f),
                         glm::vec4(vertices[47],1.0f),//24th quad
                         glm::vec4(vertices[44],1.0f),
                         glm::vec4(vertices[47],1.0f),
                         glm::vec4(vertices[45],1.0f),
                         glm::vec4(vertices[45],1.0f),
                         glm::vec4(vertices[47],1.0f),
                         glm::vec4(vertices[48],1.0f),//25th quad
                         glm::vec4(vertices[48],1.0f),
                         glm::vec4(vertices[47],1.0f),
                         glm::vec4(vertices[49],1.0f),
                         glm::vec4(vertices[49],1.0f),
                         glm::vec4(vertices[47],1.0f),
                         glm::vec4(vertices[50],1.0f),//26th quad
                         glm::vec4(vertices[51],1.0f),
                         glm::vec4(vertices[50],1.0f),
                         glm::vec4(vertices[46],1.0f),
                         glm::vec4(vertices[46],1.0f),
                         glm::vec4(vertices[50],1.0f),
                         glm::vec4(vertices[47],1.0f),//27th quad
                         glm::vec4(vertices[48],1.0f),
                         glm::vec4(vertices[49],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[45],1.0f),
                         glm::vec4(vertices[48],1.0f),
                         glm::vec4(vertices[2],1.0f),//28th quad
                         glm::vec4(vertices[48],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[4],1.0f),//29th quad
                         glm::vec4(vertices[51],1.0f),
                         glm::vec4(vertices[53],1.0f),
                         glm::vec4(vertices[50],1.0f),
                         glm::vec4(vertices[50],1.0f),
                         glm::vec4(vertices[53],1.0f),
                         glm::vec4(vertices[52],1.0f),//30th quad
                         glm::vec4(vertices[53],1.0f),
                         glm::vec4(vertices[54],1.0f),
                         glm::vec4(vertices[52],1.0f),
                         glm::vec4(vertices[52],1.0f),
                         glm::vec4(vertices[54],1.0f),
                         glm::vec4(vertices[55],1.0f),//31th quad
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[52],1.0f),
                         glm::vec4(vertices[24],1.0f),
                         glm::vec4(vertices[24],1.0f),
                         glm::vec4(vertices[52],1.0f),
                         glm::vec4(vertices[55],1.0f),//32th quad
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[49],1.0f),//33th quad
                         glm::vec4(vertices[52],1.0f),
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[49],1.0f),//11th triangle
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[1],1.0f),//12th triangle

                         //chest-beam
                         glm::vec4(vertices[65],1.0f),
                         glm::vec4(vertices[56],1.0f),
                         glm::vec4(vertices[57],1.0f),//13th triangle
                         glm::vec4(vertices[65],1.0f),
                         glm::vec4(vertices[57],1.0f),
                         glm::vec4(vertices[58],1.0f),//14th triangle
                         glm::vec4(vertices[65],1.0f),
                         glm::vec4(vertices[58],1.0f),
                         glm::vec4(vertices[59],1.0f),//15th triangle
                         glm::vec4(vertices[65],1.0f),
                         glm::vec4(vertices[59],1.0f),
                         glm::vec4(vertices[60],1.0f),//16th triangle
                         glm::vec4(vertices[65],1.0f),
                         glm::vec4(vertices[60],1.0f),
                         glm::vec4(vertices[61],1.0f),//17th triangle
                         glm::vec4(vertices[65],1.0f),
                         glm::vec4(vertices[61],1.0f),
                         glm::vec4(vertices[62],1.0f),//18th triangle
                         glm::vec4(vertices[65],1.0f),
                         glm::vec4(vertices[62],1.0f),
                         glm::vec4(vertices[63],1.0f),//19th triangle
                         glm::vec4(vertices[65],1.0f),
                         glm::vec4(vertices[63],1.0f),
                         glm::vec4(vertices[64],1.0f),//20th triangle

                         glm::vec4(vertices[56],1.0f),
                         glm::vec4(vertices[66],1.0f),
                         glm::vec4(vertices[57],1.0f),
                         glm::vec4(vertices[57],1.0f),
                         glm::vec4(vertices[66],1.0f),
                         glm::vec4(vertices[67],1.0f),//34th quad
                         glm::vec4(vertices[57],1.0f),
                         glm::vec4(vertices[67],1.0f),
                         glm::vec4(vertices[58],1.0f),
                         glm::vec4(vertices[58],1.0f),
                         glm::vec4(vertices[67],1.0f),
                         glm::vec4(vertices[68],1.0f),//35th quad
                         glm::vec4(vertices[58],1.0f),
                         glm::vec4(vertices[68],1.0f),
                         glm::vec4(vertices[59],1.0f),
                         glm::vec4(vertices[59],1.0f),
                         glm::vec4(vertices[68],1.0f),
                         glm::vec4(vertices[69],1.0f),//36th quad
                         glm::vec4(vertices[59],1.0f),
                         glm::vec4(vertices[69],1.0f),
                         glm::vec4(vertices[60],1.0f),
                         glm::vec4(vertices[60],1.0f),
                         glm::vec4(vertices[69],1.0f),
                         glm::vec4(vertices[70],1.0f),//37th quad
                         glm::vec4(vertices[60],1.0f),
                         glm::vec4(vertices[70],1.0f),
                         glm::vec4(vertices[61],1.0f),
                         glm::vec4(vertices[61],1.0f),
                         glm::vec4(vertices[70],1.0f),
                         glm::vec4(vertices[71],1.0f),//38th quad
                         glm::vec4(vertices[61],1.0f),
                         glm::vec4(vertices[71],1.0f),
                         glm::vec4(vertices[62],1.0f),
                         glm::vec4(vertices[62],1.0f),
                         glm::vec4(vertices[71],1.0f),
                         glm::vec4(vertices[72],1.0f),//39th quad
                         glm::vec4(vertices[62],1.0f),
                         glm::vec4(vertices[72],1.0f),
                         glm::vec4(vertices[63],1.0f),
                         glm::vec4(vertices[63],1.0f),
                         glm::vec4(vertices[72],1.0f),
                         glm::vec4(vertices[73],1.0f),//40th quad
                         glm::vec4(vertices[63],1.0f),
                         glm::vec4(vertices[73],1.0f),
                         glm::vec4(vertices[64],1.0f),
                         glm::vec4(vertices[64],1.0f),
                         glm::vec4(vertices[73],1.0f),
                         glm::vec4(vertices[74],1.0f),//41th quad
                         glm::vec4(vertices[66],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[75],1.0f),
                         glm::vec4(vertices[66],1.0f),
                         glm::vec4(vertices[75],1.0f),
                         glm::vec4(vertices[67],1.0f),//42th quad
                         glm::vec4(vertices[67],1.0f),
                         glm::vec4(vertices[75],1.0f),
                         glm::vec4(vertices[68],1.0f),
                         glm::vec4(vertices[68],1.0f),
                         glm::vec4(vertices[75],1.0f),
                         glm::vec4(vertices[9],1.0f),//43th quad
                         glm::vec4(vertices[68],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[76],1.0f),
                         glm::vec4(vertices[68],1.0f),
                         glm::vec4(vertices[76],1.0f),
                         glm::vec4(vertices[69],1.0f),//44th quad
                         glm::vec4(vertices[69],1.0f),
                         glm::vec4(vertices[76],1.0f),
                         glm::vec4(vertices[70],1.0f),
                         glm::vec4(vertices[70],1.0f),
                         glm::vec4(vertices[76],1.0f),
                         glm::vec4(vertices[8],1.0f),//45th quad
                         glm::vec4(vertices[70],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[77],1.0f),
                         glm::vec4(vertices[70],1.0f),
                         glm::vec4(vertices[77],1.0f),
                         glm::vec4(vertices[71],1.0f),//46th quad
                         glm::vec4(vertices[71],1.0f),
                         glm::vec4(vertices[77],1.0f),
                         glm::vec4(vertices[72],1.0f),
                         glm::vec4(vertices[72],1.0f),
                         glm::vec4(vertices[77],1.0f),
                         glm::vec4(vertices[6],1.0f),//47th quad
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[70],1.0f),
                         glm::vec4(vertices[8],1.0f),//21th triangle
                         glm::vec4(vertices[72],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[24],1.0f),
                         glm::vec4(vertices[72],1.0f),
                         glm::vec4(vertices[24],1.0f),
                         glm::vec4(vertices[73],1.0f),//48th quad
                         glm::vec4(vertices[54],1.0f),
                         glm::vec4(vertices[74],1.0f),
                         glm::vec4(vertices[24],1.0f),
                         glm::vec4(vertices[54],1.0f),
                         glm::vec4(vertices[24],1.0f),
                         glm::vec4(vertices[55],1.0f),//49th quad
                         glm::vec4(vertices[74],1.0f),
                         glm::vec4(vertices[73],1.0f),
                         glm::vec4(vertices[24],1.0f),//22th triangle

                         //extensions
                         glm::vec4(vertices[78],1.0f),
                         glm::vec4(vertices[82],1.0f),
                         glm::vec4(vertices[80],1.0f),
                         glm::vec4(vertices[80],1.0f),
                         glm::vec4(vertices[82],1.0f),
                         glm::vec4(vertices[84],1.0f),//50th quad
                         glm::vec4(vertices[80],1.0f),
                         glm::vec4(vertices[84],1.0f),
                         glm::vec4(vertices[81],1.0f),
                         glm::vec4(vertices[81],1.0f),
                         glm::vec4(vertices[84],1.0f),
                         glm::vec4(vertices[85],1.0f),//51th quad
                         glm::vec4(vertices[81],1.0f),
                         glm::vec4(vertices[85],1.0f),
                         glm::vec4(vertices[79],1.0f),
                         glm::vec4(vertices[79],1.0f),
                         glm::vec4(vertices[85],1.0f),
                         glm::vec4(vertices[83],1.0f),//52th quad
                         glm::vec4(vertices[82],1.0f),
                         glm::vec4(vertices[83],1.0f),
                         glm::vec4(vertices[84],1.0f),
                         glm::vec4(vertices[84],1.0f),
                         glm::vec4(vertices[83],1.0f),
                         glm::vec4(vertices[85],1.0f),//53th quad

                         //hole in back corrections
                         glm::vec4(vertices[20],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[86],1.0f),
                         glm::vec4(vertices[86],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[89],1.0f),//54th quad
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[86],1.0f),
                         glm::vec4(vertices[87],1.0f),
                         glm::vec4(vertices[87],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[18],1.0f),//55th quad
                         glm::vec4(vertices[87],1.0f),
                         glm::vec4(vertices[86],1.0f),
                         glm::vec4(vertices[88],1.0f),
                         glm::vec4(vertices[88],1.0f),
                         glm::vec4(vertices[86],1.0f),
                         glm::vec4(vertices[89],1.0f),//56th quad
                         glm::vec4(vertices[88],1.0f),
                         glm::vec4(vertices[89],1.0f),
                         glm::vec4(vertices[91],1.0f),
                         glm::vec4(vertices[91],1.0f),
                         glm::vec4(vertices[89],1.0f),
                         glm::vec4(vertices[90],1.0f),//57th quad
                         glm::vec4(vertices[21],1.0f),
                         glm::vec4(vertices[87],1.0f),
                         glm::vec4(vertices[88],1.0f),
                         glm::vec4(vertices[21],1.0f),
                         glm::vec4(vertices[88],1.0f),
                         glm::vec4(vertices[91],1.0f),//58th quad

                         //shoulder joint
                         glm::vec4(vertices[92],1.0f),
                         glm::vec4(vertices[93],1.0f),
                         glm::vec4(vertices[96],1.0f),
                         glm::vec4(vertices[96],1.0f),
                         glm::vec4(vertices[93],1.0f),
                         glm::vec4(vertices[97],1.0f),//59th quad
                         glm::vec4(vertices[94],1.0f),
                         glm::vec4(vertices[92],1.0f),
                         glm::vec4(vertices[98],1.0f),
                         glm::vec4(vertices[98],1.0f),
                         glm::vec4(vertices[92],1.0f),
                         glm::vec4(vertices[96],1.0f),//60th quad
                         glm::vec4(vertices[95],1.0f),
                         glm::vec4(vertices[94],1.0f),
                         glm::vec4(vertices[99],1.0f),
                         glm::vec4(vertices[99],1.0f),
                         glm::vec4(vertices[94],1.0f),
                         glm::vec4(vertices[98],1.0f),//61th quad
                         glm::vec4(vertices[97],1.0f),
                         glm::vec4(vertices[99],1.0f),
                         glm::vec4(vertices[93],1.0f),
                         glm::vec4(vertices[93],1.0f),
                         glm::vec4(vertices[99],1.0f),
                         glm::vec4(vertices[95],1.0f),//62th quad

                         glm::vec4(vertices[100],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[101],1.0f),
                         glm::vec4(vertices[101],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[102],1.0f),//62th quad
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[21],1.0f),
                         glm::vec4(vertices[102],1.0f),//23th triangle
                         };
int len = sizeof(torso_positions)/16;
copy_col_norm(len, normals, colors, positions, torso_positions, glm::vec4(1.0f), true, reflect, reflect2);

for(int i=0;i<24;i++){
  colors[260-i]=glm::vec4(1.0f, 0.1f, 0.1f, 1.0f);
  colors[260+len-i]=glm::vec4(210/255.0f, 4/255.0f, 45/255.0f, 1.0f);
}
}

//upper arm
const glm::mat4 upper_arm_transform = glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(3.4f, 4.89f, 0.0f)), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
const int upper_arm_size = 324;
void upper_arm(glm::vec4 positions[upper_arm_size], glm::vec3 normals[upper_arm_size], glm::vec4 colors[upper_arm_size])
{
glm::vec3 vertices[]={//Circle
                      glm::vec3(0.0f, 1.0f, 1.0f),
                      glm::vec3(0.3827f, 0.9239f, 1.0f),
                      glm::vec3(0.7071f, 0.7071f, 1.0f),
                      glm::vec3(0.9239f, 0.3827f, 1.0f),//top4 - 4
                      glm::vec3(1.0f, 0.0f, 1.0f),
                      glm::vec3(0.9239f, -0.3827f, 1.0f),
                      glm::vec3(0.7071f, -0.7071f, 1.0f),
                      glm::vec3(0.3827f, -0.9239f, 1.0f),//2nd 4 - 8
                      glm::vec3(0.0f, -1.0f, 1.0f),
                      glm::vec3(-0.3827f, -0.9239f, 1.0f),
                      glm::vec3(-0.7071f, -0.7071f, 1.0f),
                      glm::vec3(-0.9239f, -0.3827f, 1.0f),//3rd 4 - 12
                      glm::vec3(-1.0f, 0.0f, 1.0f),
                      glm::vec3(-0.9239f, 0.3827f, 1.0f),
                      glm::vec3(-0.7071f, 0.7071f, 1.0f),
                      glm::vec3(-0.3827f, 0.9239f, 1.0f),//4th 4 - 16
                      glm::vec3(0.0f, 0.0f, 1.0f),

                      glm::vec3(0.0f, 1.0f, -1.0f),
                      glm::vec3(0.3827f, 0.9239f, -1.0f),
                      glm::vec3(0.7071f, 0.7071f, -1.0f),//5th 4 - 20
                      glm::vec3(0.9239f, 0.3827f, -1.0f),
                      glm::vec3(1.0f, 0.0f, -1.0f),
                      glm::vec3(0.9239f, -0.3827f, -1.0f),
                      glm::vec3(0.7071f, -0.7071f, -1.0f),//6th 4 - 24
                      glm::vec3(0.3827f, -0.9239f, -1.0f),
                      glm::vec3(0.0f, -1.0f, -1.0f),
                      glm::vec3(-0.3827f, -0.9239f, -1.0f),
                      glm::vec3(-0.7071f, -0.7071f, -1.0f),//7th 4 - 28
                      glm::vec3(-0.9239f, -0.3827f, -1.0f),
                      glm::vec3(-1.0f, 0.0f, -1.0f),
                      glm::vec3(-0.9239f, 0.3827f, -1.0f),
                      glm::vec3(-0.7071f, 0.7071f, -1.0f),//8th 4 - 32
                      glm::vec3(-0.3827f, 0.9239f, -1.0f),
                      glm::vec3(0.0f, 0.0f, -1.0f),

                      //semi-circles
                      glm::vec3(0.3f, -2.4f, -0.6f),
                      glm::vec3(0.3f, -2.824f, -0.4243f),//9th 4 - 36
                      glm::vec3(0.3f, -3.0f, 0.0f),
                      glm::vec3(0.3f, -2.824f, 0.4243f),
                      glm::vec3(0.3f, -2.4f, 0.6f),
                      glm::vec3(0.3f, -2.4f, 0.0f),//10th 4 - 40
                      glm::vec3(0.7f, -2.4f, 0.0f),

                      //semi-circles
                      glm::vec3(-0.3f, -2.4f, -0.6f),
                      glm::vec3(-0.3f, -2.824f, -0.4243f),
                      glm::vec3(-0.3f, -3.0f, 0.0f),//11th 4 - 44
                      glm::vec3(-0.3f, -2.824f, 0.4243f),
                      glm::vec3(-0.3f, -2.4f, 0.6f),
                      glm::vec3(-0.3f, -2.4f, 0.0f),
                      glm::vec3(-0.7f, -2.4f, 0.0f),//12th 4 - 48


                      glm::vec3(-0.3f, -1.8f, -0.85f),
                      glm::vec3(0.3f, -1.8f, -0.85f),
                      glm::vec3(0.3f, -1.8f, 0.85f),
                      glm::vec3(-0.3f, -1.8f, 0.85f),//13th 4 - 52
                      glm::vec3(0.9f, -1.5f, 0.0f),
                      glm::vec3(-0.9f, -1.5f, 0.0f),
                      glm::vec3(-0.3f, 0.0f, -0.85f),
                      glm::vec3(0.3f, 0.0f, -0.85f),//14th 4 - 56
                      glm::vec3(0.3f, 0.0f, 0.85f),
                      glm::vec3(-0.3f, 0.0f, 0.85f),
                      glm::vec3(0.9f, 0.0f, 0.0f),
                      glm::vec3(-0.9f, 0.0f, 0.0f),//15th 5 - 60
                     };

glm::vec4 upper_arm_positions[]={glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[1],1.0f),//1st triangle
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[2],1.0f),//2nd triangle
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[3],1.0f),//3rd triangle
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[4],1.0f),//4th triangle
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[5],1.0f),//5th triangle
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[6],1.0f),//6th triangle
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[7],1.0f),//7th triangle
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[8],1.0f),//8th triangle
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[9],1.0f),//9th triangle
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[10],1.0f),//10th triangle
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[11],1.0f),//11th triangle
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[12],1.0f),//12th triangle
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[13],1.0f),//13th triangle
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[14],1.0f),//14th triangle
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[15],1.0f),//15th triangle

                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[17],1.0f),//16th triangle
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[19],1.0f),
                         glm::vec4(vertices[18],1.0f),//17th triangle
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[20],1.0f),
                         glm::vec4(vertices[19],1.0f),//18th triangle
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[21],1.0f),
                         glm::vec4(vertices[20],1.0f),//19th triangle
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[21],1.0f),//20th triangle
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[22],1.0f),//21th triangle
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[24],1.0f),
                         glm::vec4(vertices[23],1.0f),//22th triangle
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[25],1.0f),
                         glm::vec4(vertices[24],1.0f),//23th triangle
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[26],1.0f),
                         glm::vec4(vertices[25],1.0f),//24th triangle
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[27],1.0f),
                         glm::vec4(vertices[26],1.0f),//25th triangle
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[28],1.0f),
                         glm::vec4(vertices[27],1.0f),//26th triangle
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[28],1.0f),//27th triangle
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[30],1.0f),
                         glm::vec4(vertices[29],1.0f),//28th triangle
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[31],1.0f),
                         glm::vec4(vertices[30],1.0f),//29th triangle
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[32],1.0f),
                         glm::vec4(vertices[31],1.0f),//30th triangle

                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[0],1.0f),//31th triangle
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[32],1.0f),//32th triangle 

                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[18],1.0f),//1st quad
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[19],1.0f),//2nd quad
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[19],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[19],1.0f),
                         glm::vec4(vertices[20],1.0f),//3rd quad
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[20],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[20],1.0f),
                         glm::vec4(vertices[21],1.0f),//4th quad
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[21],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[21],1.0f),
                         glm::vec4(vertices[22],1.0f),//5th quad
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[23],1.0f),//6th quad
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[24],1.0f),//7th quad
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[24],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[24],1.0f),
                         glm::vec4(vertices[25],1.0f),//8th quad
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[25],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[25],1.0f),
                         glm::vec4(vertices[26],1.0f),//9th quad
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[26],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[26],1.0f),
                         glm::vec4(vertices[27],1.0f),//10th quad
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[27],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[27],1.0f),
                         glm::vec4(vertices[28],1.0f),//11th quad
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[28],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[28],1.0f),
                         glm::vec4(vertices[29],1.0f),//12th quad
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[30],1.0f),//13th quad
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[30],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[30],1.0f),
                         glm::vec4(vertices[31],1.0f),//14th quad
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[31],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[31],1.0f),
                         glm::vec4(vertices[32],1.0f),//15th quad
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[32],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[32],1.0f),
                         glm::vec4(vertices[17],1.0f),//16th quad

                         //semi-circles
                         glm::vec4(vertices[34],1.0f),
                         glm::vec4(vertices[39],1.0f),
                         glm::vec4(vertices[35],1.0f),//33th triangle
                         glm::vec4(vertices[35],1.0f),
                         glm::vec4(vertices[39],1.0f),
                         glm::vec4(vertices[36],1.0f),//34th triangle
                         glm::vec4(vertices[36],1.0f),
                         glm::vec4(vertices[39],1.0f),
                         glm::vec4(vertices[37],1.0f),//35th triangle
                         glm::vec4(vertices[37],1.0f),
                         glm::vec4(vertices[39],1.0f),
                         glm::vec4(vertices[38],1.0f),//36th triangle

                         glm::vec4(vertices[40],1.0f),
                         glm::vec4(vertices[34],1.0f),
                         glm::vec4(vertices[35],1.0f),//37th triangle
                         glm::vec4(vertices[40],1.0f),
                         glm::vec4(vertices[35],1.0f),
                         glm::vec4(vertices[36],1.0f),//38th triangle
                         glm::vec4(vertices[40],1.0f),
                         glm::vec4(vertices[36],1.0f),
                         glm::vec4(vertices[37],1.0f),//39th triangle
                         glm::vec4(vertices[40],1.0f),
                         glm::vec4(vertices[37],1.0f),
                         glm::vec4(vertices[38],1.0f),//40th triangle

                         //semi-circles
                         glm::vec4(vertices[46],1.0f),
                         glm::vec4(vertices[41],1.0f),
                         glm::vec4(vertices[42],1.0f),//41th triangle
                         glm::vec4(vertices[46],1.0f),
                         glm::vec4(vertices[42],1.0f),
                         glm::vec4(vertices[43],1.0f),//42th triangle
                         glm::vec4(vertices[46],1.0f),
                         glm::vec4(vertices[43],1.0f),
                         glm::vec4(vertices[44],1.0f),//43th triangle
                         glm::vec4(vertices[46],1.0f),
                         glm::vec4(vertices[44],1.0f),
                         glm::vec4(vertices[45],1.0f),//44th triangle

                         glm::vec4(vertices[41],1.0f),
                         glm::vec4(vertices[47],1.0f),
                         glm::vec4(vertices[42],1.0f),//45th triangle
                         glm::vec4(vertices[42],1.0f),
                         glm::vec4(vertices[47],1.0f),
                         glm::vec4(vertices[43],1.0f),//46th triangle
                         glm::vec4(vertices[43],1.0f),
                         glm::vec4(vertices[47],1.0f),
                         glm::vec4(vertices[44],1.0f),//47th triangle
                         glm::vec4(vertices[44],1.0f),
                         glm::vec4(vertices[47],1.0f),
                         glm::vec4(vertices[45],1.0f),//48th triangle


                         glm::vec4(vertices[45],1.0f),
                         glm::vec4(vertices[51],1.0f),
                         glm::vec4(vertices[41],1.0f),
                         glm::vec4(vertices[41],1.0f),
                         glm::vec4(vertices[51],1.0f),
                         glm::vec4(vertices[48],1.0f),//17th quad
                         glm::vec4(vertices[34],1.0f),
                         glm::vec4(vertices[49],1.0f),
                         glm::vec4(vertices[38],1.0f),
                         glm::vec4(vertices[38],1.0f),
                         glm::vec4(vertices[49],1.0f),
                         glm::vec4(vertices[50],1.0f),//18th quad
                         glm::vec4(vertices[48],1.0f),
                         glm::vec4(vertices[51],1.0f),
                         glm::vec4(vertices[49],1.0f),
                         glm::vec4(vertices[49],1.0f),
                         glm::vec4(vertices[51],1.0f),
                         glm::vec4(vertices[50],1.0f),//19th quad
                         glm::vec4(vertices[50],1.0f),
                         glm::vec4(vertices[52],1.0f),
                         glm::vec4(vertices[38],1.0f),
                         glm::vec4(vertices[38],1.0f),
                         glm::vec4(vertices[52],1.0f),
                         glm::vec4(vertices[40],1.0f),//20th quad
                         glm::vec4(vertices[52],1.0f),
                         glm::vec4(vertices[49],1.0f),
                         glm::vec4(vertices[40],1.0f),
                         glm::vec4(vertices[40],1.0f),
                         glm::vec4(vertices[49],1.0f),
                         glm::vec4(vertices[34],1.0f),//21th quad
                         glm::vec4(vertices[45],1.0f),
                         glm::vec4(vertices[47],1.0f),
                         glm::vec4(vertices[51],1.0f),
                         glm::vec4(vertices[51],1.0f),
                         glm::vec4(vertices[47],1.0f),
                         glm::vec4(vertices[53],1.0f),//23th quad
                         glm::vec4(vertices[41],1.0f),
                         glm::vec4(vertices[48],1.0f),
                         glm::vec4(vertices[47],1.0f),
                         glm::vec4(vertices[47],1.0f),
                         glm::vec4(vertices[48],1.0f),
                         glm::vec4(vertices[53],1.0f),//24th quad
                         glm::vec4(vertices[51],1.0f),
                         glm::vec4(vertices[57],1.0f),
                         glm::vec4(vertices[50],1.0f),
                         glm::vec4(vertices[50],1.0f),
                         glm::vec4(vertices[57],1.0f),
                         glm::vec4(vertices[56],1.0f),//25th quad
                         glm::vec4(vertices[50],1.0f),
                         glm::vec4(vertices[56],1.0f),
                         glm::vec4(vertices[52],1.0f),
                         glm::vec4(vertices[52],1.0f),
                         glm::vec4(vertices[56],1.0f),
                         glm::vec4(vertices[58],1.0f),//26th quad
                         glm::vec4(vertices[51],1.0f),
                         glm::vec4(vertices[53],1.0f),
                         glm::vec4(vertices[57],1.0f),
                         glm::vec4(vertices[57],1.0f),
                         glm::vec4(vertices[53],1.0f),
                         glm::vec4(vertices[59],1.0f),//27th quad
                         glm::vec4(vertices[48],1.0f),
                         glm::vec4(vertices[54],1.0f),
                         glm::vec4(vertices[53],1.0f),
                         glm::vec4(vertices[53],1.0f),
                         glm::vec4(vertices[54],1.0f),
                         glm::vec4(vertices[59],1.0f),//28th quad
                         glm::vec4(vertices[49],1.0f),
                         glm::vec4(vertices[52],1.0f),
                         glm::vec4(vertices[55],1.0f),
                         glm::vec4(vertices[55],1.0f),
                         glm::vec4(vertices[52],1.0f),
                         glm::vec4(vertices[58],1.0f),//29th quad
                         glm::vec4(vertices[49],1.0f),
                         glm::vec4(vertices[55],1.0f),
                         glm::vec4(vertices[48],1.0f),
                         glm::vec4(vertices[48],1.0f),
                         glm::vec4(vertices[55],1.0f),
                         glm::vec4(vertices[54],1.0f),//30th quad
                         };

int len = sizeof(upper_arm_positions)/16;
copy_col_norm(len, normals, colors, positions, upper_arm_positions, glm::vec4(1.0f));
}

//lower arm
const glm::mat4 lower_arm_transform = glm::translate(glm::rotate(glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f)), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(-0.05f, -0.6f, 0.0f));
const int lower_arm_size = 84;
void lower_arm(glm::vec4 positions[lower_arm_size], glm::vec3 normals[lower_arm_size], glm::vec4 colors[lower_arm_size])
{
glm::vec3 vertices[]={glm::vec3(-0.85f, 0.0f, 0.75f),
                      glm::vec3(0.45f, 0.0f, 0.75f),
                      glm::vec3(0.75f, 0.0f, 0.45f),
                      glm::vec3(0.75f, 0.0f, -0.45f),//top4 - 4
                      glm::vec3(0.45f, 0.0f, -0.75f),
                      glm::vec3(-0.85f, 0.0f, -0.75f),
                      glm::vec3(-0.85f, -1.6f, 0.75f),
                      glm::vec3(-0.85f, -1.6f, -0.75f),//2nd 4 - 8
                      glm::vec3(-0.55f, -1.9f, 0.75f),
                      glm::vec3(-0.55f, -1.9f, -0.75f),
                      glm::vec3(-0.55f, -3.7f, 0.75f),
                      glm::vec3(0.45f, -3.7f, 0.75f),//3rd 4 - 12
                      glm::vec3(0.75f, -3.7f, 0.45f),
                      glm::vec3(0.75f, -3.7f, -0.45f),
                      glm::vec3(0.45f, -3.7f, -0.75f),
                      glm::vec3(-0.55f, -3.7f, -0.75f),//4th 4 - 16
                     };

glm::vec4 lower_arm_positions[]={glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[4],1.0f),//1st quad
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[3],1.0f),//2nd quad
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[0],1.0f),//3rd quad
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[6],1.0f),//4th quad
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[1],1.0f),//5th quad
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[4],1.0f),//6th quad
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[9],1.0f),//7th quad
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[1],1.0f),//8th quad
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[2],1.0f),//9th quad
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[3],1.0f),//10th quad
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[4],1.0f),//11th quad
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[9],1.0f),//12th quad
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[14],1.0f),//13th quad
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[13],1.0f),//14th quad
                         };

int len = sizeof(lower_arm_positions)/16;
copy_col_norm(len, normals, colors, positions, lower_arm_positions, glm::vec4(1.0f));
}

//hand guard
const glm::mat4 hand_guard_transform = glm::translate(glm::mat4(1.0f), glm::vec3(-0.0f, 3.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::atan(-5.25f, 0.7f), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::translate(glm::mat4(1.0f), glm::vec3(4.3f, -0.866f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(8.0f), glm::vec3(0.0f, 0.0f, 1.0f));
const int hand_guard_size = 84+12;
void hand_guard(glm::vec4 positions[hand_guard_size], glm::vec3 normals[hand_guard_size], glm::vec4 colors[hand_guard_size])
{
glm::vec3 vertices[]={//glm::vec3(0.0f, 0.0f, 0.0f),
                      // glm::vec3(5.0f, 0.0f, 0.0f),
                      // glm::vec3(0.275f, -0.55f, 0.95f),
                      // glm::vec3(3.9f, -0.55f, 0.95f),//top4 - 4
                      // glm::vec3(1.0f, -2.0f, 0.95f),
                      // glm::vec3(0.275f, -0.55f, -0.95f),
                      // glm::vec3(3.9f, -0.55f, -0.95f),
                      // glm::vec3(1.0f, -2.0f, -0.95f),//2nd 4 - 8

                      // glm::vec3(0.05f, -0.1f, 0.0f),
                      // glm::vec3(4.8f, -0.1f, 0.0f),
                      // glm::vec3(0.325f, -0.56f, 0.8f),
                      // glm::vec3(3.7f, -0.56f, 0.8f),//top4 - 4
                      // glm::vec3(1.0f, -2.0f, 0.8f),
                      // glm::vec3(0.325f, -0.56f, -0.8f),
                      // glm::vec3(3.7f, -0.56f, -0.8f),
                      // glm::vec3(1.0f, -2.0f, -0.8f),//2nd 4 - 8

                      glm::vec3(-0.3f, 2.13f, 0.0f),
                      glm::vec3(4.5f, 0.0f, 0.0f),
                      glm::vec3(-0.18f, 1.36f, 0.95f),
                      glm::vec3(2.68f, 0.0f, 0.95f),//top4 -4
                      glm::vec3(0.0f, 0.0f, 0.95f),
                      glm::vec3(-0.18f, 1.36f, -0.95f),
                      glm::vec3(2.68f, 0.0f, -0.95f),
                      glm::vec3(0.0f, 0.0f, -0.95f),//2nd 4 -8

                      glm::vec3(-0.28f, 1.98f, 0.0f),
                      glm::vec3(4.5f, 0.0f, 0.0f),
                      glm::vec3(-0.18f, 1.36f, 0.8f),
                      glm::vec3(2.68f, 0.0f, 0.8f),//3rd 4 - 12
                      glm::vec3(0.0f, 0.0f, 0.8f),
                      glm::vec3(-0.18f, 1.36f, -0.8f),
                      glm::vec3(2.68f, 0.0f, -0.8f),
                      glm::vec3(0.0f, 0.0f, -0.8f),//4th 4 -16

                      glm::vec3(2.68f, 1.15f, 0.0f),
                      glm::vec3(2.68f, 1.0f, 0.0f),
                     };

glm::vec4 hand_guard_positions[]={glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[2],1.0f),//1st quad
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[5],1.0f),//2nd quad
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[16],1.0f),//3rd quad
                         //addition
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[16],1.0f),//2 triangles

                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[2],1.0f),//4th quad
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[4],1.0f),//5th quad
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[3],1.0f),//6th quad
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[1],1.0f),//7th quad
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[5],1.0f),//8th quad
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[7],1.0f),//9th quad
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[6],1.0f),//10th quad
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[1],1.0f),//11th quad

                         glm::vec4(vertices[8+0],1.0f),
                         glm::vec4(vertices[8+2],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[8+2],1.0f),
                         glm::vec4(vertices[8+3],1.0f),//12th quad
                         glm::vec4(vertices[8+2],1.0f),
                         glm::vec4(vertices[8+4],1.0f),
                         glm::vec4(vertices[8+3],1.0f),
                         glm::vec4(vertices[8+6],1.0f),
                         glm::vec4(vertices[8+7],1.0f),
                         glm::vec4(vertices[8+5],1.0f),//13th quad
                         glm::vec4(vertices[8+6],1.0f),
                         glm::vec4(vertices[8+5],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[8+5],1.0f),
                         glm::vec4(vertices[8+0],1.0f),//14th quad
                         //addition
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[17],1.0f),//2 triangles
                         };

int len = sizeof(hand_guard_positions)/16;
copy_col_norm(len, normals, colors, positions, hand_guard_positions, glm::vec4(1.0f));
}

//head
const glm::mat4 head_transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 5.8f, 0.1f));
const int head_size = 399;
void head(glm::vec4 positions[head_size], glm::vec3 normals[head_size], glm::vec4 colors[head_size])
{
glm::vec3 vertices[]={glm::vec3(0.7f, 0.0f, -1.2f),
                      glm::vec3(-0.7f, 0.0f, -1.2f),
                      glm::vec3(0.6f, 1.1f, -1.1f),
                      glm::vec3(-0.6f, 1.1f, -1.1f),//top4 - 4
                      glm::vec3(1.1f, 0.0f, -1.0f),
                      glm::vec3(-1.1f, 0.0f, -1.0f),
                      glm::vec3(0.7f, 1.5f, -0.8f),
                      glm::vec3(-0.7f, 1.5f, -0.8f),//2nd 4 - 8
                      glm::vec3(0.55f, 1.5f, -0.8f),
                      glm::vec3(-0.55f, 1.5f, -0.8f),
                      glm::vec3(0.5f, 1.95f, -0.6f),
                      glm::vec3(-0.5f, 1.95f, -0.6f),//3rd 4 - 12
                      glm::vec3(0.55f, 2.05f, 0.2f),
                      glm::vec3(-0.55f, 2.05f, 0.2f),
                      glm::vec3(0.35f, 2.05f, 1.1f),
                      glm::vec3(-0.35f, 2.05f, 1.1f),//4th 4 - 16
                      glm::vec3(0.7f, 1.5f, 0.2f),
                      glm::vec3(-0.7f, 1.5f, 0.2f), 
                      glm::vec3(0.7f, 0.0f, 0.2f),
                      glm::vec3(-0.7f, 0.0f, 0.2f),//5th 4 - 20
                      glm::vec3(0.8f, 0.6f, 0.2f),
                      glm::vec3(-0.8f, 0.6f, 0.2f),
                      glm::vec3(0.8f, 1.0f, 0.2f),
                      glm::vec3(-0.8f, 1.0f, 0.2f),//6th 4 - 24
                      glm::vec3(0.7f, 1.1f, -0.5333f),
                      glm::vec3(-0.7f, 1.1f, -0.5333f),
                      glm::vec3(0.7f, 0.5f, -0.1333f),
                      glm::vec3(-0.7f, 0.5f, -0.1333f),//7th 4 - 28
                      glm::vec3(0.7f, 0.5f, 0.2f),
                      glm::vec3(-0.7f, 0.5f, 0.2f),
                      glm::vec3(0.7f, 1.1f, 0.2f),
                      glm::vec3(-0.7f, 1.1f, 0.2f),//8th 4 - 32
                      glm::vec3(0.5f, 1.0f, 0.7f),
                      glm::vec3(-0.5f, 1.0f, 0.7f),
                      glm::vec3(0.1f, 0.9f, 0.9f),
                      glm::vec3(-0.1f, 0.9f, 0.9f),//9th 4 - 36
                      glm::vec3(0.6f, 1.04f, 0.5f),
                      glm::vec3(-0.6f, 1.04f, 0.5f),
                      glm::vec3(0.7f, 0.3f, 0.2f),
                      glm::vec3(-0.7f, 0.3f, 0.2f),//10th 4 - 40
                      glm::vec3(0.4f, 0.1f, 0.7f),
                      glm::vec3(-0.4f, 0.1f, 0.7f),
                      glm::vec3(0.4f, 0.8f, 0.7f),
                      glm::vec3(-0.4f, 0.8f, 0.7f),//11th 4 - 44
                      glm::vec3(0.6f, 0.18f, 0.5f),
                      glm::vec3(-0.6f, 0.18f, 0.5f),
                      glm::vec3(0.6f, 0.85f, 0.5f),
                      glm::vec3(-0.6f, 0.85f, 0.5f),//12th 4 - 48

                      glm::vec3(0.4f, 0.25f, 0.6f),
                      glm::vec3(-0.4f, 0.25f, 0.6f),
                      glm::vec3(0.4f, 0.8f, 0.6f),
                      glm::vec3(-0.4f, 0.8f, 0.6f),//13th 4 - 52
                      glm::vec3(0.6f, 0.85f, 0.4f),
                      glm::vec3(-0.6f, 0.85f, 0.4f),
                      glm::vec3(0.6f, 1.06f, 0.4f),
                      glm::vec3(-0.6f, 1.06f, 0.4f),//14th 4 - 56

                      glm::vec3(0.0f, 0.95f, 0.75f),
                      glm::vec3(0.0f, 0.7f, 1.0f),
                      glm::vec3(0.0f, 0.1f, 0.7f),
                     };

glm::vec4 head_positions[]={glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[3],1.0f),//1st quad
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[7],1.0f),//2nd quad
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[11],1.0f),//3rd quad
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[6],1.0f),//4th quad
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[7],1.0f),//5th quad
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[13],1.0f),//6th quad
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[15],1.0f),//7th quad
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[17],1.0f),//8th quad


                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[4],1.0f),//9th quad
                         glm::vec4(vertices[19],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[19],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[7],1.0f),//10th quad
                         glm::vec4(vertices[20],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[26],1.0f),
                         glm::vec4(vertices[26],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[24],1.0f),//11th quad
                         glm::vec4(vertices[21],1.0f),
                         glm::vec4(vertices[27],1.0f),
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[27],1.0f),
                         glm::vec4(vertices[25],1.0f),//12th quad
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[30],1.0f),
                         glm::vec4(vertices[30],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[8],1.0f),//13th quad
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[31],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[31],1.0f),
                         glm::vec4(vertices[9],1.0f),//14th quad
                         glm::vec4(vertices[28],1.0f),
                         glm::vec4(vertices[30],1.0f),
                         glm::vec4(vertices[20],1.0f),
                         glm::vec4(vertices[20],1.0f),
                         glm::vec4(vertices[30],1.0f),
                         glm::vec4(vertices[22],1.0f),//15th quad
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[21],1.0f),
                         glm::vec4(vertices[31],1.0f),
                         glm::vec4(vertices[31],1.0f),
                         glm::vec4(vertices[21],1.0f),
                         glm::vec4(vertices[23],1.0f),//16th quad
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[30],1.0f),
                         glm::vec4(vertices[24],1.0f),
                         glm::vec4(vertices[20],1.0f),
                         glm::vec4(vertices[26],1.0f),
                         glm::vec4(vertices[28],1.0f),//17th quad
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[25],1.0f),
                         glm::vec4(vertices[31],1.0f),
                         glm::vec4(vertices[27],1.0f),
                         glm::vec4(vertices[21],1.0f),
                         glm::vec4(vertices[29],1.0f),//18th quad
                         glm::vec4(vertices[34],1.0f),
                         glm::vec4(vertices[35],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[35],1.0f),
                         glm::vec4(vertices[15],1.0f),//19th quad
                         glm::vec4(vertices[34],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[35],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[15],1.0f),//20th quad
                         glm::vec4(vertices[32],1.0f),
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[34],1.0f),
                         glm::vec4(vertices[34],1.0f),
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[35],1.0f),//21th quad
                         glm::vec4(vertices[32],1.0f),
                         glm::vec4(vertices[30],1.0f),
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[30],1.0f),
                         glm::vec4(vertices[31],1.0f),//22th quad
                         glm::vec4(vertices[34],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[32],1.0f),
                         glm::vec4(vertices[32],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[30],1.0f),//23th quad
                         glm::vec4(vertices[35],1.0f),
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[31],1.0f),
                         glm::vec4(vertices[13],1.0f),//24th quad
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[5],1.0f),//25th quad
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[19],1.0f),//26th quad

                         //face guard
                         glm::vec4(vertices[44],1.0f),
                         glm::vec4(vertices[36],1.0f),
                         glm::vec4(vertices[38],1.0f),
                         glm::vec4(vertices[38],1.0f),
                         glm::vec4(vertices[36],1.0f),
                         glm::vec4(vertices[30],1.0f),//27th quad
                         glm::vec4(vertices[45],1.0f),
                         glm::vec4(vertices[39],1.0f),
                         glm::vec4(vertices[37],1.0f),
                         glm::vec4(vertices[37],1.0f),
                         glm::vec4(vertices[39],1.0f),
                         glm::vec4(vertices[31],1.0f),//28th quad
                         glm::vec4(vertices[40],1.0f),
                         glm::vec4(vertices[42],1.0f),
                         glm::vec4(vertices[44],1.0f),
                         glm::vec4(vertices[44],1.0f),
                         glm::vec4(vertices[42],1.0f),
                         glm::vec4(vertices[46],1.0f),//29th quad
                         glm::vec4(vertices[43],1.0f),
                         glm::vec4(vertices[41],1.0f),
                         glm::vec4(vertices[45],1.0f),
                         glm::vec4(vertices[45],1.0f),
                         glm::vec4(vertices[47],1.0f),
                         glm::vec4(vertices[43],1.0f),//30th quad

                         //filler
                         glm::vec4(vertices[48],1.0f),
                         glm::vec4(vertices[44],1.0f),
                         glm::vec4(vertices[49],1.0f),
                         glm::vec4(vertices[49],1.0f),
                         glm::vec4(vertices[44],1.0f),
                         glm::vec4(vertices[45],1.0f),//31th quad
                         glm::vec4(vertices[44],1.0f),
                         glm::vec4(vertices[38],1.0f),
                         glm::vec4(vertices[45],1.0f),
                         glm::vec4(vertices[45],1.0f),
                         glm::vec4(vertices[38],1.0f),
                         glm::vec4(vertices[39],1.0f),//32th quad
                         glm::vec4(vertices[38],1.0f),
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[39],1.0f),
                         glm::vec4(vertices[39],1.0f),
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[19],1.0f),//55th quad

                         glm::vec4(vertices[52],1.0f),
                         glm::vec4(vertices[54],1.0f),
                         glm::vec4(vertices[46],1.0f),
                         glm::vec4(vertices[46],1.0f),
                         glm::vec4(vertices[54],1.0f),
                         glm::vec4(vertices[36],1.0f),//56th quad
                         glm::vec4(vertices[53],1.0f),
                         glm::vec4(vertices[47],1.0f),
                         glm::vec4(vertices[55],1.0f),
                         glm::vec4(vertices[55],1.0f),
                         glm::vec4(vertices[47],1.0f),
                         glm::vec4(vertices[37],1.0f),//57th quad
                         glm::vec4(vertices[50],1.0f),
                         glm::vec4(vertices[52],1.0f),
                         glm::vec4(vertices[42],1.0f),
                         glm::vec4(vertices[42],1.0f),
                         glm::vec4(vertices[52],1.0f),
                         glm::vec4(vertices[46],1.0f),//58th quad
                         glm::vec4(vertices[51],1.0f),
                         glm::vec4(vertices[43],1.0f),
                         glm::vec4(vertices[53],1.0f),
                         glm::vec4(vertices[53],1.0f),
                         glm::vec4(vertices[43],1.0f),
                         glm::vec4(vertices[47],1.0f),//59th quad
                         glm::vec4(vertices[48],1.0f),
                         glm::vec4(vertices[50],1.0f),
                         glm::vec4(vertices[40],1.0f),
                         glm::vec4(vertices[40],1.0f),
                         glm::vec4(vertices[50],1.0f),
                         glm::vec4(vertices[42],1.0f),//60th quad
                         glm::vec4(vertices[49],1.0f),
                         glm::vec4(vertices[41],1.0f),
                         glm::vec4(vertices[51],1.0f),
                         glm::vec4(vertices[51],1.0f),
                         glm::vec4(vertices[41],1.0f),
                         glm::vec4(vertices[43],1.0f),//61th quad

                         //face
                         glm::vec4(vertices[54],1.0f),
                         glm::vec4(vertices[52],1.0f),
                         glm::vec4(vertices[56],1.0f),
                         glm::vec4(vertices[56],1.0f),
                         glm::vec4(vertices[52],1.0f),
                         glm::vec4(vertices[57],1.0f),//62th quad
                         glm::vec4(vertices[55],1.0f),
                         glm::vec4(vertices[56],1.0f),
                         glm::vec4(vertices[53],1.0f),
                         glm::vec4(vertices[53],1.0f),
                         glm::vec4(vertices[56],1.0f),
                         glm::vec4(vertices[57],1.0f),//63th quad
                         glm::vec4(vertices[48],1.0f),
                         glm::vec4(vertices[58],1.0f),
                         glm::vec4(vertices[57],1.0f),
                         glm::vec4(vertices[48],1.0f),
                         glm::vec4(vertices[57],1.0f),
                         glm::vec4(vertices[50],1.0f),//64th quad
                         glm::vec4(vertices[49],1.0f),
                         glm::vec4(vertices[57],1.0f),
                         glm::vec4(vertices[58],1.0f),
                         glm::vec4(vertices[57],1.0f),
                         glm::vec4(vertices[49],1.0f),
                         glm::vec4(vertices[51],1.0f),//65th quad

                         glm::vec4(vertices[40],1.0f),
                         glm::vec4(vertices[44],1.0f),
                         glm::vec4(vertices[48],1.0f),//1st triangle
                         glm::vec4(vertices[41],1.0f),
                         glm::vec4(vertices[49],1.0f),
                         glm::vec4(vertices[45],1.0f),//2nd triangle
                         glm::vec4(vertices[58],1.0f),
                         glm::vec4(vertices[48],1.0f),
                         glm::vec4(vertices[49],1.0f),//3rd triangle
                         };

int len = sizeof(head_positions)/16;
copy_col_norm(len, normals, colors, positions, head_positions);
}

//flap extensions (flap - torso joint)
const glm::mat4 thigh_leg_transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.8f, -0.1f));
const int thigh_leg_size = 156;
void thigh_leg(glm::vec4 positions[thigh_leg_size], glm::vec3 normals[thigh_leg_size], glm::vec4 colors[thigh_leg_size])
{
glm::vec3 vertices[]={glm::vec3(-0.8f, 0.0f, -0.9f),
                      glm::vec3(0.8f, 0.0f, -0.9f),
                      glm::vec3(0.8f, 0.0f, 0.9f),
                      glm::vec3(-0.8f, 0.0f, 0.9f),//top4 - 4

                      // glm::vec3(0.8f, 7.5f, 0.5f),
                      // glm::vec3(-0.8f, 7.5f, 0.5f),
                      // glm::vec3(0.8f, 7.5f, 2.9f),
                      // glm::vec3(-0.8f, 7.5f, 2.9f),

                      // glm::vec3(0.8f, 5.5f, 0.5f),
                      // glm::vec3(-0.8f, 5.5f, 0.5f),

                      glm::vec3(-0.8, 0.0f-1.0, 1.0f-0.3),
                      glm::vec3(-0.8, -0.3827f-1.0, 0.9239f-0.3),
                      glm::vec3(-0.8, -0.7071f-1.0, 0.7071f-0.3),
                      glm::vec3(-0.8, -0.9239f-1.0, 0.3827f-0.3),//2nd 4 - 8
                      glm::vec3(-0.8, -1.0f-1.0, 0.0f-0.3),
                      glm::vec3(-0.8, -0.9239f-1.0, -0.3827f-0.3),
                      glm::vec3(-0.8, -0.7071f-1.0, -0.7071f-0.3),
                      glm::vec3(-0.8, -0.3827f-1.0, -0.9239f-0.3),//3rd 4 - 12
                      glm::vec3(-0.8, 0.0f-1.0, -1.0f-0.3),
                      glm::vec3(-0.8, 0.3827f-1.0, -0.9239f-0.3),
                      glm::vec3(-0.8, 0.7071f-1.0, -0.7071f-0.3),
                      glm::vec3(-0.8, 0.9239f-1.0, -0.3827f-0.3),//4th 4 - 16
                      glm::vec3(-0.8, 0.0f-1.0, 0.0f-0.3),

                      glm::vec3(0.8, 0.0f-1.0, 1.0f-0.3),
                      glm::vec3(0.8, -0.3827f-1.0, 0.9239f-0.3),
                      glm::vec3(0.8, -0.7071f-1.0, 0.7071f-0.3),//5th 4 - 20
                      glm::vec3(0.8, -0.9239f-1.0, 0.3827f-0.3),
                      glm::vec3(0.8, -1.0f-1.0, 0.0f-0.3),
                      glm::vec3(0.8, -0.9239f-1.0, -0.3827f-0.3),
                      glm::vec3(0.8, -0.7071f-1.0, -0.7071f-0.3),//6th 4 - 24
                      glm::vec3(0.8, -0.3827f-1.0, -0.9239f-0.3),
                      glm::vec3(0.8, 0.0f-1.0, -1.0f-0.3),
                      glm::vec3(0.8, 0.3827f-1.0, -0.9239f-0.3),
                      glm::vec3(0.8, 0.7071f-1.0, -0.7071f-0.3),//7th 4 - 28
                      glm::vec3(0.8, 0.9239f-1.0, -0.3827f-0.3),
                      glm::vec3(0.8, 0.0f-1.0, 0.0f-0.3),
                     };

glm::vec4 thigh_leg_positions[]={glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[5],1.0f),//1th triangle
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[6],1.0f),//2th triangle
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[7],1.0f),//3th triangle
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[8],1.0f),//4th triangle
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[9],1.0f),//5th triangle
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[10],1.0f),//6th triangle
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[11],1.0f),//7th triangle
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[12],1.0f),//8th triangle
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[13],1.0f),//9th triangle
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[14],1.0f),//10th triangle
                         // glm::vec4(vertices[16],1.0f),
                         // glm::vec4(vertices[14],1.0f),
                         // glm::vec4(vertices[15],1.0f),//11th triangle

                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[17],1.0f),//12th triangle
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[19],1.0f),
                         glm::vec4(vertices[18],1.0f),//13th triangle
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[20],1.0f),
                         glm::vec4(vertices[19],1.0f),//14th triangle
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[21],1.0f),
                         glm::vec4(vertices[20],1.0f),//15th triangle
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[21],1.0f),//16th triangle
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[22],1.0f),//17th triangle
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[24],1.0f),
                         glm::vec4(vertices[23],1.0f),//18th triangle
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[25],1.0f),
                         glm::vec4(vertices[24],1.0f),//19th triangle
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[26],1.0f),
                         glm::vec4(vertices[25],1.0f),//20th triangle
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[27],1.0f),
                         glm::vec4(vertices[26],1.0f),//21th triangle
                         // glm::vec4(vertices[29],1.0f),
                         // glm::vec4(vertices[28],1.0f),
                         // glm::vec4(vertices[27],1.0f),//22th triangle

                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[18],1.0f),//1th quad
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[19],1.0f),//2th quad
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[19],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[19],1.0f),
                         glm::vec4(vertices[20],1.0f),//3th quad
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[20],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[20],1.0f),
                         glm::vec4(vertices[21],1.0f),//4th quad
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[21],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[21],1.0f),
                         glm::vec4(vertices[22],1.0f),//5th quad
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[23],1.0f),//6th quad
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[24],1.0f),//7th quad
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[24],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[24],1.0f),
                         glm::vec4(vertices[25],1.0f),//8th quad
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[25],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[25],1.0f),
                         glm::vec4(vertices[26],1.0f),//9th quad
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[26],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[26],1.0f),
                         glm::vec4(vertices[27],1.0f),//10th quad
                         // glm::vec4(vertices[14],1.0f),
                         // glm::vec4(vertices[27],1.0f),
                         // glm::vec4(vertices[15],1.0f),
                         // glm::vec4(vertices[15],1.0f),
                         // glm::vec4(vertices[27],1.0f),
                         // glm::vec4(vertices[28],1.0f),//11th quad

                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[27],1.0f),//12th quad
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[3],1.0f),//13th quad
                         glm::vec4(vertices[27],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[2],1.0f),//14th quad
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[2],1.0f),//11th quad
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[1],1.0f),//15th quad
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[27],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[27],1.0f),
                         glm::vec4(vertices[1],1.0f),//16th quad
                         };

int len = sizeof(thigh_leg_positions)/16;
copy_col_norm(len, normals, colors, positions, thigh_leg_positions, glm::vec4(0.1f, 1.0f, 0.1f, 1.0f));
}

const glm::mat4 hand_transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.1f, -3.7f, 0.0f));
const int hand_size = 126;
void hand(glm::vec4 positions[hand_size], glm::vec3 normals[hand_size], glm::vec4 colors[hand_size])
{
glm::vec3 vertices[]={glm::vec3(-0.5f, -0.2f, 0.5f),
                      glm::vec3(0.5f, -0.2f, 0.5f),
                      glm::vec3(-0.5f, -0.2f, -0.5f),
                      glm::vec3(0.5f, -0.2f, -0.5f),//top4 - 4
                      glm::vec3(-0.5f, -1.2f, 0.5f),
                      glm::vec3(0.5f, -1.2f, 0.5f),
                      glm::vec3(-0.5f, -1.2f, -0.5f),
                      glm::vec3(0.5f, -1.2f, -0.5f),//2nd 4 - 8

                      glm::vec3(-0.25f, 0.2f, 0.2f),
                      glm::vec3(0.25f, 0.2f, 0.2f),
                      glm::vec3(-0.25f, 0.2f, -0.2f),
                      glm::vec3(0.25f, 0.2f, -0.2f),//3rd 4 - 12
                      glm::vec3(-0.35f, -0.2f, 0.35f),
                      glm::vec3(0.35f, -0.2f, 0.35f),
                      glm::vec3(-0.35f, -0.2f, -0.35f),
                      glm::vec3(0.35f, -0.2f, -0.35f),// 4th 4 - 16
                      };

glm::vec4 hand_positions[]={glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[3],1.0f),//1st quad
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[7],1.0f),//2st quad
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[1],1.0f),//3rd quad
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[0],1.0f),//4th quad
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[7],1.0f),//5th quad
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[2],1.0f),//6th quad

                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[8],1.0f),//7th quad
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[9],1.0f),//8th quad
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[11],1.0f),//9th quad
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[10],1.0f),//10th quad
                         };

int len = sizeof(hand_positions)/16;
copy_col_norm(len, normals, colors, positions, hand_positions, glm::vec4(1.0f));
}

//************************************************************************************************************************************
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
//************************************************************************************************************************************

void initComponentBuffer(GLuint vao, GLuint vbo, GLuint vPosition, GLuint vColor, GLuint vNormal, glm::vec4 v_positions[], glm::vec4 v_colors[], glm::vec3 v_normals[], const int size){
  glBindVertexArray (vao);
  glBindBuffer (GL_ARRAY_BUFFER, vbo);
  
  //Copy the points into the current buffer
  glBufferData (GL_ARRAY_BUFFER, size*sizeof(glm::vec4) + size*sizeof(glm::vec4) + size*sizeof(glm::vec3), NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, size*sizeof(glm::vec4), v_positions);
  glBufferSubData( GL_ARRAY_BUFFER, size*sizeof(glm::vec4), size*sizeof(glm::vec4), v_colors );
  glBufferSubData( GL_ARRAY_BUFFER, size*sizeof(glm::vec4) + size*sizeof(glm::vec4), size*sizeof(glm::vec3), v_normals );

  // set up vertex array
  glEnableVertexAttribArray( vPosition );
  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  
  glEnableVertexAttribArray( vColor );
  glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(size*sizeof(glm::vec4)) );

  glEnableVertexAttribArray( vNormal );
  glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(size*sizeof(glm::vec4) + size*sizeof(glm::vec4)) );
}

//************************************************************************************************************************************
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
//************************************************************************************************************************************

void init_torso(GLuint vao, GLuint vbo, GLuint vPosition, GLuint vColor, GLuint vNormal){
  glm::vec4 v_positions[torso_size];       
  glm::vec4 v_colors[torso_size];
  glm::vec3 v_normals[torso_size];

  torso(v_positions, v_normals, v_colors);

  initComponentBuffer(vao, vbo, vPosition, vColor, vNormal, v_positions, v_colors, v_normals, torso_size);
}
void init_head(GLuint vao, GLuint vbo, GLuint vPosition, GLuint vColor, GLuint vNormal){
  glm::vec4 v_positions[head_size];       
  glm::vec4 v_colors[head_size];
  glm::vec3 v_normals[head_size];

  head(v_positions, v_normals, v_colors);

  initComponentBuffer(vao, vbo, vPosition, vColor, vNormal, v_positions, v_colors, v_normals, head_size);
}
void init_ship_torso(GLuint vao, GLuint vbo, GLuint vPosition, GLuint vColor, GLuint vNormal){
  glm::vec4 v_positions[ship_torso_size];       
  glm::vec4 v_colors[ship_torso_size];
  glm::vec3 v_normals[ship_torso_size];

  ship_torso(v_positions, v_normals, v_colors);

  initComponentBuffer(vao, vbo, vPosition, vColor, vNormal, v_positions, v_colors, v_normals, ship_torso_size);
}
void init_ship(GLuint vao, GLuint vbo, GLuint vPosition, GLuint vColor, GLuint vNormal){
  glm::vec4 v_positions[ship_size];       
  glm::vec4 v_colors[ship_size];
  glm::vec3 v_normals[ship_size];

  ship(v_positions, v_normals, v_colors);

  initComponentBuffer(vao, vbo, vPosition, vColor, vNormal, v_positions, v_colors, v_normals, ship_size);
}
void init_wing(GLuint vao, GLuint vbo, GLuint vPosition, GLuint vColor, GLuint vNormal){
  glm::vec4 v_positions[wing_size];       
  glm::vec4 v_colors[wing_size];
  glm::vec3 v_normals[wing_size];

  wing(v_positions, v_normals, v_colors);

  initComponentBuffer(vao, vbo, vPosition, vColor, vNormal, v_positions, v_colors, v_normals, wing_size);
}
void init_wing_torso(GLuint vao, GLuint vbo, GLuint vPosition, GLuint vColor, GLuint vNormal){
  glm::vec4 v_positions[wing_torso_size];       
  glm::vec4 v_colors[wing_torso_size];
  glm::vec3 v_normals[wing_torso_size];

  wing_torso(v_positions, v_normals, v_colors);

  initComponentBuffer(vao, vbo, vPosition, vColor, vNormal, v_positions, v_colors, v_normals, wing_torso_size);
}
void init_shoulder_pad(GLuint vao, GLuint vbo, GLuint vPosition, GLuint vColor, GLuint vNormal){
  glm::vec4 v_positions[shoulder_pad_size];       
  glm::vec4 v_colors[shoulder_pad_size];
  glm::vec3 v_normals[shoulder_pad_size];

  shoulder_pad(v_positions, v_normals, v_colors);

  initComponentBuffer(vao, vbo, vPosition, vColor, vNormal, v_positions, v_colors, v_normals, shoulder_pad_size);
}
void init_foot(GLuint vao, GLuint vbo, GLuint vPosition, GLuint vColor, GLuint vNormal){
  glm::vec4 v_positions[foot_size];       
  glm::vec4 v_colors[foot_size];
  glm::vec3 v_normals[foot_size];

  foot(v_positions, v_normals, v_colors);

  initComponentBuffer(vao, vbo, vPosition, vColor, vNormal, v_positions, v_colors, v_normals, foot_size);
}
void init_lower_leg(GLuint vao, GLuint vbo, GLuint vPosition, GLuint vColor, GLuint vNormal){
  glm::vec4 v_positions[lower_leg_size];       
  glm::vec4 v_colors[lower_leg_size];
  glm::vec3 v_normals[lower_leg_size];

  lower_leg(v_positions, v_normals, v_colors);

  initComponentBuffer(vao, vbo, vPosition, vColor, vNormal, v_positions, v_colors, v_normals, lower_leg_size);
}
void init_thigh(GLuint vao, GLuint vbo, GLuint vPosition, GLuint vColor, GLuint vNormal){
  glm::vec4 v_positions[thigh_size];       
  glm::vec4 v_colors[thigh_size];
  glm::vec3 v_normals[thigh_size];

  thigh(v_positions, v_normals, v_colors);

  initComponentBuffer(vao, vbo, vPosition, vColor, vNormal, v_positions, v_colors, v_normals, thigh_size);
}
void init_joint(GLuint vao, GLuint vbo, GLuint vPosition, GLuint vColor, GLuint vNormal){
  glm::vec4 v_positions[joint_size];       
  glm::vec4 v_colors[joint_size];
  glm::vec3 v_normals[joint_size];

  joint(v_positions, v_normals, v_colors);

  initComponentBuffer(vao, vbo, vPosition, vColor, vNormal, v_positions, v_colors, v_normals, joint_size);
}
void init_hand_guard(GLuint vao, GLuint vbo, GLuint vPosition, GLuint vColor, GLuint vNormal){
  glm::vec4 v_positions[hand_guard_size];       
  glm::vec4 v_colors[hand_guard_size];
  glm::vec3 v_normals[hand_guard_size];

  hand_guard(v_positions, v_normals, v_colors);

  initComponentBuffer(vao, vbo, vPosition, vColor, vNormal, v_positions, v_colors, v_normals, hand_guard_size);
}
void init_upper_arm(GLuint vao, GLuint vbo, GLuint vPosition, GLuint vColor, GLuint vNormal){
  glm::vec4 v_positions[upper_arm_size];       
  glm::vec4 v_colors[upper_arm_size];
  glm::vec3 v_normals[upper_arm_size];

  upper_arm(v_positions, v_normals, v_colors);

  initComponentBuffer(vao, vbo, vPosition, vColor, vNormal, v_positions, v_colors, v_normals, upper_arm_size);
}
void init_lower_arm(GLuint vao, GLuint vbo, GLuint vPosition, GLuint vColor, GLuint vNormal){
  glm::vec4 v_positions[lower_arm_size];       
  glm::vec4 v_colors[lower_arm_size];
  glm::vec3 v_normals[lower_arm_size];

  lower_arm(v_positions, v_normals, v_colors);

  initComponentBuffer(vao, vbo, vPosition, vColor, vNormal, v_positions, v_colors, v_normals, lower_arm_size);
}
void init_thigh_leg(GLuint vao, GLuint vbo, GLuint vPosition, GLuint vColor, GLuint vNormal){
  glm::vec4 v_positions[thigh_leg_size];       
  glm::vec4 v_colors[thigh_leg_size];
  glm::vec3 v_normals[thigh_leg_size];

  thigh_leg(v_positions, v_normals, v_colors);

  initComponentBuffer(vao, vbo, vPosition, vColor, vNormal, v_positions, v_colors, v_normals, thigh_leg_size);
}
void init_hand(GLuint vao, GLuint vbo, GLuint vPosition, GLuint vColor, GLuint vNormal){
  glm::vec4 v_positions[thigh_leg_size];       
  glm::vec4 v_colors[thigh_leg_size];
  glm::vec3 v_normals[thigh_leg_size];

  hand(v_positions, v_normals, v_colors);

  initComponentBuffer(vao, vbo, vPosition, vColor, vNormal, v_positions, v_colors, v_normals, hand_size);
}

//************************************************************************************************************************************
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
//************************************************************************************************************************************

int sizes[buff_size];
void init_vector_prime(GLuint vao[], GLuint vbo[], GLuint vPosition, GLuint vColor, GLuint vNormal){
  init_torso(vao[0], vbo[0], vPosition, vColor, vNormal);
  sizes[0] = torso_size;
  init_head(vao[1], vbo[1], vPosition, vColor, vNormal);
  sizes[1] = head_size;
  init_ship_torso(vao[2], vbo[2], vPosition, vColor, vNormal);
  sizes[2] = ship_torso_size;
  init_ship(vao[3], vbo[3], vPosition, vColor, vNormal);
  sizes[3] = ship_size;
  init_wing(vao[4], vbo[4], vPosition, vColor, vNormal);
  sizes[4] = wing_size;
  init_wing_torso(vao[5], vbo[5], vPosition, vColor, vNormal);
  sizes[5] = wing_torso_size;
  init_shoulder_pad(vao[6], vbo[6], vPosition, vColor, vNormal);
  sizes[6] = shoulder_pad_size;
  init_foot(vao[7], vbo[7], vPosition, vColor, vNormal);
  sizes[7] = foot_size;
  init_lower_leg(vao[8], vbo[8], vPosition, vColor, vNormal);
  sizes[8] = lower_leg_size;
  init_thigh(vao[9], vbo[9], vPosition, vColor, vNormal);
  sizes[9] = thigh_size;
  init_joint(vao[10], vbo[10], vPosition, vColor, vNormal);
  sizes[10] = joint_size;
  init_hand_guard(vao[11], vbo[11], vPosition, vColor, vNormal);
  sizes[11] = hand_guard_size;
  init_upper_arm(vao[12], vbo[12], vPosition, vColor, vNormal);
  sizes[12] = upper_arm_size;
  init_lower_arm(vao[13], vbo[13], vPosition, vColor, vNormal);
  sizes[13] = lower_arm_size;
  init_thigh_leg(vao[14], vbo[14], vPosition, vColor, vNormal);
  sizes[14] = thigh_leg_size;
  init_hand(vao[15], vbo[15], vPosition, vColor, vNormal);
  sizes[15] = hand_size;
}

//************************************************************************************************************************************
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
//************************************************************************************************************************************

//--------------------------------------------RIGHT-SIDE------------------------------------------------------------------------------

void draw_right_hand(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*hand_transform * glm::rotate(glm::rotate(glm::rotate(glm::mat4(1.0f), glm::radians(vp_right_hand_x), glm::vec3(1.0f, 0.0f, 0.0f)), glm::radians(vp_right_hand_y), glm::vec3(0.0f, 1.0f, 0.0f)), glm::radians(vp_right_hand_z), glm::vec3(0.0f, 0.0f, 1.0f));
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[15]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[15]);
}

void draw_right_hand_guard(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix * glm::translate(glm::mat4(1.0f), glm::vec3(0.3f*vp_right_hand_guard, 1.1f*vp_right_hand_guard, 0.0f)) * hand_guard_transform;
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[11]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[11]);
}

void draw_right_lower_arm(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*lower_arm_transform * glm::rotate(glm::mat4(1.0f), glm::radians(vp_right_elbow_x), glm::vec3(0.0f, 1.0f, 0.0f));
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[13]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[13]);

  draw_right_hand_guard(vao, vbo, modelview_matrix);
  draw_right_hand(vao, vbo, modelview_matrix);
}

void draw_right_elbow_joint(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*elbow_joint_transform * glm::rotate(glm::mat4(1.0f), glm::radians(vp_right_elbow_y), glm::vec3(0.0f, 0.0f, 1.0f));
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix*elbow_joint_scale));
  normal_matrix = glm::mat3(modelview_matrix*elbow_joint_scale);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix*elbow_joint_scale));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[10]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[10]);

  draw_right_lower_arm(vao, vbo, modelview_matrix);
}

void draw_right_upper_arm(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*upper_arm_transform * glm::rotate(glm::rotate(glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(0.99f*vp_right_shoulder_translate, 0.09f*vp_right_shoulder_translate, 0.0f)), glm::radians(vp_right_shoulder_x), glm::vec3(1.0f, 0.0f, 0.0f)), glm::radians(vp_right_shoulder_y), glm::vec3(0.0f, 1.0f, 0.0f)), glm::radians(vp_right_shoulder_z), glm::vec3(0.0f, 0.0f, 1.0f));
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[12]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[12]);

  draw_right_elbow_joint(vao, vbo, modelview_matrix);
}

void draw_right_foot(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*foot_transform * glm::rotate(glm::rotate(glm::rotate(glm::mat4(1.0f), glm::radians(vp_right_foot_x), glm::vec3(1.0f, 0.0f, 0.0f)), glm::radians(vp_right_foot_y), glm::vec3(0.0f, 1.0f, 0.0f)), glm::radians(vp_right_foot_z), glm::vec3(0.0f, 0.0f, 1.0f));
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[7]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[7]);
}

void draw_right_lower_leg(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*lower_leg_transform * glm::rotate(glm::mat4(1.0f), glm::radians(vp_right_knee_y), glm::vec3(1.0f, 0.0f, 0.0f));
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[8]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[8]);

  draw_right_foot(vao, vbo, modelview_matrix);
}

void draw_right_thigh_leg(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*thigh_leg_transform * glm::rotate(glm::mat4(1.0f), glm::radians(vp_right_knee_x), glm::vec3(0.0f, 1.0f, 0.0f));
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[14]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[14]);

  draw_right_lower_leg(vao, vbo, modelview_matrix);
}

void draw_right_thigh(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*thigh_transform * glm::rotate(glm::rotate(glm::mat4(1.0f), glm::radians(vp_right_hip_z), glm::vec3(0.0f, 1.0f, 0.0f)), glm::radians(vp_right_hip_y), glm::vec3(0.0f, 0.0f, 1.0f));
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[9]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[9]);

  draw_right_thigh_leg(vao, vbo, modelview_matrix);
}

void draw_right_hip_joint(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*hip_joint_transform * glm::rotate(glm::mat4(1.0f), glm::radians(vp_right_hip_x), glm::vec3(1.0f, 0.0f, 0.0f));
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[10]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[10]);

  draw_right_thigh(vao, vbo, modelview_matrix);
}

const glm::mat4 z_reflect = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, -1.0f));
void draw_right_wing(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*glm::translate(glm::mat4(1.0f), glm::vec3(-vp_right_wing/360.0f, 0.0f, 0.0f))*wing_transform;
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix * glm::rotate(glm::mat4(1.0f), glm::radians(vp_right_wing), glm::vec3(0.0f, -1.0f, 0.0f))));
  normal_matrix = glm::mat3(modelview_matrix * glm::rotate(glm::mat4(1.0f), glm::radians(vp_right_wing), glm::vec3(0.0f, -1.0f, 0.0f)));
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix * glm::rotate(glm::mat4(1.0f), glm::radians(vp_right_wing), glm::vec3(0.0f, -1.0f, 0.0f))));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[4]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[4]);

  modelview_matrix = modelview_matrix*z_reflect * glm::rotate(glm::mat4(1.0f), glm::radians(vp_right_wing), glm::vec3(0.0f, -1.0f, 0.0f));
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glDrawArrays(GL_TRIANGLES, 0, sizes[4]);
}

void draw_right_wing_joint(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*wing_joint_transform * glm::rotate(glm::mat4(1.0f), glm::radians(vp_right_wing_wing_torso), glm::vec3(0.0f, 0.0f, -1.0f));
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix*wing_joint_scale));
  normal_matrix = glm::mat3(modelview_matrix*wing_joint_scale);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix*wing_joint_scale));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[10]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[10]);

  draw_right_wing(vao, vbo, modelview_matrix);
}

void draw_right_wing_torso(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*wing_torso_transform * glm::rotate(glm::mat4(1.0f), glm::radians(vp_right_wing_torso_torso), glm::vec3(0.0f, 0.0f, -1.0f));
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[5]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[5]);

  draw_right_wing_joint(vao, vbo, modelview_matrix);
}

void draw_right_shoulder_pad(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*shoulder_pad_transform * glm::rotate(glm::rotate(glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(0.09f*vp_right_shoulder_translate, 0.99f*vp_right_shoulder_translate, 0.0f)), glm::radians(vp_right_shoulder_x), glm::vec3(0.0f, 1.0f, 0.0f)), glm::radians(vp_right_shoulder_y), glm::vec3(-1.0f, 0.0f, 0.0f)), glm::radians(vp_right_shoulder_pad), glm::vec3(0.0f, 0.0f, 1.0f));
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[6]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[6]);
}

//---------------------------------------------LEFT-SIDE------------------------------------------------------------------------------

const glm::mat4 left = glm::scale(glm::mat4(1.0f), glm::vec3(-1.0f, 1.0f, 1.0f));

void draw_left_hand(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*hand_transform * glm::rotate(glm::rotate(glm::rotate(glm::mat4(1.0f), glm::radians(vp_left_hand_x), glm::vec3(1.0f, 0.0f, 0.0f)), glm::radians(vp_left_hand_y), glm::vec3(0.0f, 1.0f, 0.0f)), glm::radians(vp_left_hand_z), glm::vec3(0.0f, 0.0f, 1.0f));
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[15]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[15]);
}

void draw_left_hand_guard(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix * glm::translate(glm::mat4(1.0f), glm::vec3(0.3f*vp_left_hand_guard, 1.1f*vp_left_hand_guard, 0.0f)) * hand_guard_transform;
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[11]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[11]);
}

void draw_left_lower_arm(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*lower_arm_transform * glm::rotate(glm::mat4(1.0f), glm::radians(vp_left_elbow_x), glm::vec3(0.0f, 1.0f, 0.0f));;
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[13]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[13]);

  draw_left_hand_guard(vao, vbo, modelview_matrix);
  draw_left_hand(vao, vbo, modelview_matrix);
}

void draw_left_elbow_joint(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*elbow_joint_transform * glm::rotate(glm::mat4(1.0f), glm::radians(vp_left_elbow_y), glm::vec3(0.0f, 0.0f, 1.0f));
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix*elbow_joint_scale));
  normal_matrix = glm::mat3(modelview_matrix*elbow_joint_scale);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix*elbow_joint_scale));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[10]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[10]);

  draw_left_lower_arm(vao, vbo, modelview_matrix);
}

void draw_left_upper_arm(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*left*upper_arm_transform * glm::rotate(glm::rotate(glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(0.99f*vp_left_shoulder_translate, 0.09f*vp_left_shoulder_translate, 0.0f)), glm::radians(vp_left_shoulder_x), glm::vec3(1.0f, 0.0f, 0.0f)), glm::radians(vp_left_shoulder_y), glm::vec3(0.0f, 1.0f, 0.0f)), glm::radians(vp_left_shoulder_z), glm::vec3(0.0f, 0.0f, 1.0f));
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[12]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[12]);

  draw_left_elbow_joint(vao, vbo, modelview_matrix);
}

void draw_left_foot(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*foot_transform * glm::rotate(glm::rotate(glm::rotate(glm::mat4(1.0f), glm::radians(vp_left_foot_x), glm::vec3(1.0f, 0.0f, 0.0f)), glm::radians(vp_left_foot_y), glm::vec3(0.0f, 1.0f, 0.0f)), glm::radians(vp_left_foot_z), glm::vec3(0.0f, 0.0f, 1.0f));
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[7]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[7]);
}

void draw_left_lower_leg(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*lower_leg_transform * glm::rotate(glm::mat4(1.0f), glm::radians(vp_left_knee_y), glm::vec3(1.0f, 0.0f, 0.0f));
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[8]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[8]);

  draw_left_foot(vao, vbo, modelview_matrix);
}

void draw_left_thigh_leg(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*thigh_leg_transform * glm::rotate(glm::mat4(1.0f), glm::radians(vp_left_knee_x), glm::vec3(0.0f, 1.0f, 0.0f));
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[14]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[14]);

  draw_left_lower_leg(vao, vbo, modelview_matrix);
}

void draw_left_thigh(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*thigh_transform * glm::rotate(glm::rotate(glm::mat4(1.0f), glm::radians(vp_left_hip_z), glm::vec3(0.0f, 1.0f, 0.0f)), glm::radians(vp_left_hip_y), glm::vec3(0.0f, 0.0f, 1.0f));
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[9]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[9]);

  draw_left_thigh_leg(vao, vbo, modelview_matrix);
}

void draw_left_hip_joint(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*left*hip_joint_transform * glm::rotate(glm::mat4(1.0f), glm::radians(vp_left_hip_x), glm::vec3(1.0f, 0.0f, 0.0f));
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[10]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[10]);

  draw_left_thigh(vao, vbo, modelview_matrix);
}

void draw_left_wing(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*glm::translate(glm::mat4(1.0f), glm::vec3(-vp_left_wing/360.0f,0.0f, 0.0f))*wing_transform;
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix * modelview_matrix * glm::rotate(glm::mat4(1.0f), glm::radians(vp_left_wing), glm::vec3(0.0f, -1.0f, 0.0f))));
  normal_matrix = glm::mat3(modelview_matrix * glm::rotate(glm::mat4(1.0f), glm::radians(vp_left_wing), glm::vec3(0.0f, -1.0f, 0.0f)));
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix * glm::rotate(glm::mat4(1.0f), glm::radians(vp_left_wing), glm::vec3(0.0f, -1.0f, 0.0f))));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[4]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[4]);

  modelview_matrix = modelview_matrix*z_reflect * glm::rotate(glm::mat4(1.0f), glm::radians(vp_left_wing), glm::vec3(0.0f, -1.0f, 0.0f));
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glDrawArrays(GL_TRIANGLES, 0, sizes[4]);
}

void draw_left_wing_joint(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*wing_joint_transform * glm::rotate(glm::mat4(1.0f), glm::radians(vp_left_wing_wing_torso), glm::vec3(0.0f, 0.0f, -1.0f));
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix*wing_joint_scale));
  normal_matrix = glm::mat3(modelview_matrix*wing_joint_scale);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix*wing_joint_scale));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[10]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[10]);

  draw_left_wing(vao, vbo, modelview_matrix);
}

void draw_left_wing_torso(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*left*wing_torso_transform * glm::rotate(glm::mat4(1.0f), glm::radians(vp_left_wing_torso_torso), glm::vec3(0.0f, 0.0f, -1.0f));
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[5]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[5]);

  draw_left_wing_joint(vao, vbo, modelview_matrix);
}

void draw_left_shoulder_pad(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){//109
  modelview_matrix = modelview_matrix*left*shoulder_pad_transform * glm::rotate(glm::rotate(glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(0.09f*vp_left_shoulder_translate, 0.99f*vp_left_shoulder_translate, 0.0f)), glm::radians(vp_left_shoulder_x), glm::vec3(0.0f, 1.0f, 0.0f)), glm::radians(vp_left_shoulder_y), glm::vec3(-1.0f, 0.0f, 0.0f)), glm::radians(vp_left_shoulder_pad), glm::vec3(0.0f, 0.0f, 1.0f));
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[6]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[6]);
}

//---------------------------------------------UNIVERSAL------------------------------------------------------------------------------

void draw_ship(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*ship_transform*glm::rotate(glm::mat4(1.0f), glm::radians(vp_ship_rotate), glm::vec3(-1.0f, 0.0f, 0.0f));
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[3]);
  glBindBuffer (GL_ARRAY_BUFFER, vbo[3]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[3]);
}

void draw_ship_torso(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*ship_torso_transform * glm::rotate(glm::mat4(1.0f), glm::radians(vp_ship_rotate), glm::vec3(-1.0f, 0.0f, 0.0f));
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[2]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[2]);

  draw_ship(vao, vbo, modelview_matrix);
}

void draw_head(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*head_transform * glm::rotate(glm::rotate(glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, vp_head_translate, 0.0f)), glm::radians(vp_head_x), glm::vec3(1.0f, 0.0f, 0.0f)), glm::radians(vp_head_y), glm::vec3(0.0f, 1.0f, 0.0f)), glm::radians(vp_head_z), glm::vec3(0.0f, 0.0f, 1.0f));
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[1]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[1]);
}

void draw_torso(GLuint vao[], GLuint vbo[]){
  glm::mat4 modelview_matrix = model_matrix * glm::rotate(glm::rotate(glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(vp_xpos, vp_ypos, vp_zpos)), glm::radians(vp_torso_x), glm::vec3(1.0f, 0.0f, 0.0f)), glm::radians(vp_torso_y), glm::vec3(0.0f, 1.0f, 0.0f)), glm::radians(vp_torso_z), glm::vec3(0.0f, 0.0f, 1.0f));
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[0]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[0]);

  draw_right_upper_arm(vao, vbo, modelview_matrix);
  draw_left_upper_arm(vao, vbo, modelview_matrix);
  draw_right_hip_joint(vao, vbo, modelview_matrix);
  draw_left_hip_joint(vao, vbo, modelview_matrix);
  draw_right_wing_torso(vao, vbo, modelview_matrix);
  draw_left_wing_torso(vao, vbo, modelview_matrix);
  draw_head(vao, vbo, modelview_matrix);
  draw_ship_torso(vao, vbo, modelview_matrix);
  draw_right_shoulder_pad(vao, vbo, modelview_matrix);
  draw_left_shoulder_pad(vao, vbo, modelview_matrix);
}

//************************************************************************************************************************************
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
//************************************************************************************************************************************

void vp_transform(void){
  float a = 2*vp_count*vp_form + transform_frames - transform_frames*vp_form - vp_count;
  float b = transform_frames*vp_form + vp_count - 2*vp_count*vp_form;
  a /= transform_frames;
  b /= transform_frames;
  vp_count++;

  vp_ship_rotate = a*rvp_ship_rotate + b*svp_ship_rotate;

  vp_head_x = a*rvp_head_x + b*svp_head_x;
  vp_head_y = a*rvp_head_y + b*svp_head_y;
  vp_head_z = a*rvp_head_z + b*svp_head_z;
  vp_head_translate = a*rvp_head_translate + b*svp_head_translate;

  vp_torso_x = a*rvp_torso_x + b*svp_torso_x;
  vp_torso_y = a*rvp_torso_y + b*svp_torso_y;

  //-------------------------------------Left-----------------------------------------------
  vp_left_wing = a*rvp_left_wing + b*svp_left_wing;
  vp_left_wing_wing_torso = a*rvp_left_wing_wing_torso + b*svp_left_wing_wing_torso;
  vp_left_wing_torso_torso = a*rvp_left_wing_torso_torso + b*svp_left_wing_torso_torso;

  vp_left_shoulder_x = a*rvp_left_shoulder_x + b*svp_left_shoulder_x;
  vp_left_shoulder_y = a*rvp_left_shoulder_y + b*svp_left_shoulder_y;
  vp_left_shoulder_z = a*rvp_left_shoulder_z + b*svp_left_shoulder_z;
  vp_left_shoulder_pad = a*rvp_left_shoulder_pad + b*svp_left_shoulder_pad;
  vp_left_shoulder_translate = a*rvp_left_shoulder_translate + b*svp_left_shoulder_translate;

  vp_left_elbow_x = a*rvp_left_elbow_x + b*svp_left_elbow_x;
  vp_left_elbow_y = a*rvp_left_elbow_y + b*svp_left_elbow_y;

  vp_left_foot_x = a*rvp_left_foot_x + b*svp_left_foot_x;
  vp_left_foot_y = a*rvp_left_foot_y + b*svp_left_foot_y;
  vp_left_foot_z = a*rvp_left_foot_z + b*svp_left_foot_z;

  vp_left_hand_x = a*rvp_left_hand_x + b*svp_left_hand_x;
  vp_left_hand_y = a*rvp_left_hand_y + b*svp_left_hand_y;
  vp_left_hand_z = a*rvp_left_hand_z + b*svp_left_hand_z;

  vp_left_knee_x = a*rvp_left_knee_x + b*svp_left_knee_x;
  vp_left_knee_y = a*rvp_left_knee_y + b*svp_left_knee_y;

  vp_left_hip_x = a*rvp_left_hip_x + b*svp_left_hip_x;
  vp_left_hip_y = a*rvp_left_hip_y + b*svp_left_hip_y;
  vp_left_hip_z = a*rvp_left_hip_z + b*svp_left_hip_z;

  vp_left_hand_guard = a*rvp_left_hand_guard + b*svp_left_hand_guard;

  //-------------------------------------Right----------------------------------------------
  vp_right_wing = a*rvp_right_wing + b*svp_right_wing;
  vp_right_wing_wing_torso = a*rvp_right_wing_wing_torso + b*svp_right_wing_wing_torso;
  vp_right_wing_torso_torso = a*rvp_right_wing_torso_torso + b*svp_right_wing_torso_torso;

  vp_right_shoulder_x = a*rvp_right_shoulder_x + b*svp_right_shoulder_x;
  vp_right_shoulder_y = a*rvp_right_shoulder_y + b*svp_right_shoulder_y;
  vp_right_shoulder_z = a*rvp_right_shoulder_z + b*svp_right_shoulder_z;
  vp_right_shoulder_pad = a*rvp_right_shoulder_pad + b*svp_right_shoulder_pad;
  vp_right_shoulder_translate = a*rvp_right_shoulder_translate + b*svp_right_shoulder_translate;

  vp_right_elbow_x = a*rvp_right_elbow_x + b*svp_right_elbow_x;
  vp_right_elbow_y = a*rvp_right_elbow_y + b*svp_right_elbow_y;

  vp_right_foot_x = a*rvp_right_foot_x + b*svp_right_foot_x;
  vp_right_foot_y = a*rvp_right_foot_y + b*svp_right_foot_y;
  vp_right_foot_z = a*rvp_right_foot_z + b*svp_right_foot_z;

  vp_right_hand_x = a*rvp_right_hand_x + b*svp_right_hand_x;
  vp_right_hand_y = a*rvp_right_hand_y + b*svp_right_hand_y;
  vp_right_hand_z = a*rvp_right_hand_z + b*svp_right_hand_z;

  vp_right_knee_x = a*rvp_right_knee_x + b*svp_right_knee_x;
  vp_right_knee_y = a*rvp_right_knee_y + b*svp_right_knee_y;

  vp_right_hip_x = a*rvp_right_hip_x + b*svp_right_hip_x;
  vp_right_hip_y = a*rvp_right_hip_y + b*svp_right_hip_y;
  vp_right_hip_z = a*rvp_right_hip_z + b*svp_right_hip_z;

  vp_right_hand_guard = a*rvp_right_hand_guard + b*svp_right_hand_guard;

  if(vp_count > transform_frames){
    vp_count = 0;
    vp_transformation = 0;
    vp_form = 1 - vp_form;
  }
}

//************************************************************************************************************************************
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
//************************************************************************************************************************************

void update_lights_camera(){
  vp_light_pos = glm::vec3(model_matrix * glm::rotate(glm::rotate(glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(vp_xpos, vp_ypos, vp_zpos)), glm::radians(vp_torso_x), glm::vec3(1.0f, 0.0f, 0.0f)), glm::radians(vp_torso_y), glm::vec3(0.0f, 1.0f, 0.0f)), glm::radians(vp_torso_z), glm::vec3(0.0f, 0.0f, 1.0f)) * light_pos);
  vp_light_dir = glm::vec3(model_matrix * glm::rotate(glm::rotate(glm::rotate(glm::mat4(1.0f), glm::radians(vp_torso_x), glm::vec3(1.0f, 0.0f, 0.0f)), glm::radians(vp_torso_y), glm::vec3(0.0f, 1.0f, 0.0f)), glm::radians(vp_torso_z), glm::vec3(0.0f, 0.0f, 1.0f)) * light_dir);

  glm::mat4 model_mat = model_matrix * glm::rotate(glm::rotate(glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(vp_xpos, vp_ypos, vp_zpos)), glm::radians(vp_torso_x), glm::vec3(1.0f, 0.0f, 0.0f)), glm::radians(vp_torso_y), glm::vec3(0.0f, 1.0f, 0.0f)), glm::radians(vp_torso_z), glm::vec3(0.0f, 0.0f, 1.0f));
  if(vp_form == 0){
    vp_cent = glm::vec3(model_mat * cent);
    vp_eye = glm::vec3(model_mat * eye);
    vp_up = glm::vec3(model_matrix * glm::rotate(glm::rotate(glm::rotate(glm::mat4(1.0f), glm::radians(vp_torso_x), glm::vec3(1.0f, 0.0f, 0.0f)), glm::radians(vp_torso_y), glm::vec3(0.0f, 1.0f, 0.0f)), glm::radians(vp_torso_z), glm::vec3(0.0f, 0.0f, 1.0f)) * up);
  }
  else{
    vp_cent = glm::vec3(model_mat * cent_t);
    vp_eye = glm::vec3(model_mat * eye_t);
    vp_up = glm::vec3(model_matrix * glm::rotate(glm::rotate(glm::rotate(glm::mat4(1.0f), glm::radians(vp_torso_x), glm::vec3(1.0f, 0.0f, 0.0f)), glm::radians(vp_torso_y), glm::vec3(0.0f, 1.0f, 0.0f)), glm::radians(vp_torso_z), glm::vec3(0.0f, 0.0f, 1.0f)) * up_t);
  }
}

void draw_vector_prime(GLuint vao[], GLuint vbo[]){

  if(vp_transformation==1)
    vp_transform();

  draw_torso(vao, vbo);
  // draw_right_hand(vao, vbo, view_matrix*model_matrix);

  // draw_ship(vao, vbo, view_matrix * model_matrix);
  // modelview_matrix = view_matrix*model_matrix;
  // glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  // normal_matrix = glm::mat3(modelview_matrix); glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  // glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  // glBindVertexArray (vao[11]);
  // glDrawArrays(GL_TRIANGLES, 0, sizes[11]);


  // glm::mat4 modelview_matrix1 = modelview_matrix*hand_guard_transform*glm::translate(glm::mat4(1.0f), glm::vec3(-3.0, 0.0, 0.0));//*glm::rotate(glm::mat4(1.0f), glm::atan(1.0f,11.0f), glm::vec3(0.0f, 0.0f, 1.0f));//*glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f,0.0f,0.0f));
  // glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix1));
  // normal_matrix = glm::transpose (glm::inverse(glm::mat3(modelview_matrix1)));
  // glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  // glBindVertexArray (vao[11]);
  // glDrawArrays(GL_TRIANGLES, 0, sizes[11]);

  // modelview_matrix1 = modelview_matrix1*hand_guard_transform;
  // glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix1));
  // normal_matrix = glm::transpose (glm::inverse(glm::mat3(modelview_matrix1)));
  // glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  // glBindVertexArray (vao[11]);
  // glDrawArrays(GL_TRIANGLES, 0, sizes[11]);

  // modelview_matrix1 = modelview_matrix*ship_torso_transform;
  // glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix1));
  // normal_matrix = glm::transpose (glm::inverse(glm::mat3(modelview_matrix1)));
  // glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  // glBindVertexArray (vao[2]);
  // glDrawArrays(GL_TRIANGLES, 0, ship_torso_size);
}

}
