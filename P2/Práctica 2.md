# Práctica – Uso de ncurses y desarrollo de un juego tipo Pong

**Alumno:** Miguel Moreno Murcia  
**Curso/Grupo:** 4º  
**Asignatura:** PDIH

El objetivo de esta práctica es aprender a utilizar la librería **ncurses** en Linux para el desarrollo de aplicaciones en terminal con entrada/salida interactiva. En concreto, se busca manejar la terminal en modo texto avanzado, detectar entrada de teclado sin bloqueo, dibujar elementos en pantalla (texto, marcos y figuras), controlar el refresco de la pantalla e implementar un juego sencillo tipo Pong.

Para la instalación de la librería ncurses en sistemas basados en Debian/Ubuntu se utiliza:

```bash
sudo apt update
sudo apt install libncurses5-dev libncursesw5-dev
```

La compilación del programa se realiza con:

```bash
gcc pong.c -o pong -lncurses
```

y su ejecución mediante:

```bash
./pong
```

El programa implementa un juego tipo Pong en terminal con una pantalla inicial, una mecánica de juego basada en el movimiento de una pelota y una pala, un sistema de puntuación y una pantalla final con el resultado, permitiendo además repetir la partida o salir.

La inicialización de ncurses se realiza con:

```c
initscr();
noecho();
cbreak();
curs_set(FALSE);
keypad(stdscr, TRUE);
```

donde se inicia el modo ncurses, se desactiva la salida automática de caracteres, se habilita la lectura inmediata de teclas, se oculta el cursor y se activan las teclas especiales.

A continuación, se configuran colores:

```c
start_color();
init_pair(1, COLOR_GREEN, COLOR_BLACK);
init_pair(2, COLOR_WHITE, COLOR_BLACK);
```

Antes de comenzar el juego se muestra una pantalla de bienvenida con instrucciones:

```c
mvprintw(max_y/2 - 2, max_x/2 - 10, "=== JUEGO PONG ===");
mvprintw(max_y/2,     max_x/2 - 15, "W/S para mover la pala");
mvprintw(max_y/2 + 1, max_x/2 - 15, "No dejes pasar la pelota!");
mvprintw(max_y/2 + 3, max_x/2 - 12, "Pulsa ENTER para jugar");
```

y se espera la pulsación de ENTER:

```c
while(getch() != 10);
```

Durante el juego, los elementos principales son la pelota, la pala y el marcador. La pelota se representa con el carácter `"O"`:

```c
mvprintw(y, x, "O");
```

y la pala con varios caracteres `"|"`:

```c
for(int i = 0; i < PADDLE_SIZE; i++) {
    mvprintw(yc + i, xc, "|");
}
```

El control de la pala se realiza mediante teclado:

```c
if (ch == 'w' && yc > 1)
    yc--;
else if (ch == 's' && yc < max_y - PADDLE_SIZE - 1)
    yc++;
```

El movimiento de la pelota se basa en direcciones horizontales y verticales:

```c
int next_x = x + directionx;
int next_y = y + directiony;
```

y se actualiza en cada iteración con un retardo:

```c
usleep(DELAY);
```

Las colisiones se gestionan de la siguiente forma:

- Rebote vertical en bordes superior e inferior invirtiendo `directiony`.
- Rebote con la pala invirtiendo `directionx` y aumentando la puntuación.
- Rebote en el borde derecho invirtiendo la dirección horizontal.
- Si la pelota cruza el borde izquierdo, se termina la partida.

Al finalizar la partida se muestra una pantalla final con el resultado:

```c
if (score >= 10)
    mvprintw(max_y/2 - 1, max_x/2 - 5, "HAS GANADO!");
else
    mvprintw(max_y/2 - 1, max_x/2 - 5, "HAS PERDIDO!");

mvprintw(max_y/2, max_x/2 - 7, "Puntuacion: %d", score);
mvprintw(max_y/2 + 2, max_x/2 - 12, "¿Jugar otra vez? (s/n)");
```

Si el usuario pulsa `s`, el juego se reinicia; en caso contrario, el programa finaliza.

Finalmente, se cierra ncurses correctamente con:

```c
endwin();
```