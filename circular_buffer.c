//
// Created by Frank3r on 14.04.2023.
//

// by my understanding of assignment This Circular buffer
// will be used for loading a line and then printing it out

#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

struct Circular_buffer{
    char* buf;
    long start;
    long end;
    long limit;
};


/* cb_create
 * Creates buffer of size n
 */
struct Circular_buffer cb_create(long n){
    struct Circular_buffer buffer;
    buffer.buf = malloc(sizeof(char)*n);
    if(buffer.buf == NULL){
        fprintf(stderr,"Failed to allocate buffer space");
        exit(1);
    }
    buffer.start=0;
    buffer.end=0;
    buffer.limit=n;
    return buffer;
}

/*
 * cp_put
 * puts a line into the buffer
 * throws overflow error when line is longer
 * than buffer size limit, but keeps shortened line
 *
 * if buffer is full, the contents are overwritten
 */

void cb_put(struct Circular_buffer cb, const char* line){
    for(long i=0; line[i] != '\n' && line[i] != '\0';i++){
        cb.buf[cb.end++]=line[i];
        cb.end%=cb.limit;
        if(cb.end == cb.start){
            fprintf(stderr,"Circular buffer limit overflow");
            break;
        }
    }
    if(cb.end == cb.start){ //add end character
        cb.buf[cb.end-1]='\0';
    }else{
        cb.buf[cb.end++]='\0';
    }
}


/*
 * cb_get
 * Returns pointer to buffer
 * Note:
 * To avoid memory allocation,
 * the contents are rotated until start pointer is equal 0
 */

char* cb_get(struct Circular_buffer cb){ // return full content of circular Buffer
    char temp_char;
    while(cb.start!=0){ // rotate buffer to the left
        temp_char=cb.buf[0];
        for(long i = 0 ; i < cb.limit-1;i++){
            cb.buf[i]=cb.buf[i+1];
        }
        cb.buf[cb.limit-1]=temp_char;
    }
    return cb.buf;
}

/*
 * cb_free
 * Frees the buffers memory.
 */

void cb_free(struct Circular_buffer cb){
    free(cb.buf);
}



