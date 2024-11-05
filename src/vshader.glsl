#version 330

in vec4 vPosition;
in vec4 vColor;
in vec3 vNormal;

out vec4 color;
out vec3 pos;
out vec3 normal;

uniform mat4 uModelViewMatrix;
uniform mat3 normalMatrix;
uniform mat4 viewMatrix;

void main (void) 
{
  gl_Position = uModelViewMatrix * vPosition;
  
  pos = vec3(viewMatrix * vPosition);
  normal = normalMatrix * vNormal;
  color = vColor;
}
