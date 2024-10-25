{
    "targets": [
        {
            "target_name": "glfw",
            "sources": [ "glfw.cpp" ],
            "libraries": [ "/lib/x86_64-linux-gnu/libglfw.so" ]
        },
        {
            "target_name": "opengl",
            "sources": [ "opengl.cpp", "glad.c" ],
            "libraries": [ "/lib/x86_64-linux-gnu/libglfw.so" ],
            "include_dirs": [
                "."
            ]
        }
    ]
}