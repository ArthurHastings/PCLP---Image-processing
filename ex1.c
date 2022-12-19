#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./bmp_header.h"
#define PATRU 4
#define CINCI 5
#define SASE 6
#define SAPTE 7
#define ZECE 10
#define PAISPREZECE 14
#define OSUTA 100
#define OMIE 1000
#define DOUAMIL 2000000
void citire_comanda(char *cerinta, char *comanda, int cont) {
    for (int i = 0; i < cont; i++) {
        comanda[i] = cerinta[i];
    }
}

void curatare(char *comanda, int l) {
    memset(comanda, 0, l);
}

void fill_function(int matrice[OMIE][OMIE], int m, int n, int cont) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matrice[i][j] == cont-1) {
                if (matrice[i-1][j] == 0) {
                    matrice[i-1][j] = cont;
                }
                if (matrice[i-1][j-1] == 0) {
                    matrice[i-1][j-1] = cont;
                }
                if (matrice[i][j-1] == 0) {
                    matrice[i][j-1] = cont;
                }
                if (matrice[i+1][j-1] == 0) {
                    matrice[i+1][j-1] = cont;
                }
                if (matrice[i+1][j] == 0) {
                    matrice[i+1][j] = cont;
                }
                if (matrice[i+1][j+1] == 0) {
                    matrice[i+1][j+1] = cont;
                }
                if (matrice[i][j+1] == 0) {
                    matrice[i][j+1] = cont;
                }
                if (matrice[i-1][j+1] == 0) {
                    matrice[i-1][j+1] = cont;
                }
            }
        }
    }
}

int  dif_triunghi(int x, int y) {
    int dif_tri = x - y;
    if (dif_tri < 0) {
        dif_tri = -dif_tri;
    }
    return dif_tri;
}


