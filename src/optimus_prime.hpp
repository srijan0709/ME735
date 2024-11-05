#include "transformers.hpp"
#include <iostream>


#define transform_frames 200

GLfloat op_xpos = 0.0f, op_ypos = 13.85f, op_zpos = 0.0f;

GLfloat op_lower_torso_rotate_x =0.0f , op_lower_torso_rotate_y=180.0f, op_lower_torso_rotate_z =0.0f;//extra added 
GLfloat op_ship_rotate_x=90.0f , op_ship_rotate_y =0.0f , op_ship_rotate_z= 0.0f, op_ship_translate= -26.0f; //add
GLfloat op_right_upperarm_x=0.0f, op_right_upperarm_y=0.0f, op_right_upperarm_z=0.0f, op_left_upperarm_x=0.0f, op_left_upperarm_y=0.0f, op_left_upperarm_z=0.0f;
GLfloat op_right_hand_x=0.0f, op_right_hand_y=0.0f, op_right_hand_z=0.0f, op_left_hand_x=0.0f, op_left_hand_y=0.0f, op_left_hand_z=0.0f;

GLfloat op_head_translate=-3.0f, op_head_x=0.0f, op_head_y=0.0f, op_head_z=0.0f; 
GLfloat op_shoulder_translate=-8.0f, op_right_shoulder_x=0.0f, op_right_shoulder_y=90.0f, op_right_shoulder_z=0.0f, op_left_shoulder_x=0.0f, op_left_shoulder_y=90.0f, op_left_shoulder_z=0.0f;
GLfloat op_wrist_translate= -10.0f ,op_right_wrist_x=0.0f, op_right_wrist_y=0.0f, op_right_wrist_z=30.0f, op_left_wrist_x=0.0f, op_left_wrist_y=0.0f, op_left_wrist_z=30.0f;
GLfloat op_right_elbow_x=-90.0f, op_left_elbow_x=-90.0f, op_right_elbow_y=0.0f, op_left_elbow_y=0.0f;

GLfloat op_right_foot_x=-90.0f, op_right_foot_y=0.0f, op_right_foot_z=0.0f, op_left_foot_x=-90.0f, op_left_foot_y=0.0f, op_left_foot_z=0.0f;
GLfloat op_right_knee_x=0.0f, op_left_knee_x=0.0f, op_right_knee_y=0.0f, op_left_knee_y=0.0f;
GLfloat op_right_hip_x=0.0f, op_right_hip_y=0.0f, op_right_hip_z=0.0f, op_left_hip_x=0.0f, op_left_hip_y=0.0f, op_left_hip_z=0.0f;
GLfloat op_torso_x=0.0f, op_torso_y=0.0f, op_torso_z=0.0f;
GLint op_transformation=0;

GLfloat op_light_spread=0.75f;
glm::vec3 op_light1_pos;
glm::vec3 op_light2_pos;
glm::vec3 op_light_dir;
glm::vec3 op_eye;
glm::vec3 op_cent;
glm::vec3 op_up;

