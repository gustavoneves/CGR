#include <GL/glut.h>
#include <stdio.h>

char title[] = "3D Shapes";

static GLfloat xRot = 0.0f;  
static GLfloat yRot = 0.0f;

 
void desenhaTorre(GLUquadricObj *quad, GLfloat x, GLfloat y, GLfloat z);

void Mouse(int button, int state, int mouseX, int mouseY);

void SpecialKeys(int key, int x, int y);

void desenhaChao();
/* Initialize OpenGL Graphics */

/*
void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

void SetupRC(){  
*/
void initGL() {
    // Light values and coordinates  
    GLfloat  whiteLight[] = { 0.05f, 0.05f, 0.05f, 1.0f };  
    GLfloat  sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };  
    GLfloat  lightPos[] = { -10.f, 5.0f, 5.0f, 1.0f };  
  
    glEnable(GL_DEPTH_TEST);    // Hidden surface removal  
    glFrontFace(GL_CCW);        // Counter clock-wise polygons face out  
    glEnable(GL_CULL_FACE);     // Do not calculate inside  
  
    // Enable lighting  
    glEnable(GL_LIGHTING);  
  
    // Setup and enable light 0  
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);  
    glLightfv(GL_LIGHT0,GL_AMBIENT,sourceLight);  
    glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);  
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);  
    glEnable(GL_LIGHT0);  
  
    // Enable color tracking  
    glEnable(GL_COLOR_MATERIAL);  
      
    // Set Material properties to follow glColor values  
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);  
  
    // Black blue background  
    glClearColor(0.25f, 0.25f, 0.50f, 1.0f);  

}  

/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
   glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

   desenhaChao();
   
   //glRotatef(xRot, 1.0f, 0.0f, 0.0f);  
   //glRotatef(yRot, 0.0f, 1.0f, 0.0f);

   GLUquadricObj *pObj = gluNewQuadric();  
   gluQuadricNormals(pObj, GLU_SMOOTH);

   //torre direita - frentre
   glColor3f(1.0f, 0.0f, 0.0f);
   desenhaTorre(pObj, 1.5f, 0.0f, -7.0f);

   //torre esquerda - frente
   glColor3f(0.0f, 1.0f, 0.0f);
   desenhaTorre(pObj, -2.5f, 0.0f, -7.0f);

   //torre direita - atras
   glColor3f(0.0f, 0.0f, 1.0f);
   desenhaTorre(pObj, 1.5f, 2.0f, -7.0f);

   //torre esquerda - atras
   glColor3f(0.0f, 1.0f, 1.0f);
   desenhaTorre(pObj, -2.5f, 2.0f, -7.0f);
   
   //parede frontal 
   glLoadIdentity();
   glColor3f(1.0f, 0.5f, 0.0f);
   glTranslatef(0.0f, -0.8f, 0.0f);
   glBegin(GL_QUADS);
        glVertex3f(1.5f, 0.0f, -7.0f);
        glVertex3f(1.5f, 0.8f, -7.0f);
        glVertex3f(-2.5f, 0.8f, -7.0f);
        glVertex3f(-2.5f, 0.0f, -7.0f);
   glEnd();

   //parede fundos
   glLoadIdentity();
   glColor3f(1.0f, 0.0f, 1.0f);
   glTranslatef(0.0f, -0.8f, 0.0f);
   glBegin(GL_QUADS);
        glVertex3f(1.5f, 2.0f, -7.0f);
        glVertex3f(1.5f, 2.8f, -7.0f);
        glVertex3f(-2.5f, 2.8f, -7.0f);
        glVertex3f(-2.5f, 2.0f, -7.0f);
   glEnd();

    
   //parede lateral direita
   glLoadIdentity();
   glColor3f(0.1f, 0.0f, 0.1f);
   glTranslatef(0.0f, -0.8f, 0.0f);
   glBegin(GL_QUADS);
        glVertex3f(1.5f, 2.0f, -7.0f);
        glVertex3f(1.5f, 2.8f, -7.0f);
        glVertex3f(1.5f, 0.8f, -7.0f);
        glVertex3f(1.5f, 0.0f, -7.0f);
   glEnd();

   //parede lateral esquerda
   glLoadIdentity();
   glColor3f(0.1f, 0.0f, 0.1f);
   glTranslatef(0.0f, -0.8f, 0.0f);
   glBegin(GL_QUADS);
        glVertex3f(-2.5f, 2.0f, -7.0f);
        glVertex3f(-2.5f, 2.8f, -7.0f);
        glVertex3f(-2.5f, 0.8f, -7.0f);
        glVertex3f(-2.5f, 0.0f, -7.0f);
   glEnd();
   
   glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
}


