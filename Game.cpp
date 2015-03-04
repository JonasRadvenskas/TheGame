#include "Game.h"

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	//pakraunamas SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		int flags = 0;
		if (fullscreen)
		{
			flags = SDL_WINDOW_FULLSCREEN;
		}
		// init the window
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (m_pWindow != 0) //Lango sukurimas
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if (m_pRenderer != 0) //Sukuriamas piesimo pavirsius
			{
				SDL_SetRenderDrawColor(m_pRenderer, 130, 5, 5, 255); //lango spalva.
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	ProgramRunning = true;
	// langas sudarytas, prasideda pagrindinis ciklas.
	//---
	//---
	//---RESURSU DIEGIMAS---
	//---
	//---
	//KRAUNA PAVEIKSLIUKUS
	if (!CTexture::Instance()->load("assets/background3_1.png", 0, m_pRenderer))
	{
		return false;
	}
	if (!CTexture::Instance()->load("assets/background3_2.png", 1, m_pRenderer))
	{
		return false;
	}
	if (!CTexture::Instance()->load("assets/background3_3.png", 2, m_pRenderer))
	{
		return false;
	}
	if (!CTexture::Instance()->load("assets/player_fighter.png", 3, m_pRenderer))
	{
		return false;
	}
	if (!CTexture::Instance()->load("assets/enemy2.png", 4, m_pRenderer))
	{
		return false;
	}
	if (!CTexture::Instance()->load("assets/explosion2.png", 5, m_pRenderer))
	{
		return false;
	}
	if (!CTexture::Instance()->load("assets/rocket.png", 6, m_pRenderer))
	{
		return false;
	}
	if (!CTexture::Instance()->load("assets/bullet1.png", 7, m_pRenderer))
	{
		return false;
	}
	if (!CTexture::Instance()->load("assets/medfighter.bmp", 8,m_pRenderer))
	{
		return false;
	}
	if (!CTexture::Instance()->load("assets/rocket_pav.bmp", 9, m_pRenderer))
	{
		return false;
	}
	pav_zaid.load(0, 0, 120, 85, 0, 0, 64, 68, width, height, 8);
	pav_raketa.load(0, 0, 21, 68, 810, 0, 30, 68, width, height, 9);
	m_player.load(0, 0, 120, 85, 5, 550, 120, 85, width, height, 3);
	fonas1.scrolling(width, height, 320, 200, 0, 3);
	fonas2.scrolling(width, height, 320, 200, 1, 1);
	fonas3.scrolling(width, height, 320, 200, 2, 0);
	//KURIA RAKETU MASYVA.
	for (i = 0; i < r_kiekis; i++)
	{
		raketos[i].load(0, 0, 63, 21, 0, 800, 126, 41, width, height, 6);
	}
	for (i = 0; i < r_kiekis; i++)
	{
		r_busena[i] = false;//nunulina raketu aktyvumo masyva
	}
	//KURIA KULKU MASYVA
	for (i = 0; i < k_kiekis; i++)
	{
		kulkos[i].load(0, 0, 32, 32, 1000, 500, 32, 32, width, height, 7);
	}
	for (i = 0; i < r_kiekis; i++)
	{
		k_busena[i] = false;//nunulina kulku aktyvumo masyva
	}
	//KURIA PRIESU VEKTORIU.
	spwn = height - 80;		//atsiradimo koordinaciu intervalas
	for (i = 0; i < priesu_kiekis; i++)
	{
		j = rand() % spwn;//nustato prieso atsiradimo tasko y koordinate
		priesai.push_back(new Enemy(0, 0, 64, 64, -200, j, 64, 64, width, height, 4));
	}
	for (i = 0; i < priesu_kiekis; i++)//nunulina priesu aktyvumo masyva
		p_busena[i] = 0;
	zaidejo_gyvybes = 5;//suteikiu zaidejui 5 gyvybes
	taskai = 0;			//istrinu taskus
	turimu_raketu_kiekis = 6;//pradinis turimu raketu kiekis
	kill_count = 0;		//istrinu nugaletuju kieki.
	//KRAUNA GARSA
	//load parametrai: failo vardas, nr garsu masyvuose
	sprogimas.Instance()->load("assets/explosion.wav", 0);//sprogimo garsas
	suvis_z.Instance()->load("assets/cannon_shot.wav",1); //zaidejo suvis
	suvis_p.Instance()->load("assets/laser_shot.wav",2);//prieso suvis
	g_o.Instance()->load("assets/game_over2.wav", 3);//zaidimo pabaigos garsas
	//SUDARO TEKSTUS
	std::string tekstas4 = "GAME OVER";
	game_over_text.kurti_teksta(m_pRenderer, "assets/bgothm.ttf", 100, tekstas4.c_str(), 10, 10, 255, 150, 250);
	std::string tekstas5 = "YOU WIN";
	you_win_text.kurti_teksta(m_pRenderer, "assets/bgothm.ttf", 100, tekstas5.c_str(), 10, 10, 255, 300, 250);
	return true;
}

