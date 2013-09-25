//
//  Singleton.h
//  GameWorld
//
//  Created by yingchen ma on 13-8-14.
//  Copyright (c) 2013年 RenRenGame. All rights reserved.
//  单例

#ifndef GameWorld_Singleton_h
#define GameWorld_Singleton_h

#include <stddef.h>

template <class T>
//inline 内敛函数  取代表达式宏定义  效率高  多用与存取函数
class Singleton{
public:
    static inline T* Instance(){
        if(!msSingleton){
            msSingleton = new T;            
        }
        return msSingleton;        
    }
    
    static void release(){
        if(!msSingleton){
            delete msSingleton;
            msSingleton=NULL;
        }         
    }
protected:
    Singleton(){}
    virtual ~Singleton(){
    }  //虚函数 覆盖 
    
private:
    
    static T* msSingleton;   
    
};

#endif