namespace op{

const glm::vec4 light1_pos = glm::vec4(-1.7f,0.65f, 2.6f , 1.0f);
const glm::vec4 light2_pos = glm::vec4(+1.7f,0.65f, 2.6f , 1.0f);
const glm::vec4 light_dir = glm::vec4(glm::normalize(glm::vec3(0.0f, 0.25f, -1.0f)), 1.0f);

const glm::vec4 up = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
const glm::vec4 cent = glm::vec4(0.0f, 6.0f, 0.0f, 1.0f);
const glm::vec4 eye = glm::vec4(0.0f, 8.0f, -10.0f, 1.0f);

const GLfloat sop_lower_torso_rotate_x =0.0f , sop_lower_torso_rotate_y=180.0f, sop_lower_torso_rotate_z =0.0f;//extra added
const GLfloat sop_ship_rotate_x=90.0f , sop_ship_rotate_y =0.0f , sop_ship_rotate_z= 0.0f, sop_ship_translate= -26.0f;
const GLfloat sop_right_upperarm_x=0.0f, sop_right_upperarm_y=0.0f, sop_right_upperarm_z=0.0f, sop_left_upperarm_x=0.0f, sop_left_upperarm_y=0.0f, sop_left_upperarm_z=0.0f;
const GLfloat sop_right_hand_x=0.0f, sop_right_hand_y=0.0f, sop_right_hand_z=0.0f, sop_left_hand_x=0.0f, sop_left_hand_y=0.0f, sop_left_hand_z=0.0f;
const GLfloat sop_head_translate=-3.0f, sop_head_x=0.0f, sop_head_y=0.0f, sop_head_z=0.0f;
const GLfloat sop_wrist_translate= -10.0f ,sop_right_wrist_x=0.0f, sop_right_wrist_y=0.0f, sop_right_wrist_z=30.0f, sop_left_wrist_x=0.0f, sop_left_wrist_y=0.0f, sop_left_wrist_z=30.0f; 
const GLfloat sop_shoulder_translate=-8.0f, sop_right_shoulder_x=0.0f, sop_right_shoulder_y=90.0f, sop_right_shoulder_z=0.0f, sop_left_shoulder_x=0.0f, sop_left_shoulder_y=90.0f, sop_left_shoulder_z=0.0f;
const GLfloat sop_right_elbow_x=-90.0f, sop_left_elbow_x=-90.0f, sop_right_elbow_y=0.0f, sop_left_elbow_y=0.0f;
const GLfloat sop_right_foot_x=-90.0f, sop_right_foot_y=0.0f, sop_right_foot_z=0.0f, sop_left_foot_x=-90.0f, sop_left_foot_y=0.0f, sop_left_foot_z=0.0f;
const GLfloat sop_right_knee_x=0.0f, sop_left_knee_x=0.0f, sop_right_knee_y=90.0f, sop_left_knee_y=0.0f;
const GLfloat sop_right_hip_x=0.0f, sop_right_hip_y=0.0f, sop_right_hip_z=0.0f, sop_left_hip_x=0.0f, sop_left_hip_y=0.0f, sop_left_hip_z=0.0f;
const GLfloat sop_torso_x=0.0f, sop_torso_y=0.0f;

const GLfloat rop_lower_torso_rotate_x =0.0f , rop_lower_torso_rotate_y=0.0f, rop_lower_torso_rotate_z =0.0f;
const GLfloat rop_ship_translate =0.0f, rop_ship_rotate_x=0.0f , rop_ship_rotate_y =0.0f , rop_ship_rotate_z= 0.0f;
const GLfloat rop_right_upperarm_x=0.0f, rop_right_upperarm_y=0.0f, rop_right_upperarm_z=0.0f, rop_left_upperarm_x=0.0f, rop_left_upperarm_y=0.0f, rop_left_upperarm_z=0.0f;
const GLfloat rop_right_hand_x=0.0f, rop_right_hand_y=0.0f, rop_right_hand_z=0.0f, rop_left_hand_x=0.0f, rop_left_hand_y=0.0f, rop_left_hand_z=0.0f;
const GLfloat rop_head_translate=0.0f, rop_head_x=0.0f, rop_head_y=0.0f, rop_head_z=0.0f; 
const GLfloat rop_wrist_translate= 0.0f ,rop_right_wrist_x=0.0f, rop_right_wrist_y=0.0f, rop_right_wrist_z=0.0f, rop_left_wrist_x=0.0f, rop_left_wrist_y=0.0f, rop_left_wrist_z=0.0f; 
const GLfloat rop_shoulder_translate=0.0f, rop_right_shoulder_x=0.0f, rop_right_shoulder_y=0.0f, rop_right_shoulder_z=0.0f, rop_left_shoulder_x=0.0f, rop_left_shoulder_y=0.0f, rop_left_shoulder_z=0.0f;
const GLfloat rop_right_elbow_x=0.0f, rop_left_elbow_x=0.0f, rop_right_elbow_y=0.0f, rop_left_elbow_y=0.0f;
const GLfloat rop_right_foot_x=0.0f, rop_right_foot_y=0.0f, rop_right_foot_z=0.0f, rop_left_foot_x=0.0f, rop_left_foot_y=0.0f, rop_left_foot_z=0.0f;
const GLfloat rop_right_knee_x=0.0f, rop_left_knee_x=0.0f, rop_right_knee_y=0.0f, rop_left_knee_y=0.0f;
const GLfloat rop_right_hip_x=0.0f, rop_right_hip_y=0.0f, rop_right_hip_z=0.0f, rop_left_hip_x=0.0f, rop_left_hip_y=0.0f, rop_left_hip_z=0.0f;
const GLfloat rop_torso_x=0.0f, rop_torso_y=0.0f;

GLint op_count=0, op_form=1;


const int buff_size = 12;
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

//upper ship - torso joint
const glm::mat4 ship_torso_transform = glm::translate(glm::mat4(1.0f), glm::vec3(50.0f, -93.0f, 25.7f));
const int ship_torso_size = 500;
void ship_torso(glm::vec4 positions[ship_torso_size], glm::vec3 normals[ship_torso_size], glm::vec4 colors[ship_torso_size])
{

glm::mat4 reflect = {glm::vec4(-1.0f, 0.0f, 0.0f, 0.0f),glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),};
glm::mat3 reflect2 = {glm::vec3(-1.0f, 0.0f, 0.0f),glm::vec3(0.0f, 1.0f, 0.0f),glm::vec3(0.0f, 0.0f, 1.0f)};
 glm::vec3 vertices[]={glm::vec3(86.73f -40.0f, 31.5f, 23.0f),
                      glm::vec3(61.5f-40.0f, 31.5f, 23.0f),
                      glm::vec3(61.5f-40.0f, 11.8f, 23.0f),
                      glm::vec3(76.0f-40.0f, 11.8f, 23.0f),

                      glm::vec3(61.5f-40.0f, 31.5f, 1.0f),
                      glm::vec3(86.73f-40.0f, 31.5f, 1.0f),
                      glm::vec3(76.0f-40.0f, 11.8f, 1.0f),
                      glm::vec3(61.5f-40.0f, 11.8f, 1.0f),
                      


                       glm::vec3(76.0f-40.0f, 11.8f, 23.0f),
                      glm::vec3(61.5f-40.0f, 11.8f, 23.0f),
                     
                      glm::vec3(61.5f-40.0f, 0.0f, 23.0f),
                      glm::vec3(78.5f-40.0f, 0.0f, 23.0f), //7

                       glm::vec3(61.5f-40.0f, 11.8f, 1.0f),
                     
                      glm::vec3(76.0f-40.0f, 11.8f, 1.0f),
                      glm::vec3(78.5f-40.0f, 0.0f, 1.0f),
                      glm::vec3(61.5f-40.0f, 0.0f, 1.0f),  //top struct 
                       //15

                       // box yellow

                       glm::vec3(80.0f-40.0f, 0.0f, 23.0f),
                      glm::vec3(52.5f-40.0f, 0.0f, 23.0f),
                      glm::vec3(52.5f-40.0f, -31.7f, 23.0f),
                      glm::vec3(80.0f-40.0f, -31.7f, 23.0f),

                      glm::vec3(52.5f-40.0f, 0.0f, 1.0f),
                      glm::vec3(80.0f-40.0f, 0.0f, 1.0f),
                      glm::vec3(80.0f-40.0f, -31.7f, 1.0f),
                      glm::vec3(52.5f-40.0f, -31.7f, 1.0f),

                      //connectors

                      glm::vec3(74.5f-40.0f, -31.7f, 23.0f),
                      glm::vec3(74.5f-40.0f, -45.7f, 23.0f),

                      glm::vec3(74.5f-40.0f, -31.7f, 0.0f),
                      glm::vec3(74.5f-40.0f, -45.7f, 0.0f),
                      

                      glm::vec3(51.5f-40.0f, -31.7f, 23.0f),
                      glm::vec3(51.5f-40.0f, -45.7f, 23.0f),

                      glm::vec3(51.5f-40.0f, -31.7f, 0.0f),
                      glm::vec3(51.5f-40.0f, -45.7f, 0.0f),
                      

                     // mid square

                     glm::vec3(52.5f-40.0f, -12.0f, 23.0f),
                      glm::vec3(40.0f-40.0f, -12.0f, 23.0f),
                      glm::vec3(40.0f-40.0f, -31.7f, 23.0f),
                      glm::vec3(52.5f-40.0f, -31.7f, 23.0f),

                      glm::vec3(52.5f-40.0f, -12.0f, 1.0f),
                      glm::vec3(40.0f-40.0f, -12.0f, 1.0f),
                      glm::vec3(40.0f-40.0f, -31.7f, 1.0f),
                      glm::vec3(52.5f-40.0f, -31.7f, 1.0f),

                    


                      

                     };

glm::vec4 ship_torso_positions[]={
                        glm::vec4(vertices[0],1.0f),
                        glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         
                         glm::vec4(vertices[0],1.0f),
                          glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         //front 

                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[7],1.0f), //back


                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[2],1.0f), // side

                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[6],1.0f), //side 

                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         //top

                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[3],1.0f),//bottom


                         //add 8 ------------------------------------
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[10],1.0f),
                          //front 

                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[15],1.0f), //back


                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[10],1.0f), // side

                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[14],1.0f), //side 

                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[9],1.0f),//top

                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[11],1.0f),//bottom
                        //  //----------------------------------------------------

                        //   // add 8 
                        glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[17],1.0f),
                        
                         glm::vec4(vertices[16],1.0f),
                          glm::vec4(vertices[19],1.0f),
                         glm::vec4(vertices[18],1.0f),
                         //front 

                         glm::vec4(vertices[21],1.0f),
                         glm::vec4(vertices[20],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[20],1.0f),
                         glm::vec4(vertices[23],1.0f), //back


                         glm::vec4(vertices[20],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[18],1.0f), // side

                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[21],1.0f),
                         glm::vec4(vertices[19],1.0f),
                         glm::vec4(vertices[19],1.0f),
                         glm::vec4(vertices[21],1.0f),
                         glm::vec4(vertices[22],1.0f), //side 

                         glm::vec4(vertices[21],1.0f),
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[20],1.0f),
                         glm::vec4(vertices[20],1.0f),
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[17],1.0f),//top

                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[19],1.0f),//bottom

                        //  //----------------
                         glm::vec4(vertices[24],1.0f),
                         glm::vec4(vertices[26],1.0f),
                         glm::vec4(vertices[25],1.0f),
                         glm::vec4(vertices[25],1.0f),
                         glm::vec4(vertices[26],1.0f),
                         glm::vec4(vertices[27],1.0f),

                         glm::vec4(vertices[28],1.0f),
                         glm::vec4(vertices[30],1.0f),
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[30],1.0f),
                         glm::vec4(vertices[31],1.0f),

                         //mid
                          glm::vec4(vertices[32],1.0f),
                          glm::vec4(vertices[34],1.0f),
                         glm::vec4(vertices[33],1.0f),
                         
                         glm::vec4(vertices[32],1.0f),
                         glm::vec4(vertices[35],1.0f),
                         glm::vec4(vertices[34],1.0f),
                          //front 

                         glm::vec4(vertices[36],1.0f),
                         glm::vec4(vertices[37],1.0f),
                         glm::vec4(vertices[38],1.0f),
                         glm::vec4(vertices[36],1.0f),
                         glm::vec4(vertices[38],1.0f),
                         glm::vec4(vertices[39],1.0f), //back


                         glm::vec4(vertices[36],1.0f),
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[39],1.0f),
                         glm::vec4(vertices[39],1.0f),
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[34],1.0f), // side

                         glm::vec4(vertices[32],1.0f),
                         glm::vec4(vertices[37],1.0f),
                         glm::vec4(vertices[35],1.0f),
                         glm::vec4(vertices[35],1.0f),
                         glm::vec4(vertices[37],1.0f),
                         glm::vec4(vertices[38],1.0f), //side 

                         glm::vec4(vertices[32],1.0f),
                         glm::vec4(vertices[37],1.0f),
                         glm::vec4(vertices[36],1.0f),
                         glm::vec4(vertices[37],1.0f),
                         glm::vec4(vertices[36],1.0f),
                         glm::vec4(vertices[33],1.0f),//top

                         glm::vec4(vertices[34],1.0f),
                         glm::vec4(vertices[39],1.0f),
                         glm::vec4(vertices[38],1.0f),
                         glm::vec4(vertices[39],1.0f),
                         glm::vec4(vertices[34],1.0f),
                         glm::vec4(vertices[35],1.0f),//bottom
                };

int len = sizeof(ship_torso_positions)/16;
copy_col_norm(len, normals, colors, positions, ship_torso_positions, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f) ,  true, reflect, reflect2);

}

//flap extensions (flap - torso joint)
const glm::mat4 wing_torso_transform = glm::translate(glm::mat4(1.0f), glm::vec3(1.4f, 3.0f, -2.71f));
const int wing_torso_size = 192+48;
void wing_torso(glm::vec4 positions[wing_torso_size], glm::vec3 normals[wing_torso_size], glm::vec4 colors[wing_torso_size])
{
glm::vec3 vertices[]={glm::vec3(0.0f, 0.0f, 23.5f),
                      glm::vec3(32.0f, 0.0f, 23.5f),
                      glm::vec3(32.0f, -18.5f, 23.5f),
                      glm::vec3(-0.0f, -18.5f, 23.5f),

                      glm::vec3(32.5f, -0.0f, 0.5f),
                      glm::vec3(0.0f, 0.0f, 0.5f),
                      glm::vec3(0.0f, -18.5f, 0.5f),
                      glm::vec3(32.0f, -18.5f, 0.0f),

                     };

glm::vec4 wing_torso_positions[]={glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[3],1.0f), //front 

                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[7],1.0f), //back


                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[2],1.0f), // side

                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[6],1.0f), //side 

                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[1],1.0f),//top

                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[3],1.0f),//bottom

                         };

int len = sizeof(wing_torso_positions)/16;
copy_col_norm(len, normals, colors, positions, wing_torso_positions, glm::vec4(1.0f, 0.1f, 0.1f, 1.0f));
}


