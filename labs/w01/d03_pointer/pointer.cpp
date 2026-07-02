#include<iostream>
#include<string>
#include<algorithm>

int ReturnLocalValue()
{
    int value = 42;
    return value;
}

//返回局部引用不安全，因为函数结束后局部对象已经销毁
int& BadLocalRerefence()
{
    int value = 42;
    return value;
}

//函数运行结束后指向的对象已经不存在
int* BadLocalPointer()
{
    int value = 42;
    return &value;
}

const char* BadString()
{
    std::string name = "robot";
    return name.c_str();
}

int main()
{
    ReturnLocalValue();
    BadLocalRerefence();
    BadString();
    std::cout<<"Done"<<std::endl;
    return 0;
}