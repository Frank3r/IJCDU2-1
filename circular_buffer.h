//
// Created by Frank3r on 15.04.2023.
//

#ifndef IJCDU2_CIRCULAR_BUFFER_H
#define IJCDU2_CIRCULAR_BUFFER_H

struct Circular_buffer{
    char* buf;
    long start;
    long end;
    long limit;
    long lines;
};

struct Circular_buffer *cb_create(long n);
void cb_put(struct Circular_buffer *cb, const char *line);
char* cb_get(struct Circular_buffer *cb);
void cb_free(struct Circular_buffer *cb);

#endif //IJCDU2_CIRCULAR_BUFFER_H
