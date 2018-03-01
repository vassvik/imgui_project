#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include <glad/glad.h>
#include <glad/glad.c>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include "imgui_impl_glfw_gl4.h"

GLFWwindow *window;
ImGuiIO &io = ImGui::GetIO();

ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
bool show_demo_window = true;
bool show_another_window = false;

void draw_gui() {
    // 1. Show a simple window.
    // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets automatically appears in a window called "Debug".
    {
        static float f = 0.0f;
        ImGui::Text("Hello, world!");                           // Some text (you can use a format string too)
        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float as a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats as a color
        if (ImGui::Button("Demo Window"))                       // Use buttons to toggle our bools. We could use Checkbox() as well.
            show_demo_window ^= 1;
        if (ImGui::Button("Another Window")) 
            show_another_window ^= 1;
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }

    // 2. Show another simple window. In most cases you will use an explicit Begin/End pair to name the window.
    if (show_another_window)
    {
        ImGui::Begin("Another Window", &show_another_window);
        ImGui::Text("Hello from another window!");
        ImGui::End();
    }

    // 3. Show the ImGui demo window. Most of the sample code is in ImGui::ShowDemoWindow().
    if (show_demo_window)
    {
        ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver); // Normally user code doesn't need/want to call this because positions are saved in .ini file anyway. Here we just want to make the demo initial state a bit more friendly!
        ImGui::ShowDemoWindow(&show_demo_window);
    }
}

int main() {
    // Setup GLFW
    glfwSetErrorCallback([](int error, const char* description){ fprintf(stderr, "Error %d: %s\n", error, description); });

    if (!glfwInit()) {
        return 1;
    }

    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(1280, 720, "JangaFX VectorayGen Version 1.02.5", NULL, NULL);
    if (window == NULL) {
        glfwTerminate();
        return 2;
    }
     
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // load opengl
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Could not load Opengl functions");
        return 3;
    }

    ImGui_ImplGlfwGL4_Init(window, true);
    io.Fonts->AddFontFromFileTTF("extra/Roboto-Medium.ttf", 16.0f);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplGlfwGL4_NewFrame();

        draw_gui();   

        // Rendering
        int display_w, display_h;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui::Render();
        glfwSwapBuffers(window);
    } 

    glfwTerminate();

    return 0;
}
