#include <GL/glut.h>
#include <stdio.h>
 
static GLfloat xRot = 0.0f;  
static GLfloat yRot = 0.0f;

static GLfloat xRotBracoDir = 0.0f;  
static GLfloat yRotBracoDir = 0.0f;

static GLfloat xRotBracoEsq = 0.0f;  
static GLfloat yRotBracoEsq = 0.0f;

static GLfloat cabecaReverencia = 0.0f;

static GLfloat cabecaExorcista = 5.0f;

int tempo;
float velocidade = 0.1f;

int ex = 0;
void Mouse(int button, int state, int mouseX, int mouseY);

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
    //gluPerspective(35.0f, fAspect, 1.0, 40.0);
    gluPerspective(45.0f, fAspect, 1.0, 40.0);      
  
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
  
// Setas  
void SpecialKeys(int key, int x, int y){  
    if(key == GLUT_KEY_UP){  
        xRot-= 5.0f;
        printf("cima\n");
    }  
  
    if(key == GLUT_KEY_DOWN){  
        xRot += 5.0f;
        printf("baixo\n");  
    }

    if(key == GLUT_KEY_LEFT){  
        yRot -= 5.0f;
        printf("esquerda\n");
    }  
  
    if(key == GLUT_KEY_RIGHT){  
        yRot += 5.0f;
        printf("direita\n");
    }  
                  
    xRot = (GLfloat)((const int)xRot % 360);  
    yRot = (GLfloat)((const int)yRot % 360);
    glutPostRedisplay();  
}

void TeclasPressionadas(unsigned char tecla, int x, int y){
    if(tecla == 'w'){
        yRotBracoDir += 5.0f;
        printf("W\n");
    } 

    if(tecla == 's'){
        yRotBracoEsq += 5.0f;
        printf("S\n");
    }

    if(tecla == 'g') {
        cabecaReverencia += 5.0f;
    }

    if(tecla == 'e'){
        ex = 1;
    }

    yRotBracoDir = (GLfloat)((const int)yRotBracoDir % 45);  
    yRotBracoEsq = (GLfloat)((const int)yRotBracoEsq % 45);
    cabecaReverencia = (GLfloat)((const int)cabecaReverencia % 30);
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

	glTranslatef(0.0f, -1.0f, -5.0f); 
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);  
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

    pObj = gluNewQuadric();  
    gluQuadricNormals(pObj, GLU_SMOOTH);

    glPushMatrix(); 
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // Z crescendo para cima da tela

    //cabeca
    glPushMatrix();

    if(ex){
        if(tempo > 3){
             glRotatef(cabecaExorcista, 0.0f, 0.0f, 1.0f);
        }
    }
    glRotatef(cabecaReverencia, 1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, 1.0f);
    glScalef(0.5f, 0.5f, 0.5f);
    glutSolidCube(1.0f);
    glPopMatrix();

    //tronco
    glPushMatrix();
    glColor3f(0.0f, 1.0f, 0.0f);
    glScalef(1.0f, 1.0f, 1.5f);
    glutSolidCube(1.0f);
    glPopMatrix();

    //braco direito
    glPushMatrix();
    glColor3f(0.0f, 1.0f, 1.0f);
    glRotatef(xRotBracoDir, 3.0f, 0.0f, 0.0f);
    glRotatef(yRotBracoDir, 0.0f, -1.0f, 0.0f);
    glTranslatef(0.75f, 0.0f, 0.10f);
    glScalef(0.5f, 0.5f, 1.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    //braco esquerdo
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 1.0f);
    glRotatef(-xRotBracoEsq, -3.0f, 0.0f, 0.0f);

    glRotatef(yRotBracoEsq, 0.0f, 1.0f, 0.0f);
    glTranslatef(-0.75f, 0.0f, 0.10f);
    glScalef(0.5f, 0.5f, 1.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPopMatrix(); // rotacao -90 em x

    glPopMatrix();
    // Buffer swap //chama o glFlush implicitamente

    glutSwapBuffers();
}    
  
  
int main(int argc, char *argv[]){

    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  
    glutInitWindowSize(800, 600);  
    glutCreateWindow("Robo humanoide - Quadricas");  
    glutReshapeFunc(ChangeSize);  
    glutSpecialFunc(SpecialKeys);

    glutMouseFunc(Mouse);

    glutDisplayFunc(RenderScene);
    glutKeyboardFunc(TeclasPressionadas);  
    SetupRC();
    glutTimerFunc(10, animacao, 0);  //chamo a funcao 10 vezes  
    glutMainLoop();  
      
    return 0; 

} 


void Mouse(int button, int state, int mouseX, int mouseY){
    GLint hit;
    if (button == GLUT_LEFT_BUTTON) {
       printf("Botao esquerda\n");
       xRotBracoEsq += 5.0f;
    }
    else if(button == GLUT_MIDDLE_BUTTON) {
        printf("Botao meio\n");
        ex = 0;
    }

    else if(button == GLUT_RIGHT_BUTTON) {
       printf("Botao direito\n");
       xRotBracoDir += 5.0f;
    }

    xRotBracoEsq = (GLfloat)((const int)xRotBracoEsq % 90);  
    xRotBracoDir = (GLfloat)((const int)xRotBracoDir % 90);
    glutPostRedisplay();
}

void animacao(int v){
     // https://community.khronos.org/t/gluttimerfunc/24407/2
    tempo++;
    cabecaExorcista += 1.0f;
    if(tempo >= 30){
        tempo = 0;
    }
    glutTimerFunc(velocidade, animacao, 0); // velocidade e' frequencia qu quero chamar animacao
    glutPostRedisplay();
}