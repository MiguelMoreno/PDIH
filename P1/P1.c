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
    textcolor(14);     // amarillo
    textbackground(1); // azul

    // Línea 1
    gotoxy(11,2); cputchar('.'); gotoxy(12,2); cputchar('d'); gotoxy(13,2); cputchar('8'); gotoxy(14,2); cputchar('b'); gotoxy(15,2); cputchar('.');

    // Línea 2
    gotoxy(7,3); cputchar('_'); gotoxy(8,3); cputchar('.'); gotoxy(9,3); cputchar('d'); gotoxy(10,3); cputchar('8'); gotoxy(11,3); cputchar('8'); gotoxy(12,3); cputchar('8'); gotoxy(13,3); cputchar('8'); gotoxy(14,3); cputchar('8'); gotoxy(15,3); cputchar('8'); gotoxy(16,3); cputchar('8'); gotoxy(17,3); cputchar('b'); gotoxy(18,3); cputchar('_'); gotoxy(19,3); cputchar('.');

    // Línea 3
    gotoxy(5,4); cputchar('.'); gotoxy(6,4); cputchar('8'); gotoxy(7,4); cputchar('8'); gotoxy(8,4); cputchar('8'); gotoxy(9,4); cputchar('8'); gotoxy(10,4); cputchar('8'); gotoxy(11,4); cputchar('8'); gotoxy(12,4); cputchar('8'); gotoxy(13,4); cputchar('8'); gotoxy(14,4); cputchar('8'); gotoxy(15,4); cputchar('8'); gotoxy(16,4); cputchar('8'); gotoxy(17,4); cputchar('8'); gotoxy(18,4); cputchar('8'); gotoxy(19,4); cputchar('8'); gotoxy(20,4); cputchar('b'); gotoxy(21,4); cputchar('.');

    // Línea 4
    gotoxy(4,5); cputchar('d'); gotoxy(5,5); cputchar('8'); gotoxy(6,5); cputchar('8'); gotoxy(7,5); cputchar('8'); gotoxy(8,5); cputchar('8'); gotoxy(9,5); cputchar('8'); gotoxy(10,5); cputchar('8'); gotoxy(11,5); cputchar('8'); gotoxy(12,5); cputchar('8'); gotoxy(13,5); cputchar('8'); gotoxy(14,5); cputchar('8'); gotoxy(15,5); cputchar('8'); gotoxy(16,5); cputchar('8'); gotoxy(17,5); cputchar('8'); gotoxy(18,5); cputchar('8'); gotoxy(19,5); cputchar('8'); gotoxy(20,5); cputchar('8'); gotoxy(21,5); cputchar('8'); gotoxy(22,5); cputchar('b');

    // Línea 5
    gotoxy(4,6); cputchar('8'); gotoxy(5,6); cputchar('8'); gotoxy(6,6); cputchar('8'); gotoxy(7,6); cputchar('8'); gotoxy(8,6); cputchar('8'); gotoxy(9,6); cputchar('8'); gotoxy(10,6); cputchar('8'); gotoxy(11,6); cputchar('8'); gotoxy(12,6); cputchar('8'); gotoxy(13,6); cputchar('8'); gotoxy(14,6); cputchar('8'); gotoxy(15,6); cputchar('8'); gotoxy(16,6); cputchar('8'); gotoxy(17,6); cputchar('8'); gotoxy(18,6); cputchar('8'); gotoxy(19,6); cputchar('8'); gotoxy(20,6); cputchar('8');

    // Línea 6
    gotoxy(4,7); cputchar('Y'); gotoxy(5,7); cputchar('8'); gotoxy(6,7); cputchar('8'); gotoxy(7,7); cputchar('8'); gotoxy(8,7); cputchar('8'); gotoxy(9,7); cputchar('8'); gotoxy(10,7); cputchar('8'); gotoxy(11,7); cputchar('8'); gotoxy(12,7); cputchar('8'); gotoxy(13,7); cputchar('8'); gotoxy(14,7); cputchar('8'); gotoxy(15,7); cputchar('8'); gotoxy(16,7); cputchar('8'); gotoxy(17,7); cputchar('8'); gotoxy(18,7); cputchar('8'); gotoxy(19,7); cputchar('8'); gotoxy(20,7); cputchar('P');

    // Línea 7
    gotoxy(5,8); cputchar('\''); gotoxy(6,8); cputchar('Y'); gotoxy(7,8); cputchar('8'); gotoxy(8,8); cputchar('8'); gotoxy(9,8); cputchar('8'); gotoxy(10,8); cputchar('8'); gotoxy(11,8); cputchar('8'); gotoxy(12,8); cputchar('8'); gotoxy(13,8); cputchar('8'); gotoxy(14,8); cputchar('8'); gotoxy(15,8); cputchar('8'); gotoxy(16,8); cputchar('8'); gotoxy(17,8); cputchar('8'); gotoxy(18,8); cputchar('P'); gotoxy(19,8); cputchar('\'');

    // Línea 8
    gotoxy(3,9); cputchar('_'); gotoxy(4,9); cputchar('.'); gotoxy(5,9); cputchar('.'); gotoxy(6,9); cputchar('.'); gotoxy(7,9); cputchar('_'); gotoxy(8,9); cputchar(' '); gotoxy(9,9); cputchar('\''); gotoxy(10,9); cputchar('Y'); gotoxy(11,9); cputchar('8'); gotoxy(12,9); cputchar('8'); gotoxy(13,9); cputchar('8'); gotoxy(14,9); cputchar('8'); gotoxy(15,9); cputchar('8'); gotoxy(16,9); cputchar('P'); gotoxy(17,9); cputchar('\''); gotoxy(18,9); cputchar(' '); gotoxy(19,9); cputchar('_'); gotoxy(20,9); cputchar('.'); gotoxy(21,9); cputchar('.'); gotoxy(22,9); cputchar('.'); gotoxy(23,9); cputchar('_');

    // Línea 9
    gotoxy(2,10); cputchar('.'); gotoxy(3,10); cputchar('d'); gotoxy(4,10); cputchar('8'); gotoxy(5,10); cputchar('8'); gotoxy(6,10); cputchar('8'); gotoxy(7,10); cputchar('8'); gotoxy(8,10); cputchar('8'); gotoxy(9,10); cputchar('b'); gotoxy(10,10); cputchar('.'); gotoxy(12,10); cputchar('Y'); gotoxy(13,10); cputchar('8'); gotoxy(14,10); cputchar('8'); gotoxy(15,10); cputchar('8'); gotoxy(16,10); cputchar('P'); gotoxy(18,10); cputchar('.'); gotoxy(19,10); cputchar('d'); gotoxy(20,10); cputchar('8'); gotoxy(21,10); cputchar('8'); gotoxy(22,10); cputchar('8'); gotoxy(23,10); cputchar('8'); gotoxy(24,10); cputchar('8'); gotoxy(25,10); cputchar('b'); gotoxy(26,10); cputchar('.');

    // Línea 10
    gotoxy(1,11); cputchar('d'); gotoxy(2,11); cputchar('8'); gotoxy(3,11); cputchar('8'); gotoxy(4,11); cputchar('8'); gotoxy(5,11); cputchar('8'); gotoxy(6,11); cputchar('8'); gotoxy(7,11); cputchar('8'); gotoxy(8,11); cputchar('8'); gotoxy(9,11); cputchar('8'); gotoxy(10,11); cputchar('b'); gotoxy(13,11); cputchar('8'); gotoxy(15,11); cputchar('d'); gotoxy(16,11); cputchar('8'); gotoxy(17,11); cputchar('8'); gotoxy(18,11); cputchar('8'); gotoxy(19,11); cputchar('8'); gotoxy(20,11); cputchar('8'); gotoxy(21,11); cputchar('8'); gotoxy(22,11); cputchar('8'); gotoxy(23,11); cputchar('b');

    // Línea 11
    gotoxy(1,12); cputchar('8'); gotoxy(2,12); cputchar('8'); gotoxy(3,12); cputchar('8'); gotoxy(4,12); cputchar('P'); gotoxy(6,12); cputchar('`'); gotoxy(7,12); cputchar('Y'); gotoxy(8,12); cputchar('8'); gotoxy(9,12); cputchar('8'); gotoxy(10,12); cputchar('8'); gotoxy(11,12); cputchar('8'); gotoxy(12,12); cputchar('8'); gotoxy(13,12); cputchar('8'); gotoxy(14,12); cputchar('8'); gotoxy(15,12); cputchar('8'); gotoxy(16,12); cputchar('8'); gotoxy(17,12); cputchar('8'); gotoxy(18,12); cputchar('8'); gotoxy(19,12); cputchar('P'); gotoxy(21,12); cputchar('Y'); gotoxy(22,12); cputchar('8'); gotoxy(23,12); cputchar('8'); gotoxy(24,12); cputchar('8');

    // Línea 12
    gotoxy(1,13); cputchar('b'); gotoxy(2,13); cputchar('8'); gotoxy(3,13); cputchar('b'); gotoxy(7,13); cputchar('Y'); gotoxy(8,13); cputchar('8'); gotoxy(9,13); cputchar('8'); gotoxy(10,13); cputchar('8'); gotoxy(11,13); cputchar('8'); gotoxy(12,13); cputchar('8'); gotoxy(13,13); cputchar('8'); gotoxy(14,13); cputchar('8'); gotoxy(15,13); cputchar('P'); gotoxy(21,13); cputchar('d'); gotoxy(22,13); cputchar('8'); gotoxy(23,13); cputchar('Y');

    // Línea 13
    gotoxy(1,14); cputchar('`'); gotoxy(2,14); cputchar('"'); gotoxy(3,14); cputchar('\''); gotoxy(5,14); cputchar('#'); gotoxy(6,14); cputchar('#'); gotoxy(7,14); cputchar('#'); gotoxy(8,14); cputchar('#'); gotoxy(9,14); cputchar('#'); gotoxy(10,14); cputchar('#'); gotoxy(11,14); cputchar('#'); gotoxy(12,14); cputchar('#'); gotoxy(13,14); cputchar('#'); gotoxy(14,14); cputchar('#'); gotoxy(15,14); cputchar('#'); gotoxy(16,14); cputchar('#'); gotoxy(17,14); cputchar('#'); gotoxy(18,14); cputchar('#'); gotoxy(19,14); cputchar('#'); gotoxy(20,14); cputchar('#'); gotoxy(22,14); cputchar('\''); gotoxy(23,14); cputchar('"'); gotoxy(24,14); cputchar('`');

    // Línea 14
    gotoxy(9,15); cputchar('d'); gotoxy(10,15); cputchar('P'); gotoxy(12,15); cputchar('d'); gotoxy(13,15); cputchar('8'); gotoxy(14,15); cputchar('b'); gotoxy(16,15); cputchar('Y'); gotoxy(17,15); cputchar('b');

    // Línea 15
    gotoxy(5,16); cputchar('O'); gotoxy(6,16); cputchar('b'); gotoxy(7,16); cputchar('='); gotoxy(8,16); cputchar('d'); gotoxy(9,16); cputchar('P'); gotoxy(11,16); cputchar('d'); gotoxy(12,16); cputchar('8'); gotoxy(13,16); cputchar('8'); gotoxy(14,16); cputchar('8'); gotoxy(15,16); cputchar('b'); gotoxy(17,16); cputchar('Y'); gotoxy(18,16); cputchar('b'); gotoxy(19,16); cputchar('=');

    // Línea 16
    gotoxy(7,17); cputchar('`'); gotoxy(8,17); cputchar('"'); gotoxy(9,17); cputchar('`'); gotoxy(11,17); cputchar('O'); gotoxy(12,17); cputchar('8'); gotoxy(13,17); cputchar('8'); gotoxy(14,17); cputchar('8'); gotoxy(15,17); cputchar('8'); gotoxy(16,17); cputchar('8'); gotoxy(17,17); cputchar('O'); gotoxy(19,17); cputchar('`'); gotoxy(20,17); cputchar('"'); gotoxy(21,17); cputchar('`');

    // Línea 17
    gotoxy(12,18); cputchar('\''); gotoxy(13,18); cputchar('Y'); gotoxy(14,18); cputchar('8'); gotoxy(15,18); cputchar('P'); gotoxy(16,18); cputchar('\'');

    // Línea 18
    gotoxy(14,19); cputchar('\'');
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
