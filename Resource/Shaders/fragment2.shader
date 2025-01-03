#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;
in float TexIndex;

uniform sampler2D textures[2];

void main()
{
    int index = int(TexIndex);
    FragColor = texture(textures[index], TexCoord);
}