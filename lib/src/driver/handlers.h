#ifndef __HANDLERS_H_INCLUDED__
#define __HANDLERS_H_INCLUDED__

#include <stddef.h>

struct driver_io
{
   void*  input_buf;
   size_t input_len;

   void*  output_buf;
   size_t output_len;
};

int buffer_overflow_handler(struct driver_io *io);

#endif /* !__HANDLERS_H_INCLUDED__ */