//单例模式一般情况下不适用于C语言，因为C语言中一般都是单例。。。
//出于设计模式的完整性，这里简单讲一下

//某个对象是否只需要一个全局实例？并且需要确保全局只有一个？如果有这种需求的话，就可以考虑用单例了
//举例说明：电脑只有一个物理串口，需要通过创建一个串口控制对象来访问物理串口，多个串口对象同时访问一个物理串口可能会崩。那么怎么保证控制对象的唯一性呢？
//电脑的回收站，只需要一个吧

//技巧很简单，对于高级语言，构造函数私有化，不让外面用，需要的话，自己构造自己。
//外面的用不了构造函数，可不就是单例了
//单例又分为两种，一种是饿汉式，一上来管你有用没有，先创建一个单例；一种是懒汉式，先不创建，等需要的时候再创建

public class Singleton{
    private static Singleton uniqueInstance;
    public static Singleton getInstance()
    {
        if (uniqueInstance != null) {
            uniqueInstance = new Singleton();
        }
        return uniqueInstance;
    }
    private Singleton(){}
}

public class Singleton2{
    private static Singleton2 uniqueInstance = new Singleton2();
    public static Singleton2 getInstance()
    {        
        return uniqueInstance;
    }
    private Singleton2(){}
}

//哪个是懒汉式？

Singleton.getInstance();//用法