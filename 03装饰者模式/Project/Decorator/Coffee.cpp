#include <stdint.h>
#include "Decorator.h"
#include <string.h>
#include <stdio.h>

static TTMaterial2* tMaterial;

static TTMaterial2* initCoffee(TTMaterial2* material)
{
    tMaterial = material;
    return (TTMaterial2*)&Coffee;
}
static void descriptionCoffee()
{
    char name[] = "Coffee,";

    if (tMaterial != 0)
    {
        tMaterial->description();
    }
    printf(name);
}
static uint32_t costCoffee()
{
    if (tMaterial != 0)
    {
        return 3 + tMaterial->cost();
    }
    else
    {
        return 3;
    }
}
const TTMaterial2 Coffee = {
    descriptionCoffee,
    costCoffee,
    initCoffee,
};