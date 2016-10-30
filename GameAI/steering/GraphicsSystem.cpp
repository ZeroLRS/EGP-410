#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>

#include "Game.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"

GraphicsSystem::GraphicsSystem()
	:mpDisplay(NULL)
	,mpBackBuffer(NULL)
	,mWidth(0)
	,mHeight(0)
{
}

GraphicsSystem::~GraphicsSystem()
{
	cleanup();
}

bool GraphicsSystem::init( int width, int height )
{
	mWidth = width;
	mHeight = height;
	mpDisplay = al_create_display(width, height);
	if(!mpDisplay) 
	{
		fprintf(stderr, "GraphicsSystem::failed to create display!\n");
		return false;
	}

	al_init_font_addon();
	if (!al_init_ttf_addon())
	{
		printf("ttf font addon not initted properly!\n");
		return false;
	}

	//actually load the font
	mpFont = al_load_ttf_font("cour.ttf", 20, 0);
	if (mpFont == NULL)
	{
		printf("ttf font file not loaded properly!\n");
		return false;
	}
		
	//get the backbuffer
	ALLEGRO_BITMAP* pBackBuffer = al_get_backbuffer( mpDisplay );

	//set the back buffer as the target bitmap
	al_set_target_bitmap( pBackBuffer );

	//create the GraphicsBuffer backbuffer
	mpBackBuffer = new GraphicsBuffer( pBackBuffer );

	//al_set_blender(ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA, al_map_rgb(255,255,255));

	return true;
}

void GraphicsSystem::cleanup()
{
	al_destroy_font(mpFont);
	mpFont = NULL;

	al_destroy_display( mpDisplay );
	mpDisplay = NULL;

	mpBackBuffer->invalidate();
	delete mpBackBuffer;
	mpBackBuffer = NULL;
}

void GraphicsSystem::swap()
{
	al_flip_display();
}

void GraphicsSystem::drawText(const Vector2D& pos, const std::string& text, const bool highlight)
{
	ALLEGRO_COLOR color;
	if (highlight)
		color = al_map_rgb(255, 255, 0);
	else
		color = al_map_rgb(255, 255, 255);
	al_draw_text(mpFont, color, pos.getX(), pos.getY(), ALLEGRO_ALIGN_LEFT, text.c_str());
}

void GraphicsSystem::wrapCoordinates( Vector2D& vector )
{
	if( vector.getX() < 0.0f )
	{
		vector.setX( getWidth() - 1.0f );
	}
	else if( vector.getX() >= getWidth() )
	{
		vector.setX( 0.0f );
	}

	if( vector.getY() < 0.0f )
	{
		vector.setY( getHeight() - 1.0f );
	}
	else if( vector.getY() >= getHeight() )
	{
		vector.setY( 0.0f );
	}
}

//static function
ALLEGRO_BITMAP* GraphicsSystem::switchTargetBitmap( ALLEGRO_BITMAP* pNewTarget )
{
	//get old target bitmap
	ALLEGRO_BITMAP* pOldTarget = al_get_target_bitmap();
	//set dest to be the target
	al_set_target_bitmap( pNewTarget );

	return pOldTarget;
}
