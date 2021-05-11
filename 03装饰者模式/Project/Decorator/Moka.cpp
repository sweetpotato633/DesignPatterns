#include <stdint.h>
#include "Decorator.h"
#include <string.h>
#include <stdio.h>

static TTMaterial2* tMaterial;

static TTMaterial2* initMoka(TTMaterial2* material)
{
    tMaterial = material;
    return (TTMaterial2*)&Moka;
}
static void descriptionMoka()
{
    char name[] = "Moka,";

    if (tMaterial != 0)
    {
        tMaterial->description();
    }
    printf(name);

}
static uint32_t costMoka()
{
    if (tMaterial != 0)
    {
        return 10 + tMaterial->cost();
    }
    else
    {
        return 10;
    }
}
const TTMaterial2 Moka = {
    descriptionMoka,
    costMoka,
    initMoka,
};