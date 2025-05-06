#shader vertex
#version 330 core

layout(location = 0) in vec4 a_position;
layout(location = 1) in vec4 a_color;

uniform mat4 u_MVP;


out vec4 v_Color;

void main() {
    gl_Position = u_MVP * a_position;
    v_Color = a_color;
}


#shader fragment
#version 330 core

layout(location = 0) out vec4 fragColor;

uniform vec2 u_MousePos;
uniform float u_WindowHeight;

in vec4 v_Color;

void main() {

    float distance = distance(vec2(gl_FragCoord.x, u_WindowHeight - gl_FragCoord.y), u_MousePos);
    // lighting
    fragColor = vec4(30.0/distance * v_Color.rgb, v_Color.a);
}
