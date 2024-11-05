/*
  Based on tutorial 6 by Parag C
*/


#include "vector_prime.hpp"
#include "optimus_prime.hpp"
#include "texture.hpp"
#include <iostream>

#include <fstream>

#define time_step 0.025 //40 fps
#define num_lights 7
#define factor 8

GLuint shaderProgram;
GLuint vp_vbo[vp::buff_size], vp_vao[vp::buff_size];
GLuint op_vbo[op::buff_size], op_vao[op::buff_size];
GLuint tex_optimus_prime, tex_skybox[6], tex_g;
GLuint texture;
GLuint lights, lights_dir, lights_spread, lights_intensity;
GLuint eye_pos;

GLfloat lights_arr[num_lights*3];
GLfloat lights_dir_arr[num_lights*3];
GLfloat lights_spread_arr[num_lights];
GLfloat lights_intensity_arr[num_lights];
GLfloat eye_pos_arr[3];

//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------
GLuint sb_vao, g_vao, sb_vbo, g_vbo;
glm::mat4 sb_rotations[6];

void init_skybox(GLuint vPosition, GLuint vColor, GLuint vNormal){
  GLfloat size = factor * 100.0f;
  glm::vec4 sb_vertices[] = {glm::vec4(-size, size, -size, 1.0f),
                             glm::vec4(size, size, -size, 1.0f),
                             glm::vec4(-size, -size, -size, 1.0f),
                             glm::vec4(size, -size, -size, 1.0f),
                            };
  glm::vec4 sb_positions[6] = {sb_vertices[0],
                               sb_vertices[1],
                               sb_vertices[2],
                               sb_vertices[2],
                               sb_vertices[1],
                               sb_vertices[3],
                              };
  glm::vec4 sb_colors[6];
  glm::vec3 sb_normals[6];

  for(int i=0; i<6; i++){
    sb_normals[i]=glm::vec3(0.0f, 1.0f, 0.0f);
  }

  sb_colors[0] = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
  sb_colors[1] = glm::vec4(1.0f, 1.0f, 0.0f, 0.0f);
  sb_colors[2] = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
  sb_colors[3] = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
  sb_colors[4] = glm::vec4(1.0f, 1.0f, 0.0f, 0.0f);
  sb_colors[5] = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);

  glGenVertexArrays (1, &sb_vao);
  glGenBuffers (1, &sb_vbo);


  glBindVertexArray (sb_vao);
  glBindBuffer (GL_ARRAY_BUFFER, sb_vbo);
  
  //Copy the points into the current buffer
  glBufferData (GL_ARRAY_BUFFER, sizeof(sb_positions) + sizeof(sb_colors) + sizeof(sb_normals), NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(sb_positions), sb_positions);
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(sb_positions), sizeof(sb_colors), sb_colors );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(sb_positions) + sizeof(sb_colors), sizeof(sb_normals), sb_normals );

  // set up vertex array
  glEnableVertexAttribArray( vPosition );
  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  
  glEnableVertexAttribArray( vColor );
  glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(sb_positions)) );

  glEnableVertexAttribArray( vNormal );
  glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(sb_positions) + sizeof(sb_colors)) );

  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, tex_skybox[0]);
  glActiveTexture(GL_TEXTURE2);
  glBindTexture(GL_TEXTURE_2D, tex_skybox[1]);
  glActiveTexture(GL_TEXTURE3);
  glBindTexture(GL_TEXTURE_2D, tex_skybox[2]);
  glActiveTexture(GL_TEXTURE4);
  glBindTexture(GL_TEXTURE_2D, tex_skybox[3]);
  glActiveTexture(GL_TEXTURE5);
  glBindTexture(GL_TEXTURE_2D, tex_skybox[4]);
  glActiveTexture(GL_TEXTURE6);
  glBindTexture(GL_TEXTURE_2D, tex_skybox[5]);
  glActiveTexture(GL_TEXTURE7);
  glBindTexture(GL_TEXTURE_2D, tex_g);
  glActiveTexture(GL_TEXTURE0);
  // glUniform1i(texture, 1);

  sb_rotations[0] = glm::mat4(1.0f); //back
  sb_rotations[1] = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)); //top
  sb_rotations[2] = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f)); //bot
  sb_rotations[3] = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)); //left
  sb_rotations[4] = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f)); //right
  sb_rotations[5] = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)); //front


  for(int i=0; i<6; i++){
    sb_positions[i] = sb_rotations[1] * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, factor*100.0f)) * sb_positions[i];
    sb_colors[i][0] = sb_colors[i][0]*10*factor;
    sb_colors[i][1] = sb_colors[i][1]*10*factor;
  }

  glGenVertexArrays (1, &g_vao);
  glGenBuffers (1, &g_vbo);
  glBindVertexArray (g_vao);
  glBindBuffer (GL_ARRAY_BUFFER, g_vbo);
  
  //Copy the points into the current buffer
  glBufferData (GL_ARRAY_BUFFER, sizeof(sb_positions) + sizeof(sb_colors) + sizeof(sb_normals), NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(sb_positions), sb_positions);
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(sb_positions), sizeof(sb_colors), sb_colors );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(sb_positions) + sizeof(sb_colors), sizeof(sb_normals), sb_normals );

  // set up vertex array
  glEnableVertexAttribArray( vPosition );
  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  
  glEnableVertexAttribArray( vColor );
  glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(sb_positions)) );

  glEnableVertexAttribArray( vNormal );
  glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(sb_positions) + sizeof(sb_colors)) );
}

