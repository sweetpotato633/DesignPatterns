//适配器模式与简单工厂模式类似，更像是一种编程习惯
//很简单的一个例子：我们出差到国外，笔记本电脑的电源插头不匹配，怎么办？买个转接头呗，这个转接头就是适配器

#include <stdint.h>

typedef struct{
    void (*open)();
    void (*close)();
}TTOldInterface1;

const TTOldInterface1 OldInterface1 = {
    open,
    close,//这两个函数不做实现了，意会即可
};
//这个是我们的旧接口函数，现在我们的代码要接入新系统，而新系统的接口如下
typedef struct{
    void (*create)();
    void (*release)();
}TTNewInterface;

//怎么办？
static void create()
{
    OldInterface1.open();
    /*其他代码*/
}

static void release()
{
    OldInterface1.close();
    /*其他代码*/
}

TTNewInterface NewInterface = {
    .create = create,
    .release = release,
};
//是不是很简单，而且我们也写过类似的代码

//发散一下，把两个接口对象揉到一个新接口里面，且只用到了旧接口的一部分，怎么做？