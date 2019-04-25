#include <GL/glut.h>
#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define ESCAPE 27
#define NUM_PARTICULAS 3000
//#define GRAVIDADE 0.0004

float gravidade = 0.0004;

struct s_pf {
  float x, y, veloc_x, veloc_y;
  unsigned tempoDeVida;
} particulas[NUM_PARTICULAS];

int janela;

int sangue = 0;

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

void InicializaParticulas(int cond)
{
  int i;

  if(cond){
      usleep(200000 + rand() % 2000000);
  }

  for(i=0;i<NUM_PARTICULAS;i++) {
    float velocidade = (float)(rand() % 100)/5000.0;
    int angulo = rand() % 360;
    particulas[i].veloc_x = 0.0;
    particulas[i].veloc_y =  -velocidade;
    particulas[i].x = ((float)rand()/(float)(RAND_MAX)) * 3;
    particulas[i].y = ((float)rand()/(float)(RAND_MAX)) * 0.3;
    particulas[i].tempoDeVida = 2*(rand() % 100);
  }
}


void InitGL(int Width, int Height)
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
  glClearDepth(1.0);
  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);			

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();				

  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);

  glMatrixMode(GL_MODELVIEW);

  InicializaParticulas(0);
}

void ReSizeGLScene(int largura, int altura)
{
  if (altura==0){
     altura=1;
  }

  glViewport(0, 0, largura, altura);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(45.0f, (GLfloat)largura/(GLfloat)altura, 0.1f, 100.0f);
  glMatrixMode(GL_MODELVIEW);
}

void DesenhaCena()
{
  int i, particulasAtivas=0;
  GLUquadricObj *pObj;    // Quadrica
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  pObj = gluNewQuadric();  
	gluQuadricNormals(pObj, GLU_SMOOTH);

  glPushMatrix();
  glTranslatef(-1.5f,1.0f,-6.0f);
  glColor3f(1.0f, 1.0f, 1.0f); 
  
  glBegin(GL_POINTS);
  for(i=0;i<NUM_PARTICULAS;i++) {
    if(particulas[i].tempoDeVida) {
      particulasAtivas++;
      //particulas[i].veloc_y -= GRAVIDADE;
      particulas[i].veloc_y -= gravidade;
      particulas[i].x += particulas[i].veloc_x;
      particulas[i].y += particulas[i].veloc_y;
      particulas[i].tempoDeVida--;

	  if(particulas[i].tempoDeVida==0){
	  	particulas[i].tempoDeVida = 2*(rand() % 100);
	  	particulas[i].x = ((float)rand()/(float)(RAND_MAX)) * 3;
    	particulas[i].y = ((float)rand()/(float)(RAND_MAX)) * 0.3;
    	float velocidade = (float)(rand() % 100)/5000.0;
    	particulas[i].veloc_y = -velocidade;
	  }
      if(sangue){
          glColor3f(1.0f, 0.0f, 0.0f);
      }
      glVertex3f( particulas[i].x, particulas[i].y, 0.0f);
    }
  }
  glEnd();

//Inicio Corpo Boneco
  glPushMatrix();

  glTranslatef(1.5f, -2.0f, -7.0f);
  glColor3f(1.0f, 1.0f, 1.0f);  
	gluSphere(pObj, .40f, 26, 13);  // Esfera de baixo 

  glTranslatef(0.0f, .550f, 0.0f); // esfera do centro 
	gluSphere(pObj, .3f, 26, 13);

  glTranslatef(0.0f, 0.45f, 0.0f); // Esfera de cima
	gluSphere(pObj, 0.24f, 26, 13);
 

  // Olhos
	glColor3f(0.0f, 0.0f, 0.0f);  
	glTranslatef(0.1f, 0.1f, 0.21f);
  gluSphere(pObj, 0.05f, 26, 13);    

	glTranslatef(-0.2f, 0.0f, 0.0f);  
  gluSphere(pObj, 0.05f, 26, 13);


  glColor3f(1.0f, 0.3f, 0.3f);
  glTranslatef(0.1f, -0.12f, 0.0f); 
	gluCylinder(pObj, 0.04f, 0.0f, 0.3f, 26, 13);

  desenhaBoca(pObj);

  botoesRoupa(pObj);   
  glPopMatrix();
//Fim Corpo Boneco

  // Chapeu 
	glPushMatrix();  
	glColor3f(0.0f, 0.0f, 0.0f);  
  glTranslatef(1.5f, -0.725f, -7.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);  
	gluCylinder(pObj, 0.17f, 0.17f, 0.4f, 26, 13);  

	// Base do chapeu 
	glDisable(GL_CULL_FACE);  
  gluDisk(pObj, 0.17f, 0.38f, 26, 13);  
	glEnable(GL_CULL_FACE);  

	glTranslatef(0.0f, 0.0f, 0.40f);  
  gluDisk(pObj, 0.0f, 0.17f, 26, 13);    
	glPopMatrix();



  glPopMatrix();
  glutSwapBuffers();

  if(!particulasAtivas){
      InicializaParticulas(1);
  } 

}

void keyPressed(unsigned char tecla, int x, int y) 
{
  usleep(100);

  if(tecla == ESCAPE){ 
      glutDestroyWindow(janela); 
		  exit(0);                   
  }

  if(tecla == 's'){
    if(!sangue){
      sangue = 1;
    }
    else{
        sangue = 0;
    }
    
    glutPostRedisplay();
  }

  if(tecla == 'f'){
    if(gravidade > 0.0004){
        gravidade = 0.0004;
    }
    else{
      gravidade = 0.005;
    }
    glutPostRedisplay();
  }
}

int main(int argc, char **argv) 
{  
  glutInit(&argc, argv);  
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  
  glutInitWindowSize(640, 480);  
  glutInitWindowPosition(0, 0);  
  janela = glutCreateWindow("Neve");  
  glutDisplayFunc(&DesenhaCena);  
  //glutFullScreen();
  glutIdleFunc(&DesenhaCena);
  glutReshapeFunc(&ReSizeGLScene);
  glutKeyboardFunc(&keyPressed);
  InitGL(640, 480);
  glutMainLoop();  

  return 0;
}

