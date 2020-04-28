//
// Created by engineer on 2020/4/28.
//

#include "MyTools.h"
USING_NS_CC;
void alert(std::initializer_list<const char*> list){
    JniMethodInfo methodInfo;
    if(JniHelper::getStaticMethodInfo(methodInfo,"com.xiuye.app.util.UIUtil","log","([Ljava/lang/Object;)V")){
        JniHelper::callStaticVoidMethod(methodInfo,list);
    }
}