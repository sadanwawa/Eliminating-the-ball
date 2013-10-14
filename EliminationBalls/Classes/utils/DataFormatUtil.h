//
//  DataFormatUtil.h
//  GameWorld
//
//  Created by 英臣 马 on 12-8-16.

#ifndef GameWorld_DataFormatUtil_h
#define GameWorld_DataFormatUtil_h
//数据类型转换工具类
#include "Singleton.h"
#include <sstream>
#include <vector>
#include <assert.h>

#include "cocos2d.h"
#include "cocos-ext.h"

namespace DataFormatUtil {
    
    template <class T>
    std::string toString(T val) {
        std::ostringstream oss;
        oss << val;  
        return oss.str();
    }

    template <class T>
    T toNumber(const char* val){
        if(!val)
        {
            return 0;
        }
        std::istringstream b(val);
        T num;
        b >> num;    
        return num;
    }
    
    template <class T>
    void VectorAppend(std::vector<T>& dest, std::vector<T>& src, bool (*callback)(T val) = NULL){
        for (int i = 0 ; i<src.size(); ++i) {
            if(!callback)
                dest.push_back(src[i]);
            else if(callback(src[i])){
                dest.push_back(src[i]);
            }
        }        
    }
 
    template <class T>
    void VectorToArray(std::vector<T>& src, T* dest)
    {
        for(int i = 0;i < src.size();i++)
        {
            dest[i] = src[i];
        }        
    }

    bool toBool(const char* str);
    
    void splitToSVector(std::string str, std::vector<std::string>& dest, const char* pattern);
    void splitToIVector(std::string str, std::vector<int>& dest, const char* pattern);
    void splitToFVector(std::string str, std::vector<float>& dest, const char* pattern);
    //截取字符串的第个字符
    std::string getCharAtIndex(std::string content,int index);    
    //截取字符串的前个字符
    std::string getCharBeforeIndex(std::string content,int index);
    //取得字符串长度
    int getStringLength(std::string content);
    //字符串转化为单字符数组
    std::vector<std::string> getStringVec(std::string content);
    //解析字符串
    void addCharToVec(std::vector<std::string> &vec,std::string content,int currIndex);
    //去除字符串中的空格
    void strSpaceTrim(char* str);
    
    std::string replaceString(std::string str, char* startChar, char* endChar, char* replaceChars);
    
    int getRandom(int total);  
    
}


#endif
