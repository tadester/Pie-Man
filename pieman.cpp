#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#ifdef _WIN32
#include <windows.h>
#define M_PI 3.14159265358979323846 // Window doesn't seem to define this
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <cmath>
#include <iostream>
using namespace std ;

double radius = 0.8;
double vertexCount = 500;
int mouth = 100;
int piex  = 0 ;
int piey =  0 ;
bool closed = false;
double max1=200;
double min1=0;
double piesc = 0.08;
double pelscal = 0.03 ;
double wax  = 0.035;
double way = 0.055;
double spot = -1;
double spot2  = 1;
int maxi  = 5;
bool stable = true;
int  may = 6;
int faces =4;
double moveunit = 0.2;
double moveunity = 0.133333;
double pYposition = 0.133333;
double pXposition = 0.092;
char maze [15][10] = {{'w','w','w','w','w','w','w','w','w','w'},{'w','p','p','w','p','p','p','p','p','w'}, {'w','p','p','w','p','p','p','p','p','w'},
{'w','p','p','w','w','w','w','p','p','w'}, {'w','p','p','w','w','p','p','p','p','w'},{'w','p','p','p','p','p','p','p','p','w'},{'w','p','p','p','p','e','p','w','w','w'},
{'w','w','w','w','w','p','p','p','p','w'},{'w','p','p','p','p','p','p','p','p','w'},{'w','p','p','w','p','p','p','p','p','w'},{'w','p','p','w','p','p','w','p','p','w'},
{'w','w','w','w','p','p','w','p','p','w'},{'w','p','p','p','p','p','w','p','p','w'},{'w','p','p','p','p','p','w','p','p','w'},{'w','w','w','w','w','w','w','w','w','w'}};
// the pie function is used to first create the top half of a pie then the bottom half then it uses a mouth variable
// that makes where the circle starts being made from


void pie(int mouth){
  glBegin(GL_POLYGON); // start drawing a polygon
  glVertex2f(0.0, 0.0);
for(int x=mouth; x<=vertexCount; x++){
glVertex2f(radius * cos(M_PI*x/vertexCount), radius * sin(M_PI*x/vertexCount));
}
glEnd();
glBegin(GL_POLYGON);
glVertex2f(0.0,0.0);
for(int x=mouth; x<=vertexCount; x++){
glVertex2f(radius * cos(M_PI*x/vertexCount), -radius * sin(M_PI*x/vertexCount));
}
glEnd();
}

void pellets(){
  glBegin(GL_POLYGON); // start drawing a polygon    cout<<spot << "  ";
  glVertex2f(0.0, 0.0);
for(int x=0; x<=vertexCount; x++){
glVertex2f(0.025 * cos(M_PI*x/vertexCount), 0.025 * sin(M_PI*x/vertexCount));
}
glEnd();

glBegin(GL_POLYGON);
glVertex2f(0.0,0.0);
for(int x=0; x<=vertexCount; x++){
glVertex2f(0.025 * cos(M_PI*x/vertexCount), -0.025 * sin(M_PI*x/vertexCount));
}
glEnd();
}

void walls(){
  glBegin(GL_POLYGON); // start drawing a polygon
  glVertex2f(0.0, 0.0);
  glVertex2f(0.2, 0.0);
   glVertex2f(0.2, -0.133333);
  glVertex2f(0.0, -0.133333);

glEnd();
}


void rotations() {

if (faces == 1)

{

glRotatef(270.0, 0.0, 0.0, 1.0); // angle 270 --> face Up.

}

else if (faces == 2)

{

glRotatef(90.0, 0.0, 0.0, 1.0); // angle 90 --> face down.

}

else if (faces == 3)

{

glRotatef(0.0, 0.0, 0.0, 1.0); // angle 0 --> face to the left.

}

else if(faces == 4) {

glRotatef(180.0, 0.0, 0.0, 1.0); // angle 180 --> face to the right

}

}

void pMouthChomp(int random){
  if (mouth <= max1 && !closed &&stable )

  {

  mouth += 10;

  if (max1 <= mouth && stable)

  {

  closed = true;

  }

  }

  else if (mouth >= min1 && closed && stable)

  {

    mouth -= 10;

  if (min1 >= mouth && stable)

  {

  closed = false;

  }

  }

  else if (mouth >= min1 && stable)

  {

  mouth -= 10;

  }
  glutPostRedisplay();

  glutTimerFunc(50, pMouthChomp, 42);



}
void mouseup(int ran){
  may -=1;
  stable = true;
if(maze[may][maxi] == 'p'){
  stable = true;
  maze[may][maxi]  = 'e';
  faces= 2;
  pYposition+= moveunity;

}else if(maze[may][maxi] == 'w'){
  stable = false;
  mouth = min1;
  may+=1;

}else if(maze[may][maxi]  == 'e'){
    faces= 2;
    stable = true;
pYposition+= moveunity;



}

glutPostRedisplay();
}

