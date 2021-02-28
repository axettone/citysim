#include "csvexport.h"

void export_to_csv(char *filename) {
    int fd = open(filename, O_WRONLY|O_APPEND|O_CREAT, 0775);
    if(fd<0) {
        printf("Cannot open %s for writing.", filename);
        exit(2);
    }

    char* row;

    int length;
    const char *csv_format = "%u,%d,%d,%u\n";
    length = snprintf(NULL, 0, csv_format,
        game.year,
        game.economy_stats.budget,
        game.economy_stats.GDP,
        game.population
    );

    row = (char*)malloc(sizeof(char) * length);
    snprintf(row, length+1,csv_format,
        game.year,
        game.economy_stats.budget,
        game.economy_stats.GDP,
        game.population
    );

    ssize_t written = write(fd, row, length);
    free(row);
    close(fd);
}