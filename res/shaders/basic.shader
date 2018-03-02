#shader vertex
#version 330 core                      

// Vertex buffer layout
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

// Varying
out vec2 v_texCoord;

void main(){                           
    gl_Position = position;
    v_texCoord = texCoord;
};

#shader fragment
#version 330 core                      

layout(location = 0) out vec4 color;  

// Varying
in vec2 v_texCoord;

// Uniforms
uniform vec4 u_color;
uniform sampler2D u_texture;

void main(){                           
    vec4 texColor = texture(u_texture, v_texCoord);
    color = texColor;
    //color = u_color;
    //color = vec4(0.2, 0.3, 0.8, 1.0);   
};