void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);
 
   // Set the aspect ratio of the clipping volume to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset
   // Enable perspective projection with fovy, aspect, zNear and zFar
   //gluPerspective(45.0f, aspect, 0.1f, 100.0f);
   gluPerspective(45.0f, aspect, 1.0, 40.0);

   glMatrixMode(GL_MODELVIEW);  
   glLoadIdentity();  
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
   glutInit(&argc, argv);            // Initialize GLUT
   //glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   //glutInitWindowSize(640, 480);   // Set the window's initial width & height
   glutInitWindowSize(800, 600);
   //glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   glutInitWindowPosition(20, 20);
   glutCreateWindow(title);          // Create window with the given title
   
   glutReshapeFunc(reshape);       // Register callback handler for window re-size event
   
   glutSpecialFunc(SpecialKeys);

   glutMouseFunc(Mouse);

   glutDisplayFunc(display);       // Register callback handler for window re-paint event
   
   initGL();                       // Our own OpenGL initialization



   glutMainLoop();                 // Enter the infinite event-processing loop
   return 0;
}

void desenhaTorre(GLUquadricObj *quad, GLfloat x, GLfloat y, GLfloat z){
    
    //glColor3f(1.0f, 0.0f, 0.0f); //vermelho

    //glTranslatef(-3.0f, 3.0f, 2.0f);
    glLoadIdentity();

    glTranslatef(x, y, z);

    glRotatef(-90, 1.0f, 0.0f, 0.0f);

    gluCylinder(quad, 0.3f, 0.0f, 0.5f, 26, 13);
     
    glTranslatef(0.0f, 0.0f, -0.8f);
    gluCylinder(quad, 0.3f, 0.3f, 0.8f, 26, 13);

}

void desenhaChao(){

    /*
        //torre direita - frentre
        desenhaTorre(pObj, 1.5f, 0.0f, -7.0f);

        //torre esquerda - frente
        desenhaTorre(pObj, -2.5f, 0.0f, -7.0f);

        //torre direita - atras
        desenhaTorre(pObj, 1.5f, 2.0f, -7.0f);

        //torre esquerda - atras
        desenhaTorre(pObj, -2.5f, 2.0f, -7.0f);
    */
    glLoadIdentity();
    glColor3f(0.3f, 0.9f, 0.9f);

    glTranslatef(0.0f, -1.0f, 0.0f);
    //glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_QUADS);
        /*
        glVertex3f(3.5f, 4.0f, -9.0f); //torre direita - atras
        glVertex3f(-4.5f, 4.0f, -9.0f); //torre esquerda - atras
        glVertex3f(-4.5f, -0.8f, -9.0f); //torre esquerda - frente
        glVertex3f(3.5f, -0.8f, -9.0f); //torre direita - frentre
        */

        glVertex3f(2.5f, 3.0f, -8.0f); //torre direita - atras
        glVertex3f(-3.5f, 3.0f, -8.0f); //torre esquerda - atras
        glVertex3f(-3.5f, -0.8f, -8.0f); //torre esquerda - frente
        glVertex3f(2.5f, -0.8f, -8.0f); //torre direita - frentre
        /*
           //torre direita - frentre
             glColor3f(1.0f, 0.0f, 0.0f);
             desenhaTorre(pObj, 1.5f, 0.0f, -7.0f);

           //torre esquerda - frente
             glColor3f(0.0f, 1.0f, 0.0f);
             desenhaTorre(pObj, -2.5f, 0.0f, -7.0f);

           //torre direita - atras
             glColor3f(0.0f, 0.0f, 1.0f);
             desenhaTorre(pObj, 1.5f, 2.0f, -7.0f);

           //torre esquerda - atras
             glColor3f(0.0f, 1.0f, 1.0f);
            desenhaTorre(pObj, -2.5f, 2.0f, -7.0f);
            */
    glEnd();

    glutSwapBuffers();
}

/*
void desenhaParede(){
    glLoadIdentity();

    glColor3f(0.1f, 0.1f, 0.1f);

    glBegin(GL_QUADS);
        glVertex3f();
        glVertex3f();
        glVertex3f();
        glVertex3f();
    glEnd();
}
*/
void SpecialKeys(int key, int x, int y){  

    if(key == GLUT_KEY_UP)  
        xRot-= 5.0f;  
  
    if(key == GLUT_KEY_DOWN)  
        xRot += 5.0f;  
  
    if(key == GLUT_KEY_LEFT)  
        yRot -= 5.0f;  
  
    if(key == GLUT_KEY_RIGHT)  
        yRot += 5.0f;  
                  
        xRot = (GLfloat)((const int)xRot % 360);  
        yRot = (GLfloat)((const int)yRot % 360);  
  
    // Refresh the Window  
    glutPostRedisplay();  

}


void Mouse(int button, int state, int mouseX, int mouseY){
    GLint hit;
    if (button == GLUT_LEFT_BUTTON) {
        printf("Botao esquerdo\n");
    }
    else if(button == GLUT_MIDDLE_BUTTON) {
        printf("Botao meio\n");
    }

    else if(button == GLUT_RIGHT_BUTTON) {
        printf("Botao direito\n");
    }
    glutPostRedisplay();
}