//foot
const glm::mat4 foot_transform = glm::translate(glm::mat4(1.0f), glm::vec3(15.0f, -206.05f, -15.75f));
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
copy_col_norm(len, normals, colors, positions, foot_positions, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), true, reflect, reflect2);
}

//lower leg
const glm::mat4 lower_leg_transform = glm::mat4(1.0f);
const int lower_leg_size = 243;
void lower_leg(glm::vec4 positions[lower_leg_size], glm::vec3 normals[lower_leg_size], glm::vec4 colors[lower_leg_size])
{
glm::vec3 vertices[]={glm::vec3(33.5f, -60.0f, -30.5f),
                      glm::vec3(-7.0f, -60.0f, -30.5f),
                      glm::vec3(-7.0f, -153.0f, -30.5f),
                      glm::vec3(33.5f, -153.0f, -30.5f),

                      glm::vec3(-7.0f, -60.0f, 6.5f),
                      glm::vec3(24.5f, -60.0f, 1.5f),
                      glm::vec3(24.5f, -153.0f, 1.5f),
                      glm::vec3(-7.0f, -153.0f, 6.5f),

                     

                     };

glm::vec4 lower_leg_positions[]={glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[3],1.0f), //front 

                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[7],1.0f), //back


                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[2],1.0f), // side

                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[6],1.0f), //side 

                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[1],1.0f),//top

                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[3],1.0f),//bottom

                         };

int len = sizeof(lower_leg_positions)/16;
copy_col_norm(len, normals, colors, positions, lower_leg_positions, glm::vec4(0.1f, 0.1f, 1.0f, 1.0f));

}


const glm::mat4 hip_joint_transform = glm::translate(glm::mat4(1.0f), glm::vec3(12.6f, -23.0f, 25.0f));
const glm::mat4 elbow_joint_transform = glm::rotate(glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.4f, 0.0f)), glm::radians(-90.0f), glm::vec3(0.0f,1.0f,0.0f)), glm::radians(90.0f), glm::vec3(0.0f,0.0f,1.0f));
const glm::mat4 wing_joint_transform = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(6.0f, 0.0f, 0.75f)), glm::vec3(-1.0f, 1.0f, 1.0f));
const glm::mat4 wing_joint_scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.4/0.9f, 1.4/0.9f, 0.5/0.9f));
const glm::mat4 elbow_joint_scale = glm::scale(glm::mat4(1.0f), glm::vec3(2.0/3.0f, 2.0/3.0f, 2.0/3.0f));
const int joint_size = 132;
void joint(glm::vec4 positions[joint_size], glm::vec3 normals[joint_size], glm::vec4 colors[joint_size])
{
glm::vec3 vertices[]={
                   

                      glm::vec3(20.0f, -7.0f, -25.0f),
                      glm::vec3(0.0f, -7.0f, -25.0f),
                      glm::vec3(-2.50f,  -60.0f, -26.5f),
                      glm::vec3(24.53f, -60.0f, -26.5f),

                      glm::vec3(0.0f, -7.0f, 0.0f),
                      glm::vec3(20.0f, -7.0f, 0.0f),
                      glm::vec3(20.0f, -60.0f, 1.5f),
                      glm::vec3(-2.5f,  -60.0f, 1.5f),

                     };

glm::vec4 joint_positions[]={glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[3],1.0f), //front 

                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[7],1.0f), //back


                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[2],1.0f), // side

                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[6],1.0f), //side 

                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[1],1.0f),//top

                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[3],1.0f),//bottom

                

                         };

int len = sizeof(joint_positions)/16;
copy_col_norm(len, normals, colors, positions, joint_positions, glm::vec4(0.1f, 0.1f, 1.0f, 1.0f));
}

const glm::mat4 wrist_joint_transform = glm::translate(glm::rotate(glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f)) , glm::radians(-30.0f), glm::vec3(0.0f, 0.0f, 1.0f)) , glm::vec3(45.6f, -15.0f, 30.0f));
const int wrist_size = 132;
void wrist(glm::vec4 positions[wrist_size], glm::vec3 normals[wrist_size], glm::vec4 colors[wrist_size])
{
glm::vec3 vertices[]={glm::vec3(1.0f, 3.4f, 0.1f),
                      glm::vec3(38.0f, 3.4f, 0.1f),
                      glm::vec3(38.0f, -29.0f, 0.0f),
                      glm::vec3(1.0f, -29.0f, 0.0f),

                      glm::vec3(-12.5f, -0.0f, 0.0f),
                      glm::vec3(1.0f, 0.0f, 0.0f),
                      glm::vec3(1.0f, -15.0f, 0.0f),
                      glm::vec3(-12.5f, -15.0f, 0.0f),

                      glm::vec3(1.0f, 3.4f, -30.1f),
                      glm::vec3(38.0f, 3.4f, -30.1f),
                      glm::vec3(38.0f, -29.0f, -30.0f),
                      glm::vec3(1.0f, -29.0f, -30.0f),

                      glm::vec3(-12.5f, -0.0f, -30.0f),
                      glm::vec3(1.0f, 0.0f, -30.0f),
                      glm::vec3(1.0f, -15.0f, -30.0f),
                      glm::vec3(-12.5f, -15.0f, -30.0f),




                     };

glm::vec4 wrist_positions[]={glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[3],1.0f), //front 

                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[7],1.0f), 

                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[8],1.0f), //back 

                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[12],1.0f), 

                         //
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[3],1.0f), 

                        glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[5],1.0f), 

                        glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[6],1.0f), 

                        glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[7],1.0f), 




                         };
int len = sizeof(wrist_positions)/16;
copy_col_norm(len, normals, colors, positions, wrist_positions, glm::vec4(1.0f, 0.1f, 0.1f, 1.0f));
}



//torso complete //part 1 
const int torso_size = 2*(363+24+30+24+9);
void torso(glm::vec4 positions[torso_size], glm::vec3 normals[torso_size], glm::vec4 colors[torso_size])
{
glm::mat4 reflect = {glm::vec4(-1.0f, 0.0f, 0.0f, 0.0f),glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),};
glm::mat3 reflect2 = {glm::vec3(-1.0f, 0.0f, 0.0f),glm::vec3(0.0f, 1.0f, 0.0f),glm::vec3(0.0f, 0.0f, 1.0f)};

glm::vec3 vertices[]={glm::vec3(1.0f, 0.0f, 50.0f),
                      glm::vec3(100.0f, 0.0f, 50.0f),
                      glm::vec3(100.0f, -60.0f, 50.0f),
                      glm::vec3(1.0f, -60.0f, 50.0f),  // front

                      glm::vec3(100.0f, -60.0f, 0.0f),
                      glm::vec3(1.0f, -60.0f, 0.0f),

                      glm::vec3(68.0f, -60.0f, 0.0f),
                      glm::vec3(68.0f, -60.0f, -24.0f),
                      glm::vec3(33.0f, -60.0f, -24.0f),
                      glm::vec3(33.0f, -60.0f, 0.0f), // bottom

                      glm::vec3(1.0f, -20.0f, 33.0f),  //10 //-0.5
                      glm::vec3(1.0f, -60.0f, 32.35f), //11 //-0,5

                      glm::vec3(0.0f, -20.0f, 1.0f),  //12
                      glm::vec3(0.0f, -60.0f, 1.0f), //13

                      glm::vec3(30.0f, -20.0f, 0.0f),
                      glm::vec3(33.0f, -60.0f, 0.0f),
                      glm::vec3(30.0f, -20.0f, 33.0f), //16

                      glm::vec3(30.0f, 0.0f, 33.0f),
                      glm::vec3(30.0f, 0.0f, 0.0f),
                      glm::vec3(33.0f, -60.0f, -22.0f),
                      glm::vec3(33.0f, 2.0f, -22.0f),//20 

                      glm::vec3(1.0f, 2.0f, 33.0f), //21  //-1.5

                      glm::vec3(100.0f, 2.0f, 33.0f), //22 

                      glm::vec3(100.0f, -20.0f, 33.35f), 
                      glm::vec3(100.0f, -60.0f, 32.35f), 
                      glm::vec3(100.0f, -20.0f,0.0f), 
                      glm::vec3(100.0f, -60.0f, 0.0f), 
                      glm::vec3(70.0f, -20.0f, 0.0f), 
                      glm::vec3(70.0f, -60.0f, 0.0f), //28
                      glm::vec3(70.0f, -20.0f, 33.0f), 
                      glm::vec3(70.0f, 0.0f, 33.0f), 
                      glm::vec3(70.0f, 0.0f,0.0f), 
                      glm::vec3(70.0f, -60.0f, -22.0f), 
                      glm::vec3(70.0f, 2.0f, -22.0f),  


                     };

