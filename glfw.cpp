// addon_src.cc
#include <node.h>
#include <GLFW/glfw3.h>
#include <iostream>

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::NewStringType;
using v8::Object;
using v8::String;
using v8::Number;
using v8::Boolean;
using v8::Value;

static GLFWwindow* currentWindow = nullptr;

void GlfwInit(const FunctionCallbackInfo<Value> &args)
{
	Isolate* isolate = args.GetIsolate();
	v8::MaybeLocal<Boolean> i = Boolean::New(isolate, glfwInit());
	v8::Local<Boolean> checkedI = i.ToLocalChecked();
	v8::ReturnValue<v8::Value> retVal = args.GetReturnValue();
	retVal.Set(checkedI);
}

void GlfwGetVersionMajor(const FunctionCallbackInfo<Value> &args)
{
	int major, minor, rev = 0;

	glfwGetVersion(&major, &minor, &rev);

	Isolate* isolate = args.GetIsolate();
	v8::MaybeLocal<Number> i = Number::New(isolate, major);
	v8::Local<Number> checkedI = i.ToLocalChecked();
	v8::ReturnValue<v8::Value> retVal = args.GetReturnValue();
	retVal.Set(checkedI);
}

void GlfwGetVersionMinor(const FunctionCallbackInfo<Value> &args)
{
	int major, minor, rev = 0;

	glfwGetVersion(&major, &minor, &rev);

	Isolate* isolate = args.GetIsolate();
	v8::MaybeLocal<Number> i = Number::New(isolate, minor);
	v8::Local<Number> checkedI = i.ToLocalChecked();
	v8::ReturnValue<v8::Value> retVal = args.GetReturnValue();
	retVal.Set(checkedI);
}

void GlfwGetVersionRev(const FunctionCallbackInfo<Value> &args)
{
	int major, minor, rev = 0;

	glfwGetVersion(&major, &minor, &rev);

	Isolate* isolate = args.GetIsolate();
	v8::MaybeLocal<Number> i = Number::New(isolate, rev);
	v8::Local<Number> checkedI = i.ToLocalChecked();
	v8::ReturnValue<v8::Value> retVal = args.GetReturnValue();
	retVal.Set(checkedI);
}

void GlfwWindowShouldClose(const FunctionCallbackInfo<Value> &args)
{
	Isolate* isolate = args.GetIsolate();
	v8::MaybeLocal<Boolean> i = Boolean::New(isolate, glfwWindowShouldClose(currentWindow));
	v8::Local<Boolean> checkedI = i.ToLocalChecked();
	v8::ReturnValue<v8::Value> retVal = args.GetReturnValue();
	retVal.Set(checkedI);
}

void GlfwPollEvents(const FunctionCallbackInfo<Value> &args)
{
	glfwPollEvents();
}

void GlfwSwapBuffers(const FunctionCallbackInfo<Value> &args)
{
	glfwSwapBuffers(currentWindow);
}


void GlfwCreateWindow(const FunctionCallbackInfo<Value> &args)
{
	Isolate* isolate = args.GetIsolate();

	char* title = new char[512];
	args[0].As<String>()->WriteUtf8(isolate, title);
	int width = args[1].As<Number>()->Value();
	int height = args[2].As<Number>()->Value();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

	currentWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);
}


void GlfwTerminate(const FunctionCallbackInfo<Value> &args)
{
	glfwTerminate();
}

void GlfwDestroyWindow(const FunctionCallbackInfo<Value> &args)
{
	glfwDestroyWindow(currentWindow);
}

void GlfwMakeContextCurrent(const FunctionCallbackInfo<Value> &args)
{
	glfwMakeContextCurrent(currentWindow);
}

void Initialize(Local<Object> exports)
{
	NODE_SET_METHOD(exports, "init", GlfwInit);
	NODE_SET_METHOD(exports, "terminate", GlfwTerminate);
	NODE_SET_METHOD(exports, "getVersionMajor", GlfwGetVersionMajor);
	NODE_SET_METHOD(exports, "getVersionMinor", GlfwGetVersionMinor);
	NODE_SET_METHOD(exports, "getVersionRev", GlfwGetVersionRev);
	NODE_SET_METHOD(exports, "createWindow", GlfwCreateWindow);
	NODE_SET_METHOD(exports, "windowShouldClose", GlfwWindowShouldClose);
	NODE_SET_METHOD(exports, "pollEvents", GlfwPollEvents);
	NODE_SET_METHOD(exports, "swapBuffers", GlfwSwapBuffers);
	NODE_SET_METHOD(exports, "destroyWindow", GlfwDestroyWindow);
	NODE_SET_METHOD(exports, "makeContextCurrent", GlfwMakeContextCurrent);

	
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)