void draw_skybox(){
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(model_matrix));
  glUniform4fv(diffuse, 1, glm::value_ptr(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));
  glUniform4fv(ambient, 1, glm::value_ptr(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
  glUniform4fv(specular, 1, glm::value_ptr(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));
  glUniform1f(shininess, 0.0f);

  if((lights_intensity_arr[0] + lights_intensity_arr[1] + lights_intensity_arr[5] + lights_intensity_arr[6]) == 0)
    glUniform4fv(ambient, 1, glm::value_ptr(glm::vec4(0.125f, 0.125f, 0.125f, 1.0f)));

  glm::mat4 modelview_matrix = view_matrix*model_matrix;
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(glm::mat3(model_matrix)));
  glBindVertexArray (sb_vao);

  for(int i=0; i<6; i++){
    glUniform1i(texture, i+1);
    glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix * sb_rotations[i]));
    glDrawArrays(GL_TRIANGLES, 0, 6);
  }

  glUniform1i(texture, 7);
  glUniform4fv(diffuse, 1, glm::value_ptr(glm::vec4(0.8f, 0.8f, 0.8f, 1.0f)));
  glUniform4fv(ambient, 1, glm::value_ptr(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f)));
  glUniform4fv(specular, 1, glm::value_ptr(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));

  glBindVertexArray (g_vao);
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(glm::mat3(model_matrix)));
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(model_matrix));
  glDrawArrays(GL_TRIANGLES, 0, 6);

  glUniform1i(texture, 0);
}

GLuint tree_vao, tree_vbo;
const int num_trees = factor * 20;
glm::mat4 translate_mat[num_trees];

void init_tree(GLuint vPosition, GLuint vColor, GLuint vNormal){
  GLfloat size = 5.0f;
  GLfloat width = 1.0f;

  srand(42);
  for(int i=0; i<num_trees; i++){
    GLfloat x = (rand()%(factor*200))-factor*100;
    GLfloat z = (rand()%(factor*200))-factor*100;
    GLfloat rot = glm::radians((float)(rand()%45));
    translate_mat[i] = glm::translate(glm::mat4(1.0f), glm::vec3(x, 0.0f, z)) * glm::rotate(glm::mat4(1.0f), rot, glm::vec3(0.0f, 1.0f, 0.0f));
  }

  const glm::vec4 tree_vertices[] = {glm::vec4(-1.0f, size , width, 1.0f),
                                     glm::vec4(1.0f, size, width, 1.0f),
                                     glm::vec4(1.0f, 0.0f, width, 1.0f),
                                     glm::vec4(-1.0f, 0.0f, width, 1.0f),

                                     glm::vec4(1.0f, size, -width, 1.0f),
                                     glm::vec4(-1.0f, size, -width, 1.0f),
                                     glm::vec4(-1.0f, 0.0f, -width, 1.0f),
                                     glm::vec4(1.0f, 0.0f, -width, 1.0f),

                                    glm::vec4(-2.0f, size , -2.0f, 1.0f),
                                    glm::vec4(-2.0f, size, 2.0f, 1.0f),
                                    glm::vec4(2.0f, size, 2.0f, 1.0f),
                                    glm::vec4(2.0f, size, -2.0f, 1.0f),

                                    glm::vec4(0.0f, size + 15.0f, 0.0f, 1.0f), //top of pyramid
                                   };
  const glm::vec4 tree_positions[60] = {tree_vertices[0],
                                    tree_vertices[1],
                                    tree_vertices[2],
                                    tree_vertices[0],
                                    tree_vertices[2],
                                    tree_vertices[3], //front

                                    tree_vertices[4],
                                    tree_vertices[5],
                                    tree_vertices[6],
                                    tree_vertices[4],
                                    tree_vertices[6],
                                    tree_vertices[7],//back

                                    tree_vertices[1],
                                    tree_vertices[4],
                                    tree_vertices[7],
                                    tree_vertices[1],
                                    tree_vertices[7],
                                    tree_vertices[2], //side

                                    tree_vertices[5],
                                    tree_vertices[0],
                                    tree_vertices[3],
                                    tree_vertices[5],
                                    tree_vertices[3],
                                    tree_vertices[6], //side

                                    tree_vertices[0],
                                    tree_vertices[5],
                                    tree_vertices[4],
                                    tree_vertices[0],
                                    tree_vertices[4],
                                    tree_vertices[1], //top

                                    tree_vertices[2],
                                    tree_vertices[7],
                                    tree_vertices[6],
                                    tree_vertices[2],
                                    tree_vertices[6],
                                    tree_vertices[3], //bottom

                                    tree_vertices[8],
                                    tree_vertices[9],
                                    tree_vertices[10],
                                    tree_vertices[8],
                                    tree_vertices[10],
                                    tree_vertices[11], //top

                                    tree_vertices[9],
                                    tree_vertices[8],
                                    tree_vertices[12],
                                    tree_vertices[10],
                                    tree_vertices[9],
                                    tree_vertices[12],
                                    tree_vertices[11],
                                    tree_vertices[10],
                                    tree_vertices[12],
                                    tree_vertices[8],
                                    tree_vertices[11],
                                    tree_vertices[12], 
                                   };
  glm::vec4 tree_colors[60];
  glm::vec3 tree_normals[60];

  for(int i=0; i<60; i+=3){
    tree_normals[i] = glm::cross(glm::vec3(tree_positions[i+2]-tree_positions[i]),glm::vec3(tree_positions[i+1]-tree_positions[i]));
    tree_normals[i+1] = tree_normals[i];
    tree_normals[i+2] = tree_normals[i];
  }



  for(int i=0; i<36; i++){
    tree_colors[i] = glm::vec4(0.5f, 0.35f, 0.0f, 1.0f);
  }

  for(int i=36; i<60; i++){
    tree_colors[i] = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
  }


  glGenVertexArrays (1, &tree_vao);
  glGenBuffers (1, &tree_vbo);


  glBindVertexArray (tree_vao);
  glBindBuffer (GL_ARRAY_BUFFER, tree_vbo);
  
  //Copy the points into the current buffer
  glBufferData (GL_ARRAY_BUFFER, sizeof(tree_positions) + sizeof(tree_colors) + sizeof(tree_normals), NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(tree_positions), tree_positions);
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(tree_positions), sizeof(tree_colors), tree_colors );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(tree_positions) + sizeof(tree_colors), sizeof(tree_normals), tree_normals );

  // set up vertex array
  glEnableVertexAttribArray( vPosition );
  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  
  glEnableVertexAttribArray( vColor );
  glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(tree_positions)) );

  glEnableVertexAttribArray( vNormal );
  glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(tree_positions) + sizeof(tree_colors)) );
}

