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

    gotoxy(11, 2);   printf(".d8b.");
    gotoxy(7, 3);   printf("_.d8888888b._");
    gotoxy(5, 4);   printf(".88888888888888b.");
    gotoxy(4, 5);   printf("d88888888888888888b");
    gotoxy(4, 6);   printf("8888888888888888888");
    gotoxy(4, 7);   printf("Y88888888888888888P");
    gotoxy(5, 8);   printf("'Y8888888888888P'");
    gotoxy(3, 9);   printf("_..._ 'Y88888P' _..._");
    gotoxy(2,10);   printf(".d88888b. Y888P .d88888b.");
    gotoxy(1,11);   printf("d888888888b 888 d88888888b");
    gotoxy(1,12);   printf("888P  `Y8888888888P'  Y888");
    gotoxy(1,13);   printf("b8b    Y88888888P    d8Y");
    gotoxy(1,14);   printf("`\"'  #############  '\"`");
    gotoxy(9,15);   printf("dP d8b Yb");
    gotoxy(5,16);   printf("Ob=dP d888b Yb=dO");
    gotoxy(7,17);   printf("`\"` O88888O `\"`");
    gotoxy(12,18);  printf("'Y8P'");
    gotoxy(14,19);  printf("'");
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
