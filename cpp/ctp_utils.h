#ifndef CTP_UTILS_H_
#define CTP_UTILS_H_

#include <node.h>
#include <iostream>
#include <cstring>
#include <sstream>
#include <string>

using namespace v8;

extern bool islog;
extern void logger_cout(const char *content);
extern std::string to_string(int val);
extern std::string charto_string(char val);

extern void setInt(Local<Object> obj, Local<String> localKey, int* value);
extern void setDouble(Local<Object> obj, Local<String> localKey, double* value);
extern void setChar(Local<Object> obj, Local<String> localKey, char* value);
extern void setString(Local<Object> obj, Local<String> localKey, char* value);

#endif
