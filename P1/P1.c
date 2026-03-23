#include <stdio.h>
#include <dos.h>

#define MODOTEXTO 3
#define MODOGRAFICO 4

#define INVISIBLE 0
#define NORMAL    1
#define GRUESO    2

// Variables globales de color
unsigned char cfondo = 0; // fondo por defecto negro
unsigned char ctexto = 7; // texto por defecto azul

//*****************************************//
// Prototipos de funciones
//*****************************************//
int mi_getchar(void);
void mi_putchar(char c);
void pausa(void);
void modovideo(unsigned char modo);
unsigned char char_to_color(char c);
void gotoxy(int x, int y);
void setcursortype(int tipo_cursor);
void setvideomode(unsigned char modo);
int getvideomode(void);
void textcolor(unsigned char color);
void textbackground(unsigned char color);
void clrscr(void);
void cputchar(char c);
char getche(void);
void pixel(int x, int y, unsigned char color);
void recuadro_texto(int x1, int y1, int x2, int y2);
void asciidraw(void);

//*****************************************//
// Funciones auxiliares
//*****************************************//
int mi_getchar(void){
    union REGS inregs, outregs;
    int caracter;

    inregs.h.ah = 1;
    int86(0x21, &inregs, &outregs);

    caracter = outregs.h.al;
    return caracter;
}

void mi_putchar(char c){
    union REGS inregs, outregs;

    inregs.h.ah = 2;
    inregs.h.dl = c;
    int86(0x21, &inregs, &outregs);
}

void pausa(void){
    union REGS inregs, outregs;
    inregs.h.ah = 0x00;
    int86(0x16, &inregs, &outregs);
}

void modovideo(unsigned char modo){
    union REGS inregs, outregs;
    inregs.h.al = modo;
    inregs.h.ah = 0x00;
    int86(0x10, &inregs, &outregs);
}

unsigned char char_to_color(char c){
    if(c >= '0' && c <= '9') return c - '0';
    if(c >= 'A' && c <= 'F') return 10 + (c - 'A');
    if(c >= 'a' && c <= 'f') return 10 + (c - 'a');
    return 0;
}

//*****************************************//
// Funciones de la práctica
//*****************************************//
void gotoxy(int x, int y){
    union REGS inregs, outregs;
    inregs.h.ah = 0x02;
    inregs.h.bh = 0x00;
    inregs.h.dh = y;
    inregs.h.dl = x;
    int86(0x10,&inregs,&outregs);
}

void setcursortype(int tipo_cursor){
    union REGS inregs, outregs;
    inregs.h.ah = 0x01;

    switch(tipo_cursor){
        case INVISIBLE:
            inregs.h.ch = 0x20;
            inregs.h.cl = 0x00;
            break;
        case NORMAL:
            inregs.h.ch = 0x06;
            inregs.h.cl = 0x07;
            break;
        case GRUESO:
            inregs.h.ch = 0x00;
            inregs.h.cl = 0x07;
            break;
    }
    int86(0x10, &inregs, &outregs);
}

void setvideomode(unsigned char modo){
    union REGS inregs, outregs;
    inregs.h.ah = 0x00;
    inregs.h.al = modo;
    int86(0x10, &inregs, &outregs);
}

int getvideomode(void){
    union REGS inregs, outregs;
    inregs.h.ah = 0x0F;
    int86(0x10, &inregs, &outregs);
    return outregs.h.al;
}

void textcolor(unsigned char color){
    ctexto = color;
}

void textbackground(unsigned char color){
    cfondo = color;
}

void clrscr(void){
    union REGS inregs, outregs;
    inregs.h.ah = 0x06;
    inregs.h.al = 0x00;
    inregs.h.bh = 0x07;
    inregs.x.cx = 0x0000;
    inregs.x.dx = 0x184F;
    int86(0x10, &inregs, &outregs);
}

void cputchar(char c){
    union REGS inregs, outregs;
    inregs.h.ah = 0x09;
    inregs.h.al = c;
    inregs.h.bl = (cfondo << 4) | ctexto;
    inregs.h.bh = 0x00;
    inregs.x.cx = 1;
    int86(0x10, &inregs, &outregs);
}

