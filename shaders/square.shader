#type vertex
#version 410 core
layout(location = 0) in vec4 a_Position;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

void main() {
    // gl_Position = u_ViewProjection * u_Transform * a_Position;
    gl_Position = a_Position;
}

#type fragment
#version 410 core
layout(location = 0) out vec4 fragColor;

void main() {
    fragColor = vec4(1.0);
}