#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 256
#define FILE_NAME "schedule.txt"

int main(int argc, char *argv[]){
    /* set variables */
    printf("setting variables\n");
    FILE *file;
    struct tm tm;
    int length = 0;
    char a_schedule[BUF_SIZE];
    char schedules[BUF_SIZE][BUF_SIZE];
    int a_time[5];

    /* setup time function */
    printf("setting up time function\n");
    time_t t=time(NULL);
    localtime_r(&t, &tm);

    /* count txt file's lines */
    printf("counting lines\n");
    file = fopen(FILE_NAME,"r");
    printf("opend file\n");
    while (fgets(a_schedule, BUF_SIZE, file) != NULL) {
        length++;
    }
    printf("counted(%d)\n", length);
    fclose(file);

    /* set the schedule time (default is current time) */
    printf("setting the schedule time\n");
    int times[5] = {tm.tm_min,tm.tm_hour,tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900};
    for(int i=2;i<argc;i++){
        times[i-2] = atoi(argv[i]); // put list input values
    }

    printf("Schedule that you put is %s(%d/%d/%d %d:%d)\n", argv[1], times[4], times[3], times[2], times[1], times[0]);

    /* read txt file's values and output and check */
    printf("reading txt file\n");
    file = fopen(FILE_NAME,"r");
    printf("Your all of schedule(%d) is:\n",length);
    for(int i=0;i<length;i++){
        //printf("im in for(%d)\n",i);
        // read and check
        if(fscanf(file, "%s %d %d %d %d %d\n", a_schedule, &a_time[0], &a_time[1], &a_time[2], &a_time[3], &a_time[4])!=EOF
        && (a_time[4]>tm.tm_year+1900
        || a_time[4]==tm.tm_year+1900 && a_time[3]>tm.tm_mon+1
        || a_time[4]==tm.tm_year+1900 && a_time[3]==tm.tm_mon+1 && a_time[2]>tm.tm_mday
        || a_time[4]==tm.tm_year+1900 && a_time[3]==tm.tm_mon+1 && a_time[2]==tm.tm_mday && a_time[1]>tm.tm_hour
        || a_time[4]==tm.tm_year+1900 && a_time[3]==tm.tm_mon+1 && a_time[2]==tm.tm_mday && a_time[1]==tm.tm_hour && a_time[0]>tm.tm_hour)){
            printf("%s(%d/%d/%d %d:%d)\n", a_schedule, a_time[4], a_time[3], a_time[2], a_time[1], a_time[0]);
            // put list correct values
            sprintf(schedules[i], "%s %d %d %d %d %d\n", a_schedule, a_time[0], a_time[1], a_time[2], a_time[3], a_time[4]);
        }
    }
    printf("loop end");
    fclose(file);

    printf("printed");
    /* put txt file correct values list */
    file = fopen(FILE_NAME,"w");
    for(int i=0;i<=sizeof(schedules);i++){
        fprintf(file, "%s", schedules[i]);
    }
    fprintf(file, "%s %d %d %d %d %d\n", argv[1], times[0], times[1], times[2], times[3], times[4]);
    fclose(file);

    printf("\nI'll tell you this schedule when it's time\n");
    printf("\nnow is %d/%d/%d %d:%d\n",tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min);

    return 0;
}