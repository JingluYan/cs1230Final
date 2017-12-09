#include "ResourceLoader.h"
#include <QFile>
#include <QString>
#include <QTextStream>

std::string ResourceLoader::loadResourceFileToString(const std::string &resourcePath)
{
    QString vertFilePath = QString::fromStdString(resourcePath);
    QFile vertFile(vertFilePath);
    if (vertFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream vertStream(&vertFile);
        QString contents = vertStream.readAll();
        return contents.toStdString();
    }
    throw CS123::IOException("Could not open file: " + resourcePath);
}


//static void ResourceLoader::initializeGlew() {
//    glewExperimental = GL_TRUE;
//    GLenum err = glewInit();
//    if (GLEW_OK != err) fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
//    fprintf(stdout, "Using GLEW %s\n", glewGetString(GLEW_VERSION));
//}

QGLShaderProgram* ResourceLoader::newShaderProgram(const QGLContext *context, QString vertShader, QString fragShader, QString *errors) {
    QGLShaderProgram *program = new QGLShaderProgram(context);
    if (!program->addShaderFromSourceFile(QGLShader::Vertex, vertShader)) {
        if (errors) {
            *errors = program->log();
        }
        delete program;
        return NULL;
    }
    if (!program->addShaderFromSourceFile(QGLShader::Fragment, fragShader)) {
        if (errors) {
            *errors = program->log();
        }
        delete program;
        return NULL;
    }
    program->bindAttributeLocation("position", 0);
    program->bindAttributeLocation("normal", 1);
    program->bindAttributeLocation("texCoord", 2);
    if (!program->link()) {
        if (errors) {
            *errors = program->log();
        }
        delete program;
        return NULL;
    }
    return program;
}

QGLShaderProgram* ResourceLoader::newVertShaderProgram(const QGLContext *context, QString vertShader) {
    QGLShaderProgram *program = new QGLShaderProgram(context);
    program->addShaderFromSourceFile(QGLShader::Vertex, vertShader);
    program->link();
    return program;
}

QGLShaderProgram* ResourceLoader::newFragShaderProgram(const QGLContext *context, QString fragShader) {
    QGLShaderProgram *program = new QGLShaderProgram(context);
    program->addShaderFromSourceFile(QGLShader::Fragment, fragShader);
    program->link();
    return program;
}
