#include <stdio.h>
extern "C" {
    #include "dscapture.h"
}
#include <SFML/Graphics.hpp>

static sf::Clock m_time;
static uint frames;
static bool split;
static bool init;

void toRGBA(uint8_t *out, uint16_t *in) {
    int i;
    for(i=0;i<FRAMEWIDTH*FRAMEHEIGHT*2;i++) {
        unsigned char r,g,b;
        g=((*in)>>5)&0x3f;
        b=((*in<<1)&0x3e)|(g&1);
        r=(((*in)>>10)&0x3e)|(g&1);
        out[0]=(r<<2) | (r>>4);
        out[1]=(g<<2) | (g>>4);
        out[2]=(b<<2) | (b>>4);
        out[3]=255;
        out+=4;
        in++;
    }
}


/* GIMP RGBA C-Source image dump (favicon_ds.c) */

static const struct {
  unsigned int 	 width;
  unsigned int 	 height;
  unsigned int 	 bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
  unsigned char	 pixel_data[16 * 16 * 4 + 1];
} sfml_icon = {
  16, 16, 4,
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\326\327\330\377\326\327\330\377\326\327"
  "\330\377\326\327\330\377\326\327\330\377\326\327\330\377\326\327\330\377"
  "\326\327\330\377\326\327\330\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\326\327\330\377\326\327\330\377\326\327\330\377\326\327\330\377"
  "\326\327\330\377\326\327\330\377\326\327\330\377\326\327\330\377\326\327"
  "\330\377\326\327\330\377\326\327\330\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\326\327\330\377\326\327\330\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\326\327\330\377\326\327\330\377\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\326\327\330\377\326\327\330\377\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\326\327\330\377\326\327\330\377"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\326\327\330\377\326\327\330\377"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\326\327\330\377"
  "\326\327\330\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\326\327\330\377"
  "\326\327\330\377\326\327\330\377\326\327\330\377\326\327\330\377\326\327"
  "\330\377\326\327\330\377\326\327\330\377\326\327\330\377\326\327\330\377"
  "\326\327\330\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\326\327"
  "\330\377\326\327\330\377\326\327\330\377\326\327\330\377\326\327\330\377"
  "\326\327\330\377\326\327\330\377\326\327\330\377\326\327\330\377\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\222\224\227\377\222\224\227\377\222\224"
  "\227\377\222\224\227\377\222\224\227\377\222\224\227\377\222\224\227\377"
  "\222\224\227\377\222\224\227\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\222\224\227\377\222\224\227\377\222\224\227\377\222\224\227\377"
  "\222\224\227\377\222\224\227\377\222\224\227\377\222\224\227\377\222\224"
  "\227\377\222\224\227\377\222\224\227\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\222\224\227\377\222\224\227\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\222\224\227\377\222\224\227\377\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\222\224\227\377\222\224\227\377\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\222\224\227\377\222\224\227\377"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\222\224\227\377\222\224\227\377"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\222\224\227\377"
  "\222\224\227\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\222\224\227\377"
  "\222\224\227\377\222\224\227\377\222\224\227\377\222\224\227\377\222\224"
  "\227\377\222\224\227\377\222\224\227\377\222\224\227\377\222\224\227\377"
  "\222\224\227\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\222\224"
  "\227\377\222\224\227\377\222\224\227\377\222\224\227\377\222\224\227\377"
  "\222\224\227\377\222\224\227\377\222\224\227\377\222\224\227\377\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0",
};