void draw_tree(){
  glBindVertexArray (tree_vao);

  glUniform4fv(diffuse, 1, glm::value_ptr(glm::vec4(0.875f, 0.875f, 0.875f, 1.0f)));
  glUniform4fv(ambient, 1, glm::value_ptr(glm::vec4(0.125f, 0.125f, 0.125f, 1.0f)));
  glUniform4fv(specular, 1, glm::value_ptr(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));
  glUniform1f(shininess, 0.0f);

  glm::mat4 modelview_matrix = view_matrix*model_matrix;

  for(int i=0; i<num_trees; i++){
    glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(model_matrix * translate_mat[i]));
    glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(glm::mat3(model_matrix * translate_mat[i])));
    glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix * translate_mat[i]));

    glDrawArrays(GL_TRIANGLES, 0, 60);
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------

void init_lights(int light_no, glm::vec3 light_pos, glm::vec3 light_dir, GLfloat spread, GLfloat intensity){
  lights_spread_arr[light_no] = spread;
  lights_intensity_arr[light_no] = intensity;

  light_no *= 3;

  lights_arr[light_no] = light_pos[0];
  lights_arr[light_no+1] = light_pos[1];
  lights_arr[light_no+2] = light_pos[2];

  lights_dir_arr[light_no] = light_dir[0];
  lights_dir_arr[light_no+1] = light_dir[1];
  lights_dir_arr[light_no+2] = light_dir[2];
}

