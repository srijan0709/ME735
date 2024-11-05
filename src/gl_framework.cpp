#include "gl_framework.hpp"
#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <vector>

#define camera_params 0b11
#define light_params ~0b11

extern GLfloat xrot, yrot, c_xrot, c_yrot, c_zrot, c_xpos, c_ypos, c_zpos;
extern GLint width, height;
extern GLfloat scale;
extern GLint transformer;
extern uint lights_cam;

//Vector Prime
extern GLfloat vp_ship_rotate, vp_head_translate, vp_head_x, vp_head_y, vp_head_z, vp_right_wing_wing_torso, vp_right_wing_torso_torso, vp_left_wing_wing_torso, vp_left_wing_torso_torso, vp_right_wing, vp_left_wing;
extern GLfloat vp_left_shoulder_translate, vp_right_shoulder_translate, vp_right_shoulder_x, vp_right_shoulder_y, vp_right_shoulder_z, vp_left_shoulder_x, vp_left_shoulder_y, vp_left_shoulder_z;
extern GLfloat vp_right_elbow_x, vp_left_elbow_x, vp_right_elbow_y, vp_left_elbow_y, vp_right_shoulder_pad, vp_left_shoulder_pad;
extern GLfloat vp_right_foot_x, vp_right_foot_y, vp_right_foot_z, vp_left_foot_x, vp_left_foot_y, vp_left_foot_z;
extern GLfloat vp_right_knee_x, vp_left_knee_x, vp_right_knee_y, vp_left_knee_y;
extern GLfloat vp_right_hip_x, vp_right_hip_y, vp_right_hip_z, vp_left_hip_x, vp_left_hip_y, vp_left_hip_z;
extern GLfloat vp_right_hand_guard, vp_left_hand_guard;
extern GLint vp_transformation;
extern GLfloat vp_right_hand_x, vp_right_hand_y, vp_right_hand_z, vp_left_hand_x, vp_left_hand_y, vp_left_hand_z;
extern GLfloat vp_torso_x, vp_torso_y, vp_torso_z;
extern GLfloat vp_xpos, vp_ypos, vp_zpos;

//Optimus Prime
extern GLfloat op_lower_torso_rotate_x  , op_lower_torso_rotate_y, op_lower_torso_rotate_z ; //add
extern GLfloat op_right_upperarm_x, op_right_upperarm_y, op_right_upperarm_z, op_left_upperarm_x, op_left_upperarm_y, op_left_upperarm_z;
extern GLfloat op_head_translate, op_head_x, op_head_y, op_head_z, op_right_wing_wing_torso, op_right_wing_torso_torso, op_left_wing_wing_torso, op_left_wing_torso_torso, op_right_wing, op_left_wing;
extern GLfloat op_shoulder_translate, op_right_shoulder_x, op_right_shoulder_y, op_right_shoulder_z, op_left_shoulder_x, op_left_shoulder_y, op_left_shoulder_z;
extern GLfloat op_right_elbow_x, op_left_elbow_x, op_right_elbow_y, op_left_elbow_y, op_right_shoulder_pad, op_left_shoulder_pad;
extern GLfloat op_right_foot_x, op_right_foot_y, op_right_foot_z, op_left_foot_x, op_left_foot_y, op_left_foot_z;
extern GLfloat op_right_knee_x, op_left_knee_x, op_right_knee_y, op_left_knee_y;
extern GLfloat op_right_hip_x, op_right_hip_y, op_right_hip_z, op_left_hip_x, op_left_hip_y, op_left_hip_z;
extern GLint op_transformation;
extern GLfloat op_ship_rotate_x , op_ship_rotate_y  , op_ship_rotate_z, op_ship_translate;
extern GLfloat op_right_hand_x, op_right_hand_y, op_right_hand_z, op_left_hand_x, op_left_hand_y, op_left_hand_z;
extern GLfloat op_wrist_translate,op_right_wrist_x, op_right_wrist_y, op_right_wrist_z, op_left_wrist_x, op_left_wrist_y, op_left_wrist_z;
extern GLfloat op_torso_x, op_torso_y, op_torso_z;
extern GLfloat op_xpos, op_ypos, op_zpos;

GLint lur; //left/right/universal
GLint hierarchy=0; //hierarchy of control
GLint part;
GLfloat time_elapsed = glfwGetTime();
GLint camera_light_control = 0;

extern int keyframe_status;

namespace csX75
{
  //! Initialize GL State
  void initGL(void)
  {
    //Set framebuffer clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //Set depth buffer furthest depth
    glClearDepth(1.0);
    //Set depth test to less-than
    glDepthFunc(GL_LESS);
    //Enable depth testing
    glEnable(GL_DEPTH_TEST);
  }
  
