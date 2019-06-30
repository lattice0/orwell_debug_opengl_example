#include "OpenGlVideoQtQuick2.h"

#define GET_STR(x) #x
#define A_VER 3
#define T_VER 4

//Simple shader. Outpus the same location as input, I guess
const char *vString4 = GET_STR(
    attribute vec4 vertexIn;
    attribute vec2 textureIn;
    varying vec2 textureOut;
    uniform mat4 u_transform;   
    void main(void)
    {
        gl_Position = u_transform * vertexIn;
        textureOut = textureIn;
    }
);


//The matrix below does YUV420P to RGB conversion https://en.wikipedia.org/wiki/YUV#Y%E2%80%B2UV420p_(and_Y%E2%80%B2V12_or_YV12)_to_RGB888_conversion
//This texture shader replaces the color of the pixel with the new color, but in RGB. (I guess)
const char *tString4 = GET_STR(
    varying vec2 textureOut;
    uniform sampler2D tex_y;
    uniform sampler2D tex_u;
    uniform sampler2D tex_v;
    void main(void)
    {
        gl_FragColor = vec4(1.0,0,0, 1.0);
    }

);

OpenGlVideoQtQuick2::OpenGlVideoQtQuick2()
    : openGlVideoQtQuick2Renderer2(nullptr)
{
    connect(this, &QQuickItem::windowChanged, this, &OpenGlVideoQtQuick2::handleWindowChanged);
}

OpenGlVideoQtQuick2::OpenGlVideoQtQuick2(std::string uri):
    openGlVideoQtQuick2Renderer2(nullptr) {
        this->uri = uri;
        connect(this, &QQuickItem::windowChanged, this, &OpenGlVideoQtQuick2::handleWindowChanged);
    }

void OpenGlVideoQtQuick2::update()
{
    if (window())
        window()->update();
}

void OpenGlVideoQtQuick2::handleWindowChanged(QQuickWindow *win)
{
    if (win) {
        connect(win, &QQuickWindow::beforeSynchronizing, this, &OpenGlVideoQtQuick2::sync, Qt::DirectConnection);
        win->setClearBeforeRendering(false);
    }
}

void OpenGlVideoQtQuick2::cleanup()
{
   if (openGlVideoQtQuick2Renderer2) {
        delete openGlVideoQtQuick2Renderer2;
        openGlVideoQtQuick2Renderer2 = nullptr;
    }
}

OpenGlVideoQtQuick2Renderer2::~OpenGlVideoQtQuick2Renderer2()
{
    delete program;
}

void OpenGlVideoQtQuick2::sync()
{

    if (!openGlVideoQtQuick2Renderer2) {
        openGlVideoQtQuick2Renderer2 = new OpenGlVideoQtQuick2Renderer2();
        connect(window(), &QQuickWindow::beforeRendering, openGlVideoQtQuick2Renderer2, &OpenGlVideoQtQuick2Renderer2::render, Qt::DirectConnection);

        connect(window(), &QQuickWindow::afterRendering, this, &OpenGlVideoQtQuick2::update, Qt::DirectConnection);
        openGlVideoQtQuick2Renderer2->setDimensions(x(),y(),width(),height());
        openGlVideoQtQuick2Renderer2->setViewportSize(this->size().toSize() * window()->devicePixelRatio());
        openGlVideoQtQuick2Renderer2->setWindow(window());
        openGlVideoQtQuick2Renderer2->setPosition(this->position().toPoint());
    }
}

void OpenGlVideoQtQuick2Renderer2::updateData(unsigned char**data, int frameWidth, int frameHeight)
{

    this->frameWidth = frameWidth;
    this->frameHeight = frameHeight;
    //Before first render, datas pointer isn't even created yet
    if (!firstRender) {
        memcpy(datas[0], data[0], frameWidth*frameHeight);
        memcpy(datas[1], data[1], frameWidth*frameHeight/4);
        memcpy(datas[2], data[2], frameWidth*frameHeight/4);
    }
}

