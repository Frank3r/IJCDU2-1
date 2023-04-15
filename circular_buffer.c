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
struct Circular_buffer *cb_create(long n){
    struct Circular_buffer *buffer;
    buffer=malloc(sizeof(struct Circular_buffer));
    buffer->buf = malloc(sizeof(char)*n);
    if(buffer->buf == NULL){
        fprintf(stderr,"Failed to allocate buffer space");
        exit(1);
    }
    buffer->start=0;
    buffer->end=0;
    buffer->limit=n;
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

void cb_put(struct Circular_buffer *cb, const char *line){
    for(long i=0; line[i] != '\n' && line[i] != '\0';i++){
        cb->buf[cb->end++]=line[i];
        cb->end%=cb->limit;
        if(cb->end == cb->start){
            fprintf(stderr,"Circular buffer limit overflow");
            break;
        }
    }
    if(cb->end == cb->start){ //add end character
        cb->buf[cb->end-1]='\0';
    }else{
        cb->buf[cb->end++]='\0';
    }
}


/*
 * cb_get
 * Returns pointer to buffer
 * Note:
 * To avoid memory allocation,
 * the contents are rotated until the line ends exactly at its limit.
 * This will put the start pointer at exactly zero after line is read.
 */


long cb_findEndLine(struct Circular_buffer *cb){
    long i;
    for(i=cb->start;cb->buf[i%cb->limit]!='\0';i++); // COUNTER
    i++; // count in the endline character
    return (i<cb->start)?i%cb->limit:i;
}

char* cb_get(struct Circular_buffer *cb){
    long endline_point = cb_findEndLine(cb);
    if(endline_point < cb->start){
        //ROTATION TO THE RIGHT
        char temp;
        while(cb->start!=0){
            temp=cb->buf[cb->limit-1];
            for(int i=cb->limit-1; i > 0;i--){
                cb->buf[i]=cb->buf[i-1];
            }
            cb->buf[0] = temp;
            cb->start=(cb->start+1)%cb->limit;
            cb->end++;
            endline_point++;
        }
    }
    return &cb->buf[cb->start];
}

/*
 * cb_free
 * Frees the buffers memory.
 */

void cb_free(struct Circular_buffer *cb){
    free(cb->buf);
    free(cb);
}



