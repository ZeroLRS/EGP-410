#include <stdio.h>
#include <assert.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include <sstream>

#include "Game.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "GraphicsBufferManager.h"
#include "GameMessageManager.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Timer.h"
#include "KinematicUnit.h"
#include "PlayerMoveToMessage.h"
#include "Menu.h"

Game* gpGame = NULL;

const int WIDTH = 1024;
const int HEIGHT = 768;

Game::Game()
	:mpGraphicsSystem(NULL)
	,mpGraphicsBufferManager(NULL)
	,mpSpriteManager(NULL)
	,mpLoopTimer(NULL)
	,mpMasterTimer(NULL)
	,mShouldExit(false)
	,mpSample(NULL)
	,mBackgroundBufferID(INVALID_ID)
	//,mSmurfBufferID(INVALID_ID)
{
}

Game::~Game()
{
	cleanup();
}

bool Game::init()
{
	mShouldExit = false;
	mUnitVisionRadius = 150;

	//create Timers
	mpLoopTimer = new Timer;
	mpMasterTimer = new Timer;

	//startup allegro
	if(!al_init()) 
	{
		fprintf(stderr, "failed to initialize allegro!\n");
		return false;
	}

	//create and init GraphicsSystem
	mpGraphicsSystem = new GraphicsSystem();
	bool goodGraphics = mpGraphicsSystem->init( WIDTH, HEIGHT );
	if(!goodGraphics) 
	{
		fprintf(stderr, "failed to initialize GraphicsSystem object!\n");
		return false;
	}

	mpGraphicsBufferManager = new GraphicsBufferManager();
	mpSpriteManager = new SpriteManager();
	mpInputManager = new InputManager();

	//startup a lot of allegro stuff

	//load image loader addon
	if( !al_init_image_addon() )
	{
		fprintf(stderr, "image addon failed to load!\n");
		return false;
	}

	//install audio stuff
	if( !al_install_audio() )
	{
		fprintf(stderr, "failed to initialize sound!\n");
		return false;
	}

	if(!al_init_acodec_addon())
	{
		fprintf(stderr, "failed to initialize audio codecs!\n");
		return false;
	}
 
	if (!al_reserve_samples(1))
	{
		fprintf(stderr, "failed to reserve samples!\n");
		return false;
	}

	mpInputManager->init();

	if( !al_init_primitives_addon() )
	{
		printf( "Primitives addon not added!\n" ); 
		return false;
	}

	//load the sample
	mpSample = al_load_sample( "clapping.wav" );
	if (!mpSample)
	{
		printf( "Audio clip sample not loaded!\n" ); 
		return false;
	}

	mpMessageManager = new GameMessageManager();
	mpWallManager = new WallManager();

	//load buffers
	mBackgroundBufferID = mpGraphicsBufferManager->loadBuffer("wallpaper.bmp");
	mPlayerIconBufferID = mpGraphicsBufferManager->loadBuffer("arrow.bmp");
	mEnemyIconBufferID = mpGraphicsBufferManager->loadBuffer("enemy-arrow.bmp");
	
	//setup sprites
	GraphicsBuffer* pBackGroundBuffer = mpGraphicsBufferManager->getBuffer( mBackgroundBufferID );
	if( pBackGroundBuffer != NULL )
	{
		mpSpriteManager->createAndManageSprite( BACKGROUND_SPRITE_ID, pBackGroundBuffer, 0, 0, pBackGroundBuffer->getWidth(), pBackGroundBuffer->getHeight() );
	}
	GraphicsBuffer* pPlayerBuffer = mpGraphicsBufferManager->getBuffer( mPlayerIconBufferID );
	Sprite* pArrowSprite = NULL;
	if( pPlayerBuffer != NULL )
	{
		pArrowSprite = mpSpriteManager->createAndManageSprite( PLAYER_ICON_SPRITE_ID, pPlayerBuffer, 0, 0, pPlayerBuffer->getWidth(), pPlayerBuffer->getHeight() );
	}
	GraphicsBuffer* pAIBuffer = mpGraphicsBufferManager->getBuffer( mEnemyIconBufferID );
	Sprite* pEnemyArrow = NULL;
	if( pAIBuffer != NULL )
	{
		pEnemyArrow = mpSpriteManager->createAndManageSprite( AI_ICON_SPRITE_ID, pAIBuffer, 0, 0, pAIBuffer->getWidth(), pAIBuffer->getHeight() );
	}

	//setup units
	mpUnitManager = new UnitManager();

	Vector2D pos( 100.0f, 100.0f );
	Vector2D vel( 0.0f, 0.0f );
	KinematicUnit* pUnit = new KinematicUnit( pArrowSprite, pos, 1, vel, 0.0f, 200.0f, 10.0f );
	mpUnitManager->createPlayer(pUnit);

	//Make walls on all four sides
	Vector2D right(WIDTH, 0);
	Vector2D down(0, HEIGHT);
	right.normalize();
	down.normalize();

	/* Note:
	 *	For some reason, I can't get the right and bottom walls to work correctly
	 *		for now, they work because of the game's wrap around, but they cause
	 *		wierd issues when enabled.
	*/
	Wall* topWall = new Wall(Vector2D(0, 0), right, WIDTH);
	//Wall* bottomWall = new Wall(Vector2D(0, HEIGHT), right, WIDTH);
	Wall* leftWall = new Wall(Vector2D(0, 0), down, HEIGHT);
	//Wall* rightWall = new Wall(Vector2D(WIDTH, 0), down, HEIGHT);
	mpWallManager->addWall(topWall);
	//mpWallManager->addWall(bottomWall);
	mpWallManager->addWall(leftWall);
	//mpWallManager->addWall(rightWall);

	mpMenu = new Menu();

	return true;
}

