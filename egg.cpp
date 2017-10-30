/*************************************************************************************/
//  Szkielet programu do tworzenia modelu sceny 3-D z wizualizacją osi
//  układu współrzednych
/*************************************************************************************/
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <iostream>
#include <cmath>
#include <time.h> //dla time

#define numberOfPoints 20

typedef float point3[3];
/*************************************************************************************/

static GLfloat theta[] = {-40, 85, 0}; // trzy kąty obrotu

point3 eggCords[numberOfPoints][numberOfPoints];
point3 eggCordsColors[numberOfPoints][numberOfPoints];
int model = 3;  // 1- punkty, 2- siatka, 3 - wypełnione trójkąty

using namespace std;

void countEggCords() {
    float vmin = 0;
    float vmax = 1;
    float umin = 0;
    float umax = 1;

    float v, u, x, y, z;

    float vSpace = (vmax-vmin)/numberOfPoints; //TODO: nazwac to jakos
    float uSpace = (umax-umin)/numberOfPoints; //TODO: nazwac to jakos

    for (int i = 0; i < numberOfPoints; i++) {
        for (int j = 0; j < numberOfPoints; j++) {
            v = vmin + i*vSpace;
            u = umin + j*uSpace;

            x = -90 * pow(u, 5);
            x += 225 * pow(u, 4);
            x -= 270 * pow(u, 3);
            x += 180 * pow(u, 2);
            x -= 45 * u;
            z = x;
            x *= cos(M_PI * v);

            y = 160 * pow(u, 4);
            y -= 320 * pow(u, 3);
            y += 160 * pow(u, 2);
            y -= 5;

            z *= sin(M_PI * v);

            eggCords[i][j][0] = x;
            eggCords[i][j][1] = y;
            eggCords[i][j][2] = z;
        }
    }
}

// funckja zwracajaca losowa wartosc z zakresu [0,1]; przydatna do podawania losowych kolorow
float getRandomColor() {
    int random = rand() % 10001; //generuj losowa wartosc z zakresu [0, 10000]
    float color = (float)random / 10000; // podziel na 10k, wiec zakres zmienia sie na [0,1]

    return color;
}

void loadRandomColors() {
    for (int i = 0; i < numberOfPoints; i++) {
        for (int j = 0; j < numberOfPoints; j++) {
            eggCordsColors[i][j][0] = getRandomColor();
            eggCordsColors[i][j][1] = getRandomColor();
            eggCordsColors[i][j][2] = getRandomColor();
        }
    }
}

void drawEgg() {
    if (model == 1) {
        glBegin(GL_POINTS);
        for (int i = 0; i < numberOfPoints; i++) {
            for (int j = 0; j < numberOfPoints; j++) {
                glVertex3fv(eggCords[i][j]);
            }
        }
        glEnd();
    } else if (model == 2) {
        int k = 0;
        for (int i = 0; i < numberOfPoints; i++) {
            glBegin(GL_LINES);
            for (int j = 0; j < numberOfPoints; j++) {
                glVertex3fv(eggCords[j][i]);
            }
            glEnd();
        }
        for (int i = 0; i < numberOfPoints; i++) {
            glBegin(GL_LINES);
            for (int j = 0; j < numberOfPoints; j++) {
                glVertex3fv(eggCords[i][j]);
            }
            glEnd();
        }
        for (int i = 0; i < numberOfPoints; i++) {
            glBegin(GL_LINES);
            for (int j = 0; j < numberOfPoints; j++) {
                k = i-j;
                if (k < 0)
                    k += numberOfPoints;
                glVertex3fv(eggCords[j][k]);
            }
            glEnd();
        }
    } else if (model == 3) {
        int k = 0;
        int l = 0;
        for (int i = 0; i < numberOfPoints; i++) {
            for (int j = 0; j < numberOfPoints; j++) {
                k = j+1;
                if (k >= numberOfPoints) k = 0;
                l = i+1;
                if (l >= numberOfPoints) l = 0;

                glBegin(GL_TRIANGLES);
                    glColor3fv(eggCordsColors[i][j]);
                    glVertex3fv(eggCords[i][j]);

                    glColor3fv(eggCordsColors[i][k]);
                    glVertex3fv(eggCords[i][k]);

                    glColor3fv(eggCordsColors[l][j]);
                    glVertex3fv(eggCords[l][j]);
                glEnd();
                glBegin(GL_TRIANGLES);
                    glColor3fv(eggCordsColors[i][k]);
                    glVertex3fv(eggCords[i][k]);

                    glColor3fv(eggCordsColors[l][j]);
                    glVertex3fv(eggCords[l][j]);

                    glColor3fv(eggCordsColors[l][k]);
                    glVertex3fv(eggCords[l][k]);
                glEnd();
            }
        }
    } else {
        model = 1;
        drawEgg();
    }
}