void linie_ingrosata(int line_y1, int line_x1, int line_y2,
int line_x2, int dif_x, int dif_y, int *poz_x, int *poz_y,
int matrice[OMIE][OMIE], int w_p1, int h_p1, int rosu, int albastru,
int verde, int line_width, char *pixel_p1) {
    int Contor = 0, OKAY = 0, OKAY2 = 0;
    if (dif_x < 0) {
        dif_x = -dif_x;
    }
    dif_y = line_y1 - line_y2;
    if (dif_y < 0) {
        dif_y = -dif_y;
    }
    if (dif_y > dif_x) {
        if (line_y1 > line_y2) {
            int aux = line_y1;
            line_y1 = line_y2;
            line_y2 = aux;
            OKAY = 1;
        }
        if (line_x1 > line_x2) {
            int aux = line_x1;
            line_x1 = line_x2;
            line_x2 = aux;
            OKAY2 = 1;
        }
        for (int i = line_y1; i <= line_y2; i++) {
            poz_y[Contor] = i;

            if (OKAY == 0 && OKAY2 == 0) {
                poz_x[Contor] = ((poz_y[Contor]-line_y1)*
                (line_x2-line_x1) + line_x1*line_y2-
                line_y1*line_x1)/(line_y2-line_y1);
            }
            if (OKAY == 0 && OKAY2 == 1) {
                poz_x[Contor] = (poz_y[Contor]*(line_x1-line_x2) +
                line_x2*line_y2-line_y1*line_x1)/(line_y2-line_y1);
            }
            if (OKAY == 1 && OKAY2 == 0) {
                poz_x[Contor] = (poz_y[Contor]*(line_x2-line_x1) +
                line_x1*line_y1-line_y2*line_x2)/(line_y1-line_y2);
            }
            if (OKAY == 1 && OKAY2 == 1) {
                poz_x[Contor] = (poz_y[Contor]*(line_x2-line_x1) +
                line_x1*line_y2-line_y1*line_x2)/(line_y2-line_y1);
            }
            Contor++;
        }
    } else {
        if (line_x1 > line_x2) {
            int aux = line_x1;
            line_x1 = line_x2;
            line_x2 = aux;
            OKAY2 = 1;
        }
        if (line_y1 > line_y2) {
            int aux = line_y1;
            line_y1 = line_y2;
            line_y2 = aux;
            OKAY = 1;
        }
        for (int i = line_x1; i <= line_x2; i++) {
            poz_x[Contor] = i;
            if (OKAY == 0 && OKAY2 == 0) {
                poz_y[Contor] = (poz_x[Contor]*(line_y2-line_y1) +
                line_y1*line_x2-line_y2*line_x1)/(line_x2-line_x1);
            }
            if (OKAY == 0 && OKAY2 == 1) {
                poz_y[Contor] = (poz_x[Contor]*(line_y2-line_y1) +
                line_y1*line_x1-line_y2*line_x2)/(line_x1-line_x2);
            }
            if (OKAY == 1 && OKAY2 == 0) {
                poz_y[Contor] = (poz_x[Contor]*(line_y2-line_y1) +
                line_y1*line_x1-line_y2*line_x2)/(line_x1-line_x2);
            }
            if (OKAY == 1 && OKAY2 == 1) {
                poz_x[Contor] = (poz_y[Contor]*(line_x2-line_x1) +
                line_x1*line_y2-line_y1*line_x2)/(line_y2-line_y1);
            }
            Contor++;
        }
    }
    // ---------------pentru ingrosare linie---------------------
    int auxx = 0;
    for (int i = 0; i < Contor; i++) {
        matrice[poz_x[i]][poz_y[i]] = 1;
    }
    for (int i = 0; i < line_width/2; i++) {
        fill_function(matrice, h_p1,
        w_p1, i+2);
    }
    int ok = 0;
    auxx = 0;
    for (int i = 0; i < h_p1; i++) {
        ok = 0;
        for (int j = 0; j < w_p1; j++) {
            if (matrice[i][j] != 0) {
                if (ok == 0) {
                pixel_p1[3*i*w_p1+3*j+ok] =
                (char)albastru;
                ok++;
                }
                if (ok == 1) {
                    pixel_p1[3*i*w_p1+3*j+ok] =
                    (char)verde;
                    ok++;
                }
                if (ok == 2) {
                    pixel_p1[3*i*w_p1+3*j+ok] =
                    (char)rosu;
                    ok++;
                }
                if (ok == 3) {
                    ok = 0;
                    auxx++;
                }
            }
        }
    }
}

void Fill(int i, int j, int matrice[OMIE][OMIE],
int rosu_new, int verde_new, int albastru_new, int w_p1, int h_p1,
 char *pixel_p1, char rosu, char verde, char albastru) {
    if (i >= 0 && i < h_p1 && j >= 0 && j < w_p1 && (pixel_p1[3*i*w_p1 + 3*j]
    == albastru && pixel_p1[3*i*w_p1 + 3*j+1] == verde
    && pixel_p1[3*i*w_p1 + 3*j+2] == rosu)) {
        pixel_p1[3*i*w_p1 + 3*j] = (char)albastru_new;
        pixel_p1[3*i*w_p1 + 3*j+1] = (char)verde_new;
        pixel_p1[3*i*w_p1 + 3*j+2] = (char)rosu_new;
        if (pixel_p1[3*(i-1)*w_p1 + 3*j] == albastru &&
        pixel_p1[3*(i-1)*w_p1 + 3*j+1] == verde
        && pixel_p1[3*(i-1)*w_p1 + 3*j+2] == rosu) {
            Fill(i-1, j, matrice, rosu_new, verde_new, albastru_new, w_p1,
            h_p1, pixel_p1, rosu, verde, albastru);
        }
        if (pixel_p1[3*i*w_p1 + 3*(j-1)] == albastru &&
        pixel_p1[3*i*w_p1 + 3*(j-1)+1] == verde
        && pixel_p1[3*i*w_p1 + 3*(j-1)+2] == rosu) {
            Fill(i, j-1, matrice, rosu_new, verde_new, albastru_new, w_p1, h_p1,
            pixel_p1, rosu, verde, albastru);
        }
        if (pixel_p1[3*i*w_p1 + 3*(j+1)] == albastru &&
        pixel_p1[3*i*w_p1 + 3*(j+1)+1] == verde
        && pixel_p1[3*i*w_p1 + 3*(j+1)+2] == rosu) {
            Fill(i, j+1, matrice, rosu_new, verde_new, albastru_new, w_p1,
            h_p1, pixel_p1, rosu, verde, albastru);
        }
        if (pixel_p1[3*(i+1)*w_p1 + 3*j] == albastru &&
        pixel_p1[3*(i+1)*w_p1 + 3*j+1] == verde
        && pixel_p1[3*(i+1)*w_p1 + 3*j+2] == rosu) {
            Fill(i+1, j, matrice, rosu_new, verde_new, albastru_new, w_p1,
            h_p1, pixel_p1, rosu, verde, albastru);
        }
    }
}

