//
//  main.cpp
//  Ders3
//
//  Created by Gurel Erceis on 2/25/13.
//  Copyright (c) 2013 Yogurt3D. All rights reserved.
//

#include <iostream>
#include <GL/gl.h>
#include <math.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <Planet.h>

#include <functions.h>



GLdouble angle = 0;


GLfloat material_shininess[] = { 1};

GLfloat zoom,rotx,roty,tx,ty;
GLdouble rotato;


MassiveSphere Sun= MassiveSphere(40.f,50,80,true);
Planet Earth=Planet(6.3f,100,100,true,2.f,40.f,150.f,23);
Planet Moon =Planet(1.7f,10,30,true,1.f,-50.f,10.f);

Planet Venus=Planet(6.3f,100,100,true,3.f,-30.f,100.f);
Planet Satellite = Planet(1.f,100,100,true,2,15.f,7.f);

Planet Mercury=Planet(2.f,100,100,true,3.f,20.f,50.f,2);





static void ReshapeWindow(int w, int h)

{
    glViewport(0,0,w,h);

    //set the projection transform
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(55,w/h,0.1,1000);
}

static void Draw(void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;// Clear Z-buffer
    // set the camera orientation
    glMatrixMode (GL_MODELVIEW) ;
    glLoadIdentity();
    GLdouble loc[3] ;

    gluLookAt( 0,100,300, 0,0,0 , 0,1,0);
    // rotate and zoom camera this order gives you maya like control.
    glTranslatef (0 ,0 ,-zoom ) ;
    glTranslatef ( 0, 0 , 0 ) ;
    glRotatef ( rotx,1 ,0 ,0);
    glRotatef ( roty ,0 ,1 ,0);
    glRotatef (rotato,0,0,1);


//////////   SUN
    glPushMatrix () ;
    glTranslatef ( 0 , 0 , 0 ) ;

    glDisable(GL_LIGHTING);
    Sun.MatrixOps();
    Sun.Draw();
    glPopMatrix();
    glEnable(GL_LIGHTING);
///////////




    //FOR EACH OBJECT:
    glPushMatrix ();
    Earth.MatrixOps();
    Earth.Draw();
   // DrawCircle(0,0,Moon.semiAxis,100);

    glPopMatrix();

    glPushMatrix();
    Moon.MatrixOps();
    Moon.Draw();
    glPopMatrix();



    glPushMatrix();
    Venus.MatrixOps();
    Venus.Draw();

    Satellite .Draw();
    glPopMatrix();


      glPushMatrix();
    Mercury.MatrixOps();
    Mercury.Draw();
    glPopMatrix();








    glEnable(GL_LIGHTING);
    glPopMatrix ();

    glPushMatrix();
    glRotated(90,1,0,0);
    DrawCircle(0,0,Earth.semiAxis,100);
    DrawCircle(0,0,Venus.semiAxis,100);
    DrawCircle(0,0,Mercury.semiAxis,100);
    glPopMatrix();


///////////////// Skybox
    glPushMatrix();
     SkyBox();
    glPopMatrix();


    glutSwapBuffers () ;

}


static void Key( unsigned char key, int x, int y){
    switch(key){
        case 'q':
            exit(0);
            break;
        case 'z':
            isKeyDownZ = true;
            break;
        case 'x':
            isKeyDownX = true;
            break;
        case 'c':
            isKeyDownC = true;
            break;
        case 'v':
            isKeyDownV = true;
            break;
        case 'n':
            zoom+=10;
            break;
        case 'm':
            zoom-=10;
            break;
        case 'i':
            isKeyDownI = true;
            break;
        case 'k':
            isKeyDownK = true;
            break;
        case 'j':
             isKeyDownJ = true;
            break;
        case 'l':
           isKeyDownL = true;
            break;
        case 'o':
             isKeyDownO = true;
            break;
        case 'p':
           isKeyDownP = true;
            break;


    }
}
static void KeyUp( unsigned char key, int x, int y){
    isKeyDownZ = false;
    isKeyDownX = false;
    isKeyDownI = false;
    isKeyDownK = false;
    isKeyDownJ = false;
    isKeyDownL = false;
    isKeyDownO = false;
    isKeyDownP = false;
    isKeyDownC = false;
    isKeyDownV = false;

}

