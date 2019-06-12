#include <GL/glut.h>
#include <stdio.h>

// Rotation amounts  
static GLfloat xRot = 0.0f;  
static GLfloat yRot = 0.0f;

static GLfloat rotate_x = 0.5f;

double x[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
double y[11] = {0.00000, 0.84147, 0.90930, 0.14112, -0.75680, -0.95892, -0.27942, 0.65699, 0.98936, 0.41212, -0.54402};


void Mouse(int button, int state, int mouseX, int mouseY);


double produtorio(double a, double xi, double xj);

double lagrange(double vX[], double vY[], double a, int tam);


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
    gluPerspective(120.0f, fAspect, 1.0, 40.0);   
  
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
  
    // Salva matriz de estado e rotacoes
    glPushMatrix();
    glScalef(rotate_x,rotate_x,1.0f );
    glTranslatef(-3.0f, 0.0f, 0.0f);
 
	glTranslatef(0.0f, -1.0f, -5.0f); 
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);  
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

    pObj = gluNewQuadric();  
    gluQuadricNormals(pObj, GLU_SMOOTH);

    double a;
    for(a=x[0]; a<=x[10]; a+=0.001){
        glPushMatrix();
            glTranslatef((GLfloat)a, (GLfloat)lagrange(x, y, a, 11), 0.0f);
            glColor3f(0.0f, 0.0f, 0.0f);
            glScalef(0.5f, 0.5f, 0.6f);
            glutSolidCube(0.3f);
        glPopMatrix();
    }

    glPopMatrix();
    // Buffer swap //chama o glFlush implicitamente 
    glutSwapBuffers();  

}    

  
int main(int argc, char *argv[]){
 
    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  
    glutInitWindowSize(800, 600);  
    glutCreateWindow("Sweeping");  
    glutReshapeFunc(ChangeSize);  
    glutSpecialFunc(SpecialKeys);

    glutMouseFunc(Mouse);
    glutDisplayFunc(RenderScene);  
    SetupRC();
    glutMainLoop();  

    return 0; 

} 


void Mouse(int button, int state, int mouseX, int mouseY){
    GLint hit;
    if (button == GLUT_LEFT_BUTTON) {
        printf("Botao esquerdo\n");
        rotate_x += 0.5f;
    }
    else if(button == GLUT_MIDDLE_BUTTON) {
        printf("Botao meio\n");
    }

    else if(button == GLUT_RIGHT_BUTTON) {
        printf("Botao direito\n");
        if(rotate_x > 1.0f){
            rotate_x -= 0.5f;
        }
    }
    glutPostRedisplay();
}


double produtorio(double a, double xi, double xj){
    double p;

    p = (a - xj) / (xi - xj);
    return p; 
}


double lagrange(double vX[], double vY[], double a, int tam){
    int i, j;
    double resultado = 0;
    double temp;

    for(i=0; i<tam; i++){
        temp = vY[i];
        for(j=0; j<tam; j++){
            if(i != j){
                temp *= produtorio(a, vX[i], vX[j]);
            }
        }
        resultado += temp;
    }

   return resultado;

}
