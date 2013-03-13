#include "MassiveSphere.h"

MassiveSphere::MassiveSphere(GLdouble radius,GLint slices, GLint stacks,bool isSolid )
{
    this->isSolid= isSolid;
    this->radius=radius;
    this->slices=slices;
    this->stacks=stacks;

    for(int i=0; i<3; i++)
    {
       this->location[i]=0;
    }

    //ctor

}

MassiveSphere::~MassiveSphere()
{

    //dtor
}

void MassiveSphere::MatrixOps()
{
    glTranslated ( location[0],0,location[2]) ;
    glRotated(90,1,0,0);



}


void MassiveSphere::Draw()
{

   glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, _texture); // select our current texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        GLUquadricObj *sphere = gluNewQuadric();
	    gluQuadricDrawStyle(sphere, GLU_FILL);
	    gluQuadricTexture(sphere, GL_TRUE);
	    gluQuadricNormals(sphere, GLU_SMOOTH);

      if(isSolid == true)
    {

       gluSphere(sphere,radius,slices,stacks);
    }
    else
    {

        glutWireSphere(radius,slices,stacks);
    }


    glDisable(GL_TEXTURE_2D);
}



void MassiveSphere::LoadGLTexture(const char *filename, int width, int height)
{

    // filename = "/Users/gurelerceis/Documents/XCodeWorkspace/Ders2/SOIL/img_test.bmp"

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



}

