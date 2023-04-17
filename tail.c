#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CBLEN 4095

int main(int argc, char **argv) {
    long line_count=10;
    char input=0;
    char *param_ptr;

    if(argc>1) {
// looking for options
        param_ptr=argv[1];
        if(!strcmp(param_ptr,"-n")){
            if(argc == 2){
                fprintf(stderr,"Option requires number");
                exit(1);
            }
            line_count=atol(argv[2]);
            if(line_count<=0){
                fprintf(stderr,"Invalid option parameter");
                exit(1);
            }
            if(argc!=4){
                param_ptr=argv[3];
            }else{
                input=1;
            }
        }
    }else{
        input=1;
    }

    FILE *fp;
    if(input){
        fp=fopen(param_ptr,"r");
        if(fp==NULL){
            fprintf(stderr,"File could not be opened.");
            exit(1);
        }
    }
    char* temp_buff=malloc(sizeof(char)*CBLEN);
    struct Circular_buffer* cb_buffer;

    while((fgets(temp_buff,CBLEN,(input)?stdin:fp))){

    }






return 0;
}