void initBuffersGL(void)
{
  // Load shaders and use the resulting shader program
  std::string vertex_shader_file("src/vshader.glsl");
  std::string fragment_shader_file("src/fshader.glsl");

  std::vector<GLuint> shaderList;
  shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  shaderProgram = csX75::CreateProgramGL(shaderList);
  glUseProgram( shaderProgram );

  // getting the attributes from the shader program
  GLuint vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
  GLuint vColor = glGetAttribLocation( shaderProgram, "vColor" ); 
  GLuint vNormal = glGetAttribLocation( shaderProgram, "vNormal" ); 
  uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");
  normalMatrix =  glGetUniformLocation( shaderProgram, "normalMatrix");
  viewMatrix = glGetUniformLocation( shaderProgram, "viewMatrix");

  diffuse = glGetUniformLocation( shaderProgram, "diffuse");
  ambient = glGetUniformLocation( shaderProgram, "ambient");
  specular = glGetUniformLocation( shaderProgram, "specular");
  shininess = glGetUniformLocation( shaderProgram, "shininess");

  texture = glGetUniformLocation( shaderProgram, "texture");

  lights = glGetUniformLocation( shaderProgram, "lights");
  lights_dir = glGetUniformLocation( shaderProgram, "lights_dir");
  lights_spread = glGetUniformLocation( shaderProgram, "lights_spread");
  lights_intensity = glGetUniformLocation( shaderProgram, "lights_intensity");

  eye_pos = glGetUniformLocation( shaderProgram, "eye_pos");

  glGenVertexArrays (vp::buff_size, vp_vao);
  glGenBuffers (vp::buff_size, vp_vbo);
  vp::init_vector_prime(vp_vao, vp_vbo, vPosition, vColor, vNormal);

  glGenVertexArrays (op::buff_size, op_vao);
  glGenBuffers (op::buff_size, op_vbo);
  op::init_optimus_prime(op_vao, op_vbo, vPosition, vColor, vNormal);

  // tex_skybox=LoadTexture("./img/skybox.bmp", 2048, 1536, 1); 
  // tex_skybox=LoadTexture("./img/sb2.bmp", 1400, 1050, 1); 
  tex_skybox[0]=LoadTexture("./img/skybox/back.bmp", 512, 512, 2); 
  tex_skybox[1]=LoadTexture("./img/skybox/top.bmp", 512, 512, 2); 
  tex_skybox[2]=LoadTexture("./img/skybox/bottom.bmp", 512, 512, 2); 
  tex_skybox[3]=LoadTexture("./img/skybox/left.bmp", 512, 512, 2); 
  tex_skybox[4]=LoadTexture("./img/skybox/right.bmp", 512, 512, 2); 
  tex_skybox[5]=LoadTexture("./img/skybox/front.bmp", 512, 512, 2); 

  tex_g = LoadTexture("./img/grass.bmp", 1600, 1600, 3);

  glBindTexture(GL_TEXTURE_2D, tex_skybox[0]);

  tex_optimus_prime=LoadTexture("./img/Parser_front_1.bmp", 370, 596, 0); // 596, 370
  glBindTexture(GL_TEXTURE_2D, tex_optimus_prime);

  init_skybox(vPosition, vColor, vNormal);
  init_tree(vPosition, vColor, vNormal);
}

const glm::vec3 g1_pos = glm::vec3(400.0f, 400.0f, 400.0f);
const glm::vec3 g2_pos = glm::vec3(-400.0f, 400.0f, 400.0f);
const glm::vec3 g3_pos = glm::vec3(400.0f, 400.0f, -400.0f);
const glm::vec3 g4_pos = glm::vec3(-400.0f, 400.0f, -400.0f);

const glm::vec3 g_dir = glm::vec3(1.0f, 0.0f, 0.0f);
const GLfloat g_spread = -1.0f;

