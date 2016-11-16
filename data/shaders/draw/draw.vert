#version 450
#extension GL_ARB_separate_objects : enable

out gl_PerVertex {
	vec4 gl_Position;
};

layout(binding = 0) uniform UniformBufferObject {
	mat4 model;
	mat4 view;
	mat4 proj;
} ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 center;

layout(location = 0) out vec3 fragNormal;
layout(location = 2) out vec3 lightDirection;
layout(location = 3) out vec3 fragPosition;


vec3 lightPos = vec3(-5.0, 2.0, 5.0);

void main() {
	vec4 position = ubo.model * vec4(inPosition, 1.0);
	position += vec4(center, 0.0, 1.0);
	position = ubo.proj * ubo.view * position;
	// -- Out
	fragNormal = inNormal;
	fragPosition = vec3(position);
	lightDirection = normalize(lightPos - vec3(position));

	// -- Position
	gl_Position = position;
}
