Vulkan Flocking: compute and shading in one pipeline!
======================

**University of Pennsylvania, CIS 565: GPU Programming and Architecture, Project 6**

* Trung Le
* Windows 10 Home, i7-4790 CPU @ 3.60GHz 12GB, GTX 980 Ti (Personal desktop)

![](images/vulkan_duck_flock.gif)

**THERE SHALL BE DUCKS!**

### Features

_`#define DRAW_POINTS` is used to toggle between drawing just points or drawing the duck's mesh_

On top of the naive flocking, I implemented gtTF mesh loading using tinygltfloader and enabled instancing to draw the duckies. This required some code restructuring to support mesh and instancing. Since Vulkan allows for compute and graphics to share data, I simply just used storageBufferB data as the instancing attribute for the mesh's center. Enjoy!

### Analysis

![](images/vulkan_flock.gif)


- Why do you think Vulkan expects explicit descriptors for things like generating pipelines and commands? HINT: this may relate to something in the comments about some components using pre-allocated GPU memory.

The descriptor layout uses a register array with pre-allocated GPU memory. By being able to specify explicit descriptors, developers can assign descriptor sets binding more effeciently, instead of relying on the driver (as in OpenGL), to copy this register array over everytime one of the binding changes, reducing less overheading in resource binding.

- Describe a situation besides flip-flop buffers in which you may need multiple descriptor sets to fit one descriptor layout.

Swaping textures. Let's say we have a lists of textures for a specific mesh, this list can be bound to a list of descriptor sets in a descriptor layout. When the mesh needs to update its texture, the descriptor set can be swapped to so that the shader can read from a new texture.

- What are some problems to keep in mind when using multiple Vulkan queues? 
	- take into consideration that different queues may be backed by different hardware
	- take into consideration that the same buffer may be used across multiple queues

Since Vulkan only has one graphics queue (graphics queue queue can perform compute function also, but it doesn't have to) but multiple compute queue, we should strategize the workload so that most of the computation can be carried out in the compute queue. Also, since a buffer might be potentially accessed from different queues in parallel, extra caution needs to be done to guard against this. Adding resource access masks (load, store op) and `VkSemaphore` can help prevent this read/write concurrency problem.

- What is one advantage of using compute commands that can share data with a rendering pipeline?

By using compute commands that can share data with the rendering pipeline, we can avoid unncessary memory transfer from device and host. In a CUDA pipeline, the compute data needs to be copied to host, then copied back into the graphics pipeline. This overhead can now be eliminated with Vulkan.

### Credits

* [Vulkan examples and demos](https://github.com/SaschaWillems/Vulkan) by [@SaschaWillems](https://github.com/SaschaWillems)
* [tinygltfloader](https://github.com/syoyo/tinygltfloader) by [@soyoyo](https://github.com/syoyo)
