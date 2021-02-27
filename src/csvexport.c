#include "csvexport.h"

void export_to_csv(char *filename) {
    int fd = open(filename, O_WRONLY|O_APPEND|O_CREAT, 0775);
    if(fd<0) {
        printf("Cannot open %s for writing.", filename);
        exit(2);
    }

    char* row;

    int length;
    length = snprintf(NULL, 0, "%u,%d,%d\n", game.year, game.economy_stats.budget, game.economy_stats.GDP);

    row = (char*)malloc(sizeof(char) * length);
    snprintf(row, length+1,"%u,%d,%d\n", game.year, game.economy_stats.budget, game.economy_stats.GDP);
    ssize_t written = write(fd, row, length);
    free(row);
    close(fd);
}