glm::vec4 torso_positions[]={glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[3],1.0f), // front 


                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[3],1.0f),

                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[8],1.0f), // bottom
                        
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[21],1.0f),
                         glm::vec4(vertices[21],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[11],1.0f), 
                         

                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[13],1.0f),


                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[20],1.0f),
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[20],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[19],1.0f),

                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[21],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[17],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[16],1.0f),


                         glm::vec4(vertices[20],1.0f),
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[20],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[19],1.0f),

                         

                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[21],1.0f),

                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[24],1.0f),

                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[20],1.0f),
                         glm::vec4(vertices[19],1.0f),
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[19],1.0f),
                         glm::vec4(vertices[32],1.0f),


                        //  //add 13 and  reverved --------------------------------

                         glm::vec4(vertices[24],1.0f),
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[25],1.0f),
                         glm::vec4(vertices[26],1.0f),
                         glm::vec4(vertices[24],1.0f),
                         glm::vec4(vertices[25],1.0f),


                         glm::vec4(vertices[26],1.0f),
                         glm::vec4(vertices[25],1.0f),
                         glm::vec4(vertices[27],1.0f),
                         glm::vec4(vertices[28],1.0f),
                         glm::vec4(vertices[26],1.0f),
                         glm::vec4(vertices[27],1.0f),
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[30],1.0f),
                         glm::vec4(vertices[31],1.0f),
                         glm::vec4(vertices[27],1.0f),
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[31],1.0f),
                         glm::vec4(vertices[28],1.0f),
                         glm::vec4(vertices[31],1.0f),
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[32],1.0f),
                         glm::vec4(vertices[28],1.0f),
                         glm::vec4(vertices[33],1.0f),

                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[27],1.0f),
                         glm::vec4(vertices[25],1.0f),
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[27],1.0f),
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[30],1.0f),
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[30],1.0f),


                         glm::vec4(vertices[28],1.0f),
                         glm::vec4(vertices[31],1.0f),
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[32],1.0f),
                         glm::vec4(vertices[28],1.0f),
                         glm::vec4(vertices[33],1.0f),

                         //-----------------------------------------------

        
                       
                         
                         };
int len = sizeof(torso_positions)/16;
copy_col_norm(len, normals, colors, positions, torso_positions, glm::vec4(1.0f, 0.1f, 0.1f, 1.0f), false, reflect, reflect2);

glm::vec2 t_coords[4] = {
  glm::vec2( 0.0, 0.0),
  glm::vec2( 0.0, 1.0),
  glm::vec2( 1.0, 0.0),
  glm::vec2( 1.0, 1.0)
};


// for(int i=0;i<6;i++){
colors[0] = glm::vec4(glm::vec2(t_coords[2]) , 1,0.0f);
colors[1] = glm::vec4(glm::vec2(t_coords[3]), 1,0.0f);
colors[2] = glm::vec4(glm::vec2(t_coords[1]), 1,0.0f);
colors[3] = glm::vec4(glm::vec2(t_coords[2]), 1,0.0f);
colors[4] = glm::vec4(glm::vec2(t_coords[1]), 1,0.0f);
colors[5] = glm::vec4(glm::vec2(t_coords[0]), 1,0.0f);
//   colors[260-i]=glm::vec4(1.0f, 0.1f, 0.1f, 1.0f);
//   colors[260+len-i]=glm::vec4(210/255.0f, 4/255.0f, 45/255.0f, 1.0f);
// }

}


const int lower_torso_size = 2*(363+24+30+24+9) + 100;
void lower_torso(glm::vec4 positions[lower_torso_size], glm::vec3 normals[lower_torso_size], glm::vec4 colors[lower_torso_size])
{
glm::mat4 reflect = {glm::vec4(-1.0f, 0.0f, 0.0f, 0.0f),glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),};
glm::mat3 reflect2 = {glm::vec3(-1.0f, 0.0f, 0.0f),glm::vec3(0.0f, 1.0f, 0.0f),glm::vec3(0.0f, 0.0f, 1.0f)};

glm::vec3 vertices[]={glm::vec3(-3.0f, 0.0f, 52.0f),
                      glm::vec3(39.0f, 0.0f, 52.0f),
                      glm::vec3(39.0f, -32.0f, 52.0f),
                      glm::vec3(-3.0f, -32.0f, 52.0f),
                      glm::vec3(38.5f, -57.5f, 51.5f),
                      glm::vec3(-3.0f, -57.5f, 51.5f), // front 

                      glm::vec3(38.5f, 0.0f, 52.0f),
                      glm::vec3(38.5f, 0.0f, 16.57f),
                      glm::vec3(38.5f, -32.0f, 17.07f),
                      glm::vec3(39.0f, -32.0f, 52.0f),

                      glm::vec3(30.5f, 0.0f, -5.64f), //10 
                      glm::vec3(30.5f, -32.0f, 0.0f), //11
                      glm::vec3(30.5f, -42.0f, -0.5f), //12
                      glm::vec3(38.5f, -42.0f, 17.07f), //13
                    
                      glm::vec3(38.5f, -42.0f, 43.5f), 
                      glm::vec3(38.5f, -42.0f, 52.0f),  
                      glm::vec3(38.5f, -57.5f, 43.5f), 
                      glm::vec3(38.5f, -57.5f, 52.0f),   //side(2) done 


                      glm::vec3(-3.0f, 0.0f, 52.0f),
                      glm::vec3(-3.0f, 0.0f, 16.57f),
                      glm::vec3(-3.0f, -32.0f, 16.57f),
                      glm::vec3(-3.0f, -32.0f, 52.0f),

                      glm::vec3(5.5f, 0.0f, -5.64f), // 22
                      glm::vec3(5.5f, -32.0f, 0.0f), // 23
                      glm::vec3(6.0f, -42.0f, -0.5f), //
                      glm::vec3(-2.5f, -42.0f, 17.07f), //

                      glm::vec3(-2.5f, -42.0f, 43.5f), 
                      glm::vec3(-2.5f, -42.0f, 52.0f),  
                      glm::vec3(-2.5f, -57.5f, 43.5f), 
                      glm::vec3(-2.5f, -57.5f, 52.0f),  // side 3 done

                      // side inner
                      glm::vec3(30.5f, 0.0f, 16.57f), //30
                      glm::vec3(30.5f, -32.0f, 16.57f), 
                      glm::vec3(5.5f, 0.0f, 16.57f), 
                      glm::vec3(5.5f, -32.0f, 16.57f), 

                      glm::vec3(30.5f, -42.0f, 16.57f),  //34
                       glm::vec3(5.5f, -42.0f, 16.57f), 

                     };

glm::vec4 lower_torso_positions[]={glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[3],1.0f), 
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[5],1.0f), //front 


                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[6],1.0f), // side (2)
                         glm::vec4(vertices[30],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[30],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[31],1.0f),

                         glm::vec4(vertices[31],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[31],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[34],1.0f),

                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[17],1.0f),

                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[30],1.0f),
                         glm::vec4(vertices[31],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[31],1.0f),
                         glm::vec4(vertices[8],1.0f),

                         glm::vec4(vertices[32],1.0f),
                         glm::vec4(vertices[19],1.0f),
                         glm::vec4(vertices[20],1.0f),
                         glm::vec4(vertices[32],1.0f),
                         glm::vec4(vertices[20],1.0f),
                         glm::vec4(vertices[33],1.0f),





                         //add 12 and reverse ----------------------------------

                         glm::vec4(vertices[20],1.0f),
                         glm::vec4(vertices[19],1.0f),
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[18],1.0f),
                         glm::vec4(vertices[21],1.0f),
                         glm::vec4(vertices[20],1.0f), // side(3)

                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[32],1.0f),
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[32],1.0f),

                         glm::vec4(vertices[24],1.0f),
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[35],1.0f),//.
                         glm::vec4(vertices[24],1.0f),
                         glm::vec4(vertices[33],1.0f),

                         glm::vec4(vertices[25],1.0f),
                         glm::vec4(vertices[20],1.0f),
                         glm::vec4(vertices[21],1.0f),
                         glm::vec4(vertices[27],1.0f),
                         glm::vec4(vertices[25],1.0f),
                         glm::vec4(vertices[21],1.0f),
                         glm::vec4(vertices[28],1.0f),
                         glm::vec4(vertices[26],1.0f),
                         glm::vec4(vertices[27],1.0f),
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[28],1.0f),
                         glm::vec4(vertices[27],1.0f),

                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[34],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[31],1.0f),
                         glm::vec4(vertices[34],1.0f),
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[25],1.0f),
                         glm::vec4(vertices[35],1.0f),
                         glm::vec4(vertices[33],1.0f),
                         glm::vec4(vertices[20],1.0f),
                         glm::vec4(vertices[25],1.0f),

                         // side  inner



                         //back
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[11],1.0f),

                         //top
                          glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[19],1.0f),
                         glm::vec4(vertices[7],1.0f),
                          glm::vec4(vertices[32],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[30],1.0f),
                         glm::vec4(vertices[32],1.0f),
                         glm::vec4(vertices[22],1.0f),
                         glm::vec4(vertices[10],1.0f),

                         //bottom

                          glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[23],1.0f),
                         glm::vec4(vertices[24],1.0f),
                         glm::vec4(vertices[11],1.0f),
                         glm::vec4(vertices[24],1.0f),
                         glm::vec4(vertices[12],1.0f),
                          glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[24],1.0f),
                         glm::vec4(vertices[35],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[35],1.0f),
                         glm::vec4(vertices[34],1.0f),

                          glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[25],1.0f),
                         glm::vec4(vertices[26],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[26],1.0f),
                         glm::vec4(vertices[14],1.0f),


                          glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[28],1.0f),
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[16],1.0f),
                         glm::vec4(vertices[29],1.0f),
                         glm::vec4(vertices[17],1.0f),

                          glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[26],1.0f),
                         glm::vec4(vertices[28],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[28],1.0f),
                         glm::vec4(vertices[16],1.0f),


                         //--------------------------------------------------

                         };