void renderGL(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(xrot), glm::vec3(1.0f,0.0f,0.0f));
  rotation_matrix = glm::rotate(rotation_matrix, glm::radians(yrot), glm::vec3(0.0f,1.0f,0.0f));
  model_matrix = rotation_matrix;//*trasform;
  
  //Update the lights
  vp::update_lights_camera();
  op::update_lights_camera();

  if(lights_cam & 0b01){
    //Creating the lookat and the up vectors for the camera
    c_rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(c_zrot), glm::vec3(0.0f,0.0f,1.0f));
    c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_xrot), glm::vec3(1.0f,0.0f,0.0f));
    c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_yrot), glm::vec3(0.0f,1.0f,0.0f));

    glm::vec3 c_pos = glm::vec3(c_xpos,c_ypos,c_zpos);
    glm::vec4 c_dir = glm::vec4(0.0f, 0.0f, -1.0f, 1.0)*c_rotation_matrix;
    glm::vec4 c_up = glm::vec4(0.0f, 1.0f, 0.0f, 1.0)*c_rotation_matrix;
    //Creating the lookat matrix
    lookat_matrix = glm::lookAt(c_pos, c_pos+glm::vec3(c_dir), glm::vec3(c_up));

    eye_pos_arr[0] = c_pos[0];
    eye_pos_arr[1] = c_pos[1];
    eye_pos_arr[2] = c_pos[2];
  }
  else if(lights_cam & 0b10){
    lookat_matrix = glm::lookAt(vp_eye, vp_cent, vp_up);
    eye_pos_arr[0] = vp_eye[0];
    eye_pos_arr[1] = vp_eye[1];
    eye_pos_arr[2] = vp_eye[2];
  }//TODO
  else{
    lookat_matrix = glm::lookAt(op_eye, op_cent, op_up);
    eye_pos_arr[0] = op_eye[0];
    eye_pos_arr[1] = op_eye[1];
    eye_pos_arr[2] = op_eye[2];
  }

  //creating the projection matrix
  // projection_matrix = glm::frustum(-1.0, 1.0, -1.0, 1.0, 1.0, 5.0);
  projection_matrix = glm::perspective(glm::radians(90.0), (width*1.0)/height, 0.1, factor*200.0);
  // projection_matrix = glm::ortho(-width/100.0/scale, width/100.0/scale, -height/100.0/scale, height/100.0/scale, 0.0, 200.0);

  view_matrix = projection_matrix*lookat_matrix;

  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(model_matrix));

  //global lights def
  //Gloabl Light 1
  if(lights_cam & 0b000100)
    init_lights(0, g1_pos, g_dir, g_spread ,1.0f);
  else
    init_lights(0, g1_pos, g_dir, g_spread ,0.0f);

  //Global Light 2
  if(lights_cam & 0b001000)
    init_lights(1, g2_pos, g_dir, g_spread ,1.0f);
  else
    init_lights(1, g2_pos, g_dir, g_spread ,0.0f);

  //VP Headlights
  if(lights_cam & 0b010000)
    init_lights(2, vp_light_pos, vp_light_dir, vp_light_spread, 1.0f);
  else
    init_lights(2, vp_light_pos, vp_light_dir, vp_light_spread, 0.0f);

  //OP Headlights
  if(lights_cam & 0b100000){
    init_lights(3, op_light1_pos, op_light_dir, op_light_spread, 1.0f);
    init_lights(4, op_light2_pos, op_light_dir, op_light_spread, 1.0f);
  }
  else{
    init_lights(3, op_light1_pos, op_light_dir, op_light_spread, 0.0f);
    init_lights(4, op_light2_pos, op_light_dir, op_light_spread, 0.0f);
  }

  //Global Light 3
  if(lights_cam & 0b01000000)
    init_lights(5, g3_pos, g_dir, g_spread ,1.0f);
  else
    init_lights(5, g3_pos, g_dir, g_spread ,0.0f);

  //Global Light 4
  if(lights_cam & 0b10000000)
    init_lights(6, g4_pos, g_dir, g_spread ,1.0f);
  else
    init_lights(6, g4_pos, g_dir, g_spread ,0.0f);

  glUniform3fv(lights, num_lights, lights_arr);
  glUniform3fv(lights_dir, num_lights, lights_dir_arr);
  glUniform1fv(lights_spread, num_lights, lights_spread_arr);
  glUniform1fv(lights_intensity, num_lights, lights_intensity_arr);
  glUniform3fv(eye_pos, 1, eye_pos_arr);

  //Surface details
  glUniform4fv(diffuse, 1, glm::value_ptr(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)));
  glUniform4fv(ambient, 1, glm::value_ptr(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f)));
  glUniform4fv(specular, 1, glm::value_ptr(glm::vec4(0.4f, 0.4f, 0.4f, 1.0f)));
  glUniform1f(shininess, 10.0f);
  // Draw the transformers
  vp::draw_vector_prime(vp_vao, vp_vbo);
  op::draw_optimus_prime(op_vao, op_vbo);

  //Draw Skybox
  draw_skybox();

  //Draw Trees
  draw_tree();
}

int num_frames = 0;
const int num_params = 8+55+63;
uint *lights_cam_frame = NULL;
GLint *vp_form = NULL;
GLfloat (*params)[num_params] = NULL;

void read_frames(){
  std::fstream frames("./keyframes.txt", std::fstream::in);
  frames >> num_frames;
  
  int frames_loaded = 0;

  //Deallocating previously allocated memory
  free(lights_cam_frame);
  free(vp_form);
  free(params);

  //Allocating memory
  lights_cam_frame = (uint*)malloc(sizeof(uint[num_frames]));
  vp_form = (GLint*)malloc(sizeof(GLint[num_frames]));
  params = (GLfloat(*)[num_params])malloc(sizeof(GLfloat[num_frames][num_params]));

  int prev_fno = 0;
  int fno;
  while(frames >> fno){
    fno--;

    if(fno < prev_fno || fno >= num_frames){
      std::cout<<"Error in Line "<<frames_loaded+2<<std::endl;
      num_frames = 0;
      frames_loaded = 0;
      prev_fno = -1;
      break;
    }
    //Reading the frame info
    frames >> lights_cam_frame[fno];

    frames >> vp_form[fno];

    for(int i=0;i<num_params; i++){
      frames >> params[fno][i];
    }

    //Loading the intermediate frames
    int fdif = fno - prev_fno;
    for(int i = 1; i<fdif; i++){
      lights_cam_frame[prev_fno+i] = lights_cam_frame[prev_fno];
      vp_form[prev_fno+i] = vp_form[prev_fno];
      for(int j=0; j<num_params; j++){
        params[prev_fno+i][j] = (i*params[fno][j] + (fdif-i)*params[prev_fno][j])/fdif;
      }
    }

    frames_loaded++;
    prev_fno = fno;
  }
  std::cout<<"Expected Number of Frames: "<<num_frames<<std::endl;
  std::cout<<"Number of Frames Loaded: "<<frames_loaded<<std::endl;
  std::cout<<"Total Number of Frames (Loaded + Interpolated): "<<prev_fno+1<<std::endl;

  if(num_frames < prev_fno)
    num_frames = prev_fno;
}

