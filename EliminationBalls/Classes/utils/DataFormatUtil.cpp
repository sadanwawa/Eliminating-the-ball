//
//  DataFormatUtil.cpp
//  GameWorld
//
//  Created by 英臣 马 on 12-8-16.


#include <iostream>
#include "DataFormatUtil.h"
#include "string.h"
#include <cstdlib>

namespace DataFormatUtil{
    
    bool toBool(const char* str)
    {
        bool flag;
        if (strcmp("true", str) == 0) {
            flag =  true;
        }else if(strcmp("false", str) == 0){
            flag = false;
        }
        
        return flag;
    }
      
    //字符串分割函数
    void splitToSVector(std::string str, std::vector<std::string>& dest, const char* pttn)
    {
        if(str.size() == 0) return;
        
        std::string pattern = pttn;

        std::string::size_type pos;
        str+=pattern;//扩展字符串以方便操作
        int size=str.size();
        
        for(int i=0; i<size; i++)
        {
            pos=str.find(pattern,i);
            if(pos<size)
            {
                std::string s=str.substr(i,pos-i);
                dest.push_back(s);
                i=pos+pattern.size()-1;
            }
        }
    }
    
    //字符串分割并转为int;
    void splitToIVector(std::string str, std::vector<int>& dest, const char* pttn)
    {
        if(str.size() == 0) return;
        
        std::string pattern = pttn;

        std::string::size_type pos;
        str+=pattern;//扩展字符串以方便操作
        int size=str.size();
        
        for(int i=0; i<size; i++)
        {
            pos=str.find(pattern,i);
            if(pos<size)
            {
                std::string s=str.substr(i,pos-i);            
                int num = std::atoi(s.c_str());                        
                dest.push_back(num);
                i=pos+pattern.size()-1;
            }
        }
    }
    
    void splitToFVector(std::string str, std::vector<float>& dest, const char* pttn)
    {
        if(str.size() == 0) return;
        
        std::string pattern = pttn;
        
        std::string::size_type pos;
        str+=pattern;//扩展字符串以方便操作
        int size=str.size();
        
        for(int i=0; i<size; i++)
        {
            pos=str.find(pattern,i);
            if(pos<size)
            {
                std::string s=str.substr(i,pos-i);            
                float num =toNumber<float>(s.c_str());                     
                dest.push_back(num);
                i=pos+pattern.size()-1;
            }
        }       
    }
    
 
    //截取字符串的第index个字符
    std::string getCharAtIndex(std::string content,int index){
        int currIndex=0;
        std::vector<std::string> vec;
        addCharToVec(vec,content,currIndex);
        return (vec)[index];
    }    
    
   //解析字符串
   void addCharToVec(std::vector<std::string> &vec,std::string content,int currIndex){
       const char* cont=content.c_str();
       char tmp[5] = "";
       if(cont[currIndex] & 0x80)
       {
           memcpy(tmp, &cont[currIndex], 3);
           currIndex += 3;
           tmp[3]='\0';
       }
       else
       {
           memcpy(tmp, &cont[currIndex], 1);
           currIndex += 1;
           tmp[1]='\0';
       }
       vec.push_back((std::string)tmp);
       int len=content.length();
       if(len>currIndex){
           addCharToVec(vec,content,currIndex);
       }      
    }    
    
    //截取字符串的前index个字符
    std::string getCharBeforeIndex(std::string content,int index){
        std::string targetStr="";
        int currIndex=0;
        std::vector<std::string> vec;
        addCharToVec(vec,content,currIndex);
        
        for(int i=0;i<index;i++){
            targetStr+=(vec)[i];
        }        
        return targetStr;       
    }
    
    int getStringLength(std::string content){
        int currIndex=0;
        std::vector<std::string> vec;
        addCharToVec(vec,content,currIndex);
        return vec.size();
    }
    
    std::vector<std::string> getStringVec(std::string content){        
        int currIndex=0;
        std::vector<std::string> vec;
        addCharToVec(vec,content,currIndex);
        return vec;
    }
    
    void strSpaceTrim(char* str)
    {
        char toks[2] = " ";
        char * tok = strtok( str, toks );
        while( tok )
        {
            if( tok == str )
                strcpy( str, tok );
            else
                strcat( str, tok );
            tok = strtok( NULL, toks );
        }
    }
    
    std::string replaceString(std::string str, char* startChar, char* endChar, char* replaceChars)
    {
        if(!startChar || !endChar || !replaceChars)
            return "";
        
        std::string formatStr = str;
        std::vector<std::string> strVec;
        
        int startIndex = formatStr.find(startChar, 0);
        int endIndex = formatStr.find(endChar, 0);
        while(startIndex != -1 && endIndex != -1)
        {
            std::string subStr = formatStr.substr(0, startIndex);
            strVec.push_back(subStr);
            
            formatStr = formatStr.substr(endIndex+1);
            startIndex = formatStr.find(startChar, 0);
            endIndex = formatStr.find(endChar, 0);
        }
        
        strVec.push_back(formatStr);
        
        std::string rStr = "";
        int len = strVec.size();
        for(int i = 0;i < len;i++)
        {
            rStr += strVec[i];
            if(i != len - 1)
                rStr += replaceChars;
        }
                
        return rStr;
    }
    
}