void moused(int ran){

  may +=1;
  stable = true;
if(maze[may][maxi] == 'p'){
  stable = true;
  maze[may][maxi]  = 'e';
  faces= 1;
  pYposition-= moveunity;

}else if(maze[may][maxi] == 'w'){
  stable = false;
  mouth = min1;
may-=1;
}else if(maze[may][maxi]  == 'e'){
  stable = true;
    faces= 1;
pYposition-= moveunity;

glutPostRedisplay();
}
}
void mousel(int ran){
  maxi -=1;
  stable = true;
if(maze[may][maxi] == 'p'){
  stable = true;
  maze[may][maxi]  = 'e';
  faces= 4;

  pXposition-= moveunit;

}else if(maze[may][maxi] == 'w'){
  stable = true;
  stable = false;
  mouth = min1;
  maxi += 1;
}else if(maze[may][maxi]  == 'e'){
  stable = true;
    faces= 4;

    pXposition-= moveunit;


}


glutPostRedisplay();
}
void mouser(int ran){
  maxi +=1;
  stable = true;
if(maze[may][maxi] == 'p'){
  stable = true;
  maze[may][maxi]  = 'e';
  faces= 3;

  pXposition+= moveunit;

}else if(maze[may][maxi] == 'w'){
  stable = false;
  mouth = min1;
  maxi -=1;

}else if(maze[may][maxi]  == 'e'){
  stable = true;
    faces= 3;

    pXposition+= moveunit;


}

glutPostRedisplay();
}

void mouseF( int button, int state, int x, int y)
{
}
void arrows(int key, int x, int y) {

//If UpArrow is pressed, PieMan goes up.

if (key == GLUT_KEY_UP)

{

glutTimerFunc(150, mouseup, 42);



}

//If DownArrow is pressed, PieMan goes down.

else if(key == GLUT_KEY_DOWN)

{

  glutTimerFunc(150, moused, 42);








}

//If LeftArrow is pressed, PieMan goes left.

else if(key == GLUT_KEY_LEFT)

{
  faces= 4;

  glutTimerFunc(150, mousel, 42);




glutPostRedisplay();

}

//If RightArrow is pressed, PieMan goes right.

else if(key == GLUT_KEY_RIGHT)

{
faces= 3;
  glutTimerFunc(150, mouser, 42);





glutPostRedisplay();
}
}


  // 4 if else statemets each for different parts of the screen so I can keep track of where the mouse clicks
//   if(button == GLUT_LEFT_BUTTON && state == GLUT_UP &&  x <250 && y <250) {
//     if(mouth<max1){
//         mouth = mouth+10;
//     }
//
// }


void display(void)
{

  glClearColor (0.0f, 0.0f, 0.0f, 0.0f); // background colour
  glClear(GL_COLOR_BUFFER_BIT); // clear the background
  glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f); // define the size of the world
  glColor3f(1.0, 1.0, 0.0); // change the current colour

spot2 = 1;

  for(int i = 0 ; i <15; i++){
    spot = -1;
    for (int j = 0 ;j <10; j++){
       glColor3f(1.0, 1.0, 0.0);
      if(maze[i][j] == 'p'){
        glLoadIdentity();

         glTranslatef(spot+0.1,spot2-0.0533,1);

        pellets();
      }else if (maze[i][j] == 'w'){
        glLoadIdentity();
         glTranslatef(spot,spot2,1);
         glColor3f(1.0, 0.0, 0.0); //
        walls();

      }


    spot = spot+ 0.2  ;


    }

  spot2 = spot2-0.133333;

  }
  glLoadIdentity();
  glColor3f(1.0, 1.0, 0.0);
  glTranslatef(pXposition,pYposition ,1 );
  glScalef(piesc,piesc ,1);
  rotations();
  pie(mouth);
  glFlush();
  glutSwapBuffers();


}





int main(int argc, char** argv)
{
    // First set up GLUT
    glutInit( &argc, argv );
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);

    // Make the window
    int windowHandle = glutCreateWindow(" Assignment 1- Pie Man");
    glutSetWindow(windowHandle);

    // Place and size the window
    glutPositionWindow ( 100, 100 );
    glutReshapeWindow( 500, 750 );

    // set the drawing and mouse callback functions
    // notice the names are the functions defined above
    glutDisplayFunc(display);
    glutMouseFunc( mouseF );
    glutSpecialFunc(arrows);
    glutTimerFunc(50,pMouthChomp ,42);

    // Go into an infinite loop waiting for messages
    glutMainLoop();
    return 0;
}