void load_frames(int fno){
  lights_cam = lights_cam_frame[fno];
  vp::vp_form = vp_form[fno];

  //Lights camera parameters
  int i = 0;
  xrot = params[fno][i+0];
  yrot = params[fno][i+1];
  c_xrot = params[fno][i+2];
  c_yrot = params[fno][i+3];
  c_zrot = params[fno][i+4];
  c_xpos = params[fno][i+5];
  c_ypos = params[fno][i+6];
  c_zpos = params[fno][i+7];

  //Vector Prime Parameters
  i += 8;
  vp_ship_rotate = params[fno][i+0];
  vp_head_translate = params[fno][i+1];
  vp_head_x = params[fno][i+2];
  vp_head_y = params[fno][i+3];
  vp_head_z = params[fno][i+4];
  vp_right_wing_wing_torso = params[fno][i+5];
  vp_right_wing_torso_torso = params[fno][i+6];
  vp_left_wing_wing_torso = params[fno][i+7];
  vp_left_wing_torso_torso = params[fno][i+8];
  vp_right_wing = params[fno][i+9];

  vp_left_wing = params[fno][i+10];
  vp_right_shoulder_translate = params[fno][i+11];
  vp_right_shoulder_x = params[fno][i+12];
  vp_right_shoulder_y = params[fno][i+13];
  vp_right_shoulder_z = params[fno][i+14];
  vp_left_shoulder_translate = params[fno][i+15];
  vp_left_shoulder_x = params[fno][i+16];
  vp_left_shoulder_y = params[fno][i+17];
  vp_left_shoulder_z = params[fno][i+18];
  vp_right_elbow_x = params[fno][i+19];

  vp_right_elbow_y = params[fno][i+20];
  vp_right_shoulder_pad = params[fno][i+21];
  vp_left_elbow_x = params[fno][i+22];
  vp_left_elbow_y = params[fno][i+23];
  vp_left_shoulder_pad = params[fno][i+24];
  vp_right_foot_x = params[fno][i+25];
  vp_right_foot_y = params[fno][i+26];
  vp_right_foot_z = params[fno][i+27];
  vp_left_foot_x = params[fno][i+28];
  vp_left_foot_y = params[fno][i+29];

  vp_left_foot_z = params[fno][i+30];
  vp_right_knee_x = params[fno][i+31];
  vp_right_knee_y = params[fno][i+32];
  vp_left_knee_x = params[fno][i+33];
  vp_left_knee_y = params[fno][i+34];
  vp_right_hip_x = params[fno][i+35];
  vp_right_hip_y = params[fno][i+36];
  vp_right_hip_z = params[fno][i+37];
  vp_left_hip_x = params[fno][i+38];
  vp_left_hip_y = params[fno][i+39];

  vp_left_hip_z = params[fno][i+40];
  vp_right_hand_guard = params[fno][i+41];
  vp_left_hand_guard = params[fno][i+42];
  vp_right_hand_x = params[fno][i+43];
  vp_right_hand_y = params[fno][i+44];
  vp_right_hand_z = params[fno][i+45];
  vp_left_hand_x = params[fno][i+46];
  vp_left_hand_y = params[fno][i+47];
  vp_left_hand_z = params[fno][i+48];
  vp_torso_x = params[fno][i+49];

  vp_torso_y = params[fno][i+50];
  vp_torso_z = params[fno][i+51];
  vp_xpos = params[fno][i+52];
  vp_ypos = params[fno][i+53];
  vp_zpos = params[fno][i+54];

  //Optimus Prime
  i += 55;
  op_xpos= params[fno][i+0];
  op_ypos= params[fno][i+1];
  op_zpos= params[fno][i+2];
  op_ship_rotate_x = params[fno][i+3];
  op_ship_rotate_y = params[fno][i+4];
  op_ship_rotate_z = params[fno][i+5];
  op_ship_translate = params[fno][i+6];
  op_lower_torso_rotate_x = params[fno][i+7];
  op_lower_torso_rotate_y = params[fno][i+8];
  op_lower_torso_rotate_z = params[fno][i+9];
  op_right_upperarm_x = params[fno][i+10];
  op_right_upperarm_y = params[fno][i+11];
  op_right_upperarm_z = params[fno][i+12];
  op_left_upperarm_x = params[fno][i+13];
  op_left_upperarm_y = params[fno][i+14];
  op_left_upperarm_z = params[fno][i+15];
  op_head_translate = params[fno][i+16];
  op_head_x = params[fno][i+17];
  op_head_y = params[fno][i+18];
  op_head_z = params[fno][i+19];
  op_shoulder_translate = params[fno][i+20];
  op_right_shoulder_x = params[fno][i+21];
  op_right_shoulder_y = params[fno][i+22];
  op_right_shoulder_z = params[fno][i+23];
  op_left_shoulder_x = params[fno][i+24];
  op_left_shoulder_y = params[fno][i+25];
  op_left_shoulder_z = params[fno][i+26];
  op_wrist_translate = params[fno][i+27];
  op_right_wrist_x = params[fno][i+28];
  op_right_wrist_y = params[fno][i+29];
  op_right_wrist_z = params[fno][i+30];
  op_left_wrist_x = params[fno][i+31];
  op_left_wrist_y = params[fno][i+32];
  op_left_wrist_z = params[fno][i+33];
  op_right_elbow_x = params[fno][i+34];
  op_right_elbow_y = params[fno][i+35];
  op_left_elbow_x = params[fno][i+36];
  op_left_elbow_y = params[fno][i+37];
  op_right_foot_x = params[fno][i+38];
  op_right_foot_y = params[fno][i+39];
  op_right_foot_z = params[fno][i+40];
  op_left_foot_x = params[fno][i+41];
  op_left_foot_y = params[fno][i+42];
  op_left_foot_z = params[fno][i+43];
  op_right_knee_x = params[fno][i+44];
  op_right_knee_y = params[fno][i+45];
  op_left_knee_x = params[fno][i+46];
  op_left_knee_y = params[fno][i+47];
  op_right_hip_x = params[fno][i+48];
  op_right_hip_y = params[fno][i+49];
  op_right_hip_z = params[fno][i+50];
  op_left_hip_x = params[fno][i+51];
  op_left_hip_y = params[fno][i+52];
  op_left_hip_z = params[fno][i+53];
  op_right_hand_x = params[fno][i+54];
  op_right_hand_y = params[fno][i+55];
  op_right_hand_z = params[fno][i+56];
  op_left_hand_x = params[fno][i+57];
  op_left_hand_y = params[fno][i+58];
  op_left_hand_z = params[fno][i+59];
  op_torso_x = params[fno][i+60];
  op_torso_y = params[fno][i+61];
  op_torso_z = params[fno][i+62];
}