int len = sizeof(lower_torso_positions)/16;
copy_col_norm(len, normals, colors, positions, lower_torso_positions, glm::vec4(1.0f, 0.1f, 0.1f, 1.0f), false, reflect, reflect2);


}
//upper arm
const glm::mat4 upper_arm_transform = glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(53.4f, 4.89f, 5.9f)), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
const int upper_arm_size = 324;
void upper_arm(glm::vec4 positions[upper_arm_size], glm::vec3 normals[upper_arm_size], glm::vec4 colors[upper_arm_size])
{
glm::vec3 vertices[]={glm::vec3(0.0f, 0.0f, 25.0f),
                      glm::vec3(28.0f, 0.0f, 25.0f),
                      glm::vec3(28.0f,  -28.0f, 25.0f),
                      glm::vec3(0.0f, -28.0f, 25.0f),

                      glm::vec3(28.0f, 0.0f, 0.0f),
                      glm::vec3(0.0f, 0.0f, 0.0f),
                      glm::vec3(0.0f, -28.0f, -0.0f),
                      glm::vec3(28.0f,  -28.0f, 0.0f),

                      //circle->square

                      glm::vec3(28.0f, -2.05f, 40.0f),
                      glm::vec3(28.0f, -2.05f, 25.0f),
                      glm::vec3(28.0f, -17.05f, 25.0f),
                      glm::vec3(28.0f, -17.05f, 40.0f),

                      glm::vec3(0.0f, -2.05f, 40.0f),
                      glm::vec3(0.0f, -2.05f, 25.0f),
                      glm::vec3(0.0f, -17.05f, 25.0f),
                      glm::vec3(0.0f, -17.05f, 40.0f),

                     

                     };

glm::vec4 upper_arm_positions[]={glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[3],1.0f), //front 

                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[7],1.0f), //back


                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[2],1.0f), // side

                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[6],1.0f), //side 

                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[1],1.0f),//top

                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[3],1.0f),//bottom


                         //circles
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[11],1.0f),

                          //add 4 and reverse----------------------------------
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         //--------------------------------------------------------

                         };

int len = sizeof(upper_arm_positions)/16;
copy_col_norm(len, normals, colors, positions, upper_arm_positions, glm::vec4(1.0f, 0.1f, 0.1f, 1.0f));
}

//lower arm
const glm::mat4 lower_arm_transform = glm::translate(glm::rotate(glm::rotate(glm::mat4(1.0f), glm::radians(00.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(-0.05f, -24.6f, 0.0f));
const int lower_arm_size = 84;
void lower_arm(glm::vec4 positions[lower_arm_size], glm::vec3 normals[lower_arm_size], glm::vec4 colors[lower_arm_size])
{
glm::vec3 vertices[]={glm::vec3(0.0f, -0.88f, 30.0f),
                      glm::vec3(24.0f, -0.88f, 30.0f),
                      glm::vec3(24.0f,  -32.88f, 30.0f),
                      glm::vec3(0.0f, -32.88f, 30.0f),

                      glm::vec3(25.0f,-0.88f, 0.0f),
                      glm::vec3(0.0f,-0.88f, 0.0f),
                      glm::vec3(0.0f,-32.88f, 0.0f),
                      glm::vec3(25.0f,-32.88f, 0.0f),

                      //circles
                      glm::vec3(6.0f,-32.88f, 30.0f),
                      glm::vec3(19.0f,-32.88f, 30.0f),
                      
                      glm::vec3(19.0f,-45.00f, 30.0f),
                      glm::vec3(6.0f,-45.00f, 30.0f),

                      //circles 
                      glm::vec3(6.0f,-32.88f, 0.0f),
                      glm::vec3(19.0f,-32.88f, 0.0f),
                      
                      glm::vec3(19.0f,-45.00f, 0.0f),
                      glm::vec3(6.0f,-45.00f, 0.0f),

                     

                     };

glm::vec4 lower_arm_positions[]={glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[3],1.0f), //front 

                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[7],1.0f), //back


                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[2],1.0f), // side

                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[6],1.0f), //side 

                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[1],1.0f),//top

                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[3],1.0f),//bottom


                         //circles
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[9],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[8],1.0f),
                         glm::vec4(vertices[10],1.0f),
                         glm::vec4(vertices[11],1.0f),

                          //add 4 and reverse----------------------------------
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[13],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         glm::vec4(vertices[15],1.0f),
                         glm::vec4(vertices[14],1.0f),
                         glm::vec4(vertices[12],1.0f),
                         //--------------------------------------------------------


                         };

int len = sizeof(lower_arm_positions)/16;
copy_col_norm(len, normals, colors, positions, lower_arm_positions, glm::vec4(1.0f, 0.1f, 0.1f, 1.0f));
}

//hand guard
const glm::mat4 hand_guard_transform = glm::translate(glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)), glm::vec3(-30.0f, -15.0f, -28.7f));
const int hand_guard_size = 84;
void hand_guard(glm::vec4 positions[hand_guard_size], glm::vec3 normals[hand_guard_size], glm::vec4 colors[hand_guard_size])
{
glm::vec3 vertices[]={glm::vec3(33.4f, -36.06f, 27.0f),
                      glm::vec3(33.4f, -36.06f, 0.0f),
                      glm::vec3(0.0f, -36.0f, 0.0f),
                      glm::vec3(-0.0f, -36.5f, 27.0f),

                      glm::vec3(33.4f, -0.0f, 0.0f),
                      glm::vec3(33.4f, -0.0f, 27.0f),
                      glm::vec3(0.0f, -0.1f, 27.0f),
                      glm::vec3(0.0f, -0.1f, 0.0f),

                     };

glm::vec4 hand_guard_positions[]={glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[3],1.0f), //front 

                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[7],1.0f), //back


                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[1],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[2],1.0f), // side

                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[3],1.0f),
                         glm::vec4(vertices[6],1.0f), //side 

                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[5],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[0],1.0f),
                         glm::vec4(vertices[4],1.0f),
                         glm::vec4(vertices[1],1.0f),//top

                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[7],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[2],1.0f),
                         glm::vec4(vertices[6],1.0f),
                         glm::vec4(vertices[3],1.0f),//bottom

                         };

int len = sizeof(hand_guard_positions)/16;
copy_col_norm(len, normals, colors, positions, hand_guard_positions, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
}

