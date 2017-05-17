#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>
#include "../object3D.h"
#include "../graphicPrimitives.h"

#define ANGLE_SPEED 5
#define SCALE_SPEED 1.1
#define TRANS_SPEED 5

enum MENU_TYPE{
        MENU_EXIT,
        MENU_CLEAN,
        MENU_PRINT,
        MENU_ORTO,
        MENU_CAVALEIRA,
        MENU_CABINET,
        MENU_PERSP1,
        MENU_PERSP2
};

int funcProj;
int win, main_menu, proj_menu;
graphObject* orig;
graphObject* copy;

void setup(){
   glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
   gluOrtho2D(0, 599, 0, 599);
   orig = newCube();
   scaleObject(orig,50.0f);
   funcProj = MENU_CAVALEIRA;
}

void proj (){
  copy = copyObject(orig);
  switch (funcProj) {
    case MENU_CAVALEIRA:
      cavaleira_proj(copy);
      break;
    case MENU_CABINET:
      cabinet_proj(copy);
      break;
    case MENU_ORTO:
      orto_proj(copy);
      break;
    case MENU_PERSP1:
      transZ(copy,50);
      persp1_proj(copy);
      break;
    case MENU_PERSP2:
      transZ(copy,50);
      transX(copy,50);
      persp2_proj(copy);
      break;
  }
  moveCenter(copy,250);
  showLinesCube(copy);
  destroyObject(copy);
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0f, 0.0f, 0.0f);

  createLine(300.0,0.0,300.0,600.0,2);
  createLine(0.0,300.0,600.0,300.0,2);

  clearMtrDisplay();
  proj();
  printMtrDisplay();
  glutSwapBuffers();
}

void projChoose (int item_proj){
  funcProj = item_proj;
  glutPostRedisplay();
}

void choose (int item_menu){
    switch (item_menu) {
      case MENU_EXIT:
        glutDestroyWindow(win);
        break;
      case MENU_CLEAN:
        glutPostRedisplay();
        break;
      case MENU_PRINT:
        printObjectInfo(orig);
        break;
      default:
        printf("Invalid menu item:%d\n", item_menu);
    }
}

void transformations (unsigned char key,int x, int y){
  switch (key) {
    // Rotacionar
    case 'z':
      rotateX(orig,ANGLE_SPEED);
      break;
    case 'x':
      rotateY(orig,ANGLE_SPEED);
      break;
    case 'c':
      rotateZ(orig,ANGLE_SPEED);
      break;
    case 'a':
      rotateX(orig,-ANGLE_SPEED);
      break;
    case 's':
      rotateY(orig,-ANGLE_SPEED);
      break;
    case 'd':
      rotateZ(orig,-ANGLE_SPEED);
      break;
    // Escalonar
    case 'f':
      scaleX(orig,SCALE_SPEED);
      break;
    case 'g':
      scaleY(orig,SCALE_SPEED);
      break;
    case 'h':
      scaleZ(orig,SCALE_SPEED);
      break;
    case 'v':
      scaleX(orig,1/SCALE_SPEED);
      break;
    case 'b':
      scaleY(orig,1/SCALE_SPEED);
      break;
    case 'n':
      scaleZ(orig,1/SCALE_SPEED);
      break;
    // Transladar
    case '8':
      transY(orig,TRANS_SPEED);
      break;
    case '2':
      transY(orig,-TRANS_SPEED);
      break;
    case '4':
      transX(orig,-TRANS_SPEED);
      break;
    case '6':
      transX(orig,TRANS_SPEED);
      break;
    case '1':
      transZ(orig,TRANS_SPEED);
      break;
    case '3':
      transZ(orig,-TRANS_SPEED);
      break;
  }
  glutPostRedisplay();
}

void main (int argc, char *argv[]){
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE);
   glutInitWindowSize(600,600);

   win = glutCreateWindow("Criacao de objetos 3D");

   proj_menu = glutCreateMenu(projChoose);
   glutAddMenuEntry("Paralela Ortografica Multiplas Vistas",MENU_ORTO);
   glutAddMenuEntry("Paralela Obliqua Cavaleira",MENU_CAVALEIRA);
   glutAddMenuEntry("Paralela Obliqua Cabinet",MENU_CABINET);
   glutAddMenuEntry("Perspectiva com um ponto de fuga em Z",MENU_PERSP1);
   glutAddMenuEntry("Perspectiva com dois pontos de fuga, em X e Z",MENU_PERSP2);

   main_menu = glutCreateMenu(choose);
   glutAddSubMenu("Projecoes",proj_menu);
   glutAddMenuEntry("Info",MENU_PRINT);
   glutAddMenuEntry("Refresh",MENU_CLEAN);
   glutAddMenuEntry("Sair",MENU_EXIT);

   glutAttachMenu(GLUT_RIGHT_BUTTON);
   glutKeyboardFunc(transformations);

   setup();
   glutDisplayFunc(display);
   glutMainLoop();
}
