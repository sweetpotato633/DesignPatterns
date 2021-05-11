#include <stdint.h>
#include "Decorator.h"
#include <string.h>
#include <stdio.h>

static TTMaterial2* tMaterial;

static TTMaterial2 *initMilk(TTMaterial2* material)
{
    tMaterial = material;
    return (TTMaterial2 *)&Milk;
}
static void descriptionMilk()
{
    char name[] = "Milk,";

    if (tMaterial != 0)
    {
        tMaterial->description();
    }
    printf(name);

}
static uint32_t costMilk()
{
    if (tMaterial != 0)
    {
        return 1 + tMaterial->cost();
    }
    else
    {
        return 1;
    }
}
const TTMaterial2 Milk = {
    descriptionMilk,
    costMilk,
    initMilk,
};