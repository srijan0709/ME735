#version 330

#define num_lights 7

const float rad[num_lights] = float[num_lights](0.0, 0.0, 1.3, 0.5, 0.5, 0.0, 0.0);

in vec4 color;
in vec3 pos;
in vec3 normal;
out vec4 frag_color;

uniform sampler2D texture;

uniform vec3 eye_pos;

uniform vec4 diffuse;
uniform vec4 ambient;
uniform vec4 specular;
uniform float shininess;

uniform vec3 lights[num_lights];
uniform vec3 lights_dir[num_lights];
uniform float lights_spread[num_lights];
uniform float lights_intensity[num_lights];

void main () 
{
  vec4 spec_net = vec4(0.0);
  float intensity_net = 0.0;

  float intensity;

  vec3 lightDir;
  vec3 eye = normalize(eye_pos-pos);
  vec3 n = normalize(normal);

  for(int i=0; i<num_lights; i++){
    // net_lights_intensity += lights_intensity[i];
    lightDir = normalize(lights[i]-pos); 

    if((dot(lightDir, lights_dir[i]) > lights_spread[i]) || (dot(lightDir, lights[i]-pos) < rad[i])){
      intensity =  lights_intensity[i] * max( dot(n, lightDir), 0.0);

      // Compute specular component only if light falls on vertex
      if(intensity > 0.0)
      {
        vec3 h = normalize(lightDir + eye);
        spec_net += lights_intensity[i] * (specular * pow(max(dot(h,n), 0.0), shininess));
      }  

      intensity_net += intensity;
    }
  } 

  vec4 illumination = min((intensity_net * diffuse  + spec_net) + ambient, 1.0);

  if(color.w == 0){
    frag_color = illumination * texture2D(texture, color.xy);  
  }
  else{
    frag_color = illumination * color;
  }
}
