#include "ctp_utils.h"

std::string to_string(int val){
  std::stringstream ss;
  ss << val;
  return ss.str();
}

std::string charto_string(char val){
  std::stringstream ss; 
  ss << val;
  return ss.str();
}

void logger_cout(const char *content) {
  if (islog) {
    std::cout << content << std::endl;
  }
};

void setInt(Local<Object> obj, Local<String> localKey, int* value) {
  if (!obj->Has(localKey)) return;
  Local<Value> localValue = obj->Get(localKey);
  *value = localValue->Int32Value();
};

void setDouble(Local<Object> obj, Local<String> localKey, double* value) {
  if (!obj->Has(localKey)) return;
  Local<Value> localValue = obj->Get(localKey);
  *value = localValue->NumberValue();
};

void setChar(Local<Object> obj, Local<String> localKey, char* value) {
  if (!obj->Has(localKey)) return;
  Local<Value> localValue = obj->Get(localKey);
  std::string val = *String::Utf8Value(localValue);
  *value = val[0];
};

void setString(Local<Object> obj, Local<String> localKey, char* value) {
  if (!obj->Has(localKey)) return;
  Local<Value> localValue = obj->Get(localKey);
  std::string val = *String::Utf8Value(localValue);
  strcpy(value, val.c_str());
};