void Game::update(int width, int height)//judesys
{
	//teksto apdorojimas
	life.trinti_teksta();
	score.trinti_teksta();
	rockets.trinti_teksta();
	std::string tekstas1 = std::to_string(zaidejo_gyvybes);
	life.kurti_teksta(m_pRenderer, "assets/bgothm.ttf", 64, tekstas1.c_str(), 200, 0, 50, 64, 0);
	std::string tekstas2 = std::to_string(taskai);
	score.kurti_teksta(m_pRenderer, "assets/bgothm.ttf", 64, tekstas2.c_str(), 200, 0, 50, 450, 0);
	std::string tekstas3 = std::to_string(turimu_raketu_kiekis);
	rockets.kurti_teksta(m_pRenderer, "assets/bgothm.ttf", 64, tekstas3.c_str(), 200, 0, 50, 840, 0);
	//paveiksliuku judesys
	fonas1.update();
	fonas2.update();
	fonas3.update();
	m_player.update();
	pav_zaid.update();
	pav_raketa.update();
	//priesu kulkos
	for (i = 0; i < priesai.size(); i++)
	{
		if ((i <= enemy_count) && (p_busena[i] == 0))
		{//kiekvienas priesas esantis ekrane
			for (j = 0; j < k_kiekis; j++)
			{
				if ((!kulkos[j].GetBulletBusena()) && (priesai[i]->GetShot()))
				{//jei priesas tos kulkos dar neisove, bet jis dabar sauna
					suvis_p.Instance()->playSound(2,2,0);
					k_busena[j] = true;
					kulkos[j].SetBulletBusena(true);
					//pradzioje kulka igauna prieso koordinates
					kulkos[j].SetBulletX(priesai[i]->GetEnemyX());
					kulkos[j].SetBulletY(priesai[i]->GetEnemyY()+16);
					priesai[i]->SetShot(false);//priesas pasidaro issoves
				}//tai kulka issauta

			}
		}
	}//tikrina kiekvienos kulkos situacija
	for (i = 0; i < k_kiekis; i++)
	{
		if (k_busena[i])
		{//judina kulka, jei ji dar turi teise skristi
			kulkos[i].update();
		}
		if (!kulkos[i].GetBulletBusena())//bet jei kulka psieke lango krasta
		{//uzkisa kulka uz ekrano ir parengia kitam suviui
			k_busena[i] = false;
			kulkos[i].SetBulletX(20);
			kulkos[i].SetBulletY(800);
		}
	}
	//zaidejo raketos
	for (i = 0; i < r_kiekis; i++)
	{//jei zaidejas isove, dar turi likusiu raketu ir raketa dar neisauta
		if ((!r_busena[i]) && (shoot)&&(turimu_raketu_kiekis>0))
		{//suvis- isauna tuo metu neskrendancia raketa
			suvis_z.Instance()->playSound(1, 1, 0);
			turimu_raketu_kiekis = turimu_raketu_kiekis - 1;
			r_busena[i] = true;			// tos raketos busena pasidaro "skrenda"
			raketos[i].SetRocketBusena(true);
			//pradzioje, raketa igauna zaidejo koordinates
			raketos[i].SetRocketY(m_player.getY()+20);
			shoot = false;				// suvis buvo ivykdytas
		}
		if ((r_busena[i]) && (raketos[i].GetRocketBusena()))
		{
			raketos[i].update();	//isautos raketos skrenda
			if (!raketos[i].GetRocketBusena())
			{
				r_busena[i] = false;	//isejusios uz ekrano raketos busena pasikeicia
				raketos[i].SetRocketY(800);//ir perkeliama uz ekrano
			}
		}
	}
	//susidurimu detekcija bei objektu mirtys: kulkos ir zaidejas.
	for (i = 0; i < k_kiekis; i++)
	{
		EnemyBullet *ptr = &kulkos[i];
		if ((k_busena[i]) && (kulkos[i].GetBulletBusena()))
		{//jei kulka aktyvuota ir judanti
			if (CCollision::Instance()->susidurimas_zaidejas_kulka(&m_player, ptr))
			{//susidurimo atveju zaidejas praranda gyvybe
				//o kulka tampa nebeaktyvi
				kulkos[i].SetBulletBusena(false);
				k_busena[i] = false;
				zaidejo_gyvybes = zaidejo_gyvybes - 1;
			}
		}
	}

	//susidurimu detekcija bei objektu mirtys: priesai, raketos ir zaidejas.
	for (int i = 0; i<priesai.size(); i++)
	{
		if (p_busena[i] == 0)	//jei priesas nr.i- nemirstantis ir nemires
		{
			for (j = 0; j < r_kiekis; j++)
			{
				Bullet *ptr = &raketos[j];
				if (CCollision::Instance()->susidurimas_priesas_raketa(priesai, i, ptr))
				{//jei priesas sprogsta nuo raketos
					sprogimas.Instance()->playSound(0, 0, 0);
					r_busena[j] = false;	//raketa dingsta
					raketos[j].SetRocketBusena(false);
					raketos[j].SetRocketX(0);
					raketos[j].SetRocketY(800);
					p_busena[i] = 1;	//tai priesas nr.i pasidaro mirstantis.
					priesai[i]->mirties_animacija(0);	//prasideda mirties animacija
					priesai[i]->SetDeath(false);//priesas dar nemires, bet jau mirstantis
				}
				else if (CCollision::Instance()->susidurimas_zaidejas_priesas(&m_player, priesai, i))//jei priesas sprogsta nuo zaidejo
				{
					p_busena[i] = 1;  //tai priesas nr.i pasidare mirstantis.
					priesai[i]->mirties_animacija(0);	//prasideda mirties animacija
					priesai[i]->SetDeath(false);
					suzeide = true;//registruojamas suzeidimas tam, kad butu atimta zaidejo gyvybe
				}
			}
		}
		if ((i <= enemy_count) && (p_busena[i] == 0))	//jeigu priesas turi teise buti ekrane, ir yra aktyvus
		{
			priesai[i]->update();			//tai vyksta paprastas prieso judejimas.
		}
		else if ((p_busena[i] == 1) && (priesai[i]->GetDeath()))         //jeigu priesas yra mirstantis, bet jo mirties animacija pasibaige
		{
			priesai[i]->SetEnemyX(-200);	// tai priesas uzkisamas uz ekrano
			p_busena[i] = 2;		//ir  pasidaro mires.
			kill_count++;
			taskai = taskai + 5;
			turimu_raketu_kiekis = turimu_raketu_kiekis + 2;
		}
		else if (p_busena[i] == 1)		//taciau, jei jis dar tik mirsta,
			priesai[i]->mirties_animacija((priesai[i]->GetEnemyK()) + 1);	// tai tesiama jo mirties animacija
		if (p_busena[i] == 2)				//jei priesas mires, tai
			priesai[i]->update_standby();		//priesas stovi uz ekrano.
	}
	if (suzeide)
	{
		zaidejo_gyvybes--;	//zaidejas nukencia nuo susidurimo
		suzeide = false;
	}
	if (zaidejo_gyvybes <= 0)
	{//restartuojama, jei zaidejas prarado visas gyvybes
		game_over_text.piesti_teksta(m_pRenderer);
		SDL_RenderPresent(m_pRenderer);
		g_o.Instance()->playSound(3,3,0);
		SDL_Delay(4000);
		restart_the_game(width,height);
	}
	if (kill_count == 100)
	{//restartuojama, kai zaidejas laimi
		you_win_text.piesti_teksta(m_pRenderer);
		SDL_RenderPresent(m_pRenderer);
		SDL_Delay(4000);
		restart_the_game(width, height);
	}
	enemy_count = enemy_count + 0.001;	//priesu atsiradimo laikmatis: didinama reiksme.
}

