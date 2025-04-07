#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include"shader.h"
#include<cmath>
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include"camera.h"

#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"

#define ASSERT(x) if(!(x)) __debugbreak();

#define GLErrorCall(x) GLClearError();\
    x;\
    ASSERT(GLErrorLogCall(#x,__FILE__,__LINE__))

static void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

void loadImg(const char* imgName) {
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(imgName, &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "[Main ERROR]: Fail to read image!" << std::endl;
    }
    // �ͷ�ͼ���ڴ�
    stbi_image_free(data);

}

static bool GLErrorLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL ERROR]:(" << error << ") " << function << " " << file << ": " << line << "!!\n";
        return false;
    }
    return true;
}

// ��Ļ
unsigned int Screenheight = 600;
unsigned int Screenwidth = 800;

float deltaTime = 0.0f;

bool firstMouse = true;

float lastX = Screenwidth / 2.0f;
float lastY = Screenheight / 2.0f;

// �����
Camera camera(glm::vec3(0.0f,0.0f,3.0f));


void ProcessInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.Key_MouseMovement(deltaTime, FORWARD);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.Key_MouseMovement(deltaTime, BACKWARD);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.Key_MouseMovement(deltaTime, LEFT);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.Key_MouseMovement(deltaTime, RIGHT);
    }

}

