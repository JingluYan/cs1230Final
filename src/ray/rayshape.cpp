#include "rayshape.h"
#include <algorithm> //for std::min
#include <cmath>
#include "rayutils.h"

// // // // // // // // // // // // // // // // // // // // // // // // // //
// Rayshape

RayShape::RayShape():
    material(std::make_unique<CS123SceneMaterial>())
{
}

bool RayShape::solveT(double a, double b, double c, double &t) {
    double discriminant = std::pow(b, 2) - 4 * a * c;
    if (discriminant < 0) {
        return false;
    }
    t = (-b - std::sqrt(discriminant)) / (2.0 * a);
    return t > 0;
}


// // // // // // // // // // // // // // // // // // // // // // // // // //
//Cube

glm::vec3 RayCube::getNormal(glm::vec3 hit) {
    if (std::abs(hit.x - 0.5f) <= EPSILON) {
        return glm::vec3(1, 0, 0);
    }

    if (std::abs(hit.x + 0.5f) <= EPSILON) {
        return glm::vec3(-1, 0, 0);
    }

    if (std::abs(hit.y - 0.5f) <= EPSILON) {
        return glm::vec3(0, 1, 0);
    }

    if (std::abs(hit.y + 0.5f) <= EPSILON) {
        return glm::vec3(0, -1, 0);
    }

    if (std::abs(hit.z - 0.5f) <= EPSILON) {
        return glm::vec3(0, 0, 1);
    }

    if (std::abs(hit.z + 0.5f) <= EPSILON) {
        return glm::vec3(0, 0, -1);
    }

}

bool RayCube::intersect(const glm::vec3 eye, const glm::vec3 ray, double &t) {
    double px = static_cast<double>(eye.x);
    double py = static_cast<double>(eye.y);
    double pz = static_cast<double>(eye.z);

    double dx = static_cast<double>(ray.x);
    double dy = static_cast<double>(ray.y);
    double dz = static_cast<double>(ray.z);

    bool res = false;

    double t1 = (0.5f - px) / dx;
    if ( (py + t1*dy - 0.5f) <= EPSILON && (py + t1*dy + 0.5f) >= EPSILON
         && (pz + t1*dz - 0.5f) <= EPSILON && (pz + t1*dz + 0.5f) >= EPSILON) {
        t = std::min(t, t1);
        res = true;
    }

    double t2 = (-0.5f - px) / dx;
    if ( (py + t2*dy - 0.5f) <= EPSILON && (py + t2*dy + 0.5f) >= EPSILON
         && (pz + t2*dz - 0.5f) <= EPSILON && (pz + t2*dz + 0.5f) >= EPSILON) {
        t = std::min(t, t2);
        res = true;
    }

    double t3 = (0.5f - py) / dy;
    if ( (px + t3*dx - 0.5f) <= EPSILON && (px + t3*dx + 0.5f) >= EPSILON
         && (pz + t3*dz - 0.5f) <= EPSILON && (pz + t3*dz + 0.5f) >= EPSILON) {
        t = std::min(t, t3);
        res = true;
    }

    double t4 = (-0.5f - py) / dy;
    if ( (px + t4*dx - 0.5f) <= EPSILON && (px + t4*dx + 0.5f) >= EPSILON
         && (pz + t4*dz - 0.5f) <= EPSILON && (pz + t4*dz + 0.5f) >= EPSILON) {
        t = std::min(t, t4);
        res = true;
    }

    double t5 = (0.5f - pz) / dz;
    if ( (px + t5*dx - 0.5f) <= EPSILON && (px + t5*dx + 0.5f) >= EPSILON
         && (py + t5*dy - 0.5f) <= EPSILON && (py + t5*dy + 0.5f) >= EPSILON) {
        t = std::min(t, t5);
        res = true;
    }

    double t6 = (-0.5f - pz) / dz;
    if ( (px + t6*dx - 0.5f) <= EPSILON && (px + t6*dx + 0.5f) >= EPSILON
         && (py + t6*dy - 0.5f) <= EPSILON && (py + t6*dy + 0.5f) >= EPSILON) {
        t = std::min(t, t6);
        res = true;
    }
    return res;
}

glm::vec2 RayCube::getUV(glm::vec3 hit) {
    if (hit.x <= -.5f + EPSILON_F) return glm::vec2(hit.z + 0.5f, -hit.y + 0.5f);
    if (hit.x >= .5f - EPSILON_F) return glm::vec2(-hit.z + 0.5f, -hit.y + 0.5f);

    if (hit.y <= -.5f + EPSILON_F) return glm::vec2(hit.x + 0.5f, -hit.z + 0.5f);
    if (hit.y >= .5f - EPSILON_F) return glm::vec2(hit.x + 0.5f, hit.z + 0.5f);

    if (hit.z <= -.5f + EPSILON_F) return glm::vec2(-hit.x + 0.5f, -hit.y + 0.5f);
    if (hit.z >= .5f - EPSILON_F) return glm::vec2(hit.x + 0.5f, -hit.y + 0.5f);
}


// // // // // // // // // // // // // // // // // // // // // // // // // //
// Sphere

glm::vec3 RaySphere::getNormal(glm::vec3 hit) {
    return glm::normalize(hit);
//    return hit;
}

bool RaySphere::intersect(const glm::vec3 eye, const glm::vec3 ray, double &t) {
    double px = eye.x;
    double py = eye.y;
    double pz = eye.z;
    double dx = ray.x;
    double dy = ray.y;
    double dz = ray.z;
    double a = dx * dx + dy * dy + dz * dz;
    double b = 2 * (px * dx + py * dy + pz * dz);
    double c = (px * px + py * py + pz * pz - 0.25);

    return solveT(a, b, c, t);
}

