#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <SOIL/SOIL.h>





GLboolean isKeyDownZ = false;
GLboolean isKeyDownX = false;
GLboolean isKeyDownI = false;
GLboolean isKeyDownJ = false;
GLboolean isKeyDownL = false;
GLboolean isKeyDownK = false;
GLboolean isKeyDownO = false;
GLboolean isKeyDownP = false;
GLboolean isKeyDownC = false;
GLboolean isKeyDownV = false;




GLuint LoadGLTexture(const char *filename, int width, int height)
{

    // filename = "/Users/gurelerceis/Documents/XCodeWorkspace/Ders2/SOIL/img_test.bmp"
    GLuint _texture;
    _texture = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
	(
     filename,
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );

    // check for an error during the load process
    if(_texture == 0)
    {
	    printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }

    return _texture;

}


void DrawCircle(float cx, float cy, float r, int num_segments)
{
	glBegin(GL_LINE_LOOP);
	for(int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

		float x = r * cosf(theta);//calculate the x component
		float y = r * sinf(theta);//calculate the y component

		glVertex2f(x + cx, y + cy);//output vertex

	}
	glEnd();
}




void DrawBox(float i){
	glPushMatrix();
	glTranslatef(-i/2, -i/2, -i/2);

	glBegin(GL_POLYGON);/* f1: front */
#ifdef COLOR_PER_FACE
    glColor3ub(255, 0, 0);
#endif
	glNormal3f(-i,0.0f,0.0f);
    glTexCoord2f (0.0f, 0.0f);
	glVertex3f(0.0f,0.0f,0.0f);
    glTexCoord2f (1.0f, 0.0f);
	glVertex3f(0.0f,0.0f,i);
    glTexCoord2f (1.0f, 1.0f);
	glVertex3f(i,0.0f,i);
    glTexCoord2f (0.0f, 1.0f);
	glVertex3f(i,0.0f,0.0f);
	glEnd();
	glBegin(GL_POLYGON);/* f2: bottom */
#ifdef COLOR_PER_FACE
    glColor3ub(0, 0, 255);
#endif
	glNormal3f(0.0f,0.0f,-i);
    glTexCoord2f (0.0f, 0.0f);
	glVertex3f(0.0f,0.0f,0.0f);
    glTexCoord2f (0.0f, 1.0f);
	glVertex3f(i,0.0f,0.0f);
    glTexCoord2f (1.0f, 1.0f);
	glVertex3f(i,i,0.0f);
    glTexCoord2f (1.0f, 0.0f);
	glVertex3f(0.0f,i,0.0f);
	glEnd();
	glBegin(GL_POLYGON);/* f3:back */
#ifdef COLOR_PER_FACE
    glColor3ub(0, 255, 0);
#endif
	glNormal3f(i,0.0f,0.0f);
    glTexCoord2f (0.0f, 0.0f);
	glVertex3f(i,i,0.0f);
    glTexCoord2f (0.0f, 1.0f);
	glVertex3f(i,i,i);
    glTexCoord2f (1.0f, 1.0f);
	glVertex3f(0.0f,i,i);
    glTexCoord2f (1.0f, 0.0f);
	glVertex3f(0.0f,i,0.0f);
	glEnd();
	glBegin(GL_POLYGON);/* f4: top */
#ifdef COLOR_PER_FACE
    glColor3ub(255, 255, 0);
#endif
	glNormal3f(0.0f,0.0f,i);
    glTexCoord2f (0.0, 0.0);
	glVertex3f(i,i,i);
    glTexCoord2f (0.0, 1.0);
	glVertex3f(i,0.0f,i);
    glTexCoord2f (1.0, 1.0);
	glVertex3f(0.0f,0.0f,i);
    glTexCoord2f (1.0, 0.0);
	glVertex3f(0.0f,i,i);
	glEnd();
	glBegin(GL_POLYGON);/* f5: left */
#ifdef  COLOR_PER_FACE
    glColor3ub(0, 255, 255);
#endif
	glNormal3f(0.0f,i,0.0f);
    glTexCoord2f (0.0, 0.0);
	glVertex3f(0.0f,0.0f,0.0f);
    glTexCoord2f (0.0, 1.0);
	glVertex3f(0.0f,i,0.0f);
    glTexCoord2f (1.0, 1.0);
	glVertex3f(0.0f,i,i);
    glTexCoord2f (1.0, 0.0);
	glVertex3f(0.0f,0.0f,i);
	glEnd();
	glBegin(GL_POLYGON);/* f6: right */
#ifdef COLOR_PER_FACE
    glColor3ub(255, 255, 255);
#endif
	glNormal3f(0.0f,-i,0.0f);
    glTexCoord2f (0.0f, 0.0f);
	glVertex3f(i,0.0f,0.0f);
    glTexCoord2f (0.0f, 1.0f);
	glVertex3f(i,0.0f,i);
    glTexCoord2f (1.0f, 1.0f);
	glVertex3f(i,i,i);
    glTexCoord2f (1.0f, 0.0f);
	glVertex3f(i,i,0.0f);
	glEnd();
	glPopMatrix();

}

void SkyBox()
{
    GLuint SkyTexture = LoadGLTexture("stars.jpg",500,500);

    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, SkyTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glDisable(GL_LIGHTING);
    DrawBox(1000);
    glEnable(GL_LIGHTING);
}


#endif // FUNCTIONS_H
