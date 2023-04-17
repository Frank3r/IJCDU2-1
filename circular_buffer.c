//
// Created by Frank3r on 14.04.2023.
//

// by my understanding of assignment This Circular buffer
// will be used for loading a line and then printing it out

#include <stdlib.h>
#include <stdio.h>
#include "circular_buffer.h"



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
    for(long i = 0 ; i < n; i++){
        buffer->buf[i]=1;
    }
    buffer->start=0;
    buffer->end=0;
    buffer->limit=n;
    buffer->lines=0;
    buffer->overflow=0;
    return buffer;
}

/*
 * cp_put
 * puts a line into the buffer
 * throws overflow error when line exceeds
 * buffer size limit, but keeps shortened line
 */
void cb_put(struct Circular_buffer *cb, const char *line){
    for(long i = 0; line[i]!='\0'&& line[i]!='\n';i++){
        if(cb->buf[cb->end]=='\0'&&cb->lines!=0)cb->lines--;
        cb->buf[cb->end++]=line[i];
        cb->end%=cb->limit;
        if(cb->end==cb->start){
            cb->start++;
            cb->start%=cb->limit;
        }
    }
    if(cb->buf[cb->end]=='\0'&&cb->lines!=0)cb->lines--;
    cb->buf[cb->end++]='\0';
    cb->end%=cb->limit;
    if(cb->end==cb->start){
        cb->start++;
        cb->start%=cb->limit;
    }
    cb->lines++;
}

long findEndpoint(struct Circular_buffer *cb){
    long i;
    for(i = cb->start; cb->buf[i%cb->limit]!='\0';i++); // COUNTER
    i++;
    return i%cb->limit;
}

char* cb_get(struct Circular_buffer *cb){
    if(cb->lines==0)return NULL;

    long endpoint= findEndpoint(cb);
    if(cb->start>=endpoint){ // rotation to the right
        while(cb->start!=cb->limit){
            char temp=cb->buf[cb->limit-1];
            for(long i = cb->limit-1;i > 0; i--){
                cb->buf[i]=cb->buf[i-1];
            }
            cb->buf[0]=temp;
            cb->start++;
            cb->end++;
            endpoint++;
        }
        cb->start=0;
    }
    char* oldstart=&cb->buf[cb->start];
    cb->start=endpoint;
    cb->lines--;
    return oldstart;
}

/*
 * cb_free
 * Frees the buffers memory.
 */

void cb_free(struct Circular_buffer *cb){
    free(cb->buf);
    free(cb);
}



