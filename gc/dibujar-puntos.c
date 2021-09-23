//	Program developed by
//
//	Informatika Fakultatea
//	Euskal Herriko Unibertsitatea
//	http://www.ehu.eus/if
//
// to compile it: gcc dibujar-puntos.c -lGL -lGLU -lglut
//
// This example shows :the use of GL_POINTS
//


#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

// texturaren informazioa

#include "cargar-triangulo.h"

extern void load_ppm(char *file, unsigned char **bufferptr, int *dimxptr, int * dimyptr);
unsigned char *bufferra;
int dimx,dimy,num_triangles,indice;
hiruki *triangulosptr;

unsigned char * color_textura(float u, float v)
{
    /* debe devolver un puntero al pixel adecuado, no al primero!! */
    int j, i, pos;
    j = u * dimx;
    i = (1-v)*dimy;
    pos = 3*dimx*i+3*j;//el 3 ya que cada elemento contiene 3, r,g y b

    return(bufferra + pos);
}

static void dibuja(punto *dibujo){
    unsigned char* colorv;
    unsigned char r,g,b;
    colorv=color_textura(dibujo->u,dibujo->v);
    r=colorv[0];
    g=colorv[1];
    b=colorv[2];
    glBegin(GL_POINTS);
    glColor3ub(r,g,b);
    glVertex3f(dibujo->x,dibujo->y,0.);
    glEnd();
}

static void dibujar_triangulo(){
    punto A=triangulosptr[indice].p1,B=triangulosptr[indice].p2,C=triangulosptr[indice].p3;
    punto *pintar=malloc(sizeof (punto));
    float x, y, alfa, beta, gamma, tol=0.00001;//factor de tolerancia
    int xx=-1, yy=-1;//variables para guardar el último punto dibujado
    for(alfa=0.0;alfa<=1.0+tol;alfa+=0.001)
        for(beta=0.0;beta<=1.0+tol;beta+=0.001){
            if(alfa+beta<1-tol){
                gamma=1-(alfa+beta);
            }else{
                gamma=0;
                if(alfa+beta>1+tol){
                    break;
                }
            }
            x=alfa*A.x+beta*B.x+gamma*C.x;
            y=alfa*A.y+beta*B.y+gamma*C.y;


            if(((((int)x)-xx)!=0)||((((int)y)-yy)!=0)) {//comprobamos que este punto no ha sido dibujado previamente debido al lento incremento de alfa, beta y gamma
                pintar->x=x;
                pintar->y=y;
                pintar->u=alfa*A.u+beta*B.u+gamma*C.u;//evitamos calcular estas coordenadas siempre que se calculan x e y
                pintar->v=alfa*A.v+beta*B.v+gamma*C.v;
                dibuja(pintar);
                xx=(int)x;
                yy=(int)y;
            }
        }
}

static void marraztu(void)
{
    float u,v;
    float i,j;
    unsigned char* colorv;
    unsigned char r,g,b;

// borramos lo que haya...
    glClear( GL_COLOR_BUFFER_BIT );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 500.0, 0.0, 500.0,-250.0, 250.0);

// por ahora dibujamos todos los pixels de la ventana de 500x500 con el color que devuelve la función color_textura
// pero hay que llamar a la función que dibuja un triangulo con la textura mapeada:

    //dibujar_triangulo();
    dibujar_triangulo();
    
    glFlush();
}


// This function will be called whenever the user pushes one key
static void teklatua (unsigned char key, int x, int y)
{
    switch(key)
    {
        case 13:
            
            printf ("ENTER: que hay que dibujar el siguiente triángulo.\n");
            indice++;
            if(indice == num_triangles){
                indice=0;
            }
            break;
        case 27:  // <ESC>
            exit( 0 );
            break;
        default:
            printf("%d %c\n", key, key );
    }

// The screen must be drawn to show the new triangle
    glutPostRedisplay();
}


int main(int argc, char** argv)
{

    printf("This program draws points in the viewport \n");
    printf("Press <ESC> to finish\n");
    glutInit(&argc,argv);
    glutInitDisplayMode ( GLUT_RGB );
    glutInitWindowSize ( 500, 500 );
    glutInitWindowPosition ( 100, 100 );
    glutCreateWindow( "GL_POINTS" );

    glutDisplayFunc( marraztu );
    glutKeyboardFunc( teklatua );
    /* we put the information of the texture in the buffer pointed by bufferra. The dimensions of the texture are loaded into dimx and dimy */
    load_ppm("foto.ppm", &bufferra, &dimx, &dimy);
    cargar_triangulos(&num_triangles, &triangulosptr);

    glClearColor( 0.0f, 0.0f, 0.7f, 1.0f );

    glutMainLoop();

    return 0;
}
