#shader vertex
#version 330 core

layout(location = 0) in vec4 a_position;
layout(location = 1) in vec2 a_texCoord;

out vec2 v_TexCoord;

void main() {
    gl_Position = a_position;
    v_TexCoord = a_texCoord;
}


#shader fragment
#version 330 core

layout(location = 0) out vec4 fragColor;

in vec2 v_TexCoord;

uniform sampler2D u_Texture_BeautifulSunset;

void main() {
    vec4 texColor = texture(u_Texture_BeautifulSunset, v_TexCoord);
    fragColor = vec4(texColor.xyz, 0.5);
}