void Game::cleanup()
{
	//delete units
	delete mpUnitManager;
	mpUnitManager = NULL;
	delete mpWallManager;
	mpWallManager = NULL;

	//delete the timers
	delete mpLoopTimer;
	mpLoopTimer = NULL;
	delete mpMasterTimer;
	mpMasterTimer = NULL;

	//delete the graphics system
	delete mpGraphicsSystem;
	mpGraphicsSystem = NULL;

	delete mpGraphicsBufferManager;
	mpGraphicsBufferManager = NULL;
	delete mpSpriteManager;
	mpSpriteManager = NULL;
	delete mpMessageManager;
	mpMessageManager = NULL;

	al_destroy_sample(mpSample);
	mpSample = NULL;

	delete mpMenu;
	mpMenu = NULL;

	delete mpInputManager;
	mpInputManager = NULL;

	//shutdown components
	al_uninstall_audio();
	al_shutdown_image_addon();
	al_shutdown_font_addon();
	al_shutdown_ttf_addon();
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_shutdown_primitives_addon();

}

void Game::beginLoop()
{
	mpLoopTimer->start();
}
	
void Game::processLoop()
{
	//update units
	mpUnitManager->Update( LOOP_TARGET_TIME/1000.0f );
	
	//draw background
	Sprite* pBackgroundSprite = mpSpriteManager->getSprite( BACKGROUND_SPRITE_ID );
	pBackgroundSprite->draw( *(mpGraphicsSystem->getBackBuffer()), 0, 0 );

	//draw units
	mpUnitManager->Draw( GRAPHICS_SYSTEM->getBackBuffer() );

	mpMessageManager->processMessagesForThisframe();

	mpInputManager->update();
		
	Vector2D mousePos = mpInputManager->getMousePos();
	std::string mousePosStr = std::to_string((int)mousePos.getX()) + ", " + std::to_string((int)mousePos.getY());
	mpGraphicsSystem->drawText(mousePos, mousePosStr);

	if (getMenu()->drawMenu())
	{
		int offset = 0;
		for (int i = 0; i < 5; i++)
		{
			std::string text = getMenu()->getOptionName(i) + ": " + std::to_string((int)getMenu()->getOptionValue(i));
			mpGraphicsSystem->drawText(Vector2D(0, offset), text, getMenu()->getSelected() == i);
			offset += 25;
		}
	}

	mpGraphicsSystem->swap();
}

bool Game::endLoop()
{
	//mpMasterTimer->start();
	mpLoopTimer->sleepUntilElapsed( LOOP_TARGET_TIME );
	return mShouldExit;
}

float genRandomBinomial()
{
	return genRandomFloat() - genRandomFloat();
}

float genRandomFloat()
{
	float r = (float)rand()/(float)RAND_MAX;
	return r;
}