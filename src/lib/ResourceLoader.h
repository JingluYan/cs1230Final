#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H

#include <exception>
#include <string>
#include <QGLShaderProgram>

//#include "GL/glew.h"

namespace CS123 {

class IOException : public std::exception {
public:
    IOException(const std::string &what) : message(what) {}
    virtual ~IOException() throw() {}
    virtual const char* what() const throw() override { return message.c_str(); }

private:
    std::string message;
};

}

namespace ResourceLoader
{
    std::string loadResourceFileToString(const std::string &resourcePath);

//    static void initializeGlew();

    // These return a new QGLShaderProgram.  THIS MUST BE DELETED BY THE CALLER.
    QGLShaderProgram * newVertShaderProgram(const QGLContext *context, QString vertShader);
    QGLShaderProgram * newFragShaderProgram(const QGLContext *context, QString fragShader);
    QGLShaderProgram * newShaderProgram(const QGLContext *context, QString vertShader, QString fragShader, QString *errors = 0);
};

#endif // RESOURCELOADER_H
