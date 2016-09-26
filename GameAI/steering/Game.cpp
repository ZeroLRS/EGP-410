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
	,mpFont(NULL)
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

	//should be somewhere else!
	al_init_font_addon();
	if( !al_init_ttf_addon() )
	{
		printf( "ttf font addon not initted properly!\n" ); 
		return false;
	}

	//actually load the font
	mpFont = al_load_ttf_font( "cour.ttf", 20, 0 );
	if( mpFont == NULL )
	{
		printf( "ttf font file not loaded properly!\n" ); 
		return false;
	}

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

	Vector2D pos( 0.0f, 0.0f );
	Vector2D vel( 0.0f, 0.0f );
	KinematicUnit* pUnit = new KinematicUnit( pArrowSprite, pos, 1, vel, 0.0f, 200.0f, 10.0f );
	//We have to add the player first, because the construction of the others rely on it's location...
	mpUnitManager->pushUnit(pUnit, "player");
	
	Vector2D pos2( 1000.0f, 500.0f );
	Vector2D vel2( 0.0f, 0.0f );
	KinematicUnit* pAIUnit1 = new KinematicUnit( pEnemyArrow, pos2, 1, vel2, 0.0f, 180.0f, 100.0f );
	//give steering behavior
	pAIUnit1->dynamicArrive( pUnit ); 

	Vector2D pos3( 500.0f, 500.0f );
	KinematicUnit* pAIUnit2 = new KinematicUnit( pEnemyArrow, pos3, 1, vel2, 0.0f, 180.0f, 100.0f );
	//give steering behavior
	pAIUnit2->dynamicSeek( pUnit );  

	mpUnitManager->pushUnit(pAIUnit1, "AIUnit1");
	mpUnitManager->pushUnit(pAIUnit2, "AIUnit2");

	return true;
}

void Game::cleanup()
{
	//delete units
	delete mpUnitManager;
	mpUnitManager = NULL;

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
	al_destroy_font(mpFont);
	mpFont = NULL;

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

	//all this should be moved to InputManager!!!
	{
		//get mouse state
		ALLEGRO_MOUSE_STATE mouseState;
		al_get_mouse_state( &mouseState );

		//create mouse text
		stringstream mousePos;
		mousePos << mouseState.x << ":" << mouseState.y;

		//write text at mouse position
		al_draw_text( mpFont, al_map_rgb( 255, 255, 255 ), mouseState.x, mouseState.y, ALLEGRO_ALIGN_CENTRE, mousePos.str().c_str() );

		mpGraphicsSystem->swap();

		//get current keyboard state
		ALLEGRO_KEYBOARD_STATE keyState;
		al_get_keyboard_state( &keyState );
	}
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

/*#include "System.h"
#include "Game.h"
#include "GameMessageManager.h"
#include "PlayerMoveToMessage.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "KinematicUnit.h"
#include "Vector2D.h"
*/
/*Game* gpGame = NULL;

Game::Game()
:mpMessageManager(NULL)
,mFrameNum(0)
,mMarkedForExit(false)
{
}

Game::~Game()
{
	delete mpArrowBuffer;
	delete mpArrowSprite;
	delete mpEnemyArrowBuffer;
	delete mpEnemyArrowSprite;
	delete mpUnit;
	delete mpAIUnit;
	delete mpAIUnit2;
	delete mpMessageManager;
}

void Game::init()
{
	mpMessageManager = new GameMessageManager();

	mpArrowBuffer = new GraphicsBuffer( "arrow.bmp" );
	mpArrowSprite = new Sprite( mpArrowBuffer, 0, 0, 32, 32 );
	mpEnemyArrowBuffer = new GraphicsBuffer( "enemy-arrow.bmp" );
	mpEnemyArrowSprite = new Sprite( mpEnemyArrowBuffer, 0, 0, 32, 32 );
	
	Vector2D pos( 0.0f, 0.0f );
	Vector2D vel( 0.0f, 0.0f );
	mpUnit = new KinematicUnit( mpArrowSprite, pos, 1, vel, 0.0f, 200.0f, 10.0f );

	Vector2D pos2( 1000.0f, 500.0f );
	Vector2D vel2( 0.0f, 0.0f );
	mpAIUnit = new KinematicUnit( mpEnemyArrowSprite, pos2, 1, vel2, 0.0f, 180.0f, 100.0f );
	mpAIUnit->dynamicArrive( mpUnit ); 
	//mpAIUnit->arrive( mpUnit->getPosition() ); 

	Vector2D pos3( 500.0f, 500.0f );
	mpAIUnit2 = new KinematicUnit( mpEnemyArrowSprite, pos3, 1, vel2, 0.0f, 180.0f, 100.0f );
	mpAIUnit2->dynamicSeek( mpUnit );  
	//mpAIUnit2->seek( mpUnit->getPosition() );  
}

bool Game::update()
{
	mpUnit->update( LOOP_TARGET_TIME/1000.0f );
	mpUnit->draw( GRAPHICS_SYSTEM->getBackBuffer() );
	mpAIUnit->update( LOOP_TARGET_TIME/1000.0f );
	mpAIUnit->draw( GRAPHICS_SYSTEM->getBackBuffer() );
	mpAIUnit2->update( LOOP_TARGET_TIME/1000.0f );
	mpAIUnit2->draw( GRAPHICS_SYSTEM->getBackBuffer() );

	mpMessageManager->processMessagesForThisframe();

	//get input - should be moved someplace better
	if( mouse_b & 1 )//left mouse click
	{
		Vector2D pos( mouse_x, mouse_y );
		GameMessage* pMessage = new PlayerMoveToMessage( pos );
		MESSAGE_MANAGER->addMessage( pMessage, 0 );
	}

	mFrameNum++;
	return mMarkedForExit;
}*/