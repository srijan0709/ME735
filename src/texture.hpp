#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_
GLuint LoadTexture( const char * filename, int width, int height , int chan);
void FreeTexture( GLuint texture );
#endif 
