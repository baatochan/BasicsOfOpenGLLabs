typedef float point2[2];

#include <windows.h>
#include <iostream> //dla cout/cin
#include <gl/gl.h>
#include <gl/glut.h>
#include <stdlib.h> // dla rand
#include <time.h> //dla time

int deformacja = 0; // Poziom deformacji dywanu (0-20)
int stopienRekurencji = 1; // Ilosc krokow dywanu do narysowania (0-5)

float randomOffset(float bokKwadratu) {
    if (deformacja == 0) return 0;
    int randomValue = 2 * (rand() - (RAND_MAX / 2)); // losowa liczba z zakresu [-RAND_MAX, RAND_MAX]
    float dzielnik = (float)RAND_MAX / 2 * bokKwadratu;
    float przesuniecie = ((float)randomValue * deformacja) / dzielnik;
    return przesuniecie;
}

// Rekurencyjna funkcja rysujaca dywan
void rysujDywan(int stopienRekurencji, point2 lewyGornyRog, point2 prawyDolnyRog) {
    float bokKwadratu = abs(lewyGornyRog[0] - prawyDolnyRog[0]);
    std::cout << bokKwadratu << " " << stopienRekurencji << std::endl;
    if (stopienRekurencji == 0) {
        point2 ZdefLewyGornyRog = { lewyGornyRog[0] + randomOffset(bokKwadratu), lewyGornyRog[1] + randomOffset(bokKwadratu) };
        point2 ZdefPrawyGornyRog = { prawyDolnyRog[0] + randomOffset(bokKwadratu), lewyGornyRog[1] + randomOffset(bokKwadratu) };
        point2 ZdefLewyDolnyRog = { lewyGornyRog[0] + randomOffset(bokKwadratu), prawyDolnyRog[1] + randomOffset(bokKwadratu) };
        point2 ZdefPrawyDolnyRog = { prawyDolnyRog[0] + randomOffset(bokKwadratu), prawyDolnyRog[1] + randomOffset(bokKwadratu) };


        glBegin(GL_QUADS);
        glVertex2fv(ZdefPrawyGornyRog);
        glVertex2fv(ZdefPrawyDolnyRog);
        glVertex2fv(ZdefLewyDolnyRog);
        glVertex2fv(ZdefLewyGornyRog);
        /*glVertex2f(80, 80);
        glVertex2f(80, -80);
        glVertex2f(-80, -80);
        glVertex2f(-80, 80);*/
        glEnd();
    }
    else {
        stopienRekurencji--;
        point2 lewyMniejszego;
        point2 prawyMniejszego;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (i == 1 && j == 1) continue;
                lewyMniejszego[0] = lewyGornyRog[0] + j * bokKwadratu / 3;
                lewyMniejszego[1] = lewyGornyRog[1] + i * bokKwadratu / 3;
                prawyMniejszego[0] = (prawyDolnyRog[0] - 2 * bokKwadratu) + j * bokKwadratu / 3;
                prawyMniejszego[1] = (prawyDolnyRog[1] - 2 * bokKwadratu) + i * bokKwadratu / 3;
                std::cout << lewyMniejszego[0] << " " << lewyMniejszego[1] << " " << prawyMniejszego[0] << " " << prawyMniejszego[1] << std::endl;
                rysujDywan(stopienRekurencji, lewyMniejszego, prawyMniejszego);
            }
        }
    }
}

// Funkcaja określająca, co ma być rysowane
// (zawsze wywoływana, gdy trzeba przerysować scenę)
void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT); // Czyszczenie okna aktualnym kolorem czyszczącym

    glColor3f(1.0f, 0.0f, 0.0f); // TODO: random color

    point2 lewyGornyRog = { -80.0f, 80.0f };
    point2 prawyDolnyRog = { 80.0f, -80.0f };

    rysujDywan(stopienRekurencji, lewyGornyRog, prawyDolnyRog);

    glFlush(); // Przekazanie poleceń rysujących do wykonania
}

// Funkcja ustalająca stan renderowania
void MyInit(void)
{
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    // Kolor okna wnętrza okna - ustawiono na szary
}

// Funkcja służąca do kontroli zachowania proporcji rysowanych obiektów
// niezależnie od rozmiarów okna graficznego
void ChangeSize(GLsizei horizontal, GLsizei vertical)
// Parametry horizontal i vertical (szerokość i wysokość okna) są
// przekazywane do funkcji za każdym razem, gdy zmieni się rozmiar okna
{
    GLfloat AspectRatio;
    // Deklaracja zmiennej AspectRatio określającej proporcję wymiarów okna

    if (vertical == 0)
        // Zabezpieczenie pzred dzieleniem przez 0
        vertical = 1;

    glViewport(0, 0, horizontal, vertical);
    // Ustawienie wielkościokna okna urządzenia (Viewport)
    // W tym przypadku od (0,0) do (horizontal, vertical)

    glMatrixMode(GL_PROJECTION);
    // Określenie układu współrzędnych obserwatora
    glLoadIdentity();
    // Określenie przestrzeni ograniczającej
    AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
    // Wyznaczenie współczynnika proporcji okna
    // Gdy okno na ekranie nie jest kwadratem wymagane jest
    // określenie okna obserwatora.
    // Pozwala to zachować właściwe proporcje rysowanego obiektu
    // Do określenia okna obserwatora służy funkcja glOrtho(...)

    if (horizontal <= vertical)
        glOrtho(-100.0, 100.0, -100.0 / AspectRatio, 100.0 / AspectRatio, 1.0, -1.0);
    else
        glOrtho(-100.0*AspectRatio, 100.0*AspectRatio, -100.0, 100.0, 1.0, -1.0);
    glMatrixMode(GL_MODELVIEW);
    // Określenie układu współrzędnych
    glLoadIdentity();
}

// Główny punkt wejścia programu. Program działa w trybie konsoli
int main(int argc, char* argv[])
{
    /*// Ukrycvie okna konsoli
    HWND con = GetConsoleWindow();
    ShowWindow(con, SW_HIDE);*/
    /*srand(time(0)); // ziarno dla liczb pseudo losowych

    do {
        std::cout << "Podaj stopien zdeformowania (0-20):";
        std::cin >> deformacja;
    } while (deformacja < 0 || deformacja > 20);

    do {
        std::cout << "Podaj ilosc krokow (poziom rekurencji) (0-5):";
        std::cin >> stopienRekurencji;
    } while (stopienRekurencji < 0 || stopienRekurencji > 5);
    */

    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    // Ustawienie trybu wyświetlania
    // GLUT_SINGLE - pojedynczy bufor wyświetlania
    // GLUT_RGBA - model kolorów RGB

    glutCreateWindow("Dywan Sierpińskiego z perturbacjami");
    // Utworzenie okna i określenie treści napisu w nagłówku okna

    glutDisplayFunc(RenderScene);
    // Określenie, że funkcja RenderScene będzie funkcją zwrotną (callback)
    // Biblioteka GLUT będzie wywoływała tą funkcję za każdym razem, gdy
    // trzeba będzie przerysować okno


    glutReshapeFunc(ChangeSize);
    // Dla aktualnego okna ustala funkcję zwrotną odpowiedzialną za
    // zmiany rozmiaru okna

    MyInit();
    // Funkcja MyInit (zdefiniowana powyżej) wykonuje wszelkie
    // inicjalizacje konieczneprzed przystąpieniem do renderowania

    glutMainLoop();
    // Funkcja uruchamia szkielet biblioteki GLUT

    return 0;
}