void Game::render()//piesimas
{
	SDL_RenderClear(m_pRenderer);

	fonas3.piesti(m_pRenderer);		//stacionarus fonas
	fonas2.piesti(m_pRenderer);		//letas fonas
	fonas1.piesti(m_pRenderer);		//greitas fonas
	m_player.piesti(m_pRenderer);	//animuotas zaidejas
	for (i = 0; i < r_kiekis; i++)	//piesia tik skrendancias raketas
	{
		if ((raketos[i].GetRocketBusena())&&(r_busena[i]))
		{
			raketos[i].piesti(m_pRenderer);
		}
	}
	for ( i = 0; i<priesai.size(); i++)//piesia visus skrendancius priesus arba ju sprogimus
	{
		priesai[i]->piesti(m_pRenderer);
	}
	for (i = 0; i < k_kiekis; i++)
	{
		if ((kulkos[i].GetBulletBusena()) && (k_busena[i]))
		{//piesia tik aktyvias kulkas
			kulkos[i].piesti(m_pRenderer);
		}
	}
	life.piesti_teksta(m_pRenderer);
	pav_zaid.piesti(m_pRenderer);
	score.piesti_teksta(m_pRenderer);
	rockets.piesti_teksta(m_pRenderer);
	pav_raketa.piesti(m_pRenderer);

	SDL_RenderPresent(m_pRenderer);
}


