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


// texturaren informazioa

#include "cargar-triangulo.h"

extern void load_ppm(char *file, unsigned char **bufferptr, int *dimxptr, int * dimyptr);
unsigned char *bufferra;
int dimx,dimy,num_triangles;
hiruki *triangulosptr;

unsigned char * color_textura(float u, float v)
{
/* debe devolver un puntero al pixel adecuado, no al primero!! */
return(bufferra);
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

//dibujar_triangulo(triangulosptr[indice]);
hiruki tri;
punto pu1,pu2,pu3;
pu1.x=70;
pu1.y=70;
pu2.x=70;
pu2.y=140;
pu3.x=140;
pu3.y=70;
tri.p1=pu1;
tri.p2=pu2;
tri.p3=pu3;

float a,bb,c;

for(a=0;a<=1;a+=0.001)
    for(bb=0;bb<=1;bb+=0.001){
        if(a+bb<1){
            c=1-a+bb;
        }else if( a+bb==1){
            c=0;
        }else{
            break;
        }
        
        int x,y;

        x=(int)(tri.p1.x*a+ tri.p2.x*bb+tri.p3.x*c);       
        y=(int)(tri.p1.y*a+ tri.p2.y*bb+tri.p3.y*c);   

        colorv=color_textura(0.2,0.3);
        r=colorv[0];
        g=colorv[1];
        b=colorv[2];
        glBegin(GL_POINTS);
        glColor3ub(r,g,b);
        glVertex3f(x,y,0.);
        glEnd();
        
    }
    


/*for (i=0;i<500;i++)
    for (j=0;j<500;j++)
        {
        u = i/500.0;
        v = j/500.0;
        colorv=  color_textura(u, v); // si esta función es correcta se ve la foto en la ventana
        r= colorv[0];
        g=colorv[1];
        b=colorv[2];     
	glBegin( GL_POINTS );
	glColor3ub(r,g,b);
	glVertex3f(i,j,0.);
	glEnd();
	}*/
glFlush();
}
// This function will be called whenever the user pushes one key
static void teklatua (unsigned char key, int x, int y)
{
switch(key)
	{
	case 13: 
		printf ("ENTER: que hay que dibujar el siguiente triángulo.\n");
		/* hacer algo para que se dibuje el siguiente triangulo */
		/*
		indice ++;  // pero si es el último? hay que controlarlo!
		*/
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

void dibujar_triangulo(hiruki triangulo){
/*for (i=0;i<500;i++)
    for (j=0;j<500;j++)
        {
        u = i/500.0;
        v = j/500.0;
        colorv=  color_textura(u, v); // si esta función es correcta se ve la foto en la ventana
        r= colorv[0];
        g=colorv[1];
        b=colorv[2];     
	glBegin( GL_POINTS );
	glColor3ub(r,g,b);
	glVertex3f(i,j,0.);
	glEnd();
	}*/
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