char getche(void){
    union REGS inregs, outregs;
    char c;
    inregs.h.ah = 1;
    int86(0x21, &inregs, &outregs);
    c = outregs.h.al;
    cputchar(c);
    return c;
}

void pixel(int x, int y, unsigned char color){
    union REGS inregs, outregs;
    inregs.x.cx = x;
    inregs.x.dx = y;
    inregs.h.al = color;
    inregs.h.ah = 0x0C;
    int86(0x10, &inregs, &outregs);
}

void recuadro_texto(int x1, int y1, int x2, int y2){
    int x, y;

    gotoxy(x1, y1); cputchar('+');
    gotoxy(x2, y1); cputchar('+');
    gotoxy(x1, y2); cputchar('+');
    gotoxy(x2, y2); cputchar('+');

    for(x = x1 + 1; x < x2; x++){
        gotoxy(x, y1); cputchar('-');
        gotoxy(x, y2); cputchar('-');
    }

    for(y = y1 + 1; y < y2; y++){
        gotoxy(x1, y); cputchar('|');
        gotoxy(x2, y); cputchar('|');
    }
}

void asciidraw(void){
    textcolor(14);
    textbackground(0);

    // Línea 1
    gotoxy(25,2); cputchar('.'); gotoxy(26,2); cputchar('d'); gotoxy(27,2); cputchar('8'); gotoxy(28,2); cputchar('b'); gotoxy(29,2); cputchar('.');

    // Línea 2
    gotoxy(21,3); cputchar('_'); gotoxy(22,3); cputchar('.'); gotoxy(23,3); cputchar('d'); gotoxy(24,3); cputchar('8'); gotoxy(25,3); cputchar('8'); gotoxy(26,3); cputchar('8'); gotoxy(27,3); cputchar('8'); gotoxy(28,3); cputchar('8'); gotoxy(29,3); cputchar('8'); gotoxy(30,3); cputchar('8'); gotoxy(31,3); cputchar('b'); gotoxy(32,3); cputchar('.'); gotoxy(33,3); cputchar('_');

    // Línea 3
    gotoxy(19,4); cputchar('.'); gotoxy(20,4); cputchar('d'); gotoxy(21,4); cputchar('8'); gotoxy(22,4); cputchar('8'); gotoxy(23,4); cputchar('8'); gotoxy(24,4); cputchar('8'); gotoxy(25,4); cputchar('8'); gotoxy(26,4); cputchar('8'); gotoxy(27,4); cputchar('8'); gotoxy(28,4); cputchar('8'); gotoxy(29,4); cputchar('8'); gotoxy(30,4); cputchar('8'); gotoxy(31,4); cputchar('8'); gotoxy(32,4); cputchar('8'); gotoxy(33,4); cputchar('8'); gotoxy(34,4); cputchar('b'); gotoxy(35,4); cputchar('.');

    // Línea 4
    gotoxy(18,5); cputchar('d'); gotoxy(19,5); cputchar('8'); gotoxy(20,5); cputchar('8'); gotoxy(21,5); cputchar('8'); gotoxy(22,5); cputchar('8'); gotoxy(23,5); cputchar('8'); gotoxy(24,5); cputchar('8'); gotoxy(25,5); cputchar('8'); gotoxy(26,5); cputchar('8'); gotoxy(27,5); cputchar('8'); gotoxy(28,5); cputchar('8'); gotoxy(29,5); cputchar('8'); gotoxy(30,5); cputchar('8'); gotoxy(31,5); cputchar('8'); gotoxy(32,5); cputchar('8'); gotoxy(33,5); cputchar('8'); gotoxy(34,5); cputchar('8'); gotoxy(35,5); cputchar('8'); gotoxy(36,5); cputchar('b');

    // Línea 5
    gotoxy(18,6); cputchar('8'); gotoxy(19,6); cputchar('8'); gotoxy(20,6); cputchar('8'); gotoxy(21,6); cputchar('8'); gotoxy(22,6); cputchar('8'); gotoxy(23,6); cputchar('8'); gotoxy(24,6); cputchar('8'); gotoxy(25,6); cputchar('8'); gotoxy(26,6); cputchar('8'); gotoxy(27,6); cputchar('8'); gotoxy(28,6); cputchar('8'); gotoxy(29,6); cputchar('8'); gotoxy(30,6); cputchar('8'); gotoxy(31,6); cputchar('8'); gotoxy(32,6); cputchar('8'); gotoxy(33,6); cputchar('8'); gotoxy(34,6); cputchar('8'); gotoxy(35,6); cputchar('8'); gotoxy(36,6); cputchar('8');

    // Línea 6
    gotoxy(19,7); cputchar('Y'); gotoxy(20,7); cputchar('8'); gotoxy(21,7); cputchar('8'); gotoxy(22,7); cputchar('8'); gotoxy(23,7); cputchar('8'); gotoxy(24,7); cputchar('8'); gotoxy(25,7); cputchar('8'); gotoxy(26,7); cputchar('8'); gotoxy(27,7); cputchar('8'); gotoxy(28,7); cputchar('8'); gotoxy(29,7); cputchar('8'); gotoxy(30,7); cputchar('8'); gotoxy(31,7); cputchar('8'); gotoxy(32,7); cputchar('8'); gotoxy(33,7); cputchar('8'); gotoxy(34,7); cputchar('8'); gotoxy(35,7); cputchar('P');

    // Línea 7
    gotoxy(20,8); cputchar('\''); gotoxy(21,8); cputchar('Y'); gotoxy(22,8); cputchar('8'); gotoxy(23,8); cputchar('8'); gotoxy(24,8); cputchar('8'); gotoxy(25,8); cputchar('8'); gotoxy(26,8); cputchar('8'); gotoxy(27,8); cputchar('8'); gotoxy(28,8); cputchar('8'); gotoxy(29,8); cputchar('8'); gotoxy(30,8); cputchar('8'); gotoxy(31,8); cputchar('8');gotoxy(32,8); cputchar('8'); gotoxy(33,8); cputchar('P'); gotoxy(34,8); cputchar('\'');

    // Línea 8
    gotoxy(17,9); cputchar('_'); gotoxy(18,9); cputchar('.'); gotoxy(19,9); cputchar('.'); gotoxy(20,9); cputchar('.'); gotoxy(21,9); cputchar('_'); gotoxy(22,9); cputchar(' '); gotoxy(23,9); cputchar('\''); gotoxy(24,9); cputchar('Y'); gotoxy(25,9); cputchar('8'); gotoxy(26,9); cputchar('8'); gotoxy(27,9); cputchar('8'); gotoxy(28,9); cputchar('8');gotoxy(29,9); cputchar('8'); gotoxy(30,9); cputchar('P'); gotoxy(31,9); cputchar('\''); gotoxy(32,9); cputchar(' '); gotoxy(33,9); cputchar('_'); gotoxy(34,9); cputchar('.'); gotoxy(35,9); cputchar('.'); gotoxy(36,9); cputchar('.'); gotoxy(37,9); cputchar('_');

    // Línea 9
    gotoxy(15,10); cputchar('.'); gotoxy(16,10); cputchar('d'); gotoxy(17,10); cputchar('8'); gotoxy(18,10); cputchar('8'); gotoxy(19,10); cputchar('8'); gotoxy(20,10); cputchar('8'); gotoxy(21,10); cputchar('8'); gotoxy(22,10); cputchar('b'); gotoxy(23,10); cputchar('.'); gotoxy(24,10); cputchar(' '); gotoxy(25,10); cputchar('Y'); gotoxy(26,10); cputchar('8'); gotoxy(27,10); cputchar('8'); gotoxy(28,10); cputchar('8'); gotoxy(29,10); cputchar('P'); gotoxy(30,10); cputchar(' '); gotoxy(31,10); cputchar('.'); gotoxy(32,10); cputchar('d'); gotoxy(33,10); cputchar('8'); gotoxy(34,10); cputchar('8'); gotoxy(35,10); cputchar('8'); gotoxy(36,10); cputchar('8'); gotoxy(37,10); cputchar('8'); gotoxy(38,10); cputchar('b');

    // Línea 10
    gotoxy(16,11); cputchar('d'); gotoxy(17,11); cputchar('8'); gotoxy(18,11); cputchar('8'); gotoxy(19,11); cputchar('8'); gotoxy(20,11); cputchar('P'); gotoxy(21,11); cputchar(' '); gotoxy(22,11); cputchar('`'); gotoxy(23,11); cputchar('Y'); gotoxy(24,11); cputchar('8'); gotoxy(25,11); cputchar('8'); gotoxy(26,11); cputchar('8'); gotoxy(27,11); cputchar('8'); gotoxy(28,11); cputchar('8'); gotoxy(29,11); cputchar('8'); gotoxy(30,11); cputchar('8'); gotoxy(31,11); cputchar('P'); gotoxy(32,11); cputchar('\''); gotoxy(33,11); cputchar(' '); gotoxy(34,11); cputchar('Y'); gotoxy(35,11); cputchar('8'); gotoxy(36,11); cputchar('8'); gotoxy(37,11); cputchar('8');

    // Línea 11
    gotoxy(17,12); cputchar('b'); gotoxy(18,12); cputchar('8'); gotoxy(19,12); cputchar('b'); gotoxy(20,12); cputchar(' '); gotoxy(21,12); cputchar(' '); gotoxy(22,12); cputchar(' '); gotoxy(23,12); cputchar(' '); gotoxy(24,12); cputchar('Y'); gotoxy(25,12); cputchar('8'); gotoxy(26,12); cputchar('8'); gotoxy(27,12); cputchar('8'); gotoxy(28,12); cputchar('8'); gotoxy(29,12); cputchar('8'); gotoxy(30,12); cputchar('8'); gotoxy(31,12); cputchar('P'); gotoxy(32,12); cputchar(' '); gotoxy(33,12); cputchar(' '); gotoxy(34,12); cputchar(' '); gotoxy(35,12); cputchar('d'); gotoxy(36,12); cputchar('8'); gotoxy(37,12); cputchar('Y');

    // Línea 12
    gotoxy(17,13); cputchar('`'); gotoxy(18,13); cputchar('"'); gotoxy(19,13); cputchar('\''); gotoxy(20,13); cputchar(' '); gotoxy(21,13); cputchar('#'); gotoxy(22,13); cputchar('#'); gotoxy(23,13); cputchar('#'); gotoxy(24,13); cputchar('#'); gotoxy(25,13); cputchar('#'); gotoxy(26,13); cputchar('#'); gotoxy(27,13); cputchar('#'); gotoxy(28,13); cputchar('#'); gotoxy(29,13); cputchar('#'); gotoxy(30,13); cputchar('#'); gotoxy(31,13); cputchar('#'); gotoxy(32,13); cputchar('#'); gotoxy(33,13); cputchar('#'); gotoxy(34,13); cputchar(' '); gotoxy(35,13); cputchar('\''); gotoxy(36,13); cputchar('"'); gotoxy(37,13); cputchar('`');

    // Línea 13
    gotoxy(23,14); cputchar('d'); gotoxy(24,14); cputchar('P'); gotoxy(25,14); cputchar(' '); gotoxy(26,14); cputchar('d'); gotoxy(27,14); cputchar('8'); gotoxy(28,14); cputchar('b'); gotoxy(29,14); cputchar(' '); gotoxy(30,14); cputchar('Y'); gotoxy(31,14); cputchar('b');

    // Línea 14
    gotoxy(19,15); cputchar('O'); gotoxy(20,15); cputchar('b'); gotoxy(21,15); cputchar('='); gotoxy(22,15); cputchar('d'); gotoxy(23,15); cputchar('P'); gotoxy(24,15); cputchar(' '); gotoxy(25,15); cputchar('d'); gotoxy(26,15); cputchar('8'); gotoxy(27,15); cputchar('8'); gotoxy(28,15); cputchar('8'); gotoxy(29,15); cputchar('b'); gotoxy(30,15); cputchar(' '); gotoxy(31,15); cputchar('Y'); gotoxy(32,15); cputchar('b'); gotoxy(33,15); cputchar('='); gotoxy(34,15); cputchar('d'); gotoxy(35,15); cputchar('O');

    // Línea 15
    gotoxy(20,16); cputchar('`'); gotoxy(21,16); cputchar('"'); gotoxy(22,16); cputchar('`'); gotoxy(23,16); cputchar(' '); gotoxy(24,16); cputchar('O'); gotoxy(25,16); cputchar('8'); gotoxy(26,16); cputchar('8'); gotoxy(27,16); cputchar('8'); gotoxy(28,16); cputchar('8'); gotoxy(29,16); cputchar('8'); gotoxy(30,16); cputchar('O'); gotoxy(31,16); cputchar(' '); gotoxy(32,16); cputchar('`'); gotoxy(33,16); cputchar('"'); gotoxy(34,16); cputchar('`');

    // Línea 16
    gotoxy(25,17); cputchar('\''); gotoxy(26,17); cputchar('Y'); gotoxy(27,17); cputchar('8'); gotoxy(28,17); cputchar('P'); gotoxy(29,17); cputchar('\'');

    // Línea 17
    gotoxy(27,18); cputchar('\'');

}

