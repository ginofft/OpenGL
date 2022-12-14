#pragma once

#include<glew.h>
#include<string>

#include<stb_image.h>

class Texture{
    public:
        Texture();
        Texture(char* fileLoc);

        void loadTexture();
        void useTexture();
        void clearTexture();

        ~Texture();

    private:
        GLuint textureID;
        int width, height, bitDepth;

        char* fileLocation;

};