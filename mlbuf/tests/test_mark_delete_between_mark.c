#include "test.h"

MAIN("hello\nworld",
    mark_t* other;
    other = buffer_add_mark(buf, NULL, 0);
    mark_move_beginning(cur);
    mark_move_end(other);
    mark_delete_between_mark(cur, other);
    ASSERT("count", 0, buf->byte_count);
)