//*****************************************//
// Función principal
//*****************************************//
int main(void) {
    char c;

    // 1. Limpiar pantalla y establecer modo texto
    clrscr();
    setvideomode(MODOTEXTO);
    printf("=== PRUEBA: clrscr() y setvideomode() ===\n");
    pausa();

    // 2. Probar gotoxy y cputchar
    clrscr();
    printf("=== PRUEBA: gotoxy() y cputchar() ===\n");
    textcolor(15);
    textbackground(1);
    gotoxy(10, 5); cputchar('X');
    gotoxy(12, 5); cputchar('Y');
    pausa();

    // 3. Probar setcursortype
    clrscr();
    printf("=== PRUEBA: setcursortype() ===\n");
    printf("\nCursor invisible...");
    setcursortype(INVISIBLE);
    pausa();
    printf("\nCursor normal...");
    setcursortype(NORMAL);
    pausa();
    printf("\nCursor grueso...");
    setcursortype(GRUESO);
    pausa();

    // 4. Probar textcolor y textbackground
    clrscr();
    printf("=== PRUEBA: textcolor() y textbackground() ===\n");
    textcolor(4);
    textbackground(7);
    gotoxy(5, 8); cputchar('A');
    gotoxy(6, 8); cputchar('B');
    pausa();

    // 5. Probar getche
    clrscr();
    printf("=== PRUEBA: getche() ===\n");
    gotoxy(5, 10);
    printf("Pulsa un caracter: ");
    c = getche();
    gotoxy(5, 11);
    printf("Caracter pulsado: "); cputchar(c);
    pausa();

    // 6. Probar recuadro en modo texto
    clrscr();
    printf("=== PRUEBA: recuadro_texto() ===\n");
    textcolor(15);
    textbackground(0);
    recuadro_texto(20, 12, 40, 18);
    pausa();

    // 7. Probar modo gráfico y dibujar pixels
    clrscr();
    setvideomode(MODOGRAFICO);
    printf("=== PRUEBA: pixel() en modo grafico ===\n");
    pixel(10, 10, 1);
    pixel(20, 20, 2);
    pixel(30, 30, 3);
    pixel(40, 40, 4);
    pausa();
    setvideomode(MODOTEXTO);

    // 8. Dibujar ASCII art en modo gráfico
    clrscr();
    printf("=== PRUEBA: asciidraw() ===\n");
    asciidraw();  // Llamada a la función de dibujo
    pausa();

    // 9. Volver a modo texto
    clrscr();
    printf("=== FIN DE PRUEBAS ===\n");

    return 0;
}
