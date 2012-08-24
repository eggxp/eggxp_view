/** 
 @file  callbacks.h
 @brief ENet callbacks
*/
#ifndef ENET_CALLBACKSH
#define ENET_CALLBACKSH

#include <stdlib.h>

typedef struct _ENetCallbacks
{
    void * (ENET_CALLBACK * malloc) (size_t size);
    void (ENET_CALLBACK * free) (void * memory);
    int (ENET_CALLBACK * rand) (void);
    void (ENET_CALLBACK * no_memory) (void);
} ENetCallbacks;

/** @defgroup callbacks ENet internal callbacks
    @{
    @ingroup private
*/
extern void * enet_malloc (size_t);
extern void   enet_free (void *);
extern int    enet_rand (void);

/** @} */

#endif /* ENET_CALLBACKSH */