//head
const glm::mat4 head_transform = glm::translate(glm::mat4(1.0f), glm::vec3(50.0f, 4.8f, 2.1f));
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
copy_col_norm(len, normals, colors, positions, head_positions,  glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
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

void init_wing_torso(GLuint vao, GLuint vbo, GLuint vPosition, GLuint vColor, GLuint vNormal){
  glm::vec4 v_positions[wing_torso_size];       
  glm::vec4 v_colors[wing_torso_size];
  glm::vec3 v_normals[wing_torso_size];

  wing_torso(v_positions, v_normals, v_colors);

  initComponentBuffer(vao, vbo, vPosition, vColor, vNormal, v_positions, v_colors, v_normals, wing_torso_size);
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


void init_wrist(GLuint vao, GLuint vbo, GLuint vPosition, GLuint vColor, GLuint vNormal){
  glm::vec4 v_positions[wrist_size];       
  glm::vec4 v_colors[wrist_size];
  glm::vec3 v_normals[wrist_size];

  wrist(v_positions, v_normals, v_colors);

  initComponentBuffer(vao, vbo, vPosition, vColor, vNormal, v_positions, v_colors, v_normals, wrist_size);
}

void init_lower_torso(GLuint vao, GLuint vbo, GLuint vPosition, GLuint vColor, GLuint vNormal){
  glm::vec4 v_positions[lower_torso_size];       
  glm::vec4 v_colors[lower_torso_size];
  glm::vec3 v_normals[lower_torso_size];

  lower_torso(v_positions, v_normals, v_colors);

  initComponentBuffer(vao, vbo, vPosition, vColor, vNormal, v_positions, v_colors, v_normals, lower_torso_size);
}


//************************************************************************************************************************************
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
//************************************************************************************************************************************

int sizes[buff_size];
void init_optimus_prime(GLuint vao[], GLuint vbo[], GLuint vPosition, GLuint vColor, GLuint vNormal){
  init_torso(vao[0], vbo[0], vPosition, vColor, vNormal);
  sizes[0] = torso_size;
  init_head(vao[1], vbo[1], vPosition, vColor, vNormal);
  sizes[1] = head_size;
  init_ship_torso(vao[2], vbo[2], vPosition, vColor, vNormal);
  sizes[2] = ship_torso_size;
  init_wing_torso(vao[3], vbo[3], vPosition, vColor, vNormal);
  sizes[3] = wing_torso_size;
  init_foot(vao[4], vbo[4], vPosition, vColor, vNormal);
  sizes[4] = foot_size;
  init_lower_leg(vao[5], vbo[5], vPosition, vColor, vNormal);
  sizes[5] = lower_leg_size;
  init_joint(vao[6], vbo[6], vPosition, vColor, vNormal);
  sizes[6] = joint_size;
  init_hand_guard(vao[7], vbo[7], vPosition, vColor, vNormal);
  sizes[7] = hand_guard_size;
  init_upper_arm(vao[8], vbo[8], vPosition, vColor, vNormal);
  sizes[8] = upper_arm_size;
  init_lower_arm(vao[9], vbo[9], vPosition, vColor, vNormal);
  sizes[9] = lower_arm_size;
  init_wrist(vao[10], vbo[10], vPosition, vColor, vNormal);
  sizes[10] = wrist_size;
  init_lower_torso(vao[11], vbo[11], vPosition, vColor, vNormal);
  sizes[11] = lower_torso_size;
}

//************************************************************************************************************************************
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
//************************************************************************************************************************************

//--------------------------------------------RIGHT-SIDE------------------------------------------------------------------------------

void draw_right_hand_guard(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*hand_guard_transform* glm::rotate(glm::rotate(glm::rotate(glm::mat4(1.0f), glm::radians(op_right_hand_x), glm::vec3(1.0f, 0.0f, 0.0f)), glm::radians(op_right_hand_y), glm::vec3(0.0f, 1.0f, 0.0f)), glm::radians(op_right_hand_z), glm::vec3(0.0f, 0.0f, 1.0f));
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[7]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[7]);

  // draw_right_lower_arm(vao, vbo, modelview_matrix);
}

void draw_right_wrist_joint(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*wrist_joint_transform*glm::translate(glm::mat4(1.0f), glm::vec3(op_wrist_translate, op_wrist_translate, 0.0f))* glm::rotate(glm::rotate(glm::rotate(glm::mat4(1.0f), glm::radians(op_right_wrist_x), glm::vec3(1.0f, 0.0f, 0.0f)), glm::radians(op_right_wrist_y), glm::vec3(0.0f, 1.0f, 0.0f)), glm::radians(op_right_wrist_z), glm::vec3(0.0f, 0.0f, 1.0f));
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[10]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[10]);

  draw_right_hand_guard(vao, vbo, modelview_matrix);
}


const  glm::mat4 translate_arm_rot_r= glm::translate(glm::mat4(1.0f), glm::vec3(-12.0f, 0.0f, -15.0f));
const  glm::mat4 translate_arm_rot_reverse_r= glm::translate(glm::mat4(1.0f), glm::vec3(12.0f, 0.0f, 15.0f));

void draw_right_lower_arm(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*lower_arm_transform*translate_arm_rot_reverse_r*glm::rotate(glm::mat4(1.0f), glm::radians(op_right_elbow_x), glm::vec3(0.0f, 1.0f, 0.0f))*translate_arm_rot_r;
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[9]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[9]);

  draw_right_wrist_joint(vao, vbo, modelview_matrix);
}


const glm::mat4 uar_transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -75.0f));
void draw_right_upper_arm(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*upper_arm_transform*uar_transform* glm::rotate(glm::rotate(glm::rotate(glm::mat4(1.0f), glm::radians(op_right_upperarm_x), glm::vec3(1.0f, 0.0f, 0.0f)), glm::radians(op_right_upperarm_y), glm::vec3(0.0f, 1.0f, 0.0f)), glm::radians(op_right_upperarm_z), glm::vec3(0.0f, 0.0f, 1.0f));
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[8]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[8]);

  // draw_right_elbow_joint(vao, vbo, modelview_matrix);
  draw_right_lower_arm(vao, vbo, modelview_matrix);
}

const  glm::mat4 translate_foot_rot_r= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.0f, 0.0f));
const  glm::mat4 translate_foot_rot_reverse_r= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 2.0f, 0.0f));

const  glm::mat4 scale_foot = glm::scale(glm::mat4(1.0f), glm::vec3(20.0f, 20.0f, 20.05f));
void draw_right_foot(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*foot_transform*scale_foot*translate_foot_rot_reverse_r* glm::rotate(glm::rotate(glm::rotate(glm::mat4(1.0f), glm::radians(op_right_foot_x), glm::vec3(1.0f, 0.0f, 0.0f)), glm::radians(op_right_foot_y), glm::vec3(0.0f, 1.0f, 0.0f)), glm::radians(op_right_foot_z), glm::vec3(0.0f, 0.0f, 1.0f))*translate_foot_rot_r;
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[4]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[4]);
}

void draw_right_lower_leg(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*lower_leg_transform*  glm::rotate(glm::mat4(1.0f), glm::radians(op_right_knee_x), glm::vec3(1.0f, 0.0f, 0.0f));
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[5]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[5]);

  draw_right_foot(vao, vbo, modelview_matrix);
}


void draw_right_hip_joint(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*hip_joint_transform* glm::rotate(glm::rotate(glm::rotate(glm::mat4(1.0f), glm::radians(op_right_hip_x), glm::vec3(1.0f, 0.0f, 0.0f)), glm::radians(op_right_hip_y), glm::vec3(0.0f, 1.0f, 0.0f)), glm::radians(op_right_hip_z), glm::vec3(0.0f, 0.0f, 1.0f));
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[6]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[6]);

  draw_right_lower_leg(vao, vbo, modelview_matrix);
}

const  glm::mat4 translate_wing_rot_r= glm::translate(glm::mat4(1.0f), glm::vec3(-85.0f, 0.0f, -21.0f));
const  glm::mat4 translate_wing_rot_reverse_r= glm::translate(glm::mat4(1.0f), glm::vec3( 85.0f, 0.0f, 21.0f));

const  glm::mat4 translate_right_wing= glm::translate(glm::mat4(1.0f), glm::vec3(71.0f, 5.0f, 8.0f));
void draw_right_wing_torso(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*wing_torso_transform* translate_wing_rot_reverse_r*glm::translate(glm::rotate(glm::rotate(glm::rotate(glm::mat4(1.0f), glm::radians(op_right_shoulder_x), glm::vec3(1.0f, 0.0f, 0.0f)), glm::radians(op_right_shoulder_y), glm::vec3(0.0f, 1.0f, 0.0f)), glm::radians(op_right_shoulder_z), glm::vec3(0.0f, 0.0f, 1.0f)),glm::vec3(0.0f, op_shoulder_translate, 0.0f)  )*translate_wing_rot_r;
  glm::mat4 modelview_matrix_local = modelview_matrix*translate_right_wing ;
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix_local));
  normal_matrix = glm::mat3(modelview_matrix_local);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix_local));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[3]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[3]);

  draw_right_upper_arm(vao, vbo, modelview_matrix);
}

// //---------------------------------------------LEFT-SIDE------------------------------------------------------------------------------

const glm::mat4 left = glm::scale(glm::mat4(1.0f), glm::vec3(-1.0f, 1.0f, 1.0f));


void draw_left_hand_guard(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*hand_guard_transform*  glm::rotate(glm::rotate(glm::rotate(glm::mat4(1.0f), glm::radians(op_left_hand_x), glm::vec3(1.0f, 0.0f, 0.0f)), glm::radians(op_left_hand_y), glm::vec3(0.0f, 1.0f, 0.0f)), glm::radians(op_left_hand_z), glm::vec3(0.0f, 0.0f, 1.0f));
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[7]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[7]);

  // draw_right_lower_arm(vao, vbo, modelview_matrix);
}


void draw_left_wrist_joint(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*wrist_joint_transform*glm::translate(glm::mat4(1.0f), glm::vec3(op_wrist_translate, op_wrist_translate, 0.0f))* glm::rotate(glm::rotate(glm::rotate(glm::mat4(1.0f), glm::radians(op_left_wrist_x), glm::vec3(1.0f, 0.0f, 0.0f)), glm::radians(op_left_wrist_y), glm::vec3(0.0f, 1.0f, 0.0f)), glm::radians(op_left_wrist_z), glm::vec3(0.0f, 0.0f, 1.0f));
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[10]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[10]);

  draw_left_hand_guard(vao, vbo, modelview_matrix);
}

const  glm::mat4 translate_arm_rot_l= glm::translate(glm::mat4(1.0f), glm::vec3(-12.0f, 0.0f, -15.0f));
const  glm::mat4 translate_arm_rot_reverse_l= glm::translate(glm::mat4(1.0f), glm::vec3(12.0f, 0.0f, 15.0f));

void draw_left_lower_arm(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*lower_arm_transform*translate_arm_rot_reverse_l*glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, .0f) ), glm::radians(op_left_elbow_x), glm::vec3(0.0f, 1.0f, 0.0f))*translate_arm_rot_l;
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[9]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[9]);

  draw_left_wrist_joint(vao, vbo, modelview_matrix);
}


