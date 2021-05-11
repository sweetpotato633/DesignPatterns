#ifndef _DECORATOR_H__

#define _DECORATOR_H__
#include <stdint.h>
typedef struct _material
{
    void (*description)(void);
    uint32_t (*cost)();
    struct _material* (*init)(struct _material* material);
}TTMaterial2;

extern const TTMaterial2 Milk;
extern const TTMaterial2 Coffee;
extern const TTMaterial2 Moka;
#endif // !_DECORATOR_H__