// Funkcja rysująca osie układu współrzędnych
void Axes(void)
{
    point3  x_min = {-5.0, 0.0, 0.0};
    point3  x_max = { 5.0, 0.0, 0.0};
// początek i koniec obrazu osi x

    point3  y_min = {0.0, -5.0, 0.0};
    point3  y_max = {0.0,  5.0, 0.0};
// początek i koniec obrazu osi y

    point3  z_min = {0.0, 0.0, -5.0};
    point3  z_max = {0.0, 0.0,  5.0};
//  początek i koniec obrazu osi y
    glColor3f(1.0f, 0.0f, 0.0f);  // kolor rysowania osi - czerwony
    glBegin(GL_LINES); // rysowanie osi x
    glVertex3fv(x_min);
    glVertex3fv(x_max);
    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f);  // kolor rysowania - zielony
    glBegin(GL_LINES);  // rysowanie osi y
    glVertex3fv(y_min);
    glVertex3fv(y_max);
    glEnd();

    glColor3f(0.0f, 0.0f, 1.0f);  // kolor rysowania - niebieski
    glBegin(GL_LINES); // rysowanie osi z
    glVertex3fv(z_min);
    glVertex3fv(z_max);
    glEnd();
}
/*************************************************************************************/
// Funkcja określająca co ma być rysowane (zawsze wywoływana gdy trzeba
// przerysować scenę)

void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// Czyszczenie okna aktualnym kolorem czyszczącym

    glLoadIdentity();
// Czyszczenie macierzy bieżącej
    Axes();
// Narysowanie osi przy pomocy funkcji zdefiniowanej wyżej

    glRotatef(theta[0], 1.0, 0.0, 0.0);

    glRotatef(theta[1], 0.0, 1.0, 0.0);

    glRotatef(theta[2], 0.0, 0.0, 1.0);

    drawEgg();

    glFlush();
// Przekazanie poleceń rysujących do wykonania

    glutSwapBuffers();
//
}

void spinEgg()
{

    //theta[0] -= 0.5;
    if( theta[0] > 360.0 ) theta[0] -= 360.0;

    theta[1] -= 0.01;
    if( theta[1] > 360.0 ) theta[1] -= 360.0;

    //theta[2] -= 0.5;
    if( theta[2] > 360.0 ) theta[2] -= 360.0;

    glutPostRedisplay(); //odświeżenie zawartości aktualnego okna
}

void keys(unsigned char key, int x, int y)
{
    if(key == 'p') model = 1;
    if(key == 'w') model = 2;
    if(key == 's') model = 3;

    RenderScene(); // przerysowanie obrazu sceny
}

/*************************************************************************************/
// Funkcja ustalająca stan renderowania

void MyInit(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
// Kolor czyszcący (wypełnienia okna) ustawiono na czarny
}
/*************************************************************************************/
// Funkcja ma za zadanie utrzymanie stałych proporcji rysowanych
// w przypadku zmiany rozmiarów okna.
// Parametry vertical i horizontal (wysokość i szerokość okna) są
// przekazywane do funkcji za każdym razem gdy zmieni się rozmiar okna.

void ChangeSize(GLsizei horizontal, GLsizei vertical )
{
    GLfloat AspectRatio;
// Deklaracja zmiennej AspectRatio  określającej proporcję
// wymiarów okna
    if(vertical == 0)  // Zabezpieczenie przed dzieleniem przez 0
        vertical = 1;
    glViewport(0, 0, horizontal, vertical);
// Ustawienie wielkościokna okna widoku (viewport)
// W tym przypadku od (0,0) do (horizontal, vertical)
    glMatrixMode(GL_PROJECTION);
// Przełączenie macierzy bieżącej na macierz projekcji
    glLoadIdentity();
// Czyszcznie macierzy bieżącej
    AspectRatio = (GLfloat)horizontal/(GLfloat)vertical;
// Wyznaczenie współczynnika  proporcji okna
// Gdy okno nie jest kwadratem wymagane jest określenie tak zwanej
// przestrzeni ograniczającej pozwalającej zachować właściwe
// proporcje rysowanego obiektu.
// Do okreslenia przestrzeni ograniczjącej służy funkcja
// glOrtho(...)
    if(horizontal <= vertical)
        glOrtho(-7.5,7.5,-7.5/AspectRatio,7.5/AspectRatio,10.0, -10.0);
    else
        glOrtho(-7.5*AspectRatio,7.5*AspectRatio,-7.5,7.5,10.0,-10.0);
    glMatrixMode(GL_MODELVIEW);
// Przełączenie macierzy bieżącej na macierz widoku modelu
    glLoadIdentity();
// Czyszcenie macierzy bieżącej
}
/*************************************************************************************/
// Główny punkt wejścia programu. Program działa w trybie konsoli

int main(int argc, char* argv[])
{
    srand(time(0)); // ziarno dla liczb pseudo losowych

    loadRandomColors();
    countEggCords();

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |GLUT_DEPTH);

    glutInit(&argc, argv);

    glutInitWindowSize(300, 300);

    glutCreateWindow("jajo");

    glutDisplayFunc(RenderScene);
// Określenie, że funkcja RenderScene będzie funkcją zwrotną
// (callback function).  Bedzie ona wywoływana za każdym razem
// gdy zajdzie potrzba przeryswania okna
    glutReshapeFunc(ChangeSize);
// Dla aktualnego okna ustala funkcję zwrotną odpowiedzialną
// zazmiany rozmiaru okna

    glutKeyboardFunc(keys);

    //glutIdleFunc(spinEgg);

    MyInit();
// Funkcja MyInit() (zdefiniowana powyżej) wykonuje wszelkie
// inicjalizacje konieczne  przed przystąpieniem do renderowania
    glEnable(GL_DEPTH_TEST);
// Włączenie mechanizmu usuwania powierzchni niewidocznych

    glutMainLoop();
// Funkcja uruchamia szkielet biblioteki GLUT

    return 0;
}
/*************************************************************************************/