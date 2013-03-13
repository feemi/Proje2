#ifndef PLANET_H
#define PLANET_H

#include <MassiveSphere.h>


class Planet : public MassiveSphere
{
    public:
        GLdouble rotationalVelocity;
        GLdouble orbitalSpeed;
        GLdouble semiAxis;
        GLdouble axialTilt;

        Planet(GLdouble radius,GLint slices, GLint stacks,bool isSolid, GLdouble rotationalVelocity,GLdouble orbitalSpeed, GLdouble semiAxis);
        Planet(GLdouble radius,GLint slices, GLint stacks,bool isSolid, GLdouble rotationalVelocity,GLdouble orbitalSpeed, GLdouble semiAxis,GLdouble axialTilt);
        void MatrixOps();
        void Draw();
        void MoonDraw();
        void CalculateRot();
        void CalculateOrbitalRot();
        void Move(GLdouble x,GLdouble y, GLdouble z);
        void Move();
        virtual ~Planet();
    protected:
    private:
        GLdouble rotAngle;
        GLdouble orbitalAngle;
};

#endif // PLANET_H
