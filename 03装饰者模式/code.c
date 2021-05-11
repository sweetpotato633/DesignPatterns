#include <stdint.h>

typedef struct
{
    char* (*description)();
    uint32_t (*cost)();
}TTMaterial;

//体验一下类爆炸吧
//咖啡+奶.c
static char* description1()
{
    const char descript[] = "This is coffee + milk";
    return descript;
}
static uint32_t cost1()
{
    return (1+3);//咖啡+奶的钱
}
const TTMaterial CoffeeAndMilk = {
    .description = description1,
    .cost = cost1,
};

//咖啡+奶+豆浆.c
//咖啡+奶+豆浆+.c
//纯咖啡.c
//。。。。。。

//换个思路
typedef struct
{
    uint8_t (*hasMilk)();
    uint8_t (*hasDouJiang)();
    uint8_t (*hasMoKa)();
    void (*setMilk)();
    void (*setDouJiang)();
    void (*setMoKa)();
    char* (*description)();
    uint32_t (*cost)();
}TTCoffee;


uint8_t hasMilk(){;}
uint8_t hasDouJiang(){;}
uint8_t hasMoKa(){;}
void setMilk(){;}
void setDouJiang(){;}
void setMoKa(){;}
char* description(){;}
void cost2()
{
    int count = 0;
    if(hasMilk())
    {
        count += 1;
    }
    if(hasDouJiang())
    {
        count += 2;
    }
    if(hasMoKa())
    {
        count += 1;
    }
    count += 3;//coffee
    return count;
}

const TTCoffee Coffee={
    //以上接口函数省略
    .cost = cost2,
};

void main(){
    Coffee.setMilk();
    Coffee.setDouJiang();
    Coffee.cost();
}

//这样做有什么问题？
//如果要增加饮料怎么办？双倍的摩卡+小份的牛奶怎么处理？

//简单的继承和接口不能满足要求，引入装饰者模式
//以普通咖啡为主体，用牛奶、豆浆、摩卡来装饰它，给它增加新内容
extern char* strcat(char*str1,char*str2);

typedef struct
{
    char* (*description)();
    uint32_t (*cost)();
    TTMaterial2 (*init)(TTMaterial2 *material);
}TTMaterial2;

//Milk.c
TTMaterial2 *tMaterial;
static TTMaterial2 initMilk(TTMaterial2 *material)
{
    tMaterial = material;
}
static char* descriptionMilk()
{
    if(tMaterial != 0)
    {
        return strcat("Milk,",tMaterial->description());
    }
    else
    {
        return "Milk,";
    }
}
static void costMilk()
{
    if(tMaterial != 0)
    {
        return 1 + tMaterial->cost();
    }
    else
    {
        return 1;
    }
}
const TTMaterial2 Milk = {
    .description = descriptionMilk,
    .cost = costMilk,
    .init = initMilk,
};

const TTMaterial2 Coffee2 = {
    .description = descriptionMilk,
    .cost = costMilk,
    .init = initMilk,
};

void main()
{
    TTMaterial2 Drink;
    Drink = Coffee2.init(&Drink);
    Drink.description();
    Drink.cost();
}

