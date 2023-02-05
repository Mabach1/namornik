#include <stdio.h>                          // printf()
#include <stdlib.h>                         // system(), implicit declaration srand
#include <time.h>                           // pro generaci nahodnych cisel

#define NPRINT                              // v pripade, ze chceme zobrazit simulaci namornika, staci smazat 'N'
#define STEP        1500                    // rychlost, jakou bude namornik chodit (refresh rate console)

#define RUNNING     1                       // nekonecna smycka

#define NUM_OF_COMP 5000000                 // pocet kdy namornik spadne do vody, nebo dojde do cile

#define SIRKA_MOLA  3                       // sirka mola, ktere namornik musi prejit

#define X           (SIRKA_MOLA + 2)        // velikost tabulky v x
#define Y           5                       // ! velikost tabulkt v y == ZDE LZE UPRAVIT DELKU MOLA ==
#define SIZE        (Y * X)                 // pocet bunek v tabulce

#define WATER       126                     // ascii hodnota symbolizujici vodu      (126 = '~')
#define MOLO        61                      // ascii hodnota symbolizujici molo      (61  = '=')
#define SAILOR      64                      // ascii hodnota symbolizujici namornika (64  = '@')

#define OK          0                       // stav -> namornik je pro provedeni kroku v poradku
#define WIN        -1                       // stav -> namornik je v cili
#define DROWN       1                       // stav -> namornik je ve vode => utopil se

#define START       (Y * X) - (X / 2) - 1   // startovaci pozice namornika

int grid[SIZE] = { 0 };                     // samotna tabulka s inforamcemi, na zacatku jsou vsechny hodnoty tabulky v nule

/**
 * @brief inicializace tabulky (nahrani hodnot do tabulky)
 * 
 */
void grid_init(void) {
    //  nastaveni vody 
    for (int i = 0; i < SIZE; i += X) {
        grid[i] = WATER;
    }

    for (int i = X-1; i < SIZE; i += X) {
        grid[i] = WATER;
    }

    // nastaveni mola
    // co neni voda je molo
    for (int i = 0; i < SIZE; i++) {
        if (grid[i] != WATER) {
            grid[i] = MOLO;
        }
    }
}
/**
 * @brief funcke vykresli tabulku na konzoli 
 * 
 */
void grid_draw(void) {
    int k = 0;

    for (int i = 0; i < Y; i++) {
        for (int j = 0; j < X; j++) {
            printf("%c", grid[k++]);
        }
        printf("\n");
    }
}
/**
 * @brief funcke nastavi namornika do tabulky
 * 
 */
void set_sailor(void) {
    grid[START] = SAILOR;
}
/**
 * @brief funcke vrati soucasnou pozici namornika
 * 
 * @return pozice 
 */
int current_position(void) {
    int position = 0;

    for (int i = 0; i < SIZE; i++) {
        if (grid[i] == SAILOR) {
            position = i;
        }
    }

    return position;
}
/**
 * @brief funkce vygeneruje nahodnou pozici v intervalu <0, 8)
 * 
 * pro blizsi vysvetleni generovani nove pozice prostudujte funkci check_move()
 * 
 * @return nova pozice
 */
int get_new_position(void) {
    int new_position = rand() % 8;

    return new_position;
}
/**
 * @brief funkce funkce prepocita danou pozici aby byla v intervalu <0, X)
 * 
 * @param   pozice, kterou chceme prelozit 
 * @return  prelozena pozice
 */
int translate_position(int position) {
    int translated_position = position;

    while (translated_position > X) {
        translated_position -= X;
    }
   
    return translated_position;
}
/**
 * @brief funcke kontroluje zda pozice, kterou vygenerovala funkce get_new_position() je mozna
 * 
 * @param position  - soucasna pozice namornika 
 * @param move      - pohyb, ktery chce namornik vykonat
 * @return 1 => pohyb je mozny
 * @return 0 => pohyb je nemozny 
 */
int check_move(int position, int move) {
    int transl_position = translate_position(position);

    // 0 - do leva
    if ((transl_position - 1) > 0 && move == 0) {
        return 1;
    }

    // 1 - do prava
    if ((transl_position + 1) < X && 1 == move) {
        return 1;
    } 

    // 2 - do predu
    if ((position - X) > 0 && 2 == move) {
        return 1;
    }
    
    // 3 - do zadu
    if ((position + X) < SIZE && 3 == move) {
        return 1;
    }

    // 4 - do predu, do leva
    if ((position - X - 1) > 0 && 4 == move) {
        return 1;
    }

    // 5 - do predu, do prava
    if ((position - X + 1) > 0 && (transl_position + 1) < X && 5 == move) {
        return 1;
    } 

    // 6 - do zadu, do leva
    if ((position + X - 1) < SIZE && (transl_position - 1) > 0 && 6 == move) {
        return 1;
    }

    // 7 - do zadu, do prava
    if ((position + X + 1) < SIZE && (transl_position + 1) < X && 7 == move) {
        return 1;
    }

    return 0;
}
/**
 * @brief po pohybu namornika se bunka, na ktere stal zmeni zpet na molo nebo vodu
 * 
 * reseni "resetovani bunek tabulky" by nejpis slo udelat jednoduseji, ale tento pristup je nejprimejsi
 * 
 * @param position_of_tile, ze ktere se namornik pohnul
 */