const glm::mat4 ual_transform = glm::translate(glm::mat4(1.0f), glm::vec3(-0.0f, 0.0f, 25.5f));
void draw_left_upper_arm(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*upper_arm_transform*ual_transform*  glm::rotate(glm::rotate(glm::rotate(glm::mat4(1.0f), glm::radians(op_left_upperarm_x), glm::vec3(1.0f, 0.0f, 0.0f)), glm::radians(op_left_upperarm_y), glm::vec3(0.0f, 1.0f, 0.0f)), glm::radians(op_left_upperarm_z), glm::vec3(0.0f, 0.0f, 1.0f));
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[8]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[8]);

  draw_left_lower_arm(vao, vbo, modelview_matrix);

  // draw_left_elbow_joint(vao, vbo, modelview_matrix);
}

const  glm::mat4 translate_foot_rot_l= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.0f, 0.0f));
const  glm::mat4 translate_foot_rot_reverse_l= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 2.0f, 0.0f));

void draw_left_foot(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*foot_transform*scale_foot*translate_foot_rot_reverse_l* glm::rotate(glm::rotate(glm::rotate(glm::mat4(1.0f), glm::radians(op_left_foot_x), glm::vec3(1.0f, 0.0f, 0.0f)), glm::radians(op_left_foot_y), glm::vec3(0.0f, 1.0f, 0.0f)), glm::radians(op_left_foot_z), glm::vec3(0.0f, 0.0f, 1.0f))*translate_foot_rot_l;
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[4]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[4]);
}

void draw_left_lower_leg(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*lower_leg_transform* glm::rotate(glm::mat4(1.0f), glm::radians(op_left_knee_x), glm::vec3(1.0f, 0.0f, 0.0f));
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[5]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[5]);

  draw_left_foot(vao, vbo, modelview_matrix);
}


void draw_left_hip_joint(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*left*hip_joint_transform*glm::rotate(glm::rotate(glm::rotate(glm::mat4(1.0f), glm::radians(op_left_hip_x), glm::vec3(1.0f, 0.0f, 0.0f)), glm::radians(op_left_hip_y), glm::vec3(0.0f, 1.0f, 0.0f)), glm::radians(op_left_hip_z), glm::vec3(0.0f, 0.0f, 1.0f));
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[6]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[6]);

  draw_left_lower_leg(vao, vbo, modelview_matrix);
}

const  glm::mat4 translate_left_wing= glm::translate(glm::mat4(1.0f), glm::vec3(-30.0f, 5.0f, 8.0f));

const  glm::mat4 translate_wing_rot_l= glm::translate(glm::mat4(1.0f), glm::vec3(15.0f, 0.0f, -20.0f));
const  glm::mat4 translate_wing_rot_reverse_l= glm::translate(glm::mat4(1.0f), glm::vec3(-15.0f, 0.0f, 20.0f));


void draw_left_wing_torso(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  glm::mat4 temp = modelview_matrix;
  modelview_matrix = modelview_matrix*left*wing_torso_transform*translate_wing_rot_reverse_l*glm::translate(glm::rotate(glm::rotate(glm::rotate(glm::mat4(1.0f), glm::radians(op_left_shoulder_x), glm::vec3(1.0f, 0.0f, 0.0f)), glm::radians(op_left_shoulder_y), glm::vec3(0.0f, 1.0f, 0.0f)), glm::radians(op_left_shoulder_z), glm::vec3(0.0f, 0.0f, 1.0f)),glm::vec3(0.0f, op_shoulder_translate, 0.0f)  )*translate_wing_rot_l;
  // glm::mat4 modelview_matrix_local = modelview_matrix*translate_left_wing ;
  glm::mat4 modelview_matrix_local = temp * left* wing_torso_transform*translate_wing_rot_reverse_l*glm::translate(glm::rotate(glm::rotate(glm::rotate(glm::mat4(1.0f), glm::radians(op_left_shoulder_x), glm::vec3(1.0f, 0.0f, 0.0f)), glm::radians(op_left_shoulder_y), glm::vec3(0.0f, 1.0f, 0.0f)), glm::radians(op_left_shoulder_z), glm::vec3(0.0f, 0.0f, 1.0f)),glm::vec3(0.0f, op_shoulder_translate, 0.0f)  )*translate_wing_rot_l*translate_left_wing;  
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix_local));
  normal_matrix = glm::mat3(modelview_matrix_local);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix_local));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[3]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[3]);

  draw_left_upper_arm(vao, vbo, modelview_matrix);
}

// //---------------------------------------------UNIVERSAL------------------------------------------------------------------------------


void draw_ship_torso(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*ship_torso_transform*  glm::rotate(glm::rotate(glm::rotate(glm::translate (glm::mat4(1.0f),glm::vec3(0.0f,  op_ship_translate, 0.0f)  ), glm::radians(op_ship_rotate_x), glm::vec3(-1.0f, 0.0f, 0.0f)),  glm::radians(op_ship_rotate_y), glm::vec3(0.0f, 1.0f, 0.0f) ), glm::radians(op_ship_rotate_z), glm::vec3(0.0f, 0.0f, 1.0f));
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[2]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[2]);

  draw_right_hip_joint(vao, vbo, modelview_matrix);
  draw_left_hip_joint(vao, vbo, modelview_matrix);

  // draw_ship(vao, vbo, modelview_matrix);
}

const  glm::mat4 scale_head = glm::scale(glm::mat4(1.0f), glm::vec3(20.0f, 20.0f, 20.05f));
void draw_head(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix){
  modelview_matrix = modelview_matrix*head_transform*scale_head*glm::rotate(glm::rotate(glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, op_head_translate, 0.0f)), glm::radians(op_head_x), glm::vec3(1.0f, 0.0f, 0.0f)), glm::radians(op_head_y), glm::vec3(0.0f, 1.0f, 0.0f)), glm::radians(op_head_z), glm::vec3(0.0f, 0.0f, 1.0f)) ;
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[1]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[1]);
}

const  glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.05f, 0.05f, 0.05f));
const  glm::mat4 translate_torso= glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(68.0f, -61.0f, 50.0f)) , glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
const  glm::mat4 translate_torso_rot= glm::translate(glm::mat4(1.0f), glm::vec3(-18.0f, 0.0f, -23.0f));
const  glm::mat4 translate_torso_rot_reverse= glm::translate(glm::mat4(1.0f), glm::vec3(18.0f, 0.0f, 23.0f));
const  glm::mat4 translate_torso_rot_un= glm::translate(glm::mat4(1.0f), glm::vec3(-50.0f, 0.0f, -30.0f));
const  glm::mat4 translate_torso_rot_reverse_un= glm::translate(glm::mat4(1.0f), glm::vec3(50.0f, 0.0f, 30.0f));
void draw_lower_torso(GLuint vao[], GLuint vbo[], glm::mat4 modelview_matrix1){
  glm::mat4 modelview_matrix = modelview_matrix1*translate_torso_rot_reverse_un*glm::rotate(glm::rotate( glm::rotate(glm::mat4(1.0f), glm::radians(op_lower_torso_rotate_y), glm::vec3(0.0f, 1.0f, 0.0f)),  glm::radians(op_lower_torso_rotate_x), glm::vec3(1.0f, 0.0f, 0.0f)),  glm::radians(op_lower_torso_rotate_z), glm::vec3(0.0f, 0.0f, 1.0f))*translate_torso_rot_un;
  glm::mat4 modelview_matrix_local = modelview_matrix1*translate_torso* translate_torso_rot_reverse*glm::rotate(glm::rotate( glm::rotate(glm::mat4(1.0f), glm::radians(op_lower_torso_rotate_y), glm::vec3(0.0f, 1.0f, 0.0f)),  glm::radians(op_lower_torso_rotate_x), glm::vec3(1.0f, 0.0f, 0.0f)),  glm::radians(op_lower_torso_rotate_z), glm::vec3(0.0f, 0.0f, 1.0f))*translate_torso_rot;
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix_local));
  normal_matrix = glm::mat3(modelview_matrix_local);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix_local));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[11]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[11]);

  draw_ship_torso(vao, vbo, modelview_matrix);
}

const glm::mat4 torso_cent = glm::translate(glm::mat4(1.0f), glm::vec3(-50.5f, 60.0f, 0.0f));

void draw_upper_torso(GLuint vao[], GLuint vbo[]){
  glm::mat4 modelview_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(op_xpos, op_ypos, op_zpos)) * scalingMatrix*model_matrix * glm::rotate(glm::rotate(glm::rotate(glm::mat4(1.0f), glm::radians(op_torso_x), glm::vec3(1.0f, 0.0f, 0.0f)), glm::radians(op_torso_y), glm::vec3(0.0f, 1.0f, 0.0f)), glm::radians(op_torso_z), glm::vec3(0.0f, 0.0f, 1.0f)) * torso_cent;
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix*modelview_matrix));
  normal_matrix = glm::mat3(modelview_matrix);
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glBindVertexArray (vao[0]);
  glDrawArrays(GL_TRIANGLES, 0, sizes[0]);

  draw_right_wing_torso(vao, vbo, modelview_matrix);
  draw_left_wing_torso(vao, vbo, modelview_matrix);
  draw_head(vao, vbo, modelview_matrix);
  draw_lower_torso(vao, vbo, modelview_matrix);
}

