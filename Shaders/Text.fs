 #version 450 core

 out vec4 FragColor;

 in vec3 Tex;

 uniform sampler2D Texture;

 void main(){
//     FragColor = texture(Texture, Tex.xy);
    FragColor = vec4(1.0f,1.0f,1.0f,1.0f);
 }
