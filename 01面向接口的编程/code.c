//设计原则
//#1 找出不变的地方，独立出来，区分变与不变
//#2 针对接口编程 而不是针对实现编程
//#3 多用组合 少用继承


// 问题 代码的高效复用与便于修改
//普通鸭子 塑料鸭子
#include <stdint.h>

void NormalDuckFly()
{

}
void PlasticDuckFly()
{

}

void NormalDuckQuack()
{

}

void PlasticDuckQuack()
{

}

//应用层函数
void DoFly(uint8_t type)
{
    switch(type)
    {
        case 1:
            NormalDuckFly();
            break;
        case 2:
            PlasticDuckFly();
            break;
        default:
        break;
    }
}
void DoQuack(uint8_t type)
{

}


typedef struct 
{
    void (*fly)();
    void (*quack)();
    /* data */
}TTDuck;

static void NormalDuckFly2()
{

}
static void NormalDuckQuack2()
{

}
const TTDuck NormalDuck={
    .fly = NormalDuckFly2,
    .quack = NormalDuckQuack2,
};

//应用层函数 应用层体现的应该是抽象，而不是具体
//越往顶层，越应该抽象，具体的内容在底层体现
TTDuck *GetInstanceOfDuck(uint8_t type)
{
    switch (type)
    {
    case 1:
        /* code */
        return &NormalDuck;
        break;
    
    default:
        break;
    }
}

void DoDuckAction(uint8_t type)
{
    //
    TTDuck *pDuck = GetInstanceOfDuck(type);
    pDuck->fly();
    pDuck->quack();
}

//发散一下，规约，串口如果用这种理念来设计，应该如何进行？哪些是变的，哪些是不变的，不变的提取接口，变化的做接口实现