void print_frames(std::fstream &frames){
  // std::fstream frames("./keyframes_temp.txt", std::fstream::out);
  std::cout<<"Enter frame number"<<std::endl;
  int fno;
  std::cin>>fno;

  //Frame Number - 0 (1)
  frames<<fno<<" "; //1

  //Lights , camera details - 1 (1)
  frames<<lights_cam<<" "; //1

  //VP form
  frames<<vp::vp_form<<" ";

  //Rotation Parameters and Camera Parameters - 2 (8)
  frames<<xrot<<" "<<yrot<<" ";   //2
  frames<<c_xrot<<" "<<c_yrot<<" "<<c_zrot<<" ";   //3
  frames<<c_xpos<<" "<<c_ypos<<" "<<c_zpos<<" ";   //3

  //Vector Prime - 12 (55+1)
  frames<<vp_ship_rotate<<" ";  //1
  frames<<vp_head_translate<<" "<<vp_head_x<<" "<<vp_head_y<<" "<<vp_head_z<<" "; //4
  frames<<vp_right_wing_wing_torso<<" "<<vp_right_wing_torso_torso<<" "<<vp_left_wing_wing_torso<<" "<<vp_left_wing_torso_torso<<" "; //4
  frames<<vp_right_wing<<" "<<vp_left_wing<<" "; //2
  frames<<vp_right_shoulder_translate<<" "<<vp_right_shoulder_x<<" "<<vp_right_shoulder_y<<" "<<vp_right_shoulder_z<<" "; //4
  frames<<vp_left_shoulder_translate<<" "<<vp_left_shoulder_x<<" "<<vp_left_shoulder_y<<" "<<vp_left_shoulder_z<<" "; //4
  frames<<vp_right_elbow_x<<" "<<vp_right_elbow_y<<" "<<vp_right_shoulder_pad<<" "; //3
  frames<<vp_left_elbow_x<<" "<<vp_left_elbow_y<<" "<<vp_left_shoulder_pad<<" "; //3
  frames<<vp_right_foot_x<<" "<<vp_right_foot_y<<" "<<vp_right_foot_z<<" "; //3
  frames<<vp_left_foot_x<<" "<<vp_left_foot_y<<" "<<vp_left_foot_z<<" "; //3
  frames<<vp_right_knee_x<<" "<<vp_right_knee_y<<" "; //2
  frames<<vp_left_knee_x<<" "<<vp_left_knee_y<<" "; //2
  frames<<vp_right_hip_x<<" "<<vp_right_hip_y<<" "<<vp_right_hip_z<<" "; //3
  frames<<vp_left_hip_x<<" "<<vp_left_hip_y<<" "<<vp_left_hip_z<<" "; //3
  frames<<vp_right_hand_guard<<" "<<vp_left_hand_guard<<" "; //2
  frames<<vp_right_hand_x<<" "<<vp_right_hand_y<<" "<<vp_right_hand_z<<" "; //3
  frames<<vp_left_hand_x<<" "<<vp_left_hand_y<<" "<<vp_left_hand_z<<" "; //3
  frames<<vp_torso_x<<" "<<vp_torso_y<<" "<<vp_torso_z<<" "; //3
  frames<<vp_xpos<<" "<<vp_ypos<<" "<<vp_zpos<<" "; //3

  //Optimus Prime - 67 (63)
  frames<<op_xpos<<" "<<op_ypos<<" "<<op_zpos<<" "; //3
  frames<<op_ship_rotate_x<<" "<<op_ship_rotate_y<<" "<<op_ship_rotate_z<<" "<<op_ship_translate<<" ";  //4
  frames<<op_lower_torso_rotate_x<<" "<<op_lower_torso_rotate_y<<" "<<op_lower_torso_rotate_z<<" ";  //3
  frames<<op_right_upperarm_x<<" "<<op_right_upperarm_y<<" "<<op_right_upperarm_z<<" "; //3
  frames<<op_left_upperarm_x<<" "<<op_left_upperarm_y<<" "<<op_left_upperarm_z<<" "; //3
  frames<<op_head_translate<<" "<<op_head_x<<" "<<op_head_y<<" "<<op_head_z<<" "; //4
  frames<<op_shoulder_translate<<" "<<op_right_shoulder_x<<" "<<op_right_shoulder_y<<" "<<op_right_shoulder_z<<" "; //4
  frames<<op_left_shoulder_x<<" "<<op_left_shoulder_y<<" "<<op_left_shoulder_z<<" "; //3
  frames<<op_wrist_translate<<" "<<op_right_wrist_x<<" "<<op_right_wrist_y<<" "<<op_right_wrist_z<<" "; //4
  frames<<op_left_wrist_x<<" "<<op_left_wrist_y<<" "<<op_left_wrist_z<<" "; //3
  frames<<op_right_elbow_x<<" "<<op_right_elbow_y<<" "; //2
  frames<<op_left_elbow_x<<" "<<op_left_elbow_y<<" "; //2
  frames<<op_right_foot_x<<" "<<op_right_foot_y<<" "<<op_right_foot_z<<" "; //3
  frames<<op_left_foot_x<<" "<<op_left_foot_y<<" "<<op_left_foot_z<<" "; //3
  frames<<op_right_knee_x<<" "<<op_right_knee_y<<" "; //2
  frames<<op_left_knee_x<<" "<<op_left_knee_y<<" "; //2
  frames<<op_right_hip_x<<" "<<op_right_hip_y<<" "<<op_right_hip_z<<" "; //3
  frames<<op_left_hip_x<<" "<<op_left_hip_y<<" "<<op_left_hip_z<<" "; //3
  frames<<op_right_hand_x<<" "<<op_right_hand_y<<" "<<op_right_hand_z<<" "; //3
  frames<<op_left_hand_x<<" "<<op_left_hand_y<<" "<<op_left_hand_z<<" "; //3
  frames<<op_torso_x<<" "<<op_torso_y<<" "<<op_torso_z<<" "; //3

  frames<<std::endl;
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
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  //This is for MacOSX - can be omitted otherwise
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
  //We don't want the old OpenGL 
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

  //! Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(width, height, "Assignment 3 - Transformers Animation", NULL, NULL);
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
  //Keyboard Callback
  glfwSetKeyCallback(window, csX75::key_callback);
  //Framebuffer resize callback
  glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  //Initialize GL state
  csX75::initGL();
  initBuffersGL();

  double time_prev = glfwGetTime();
  std::fstream frames("./keyframes_temp.txt", std::fstream::out);
  int playing = 0, frame_number = 0, saving = 0;

  // Loop until the user closes the window
  while (glfwWindowShouldClose(window) == 0)
    {  
      if(glfwGetTime()-time_prev >= time_step){

        time_prev=glfwGetTime();

        // Render here
        renderGL();

        if(saving == 1)
          csX75::save_fb_toimage(window, frame_number);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        if(keyframe_status>0){
          if(keyframe_status == 1){
            print_frames(frames);
            keyframe_status = 0;
            std::cout<<"Exited Keyframe Control"<<std::endl;
          }
          else if(keyframe_status == 2){
            read_frames();
            keyframe_status = 4;
          }
          else if(keyframe_status == 3){
            keyframe_status = 4;
            playing = 1;
          }
          else if(keyframe_status == 5){
            keyframe_status = 4;
            playing = 1;
            saving = 1;
          }
        }
        
        // Poll for and process events
        glfwPollEvents();

        if(playing == 1){
          if((saving == 1) && (width != 1280 || height != 720)){
            glfwSetWindowSize(window, 1280, 720);
            glViewport(0, 0, 1280, 720);
            width = 1280;
            height = 720;
          }
          if(frame_number >= num_frames){
            playing = 0;
            frame_number = 0;
            saving = 0;
          }
          else{
            load_frames(frame_number);
            frame_number++;
          }
        }
      }
    }
  
  FreeTexture(tex_optimus_prime);
  glfwTerminate();
  return 0;
}

//-------------------------------------------------------------------------