  //!GLFW Error Callback
  void error_callback(int error, const char* description)
  {
    std::cerr<<description<<std::endl;
  }
  
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width_n, int height_n)
  {
    //!Resize the viewport to fit the window size - draw to entire window
    glViewport(0, 0, width_n, height_n);
    width = width_n;
    height = height_n;
  }
  
  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    //!Close the window if the ESC key was pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);
    else if (key == GLFW_KEY_K && glfwGetTime()-time_elapsed > 0.2f && hierarchy == 0){
      if(keyframe_status > 0){
        keyframe_status = 0;
        std::cout<<"Exited Keyframe Control"<<std::endl;
      }
      else{
        keyframe_status = 4;
        std::cout<<"Entered Keyframe Control"<<std::endl;
      }
      time_elapsed = glfwGetTime();
    }
    else if(keyframe_status > 0){
      if(key == GLFW_KEY_S && glfwGetTime()-time_elapsed > 0.2f){
        keyframe_status = 1;
        time_elapsed = glfwGetTime();
      }
      else if(key == GLFW_KEY_L && glfwGetTime()-time_elapsed > 0.2f){
        keyframe_status = 2;
        time_elapsed = glfwGetTime();
      }
      else if(key == GLFW_KEY_P && glfwGetTime()-time_elapsed > 0.2f){
        keyframe_status = 3;
        time_elapsed = glfwGetTime();
      }
      else if(key == GLFW_KEY_R && glfwGetTime()-time_elapsed > 0.2f){
        keyframe_status = 5;
        time_elapsed = glfwGetTime();
      }
    }
    else if (key == GLFW_KEY_A  )
      c_yrot -= 1.0;
    else if (key == GLFW_KEY_D  )
      c_yrot += 1.0;
    else if (key == GLFW_KEY_W  )
      c_xrot -= 1.0;
    else if (key == GLFW_KEY_S  )
      c_xrot += 1.0;   
    // else if(key == GLFW_KEY_M)
    //   scale*=1.01;
    // else if(key == GLFW_KEY_N)
    //   scale*=0.99;
    else if(key == GLFW_KEY_M && glfwGetTime()-time_elapsed > 0.2f){
      camera_light_control = 1 - camera_light_control;
      if(camera_light_control == 1)
        std::cout<<"Entered Camera and Lights Control"<<std::endl;
      else
        std::cout<<"Exited Camera and Lights Control"<<std::endl;
      time_elapsed = glfwGetTime();
    }
    else if(camera_light_control == 1){
      if (key == GLFW_KEY_1){
        lights_cam = (lights_cam & light_params) | 0b01;
      }
      else if (key == GLFW_KEY_2){
        lights_cam = (lights_cam & light_params) | 0b10;
      }
      else if (key == GLFW_KEY_3){
        lights_cam = (lights_cam & light_params) | 0b00;
      }
      else if(key == GLFW_KEY_4 && glfwGetTime()-time_elapsed > 0.2f){
        lights_cam = lights_cam ^ 0b000100;
      time_elapsed = glfwGetTime();
      }
      else if(key == GLFW_KEY_5 && glfwGetTime()-time_elapsed > 0.2f){
        lights_cam = lights_cam ^ 0b001000;
      time_elapsed = glfwGetTime();
      }
      else if(key == GLFW_KEY_6 && glfwGetTime()-time_elapsed > 0.2f){
        lights_cam = lights_cam ^ 0b01000000;
      time_elapsed = glfwGetTime();
      }
      else if(key == GLFW_KEY_7 && glfwGetTime()-time_elapsed > 0.2f){
        lights_cam = lights_cam ^ 0b10000000;
      time_elapsed = glfwGetTime();
      }
      else if(key == GLFW_KEY_8 && glfwGetTime()-time_elapsed > 0.2f){
        lights_cam = lights_cam ^ 0b010000;
      time_elapsed = glfwGetTime();
      }
      else if(key == GLFW_KEY_9 && glfwGetTime()-time_elapsed > 0.2f){
        lights_cam = lights_cam ^ 0b100000;
      time_elapsed = glfwGetTime();
      }
      else if(key == GLFW_KEY_Q)
        c_zrot -= 1.0;
      else if(key == GLFW_KEY_E)
        c_zrot += 1.0;
      else if (key == GLFW_KEY_KP_5)
        c_ypos -= 0.1;
      else if (key == GLFW_KEY_KP_8)
        c_ypos += 0.1;
      else if (key == GLFW_KEY_KP_4)
        c_xpos -= 0.1;
      else if (key == GLFW_KEY_KP_6)
        c_xpos += 0.1;
      else if (key == GLFW_KEY_KP_7)
        c_zpos -= 0.1;
      else if (key == GLFW_KEY_KP_9)
        c_zpos += 0.1;
    }
    else if (key == GLFW_KEY_C && glfwGetTime()-time_elapsed > 0.2f){
      transformer=1 - transformer;
      hierarchy = 0; 
      time_elapsed = glfwGetTime();
    }
    else if(glfwGetTime()-time_elapsed > 0.2f){
      if(transformer == 0){
        if (key == GLFW_KEY_LEFT )
          vp_torso_y -= 1.0;
        else if (key == GLFW_KEY_RIGHT )
          vp_torso_y += 1.0;
        else if (key == GLFW_KEY_UP )
          vp_torso_x -= 1.0;
        else if (key == GLFW_KEY_DOWN )
          vp_torso_x += 1.0;
        else if (key == GLFW_KEY_PAGE_UP || key == GLFW_KEY_KP_9)
          vp_torso_z -= 1.0;
        else if (key == GLFW_KEY_PAGE_DOWN || key == GLFW_KEY_KP_3)
          vp_torso_z += 1.0;
        else if (key == GLFW_KEY_KP_5)
          vp_ypos -= 0.1;
        else if (key == GLFW_KEY_KP_8)
          vp_ypos += 0.1;
        else if (key == GLFW_KEY_KP_4)
          vp_xpos -= 0.1;
        else if (key == GLFW_KEY_KP_6)
          vp_xpos += 0.1;
        else if (key == GLFW_KEY_KP_7)
          vp_zpos -= 0.1;
        else if (key == GLFW_KEY_KP_1)
          vp_zpos += 0.1;
        else if (key == GLFW_KEY_Q){
          if(hierarchy>0)
            std::cout<<"KEY BINDINGS:\nU - To get control of the Ship and Head\nL - To get control of the Left Half of the Transformer\nR - To get control of the Right Half of the Transformer"<<std::endl;
          hierarchy=0;
          time_elapsed = glfwGetTime();
        }

        else if (key == GLFW_KEY_T)
          vp_transformation=1; 

        else if(hierarchy <= 0){
          if(key == GLFW_KEY_U && glfwGetTime()-time_elapsed > 0.2f){
            hierarchy=1;
            lur = 0;
            time_elapsed = glfwGetTime();
            std::cout<<"KEY BINDINGS:\nY, G - To rotate the Ship Torso joint\nU, H - To rotate the Head along the x axis\nI, J - To rotate the Head along the y axis\nO, K - To rotate the Head along the z axis\nP, L - To translate the Head along the y axis"<<std::endl;
          }
          else if(key == GLFW_KEY_L && glfwGetTime()-time_elapsed > 0.2f){
            hierarchy=1;
            lur = -1;
            time_elapsed = glfwGetTime();
            std::cout<<"KEY BINDINGS:\nI - To get control of the Left Shoulder\nK - To get control of the Left Elbow, Hand Guard and Hand\nO - To get control of the Left Hip Joint\nL - To get control of the Left Knee and Ankle\nP - To get control of the Left Wings/Flaps/Cape"<<std::endl;
          }
          else if(key == GLFW_KEY_R && glfwGetTime()-time_elapsed > 0.2f){
            hierarchy=1;
            lur = 1;
            time_elapsed = glfwGetTime();
            std::cout<<"KEY BINDINGS:\nI - To get control of the Right Shoulder\nK - To get control of the Right Elbow, Hand Guard and Hand\nO - To get control of the Right Hip Joint\nL - To get control of the Right Knee and Ankle\nP - To get control of the Right Wings/Flaps/Cape"<<std::endl;
          }
        }
        else if(hierarchy == 1){
          if(lur == 0){
            if(key == GLFW_KEY_Y){
              vp_ship_rotate+=1.0f;
              if(vp_ship_rotate>90.0f)
                vp_ship_rotate=90.0f;
            }
            else if(key == GLFW_KEY_G){
              vp_ship_rotate-=1.0f;
              if(vp_ship_rotate<0.0f)
                vp_ship_rotate=0.0f;
            }
            else if(key == GLFW_KEY_U){
              vp_head_x+=1.0f;
              if(vp_head_x>45.0f)
                vp_head_x=45.0f;
            }
            else if(key == GLFW_KEY_H){
              vp_head_x-=1.0f;
              if(vp_head_x<-45.0f)
                vp_head_x=-45.0f;
            }
            else if(key == GLFW_KEY_I){
              vp_head_y+=1.0f;
              if(vp_head_y>180.0f)
                vp_head_y=180.0f;
            }
            else if(key == GLFW_KEY_J){
              vp_head_y-=1.0f;
              if(vp_head_y<-180.0f)
                vp_head_y=-180.0f;
            }
            else if(key == GLFW_KEY_O){
              vp_head_z+=1.0f;
              if(vp_head_z>45.0f)
                vp_head_z=45.0f;
            }
            else if(key == GLFW_KEY_K){
              vp_head_z-=1.0f;
              if(vp_head_z<-45.0f)
                vp_head_z=-45.0f;
            }
            else if(key == GLFW_KEY_P){
              vp_head_translate+=0.01f;
              if(vp_head_translate>0.5f)
                vp_head_translate=0.5f;
            }
            else if(key == GLFW_KEY_L){
              vp_head_translate-=0.01f;
              if(vp_head_translate<0.0f)
                vp_head_translate=0.0f;
            }
          }
          else if(lur == 1){
            if(key == GLFW_KEY_I){
              hierarchy = 2;
              part = 0;
              time_elapsed = glfwGetTime();
              std::cout<<"KEY BINDINGS:\nY, G - To rotate the Right Shoulder Pad\nU, H - To rotate the Right Shoulder along the x axis\nI, J - To rotate the Right Shoulder along the y axis\nO, K - To rotate the Right Shoulder along the z axis\nP, L - To translate the Right Shoulder along the x axis"<<std::endl;
            }
            else if(key == GLFW_KEY_K){
              hierarchy = 2;
              part = 1;
              time_elapsed = glfwGetTime();
              std::cout<<"KEY BINDINGS:\nY, G - To rotate the Right Elbow along the x axis\nU, H - To rotate the Right Elbow along the z axis\nI, J - To rotate the Right Hand along the x axis\nO, K - To rotate the Right Hand along the y axis\nP, L - To rotate the Right Hand along the z axis\nV, B - To translate the Right Hand Guard along the y axis"<<std::endl;
            }
            else if(key == GLFW_KEY_O){
              hierarchy = 2;
              part = 2;
              time_elapsed = glfwGetTime();
              std::cout<<"KEY BINDINGS:\nY, G - To rotate the Right Hip Joint along the x axis\nU, H - To rotate the Right Hip Joint along the y axis\nI, J - To translate the Right Hip Joint along the z axis"<<std::endl;
            }
            else if(key == GLFW_KEY_L){
              hierarchy = 2;
              part = 3;
              time_elapsed = glfwGetTime();
              std::cout<<"KEY BINDINGS:\nY, G - To rotate the Right Knee along the x axis\nU, H - To rotate the Right Knee along the y axis\nI, J - To rotate the Right Ankle along the x axis\nO, K - To rotate the Right Ankle along the y axis\nP, L - To rotate the Right Ankle along the z axis"<<std::endl;
            }
            else if(key == GLFW_KEY_P){
              hierarchy = 2;
              part = 4;
              time_elapsed = glfwGetTime();
              std::cout<<"KEY BINDINGS:\nY, G - To rotate the Right Torso Joint\nU, H - To rotate the Right Flaps Joint\nI, J - To open or close the Right Wings/Flaps/Cape"<<std::endl;
            }
          }
          else if(lur == -1){
            if(key == GLFW_KEY_I){
              hierarchy = 2;
              part = 0;
              time_elapsed = glfwGetTime();
              std::cout<<"KEY BINDINGS:\nY, G - To rotate the Left Shoulder Pad\nU, H - To rotate the Left Shoulder along the x axis\nI, J - To rotate the Left Shoulder along the y axis\nO, K - To rotate the Left Shoulder along the z axis\nP, L - To translate the Left Shoulder along the x axis"<<std::endl;
            }
            else if(key == GLFW_KEY_K){
              hierarchy = 2;
              part = 1;
              time_elapsed = glfwGetTime();
              std::cout<<"KEY BINDINGS:\nY, G - To rotate the Left Elbow along the x axis\nU, H - To rotate the Left Elbow along the z axis\nI, J - To rotate the Left Hand along the x axis\nO, K - To rotate the Left Hand along the y axis\nP, L - To rotate the Left Hand along the z axis\nV, B - To translate the Left Hand Guard along the y axis"<<std::endl;
            }
            else if(key == GLFW_KEY_O){
              hierarchy = 2;
              part = 2;
              time_elapsed = glfwGetTime();
              std::cout<<"KEY BINDINGS:\nY, G - To rotate the Left Hip Joint along the x axis\nU, H - To rotate the Left Hip Joint along the y axis\nI, J - To translate the Left Hip Joint along the z axis"<<std::endl;
            }
            else if(key == GLFW_KEY_L){
              hierarchy = 2;
              part = 3;
              time_elapsed = glfwGetTime();
              std::cout<<"KEY BINDINGS:\nY, G - To rotate the Left Knee along the x axis\nU, H - To rotate the Left Knee along the y axis\nI, J - To rotate the Left Ankle along the x axis\nO, K - To rotate the Left Ankle along the y axis\nP, L - To rotate the Left Ankle along the z axis"<<std::endl;
            }
            else if(key == GLFW_KEY_P){
              hierarchy = 2;
              part = 4;
              time_elapsed = glfwGetTime();
              std::cout<<"KEY BINDINGS:\nY, G - To rotate the Left Torso Joint\nU, H - To rotate the Left Flaps Joint\nI, J - To open or close the Left Wings/Flaps/Cape"<<std::endl;
            }
          }
        }
        else if(hierarchy == 2){
          if(lur == 1){
            if(part == 0){
              if(key == GLFW_KEY_Y){
                vp_right_shoulder_pad+=1.0f;
                if(vp_right_shoulder_pad>109.0f)
                  vp_right_shoulder_pad=109.0f;
              }
              else if(key == GLFW_KEY_G){
                vp_right_shoulder_pad-=1.0f;
                if(vp_right_shoulder_pad<0.0f)
                  vp_right_shoulder_pad=0.0f;
              }
              else if(key == GLFW_KEY_U){
                vp_right_shoulder_x+=1.0f;
                if(vp_right_shoulder_x>180.0f)
                  vp_right_shoulder_x=180.0f;
              }
              else if(key == GLFW_KEY_H){
                vp_right_shoulder_x-=1.0f;
                if(vp_right_shoulder_x<-180.0f)
                  vp_right_shoulder_x=-180.0f;
              }
              else if(key == GLFW_KEY_I){
                vp_right_shoulder_y+=1.0f;
                if(vp_right_shoulder_y>30.0f)
                  vp_right_shoulder_y=30.0f;
              }
              else if(key == GLFW_KEY_J){
                vp_right_shoulder_y-=1.0f;
                if(vp_right_shoulder_y<-30.0f)
                  vp_right_shoulder_y=-30.0f;
              }
              else if(key == GLFW_KEY_O){
                vp_right_shoulder_z+=1.0f;
                if(vp_right_shoulder_z>109.0f)
                  vp_right_shoulder_z=109.0f;
                if(vp_right_shoulder_z>vp_right_shoulder_pad)
                  vp_right_shoulder_pad = vp_right_shoulder_z;
              }
              else if(key == GLFW_KEY_K){
                vp_right_shoulder_z-=1.0f;
                if(vp_right_shoulder_z<0.0f)
                  vp_right_shoulder_z=0.0f;
              }
              else if(key == GLFW_KEY_P){
                vp_right_shoulder_translate+=0.01f;
                if(vp_right_shoulder_translate>0.5f)
                  vp_right_shoulder_translate=0.5f;
              }
              else if(key == GLFW_KEY_L){
                vp_right_shoulder_translate-=0.01f;
                if(vp_right_shoulder_translate<0.0f)
                  vp_right_shoulder_translate=0.0f;
              }
            }
            else if(part == 1){
              if(key == GLFW_KEY_Y){
                vp_right_elbow_y+=1.0f;
                if(vp_right_elbow_y>90.0f)
                  vp_right_elbow_y=90.0f;
              }
              else if(key == GLFW_KEY_G){
                vp_right_elbow_y-=1.0f;
                if(vp_right_elbow_y<-90.0f)
                  vp_right_elbow_y=-90.0f;
              }
              else if(key == GLFW_KEY_U){
                vp_right_elbow_x+=1.0f;
                if(vp_right_elbow_x>180.0f)
                  vp_right_elbow_x=180.0f;
              }
              else if(key == GLFW_KEY_H){
                vp_right_elbow_x-=1.0f;
                if(vp_right_elbow_x<-180.0f)
                  vp_right_elbow_x=-180.0f;
              }
              else if(key == GLFW_KEY_B){
                vp_right_hand_guard+=0.04f;
                if(vp_right_hand_guard>1.0f)
                  vp_right_hand_guard=1.0f;
              }
              else if(key == GLFW_KEY_V){
                vp_right_hand_guard-=0.04f;
                if(vp_right_hand_guard<0.0f)
                  vp_right_hand_guard=0.0f;
              }
              else if(key == GLFW_KEY_I){
                vp_right_hand_x+=1.0f;
                if(vp_right_hand_x>10.0f)
                  vp_right_hand_x=10.0f;
              }
              else if(key == GLFW_KEY_J){
                vp_right_hand_x-=1.0f;
                if(vp_right_hand_x<-10.0f)
                  vp_right_hand_x=-10.0f;
              }
              else if(key == GLFW_KEY_O){
                vp_right_hand_y+=1.0f;
                if(vp_right_hand_y>180.0f)
                  vp_right_hand_y=180.0f;
              }
              else if(key == GLFW_KEY_K){
                vp_right_hand_y-=1.0f;
                if(vp_right_hand_y<-180.0f)
                  vp_right_hand_y=-180.0f;
              }
              else if(key == GLFW_KEY_P){
                vp_right_hand_z+=1.0f;
                if(vp_right_hand_z>10.0f)
                  vp_right_hand_z=10.0f;
              }
              else if(key == GLFW_KEY_L){
                vp_right_hand_z-=1.0f;
                if(vp_right_hand_z<-10.0f)
                  vp_right_hand_z=-10.0f;
              }
            }
            else if(part == 2){
              if(key == GLFW_KEY_Y){
                vp_right_hip_z+=1.0f;
                if(vp_right_hip_z>10.0f)
                  vp_right_hip_z=10.0f;
              }
              else if(key == GLFW_KEY_G){
                vp_right_hip_z-=1.0f;
                if(vp_right_hip_z<-10.0f)
                  vp_right_hip_z=-10.0f;
              }
              else if(key == GLFW_KEY_U){
                vp_right_hip_x+=1.0f;
                if(vp_right_hip_x>90.0f)
                  vp_right_hip_x=90.0f;
              }
              else if(key == GLFW_KEY_H){
                vp_right_hip_x-=1.0f;
                if(vp_right_hip_x<-90.0f)
                  vp_right_hip_x=-90.0f;
              }
              else if(key == GLFW_KEY_I){
                vp_right_hip_y+=1.0f;
                if(vp_right_hip_y>98.0f)
                  vp_right_hip_y=98.0f;
              }
              else if(key == GLFW_KEY_J){
                vp_right_hip_y-=1.0f;
                if(vp_right_hip_y<0.0f)
                  vp_right_hip_y=0.0f;
              }
            }
            else if(part == 3){
              if(key == GLFW_KEY_Y){
                vp_right_knee_y+=1.0f;
                if(vp_right_knee_y>113.0f)
                  vp_right_knee_y=113.0f;
              }
              else if(key == GLFW_KEY_G){
                vp_right_knee_y-=1.0f;
                if(vp_right_knee_y<0.0f)
                  vp_right_knee_y=0.0f;
              }
              else if(key == GLFW_KEY_U){
                vp_right_knee_x+=1.0f;
                if(vp_right_knee_x>180.0f)
                  vp_right_knee_x=180.0f;
              }
              else if(key == GLFW_KEY_H){
                vp_right_knee_x-=1.0f;
                if(vp_right_knee_x<-180.0f)
                  vp_right_knee_x=-180.0f;
              }
              else if(key == GLFW_KEY_I){
                vp_right_foot_y+=1.0f;
                if(vp_right_foot_y>5.0f)
                  vp_right_foot_y=5.0f;
              }
              else if(key == GLFW_KEY_J){
                vp_right_foot_y-=1.0f;
                if(vp_right_foot_y<-5.0f)
                  vp_right_foot_y=-5.0f;
              }
              else if(key == GLFW_KEY_O){
                vp_right_foot_x+=1.0f;
                if(vp_right_foot_x>240.0f)
                  vp_right_foot_x=240.0f;
              }
              else if(key == GLFW_KEY_K){
                vp_right_foot_x-=1.0f;
                if(vp_right_foot_x<0.0f)
                  vp_right_foot_x=0.0f;
              }
              else if(key == GLFW_KEY_P){
                vp_right_foot_z+=1.0f;
                if(vp_right_foot_z>10.0f)
                  vp_right_foot_z=10.0f;
              }
              else if(key == GLFW_KEY_L){
                vp_right_foot_z-=1.0f;
                if(vp_right_foot_z<-10.0f)
                  vp_right_foot_z=-10.0f;
              }
            }
            else if(part == 4){
              if(key == GLFW_KEY_Y){
                vp_right_wing_torso_torso+=1.0f;
                if(vp_right_wing_torso_torso>90.0f)
                  vp_right_wing_torso_torso=90.0f;
              }
              else if(key == GLFW_KEY_G){
                vp_right_wing_torso_torso-=1.0f;
                if(vp_right_wing_torso_torso<-90.0f)
                  vp_right_wing_torso_torso=-90.0f;
              }
              else if(key == GLFW_KEY_U){
                vp_right_wing_wing_torso+=1.0f;
                if(vp_right_wing_wing_torso>90.0f)
                  vp_right_wing_wing_torso=90.0f;
              }
              else if(key == GLFW_KEY_H){
                vp_right_wing_wing_torso-=1.0f;
                if(vp_right_wing_wing_torso<-90.0f)
                  vp_right_wing_wing_torso=-90.0f;
              }
              else if(key == GLFW_KEY_I){
                vp_right_wing+=1.0f;
                if(vp_right_wing>90.0f)
                  vp_right_wing=90.0f;
              }
              else if(key == GLFW_KEY_J){
                vp_right_wing-=1.0f;
                if(vp_right_wing<0.0f)
                  vp_right_wing=0.0f;
              }
            }
          }
          else if(lur == -1){
            if(part == 0){
              if(key == GLFW_KEY_Y){
                vp_left_shoulder_pad+=1.0f;
                if(vp_left_shoulder_pad>109.0f)
                  vp_left_shoulder_pad=109.0f;
              }
              else if(key == GLFW_KEY_G){
                vp_left_shoulder_pad-=1.0f;
                if(vp_left_shoulder_pad<0.0f)
                  vp_left_shoulder_pad=0.0f;
              }
              else if(key == GLFW_KEY_U){
                vp_left_shoulder_x+=1.0f;
                if(vp_left_shoulder_x>180.0f)
                  vp_left_shoulder_x=180.0f;
              }
              else if(key == GLFW_KEY_H){
                vp_left_shoulder_x-=1.0f;
                if(vp_left_shoulder_x<-180.0f)
                  vp_left_shoulder_x=-180.0f;
              }
              else if(key == GLFW_KEY_I){
                vp_left_shoulder_y+=1.0f;
                if(vp_left_shoulder_y>30.0f)
                  vp_left_shoulder_y=30.0f;
              }
              else if(key == GLFW_KEY_J){
                vp_left_shoulder_y-=1.0f;
                if(vp_left_shoulder_y<-30.0f)
                  vp_left_shoulder_y=-30.0f;
              }
              else if(key == GLFW_KEY_O){
                vp_left_shoulder_z+=1.0f;
                if(vp_left_shoulder_z>109.0f)
                  vp_left_shoulder_z=109.0f;
                if(vp_left_shoulder_z>vp_left_shoulder_pad)
                  vp_left_shoulder_pad = vp_left_shoulder_z;
              }
              else if(key == GLFW_KEY_K){
                vp_left_shoulder_z-=1.0f;
                if(vp_left_shoulder_z<0.0f)
                  vp_left_shoulder_z=0.0f;
              }
              else if(key == GLFW_KEY_P){
                vp_left_shoulder_translate+=0.01f;
                if(vp_left_shoulder_translate>0.5f)
                  vp_left_shoulder_translate=0.5f;
              }
              else if(key == GLFW_KEY_L){
                vp_left_shoulder_translate-=0.01f;
                if(vp_left_shoulder_translate<0.0f)
                  vp_left_shoulder_translate=0.0f;
              }
            }
            else if(part == 1){
              if(key == GLFW_KEY_Y){
                vp_left_elbow_y+=1.0f;
                if(vp_left_elbow_y>90.0f)
                  vp_left_elbow_y=90.0f;
              }
              else if(key == GLFW_KEY_G){
                vp_left_elbow_y-=1.0f;
                if(vp_left_elbow_y<-90.0f)
                  vp_left_elbow_y=-90.0f;
              }
              else if(key == GLFW_KEY_U){
                vp_left_elbow_x+=1.0f;
                if(vp_left_elbow_x>180.0f)
                  vp_left_elbow_x=180.0f;
              }
              else if(key == GLFW_KEY_H){
                vp_left_elbow_x-=1.0f;
                if(vp_left_elbow_x<-180.0f)
                  vp_left_elbow_x=-180.0f;
              }
              else if(key == GLFW_KEY_B){
                vp_left_hand_guard+=0.04f;
                if(vp_left_hand_guard>1.0f)
                  vp_left_hand_guard=1.0f;
              }
              else if(key == GLFW_KEY_V){
                vp_left_hand_guard-=0.04f;
                if(vp_left_hand_guard<0.0f)
                  vp_left_hand_guard=0.0f;
              }
              else if(key == GLFW_KEY_I){
                vp_left_hand_x+=1.0f;
                if(vp_left_hand_x>10.0f)
                  vp_left_hand_x=10.0f;
              }
              else if(key == GLFW_KEY_J){
                vp_left_hand_x-=1.0f;
                if(vp_left_hand_x<-10.0f)
                  vp_left_hand_x=-10.0f;
              }
              else if(key == GLFW_KEY_O){
                vp_left_hand_y+=1.0f;
                if(vp_left_hand_y>180.0f)
                  vp_left_hand_y=180.0f;
              }
              else if(key == GLFW_KEY_K){
                vp_left_hand_y-=1.0f;
                if(vp_left_hand_y<-180.0f)
                  vp_left_hand_y=-180.0f;
              }
              else if(key == GLFW_KEY_P){
                vp_left_hand_z+=1.0f;
                if(vp_left_hand_z>10.0f)
                  vp_left_hand_z=10.0f;
              }
              else if(key == GLFW_KEY_L){
                vp_left_hand_z-=1.0f;
                if(vp_left_hand_z<-10.0f)
                  vp_left_hand_z=-10.0f;
              }
            }
            else if(part == 2){
              if(key == GLFW_KEY_Y){
                vp_left_hip_z+=1.0f;
                if(vp_left_hip_z>10.0f)
                  vp_left_hip_z=10.0f;
              }
              else if(key == GLFW_KEY_G){
                vp_left_hip_z-=1.0f;
                if(vp_left_hip_z<-10.0f)
                  vp_left_hip_z=-10.0f;
              }
              else if(key == GLFW_KEY_U){
                vp_left_hip_x+=1.0f;
                if(vp_left_hip_x>90.0f)
                  vp_left_hip_x=90.0f;
              }
              else if(key == GLFW_KEY_H){
                vp_left_hip_x-=1.0f;
                if(vp_left_hip_x<-90.0f)
                  vp_left_hip_x=-90.0f;
              }
              else if(key == GLFW_KEY_I){
                vp_left_hip_y+=1.0f;
                if(vp_left_hip_y>98.0f)
                  vp_left_hip_y=98.0f;
              }
              else if(key == GLFW_KEY_J){
                vp_left_hip_y-=1.0f;
                if(vp_left_hip_y<0.0f)
                  vp_left_hip_y=0.0f;
              }
            }
            else if(part == 3){
              if(key == GLFW_KEY_Y){
                vp_left_knee_y+=1.0f;
                if(vp_left_knee_y>113.0f)
                  vp_left_knee_y=113.0f;
              }
              else if(key == GLFW_KEY_G){
                vp_left_knee_y-=1.0f;
                if(vp_left_knee_y<0.0f)
                  vp_left_knee_y=0.0f;
              }
              else if(key == GLFW_KEY_U){
                vp_left_knee_x+=1.0f;
                if(vp_left_knee_x>180.0f)
                  vp_left_knee_x=180.0f;
              }
              else if(key == GLFW_KEY_H){
                vp_left_knee_x-=1.0f;
                if(vp_left_knee_x<-180.0f)
                  vp_left_knee_x=-180.0f;
              }
              else if(key == GLFW_KEY_I){
                vp_left_foot_y+=1.0f;
                if(vp_left_foot_y>5.0f)
                  vp_left_foot_y=5.0f;
              }
              else if(key == GLFW_KEY_J){
                vp_left_foot_y-=1.0f;
                if(vp_left_foot_y<-5.0f)
                  vp_left_foot_y=-5.0f;
              }
              else if(key == GLFW_KEY_O){
                vp_left_foot_x+=1.0f;
                if(vp_left_foot_x>240.0f)
                  vp_left_foot_x=240.0f;
              }
              else if(key == GLFW_KEY_K){
                vp_left_foot_x-=1.0f;
                if(vp_left_foot_x<0.0f)
                  vp_left_foot_x=0.0f;
              }
              else if(key == GLFW_KEY_P){
                vp_left_foot_z+=1.0f;
                if(vp_left_foot_z>10.0f)
                  vp_left_foot_z=10.0f;
              }
              else if(key == GLFW_KEY_L){
                vp_left_foot_z-=1.0f;
                if(vp_left_foot_z<-10.0f)
                  vp_left_foot_z=-10.0f;
              }
            }
            else if(part == 4){
              if(key == GLFW_KEY_Y){
                vp_left_wing_torso_torso+=1.0f;
                if(vp_left_wing_torso_torso>90.0f)
                  vp_left_wing_torso_torso=90.0f;
              }
              else if(key == GLFW_KEY_G){
                vp_left_wing_torso_torso-=1.0f;
                if(vp_left_wing_torso_torso<-90.0f)
                  vp_left_wing_torso_torso=-90.0f;
              }
              else if(key == GLFW_KEY_U){
                vp_left_wing_wing_torso+=1.0f;
                if(vp_left_wing_wing_torso>90.0f)
                  vp_left_wing_wing_torso=90.0f;
              }
              else if(key == GLFW_KEY_H){
                vp_left_wing_wing_torso-=1.0f;
                if(vp_left_wing_wing_torso<-90.0f)
                  vp_left_wing_wing_torso=-90.0f;
              }
              else if(key == GLFW_KEY_I){
                vp_left_wing+=1.0f;
                if(vp_left_wing>90.0f)
                  vp_left_wing=90.0f;
              }
              else if(key == GLFW_KEY_J){
                vp_left_wing-=1.0f;
                if(vp_left_wing<0.0f)
                  vp_left_wing=0.0f;
              }
            }
          }
        }
      }
      else if(transformer == 1){
        if (key == GLFW_KEY_LEFT )
          op_torso_y -= 1.0;
        else if (key == GLFW_KEY_RIGHT )
          op_torso_y += 1.0;
        else if (key == GLFW_KEY_UP )
          op_torso_x -= 1.0;
        else if (key == GLFW_KEY_DOWN )
          op_torso_x += 1.0;
        else if (key == GLFW_KEY_PAGE_UP || key == GLFW_KEY_KP_9)
          op_torso_z -= 1.0;
        else if (key == GLFW_KEY_PAGE_DOWN || key == GLFW_KEY_KP_3)
          op_torso_z += 1.0;
        else if (key == GLFW_KEY_KP_5)
          op_ypos -= 0.1;
        else if (key == GLFW_KEY_KP_8)
          op_ypos += 0.1;
        else if (key == GLFW_KEY_KP_4)
          op_xpos -= 0.1;
        else if (key == GLFW_KEY_KP_6)
          op_xpos += 0.1;
        else if (key == GLFW_KEY_KP_7)
          op_zpos -= 0.1;
        else if (key == GLFW_KEY_KP_1)
          op_zpos += 0.1;
        else if (key == GLFW_KEY_Q){
          if(hierarchy>0)
            std::cout<<"KEY BINDINGS:\nU - To get control of the Ship and Head\nL - To get control of the Left Half of the Transformer\nR - To get control of the Right Half of the Transformer"<<std::endl;
          hierarchy=0;
          time_elapsed = glfwGetTime();
        }

        else if (key == GLFW_KEY_T)
          op_transformation=1; 

        else if(hierarchy <= 0){
          if(key == GLFW_KEY_U){
            hierarchy=1;
            lur = 0;
            time_elapsed = glfwGetTime();
            std::cout<<"KEY BINDINGS:\n1, 2 - To rotate the lower Torso along x axis\n3, 4 - To rotate the lower Torso along y axis\n5, 6 - To rotate the lower Torso along z axis\nY, G - To rotate the Ship Torso along x axis\nE, F - To rotate the Ship Torso along y axis\nX, Z - To rotate the Ship Torso along z axis\nU, H - To rotate the Head along the x axis\nI, J - To rotate the Head along the y axis\nO, K - To rotate the Head along the z axis\nP, L - To translate the Head along the y axis"<<std::endl;
          }
          else if(key == GLFW_KEY_L){
            hierarchy=1;
            lur = -1;
            time_elapsed = glfwGetTime();
            std::cout<<"KEY BINDINGS:\nI - To get control of the Left Shoulder and left upperarm\nK - To get control of the Left Elbow, Wrist and Hand\nO - To get control of the Left Hip Joint\nL - To get control of the Left Knee and Ankle\n"<<std::endl;
          }
          else if(key == GLFW_KEY_R){
            hierarchy=1;
            lur = 1;
            time_elapsed = glfwGetTime();
            std::cout<<"KEY BINDINGS:\nI - To get control of the Right Shoulder and right upperarm \nK - To get control of the Right Elbow, Wrist and Hand\nO - To get control of the Right Hip Joint\nL - To get control of the Right Knee and Ankle\n"<<std::endl;
          }
        }
        else if(hierarchy == 1){
          if(lur == 0){

            //lower lorso
            if(key == GLFW_KEY_1){
              op_lower_torso_rotate_x+=1.0f;
              if(op_lower_torso_rotate_x>90.0f)
                op_lower_torso_rotate_x=90.0f;
            }
            else if(key == GLFW_KEY_2){
              op_lower_torso_rotate_x-=1.0f;
              if(op_lower_torso_rotate_x<0.0f)
                op_lower_torso_rotate_x=0.0f;
            }
            else if(key == GLFW_KEY_3){
              op_lower_torso_rotate_y+=1.0f;
              if(op_lower_torso_rotate_y>90.0f)
                op_lower_torso_rotate_y=90.0f;
            }
            else if(key == GLFW_KEY_4){
              op_lower_torso_rotate_y-=1.0f;
              if(op_lower_torso_rotate_y<0.0f)
                op_lower_torso_rotate_y=0.0f;
            }
            else if(key == GLFW_KEY_5){
              op_lower_torso_rotate_z+=1.0f;
              if(op_lower_torso_rotate_z>90.0f)
                op_lower_torso_rotate_z=90.0f;
            }
            else if(key == GLFW_KEY_6){
              op_lower_torso_rotate_z-=1.0f;
              if(op_lower_torso_rotate_z<0.0f)
                op_lower_torso_rotate_z=0.0f;
            }
            //----------ship torso
            else if(key == GLFW_KEY_Y){
              op_ship_rotate_x+=1.0f;
              if(op_ship_rotate_x>90.0f)
                op_ship_rotate_x=90.0f;
            }
            else if(key == GLFW_KEY_G){
              op_ship_rotate_x-=1.0f;
              if(op_ship_rotate_x<0.0f)
                op_ship_rotate_x=0.0f;
            }
            else if(key == GLFW_KEY_E){
              op_ship_rotate_y+=1.0f;
              if(op_ship_rotate_x>90.0f)
                op_ship_rotate_x=90.0f;
            }
            else if(key == GLFW_KEY_F){
              op_ship_rotate_y-=1.0f;
              if(op_ship_rotate_x<0.0f)
                op_ship_rotate_x=0.0f;
            }
            else if(key == GLFW_KEY_X){
              op_ship_rotate_z+=1.0f;
              if(op_ship_rotate_x>90.0f)
                op_ship_rotate_x=90.0f;
            }
            else if(key == GLFW_KEY_Z){
              op_ship_rotate_z-=1.0f;
              if(op_ship_rotate_x<0.0f)
                op_ship_rotate_x=0.0f;
            }

            else if(key == GLFW_KEY_U){
              op_head_x+=1.0f;
              if(op_head_x>45.0f)
                op_head_x=45.0f;
            }
            else if(key == GLFW_KEY_H){
              op_head_x-=1.0f;
              if(op_head_x<-45.0f)
                op_head_x=-45.0f;
            }
            else if(key == GLFW_KEY_I){
              op_head_y+=1.0f;
              if(op_head_y>180.0f)
                op_head_y=180.0f;
            }
            else if(key == GLFW_KEY_J){
              op_head_y-=1.0f;
              if(op_head_y<-180.0f)
                op_head_y=-180.0f;
            }
            else if(key == GLFW_KEY_O){
              op_head_z+=1.0f;
              if(op_head_z>45.0f)
                op_head_z=45.0f;
            }
            else if(key == GLFW_KEY_K){
              op_head_z-=1.0f;
              if(op_head_z<-45.0f)
                op_head_z=-45.0f;
            }
            else if(key == GLFW_KEY_P){
              op_head_translate+=0.03f;
              if(op_head_translate>0.0f)
                op_head_translate=0.0f;
            }
            else if(key == GLFW_KEY_L){
              op_head_translate-=0.03f;
              if(op_head_translate<-3.0f)
                op_head_translate=-30.0f;
            }
          }
          else if(lur == 1){
            if(key == GLFW_KEY_I){
              hierarchy = 2;
              part = 0;
              time_elapsed = glfwGetTime();
              std::cout<<"KEY BINDINGS:\nU, H - To rotate the Right Shoulder along the x axis\nI, J - To rotate the Right Shoulder along the y axis\nO, K - To rotate the Right Shoulder along the z axis\nP, L - To translate the Right Shoulder along the x axis\nY, G - To rotate the Right upperarm along the x axis\nE, F - To rotate the Right upperarm along the y axis\nX, Z - To rotate the Right apperarm along the z axis"<<std::endl;
            }

            else if(key == GLFW_KEY_K){
              hierarchy = 2;
              part = 1;
              time_elapsed = glfwGetTime();
              std::cout<<"KEY BINDINGS:\nY, G - To rotate the Right Elbow along the x axis\nU, H - To rotate the Right Elbow along the z axis\nI, J - To rotate the Right Hand along the x axis\nO, K - To rotate the Right Hand along the y axis\nP, L - To rotate the Right Hand along the z axis\nE, F - To rotate the Right Wrist along the x axis\nX, Z - To rotate the Right Wrist along the y axis\nV, B - To rotate the Right Wrist along the z axis"<<std::endl;
            }
            else if(key == GLFW_KEY_O){
              hierarchy = 2;
              part = 2;
              time_elapsed = glfwGetTime();
              std::cout<<"KEY BINDINGS:\nY, G - To rotate the Right Hip Joint along the x axis\nU, H - To rotate the Right Hip Joint along the y axis\nI, J - To translate the Right Hip Joint along the z axis"<<std::endl;
            }
            else if(key == GLFW_KEY_L){
              hierarchy = 2;
              part = 3;
              time_elapsed = glfwGetTime();
              std::cout<<"KEY BINDINGS:\nY, G - To rotate the Right Knee along the x axis\nU, H - To rotate the Right Knee along the y axis\nI, J - To rotate the Right Ankle along the x axis\nO, K - To rotate the Right Ankle along the y axis\nP, L - To rotate the Right Ankle along the z axis"<<std::endl;
            }
            else if(key == GLFW_KEY_P){
              hierarchy = 2;
              part = 4;
              time_elapsed = glfwGetTime();
              std::cout<<"KEY BINDINGS:\nY, G - To rotate the Right Torso Joint\nU, H - To rotate the Right Flaps Joint\nI, J - To open or close the Right Wings/Flaps/Cape"<<std::endl;
            }
          }
          else if(lur == -1){
            if(key == GLFW_KEY_I){
              hierarchy = 2;
              part = 0;
              time_elapsed = glfwGetTime();
              std::cout<<"KEY BINDINGS:\nU,  H - To rotate the Left Shoulder along the x axis\nI, J - To rotate the Left Shoulder along the y axis\nO, K - To rotate the Left Shoulder along the z axis\nP, L - To translate the Left Shoulder along the x axis\nY, G - To rotate the left upperarm along the x axis\nE, F - To rotate the left upperarm along the y axis\nX, Z - To rotate the left apperarm along the z axis"<<std::endl;
            }
            else if(key == GLFW_KEY_K){
              hierarchy = 2;
              part = 1;
              time_elapsed = glfwGetTime();
              std::cout<<"KEY BINDINGS:\nY, G - To rotate the Left Elbow along the x axis\nU, H - To rotate the Left Elbow along the z axis\nI, J - To rotate the Left Hand along the x axis\nO, K - To rotate the Left Hand along the y axis\nP, L - To rotate the Left Hand along the z axis\nE, F - To rotate the Left Wrist along the x axis\nX, Z - To rotate the Left Wrist along the y axis\nV, B - To rotate the Left Wrist along the z axis"<<std::endl;
            }
            else if(key == GLFW_KEY_O){
              hierarchy = 2;
              part = 2;
              time_elapsed = glfwGetTime();
              std::cout<<"KEY BINDINGS:\nY, G - To rotate the Left Hip Joint along the x axis\nU, H - To rotate the Left Hip Joint along the y axis\nI, J - To translate the Left Hip Joint along the z axis"<<std::endl;
            }
            else if(key == GLFW_KEY_L){
              hierarchy = 2;
              part = 3;
              time_elapsed = glfwGetTime();
              std::cout<<"KEY BINDINGS:\nY, G - To rotate the Left Knee along the x axis\nU, H - To rotate the Left Knee along the y axis\nI, J - To rotate the Left Ankle along the x axis\nO, K - To rotate the Left Ankle along the y axis\nP, L - To rotate the Left Ankle along the z axis"<<std::endl;
            }
            else if(key == GLFW_KEY_P){
              hierarchy = 2;
              part = 4;
              time_elapsed = glfwGetTime();
              std::cout<<"KEY BINDINGS:\nY, G - To rotate the Left Torso Joint\nU, H - To rotate the Left Flaps Joint\nI, J - To open or close the Left Wings/Flaps/Cape"<<std::endl;
            }
          }
        }
        else if(hierarchy == 2){
          if(lur == 1){
            if(part == 0){
              if(key == GLFW_KEY_U){
                op_right_shoulder_x+=1.0f;
                if(op_right_shoulder_x>90.0f)
                  op_right_shoulder_x=90.0f;
              }
              else if(key == GLFW_KEY_H){
                op_right_shoulder_x-=1.0f;
                if(op_right_shoulder_x<-90.0f)
                  op_right_shoulder_x=-90.0f;
              }
              else if(key == GLFW_KEY_I){
                op_right_shoulder_y+=1.0f;
                if(op_right_shoulder_y>90.0f)
                  op_right_shoulder_y=90.0f;
              }
              else if(key == GLFW_KEY_J){
                op_right_shoulder_y-=1.0f;
                if(op_right_shoulder_y<0.0f)
                  op_right_shoulder_y=0.0f;
              }
              else if(key == GLFW_KEY_O){
                op_right_shoulder_z+=1.0f;
                if(op_right_shoulder_z>90.0f)
                  op_right_shoulder_z=90.0f;
              }
              else if(key == GLFW_KEY_K){
                op_right_shoulder_z-=1.0f;
                if(op_right_shoulder_z<-90.0f)
                  op_right_shoulder_z=-90.0f;
              }
              else if(key == GLFW_KEY_P){
                op_shoulder_translate+=0.08f;
                if(op_shoulder_translate>0.0f)
                  op_shoulder_translate=0.0f;
              }
              else if(key == GLFW_KEY_L){
                op_shoulder_translate-=0.08f;
                if(op_shoulder_translate<-8.0f)
                  op_shoulder_translate=-8.0f;
              }
            // upperarm 
              else if(key == GLFW_KEY_Y){
                op_right_upperarm_x+=1.0f;
                if(op_right_upperarm_x>90.0f)
                  op_right_upperarm_x=90.0f;
              }
              else if(key == GLFW_KEY_G){
                op_right_upperarm_x-=1.0f;
                if(op_right_upperarm_x<-90.0f)
                  op_right_upperarm_x=-90.0f;
              }
              else if(key == GLFW_KEY_E){
                op_right_upperarm_y+=1.0f;
                if(op_right_upperarm_y>90.0f)
                  op_right_upperarm_y=90.0f;
              }
              else if(key == GLFW_KEY_F){
                op_right_upperarm_y-=1.0f;
                if(op_right_upperarm_y<0.0f)
                  op_right_upperarm_y=0.0f;
              }
              else if(key == GLFW_KEY_X){
                op_right_upperarm_z+=1.0f;
                if(op_right_upperarm_z>90.0f)
                  op_right_upperarm_z=90.0f;
              }
              else if(key == GLFW_KEY_Z){
                op_right_upperarm_z-=1.0f;
                if(op_right_upperarm_z<-90.0f)
                  op_right_upperarm_z=-90.0f;
              }
            }
            else if(part == 1){
              if(key == GLFW_KEY_Y){
                op_right_elbow_y+=1.0f;
                if(op_right_elbow_y>90.0f)
                  op_right_elbow_y=90.0f;
              }
              else if(key == GLFW_KEY_G){
                op_right_elbow_y-=1.0f;
                if(op_right_elbow_y<-90.0f)
                  op_right_elbow_y=-90.0f;
              }
              else if(key == GLFW_KEY_U){
                op_right_elbow_x+=1.0f;
                if(op_right_elbow_x>180.0f)
                  op_right_elbow_x=180.0f;
              }
              else if(key == GLFW_KEY_H){
                op_right_elbow_x-=1.0f;
                if(op_right_elbow_x<-180.0f)
                  op_right_elbow_x=-180.0f;
              }
              else if(key == GLFW_KEY_E){
                op_right_wrist_x+=1.0f;
                if(op_right_wrist_x>10.0f)
                  op_right_wrist_x=10.0f;
              }
              else if(key == GLFW_KEY_F){
                op_right_wrist_x-=1.0f;
                if(op_right_wrist_x<-10.0f)
                  op_right_wrist_x=-10.0f;
              }
              else if(key == GLFW_KEY_X){
                op_right_wrist_y+=1.0f;
                if(op_right_wrist_y>180.0f)
                  op_right_wrist_y=180.0f;
              }
              else if(key == GLFW_KEY_Z){
                op_right_wrist_y-=1.0f;
                if(op_right_wrist_y<-180.0f)
                  op_right_wrist_y=-180.0f;
              }
              else if(key == GLFW_KEY_V){
                op_right_wrist_z+=1.0f;
                if(op_right_wrist_z>10.0f)
                  op_right_wrist_z=10.0f;
              }
              else if(key == GLFW_KEY_B){
                op_right_wrist_z-=1.0f;
                if(op_right_wrist_z<-10.0f)
                  op_right_wrist_z=-10.0f;
              }
              else if(key == GLFW_KEY_I){
                op_right_hand_x+=1.0f;
                if(op_right_hand_x>10.0f)
                  op_right_hand_x=10.0f;
              }
              else if(key == GLFW_KEY_J){
                op_right_hand_x-=1.0f;
                if(op_right_hand_x<-10.0f)
                  op_right_hand_x=-10.0f;
              }
              else if(key == GLFW_KEY_O){
                op_right_hand_y+=1.0f;
                if(op_right_hand_y>180.0f)
                  op_right_hand_y=180.0f;
              }
              else if(key == GLFW_KEY_K){
                op_right_hand_y-=1.0f;
                if(op_right_hand_y<-180.0f)
                  op_right_hand_y=-180.0f;
              }
              else if(key == GLFW_KEY_P){
                op_right_hand_z+=1.0f;
                if(op_right_hand_z>10.0f)
                  op_right_hand_z=10.0f;
              }
              else if(key == GLFW_KEY_L){
                op_right_hand_z-=1.0f;
                if(op_right_hand_z<-10.0f)
                  op_right_hand_z=-10.0f;
              }
            }
            else if(part == 2){
              if(key == GLFW_KEY_Y){
                op_right_hip_z+=1.0f;
                if(op_right_hip_z>10.0f)
                  op_right_hip_z=10.0f;
              }
              else if(key == GLFW_KEY_G){
                op_right_hip_z-=1.0f;
                if(op_right_hip_z<-10.0f)
                  op_right_hip_z=-10.0f;
              }
              else if(key == GLFW_KEY_U){
                op_right_hip_x+=1.0f;
                if(op_right_hip_x>90.0f)
                  op_right_hip_x=90.0f;
              }
              else if(key == GLFW_KEY_H){
                op_right_hip_x-=1.0f;
                if(op_right_hip_x<-90.0f)
                  op_right_hip_x=-90.0f;
              }
              else if(key == GLFW_KEY_I){
                op_right_hip_y+=1.0f;
                if(op_right_hip_y>98.0f)
                  op_right_hip_y=98.0f;
              }
              else if(key == GLFW_KEY_J){
                op_right_hip_y-=1.0f;
                if(op_right_hip_y<0.0f)
                  op_right_hip_y=0.0f;
              }
            }
            else if(part == 3){
              if(key == GLFW_KEY_Y){
                op_right_knee_y+=1.0f;
                if(op_right_knee_y>113.0f)
                  op_right_knee_y=113.0f;
              }
              else if(key == GLFW_KEY_G){
                op_right_knee_y-=1.0f;
                if(op_right_knee_y<0.0f)
                  op_right_knee_y=0.0f;
              }
              else if(key == GLFW_KEY_U){
                op_right_knee_x+=1.0f;
                if(op_right_knee_x>180.0f)
                  op_right_knee_x=180.0f;
              }
              else if(key == GLFW_KEY_H){
                op_right_knee_x-=1.0f;
                if(op_right_knee_x<-180.0f)
                  op_right_knee_x=-180.0f;
              }
              else if(key == GLFW_KEY_I){
                op_right_foot_y+=1.0f;
                if(op_right_foot_y>5.0f)
                  op_right_foot_y=5.0f;
              }
              else if(key == GLFW_KEY_J){
                op_right_foot_y-=1.0f;
                if(op_right_foot_y<-5.0f)
                  op_right_foot_y=-5.0f;
              }
              else if(key == GLFW_KEY_O){
                op_right_foot_x+=1.0f;
                if(op_right_foot_x>240.0f)
                  op_right_foot_x=240.0f;
              }
              else if(key == GLFW_KEY_K){
                op_right_foot_x-=1.0f;
                if(op_right_foot_x<0.0f)
                  op_right_foot_x=0.0f;
              }
              else if(key == GLFW_KEY_P){
                op_right_foot_z+=1.0f;
                if(op_right_foot_z>10.0f)
                  op_right_foot_z=10.0f;
              }
              else if(key == GLFW_KEY_L){
                op_right_foot_z-=1.0f;
                if(op_right_foot_z<-10.0f)
                  op_right_foot_z=-10.0f;
              }
            }
          }
          else if(lur == -1){
            if(part == 0){
              if(key == GLFW_KEY_U){
                op_left_shoulder_x+=1.0f;
                if(op_left_shoulder_x>180.0f)
                  op_left_shoulder_x=180.0f;
              }
              else if(key == GLFW_KEY_H){
                op_left_shoulder_x-=1.0f;
                if(op_left_shoulder_x<-180.0f)
                  op_left_shoulder_x=-180.0f;
              }
              else if(key == GLFW_KEY_I){
                op_left_shoulder_y+=1.0f;
                if(op_left_shoulder_y>30.0f)
                  op_left_shoulder_y=30.0f;
              }
              else if(key == GLFW_KEY_J){
                op_left_shoulder_y-=1.0f;
                if(op_left_shoulder_y<-30.0f)
                  op_left_shoulder_y=-30.0f;
              }
              else if(key == GLFW_KEY_O){
                op_left_shoulder_z+=1.0f;
                if(op_left_shoulder_z>109.0f)
                  op_left_shoulder_z=109.0f;
              }
              else if(key == GLFW_KEY_K){
                op_left_shoulder_z-=1.0f;
                if(op_left_shoulder_z<0.0f)
                  op_left_shoulder_z=0.0f;
              }
              else if(key == GLFW_KEY_P){
                op_shoulder_translate+=0.01f;
                if(op_shoulder_translate>0.5f)
                  op_shoulder_translate=0.5f;
              }
              else if(key == GLFW_KEY_L){
                op_shoulder_translate-=0.01f;
                if(op_shoulder_translate<0.0f)
                  op_shoulder_translate=0.0f;
              }

              else if(key == GLFW_KEY_Y){
                op_left_upperarm_x+=1.0f;
                if(op_left_upperarm_x>90.0f)
                  op_left_upperarm_x=90.0f;
              }
              else if(key == GLFW_KEY_G){
                op_left_upperarm_x-=1.0f;
                if(op_left_upperarm_x<-90.0f)
                  op_left_upperarm_x=-90.0f;
              }
              else if(key == GLFW_KEY_E){
                op_left_upperarm_y+=1.0f;
                if(op_left_upperarm_y>90.0f)
                  op_left_upperarm_y=90.0f;
              }
              else if(key == GLFW_KEY_F){
                op_left_upperarm_y-=1.0f;
                if(op_left_upperarm_y<0.0f)
                  op_left_upperarm_y=0.0f;
              }
              else if(key == GLFW_KEY_X){
                op_left_upperarm_z+=1.0f;
                if(op_left_upperarm_z>90.0f)
                  op_left_upperarm_z=90.0f;
              }
              else if(key == GLFW_KEY_Z){
                op_left_upperarm_z-=1.0f;
                if(op_left_upperarm_z<-90.0f)
                  op_left_upperarm_z=-90.0f;
              }
            }
            else if(part == 1){
              if(key == GLFW_KEY_Y){
                op_left_elbow_y+=1.0f;
                if(op_left_elbow_y>90.0f)
                  op_left_elbow_y=90.0f;
              }
              else if(key == GLFW_KEY_G){
                op_left_elbow_y-=1.0f;
                if(op_left_elbow_y<-90.0f)
                  op_left_elbow_y=-90.0f;
              }
              else if(key == GLFW_KEY_U){
                op_left_elbow_x+=1.0f;
                if(op_left_elbow_x>180.0f)
                  op_left_elbow_x=180.0f;
              }
              else if(key == GLFW_KEY_H){
                op_left_elbow_x-=1.0f;
                if(op_left_elbow_x<-180.0f)
                  op_left_elbow_x=-180.0f;
              }
//----------------------------------
              else if(key == GLFW_KEY_E){
                op_left_wrist_x+=1.0f;
                if(op_left_wrist_x>10.0f)
                  op_left_wrist_x=10.0f;
              }
              else if(key == GLFW_KEY_F){
                op_left_wrist_x-=1.0f;
                if(op_left_wrist_x<-10.0f)
                  op_left_wrist_x=-10.0f;
              }
              else if(key == GLFW_KEY_X){
                op_left_wrist_y+=1.0f;
                if(op_left_wrist_y>180.0f)
                  op_left_wrist_y=180.0f;
              }
              else if(key == GLFW_KEY_Z){
                op_left_wrist_y-=1.0f;
                if(op_left_wrist_y<-180.0f)
                  op_left_wrist_y=-180.0f;
              }
              else if(key == GLFW_KEY_V){
                op_left_wrist_z+=1.0f;
                if(op_left_wrist_z>10.0f)
                  op_left_wrist_z=10.0f;
              }
              else if(key == GLFW_KEY_B){
                op_left_wrist_z-=1.0f;
                if(op_left_wrist_z<-10.0f)
                  op_left_wrist_z=-10.0f;
              }
              else if(key == GLFW_KEY_I){
                op_left_hand_x+=1.0f;
                if(op_left_hand_x>10.0f)
                  op_left_hand_x=10.0f;
              }
              else if(key == GLFW_KEY_J){
                op_left_hand_x-=1.0f;
                if(op_left_hand_x<-10.0f)
                  op_left_hand_x=-10.0f;
              }
              else if(key == GLFW_KEY_O){
                op_left_hand_y+=1.0f;
                if(op_left_hand_y>180.0f)
                  op_left_hand_y=180.0f;
              }
              else if(key == GLFW_KEY_K){
                op_left_hand_y-=1.0f;
                if(op_left_hand_y<-180.0f)
                  op_left_hand_y=-180.0f;
              }
              else if(key == GLFW_KEY_P){
                op_left_hand_z+=1.0f;
                if(op_left_hand_z>10.0f)
                  op_left_hand_z=10.0f;
              }
              else if(key == GLFW_KEY_L){
                op_left_hand_z-=1.0f;
                if(op_left_hand_z<-10.0f)
                  op_left_hand_z=-10.0f;
              }
            }
            else if(part == 2){
              if(key == GLFW_KEY_Y){
                op_left_hip_z+=1.0f;
                if(op_left_hip_z>10.0f)
                  op_left_hip_z=10.0f;
              }
              else if(key == GLFW_KEY_G){
                op_left_hip_z-=1.0f;
                if(op_left_hip_z<-10.0f)
                  op_left_hip_z=-10.0f;
              }
              else if(key == GLFW_KEY_U){
                op_left_hip_x+=1.0f;
                if(op_left_hip_x>90.0f)
                  op_left_hip_x=90.0f;
              }
              else if(key == GLFW_KEY_H){
                op_left_hip_x-=1.0f;
                if(op_left_hip_x<-90.0f)
                  op_left_hip_x=-90.0f;
              }
              else if(key == GLFW_KEY_I){
                op_left_hip_y+=1.0f;
                if(op_left_hip_y>98.0f)
                  op_left_hip_y=98.0f;
              }
              else if(key == GLFW_KEY_J){
                op_left_hip_y-=1.0f;
                if(op_left_hip_y<0.0f)
                  op_left_hip_y=0.0f;
              }
            }
            else if(part == 3){
              if(key == GLFW_KEY_Y){
                op_left_knee_y+=1.0f;
                if(op_left_knee_y>113.0f)
                  op_left_knee_y=113.0f;
              }
              else if(key == GLFW_KEY_G){
                op_left_knee_y-=1.0f;
                if(op_left_knee_y<0.0f)
                  op_left_knee_y=0.0f;
              }
              else if(key == GLFW_KEY_U){
                op_left_knee_x+=1.0f;
                if(op_left_knee_x>180.0f)
                  op_left_knee_x=180.0f;
              }
              else if(key == GLFW_KEY_H){
                op_left_knee_x-=1.0f;
                if(op_left_knee_x<-180.0f)
                  op_left_knee_x=-180.0f;
              }
              else if(key == GLFW_KEY_I){
                op_left_foot_y+=1.0f;
                if(op_left_foot_y>5.0f)
                  op_left_foot_y=5.0f;
              }
              else if(key == GLFW_KEY_J){
                op_left_foot_y-=1.0f;
                if(op_left_foot_y<-5.0f)
                  op_left_foot_y=-5.0f;
              }
              else if(key == GLFW_KEY_O){
                op_left_foot_x+=1.0f;
                if(op_left_foot_x>240.0f)
                  op_left_foot_x=240.0f;
              }
              else if(key == GLFW_KEY_K){
                op_left_foot_x-=1.0f;
                if(op_left_foot_x<0.0f)
                  op_left_foot_x=0.0f;
              }
              else if(key == GLFW_KEY_P){
                op_left_foot_z+=1.0f;
                if(op_left_foot_z>10.0f)
                  op_left_foot_z=10.0f;
              }
              else if(key == GLFW_KEY_L){
                op_left_foot_z-=1.0f;
                if(op_left_foot_z<-10.0f)
                  op_left_foot_z=-10.0f;
              }
            }
          }
        }
      }
    }
  }

  int save_fb_toimage(GLFWwindow* window, int num)
  {
    num--;
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    char name[25] = "./frames/frame-00000.jpg";

    for(int i=19; i>=15; i--){
      name[i] += num%10;
      num/=10;
    }

    GLsizei num_channels = 4;
    GLsizei ch_width = num_channels * width;
    GLsizei bufferSize = ch_width * height;

    std::vector<char> buffer(bufferSize);
    glPixelStorei(GL_PACK_ALIGNMENT, 4);
    glReadBuffer(GL_BACK);
    glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, buffer.data());

    stbi_flip_vertically_on_write(true);
    int num_bytes_written = stbi_write_jpg(name, width, height, num_channels, buffer.data(), 100);

    return num_bytes_written;
  }
};  
  


