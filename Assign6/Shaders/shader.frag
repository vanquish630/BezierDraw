#version 330                                                                  

out vec4 colour;
uniform vec4 customColour;
void main()                                                                   
{
    colour = customColour;															  
}