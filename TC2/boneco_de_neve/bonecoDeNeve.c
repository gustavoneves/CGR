// gcc snowman.c -lglut -lGL -lGLU -lm -o snowman && ./snowman

#include <GL/glut.h>
#include <stdio.h>
// Rotation amounts  
static GLfloat xRot = 0.0f;  
static GLfloat yRot = 0.0f;

//cores do nariz
GLfloat nariz_R = 1.0f;
GLfloat nariz_G = 0.3f;
GLfloat nariz_B = 0.3f;

int tempo;
float velocidade = 2.0f;

void desenhaBoca(GLUquadricObj *quad);

void Mouse(int button, int state, int mouseX, int mouseY);

void botoesRoupa(GLUquadricObj *quad);

void animacao(int v);

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
  
    // Salva matriz de estado e rotacoes
    glPushMatrix();  

	// Move o objeto para tras e faz a rotacao no lugar
	glTranslatef(0.0f, -1.0f, -5.0f);  
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);  
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);  

	// Incializa a quadrica 
	pObj = gluNewQuadric();  
	gluQuadricNormals(pObj, GLU_SMOOTH);  

	// corpo do boneco
	glPushMatrix();  
	glColor3f(1.0f, 1.0f, 1.0f);  
	gluSphere(pObj, .40f, 26, 13);  // Esfera de baixo 

	glTranslatef(0.0f, .550f, 0.0f); // esfera do centro 
	gluSphere(pObj, .3f, 26, 13);  

	glTranslatef(0.0f, 0.45f, 0.0f); // Esfera de cima
	gluSphere(pObj, 0.24f, 26, 13);  

	// Olhos
	glColor3f(0.0f, 0.0f, 0.0f);  
	glTranslatef(0.1f, 0.1f, 0.21f);  
	gluSphere(pObj, 0.02f, 26, 13);  

	glTranslatef(-0.2f, 0.0f, 0.0f);  
	gluSphere(pObj, 0.02f, 26, 13);  

	// Nariz
    if(tempo > 3){ //faz o nariz piscar
        glColor3f(nariz_R, nariz_G, nariz_B); //alaranjado
    }
    else{
        glColor3f(1.0f, 1.0f, 1.0f); //branco
    }  
	glTranslatef(0.1f, -0.12f, 0.0f); 
	gluCylinder(pObj, 0.04f, 0.0f, 0.3f, 26, 13); 

    //Boca
    desenhaBoca(pObj);
    botoesRoupa(pObj);
    //Termina de desenhar a cabeca

    glPopMatrix();

	// Chapeu 
	glPushMatrix();  
	glColor3f(0.0f, 0.0f, 0.0f);  
	glTranslatef(0.0f, 1.17f, 0.0f);  
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);  
	gluCylinder(pObj, 0.17f, 0.17f, 0.4f, 26, 13);  

	// Base do chapeu 
	glDisable(GL_CULL_FACE);  
	gluDisk(pObj, 0.17f, 0.28f, 26, 13);  
	glEnable(GL_CULL_FACE);  

	glTranslatef(0.0f, 0.0f, 0.40f);  
	gluDisk(pObj, 0.0f, 0.17f, 26, 13);  
	glPopMatrix();  

    glPopMatrix();  
  
    // Buffer swap //chama o glFlush implicitamente 
    glutSwapBuffers();  

}    
  
  
int main(int argc, char *argv[]){

    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  
    glutInitWindowSize(800, 600);  
    glutCreateWindow("Boneco de Neve - Quadricas");  
    glutReshapeFunc(ChangeSize);  
    glutSpecialFunc(SpecialKeys);

    glutMouseFunc(Mouse);

    glutDisplayFunc(RenderScene);  
    SetupRC();
    glutTimerFunc(10, animacao, 0);  //chamo a funcao 10 vezes
    glutMainLoop();  
      
    return 0; 

} 

void desenhaBoca(GLUquadricObj *quad){
    //boca
    glColor3f(1.0f, 0.0f, 0.0f); //vermelho

    glTranslatef(0.11f, 0.0f, 0.0f); 
    gluSphere(quad, 0.02f, 26, 13);

    glTranslatef(-0.22f, 0.0f, 0.0f); 
    gluSphere(quad, 0.02f, 26, 13);

    glTranslatef(0.02f, -0.04f, 0.0f); 
    gluSphere(quad, 0.02f, 26, 13);

    glTranslatef(0.18f, 0.0f, 0.0f); 
    gluSphere(quad, 0.02f, 26, 13);

    glTranslatef(-0.04f, -0.03f, 0.0f); 
    gluSphere(quad, 0.02f, 26, 13);

    glTranslatef(-0.10f, 0.0f, 0.0f); 
    gluSphere(quad, 0.02f, 26, 13);

    glTranslatef(0.05f, -0.01f, 0.0f); 
    gluSphere(quad, 0.02f, 26, 13);

}

void Mouse(int button, int state, int mouseX, int mouseY){
    GLint hit;
    if (button == GLUT_LEFT_BUTTON) {
        printf("Botao esquerdo\n");
        nariz_B = 0.0f;
        nariz_G = 1.0f;
        nariz_R = 0.0f;
    }
    else if(button == GLUT_MIDDLE_BUTTON) {
        printf("Botao meio\n");
    }

    else if(button == GLUT_RIGHT_BUTTON) {
        printf("Botao direito\n");
    }
    glutPostRedisplay();
}

void botoesRoupa(GLUquadricObj *quad){
    //botoes roupa
    glColor3f(0.0f, 0.0f, 0.0f); //preto

    glTranslatef(0.0f, -0.3f, 0.1f); 
    gluSphere(quad, 0.04f, 26, 13);

    glTranslatef(0.0f, -0.3f, -0.02f);
    gluSphere(quad, 0.04f, 26, 13); 

    glTranslatef(0.0f, -0.25f, 0.12f);
    gluSphere(quad, 0.04f, 26, 13); 

}

void animacao(int v){
    // https://community.khronos.org/t/gluttimerfunc/24407/2
    tempo++;
    if(tempo >= 30){
        tempo = 0;
    }
    glutTimerFunc(velocidade, animacao, 0); // velocidade e' frequencia qu quero chamar animacao
    glutPostRedisplay();
}