#include "ard.h"

int arduinoReadData(int *x)
{
    char chemin[] = "/dev/ttyUSB0";
    FILE *f;
    char c;
    f = fopen(chemin, "r");

    if (f == NULL)
        return (-1);

    fscanf(f, "%d", x);

    fclose(f);

    return (0);
}

int arduinoReadDataJoyStickPos(int *x, int *y, int *state)
{
    char chemin[] = "/dev/ttyUSB0";
    FILE *f;
    char c;
    f = fopen(chemin, "r");

    if (f == NULL)
        return (-1);

    fscanf(f, "X: %d | Y: %d | Button: %d", x, y, state);

    fclose(f);
    return (0);
}
int arduinoWriteData(int x)
{
    char chemin[] = "/dev/ttyUSB0";
    FILE *f;

    f = fopen(chemin, "w");
    if (f == NULL)
        return (-1);

    fprintf(f, "%d", x);
    fclose(f);

    return (0);
}