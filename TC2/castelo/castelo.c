// gcc snowman.c -lglut -lGL -lGLU -lm -o snowman && ./snowman

#include <GL/glut.h>
#include <stdio.h>
// Rotation amounts  
static GLfloat xRot = 0.0f;  
static GLfloat yRot = 0.0f;

void Mouse(int button, int state, int mouseX, int mouseY);

void desenhaTorre(GLUquadricObj *quad);

// Change viewing volume and viewport.  Called when window is resized  
void ChangeSize(int w, int h){  
    GLfloat fAspect;  
  
    // Prevent a divide by zero  
    if(h == 0)  
        h = 1;  
  
    // Set Viewport to window dimensions  
    glViewport(0, 0, w, h);  
  
    fAspect = (GLfloat)w/(GLfloat)h;  
  
    // Reset coordinate system  
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();  
  
    // Produce the perspective projection  
    gluPerspective(35.0f, fAspect, 1.0, 40.0);  
  
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();  
}  
  
  
// This function does any needed initialization on the rendering context.
//  Here it sets up and initializes the lighting for the scene.  
void SetupRC(){  

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
  
// Respond to arrow keys  
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
  
  
// Desenhar a cena 
void RenderScene(void){  

    GLUquadricObj *pObj;    // Quadrica
    // Limpa a janela e o buffer 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
  
    // Sava matriz de estado e rotacoes
    glPushMatrix();  

	// Move object back and do in place rotation  
	glTranslatef(0.0f, -1.0f, -5.0f);  
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);  
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);  

	// Draw something  
	pObj = gluNewQuadric();  
	gluQuadricNormals(pObj, GLU_SMOOTH);  

    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	// Main Body 
    
	glPushMatrix();
    //torre mais a esquerda  
    glTranslatef(-2.0f, 7.0f, 0.0f);
	desenhaTorre(pObj);

    //torre esquerda
    glTranslatef(-2.0f, 7.0f, -1.0f);
    desenhaTorre(pObj);

    //torre de tras
    //glTranslatef(6.0f, 0.0f, 0.0f);

    glTranslatef(9.0f, -6.0f, -1.0f);
    desenhaTorre(pObj);

    glPopMatrix();

    // Restore the matrix state  
    glPopMatrix();  
  
    // Buffer swap //chama o glFlush implicitamente 
    glutSwapBuffers();  

}    
  
  
int main(int argc, char *argv[]){

    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  
    glutInitWindowSize(800, 600);  
    glutCreateWindow("Castelo - Quadricas");  
    glutReshapeFunc(ChangeSize);  
    glutSpecialFunc(SpecialKeys);

    glutMouseFunc(Mouse);

    glutDisplayFunc(RenderScene);  
    SetupRC();  
    glutMainLoop();  
      
    return 0; 

} 

void desenhaTorre(GLUquadricObj *quad){
    
    glColor3f(1.0f, 0.0f, 0.0f); //vermelho

    glTranslatef(-3.0f, 3.0f, 2.0f);

    gluCylinder(quad, 0.3f, 0.0f, 0.5f, 26, 13);
     
    glTranslatef(0.0f, 0.0f, -0.8f);
    gluCylinder(quad, 0.3f, 0.3f, 0.8f, 26, 13);

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