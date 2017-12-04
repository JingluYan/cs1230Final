/**
 * @file   CamtransCamera.cpp
 *
 * This is the perspective camera class you will need to fill in for the Camtrans lab.  See the
 * lab handout for more details.
 */

#include "CamtransCamera.h"
#include <Settings.h>
#include <math.h>

CamtransCamera::CamtransCamera() :
    heightAngle(60),
    aspectRatio(1),
    near(1),
    far(30)
{
    // @TODO: [CAMTRANS] Fill this in...
    orientLook(
                glm::vec4(2.f, 2.f, 2.f, 1.f),
                glm::vec4(-2.f, -2.f, -2.f, 0.f),
                glm::vec4(0.f, 1.f, 0.f, 0.f)
                );
}

void CamtransCamera::setAspectRatio(float a)
{
    // @TODO: [CAMTRANS] Fill this in...
    aspectRatio = a;
    updateProjection();
}

glm::mat4x4 CamtransCamera::getProjectionMatrix() const {
    // @TODO: [CAMTRANS] Fill this in...
    return projection;
}

glm::mat4x4 CamtransCamera::getViewMatrix() const {
    // @TODO: [CAMTRANS] Fill this in...
    return view;
}

glm::mat4x4 CamtransCamera::getScaleMatrix() const {
    // @TODO: [CAMTRANS] Fill this in...
    float tanThetaH = std::tan(heightAngle / 2.f * M_PI / 180.f);
    float tanThetaW = tanThetaH * aspectRatio;
    glm::mat4 scaleMat = glm::transpose(
                glm::mat4x4(
                    1.f / (far*tanThetaW), 0, 0, 0,
                    0, 1.f / (far * tanThetaH), 0, 0,
                    0, 0, (1.f / far),0,
                    0, 0, 0, 1
                    )
                );
    return scaleMat;
}

glm::mat4x4 CamtransCamera::getPerspectiveMatrix() const {
    // @TODO: [CAMTRANS] Fill this in...
    return glm::mat4x4();
}

glm::vec4 CamtransCamera::getPosition() const {
    // @TODO: [CAMTRANS] Fill this in...
    return E;
}

glm::vec4 CamtransCamera::getLook() const {
    // @TODO: [CAMTRANS] Fill this in...
    return -w;
}

glm::vec4 CamtransCamera::getUp() const {
    // @TODO: [CAMTRANS] Fill this in...
    return v;
}

float CamtransCamera::getAspectRatio() const {
    // @TODO: [CAMTRANS] Fill this in...
    return aspectRatio;
}

float CamtransCamera::getHeightAngle() const {
    // @TODO: [CAMTRANS] Fill this in...
    return heightAngle;
}

void CamtransCamera::orientLook(const glm::vec4 &eye, const glm::vec4 &look, const glm::vec4 &up) {
    // @TODO: [CAMTRANS] Fill this in...
    E = eye;
    w = -glm::normalize(look);
    v = glm::normalize(up - w * glm::dot(up, w));
    u = glm::normalize(glm::vec4(glm::cross(glm::vec3(v.x, v.y, v.z), glm::vec3(w.x, w.y, w.z)), 0.f));
    updateView();
    updateProjection();
}

void CamtransCamera::setHeightAngle(float h) {
    // @TODO: [CAMTRANS] Fill this in...
    heightAngle = h;
    updateProjection();
}

void CamtransCamera::translate(const glm::vec4 &v) {
    // @TODO: [CAMTRANS] Fill this in...
    E += v;
    updateView();
}

void CamtransCamera::rotateU(float degrees) {
    // @TODO: [CAMTRANS] Fill this in...
//    float sin = std::sin(degrees * M_PI / 180.f);
//    float cos = std::cos(degrees * M_PI / 180.f);
    float sin = std::sin(glm::radians(degrees));
    float cos = std::cos(glm::radians(degrees));
    glm::vec4 v2 = v * cos + w * sin;
    glm::vec4 w2 = -v * sin + w * cos;
    v = v2;
    w = w2;
    updateView();
}

void CamtransCamera::rotateV(float degrees) {
    // @TODO: [CAMTRANS] Fill this in...
    float sin = std::sin(glm::radians(degrees));
    float cos = std::cos(glm::radians(degrees));
    glm::vec4 u2 = u * cos - w * sin;
    glm::vec4 w2 = u * sin + w * cos;
    u = u2;
    w = w2;
    updateView();
}

void CamtransCamera::rotateW(float degrees) {
    // @TODO: [CAMTRANS] Fill this in...
    float sin = std::sin(glm::radians(-degrees));
    float cos = std::cos(glm::radians(-degrees));
    glm::vec4 v2 = v * cos + u * sin;
    glm::vec4 u2 = -v * sin + u * cos;
    v = v2;
    u = u2;
    updateView();
}

void CamtransCamera::setClip(float nearPlane, float farPlane) {
    // @TODO: [CAMTRANS] Fill this in...
    near = nearPlane;
    far = farPlane;
    updateProjection();
}

void CamtransCamera::updateProjection() {
    float tanThetaH = std::tan(heightAngle / 2.f * M_PI / 180.f);
    float tanThetaW = tanThetaH * aspectRatio;
    float c = -near * (1.f / far);
    projection = glm::transpose(
                glm::mat4x4(
                    1.f / (far*tanThetaW), 0, 0, 0,
                    0, 1.f / (far * tanThetaH), 0, 0,
                    0, 0, -(1.f / far) / (c + 1.f), c / (c + 1.f),
                    0, 0, -(1.f / far), 0
                    )
                );
}

void CamtransCamera::updateView() {
    view = glm::transpose(
                glm::mat4x4 (
                    u[0], u[1], u[2], -glm::dot(E, u),
                    v[0], v[1], v[2], -glm::dot(E, v),
                    w[0], w[1], w[2], -glm::dot(E, w),
                    0, 0, 0, 1 )
                );
}

