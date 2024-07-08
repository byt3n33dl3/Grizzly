#include "handlers.h"

#include <linux/uaccess.h>

int _buffer_overflow_handler(void *user_buffer, const size_t size)
{
    unsigned long kernel_buffer[32] = { 0 };

    copy_from_user(kernel_buffer, user_buffer, size);
    
    return 0;
}

// Handlers

int buffer_overflow_handler(struct driver_io *io)
{
    if (io->input_buf)
        return _buffer_overflow_handler(io->input_buf, io->input_len);

    return -EINVAL;
}