glm::vec2 RaySphere::getUV(glm::vec3 hit) {
    float radius = std::sqrt(hit.x * hit.x + hit.y * hit.y + hit.z * hit.z);
    float theta = atan2(hit.z, hit.x);
    float u = 0.f;
    if (theta < 0) {
        u = -theta / (2 * M_PI);
    } else {
        u = 1 -theta / (2 * M_PI);
    }

    float v = asin(-hit.y/ radius)/M_PI + 0.5;

    return glm::vec2(u, v);
}

// // // // // // // // // // // // // // // // // // // // // // // // // //
//Cone

// hit must be in object space
glm::vec3 RayCone::getNormal(glm::vec3 hit) {
    if (hit.y + 0.5 <= EPSILON) {
        return glm::vec3(0,-1,0);
    }
    // horizontal part of the normal is determined by x and z
    glm::vec3 horizontal = glm::vec3(hit.x, 0, hit.z);
    horizontal = glm::normalize(horizontal);
    // vertical part's magnitude is half of the horizontal part
    // because of the slope of the cone
    glm::vec3 vertical = glm::vec3(0, 0.5f, 0);
    glm::vec3 n = glm::normalize(horizontal + vertical);
    return n;
}

bool RayCone::intersect(const glm::vec3 eye, const glm::vec3 ray, double &t) {
    // check if the bottom disk can be hit from below
    // if can be hit, then bottom disk is the closest
    if(ray.y > 0.0 && eye.y < -0.5) {
            t = (-0.5 - eye.y) / ray.y;
            double hitX = eye.x + ray.x * t;
            double hitZ = eye.z + ray.z * t;
            if(hitX * hitX + hitZ * hitZ <= 0.25) {
                return true;
            }
    }

    double a = ray.x * ray.x + ray.z * ray.z - 0.25 * ray.y * ray.y;
    double b = 2.0 * eye.x * ray.x + 2.0 * eye.z * ray.z - 0.5 * eye.y * ray.y + 0.25 * ray.y;
    double c = eye.x * eye.x + eye.z * eye.z - 0.25 * eye.y * eye.y + 0.25 * eye.y - (1.0 / 16.0);
    if(!solveT(a, b, c, t)) {
        return false;
    }
    double hitY = eye.y + ray.y * t;
    return (hitY >= -0.5 && hitY <= 0.5);
}

glm::vec2 RayCone::getUV(glm::vec3 hit) {
    if (hit.y <= -.5f + EPSILON_F) return glm::vec2(hit.x + 0.5f, -hit.z + 0.5f);
    float v = -hit.y + 0.5f;
    float theta = atan2(hit.z, hit.x);
    float u = 0.f;
    if (theta < 0) {
        u = -theta / (2 * M_PI);
    } else {
        u = 1 -theta / (2 * M_PI);
    }

    return glm::vec2(u, v);
}

// // // // // // // // // // // // // // // // // // // // // // // // // //
//Cylinder

// hit must be in object space
glm::vec3 RayCylinder::getNormal(glm::vec3 hit) {
    if (hit.y + 0.5f <= EPSILON) {
        return glm::vec3(0, -1, 0);
    }
    if (hit.y - 0.5f >= -EPSILON) {
        return glm::vec3(0, 1, 0);
    }
    return glm::vec3(hit.x, 0, hit.z);
}

bool RayCylinder::intersect(const glm::vec3 eye, const glm::vec3 ray, double &t) {
        // check hit bottom disk, the same way as cone
        if(ray.y > 0 && eye.y < -0.5)
        {
            t = (-0.5 - eye.y) / ray.y;
            double hitX = eye.x + ray.x * t;
            double hitZ = eye.z + ray.z * t;
            if(hitX * hitX + hitZ * hitZ <= 0.25 + EPSILON) {
                return true;
            }
        }

        // check hit top disk
        if(ray.y < 0 && eye.y > 0.5)
        {
            t = (0.5 - eye.y) / ray.y;
            double hitX = eye.x + ray.x * t;
            double hitZ = eye.z + ray.z * t;
            if(hitX * hitX + hitZ * hitZ <= 0.25 + EPSILON) {
                return true;
            }
        }

        //check hit infinite cylinder
        double a = ray.x * ray.x + ray.z * ray.z;
        double b = 2.0 * (eye.x * ray.x + eye.z * ray.z);
        double c = eye.x * eye.x + eye.z*eye.z - 0.25;
        // if no hit
        if(!solveT(a, b, c, t)) {
            return false;
        }
        // if hit, check if y is within valid range
        double hitY = eye.y + ray.y * t;
        return (hitY >= -0.5 - EPSILON && hitY <= 0.5 + EPSILON);
}

glm::vec2 RayCylinder::getUV(glm::vec3 hit) {
    if (hit.y <= -.5f + EPSILON_F) return glm::vec2(hit.x + 0.5f, -hit.z + 0.5f);
    if (hit.y >= .5f - EPSILON_F) return glm::vec2(hit.x + 0.5f, hit.z + 0.5f);
    float v = -hit.y + .5f;
    float theta = atan2(hit.z, hit.x);
    float u = 0.f;
    if (theta < 0) {
        u = -theta / (2 * M_PI);
    } else {
        u = 1 -theta / (2 * M_PI);
    }

    return glm::vec2(u, v);
}
