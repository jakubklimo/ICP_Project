#include "texture.hpp"


Texture::Texture(const std::string& path)
{
    cv::Mat image = cv::imread(path, cv::IMREAD_UNCHANGED);

    if (image.empty())
    {
        std::cerr << "Failed to load texture: " << path << std::endl;
        return;
    }

    cv::flip(image, image, 0);

    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    GLenum internalFormat;
    GLenum dataFormat;

    if (image.channels() == 4)
    {
        internalFormat = GL_RGBA;
        dataFormat = GL_BGRA;
    }
    else
    {
        internalFormat = GL_RGB;
        dataFormat = GL_BGR;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, image.cols, image.rows, 0, dataFormat, GL_UNSIGNED_BYTE, image.data);

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
    glDeleteTextures(1, &ID);
}

void Texture::bind(unsigned int unit) const
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, ID);
}