void Game::handleEvents()//vartotojo saveika
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			ProgramRunning = false;
			break;
		case SDL_KEYDOWN:
		{
							switch (event.key.keysym.sym)
							{
							case SDLK_SPACE:{
												   shoot = true;
												  break; }
							case SDLK_DOWN:{
											  m_player.SetMovedown(true);
											  break; }
							case SDLK_UP:{
											m_player.SetMoveup(true);
											break; }
							case SDLK_ESCAPE:{
												 ProgramRunning = false;
												 break; }
							default:
								break;}
							break;
		}
		case SDL_KEYUP:
		{
						  switch (event.key.keysym.sym)
						  {
						  case SDLK_SPACE:{
												shoot = false;
												break; }
						  case SDLK_DOWN:{
											 m_player.SetMovedown(false);
											break; }
						  case SDLK_UP:{
										   m_player.SetMoveup(false);
										  break; }
						  default:
							  break;
						  }
						  break;
		}
		default:
			break;
		}
	}
}


void Game::restart_the_game(int width, int height)
{
	int i,l;
	//restartuojami priesai
	for (std::vector<Enemy*>::iterator i = priesai.begin(); i != priesai.end(); i++)//istrinami
	{
		delete (*i);
	}
	priesai.clear();
	spwn = height - 80;
	for (i = 0; i < priesu_kiekis; i++)	//perrasomi
	{
		j = rand() % spwn;
		priesai.push_back(new Enemy(0, 0, 64, 64, -200, j, 64, 64, width, height, 4));
		priesai[i]->SetEnemyX(-100);
		p_busena[i] = 0;
		priesai[i]->SetShootCounter(0);
		priesai[i]->SetShot(false);
	}
	enemy_count = 0;
	//restartuojamos raketos
	for (i = 0; i < r_kiekis; i++)
	{
		raketos[i].SetRocketBusena(false);
		r_busena[i] = false;
		raketos[i].SetRocketX(0);
	}
	//restartuojamos kulkos
	for (i = 0; i < k_kiekis; i++)
	{
		kulkos[j].SetBulletBusena(false);
		k_busena[i] = false;
	}
	//restartuojamas zaidejas
	m_player.setY(550);
	zaidejo_gyvybes = 5;
	turimu_raketu_kiekis = 6;
	taskai = 0;
	kill_count = 0;
	suzeide = false;
}


void Game::clean()//programos sunaikinimas
{
	for (std::vector<Enemy*>::iterator i = priesai.begin(); i != priesai.end(); i++)//naikina visus priesus
	{
		delete (*i);
	}
	priesai.clear();
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}