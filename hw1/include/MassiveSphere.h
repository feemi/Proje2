#ifndef MASSIVESPHERE_H
#define MASSIVESPHERE_H

#include <stdio.h>
#include <GL/gl.h>
#include <math.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <SOIL/SOIL.h>

class MassiveSphere
{
    public:
        GLdouble location[3];
        GLdouble radius;
        GLint slices;
        GLint stacks;
        bool isSolid;
        GLuint _texture;
        MassiveSphere(GLdouble radius,GLint slices, GLint stacks, bool isSolid);
       // MassiveSphere();
        void LoadGLTexture(const char *filename, int width, int height);
        void Draw();

        GLdouble GetLocation(int axis)
        {
            return location[axis];}
        void SetLocation(GLdouble x,GLdouble y, GLdouble z)
        {
            location[0]=x;
            location[1]=y;
            location[2]=z;
        }
        void MatrixOps();



        virtual ~MassiveSphere();
    protected:
    private:


};

#endif // MASSIVESPHERE_H