//************************************************************************************************************************************
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
//************************************************************************************************************************************

void op_transform(void){
  float a = 2*op_count*op_form + transform_frames - transform_frames*op_form - op_count;
  float b = transform_frames*op_form + op_count - 2*op_count*op_form;
  a /= transform_frames;
  b /= transform_frames;
  op_count++;

  op_lower_torso_rotate_x = a*rop_lower_torso_rotate_x + b*sop_lower_torso_rotate_x;
  op_lower_torso_rotate_y = a*rop_lower_torso_rotate_y + b*sop_lower_torso_rotate_y;
  op_lower_torso_rotate_z = a*rop_lower_torso_rotate_z + b*sop_lower_torso_rotate_z;

  op_ship_rotate_x = a*rop_ship_rotate_x + b*sop_ship_rotate_x;
  op_ship_rotate_y = a*rop_ship_rotate_y + b*sop_ship_rotate_y;
  op_ship_rotate_z = a*rop_ship_rotate_z + b*sop_ship_rotate_z;

  op_ship_translate = a*rop_ship_translate + b*sop_ship_translate;

  op_head_x = a*rop_head_x + b*sop_head_x;
  op_head_y = a*rop_head_y + b*sop_head_y;
  op_head_z = a*rop_head_z + b*sop_head_z;
  op_head_translate = a*rop_head_translate + b*sop_head_translate;

  // op_wing = a*rop_wing + b*sop_wing;
  // op_wing_torso = a*rop_wing_torso + b*sop_wing_torso;

  // op_shoulder_pad = a*rop_shoulder_pad + b*sop_shoulder_pad;
  op_shoulder_translate = a*rop_shoulder_translate + b*sop_shoulder_translate;
  op_wrist_translate = a*rop_wrist_translate + b*sop_wrist_translate;

  op_torso_x = a*rop_torso_x + b*sop_torso_x;
  op_torso_y = a*rop_torso_y + b*sop_torso_y;

  // op_hand_guard = a*rop_hand_guard + b*sop_hand_guard;

  //-------------------------------------Left-----------------------------------------------
  op_left_shoulder_x = a*rop_left_shoulder_x + b*sop_left_shoulder_x;
  op_left_shoulder_y = a*rop_left_shoulder_y + b*sop_left_shoulder_y;
  op_left_shoulder_z = a*rop_left_shoulder_z + b*sop_left_shoulder_z;

  op_left_wrist_x = a*rop_left_wrist_x + b*sop_left_wrist_x;
  op_left_wrist_y = a*rop_left_wrist_y + b*sop_left_wrist_y;
  op_left_wrist_z = a*rop_left_wrist_z + b*sop_left_wrist_z;

  op_left_elbow_x = a*rop_left_elbow_x + b*sop_left_elbow_x;
  op_left_elbow_y = a*rop_left_elbow_y + b*sop_left_elbow_y;

  op_left_foot_x = a*rop_left_foot_x + b*sop_left_foot_x;
  op_left_foot_y = a*rop_left_foot_y + b*sop_left_foot_y;
  op_left_foot_z = a*rop_left_foot_z + b*sop_left_foot_z;

  op_left_upperarm_x = a*rop_left_upperarm_x + b*sop_left_upperarm_x;
  op_left_upperarm_y = a*rop_left_upperarm_y + b*sop_left_upperarm_y;
  op_left_upperarm_z = a*rop_left_upperarm_z + b*sop_left_upperarm_z;

  op_left_hand_x = a*rop_left_hand_x + b*sop_left_hand_x;
  op_left_hand_y = a*rop_left_hand_y + b*sop_left_hand_y;
  op_left_hand_z = a*rop_left_hand_z + b*sop_left_hand_z;


  op_left_knee_x = a*rop_left_knee_x + b*sop_left_knee_x;
  op_left_knee_y = a*rop_left_knee_y + b*sop_left_knee_y;

  op_left_hip_x = a*rop_left_hip_x + b*sop_left_hip_x;
  op_left_hip_y = a*rop_left_hip_y + b*sop_left_hip_y;
  op_left_hip_z = a*rop_left_hip_z + b*sop_left_hip_z;

  //-------------------------------------Right----------------------------------------------
  op_right_shoulder_x = a*rop_right_shoulder_x + b*sop_right_shoulder_x;
  op_right_shoulder_y = a*rop_right_shoulder_y + b*sop_right_shoulder_y;
  op_right_shoulder_z = a*rop_right_shoulder_z + b*sop_right_shoulder_z;

  op_right_wrist_x = a*rop_right_wrist_x + b*sop_right_wrist_x;
  op_right_wrist_y = a*rop_right_wrist_y + b*sop_right_wrist_y;
  op_right_wrist_z = a*rop_right_wrist_z + b*sop_right_wrist_z;


  op_right_elbow_x = a*rop_right_elbow_x + b*sop_right_elbow_x;
  op_right_elbow_y = a*rop_right_elbow_y + b*sop_right_elbow_y;

  op_right_foot_x = a*rop_right_foot_x + b*sop_right_foot_x;
  op_right_foot_y = a*rop_right_foot_y + b*sop_right_foot_y;
  op_right_foot_z = a*rop_right_foot_z + b*sop_right_foot_z;

  op_right_upperarm_x = a*rop_right_upperarm_x + b*sop_right_upperarm_x;
  op_right_upperarm_y = a*rop_right_upperarm_y + b*sop_right_upperarm_y;
  op_right_upperarm_z = a*rop_right_upperarm_z + b*sop_right_upperarm_z;

  op_right_hand_x = a*rop_right_hand_x + b*sop_right_hand_x;
  op_right_hand_y = a*rop_right_hand_y + b*sop_right_hand_y;
  op_right_hand_z = a*rop_right_hand_z + b*sop_right_hand_z;

  op_right_knee_x = a*rop_right_knee_x + b*sop_right_knee_x;
  op_right_knee_y = a*rop_right_knee_y + b*sop_right_knee_y;

  op_right_hip_x = a*rop_right_hip_x + b*sop_right_hip_x;
  op_right_hip_y = a*rop_right_hip_y + b*sop_right_hip_y;
  op_right_hip_z = a*rop_right_hip_z + b*sop_right_hip_z;

  if(op_count > transform_frames){
    op_count = 0;
    op_transformation = 0;
    op_form = 1 - op_form;
  }
}

void update_lights_camera(){
  op_light1_pos = glm::vec3(glm::translate(glm::mat4(1.0f), glm::vec3(op_xpos, op_ypos, op_zpos)) * model_matrix * glm::rotate(glm::rotate(glm::rotate(glm::mat4(1.0f), glm::radians(op_torso_x), glm::vec3(1.0f, 0.0f, 0.0f)), glm::radians(op_torso_y), glm::vec3(0.0f, 1.0f, 0.0f)), glm::radians(op_torso_z), glm::vec3(0.0f, 0.0f, 1.0f)) * light1_pos);
  op_light2_pos = glm::vec3(glm::translate(glm::mat4(1.0f), glm::vec3(op_xpos, op_ypos, op_zpos)) * model_matrix * glm::rotate(glm::rotate(glm::rotate(glm::mat4(1.0f), glm::radians(op_torso_x), glm::vec3(1.0f, 0.0f, 0.0f)), glm::radians(op_torso_y), glm::vec3(0.0f, 1.0f, 0.0f)), glm::radians(op_torso_z), glm::vec3(0.0f, 0.0f, 1.0f)) * light2_pos);
  op_light_dir = glm::vec3(model_matrix * glm::rotate(glm::rotate(glm::rotate(glm::mat4(1.0f), glm::radians(op_torso_x), glm::vec3(1.0f, 0.0f, 0.0f)), glm::radians(op_torso_y), glm::vec3(0.0f, 1.0f, 0.0f)), glm::radians(op_torso_z), glm::vec3(0.0f, 0.0f, 1.0f)) * light_dir);

  glm::mat4 model_mat = glm::translate(glm::mat4(1.0f), glm::vec3(op_xpos, op_ypos, op_zpos)) * model_matrix * glm::rotate(glm::rotate(glm::rotate(glm::mat4(1.0f), glm::radians(op_torso_x), glm::vec3(1.0f, 0.0f, 0.0f)), glm::radians(op_torso_y), glm::vec3(0.0f, 1.0f, 0.0f)), glm::radians(op_torso_z), glm::vec3(0.0f, 0.0f, 1.0f));
  op_cent = glm::vec3(model_mat * cent);
  op_eye = glm::vec3(model_mat * eye);
  op_up = glm::vec3(model_matrix * glm::rotate(glm::rotate(glm::rotate(glm::mat4(1.0f), glm::radians(op_torso_x), glm::vec3(1.0f, 0.0f, 0.0f)), glm::radians(op_torso_y), glm::vec3(0.0f, 1.0f, 0.0f)), glm::radians(op_torso_z), glm::vec3(0.0f, 0.0f, 1.0f)) * up);
}

void draw_optimus_prime(GLuint vao[], GLuint vbo[]){
  if(op_transformation==1)
    op_transform();

  draw_upper_torso(vao, vbo);
 
}

}