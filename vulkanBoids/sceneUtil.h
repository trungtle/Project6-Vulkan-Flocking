#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <array>
#include <map>
#include <glm/mat4x4.hpp>
#include "vulkanbuffer.hpp"

typedef unsigned char Byte;

typedef enum
{
	INDEX,
	POSITION,
	NORMAL,
	TEXCOORD
} EVertexAttributeType;


typedef struct VertexAttributeInfoTyp
{
	size_t byteStride;
	size_t count;
	int componentLength;
	int componentTypeByteSize;

} VertexAttributeInfo;

typedef struct MaterialTyp
{
	glm::vec4 diffuse;
	glm::vec4 ambient;
	glm::vec4 emission;
	glm::vec4 specular;
	float shininess;
	float transparency;
} Material;

// ===================
// UNIFORM
// ===================

typedef struct UniformBufferObjectTyp
{
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
} UniformBufferObject;

// ===================
// BUFFER
// ===================

typedef struct BufferLayoutTyp
{
	VkDeviceSize indexBufferOffset;
	std::map<EVertexAttributeType, VkDeviceSize> vertexBufferOffsets;
} BufferLayout;

// ===================
// GEOMETRIES
// ===================
typedef struct GeometryBufferTyp
{
	/**
	* \brief Byte offsets for vertex attributes and resource buffers into our unified buffer
	*/
	BufferLayout bufferLayout;

	/**
	* \brief Handle to the vertex buffers
	*/
	VkBuffer vertexBuffer;

	/**
	* \brief Handle to the device memory
	*/
	VkDeviceMemory vertexBufferMemory;
} GeometryBuffer;

static
VkVertexInputBindingDescription
GetVertexInputBindingDescription(
	uint32_t binding,
	const VertexAttributeInfo& vertexAttrib
)
{
	VkVertexInputBindingDescription bindingDesc;
	bindingDesc.binding = binding; // Which index of the array of VkBuffer for vertices
	bindingDesc.stride = vertexAttrib.componentLength * vertexAttrib.componentTypeByteSize;
	bindingDesc.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	return bindingDesc;
}

typedef struct VertexAttributeDescriptionsTyp
{

	VkVertexInputAttributeDescription position;
	VkVertexInputAttributeDescription normal;
	VkVertexInputAttributeDescription center;

	std::array<VkVertexInputAttributeDescription, 3>
		ToArray() const
	{
		std::array<VkVertexInputAttributeDescription, 3> attribDesc = {
			position,
			normal,
			center
		};

		return attribDesc;
	}

} VertexAttributeDescriptions;

static
std::array<VkVertexInputAttributeDescription, 3>
GetAttributeDescriptions()
{
	VertexAttributeDescriptions attributeDesc;

	// Position attribute
	attributeDesc.position.binding = 0;
	attributeDesc.position.location = 0;
	attributeDesc.position.format = VK_FORMAT_R32G32B32_SFLOAT;
	attributeDesc.position.offset = 0;

	// Normal attribute
	attributeDesc.normal.binding = 1;
	attributeDesc.normal.location = 1;
	attributeDesc.normal.format = VK_FORMAT_R32G32B32_SFLOAT;
	attributeDesc.normal.offset = 0;

	// Instance attribute
	attributeDesc.center.binding = 2;
	attributeDesc.center.location = 2;
	attributeDesc.center.format = VK_FORMAT_R32G32_SFLOAT;
	attributeDesc.center.offset = 0;

	return attributeDesc.ToArray();
}