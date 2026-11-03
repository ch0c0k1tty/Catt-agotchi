#include "display.h"
#include "sprites.h"
#include <stddef.h>
#include <assert.h>

static TFT_t dev;

//#define BAR_WIDTH
//#define BAR_HEIGHT

#define SCREEN_WIDTH  240
#define SCREEN_HEIGHT 320

#define BABY_PINK rgb565( 0xFD , 0xBD , 0xE4 )
#define FUSCHIA   rgb565( 0xFF , 0x00 , 0xFF )
#define VIOLET    rgb565( 0x7F , 0x00 , 0xFF )
#define LAVENDER  rgb565( 0xDF , 0xC5 , 0xFE )

static const uint16_t backgroundColor = LAVENDER;
//static const uint16_t textColor       = VIOLET;
//static const uint16_t statusbarColor  = FUSCHIA;
//static const uint16_t fillerColor     = BABY_PINK;

void display_init( const display_pins_t * pins )
{
    assert( pins != NULL );

    spi_master_init(
        &dev,
        pins->mosi,
        pins->sclk,
        pins->cs,
        pins->dc,
        pins->reset,
        pins->bl
    );

    lcdInit( &dev , SCREEN_WIDTH , SCREEN_HEIGHT , 0 , 0 );
}

static void draw_catt( catt_t * catt );

void display_render( catt_t * catt , display_icon_t icon )
{
    lcdFillScreen( &dev , backgroundColor );
    draw_catt( catt );
    // ...
}

static void draw_icons( display_icon_t highlighted )
{
    //...
}

static void draw_sprite( const uint16_t * frame )
{
    uint16_t row[SPRITE_WIDTH];

    for ( int y = 0 ; y < SPRITE_HEIGHT ; y++ )
    {
        for ( int x = 0 ; x < SPRITE_WIDTH ; x++ )
        {
            uint16_t px = frame[y * SPRITE_WIDTH + x];
            row[x] = ( px == SPRITE_TRANSPARENT ) ? backgroundColor : px;
        }
        lcdDrawMultiPixels( &dev , SPRITE_X , SPRITE_Y + y , SPRITE_WIDTH , row );
    }
}

// Advances one animation frame per render call; sad animation plays while any stat is empty.
static void draw_catt( catt_t * catt )
{
    static uint8_t frame = 0;

    if ( catt_satisfied( catt ) )
    {
        draw_sprite( sprites_happy[ frame % SPRITE_HAPPY_FRAMES ] );
    }
    else
    {
        draw_sprite( sprites_sad[ frame % SPRITE_SAD_FRAMES ] );
    }
    frame++;
}

static void draw_statusbar()
{
    //...
}

static void draw_stats()
{
    //...
}

static void draw_dead_catt()
{
    //...
}