static void timerCallback (int value)
{
    int turn = 1;
    if( isKeyDownX )
    {
        rotato-=1;
    }
    if( isKeyDownZ)
    {
        rotato+=1;
    }
    if( isKeyDownI )
    {
        ty+=turn;
    }
    if( isKeyDownK)
    {
        ty-=turn;
    }
    if( isKeyDownJ )
    {
        tx+=turn;
    }
    if( isKeyDownL )
    {
        tx-=turn;
    }
    if( isKeyDownO)
    {
        zoom+=turn;
    }
    if( isKeyDownP)
    {
        zoom-=turn;
    }
    if(isKeyDownC)
    {
        material_shininess[0]-=3;
    }
    if(isKeyDownV)
    {
        material_shininess[0]+=3;
    }

//EarthSpin+=0.001;
    Earth.CalculateOrbitalRot();
    Earth.CalculateRot();
    Earth.Move();

    Moon.CalculateOrbitalRot();
    Moon.CalculateRot();
    Moon.Move(Earth.GetLocation(0),Earth.GetLocation(1),Earth.GetLocation(2));

    Venus.CalculateOrbitalRot();
    Venus.CalculateRot();
    Venus.Move();

    //Satellite.CalculateOrbitalRot();
    //Satellite.CalculateRot();
    //Satellite.Move(Venus.GetLocation(0),Venus.GetLocation(1),Venus.GetLocation(2));

    Mercury.CalculateOrbitalRot();
    Mercury.CalculateRot();
    Mercury.Move();


    Sun.SetLocation(0,0,0);

    GLfloat light_position[] = { tx, 0,ty , 1};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glMaterialfv(GL_FRONT,GL_SHININESS, material_shininess);

    glutTimerFunc(10, timerCallback, 0);
    glutPostRedisplay();
}

void setupLight(){

       // Enable lightingwa
    glEnable(GL_LIGHTING);

    // Ambient, diffuse and specular lighting values (note that these are ALL FOUR COMPONENT VECTORS!)
    GLfloat  ambientLight[] = { 0.f, 0.f, 0.f, 1.0f };
    GLfloat  diffuseLight[] = { 255.f, 255.f, 0.f, 1.0f };
    GLfloat specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_position[] = { 0, 0, 0 , 1};



    // Setup and enable light 0
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);          // Specify the position of the light
    glLightfv(GL_LIGHT0, GL_AMBIENT,  ambientLight);      // Specify ambient light properties
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  diffuseLight);      // Specify diffuse light properties
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);     // Specify specular light properties
   // glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0001) ;
    glEnable(GL_LIGHT0);

    // Enable colour tracking of materials
    glEnable(GL_COLOR_MATERIAL);

    // Define the shininess of the material we'll use to draw things
    GLfloat materialSpecularReflectance[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    // Set Material properties to follow glColor values
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // Use our shiny material and magnitude
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecularReflectance);

    glEnable(GL_SMOOTH);
}

void LoadTextures()
{
        Earth.LoadGLTexture("url.jpeg",4096,2048);
        Sun.LoadGLTexture("sun.jpg",1024,512);
        Venus.LoadGLTexture("venus.jpg",1440,720);
        Mercury.LoadGLTexture("mercurymap.jpg", 1024,512);
        Moon.LoadGLTexture("moon.jpg",1440,720);
}



int main (int argc, char ** argv)
{

    GLenum type;

	glutInit(&argc, argv);
	glutInitWindowSize(800,600);
	type = GLUT_RGB;
	type |= GLUT_DOUBLE;
	type |= GLUT_DEPTH;
    type |= GLUT_MULTISAMPLE;
	glutInitDisplayMode(type);
	glutCreateWindow("Ders 2");

    glClearColor(0.0, 0, 0, 1.0);
    glEnable(GL_DEPTH_TEST);

    zoom= -100;
    ty= 0;
    tx = 0;
    ReshapeWindow(800,600);
    LoadTextures();
    glMatrixMode(GL_MODELVIEW);

    setupLight();

    timerCallback(0);
    glutDisplayFunc(Draw);
    glutKeyboardFunc(Key);
    glutKeyboardUpFunc(KeyUp);
    glutMainLoop();
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
