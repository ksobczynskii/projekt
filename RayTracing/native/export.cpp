#include "rtweekend.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include "color.h"
#include "camera.h"
#include <vector>
#include <cstring>
#include <memory>
#include <cstdint>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "external/stb_image_write.h"

#ifdef _WIN32
  #define EXPORT __declspec(dllexport)
#else
  #define EXPORT __attribute__((visibility("default")))
#endif

extern "C" EXPORT material* CreateMaterial();
extern "C" EXPORT camera* CreateCamera();
extern "C" EXPORT ray* CreateRay();
extern "C" EXPORT vec3* CreateVec3();
extern "C" EXPORT interval* CreateInterval();
extern "C" EXPORT hittable_list* CreateHittableList();

extern "C" EXPORT void DestroyMaterial(material*);
extern "C" EXPORT void DestroyCamera(camera*);
extern "C" EXPORT void DestroyRay(ray*);
extern "C" EXPORT void DestroyVec3(vec3*);
extern "C" EXPORT void DestroyInterval(interval*);
extern "C" EXPORT void DestroyHittableList(hittable_list*);

extern "C" EXPORT CameraConfig;
extern "C" EXPORT uint8_t* RenderScene(CameraConfig config);
extern "C" EXPORT void SavePng(const char* filename, int w, int h,int comp, int stride_in_bytes,uint8_t* buffer);
// Create
material* CreateMaterial()
{
    return new material();
}

camera* CreateCamera()
{
    return new camera();
}

// hittable* CreateHittable()
// {
//     return new hittable();
// }
ray* CreateRay()
{
    return new ray();
}

// sphere* CreateSphere()
// {
//     return new sphere();
// }

vec3* CreateVec3()
{
    return new vec3();
}

interval* CreateInterval()
{
    return new interval();
}

hittable_list* CreateHittableList()
{
    return new hittable_list();
}


// Destroy
void DestroyMaterial(material* &mat)
{
    delete mat;
}

void DestroyCamera(camera*&cam)
{
    delete cam;
}

void DestroyHittable(hittable*&hit)
{
    delete hit;
}
void DestroyRay(ray*&r)
{
    delete r;
}

// sphere* CreateSphere()
// {
//     return new sphere();
// }

void DestroyVec3(vec3*&v3)
{
    delete v3;
}

void DeleteInterval(interval*& inter)
{
    delete inter;
}

void DeleteHittableList(hittable_list*& hList)
{
    delete hList();
}
struct CameraConfig
{
    double aspect_ratio;
    int    image_width;
    int    samples_per_pixel;
    int    max_depth;

    double vfov;
    point3 lookfrom;
    point3 lookat;
    vec3   vup;

    double defocus_angle;
    double focus_dist;
    
};
typedef void (*RenderCallback)(int samples, uint8_t* buffer);
uint8_t* RenderScene(CameraConfig config)
{
    camera cam;
    cam.aspect_ratio = config.aspect_ratio;
    cam.image_width = config.image_width;
    cam.samples_per_pixel = config.samples_per_pixel;
    cam.max_depth = config.max_depth;

    cam.vfov = config.vfov;
    cam.lookfrom = config.lookfrom;
    cam.lookat = config.lookat;
    cam.vup = config.vup;
    
    cam.defocus_angle = config.defocus_angle;
    cam.focus_dist = config.focus_dist;

    hittable world;
    uint8_t* buffer;
    cam.render(world,buffer,RenderCallback);
    return buffer;
}

void SavePng(const char* filename, int w, int h,int comp, int stride_in_bytes,uint8_t* buffer)
{
    stbi_write_png(filename,w,h,comp,buffer,stride_in_bytes);
}


