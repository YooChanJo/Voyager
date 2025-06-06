#type vertex
#version 410 core
layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec4 a_Color;

out vec4 v_Color;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

void main() {
    gl_Position = u_ViewProjection * u_Transform * a_Position;
    v_Color = a_Color;
}

#type fragment
#version 410 core
layout(location = 0) out vec4 fragColor;

in vec4 v_Color;

void main() {
    fragColor = v_Color;
}