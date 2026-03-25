// gcc pong.c -o pong -lncurses

#include <ncurses.h>
#include <unistd.h>

#define DELAY 80000
#define PADDLE_SIZE 5

int main() {
    int max_y, max_x;
    int ch;

    initscr();
    noecho();
    cbreak();
    curs_set(FALSE);        // Oculta el cursor
    keypad(stdscr, TRUE);   // Habilita teclas especiales

    // Colores
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK); // juego
    init_pair(2, COLOR_WHITE, COLOR_BLACK); // texto

    while (1) {
        int x = 10, y = 5;
        int directionx = 1, directiony = 1;

        int xc = 2;
        int yc = 10;

        int score = 0;
        int hit = 0;

        getmaxyx(stdscr, max_y, max_x);

        // Pantalla inicial
        nodelay(stdscr, FALSE);
        clear();
        attron(COLOR_PAIR(2));
        box(stdscr, 0, 0);

        mvprintw(max_y/2 - 2, max_x/2 - 10, "=== JUEGO PONG ===");
        mvprintw(max_y/2,     max_x/2 - 15, "W/S para mover la pala");
        mvprintw(max_y/2 + 1, max_x/2 - 15, "No dejes pasar la pelota!");
        mvprintw(max_y/2 + 3, max_x/2 - 12, "Pulsa ENTER para jugar");

        refresh();
        while(getch() != 10);

        nodelay(stdscr, TRUE);

        // Juego
        while(1) {
            clear();
            attron(COLOR_PAIR(1));
            box(stdscr, 0, 0);

            // marcador
            mvprintw(0, 2, "Score: %d", score);

            // pelota
            mvprintw(y, x, "O");

            // pala (más grande)
            for(int i = 0; i < PADDLE_SIZE; i++) {
                mvprintw(yc + i, xc, "|");
            }

            refresh();

            ch = getch();

            // mover pala
            if (ch == 'w' && yc > 1)
                yc--;
            else if (ch == 's' && yc < max_y - PADDLE_SIZE - 1)
                yc++;

            usleep(DELAY);

            int next_x = x + directionx;
            int next_y = y + directiony;

            // rebote vertical
            if (next_y >= max_y - 1 || next_y <= 0) {
                directiony *= -1;
            } else {
                y += directiony;
            }

            // colisión con la pala
            if (next_x <= xc + 1 &&
                next_y >= yc - 1 &&
                next_y <= yc + PADDLE_SIZE) {

                if (!hit) {
                    directionx = 1;
                    score++;
                    hit = 1;
                }
            }

            // rebote derecha
            else if (next_x >= max_x - 1) {
                directionx = -1;
            }

            // pierde
            else if (next_x <= 0) {
                break;
            }

            else {
                x += directionx;
            }
        }

        // Pantalla final
        nodelay(stdscr, FALSE);
        clear();
        attron(COLOR_PAIR(2));
        box(stdscr, 0, 0);

        if (score >= 10)
            mvprintw(max_y/2 - 1, max_x/2 - 5, "HAS GANADO!");
        else
            mvprintw(max_y/2 - 1, max_x/2 - 5, "HAS PERDIDO!");

        mvprintw(max_y/2, max_x/2 - 7, "Puntuacion: %d", score);
        mvprintw(max_y/2 + 2, max_x/2 - 12, "¿Jugar otra vez? (s/n)");

        refresh();

        ch = getch();
        if (ch != 's' && ch != 'S') {
            break;
        }
    }

    endwin();
    return 0;
}