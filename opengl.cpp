#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <node.h>
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

void GladLoad(const FunctionCallbackInfo<Value> &args) {
    Isolate* isolate = args.GetIsolate();
	v8::MaybeLocal<Boolean> i = Boolean::New(isolate, gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));
	v8::Local<Boolean> checkedI = i.ToLocalChecked();
	v8::ReturnValue<v8::Value> retVal = args.GetReturnValue();
	retVal.Set(checkedI);
}

void GlClearColor(const FunctionCallbackInfo<Value> &args) {
    Isolate* isolate = args.GetIsolate();

    glClearColor(args[0].As<Number>()->Value(), args[1].As<Number>()->Value(), args[2].As<Number>()->Value(), args[3].As<Number>()->Value());
}

void GlClear(const FunctionCallbackInfo<Value> &args) {
    Isolate* isolate = args.GetIsolate();

    glClear(args[0].As<Number>()->Value());
}

#pragma region vbo

void GlCreateBuffer(const FunctionCallbackInfo<Value> &args) {
    Isolate* isolate = args.GetIsolate();

    unsigned int vbo;

    glGenBuffers(1, &vbo);

    v8::MaybeLocal<Number> i = Number::New(isolate, vbo);
	v8::Local<Number> checkedI = i.ToLocalChecked();
	v8::ReturnValue<v8::Value> retVal = args.GetReturnValue();
	retVal.Set(checkedI);
}

void GlBufferData(const FunctionCallbackInfo<Value> &args) {
    Isolate* isolate = args.GetIsolate();

    unsigned int vbo = args[0].As<Number>()->Value();
    unsigned int size = args[2].As<Number>()->Value();

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, size, args[1].As<v8::Float32Array>()->Buffer()->Data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

#pragma endregion

#pragma region vao

void GlCreateVertexArray(const FunctionCallbackInfo<Value> &args) {
    Isolate* isolate = args.GetIsolate();

    unsigned int vao;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    v8::MaybeLocal<Number> i = Number::New(isolate, vao);
	v8::Local<Number> checkedI = i.ToLocalChecked();
	v8::ReturnValue<v8::Value> retVal = args.GetReturnValue();
	retVal.Set(checkedI);
}

void GlVertexAttribPointer(const FunctionCallbackInfo<Value> &args) {
    Isolate* isolate = args.GetIsolate();

    unsigned int vao = args[0].As<Number>()->Value();
    unsigned int vbo = args[1].As<Number>()->Value();
    unsigned int index = args[2].As<Number>()->Value();
    unsigned int size = args[3].As<Number>()->Value();
    unsigned int type = args[4].As<Number>()->Value();
    bool normalized = args[5].As<Boolean>()->Value();
    unsigned int stride = args[6].As<Number>()->Value();
    unsigned int ptr = args[7].As<Number>()->Value();

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glVertexAttribPointer(stride, size, type, normalized, stride, (void*)ptr);

    glEnableVertexAttribArray(index);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

#pragma endregion

#pragma region shader

void GlCreateShader(const FunctionCallbackInfo<Value> &args) {
    Isolate* isolate = args.GetIsolate();

    char* source = new char[512];
	args[0].As<String>()->WriteUtf8(isolate, source);
    unsigned int type = args[1].As<Number>()->Value();

    unsigned int shader;
    shader = glCreateShader(type);

    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    v8::MaybeLocal<Number> i = Number::New(isolate, shader);
	v8::Local<Number> checkedI = i.ToLocalChecked();
	v8::ReturnValue<v8::Value> retVal = args.GetReturnValue();
	retVal.Set(checkedI);
}

void GlCreateProgram(const FunctionCallbackInfo<Value> &args) {
    Isolate* isolate = args.GetIsolate();

    unsigned int vertexShader = args[0].As<Number>()->Value();
    unsigned int fragmentShader = args[0].As<Number>()->Value();

    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    int  success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);

        std::cout << "ERROR::SHADERPROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    }

    v8::MaybeLocal<Number> i = Number::New(isolate, program);
	v8::Local<Number> checkedI = i.ToLocalChecked();
	v8::ReturnValue<v8::Value> retVal = args.GetReturnValue();
	retVal.Set(checkedI);
}

#pragma endregion

#pragma region rendering

void GlDrawArrays(const FunctionCallbackInfo<Value> &args) {
    unsigned int type = args[0].As<Number>()->Value();
    unsigned int start = args[1].As<Number>()->Value();
    unsigned int end = args[1].As<Number>()->Value();

    glDrawArrays(type, 0, 3);
}

void GlUseProgram(const FunctionCallbackInfo<Value> &args) {
    unsigned int program = args[0].As<Number>()->Value();

    glUseProgram(program);
}

void GlBindVertexArray(const FunctionCallbackInfo<Value> &args) {
    unsigned int vao = args[0].As<Number>()->Value();

    glBindVertexArray(vao);
}

#pragma endregion

void Initialize(Local<Object> exports)
{
    Isolate* isolate = exports->GetIsolate();

	NODE_SET_METHOD(exports, "load", GladLoad);
	NODE_SET_METHOD(exports, "clearColor", GlClearColor);
	NODE_SET_METHOD(exports, "clear", GlClear);

	NODE_SET_METHOD(exports, "createBuffer", GlCreateBuffer);
	NODE_SET_METHOD(exports, "bufferData", GlBufferData);

	NODE_SET_METHOD(exports, "createVertexArray", GlCreateVertexArray);
	NODE_SET_METHOD(exports, "vertexAttribPointer", GlVertexAttribPointer);

	NODE_SET_METHOD(exports, "createShader", GlCreateShader);
	NODE_SET_METHOD(exports, "createProgram", GlCreateProgram);

	NODE_SET_METHOD(exports, "drawArrays", GlDrawArrays);
	NODE_SET_METHOD(exports, "useProgram", GlUseProgram);
	NODE_SET_METHOD(exports, "bindVertexArray", GlBindVertexArray);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)