#include "limitlit/graphics/Framebuffer.hpp"
#include "limitlit/graphics/BitmapFont.hpp"
#include <algorithm>
#include <cstdlib>
namespace LimitLit
{
Framebuffer::Framebuffer(int width,int height):m_width(width),m_height(height),m_pixels(static_cast<std::size_t>(width*height)){}
void Framebuffer::Clear(uint32_t color){std::fill(m_pixels.begin(),m_pixels.end(),color);}
void Framebuffer::SetPixel(int x,int y,uint32_t color){if(x<0||y<0||x>=m_width||y>=m_height)return; m_pixels[static_cast<std::size_t>(y*m_width+x)]=color;}
void Framebuffer::DrawLine(int x0,int y0,int x1,int y1,uint32_t color){const int dx=std::abs(x1-x0),sx=x0<x1?1:-1,dy=-std::abs(y1-y0),sy=y0<y1?1:-1; int err=dx+dy; while(true){SetPixel(x0,y0,color); if(x0==x1&&y0==y1)break; const int e2=2*err; if(e2>=dy){err+=dy;x0+=sx;} if(e2<=dx){err+=dx;y0+=sy;}}}
void Framebuffer::DrawRectangle(int x,int y,int width,int height,uint32_t color){if(width<=0||height<=0)return; DrawLine(x,y,x+width-1,y,color); DrawLine(x,y,x,y+height-1,color); DrawLine(x+width-1,y,x+width-1,y+height-1,color); DrawLine(x,y+height-1,x+width-1,y+height-1,color);}
void Framebuffer::FillRectangle(int x,int y,int width,int height,uint32_t color){if(width<=0||height<=0)return; for(int r=y;r<y+height;++r)for(int c=x;c<x+width;++c)SetPixel(c,r,color);}
void Framebuffer::FillCircle(int cx,int cy,int radius,uint32_t color){if(radius<=0)return; const int r2=radius*radius; for(int y=-radius;y<=radius;++y)for(int x=-radius;x<=radius;++x)if(x*x+y*y<=r2)SetPixel(cx+x,cy+y,color);}
void Framebuffer::DrawCharacter(int x,int y,char ch,uint32_t color,int scale){if(scale<=0)return; const auto glyph=BitmapFont::Glyph(ch); for(int row=0;row<7;++row){const uint8_t bits=glyph[static_cast<std::size_t>(row)]; for(int col=0;col<5;++col)if((bits&(1u<<(4-col)))!=0)FillRectangle(x+col*scale,y+row*scale,scale,scale,color);}}
void Framebuffer::DrawString(int x,int y,std::string_view text,uint32_t color,int scale){int cx=x; for(char ch:text){DrawCharacter(cx,y,ch,color,scale); cx+=6*scale;}}
const uint32_t* Framebuffer::Data() const{return m_pixels.data();} int Framebuffer::Width() const{return m_width;} int Framebuffer::Height() const{return m_height;}
}