void resetare_matrice(int matrice[OMIE][OMIE], int h, int l) {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < l; j++) {
            matrice[i][j] = 0;
        }
    }
}

struct pixel {
    unsigned char R;
    unsigned char G;
    unsigned char B;
};

int main() {
    char *cerinta = NULL, *comanda = NULL, *path_p1 = NULL;
    char *path_p2 = NULL, *bin_p1 = NULL, *bin_p2 = NULL;
    char *set_command = NULL, *draw_command = NULL;
    char *pixel_p1 = NULL, *pixel_p2 = NULL;
    int *poz_x = NULL, *poz_y = NULL;
    FILE *f_input = NULL, *f_output = NULL, *f_insert = NULL;
    cerinta = (char *)malloc(DOUAMIL * sizeof(char));
    comanda = (char *)malloc(DOUAMIL * sizeof(char));
    path_p1 = (char *)malloc(DOUAMIL * sizeof(char));
    path_p2 = (char *)malloc(DOUAMIL * sizeof(char));
    bin_p1 =  (char *)malloc(DOUAMIL * sizeof(char));
    bin_p2 =  (char *)malloc(DOUAMIL * sizeof(char));
    pixel_p1 =  (char *)malloc(DOUAMIL * sizeof(char));
    pixel_p2 =  (char *)malloc(DOUAMIL * sizeof(char));
    set_command =  (char *)malloc(DOUAMIL * sizeof(char));
    draw_command = (char *)malloc(DOUAMIL * sizeof(char));
    poz_x = (int *)malloc(DOUAMIL * sizeof(int));
    poz_y = (int *)malloc(DOUAMIL * sizeof(int));
    bmp_fileheader bin_file_p1, bin_file_p2;
    bmp_infoheader bin_info_p1, bin_info_p2;
    int cont = 0, contor = 0, size_p1 = 0, size_p2 = 0;
    int ok = 0, OK = 0, rosu = 0, verde = 0, albastru = 0;
    int p2_x = 0, p2_y = 0, aux = 0, line_width = 0;
    int line_x1 = 0, line_y1 = 0, line_x2 = 0, line_y2 = 0;
    int matrice[OMIE][OMIE];
    int triangle_y1 = 0, triangle_x1 = 0, triangle_y2 = 0;
    int triangle_x2 = 0, triangle_y3 = 0, triangle_x3 = 0;
    int fill_x = 0, fill_y = 0;
    char albastru_og = 0, verde_og = 0, rosu_og = 0;

    while (fgets(cerinta, OSUTA , stdin) != NULL) {
        if (OK == 0) {
        cont = 0;
        curatare(comanda, (int)strlen(comanda));
        curatare(set_command, (int)strlen(set_command));
        for (int i = 0; i < (int)strlen(cerinta); i++) {
            if (cerinta[i] == ' ') {
                citire_comanda(cerinta, comanda, cont);
                cont = 0;
                break;
            } else {
                cont++;
            }
        }
        } else {
            strncpy(comanda, "quit", SAPTE);
        }
        if (strcmp(comanda, "edit") == 0) {
            for (int i = 0; i < (int)strlen(cerinta); i++) {
                if (cerinta[i] == '\n') {
                    for (int j = CINCI; j < (int)strlen(cerinta)-1; j++) {
                        path_p1[contor++] = cerinta[j];
                    }
                }
            }
            f_input = fopen(path_p1, "rb");
            fread(bin_p1, sizeof(char), size_p1, f_input);
            rewind(f_input);
            fread(&bin_file_p1, sizeof(bmp_fileheader), 1, f_input);
            fread(&bin_info_p1, sizeof(bmp_infoheader), 1, f_input);
            fread(pixel_p1, 3*bin_info_p1.height*bin_info_p1.width,
             1, f_input);
            resetare_matrice(matrice, bin_info_p1.height, bin_info_p1.width);

        } else if (strcmp(comanda, "insert") == 0) {
            contor = 0, p2_x = 0, p2_y = 0, ok = 0;
            for (int i = 0; i < (int)strlen(cerinta); i++) {
                if (cerinta[i] == '\n') {
                    for (int j = SAPTE; j < (int)strlen(cerinta); j++) {
                        if (cerinta[j] == ' ') {
                            break;
                        } else {
                            path_p2[contor++] = cerinta[j];
                        }
                    }
                }
            }
            for (int i = 0; i < (int)strlen(cerinta); i++) {
                if (ok == 2 && cerinta[i] != ' ') {
                    aux = '0' - cerinta[i];
                    aux = -aux;
                    p2_x = p2_x + aux;
                    p2_x *= ZECE;
                }
                if (ok == 3 && cerinta[i] != '\n' && cerinta[i] != ' ') {
                    aux = '0' - cerinta[i];
                    aux = -aux;
                    p2_y = p2_y + aux;
                    p2_y *= ZECE;
                }
                if (cerinta[i] == ' ') {
                    ok++;
                }
            }
            p2_x /= ZECE;
            p2_y /= ZECE;
            f_insert = fopen(path_p2, "rb");
            fseek(f_insert, 0, 2);
            size_p2 = (int)ftell(f_insert);
            rewind(f_insert);
            fread(bin_p2, sizeof(char), size_p2, f_insert);
            rewind(f_insert);
            fread(&bin_file_p2, sizeof(bmp_fileheader), 1, f_insert);
            fread(&bin_info_p2, sizeof(bmp_infoheader), 1, f_insert);
            fread(pixel_p2, 3*bin_info_p2.width*bin_info_p2.height,
             1, f_insert);
            int k = 0, l = 0;
            for (int i = p2_y; (i < bin_info_p1.height) &&
            (i < bin_info_p2.height+p2_y); i++) {
                for (int j = 3*p2_x; j < 3*bin_info_p1.width
                && (j < 3*bin_info_p2.width+3*p2_x); j++) {
                    pixel_p1[3*i*bin_info_p1.width+j] =
                    pixel_p2[3*k*bin_info_p2.width+l++];
                }
                k++;
                l = 0;
            }

        } else if (strcmp(comanda, "save") == 0 && OK == 0) {
            contor = 0;
            for (int i = 0; i < (int)strlen(cerinta); i++) {
                if (cerinta[i] == '\n') {
                    for (int j = CINCI; j < (int)strlen(cerinta)-1; j++) {
                        path_p1[contor++] = cerinta[j];
                    }
                }
            }
            f_output = fopen(path_p1, "wb");
            fwrite(&bin_file_p1, sizeof(bmp_fileheader), 1, f_output);
            fwrite(&bin_info_p1, sizeof(bmp_infoheader), 1, f_output);
            fwrite(pixel_p1, 3*bin_info_p1.width*bin_info_p1.height,
             1, f_output);
            OK++;
        } else if (strcmp(comanda, "set") == 0) {
            contor = 0;
            for (int i = 4; i < (int)strlen(cerinta); i++) {
                if (cerinta[i] == ' ') {
                    for (int j = PATRU; j < PAISPREZECE; j++) {
                        set_command[contor++] = cerinta[j];
                    }
                    break;
                }
            }
            if (strcmp(set_command, "draw_color") == 0) {
                ok = 0, rosu = 0, verde = 0, albastru = 0;
                for (int i = 0; i < (int)strlen(cerinta); i++) {
                    if (ok == 2 && cerinta[i] != ' ') {
                        aux = '0' - cerinta[i];
                        aux = -aux;
                        rosu = rosu + aux;
                        rosu *= ZECE;
                    }
                    if (ok == 3 && cerinta[i] != '\n' && cerinta[i] != ' ') {
                        aux = '0' - cerinta[i];
                        aux = -aux;
                        verde = verde + aux;
                        verde *= ZECE;
                    }
                    if (ok == 4 && cerinta[i] != '\n' && cerinta[i] != ' ') {
                        aux = '0' - cerinta[i];
                        aux = -aux;
                        albastru = albastru + aux;
                        albastru *= ZECE;
                    }
                    if (cerinta[i] == ' ') {
                        ok++;
                    }
                }
                rosu /= ZECE;
                verde /= ZECE;
                albastru /= ZECE;
            } else if (strcmp(set_command, "line_width") == 0) {
                ok = 0, line_width = 0;
                for (int i = 0; i < (int)strlen(cerinta); i++) {
                    if (ok == 2 && cerinta[i] != ' ' && cerinta[i] != '\n') {
                        aux = '0' - cerinta[i];
                        aux = -aux;
                        line_width = line_width + aux;
                        line_width *= ZECE;
                    }
                    if (cerinta[i] == ' ') {
                        ok++;
                    }
                }
                line_width /= ZECE;
            }
        } else if (strcmp(comanda, "draw") == 0) {
            contor = 0;
            for (int i = CINCI; i < (int)strlen(cerinta); i++) {
                if (cerinta[i] == ' ') {
                    int j = CINCI;
                    while (cerinta[j] != ' ') {
                        draw_command[contor++] = cerinta[j];
                        j++;
                    }
                    break;
                }
            }
            if (strcmp(draw_command, "line") == 0) {
                ok = 0, line_x1 = 0, line_y1 = 0, line_x2 = 0, line_y2 = 0;
                resetare_matrice(matrice, bin_info_p1.height,
                 bin_info_p1.width);
                for (int i = 0; i < (int)strlen(cerinta); i++) {
                    if (ok == 2 && cerinta[i] != ' ') {
                        aux = '0' - cerinta[i];
                        aux = -aux;
                        line_y1 = line_y1 + aux;
                        line_y1 *= ZECE;
                    }
                    if (ok == 3 && cerinta[i] != '\n' && cerinta[i] != ' ') {
                        aux = '0' - cerinta[i];
                        aux = -aux;
                        line_x1 = line_x1 + aux;
                        line_x1 *= ZECE;
                    }
                    if (ok == 4 && cerinta[i] != '\n' && cerinta[i] != ' ') {
                        aux = '0' - cerinta[i];
                        aux = -aux;
                        line_y2 = line_y2 + aux;
                        line_y2 *= ZECE;
                    }
                    if (ok == CINCI && cerinta[i] != '\n' && cerinta[i] != ' '
                    && cerinta[i] != '\n') {
                        aux = '0' - cerinta[i];
                        aux = -aux;
                        line_x2 = line_x2 + aux;
                        line_x2 *= ZECE;
                    }
                    if (cerinta[i] == ' ') {
                        ok++;
                    }
                }
                line_y1 /= ZECE;
                line_x1 /= ZECE;
                line_y2 /= ZECE;
                line_x2 /= ZECE;
                int dif_x = 0, dif_y = 0;
                dif_x = line_x1 - line_x2;
                if (dif_x < 0) {
                    dif_x = -dif_x;
                }
                dif_y = line_y1 - line_y2;
                if (dif_y < 0) {
                    dif_y = -dif_y;
                }
                linie_ingrosata(line_y1, line_x1, line_y2, line_x2, dif_x,
                dif_y, poz_x, poz_y, matrice, bin_info_p1.width,
                bin_info_p1.height, rosu, albastru, verde
                , line_width, pixel_p1);
                // -------------ingrosare linie-----------------------------
            } else if (strcmp(draw_command, "rectangle") == 0) {
                int ok = 0, rectangle_x1 = 0, rectangle_y1 = 0;
                int rectangle_width = 0, rectangle_height = 0;
                for (int i = 0; i < (int)strlen(cerinta); i++) {
                    if (ok == 2 && cerinta[i] != ' ') {
                        aux = '0' - cerinta[i];
                        aux = -aux;
                        rectangle_y1 = rectangle_y1 + aux;
                        rectangle_y1 *= ZECE;
                    }
                    if (ok == 3 && cerinta[i] != '\n' && cerinta[i] != ' ') {
                        aux = '0' - cerinta[i];
                        aux = -aux;
                        rectangle_x1 = rectangle_x1 + aux;
                        rectangle_x1 *= ZECE;
                    }
                    if (ok == 4 && cerinta[i] != '\n' && cerinta[i] != ' ') {
                        aux = '0' - cerinta[i];
                        aux = -aux;
                        rectangle_width = rectangle_width + aux;
                        rectangle_width *= ZECE;
                    }
                    if (ok == CINCI && cerinta[i] != '\n' && cerinta[i] != ' '
                    && cerinta[i] != '\n') {
                        aux = '0' - cerinta[i];
                        aux = -aux;
                        rectangle_height = rectangle_height + aux;
                        rectangle_height *= ZECE;
                    }
                    if (cerinta[i] == ' ') {
                        ok++;
                    }
                }
                rectangle_y1 /= ZECE;
                rectangle_x1 /= ZECE;
                rectangle_width /= ZECE;
                rectangle_height /= ZECE;
                int rectangle_y2 = rectangle_y1,
                rectangle_x2 = rectangle_height + rectangle_x1;

                int rectangle_y3 = rectangle_width + rectangle_y1,
                rectangle_x3 = rectangle_x1;
                int rectangle_y4 = rectangle_y3
                , rectangle_x4 = rectangle_height + rectangle_x3;
                int difd_x_l1 = rectangle_x1 - rectangle_x2;
                if (difd_x_l1 < 0) {
                    difd_x_l1 = -difd_x_l1;
                }
                int difd_y_l1 = rectangle_y1 - rectangle_y2;
                if (difd_y_l1 < 0) {
                    difd_y_l1 = -difd_y_l1;
                }

                int difd_x_l2 = rectangle_x1 - rectangle_x3;
                if (difd_x_l2 < 0) {
                    difd_x_l2 = -difd_x_l2;
                }
                int difd_y_l2 = rectangle_y1 - rectangle_y3;
                if (difd_y_l2 < 0) {
                    difd_y_l2 = -difd_y_l2;
                }

                int difd_x_l3 = rectangle_x2 - rectangle_x4;
                if (difd_x_l3 < 0) {
                    difd_x_l3 = -difd_x_l3;
                }
                int difd_y_l3 = rectangle_y2 - rectangle_y4;
                if (difd_y_l3 < 0) {
                    difd_y_l3 = -difd_y_l3;
                }

                int difd_x_l4 = rectangle_x3 - rectangle_x4;
                if (difd_x_l4 < 0) {
                    difd_x_l4 = -difd_x_l4;
                }
                int difd_y_l4 = rectangle_y3 - rectangle_y4;
                if (difd_y_l4 < 0) {
                    difd_y_l4 = -difd_y_l4;
                }
                resetare_matrice(matrice, bin_info_p1.height,
                 bin_info_p1.width);
                linie_ingrosata(rectangle_y1, rectangle_x1, rectangle_y2,
                rectangle_x2, difd_x_l1, difd_y_l1, poz_x, poz_y, matrice,
                bin_info_p1.width, bin_info_p1.height, rosu, albastru
                , verde, line_width, pixel_p1);

                resetare_matrice(matrice, bin_info_p1.height,
                 bin_info_p1.width);

                linie_ingrosata(rectangle_y1, rectangle_x1, rectangle_y3,
                rectangle_x3, difd_x_l2, difd_y_l2, poz_x, poz_y, matrice,
                bin_info_p1.width, bin_info_p1.height, rosu, albastru
                , verde, line_width, pixel_p1);

                resetare_matrice(matrice, bin_info_p1.height,
                 bin_info_p1.width);

                linie_ingrosata(rectangle_y2, rectangle_x2, rectangle_y4,
                rectangle_x4, difd_x_l3, difd_y_l3, poz_x, poz_y, matrice,
                bin_info_p1.width, bin_info_p1.height, rosu, albastru
                , verde, line_width, pixel_p1);

                resetare_matrice(matrice, bin_info_p1.height,
                 bin_info_p1.width);

                linie_ingrosata(rectangle_y3, rectangle_x3, rectangle_y4,
                rectangle_x4, difd_x_l4, difd_y_l4, poz_x, poz_y, matrice,
                bin_info_p1.width, bin_info_p1.height, rosu, albastru
                , verde, line_width, pixel_p1);



            } else {
                ok = 0, triangle_y1 = 0, triangle_x1 = 0, triangle_y2 = 0;
                triangle_x2 = 0, triangle_y3 = 0, triangle_x3 = 0;
                resetare_matrice(matrice, bin_info_p1.height,
                 bin_info_p1.width);
                for (int i = 0; i < (int)strlen(cerinta); i++) {
                    if (ok == 2 && cerinta[i] != ' ') {
                        aux = '0' - cerinta[i];
                        aux = -aux;
                        triangle_y1 = triangle_y1 + aux;
                        triangle_y1 *= ZECE;
                    }
                    if (ok == 3 && cerinta[i] != '\n' && cerinta[i] != ' ') {
                        aux = '0' - cerinta[i];
                        aux = -aux;
                        triangle_x1 = triangle_x1 + aux;
                        triangle_x1 *= ZECE;
                    }
                    if (ok == 4 && cerinta[i] != '\n' && cerinta[i] != ' ') {
                        aux = '0' - cerinta[i];
                        aux = -aux;
                        triangle_y2 = triangle_y2 + aux;
                        triangle_y2 *= ZECE;
                    }
                    if (ok == CINCI && cerinta[i] != '\n' &&
                    cerinta[i] != ' ') {
                        aux = '0' - cerinta[i];
                        aux = -aux;
                        triangle_x2 = triangle_x2 + aux;
                        triangle_x2 *= ZECE;
                    }
                    if (ok == SASE && cerinta[i] != ' ') {
                        aux = '0' - cerinta[i];
                        aux = -aux;
                        triangle_y3 = triangle_y3 + aux;
                        triangle_y3 *= ZECE;
                    }
                    if (ok == SAPTE && cerinta[i] != '\n' &&
                    cerinta[i] != ' ' &&
                    cerinta[i] != '\n') {
                        aux = '0' - cerinta[i];
                        aux = -aux;
                        triangle_x3 = triangle_x3 + aux;
                        triangle_x3 *= ZECE;
                    }
                    if (cerinta[i] == ' ') {
                        ok++;
                    }
                }
                triangle_y1 /= ZECE;
                triangle_x1 /= ZECE;
                triangle_y2 /= ZECE;
                triangle_x2 /= ZECE;
                triangle_y3 /= ZECE;
                triangle_x3 /= ZECE;
                int dif_x_l1 = 0, dif_y_l1 = 0, dif_x_l2 = 0, dif_y_l2 = 0;
                int dif_x_l3 = 0, dif_y_l3 = 0;

                dif_x_l1 = dif_triunghi(triangle_x1, triangle_x2);
                dif_y_l1 = dif_triunghi(triangle_y1, triangle_y2);
                dif_x_l2 = dif_triunghi(triangle_x1, triangle_x3);
                dif_y_l2 = dif_triunghi(triangle_y1, triangle_y2);
                dif_x_l3 = dif_triunghi(triangle_x2, triangle_x3);
                dif_y_l3 = dif_triunghi(triangle_x2, triangle_x3);
                linie_ingrosata(triangle_y1, triangle_x1, triangle_y2,
                triangle_x2, dif_x_l1, dif_y_l1, poz_x, poz_y, matrice,
                bin_info_p1.width, bin_info_p1.height, rosu, albastru
                , verde, line_width, pixel_p1);
                resetare_matrice(matrice, bin_info_p1.height,
                 bin_info_p1.width);
                linie_ingrosata(triangle_y1, triangle_x1, triangle_y3,
                triangle_x3, dif_x_l2, dif_y_l2, poz_x, poz_y, matrice
                , bin_info_p1.width, bin_info_p1.height, rosu, albastru
                , verde, line_width, pixel_p1);
                resetare_matrice(matrice, bin_info_p1.height,
                 bin_info_p1.width);
                linie_ingrosata(triangle_y2, triangle_x2, triangle_y3,
                triangle_x3, dif_x_l3, dif_y_l3, poz_x, poz_y,
                matrice, bin_info_p1.width, bin_info_p1.height,
                rosu, albastru, verde, line_width, pixel_p1);
            }

        } else if (strcmp(comanda, "fill") == 0) {
            contor = 0, ok = 0, fill_y = 0, fill_x = 0;
            for (int i = 0; i < bin_info_p1.height; i++) {
                    for (int j = 0; j < bin_info_p1.width; j++) {
                        matrice[i][j] = 0;
                    }
                }
            for (int i = 0; i < (int)strlen(cerinta); i++) {
                if (ok == 1 && cerinta[i] != ' ') {
                    aux = '0' - cerinta[i];
                    aux = -aux;
                    fill_y = fill_y + aux;
                    fill_y *= ZECE;
                }
                if (ok == 2 && cerinta[i] != ' ' && cerinta[i] != '\n') {
                    aux = '0' - cerinta[i];
                    aux = -aux;
                    fill_x = fill_x + aux;
                    fill_x *= ZECE;
                }
                if (cerinta[i] == ' ') {
                    ok++;
                }
            }
            fill_y /= ZECE;
            fill_x /= ZECE;
            albastru_og = (char)pixel_p1[3 * fill_x * bin_info_p1.width +
            3 * fill_y];
            verde_og = (char)pixel_p1[3 * fill_x * bin_info_p1.width +
            (3 * fill_y)+1];
            rosu_og = (char)pixel_p1[3 * fill_x * bin_info_p1.width +
            (3 * fill_y)+2];
            matrice[fill_y][fill_x] = 1;
            int CONTOR = 0;
            for (int i = 0; i < bin_info_p1.height; i++) {
                for (int j = 0; j < bin_info_p1.width; j++) {
                    if (pixel_p1[3*i*bin_info_p1.width + 3*j]
                     == (char)albastru_og
                    && pixel_p1[3*i*bin_info_p1.width + 3*j+1]
                     == (char)verde_og
                    && pixel_p1[3*i*bin_info_p1.width + 3*j+2]
                     == (char)rosu_og) {
                        CONTOR++;
                    }
                }
            }
            if (CONTOR == bin_info_p1.height*bin_info_p1.width) {
                for (int i = 0; i <= bin_info_p1.height; i++) {
                    for (int j = 0; j <= 3*bin_info_p1.width; j++) {
                        pixel_p1[3*i*bin_info_p1.width + 3*j] = (char)albastru;
                        pixel_p1[3*i*bin_info_p1.width + 3*j+1] = (char)verde;
                        pixel_p1[3*i*bin_info_p1.width+ 3*j+2] = (char)rosu;
                    }
                }
            } else {
                Fill(fill_x, fill_y, matrice, rosu, verde, albastru,
                bin_info_p1.width, bin_info_p1.height, pixel_p1, rosu_og,
                 verde_og, albastru_og);
            }

        } else if (strcmp(cerinta, "quit\n") == 0) {
            free(cerinta);
            free(comanda);
            free(path_p1);
            free(path_p2);
            free(bin_p1);
            free(bin_p2);
            return 0;
        }
    }
}
