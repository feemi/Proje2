#include <Planet.h>

Planet::Planet(GLdouble radius,GLint slices, GLint stacks,bool isSolid, GLdouble rotationalVelocity,GLdouble orbitalSpeed, GLdouble semiAxis)
    :MassiveSphere(radius,slices,stacks,isSolid)
{
    this->rotationalVelocity= rotationalVelocity;
    this->orbitalSpeed = orbitalSpeed;
    this->semiAxis = semiAxis;
    this->axialTilt = axialTilt;
    this->rotAngle=0;
    this->orbitalAngle=0;
    //ctor
}

Planet::Planet(GLdouble radius,GLint slices, GLint stacks,bool isSolid, GLdouble rotationalVelocity,GLdouble orbitalSpeed, GLdouble semiAxis, GLdouble axialTilt)
    :MassiveSphere(radius,slices,stacks,isSolid)
{
    this->rotationalVelocity= rotationalVelocity;
    this->orbitalSpeed = orbitalSpeed;
    this->semiAxis = semiAxis;
    this->axialTilt = axialTilt;
    this->rotAngle=0;
    this->orbitalAngle=0;
    //ctor
}

void Planet::CalculateRot()
{
    rotAngle += rotationalVelocity*0.5;
    if(rotAngle>360)
    {
        rotAngle==0;
    }
}
void Planet::CalculateOrbitalRot()
{
    orbitalAngle += orbitalSpeed * 0.0001;
    if(orbitalAngle>360)
    {
        orbitalAngle==0;
    }
}
void Planet::Move()
{
     location[0] = 0 + sin(orbitalAngle)*semiAxis;
     location[2] = 0 + cos(orbitalAngle)*semiAxis;
}
void Planet::Move(GLdouble x, GLdouble y, GLdouble z)
{
     location[0] = x + sin(orbitalAngle)*semiAxis;
     location[2] = z + cos(orbitalAngle)*semiAxis;
}
void Planet::MatrixOps()
{
    MassiveSphere::MatrixOps();


    if(axialTilt>0)
    {
        glRotated (axialTilt,0,1,0);
    }

    glRotated(rotAngle,0,0,1);


}

void Planet::Draw()
{
    MassiveSphere::Draw();
}


Planet::~Planet()
{
    //dtor
}
