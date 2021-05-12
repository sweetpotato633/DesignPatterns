#include <stdint.h>

//做披萨，并且最终送出去，要分几步呢，先来一个普通的实现

typedef struct
{
    void (*prepare)();
    void (*bake)();
    void (*cut)();
    void (*box)();
}TTPizza;

//CheesePizza.c
extern TTPizza CheesePizza;
//GreekPizza.c
extern TTPizza GreekPizza;
//PepperoniPizza.c
extern TTPizza PepperoniPizza;

TTPizza* orderPizza(uint8_t type)
{
    TTPizza *tPizza = 0;
    if(type == 1)
    {
        tPizza = &CheesePizza;
    }
    else if(type == 2)
    {
        tPizza = &GreekPizza;
    }
    else if(type == 3)
    {
        tPizza = &PepperoniPizza;
    }
    else
    {
        return 0;
    }

    tPizza->prepare();
    tPizza->bake();
    tPizza->cut();
    tPizza->box();

    return tPizza;
}

//有什么问题？后面如果新增披萨类型或者某种披萨不要了，if else部分的代码是不是需要更改，那么从测试的原则看，整个orderPizza是不是都需要重测？
//违反了什么原则？
//顶层应用体现的应该是抽象，而不是具体
//不变的和改变的，要分开

//很明显，此时需要把变化的部分封装起来了,有一个方法或者对象，专门负责生成披萨，这个东东就叫做披萨工厂
TTPizza* pizzaFactory(uint8_t type)//也可以封装成对象，看上去更美观，此处简化处理了
{
    if(type == 1)
    {
        return &CheesePizza;
    }
    else if(type == 2)
    {
        return &GreekPizza;
    }
    else if(type == 3)
    {
        return &PepperoniPizza;
    }
    else
    {
        return 0;
    }
}

TTPizza* orderPizza(uint8_t type)
{
    TTPizza *tPizza = 0;
    tPizza = pizzaFactory(type);

    tPizza->prepare();
    tPizza->bake();
    tPizza->cut();
    tPizza->box();

    return tPizza;
}

//貌似只是简单的把代码挪到另一个地方去了，问题依然存在啊
//是的，上面的工厂叫做简单工厂，严格的说算不上设计模式，反而比较像一种编程习惯，不过这种简单工厂对于我们的日常应用足够了

//高级语言中，可以通过反射来动态创建对象

TTPizza pizzaFactory2(char* className)
{
    TTPizza tPizza;

    tPizza = (TTPizza)Class.forName(className).newInstance();

    return tPizza;
}

//新建 otherPizza.c
//利用反射技巧，工厂方法不需要做修改，只需要新增otherPizza.c，写好新增的披萨类型就可以了