// Version du GLSL

#version 150 core


// Entr�e

in vec2 coordTexture;


// Uniform

uniform sampler2D tex;


// Sortie 

out vec4 out_Color;


// Fonction main

void main()
{
    // Couleur du pixels

	out_Color = texture(tex, coordTexture);
}
