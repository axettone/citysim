#include "csvexport.h"

void export_to_csv(char *filename) {
    int fd = open(filename, O_WRONLY|O_APPEND|O_CREAT, 0664);
    if(fd<0) {
        printf("Cannot open %s for writing.", filename);
        exit(2);
    }
    
    int length;
    struct stat statbuf;
    ssize_t written;
    fstat(fd, &statbuf);
    char* row;

    if(statbuf.st_size == 0) {
        //If the CSV is new, print the header row
        const char* header = "Year,budget,GDP,unemployment,population\n";        
        written = write(fd,header,strlen(header));
    }
    

    const char *csv_format = "%u,%d,%d,%.2f,%u\n";
    length = snprintf(NULL, 0, csv_format,
        game.year,
        game.economy_stats.budget,
        game.economy_stats.GDP,
        100-100*((float)(game.ind_workers + game.com_workers)/game.population),
        game.population
    );

    row = (char*)malloc(sizeof(char) * length);
    snprintf(row, length+1,csv_format,
        game.year,
        game.economy_stats.budget,
        game.economy_stats.GDP,
        game.population
    );

    written = write(fd, row, length);
    free(row);
    close(fd);
}