void MouseCallback(GLFWwindow* window, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    
    //��Ҫ�����һ�ε���Ӵ�
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    camera.MouseMovement(xoffset, yoffset);
}
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.MouseScroll(yoffset);
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */


    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cout << "Error Init";
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    // ����ص�����
    glfwSetCursorPosCallback(window,MouseCallback);
    glfwSetScrollCallback(window,ScrollCallback);
    // ��׽���
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    /*
    float vertices[] = {
        //---loc---            ---color---    ---����---
        1.0f,1.0f,0.0f,     1.0f,1.0f,1.0f,   1.0f,1.0f,  //����
        1.0f,-1.0f,0.0f,    0.0f,1.0f,0.0f,   1.0f,0.0f,  //����
        -1.0f,-1.0f,0.0f,   1.0f,0.0f,0.0f,   0.0f,0.0f,  //����
        -1.0f,1.0f,0.0f,    0.0f,0.0f,1.0f,   0.0f,1.0f   //����
    };
    */
    float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    float vertices_Triangle[] = {
        -0.5f,-0.5f,0.0f,  //����
        0.5f,-0.5f,0.0f,  //����
        0.0f,0.5f,0.0f //��
    };

    unsigned int indices[] = {
        0,1,2,
        2,3,0
    };
    // ������Ȳ���
    glEnable(GL_DEPTH_TEST);

   //  glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
   //  glm::mat4 trans = glm::mat4(1.0f);
   //  trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
   //  //ָ����������ת����
   //  trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));

    unsigned int VBOs[2], VAOs[2];  // ��������ID
    unsigned int EBO;
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs); //����Vertex Buffer Objects

    // ���Ƶ�һ������
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]); // ��
    //glGenBuffers(1, &EBO);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //�������ݵ�������
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
    glEnableVertexAttribArray(0);
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(3*sizeof(float)));
    //glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);// ����ʡ��

    //����������
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]); // ��
    //�������ݵ�������
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_Triangle), vertices_Triangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
    glEnableVertexAttribArray(0);
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(1);
    glBindVertexArray(0);// ����ʡ��

    // ����
    unsigned int texture[2];
    glGenTextures(2, texture);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    // ��䷽ʽ
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // �Ŵ���С��ʽ
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // ��������
    loadImg("spica.jpg");

    float borderColor[] = { 0.4f,1.0f,0.0f,1.0f };
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    // ��䷽ʽ
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //GLErrorCall(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);)
    // �Ŵ���С��ʽ
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // ��������
    loadImg("map.jpg");



    

    // ������ɫ��
    Shader shader("shader.vs", "shader.fs");
    Shader shader2("shader2.vs", "shader2.fs");

 
    int max_attributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &max_attributes);
    std::cout << "Maximum attributes: " << max_attributes << std::endl;

     


    /* Loop until the user closes the window */
    float last_timeValue = 0;
    while (!glfwWindowShouldClose(window))
    {
        //������Esc���˳�
        ProcessInput(window);

        //����֡ʱ��
        float currantTime = glfwGetTime();
        deltaTime = currantTime - last_timeValue;
        last_timeValue = currantTime;


        /* Render here */
        glClear(GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 0.8f);  // ���ñ�����ɫ
        glClear(GL_COLOR_BUFFER_BIT);

        // ���ƾ���
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        shader2.use();
        shader2.setInt("texture1", 0);
        shader2.setInt("texture2", 1);
        //glUniform1i(glGetUniformLocation(shader2.ID,"ourTex"),0);
        glBindVertexArray(VAOs[0]);

        // ����
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 1.0f));

        //3D
        //Step1 �任����������ϵ��ģ�;��󣬰�������λ�ƺ���ת
        //glm::mat4 model = glm::mat4(1.0f);
        //model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 1.0f));
       
        //Step2 �۲�ռ� �Ӳ����
        glm::mat4 view = glm::mat4(1.0f);
        float CamX = sin(glfwGetTime()) * 10.0f;
        float CamZ = cos(glfwGetTime()) * 10.0f;

        //view = glm::lookAt(CamPos, CamPos+CamFront, CamUp);
        view = camera.CreateView_M();
        // lookAt�ڲ�����CreamerPos�����λ�ã�,Target��Ŀ��λ�ã����ǿ������,UpVertex��ָ��һ������������������������
        //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        // 
        //Step3 �ü����� ͶӰ����
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(camera.m_fov), (float)Screenwidth / (float)Screenheight, 0.1f, 100.0f);
         
        //Step4 ��Ļ���� �Զ�
        // ������ɫ������
        //unsigned int modelLoc = glGetUniformLocation(shader2.ID, "model");
        //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        unsigned int viewLoc = glGetUniformLocation(shader2.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        unsigned int projectionLoc = glGetUniformLocation(shader2.ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));



        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
        // ʵ��˳��������ת��ƽ��
        unsigned int transformLoc = glGetUniformLocation(shader2.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));


        glActiveTexture(GL_TEXTURE0); // ��������Ԫ
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture[1]);


        //model = glm::translate(model, glm::vec3(1.0f, 1.0f, 1.0f));
        for (unsigned int i = 0; i < 3; ++i) {
           // model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
            //std::cout << cos(i * 10) << ' ' << sin(i * 10) << std::endl;
            glm::mat4 model = glm::mat4(1.0f);

            model = glm::translate(model, glm::vec3(cos(i), sin(i), sin(cos(i)+0.5f)));
           // model = glm::rotate(model, glm::radians((float)i * 10) * (float)glfwGetTime(), glm::vec3(1.0f, 0.5f, 0.4f));

            unsigned int modelLoc = glGetUniformLocation(shader2.ID, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        //GLErrorCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);)
        //glDrawArrays(GL_TRIANGLES, 0, 36);

        // ����������
        // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        shader.use();
        glBindVertexArray(VAOs[1]);
        double timeValue = glfwGetTime();
        float rValue = (sin(timeValue) + 1.0f) / 2.0f;
        float gValue = 1.0f - (cos(timeValue) + 1.0f) / 2.0f;
        int sgnValue = (cos(timeValue) * cos(last_timeValue)) < 0 ? 1 : -1;
        int vertexLocation = glGetUniformLocation(shader.ID, "m_Pos_sgn");
        
        glUniform3i(vertexLocation, sgnValue, sgnValue, sgnValue);
        int vertexColorLocation = glGetUniformLocation(shader.ID, "m_Color");
        glUniform4f(vertexColorLocation, rValue, gValue, 0.0f, 0.3f);
       // glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    shader.Delete();
    shader2.Delete();
    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    glfwTerminate();
    return 0;
}