static const GLfloat ver[] = {
    -1.0f,-1.0f,
     1.0f,-1.0f,
    -1.0f, 1.0f,
     1.0f, 1.0f
};

static const GLfloat tex[] = {
    0.0f, 1.0f,
    1.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f
};

void OpenGlVideoQtQuick2Renderer2::render()
{
    frameWidth = 1280;
    frameHeight = 720;
    if (this->firstRender) {
        std::cout << "Creating QOpenGLShaderProgram " << std::endl;
        program = new QOpenGLShaderProgram();
        initializeOpenGLFunctions();
        //this->m_F  = QOpenGLContext::currentContext()->functions();
        std::cout << "frameWidth: " << frameWidth << + " frameHeight: " << frameHeight << std::endl;
        datas[0] = new unsigned char[frameWidth*frameHeight];	//Y
        datas[1] = new unsigned char[frameWidth*frameHeight/4];	//U
        datas[2] = new unsigned char[frameWidth*frameHeight/4];	//V

        std::cout << "Fragment Shader compilation: " << program->addShaderFromSourceCode(QOpenGLShader::Fragment, tString4) << std::endl;
        std::cout << "Vertex Shader compilation: " << program->addShaderFromSourceCode(QOpenGLShader::Vertex, vString4) << std::endl;

        program->bindAttributeLocation("vertexIn",A_VER);
        program->bindAttributeLocation("textureIn",T_VER);
        std::cout << "program->link() = " << program->link() << std::endl;

        glGenTextures(3, texs);//TODO: ERASE THIS WITH glDeleteTextures
        this->firstRender = false;
        
    }
    program->bind();
    int y = (m_window->size()* m_window->devicePixelRatio()).height() - m_viewportSize.height() -  m_position.y();
    glViewport(m_position.x(), y, m_viewportSize.width(), m_viewportSize.height());

    QMatrix4x4 transform;
    transform.setToIdentity();
 
    program->setUniformValue("u_transform", this->qQuickVideoMatrix);

    glVertexAttribPointer(A_VER, 2, GL_FLOAT, 0, 0, ver);
    glEnableVertexAttribArray(A_VER);

    glVertexAttribPointer(T_VER, 2, GL_FLOAT, 0, 0, tex);
    glEnableVertexAttribArray(T_VER);

    unis[0] = program->uniformLocation("tex_y");
    unis[1] = program->uniformLocation("tex_u");
    unis[2] = program->uniformLocation("tex_v");
    
    //Y
    glBindTexture(GL_TEXTURE_2D, texs[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, frameWidth, frameHeight, 0, GL_RED, GL_UNSIGNED_BYTE, 0);

    //U
    glBindTexture(GL_TEXTURE_2D, texs[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, frameWidth/2, frameHeight / 2, 0, GL_RED, GL_UNSIGNED_BYTE, 0);

    //V
    glBindTexture(GL_TEXTURE_2D, texs[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, frameWidth / 2, frameHeight / 2, 0, GL_RED, GL_UNSIGNED_BYTE, 0);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texs[0]);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, frameWidth, frameHeight, GL_RED, GL_UNSIGNED_BYTE, datas[0]);
    glUniform1i(unis[0], 0);


    glActiveTexture(GL_TEXTURE0+1);
    glBindTexture(GL_TEXTURE_2D, texs[1]); 
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, frameWidth/2, frameHeight / 2, GL_RED, GL_UNSIGNED_BYTE, datas[1]);
    glUniform1i(unis[1],1);


    glActiveTexture(GL_TEXTURE0+2);
    glBindTexture(GL_TEXTURE_2D, texs[2]);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, frameWidth / 2, frameHeight / 2, GL_RED, GL_UNSIGNED_BYTE, datas[2]);
    glUniform1i(unis[2], 2);
    
    glDrawArrays(GL_TRIANGLE_STRIP,0,4);

    program->disableAttributeArray(A_VER);
    program->disableAttributeArray(T_VER);
    program->release();
}