void reset_tile(int position_of_tile) {
    // jestli pozice bunky se shoduje s indexem bunky vody nastavime bunku na vodu
    for (int i = 0; i < SIZE; i += X) {
        if (position_of_tile == i) {
            grid[i] = WATER;
        }
    }
    
    for (int i = X - 1; i < SIZE; i += X) {
        if (position_of_tile == i) {
            grid[i] = WATER;
        }
    }

    // jestli bunka neni voda a zaroven indexy mola a bunky se rovnaji nastavi se bunka na molo
    for (int i = 0; i < SIZE; i++) {
        if (grid[i] != WATER && position_of_tile == i) {
            grid[i] = MOLO;
        }
    }
}
/**
 * @brief samotny pohyb namornika
 * 
 * @param position - soucasna pozice namornika
 */
void sailor_step(int position) {
    int move = get_new_position();  // nova pozice namornika

    // budeme volat funkci pro novou pozici do te doby dokud nedostaneme pouzitelnou pozici
    // pouzitelna pozice = {0, 1, 2, 3, 4, 5, 6, 7} 
    do {
        move = get_new_position();
    } while (!check_move(position, move));

    // ! samotny pohyb
    // dostne novou pozici, ktera byla uz zkontrolovana a pohne se pomoci swithce
    int previous_position = current_position();

    switch (move) {
        case 0:
            grid[previous_position - 1] = SAILOR;
            break;
        case 1:
            grid[previous_position + 1] = SAILOR;
            break;
        case 2:
            grid[previous_position - X] = SAILOR;
            break;
        case 3:
            grid[previous_position + X] = SAILOR;
            break;
        case 4:
            grid[previous_position - X - 1] = SAILOR;
            break;
        case 5:
            grid[previous_position - X + 1] = SAILOR;
            break;
        case 6:
            grid[previous_position + X -1] = SAILOR;
            break;
        case 7:
            grid[previous_position + X + 1] = SAILOR;
            break;
    }

    // predchozi pozice namornika se vrati do puvodniho stavu
    reset_tile(previous_position);
}
/**
 * @brief funkce zijsti jestli se namornik pri soucasnem pohybu utopil
 * 
 * @param position - soucasna pozice namornika
 * @return 1 => utopil se
 * @return 0 => neutopil se
 */
int sailor_drown(int position) {
    for (int i = 0; i < SIZE; i += X) {
        if (i == position) { return 1; }
    }

    for (int i = X - 1; i < SIZE; i += X) {
        if (i == position) { return 1; }
    }

    return 0;
}
/**
 * @brief funkce zijsti, jestli namornik se dostal do cile 
 * 
 * @param position - soucasna pozice
 * @return 1 => vyhral
 * @return 0 => jeste nevyhral
 */
int sailor_win(int position) {
    if (position >= 1 && position <= X-1) {
        return 1;
    }

    return 0;
}
/**
 * @brief funkce zijsti soucasny stav namornika 
 * 
 * @param position - soucasna pozice namornika
 * @return stav - DROWN, WIN nebo OK
 */
int check_sailor_state(int position) {
    if (sailor_drown(position)) { return DROWN; }
    if (sailor_win(position)) { return WIN; }

    // seilor is okay
    return OK;
}
/**
 * @brief resetovani tabulky po vyhre nebo utopeni namornika
 * 
 */
void sailor_reset(void) {
    grid_init();
    set_sailor();
}
/**
 * @brief funcke pro vizualizaci simulace namornika
 * 
 * funkce pozastavi vypis na kratkou dobu aby byl uzivatel schopen zaznamenat soucasny pohyb namornika na konzoli 
 * 
 * @param time - funkce nepracuje s casem, promenna time je pouze orientacni
 */
void delay(int time) {
    for (int i = 0; i < time; i++) {
        for (int j = 0; j < time; j++);
    }
}
int main(void) {
    // srand funcke pro spravne generovani nahodnych cisel
    srand(time(NULL));

    // inicializace tabulky a namornika
    grid_init();
    set_sailor();

    // promenne pro vypocet pravdepodobnosti, ze namornik dorazi do cile
    int number_of_computations = 0;
    int number_of_wins = 0;
    int number_of_drowns = 0;

    #ifdef PRINT
        grid_draw();
        printf("Press any key to start...");
        getchar();
        system("cls");
    #endif

    while (RUNNING) {
        sailor_step(current_position()); 

        switch (check_sailor_state(current_position())) {
            case -1:
                ++number_of_wins;
                ++number_of_computations;
                sailor_reset();
                break;
           case 1:
                ++number_of_drowns;
                ++number_of_computations;
                sailor_reset();
                break;
        }


        if (number_of_computations >= NUM_OF_COMP) { break; }

        #ifdef PRINT
            grid_draw();
            printf("WINS - %d\n", number_of_wins);
            printf("FAIL - %d", number_of_drowns);

            delay(STEP);
            system("cls");
        #endif
    }

    printf("WINS - %d\n", number_of_wins);
    printf("FAIL - %d", number_of_drowns);

    return 0;
}
