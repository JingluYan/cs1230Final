No known bugs. Tested against all scene files in the intersect folders and many in other folders

Design decision:
1. created a rayshape class and four subclasses: raycube, raycylinder, raysphere, and raycone. Each rayshape is responsible for calculating the intersection and normal of the hit point. I choose not to add the intersection calculation in the shape classes in early shape assignments because we don't need to know the vertices and normals of the shape, so to save memory, I created rayshape classes to store only the information needed for calculating ray.

2. Created a light class, my plan is to have different light types inherit the light base class, so I have point light and direcitonal light sub class to add diffuse, specular, texture light contribution to each pixel. Each light class is responsible for calculatin its own light contribution to a pixel.

3. In rayscene, I instantiated all light and rayshape instances based on the lights and shapes in the sceneviewscene. The raylights and rayshapes copies necessary information from the lights and shapes in the sceneviewscene. This way we reduces the memeory load. 

EXTRA CREIDT:
I implemented multi-threading, see the rendertask.cpp. In raytracer render function, I dispatch a thread in the thread pool and run the render trask.

OTHER Note:
The max recursion depth is set to 4. it can be adjusted in rayutils.h

