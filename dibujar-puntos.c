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
    return(bufferra);
}

static void dibuja(int x,int y){
    unsigned char* colorv;
    unsigned char r,g,b;
    colorv=color_textura(0.2,0.3);
    r=colorv[0];
    g=colorv[1];
    b=colorv[2];
    glBegin(GL_POINTS);
    glColor3ub(r,g,b);
    glVertex3f(x,y,0.);
    glEnd();
}

static void dibujarSegmento(int x1,int x2,int y){
    int izq=x2,dcha=x1;
    if(x1<x2){
        izq=x1;
        dcha=x2;
    }
    int i;
    for(i=izq;i<=dcha;i++){
        dibuja(i,y);
    }
}

static void dibujar_triangulo_algebra(){
    punto A=triangulosptr[indice].p1,B=triangulosptr[indice].p2,C=triangulosptr[indice].p3;
    float x,y,alfa,beta,gamma,tol=0.00001;//factor de tolerancia
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
            dibuja(x,y);
        }
}

static void dibujar_triangulo(){
    punto arriba, abajo, medio;
    
    if((triangulosptr+indice)->p1.y>(triangulosptr+indice)->p2.y){
        if((triangulosptr+indice)->p1.y>(triangulosptr+indice)->p3.y){
            arriba=(triangulosptr+indice)->p1;
            if((triangulosptr+indice)->p2.y>(triangulosptr+indice)->p3.y){
                abajo=(triangulosptr+indice)->p3;
                medio=(triangulosptr+indice)->p2;
            }else{
                abajo=(triangulosptr+indice)->p2;
                medio=(triangulosptr+indice)->p3;
            }
        }else{
            medio=(triangulosptr+indice)->p1;
            arriba=(triangulosptr+indice)->p3;
            abajo=(triangulosptr+indice)->p2;
        }
    }else{
        if((triangulosptr+indice)->p2.y>(triangulosptr+indice)->p3.y){
            arriba=(triangulosptr+indice)->p2;
            if((triangulosptr+indice)->p3.y>(triangulosptr+indice)->p1.y){
                medio=(triangulosptr+indice)->p3;
                abajo=(triangulosptr+indice)->p1;
            }else{
                medio=(triangulosptr+indice)->p1;
                abajo=(triangulosptr+indice)->p3;
            }
        }else{
            abajo=(triangulosptr+indice)->p1;
            medio=(triangulosptr+indice)->p2;
            arriba=(triangulosptr+indice)->p3;
        }
    }

    float e1=0.0,e2=0.0,e3=0.0, m1, m2,m3=((medio.y-abajo.y)/(medio.x-abajo.x));

    //Usamos pendientes invertidas
    if((arriba.y-medio.y)==0){
        m1=-1000;//número considerado infinito en este caso
    }else{
        m1=((arriba.x-medio.x)/(arriba.y-medio.y));
    }

    if((arriba.y-abajo.y)==0){
        m2=-1000;//número considerado infinito en este caso
    }else {
        m2 = ((arriba.x - abajo.x) / (arriba.y - abajo.y));
    }

    if((medio.y-abajo.y)==0){
        m3=-1000;//número considerado infinito en este caso
    }else{
        m3=((medio.x-abajo.x)/(medio.y-abajo.y));
    }

    int yi,x1=arriba.x,x2=arriba.x,x3=medio.x;
    dibuja(arriba.x,arriba.y);
    dibuja(abajo.x,abajo.y);
    if(m1==-1000){//tienen la misma y
        //dibujo el segmento
        dibujarSegmento(arriba.x,medio.x,arriba.y);



    }else{
        for(yi=arriba.y-1;yi>medio.y;yi--){
            e1+=m1;
            e2+=m2;
            if(e1<=-1){//para saber si va a la izquierda o derecha
                while(e1<=-1){
                    e1++;
                    x1++;
                }
            }else if(e1>=1){
                while(e1>=1){
                    e1--;
                    x1--;
                }
            }

            if(e2<=-1){
                while(e2<=-1){
                    e2++;
                    x2++;
                }
            }else if(e2>=1){
                while(e2>=1){
                    e2--;
                    x2--;
                }
            }
            //dibujo el segmento x1,x2,yi
            dibujarSegmento(x1,x2,yi);
        }
    }
    if(m3==-1000){
        //dibujo segmento
        dibujarSegmento(medio.x,abajo.x,medio.y);
    }else{
        //dibujo segmento medio.x, x2, medio.y
        dibujarSegmento(medio.x,x2,medio.y);
        for(yi=medio.y-1;yi>abajo.y;yi--){
            e2+=m2;
            e3+=m3;
            if(e2<=-1){//para saber si va a la izquierda o derecha
                while(e2<=-1){
                    e2++;
                    x2++;
                }
            }else if(e2>=1){
                while(e2>=1){
                    e2--;
                    x2--;
                }
            }

            if(e3<=-1){
                while(e3<=-1){
                    e3++;
                    x3++;
                }
            }else if(e3>=1){
                while(e3>=1){
                    e3--;
                    x3--;
                }
            }
            //dibujo el segmento x3,x2,yi
            dibujarSegmento(x3,x2,yi);
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
    dibujar_triangulo_algebra();
    
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