int main()
{
    init = dscapture_init();
    split = false;
    frames = 0;
    m_time = sf::Clock();
    sf::RenderWindow window(sf::VideoMode(FRAMEWIDTH, FRAMEHEIGHT*2), "Cute DS Capture");
    sf::RenderWindow bottom_window;
    sf::RectangleShape top_screen(sf::Vector2f(FRAMEWIDTH, FRAMEHEIGHT));
    //top_screen.rotate(-90);
    //top_screen.setPosition(0,FRAMEHEIGHT);
    sf::RectangleShape bottom_screen(sf::Vector2f(FRAMEWIDTH, FRAMEHEIGHT));
    //bottom_screen.rotate(-90);
    bottom_screen.setPosition(0,FRAMEHEIGHT);

    sf::View total = sf::View(sf::FloatRect(0, 0, FRAMEWIDTH, FRAMEHEIGHT*2));
    sf::View top = sf::View(sf::FloatRect(0, 0, FRAMEWIDTH, FRAMEHEIGHT));
    sf::View bottom = sf::View(sf::FloatRect(0, FRAMEHEIGHT, FRAMEWIDTH, FRAMEHEIGHT));


    sf::Texture texture;
    uint8_t tex[] = {0,0,0,255};
    texture.create(int(FRAMEWIDTH),int(FRAMEHEIGHT)*2);
    texture.update(tex,1,1,0,0);

    top_screen.setTexture(&texture);
    top_screen.setTextureRect(sf::IntRect(0, 0, FRAMEWIDTH, FRAMEHEIGHT));
    bottom_screen.setTexture(&texture);
    bottom_screen.setTextureRect(sf::IntRect(0, FRAMEHEIGHT, FRAMEWIDTH, FRAMEHEIGHT));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type) {
            case sf::Event::Closed:
                if (bottom_window.isOpen()) {
                    bottom_window.close();
                }
                window.close();
                break;
            case sf::Event::KeyPressed:
                switch(event.key.code) {
                case sf::Keyboard::Num1:
                    window.setSize(sf::Vector2u(FRAMEWIDTH, FRAMEHEIGHT*(2-int(split))));
                    break;
                case sf::Keyboard::Num2:
                    window.setSize(sf::Vector2u(FRAMEWIDTH*3/2, FRAMEHEIGHT*3/2*(2-int(split))));
                    break;
                case sf::Keyboard::Num3:
                    window.setSize(sf::Vector2u(FRAMEWIDTH*4/2, FRAMEHEIGHT*4/2*(2-int(split))));
                    break;
                case sf::Keyboard::Num4:
                    window.setSize(sf::Vector2u(FRAMEWIDTH*5/2, FRAMEHEIGHT*5/2*(2-int(split))));
                    break;
                case sf::Keyboard::Num5:
                    window.setSize(sf::Vector2u(FRAMEWIDTH*6/2, FRAMEHEIGHT*6/2*(2-int(split))));
                    break;
                case sf::Keyboard::Num6:
                    window.setSize(sf::Vector2u(FRAMEWIDTH*7/2, FRAMEHEIGHT*7/2*(2-int(split))));
                    break;
                case sf::Keyboard::Num7:
                    window.setSize(sf::Vector2u(FRAMEWIDTH*8/2, FRAMEHEIGHT*8/2*(2-int(split))));
                    break;
                case sf::Keyboard::Num8:
                    window.setSize(sf::Vector2u(FRAMEWIDTH*9/2, FRAMEHEIGHT*9/2*(2-int(split))));
                    break;
                case sf::Keyboard::Num9:
                    window.setSize(sf::Vector2u(FRAMEWIDTH*10/2, FRAMEHEIGHT*10/2*(2-int(split))));
                    break;
                case sf::Keyboard::Num0:
                    window.setSize(sf::Vector2u(FRAMEWIDTH*11/2, FRAMEHEIGHT*11/2*(2-int(split))));
                    break;
                case sf::Keyboard::Space:
                    if (!split) {
                        window.setView(top);
                        window.setSize(sf::Vector2u(FRAMEWIDTH, FRAMEHEIGHT));
                        bottom_window.create(sf::VideoMode(FRAMEWIDTH, FRAMEHEIGHT), "Bottom Screen Cute DS Capture");
                        bottom_window.setView(bottom);
                        split = true;
                    } else {
                        window.setView(total);
                        window.setSize(sf::Vector2u(FRAMEWIDTH, FRAMEHEIGHT * 2));
                        bottom_window.close();
                        split = false;
                    }
                    break;
                default:
                    break;
                }

            default:
                break;
            }

        }

        if (bottom_window.isOpen()) {
            while (bottom_window.pollEvent(event))
            {
                switch(event.type) {
                case sf::Event::Closed:
                    bottom_window.close();
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    switch(event.key.code) {
                    case sf::Keyboard::Num1:
                        bottom_window.setSize(sf::Vector2u(FRAMEWIDTH, FRAMEHEIGHT));
                        break;
                    case sf::Keyboard::Num2:
                        bottom_window.setSize(sf::Vector2u(FRAMEWIDTH*3/2, FRAMEHEIGHT*3/2));
                        break;
                    case sf::Keyboard::Num3:
                        bottom_window.setSize(sf::Vector2u(FRAMEWIDTH*4/2, FRAMEHEIGHT*4/2));
                        break;
                    case sf::Keyboard::Num4:
                        bottom_window.setSize(sf::Vector2u(FRAMEWIDTH*5/2, FRAMEHEIGHT*5/2));
                        break;
                    case sf::Keyboard::Num5:
                        bottom_window.setSize(sf::Vector2u(FRAMEWIDTH*6/2, FRAMEHEIGHT*6/2));
                        break;
                    case sf::Keyboard::Num6:
                        bottom_window.setSize(sf::Vector2u(FRAMEWIDTH*7/2, FRAMEHEIGHT*7/2));
                        break;
                    case sf::Keyboard::Num7:
                        bottom_window.setSize(sf::Vector2u(FRAMEWIDTH*8/2, FRAMEHEIGHT*8/2));
                        break;
                    case sf::Keyboard::Num8:
                        bottom_window.setSize(sf::Vector2u(FRAMEWIDTH*9/2, FRAMEHEIGHT*9/2));
                        break;
                    case sf::Keyboard::Num9:
                        bottom_window.setSize(sf::Vector2u(FRAMEWIDTH*10/2, FRAMEHEIGHT*10/2));
                        break;
                    case sf::Keyboard::Num0:
                        bottom_window.setSize(sf::Vector2u(FRAMEWIDTH*11/2, FRAMEHEIGHT*11/2));
                        break;
                    case sf::Keyboard::Space:
                        if (!split) {
                            window.setView(top);
                            window.setSize(sf::Vector2u(FRAMEWIDTH, FRAMEHEIGHT));
                            bottom_window.create(sf::VideoMode(FRAMEWIDTH, FRAMEHEIGHT), "Bottom Screen Cute DS Capture");
                            bottom_window.setView(bottom);
                            split = true;
                        } else {
                            window.setView(total);
                            window.setSize(sf::Vector2u(FRAMEWIDTH, FRAMEHEIGHT * 2));
                            bottom_window.close();
                            split = false;
                        }
                        break;
                    default:
                        break;
                    }

                default:
                    break;
                }

            }
        }


        frames++;
        if (m_time.getElapsedTime().asMilliseconds() > 250) {
            char title[50];
            if (!split) {
                sprintf(title,"Cute DS Capture (%.2f FPS)", float(frames)/(m_time.getElapsedTime().asSeconds()));
            } else {
                sprintf(title,"Top Screen Cute DS Capture (%4.2f FPS)", float(frames)/(m_time.getElapsedTime().asSeconds()));
            }
            m_time.restart();
            frames = 0;
            window.setTitle(title);
        }

        window.clear();
		window.setIcon(sfml_icon.width,  sfml_icon.height,  sfml_icon.pixel_data);
        if(split) {
            bottom_window.clear();
			bottom_window.setIcon(sfml_icon.width,  sfml_icon.height,  sfml_icon.pixel_data);
        }

        if(!init) {
            init = dscapture_init();
        }

        uint16_t frameBuf[FRAMEHEIGHT*FRAMEWIDTH*2];
        uint8_t rgbaBuf[FRAMEHEIGHT*FRAMEWIDTH*2*4];
        if(init){
            switch(dscapture_grabFrame(frameBuf)) {
            case true:
                toRGBA(rgbaBuf,frameBuf);
                texture.update(rgbaBuf,int(FRAMEWIDTH),int(FRAMEHEIGHT*2),0,0);
                break;
            /*case CAPTURE_ERROR:
                dscapture_deinit();
                init = false;
                break;
            /*case CAPTURE_SKIP:
                break;*/
            default:
                dscapture_deinit();
                init = false;
                break;
            }
        }

        window.draw(top_screen);
        if (!split) {
            window.draw(bottom_screen);
        } else {
            bottom_window.draw(bottom_screen);
            bottom_window.display();
        }
		
        window.display();
    }
    dscapture_deinit();
    return 0;
}


