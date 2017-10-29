typedef float point2[2];

#include <windows.h>
#include <iostream> //dla cout/cin
#include <gl/gl.h>
#include <gl/glut.h>

using namespace std;

int perturbationLevel; // Poziom deformacji dywanu (0-20)
int numberOfStepsToDraw; // Ilosc krokow dywanu do narysowania (0-5)
bool askUser; // Czy pytac użytwkownika o wartosci powyzszych zmiennych

// Rekurencyjna funkcja rysujaca dywan
void drawCarpet(int numberOfStepsToDraw, point2 leftTopCorner, point2 rightBottomCorner) {
    float sideOfSquare = 
    if (numberOfStepsToDraw == 0) {
        point2 finalLeftTopCorner = { leftTopCorner[0], leftTopCorner[1] };
        point2 finalRightTopCorner = { rightBottomCorner[0], leftTopCorner[1] };
        point2 finalLeftBottomCorner = { leftTopCorner[0], rightBottomCorner[1] };
        point2 finalRightBottomCorner = { rightBottomCorner[0], rightBottomCorner[1] };

        glBegin(GL_QUADS);
            glVertex2fv(finalRightTopCorner);
            glVertex2fv(finalRightBottomCorner);
            glVertex2fv(finalLeftBottomCorner);
            glVertex2fv(finalLeftTopCorner);
        glEnd();
    } else if (numberOfStepsToDraw < 0) {
        cout<<"Cos jest nie tak. Aplikacja nie moze kontynuowac."<<endl;
        return;
    } else {
        numberOfStepsToDraw--;

    }
}

// Funkcaja określająca, co ma być rysowane
// (zawsze wywoływana, gdy trzeba przerysować scenę)
void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT); // Czyszczenie okna aktualnym kolorem czyszczącym

    glColor3f(1.0f, 0.0f, 0.0f); // TODO: random color

    point2 leftTopCorner = { -80.0f, 80.0f };
    point2 rightBottomCorner = { 80.0f, -80.0f };

    drawCarpet(numberOfStepsToDraw, leftTopCorner, rightBottomCorner);

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
    // srand(time(0)); // ziarno dla liczb pseudo losowych
    askUser = false;

    if (askUser) {
        do {
            cout << "Podaj stopien zdeformowania (0-20):";
            cin >> perturbationLevel;
        } while (perturbationLevel < 0 || perturbationLevel > 20);

        do {
            cout << "Podaj ilosc krokow (poziom rekurencji) (0-5):";
            cin >> numberOfStepsToDraw;
        } while (numberOfStepsToDraw < 0 || numberOfStepsToDraw > 5);
    } else {
        // Jesli chcesz podac dane bez pytania uzytkownika ustaw askUser na false i podaj tu dane
        perturbationLevel = 0;
        numberOfStepsToDraw = 0;
    }

    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    // Ustawienie trybu wyświetlania
    // GLUT_SINGLE - pojedynczy bufor wyświetlania
    // GLUT_RGBA - model kolorów RGB

    glutCreateWindow("Dywan Sierpinskiego z perturbacjami");
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