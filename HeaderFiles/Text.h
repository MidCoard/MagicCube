//#ifndef MAGICCUBE_TEXT_H
//#define MAGICCUBE_TEXT_H
//
//#include <map>
//#include <ft2build.h>
//#include FT_FREETYPE_H
//
//#include "Shader.h"
//
//
//using namespace std;
//using namespace glm;
//
//struct Character {
//    GLuint     TextureID;  // 字形纹理的ID
//    ivec2 Size;       // 字形大小
//    ivec2 Bearing;    // 从基准线到字形左部/顶部的偏移值
//    FT_Pos     Advance;    // 原点距下一个字形原点的距离
//};
//
//map<GLchar, Character> Characters;
//
//
//void loadText(){
//    FT_Library ft;
//    if (FT_Init_FreeType(&ft))
//        cout << "ERROR::FREETYPE: Could not init FreeType Library" << endl;
//
//    FT_Face face;
//    if (FT_New_Face(ft, "fonts/arial.ttf", 0, &face))
//        cout << "ERROR::FREETYPE: Failed to load font" << endl;
//
//    FT_Set_Pixel_Sizes(face, 0, 48);
//
//    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //禁用字节对齐限制
//    for (GLubyte c = 0; c < 128; c++)
//    {
//        // 加载字符的字形
//        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
//        {
//            cout << "ERROR::FREETYPE: Failed to load Glyph" << endl;
//            continue;
//        }
//        // 生成纹理
//        GLuint texture;
//        glGenTextures(1, &texture);
//        glBindTexture(GL_TEXTURE_2D, texture);
//        glTexImage2D(
//                GL_TEXTURE_2D,
//                0,
//                GL_RED,
//                face->glyph->bitmap.width,
//                face->glyph->bitmap.rows,
//                0,
//                GL_RED,
//                GL_UNSIGNED_BYTE,
//                face->glyph->bitmap.buffer
//        );
//        // 设置纹理选项
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//        // 储存字符供之后使用
//        Character character = {
//                texture,
//                ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
//                ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
//                face->glyph->advance.x
//        };
//        Characters.insert(pair<GLchar, Character>(c, character));
//    }
//
//    FT_Done_Face(face);
//    FT_Done_FreeType(ft);
//}
//
//void renderText(Shader* &s, string text, GLfloat x, GLfloat y, GLfloat scale, vec3 color)
//{
//    // 激活对应的渲染状态
//    s->use();
//    glUniform3f(glGetUniformLocation(s->getProgramId(), "textColor"), color.x, color.y, color.z);
//    glActiveTexture(GL_TEXTURE0);
//    glBindVertexArray(textVAO);
//
//    // 遍历文本中所有的字符
//    string::const_iterator c;
//    for (c = text.begin(); c != text.end(); c++)
//    {
//        Character ch = Characters[*c];
//
//        GLfloat xpos = x + ch.Bearing.x * scale;
//        GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
//
//        GLfloat w = ch.Size.x * scale;
//        GLfloat h = ch.Size.y * scale;
//        // 对每个字符更新VBO
//        GLfloat vertices[6][4] = {
//                { xpos,     ypos + h,   0.0, 0.0 },
//                { xpos,     ypos,       0.0, 1.0 },
//                { xpos + w, ypos,       1.0, 1.0 },
//
//                { xpos,     ypos + h,   0.0, 0.0 },
//                { xpos + w, ypos,       1.0, 1.0 },
//                { xpos + w, ypos + h,   1.0, 0.0 }
//        };
//        // 在四边形上绘制字形纹理
//        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
//        // 更新VBO内存的内容
//        glBindBuffer(GL_ARRAY_BUFFER, textVBO);
//        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
//        glBindBuffer(GL_ARRAY_BUFFER, 0);
//        glDrawArrays(GL_TRIANGLES, 0, 6);
//        x += (ch.Advance >> 6) * scale; // 位偏移6个单位来获取单位为像素的值 (2^6 = 64)
//    }
//    glBindVertexArray(0);
//    glBindTexture(GL_TEXTURE_2D, 0);
//}
//#endif