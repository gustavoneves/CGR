#include <GL/glut.h>
#include <stdio.h>

// Rotation amounts  
static GLfloat xRot = 0.0f;  
static GLfloat yRot = 0.0f;

static GLfloat rotate_x = 0.5f;

double x[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
double y[11] = {0.00000, 0.84147, 0.90930, 0.14112, -0.75680, -0.95892, -0.27942, 0.65699, 0.98936, 0.41212, -0.54402};

//void desenhaTorre(GLUquadricObj *quad, GLfloat x, GLfloat y, GLfloat z);

void Mouse(int button, int state, int mouseX, int mouseY);

//void desenhaChao();

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
    //gluPerspective(35.0f, fAspect, 1.0, 40.0);
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
  
    // Sava matriz de estado e rotacoes
    glPushMatrix();
    glScalef(rotate_x,rotate_x,1.0f );
    glTranslatef(-3.0f, 0.0f, 0.0f);
	// Move object back and do in place rotation  
	glTranslatef(0.0f, -1.0f, -5.0f); 
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);  
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

    pObj = gluNewQuadric();  
    gluQuadricNormals(pObj, GLU_SMOOTH);

    //glPushMatrix(); 
    //glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // Z crescendo para cima da tela

    double a;
    for(a=x[0]; a<=x[10]; a+=0.001){
        //printf("x: %f     y:%f\n", a, lagrange(x, y, a, 11));
        glPushMatrix();
            glTranslatef((GLfloat)a, (GLfloat)lagrange(x, y, a, 11), 0.0f);
            glColor3f(0.0f, 0.0f, 0.0f);
            glScalef(0.5f, 0.5f, 0.6f);
            glutSolidCube(0.3f);
        glPopMatrix();
    }

    //glPopMatrix();

    glPopMatrix();
    // Buffer swap //chama o glFlush implicitamente 
    glutSwapBuffers();  

}    

  
int main(int argc, char *argv[]){
    /*
    double x[3] = {-1, 0, 3};
    double y[3] = {15, 8, -1};

    printf("%f\n", lagrange(x, y, 1, 3));
    */
    //double x[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    //double y[11] = {0.00000, 0.84147, 0.90930, 0.14112, -0.75680, -0.95892, -0.27942, 0.65699, 0.98936, 0.41212, -0.54402};

/*
    double a;

    for(a=x[0]; a<=x[10]; a+=0.1){
        printf("x: %f     y:%f\n", a, lagrange(x, y, a, 11));
    }
*/
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


/*
void desenhaTorre(GLUquadricObj *quad, GLfloat x, GLfloat y, GLfloat z){

    glTranslatef(x, y, z-0.8f);
    gluCylinder(quad, 0.3f, 0.3f, 1.1f, 26, 13);
    glTranslatef(0.0f, 0.0f, 1.0f);
    gluCylinder(quad, 0.4f, 0.0f, 0.5f, 26, 13);

}


void desenhaChao(){
    glScalef(5.0f, 4.0f, 0.125f);
    glutSolidCube(1.0f);
}

*/


/*
    //torre direita - frentre
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);  
    desenhaTorre(pObj, 1.5f, 0.0f, 1.0f);
    glPopMatrix();

    //torre esquerda - frente
    glPushMatrix();
    glColor3f(0.0f, 1.0f, 0.0f);
    desenhaTorre(pObj, -1.5f, 0.0f, 1.0f);
    glPopMatrix();

    //torre direita atras
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 1.0f);
    desenhaTorre(pObj, 1.5f, 3.0f, 1.0f);
    glPopMatrix();

    //torre esquerda atras
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    desenhaTorre(pObj, -1.5f, 3.0f, 1.0f);
    glPopMatrix();

    //Desenha o chao
    glPushMatrix();
    glColor3f(0.9f, 0.9f, 0.9f);
    glTranslatef(0.0f, 1.0f, 0.125f);
    desenhaChao();
    glPopMatrix();


    //Desenha parede entre as torres direita e esquerda - frente
    //Direita frente desenhaTorre(pObj, 1.5f, 0.0f, 1.0f);
    //Esquerda frente desenhaTorre(pObj, -1.5f, 0.0f, 1.0f);
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.5f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glScalef(3.0f, 0.125f, 0.6f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.9f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glScalef(3.0f, 0.250f, 0.2f);
    glutSolidCube(1.0f);
    glPopMatrix();



    //Desenha parede entre as torres direita e esquerda - atras
    //Direita atras desenhaTorre(pObj, 1.5f, 2.0f, 1.0f);
    //Esquerda atras desenhaTorre(pObj, -1.5f, 2.0f, 1.0f);
    glPushMatrix();
    glTranslatef(0.0, 3.0, 0.5f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glScalef(3.0f, 0.125f, 0.6f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 3.0, 0.9f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glScalef(3.0f, 0.250f, 0.2f);
    glutSolidCube(1.0f);
    glPopMatrix();


    //Desenha parede entre as torres da direita
    //Direita frente desenhaTorre(pObj, 1.5f, 0.0f, 1.0f);
    //Direita atras desenhaTorre(pObj, 1.5f, 2.0f, 1.0f);
    glPushMatrix();
    glTranslatef(1.5, 1.5, 0.5f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glScalef(0.125f, 3.0f, 0.6f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.5, 1.5, 0.9f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glScalef(0.250f, 3.0f, 0.2f);
    glutSolidCube(1.0f);
    glPopMatrix();



    //Desenha parede entre as torres da esquerda
    //Esquerda frente desenhaTorre(pObj, -1.5f, 0.0f, 1.0f);
    //Esquerda atras desenhaTorre(pObj, -1.5f, 3.0f, 1.0f);
    glPushMatrix();
    glTranslatef(-1.5, 1.5, 0.5f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glScalef(0.125f, 3.0f, 0.6f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.5, 1.5, 0.9f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glScalef(0.250f, 3.0f, 0.2f);
    glutSolidCube(1.0f);
    glPopMatrix();


    //interior portao frente
    glPushMatrix();
    glTranslatef(0.0, -0.1f, 0.4f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glScalef(0.5f, 0.5f, 0.6f);
    glutSolidCube(1.0f);
    glPopMatrix();


    //portao frente
    glPushMatrix();
    glTranslatef(0.0, -0.1f, 0.7f);
    glColor3f(0.0f, 1.0f, 1.0f);
    glScalef(0.7f, 0.5f, 1.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    //comeca telhado portao frente
    glPushMatrix();
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 1.6f, 0.1f);


    glBegin(GL_TRIANGLES);    
      glColor3f(0.5f, 0.0f, 0.0f);
      // triangulo frente
      glVertex3f( 0.0f, 0.05f, 0.0f);
      glVertex3f(-0.35f, -0.35f, 0.25f);
      glVertex3f(0.35f, -0.35f, 0.25f);
 
      // triangulo direita
      glVertex3f( 0.0f, 0.05f, 0.0f);
      glVertex3f(0.35f, -0.35f, 0.25f);
      glVertex3f(0.35f, -0.35f, -0.25f);

      // triangulo atras
      glVertex3f( 0.0f, 0.05f, 0.0f);
      glVertex3f(0.35f, -0.35f, -0.25f);
      glVertex3f(-0.35f, -0.35f, -0.25f);

      // triangulo esquerda
      glVertex3f( 0.0f, 0.05f, 0.0f);
      glVertex3f(-0.35f,-0.35f,-0.25f);
      glVertex3f(-0.35f,-0.35f, 0.25f);
    glEnd();
    glPopMatrix();
    //termina telhado portao frente

    //Torre central
    glPushMatrix();
    glTranslatef(0.0, 1.5f, 1.0f);
    glColor3f(0.0f, 1.0f, 1.0f);
    glScalef(0.9f, 0.7f, 1.4f);
    glutSolidCube(1.0f);
    glPopMatrix();

    //telhado torre central
    glPushMatrix();
    glTranslatef(0.0f, 1.5f, 2.05f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);

    glBegin(GL_TRIANGLES);    
      glColor3f(0.5f, 0.0f, 0.0f);
      // triangulo frente
      glVertex3f( 0.0f, 0.05f, 0.0f);
      glVertex3f(-0.45f, -0.35f, 0.38f);
      glVertex3f(0.45f, -0.35f, 0.38f);

      // triangulo direita
      glVertex3f( 0.0f, 0.05f, 0.0f);
      glVertex3f(0.45f, -0.35f, 0.38f);
      glVertex3f(0.45f, -0.35f, -0.38f);

      // triangulo atras
      glVertex3f( 0.0f, 0.05f, 0.0f);
      glVertex3f(0.45f, -0.35f, -0.38f);
      glVertex3f(-0.45f, -0.35f, -0.38f);

      // triangulo esquerda
      glVertex3f( 0.0f, 0.05f, 0.0f);
      glVertex3f(-0.45f,-0.35f,-0.38f);
      glVertex3f(-0.45f,-0.35f, 0.38f);
    glEnd();
    glPopMatrix();




    glPopMatrix(); // rotacao -90 em x


 */