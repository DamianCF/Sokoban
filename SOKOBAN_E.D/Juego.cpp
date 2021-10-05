#include "Juego.h"
#include "Menu.h"

Juego::~Juego()
{
}

Juego::Juego(int ancho, int alto, string titu)
{
	pantallaJuego = new RenderWindow(VideoMode(ancho, alto), titu);

	texturaFondo = new Texture;
	fondoPantalla = new Sprite;
	texturaFondo->loadFromFile("resource/fondoLadrillos.jpg");
	fondoPantalla->setTexture(*texturaFondo);
	fondoPantalla->setScale(((float)pantallaJuego->getSize().x / fondoPantalla->getTexture()->getSize().x), ((float)pantallaJuego->getSize().y / fondoPantalla->getTexture()->getSize().y));

	/*
	Tmuros = new Texture;
	Tmuros->loadFromFile("resource/1.png");
	IntRect posicion(1408,768 , 128, 128);
	Smuro = new Sprite;
	Smuro->setTextureRect(posicion);
	Smuro->setTexture(*Tmuros);*/
	//Smuro->setScale(800.f / Smuro->getTexture()->getSize().x, 400.f / Smuro->getTexture()->getSize().y);
	//Smuro->setPosition(580, 200);

	evento = new Event;

	fuente = new Font();
	fuente->loadFromFile("fonts/PressStart2P-Regular.ttf");


	label1 = new Text();
	label1->setFont(*fuente);
	label1->setFillColor(Color::White);
	label1->setString("JUDANDO...");
	label1->setCharacterSize(40);
	label1->setPosition(300, 100);

	gameloop();
}

void Juego::gameloop()
{

	crearGrid();

	while (pantallaJuego->isOpen())
	{
		ejecutar();
		dibujar();
	}
}

void Juego::dibujar()
{



}

void Juego::ejecutar()
{
	while (pantallaJuego->pollEvent(*evento))
	{
		if (evento->type == Event::Closed)
		{
			pantallaJuego->close();
			exit(1);
		}
		if (evento->type == Event::KeyReleased)
		{
			if (evento->key.code == Keyboard::Escape)
			{
				Menu* backmain;
				pantallaJuego->close();
				backmain = new Menu(960, 540, "SOKOBAN");
			}
			if (evento->key.code == Keyboard::W || evento->key.code == Keyboard::Up)
			{
				Mover();
			}
			if (evento->key.code == Keyboard::D || evento->key.code == Keyboard::Right)
			{
				moverDerecha();
			}
			if (evento->key.code == Keyboard::S || evento->key.code == Keyboard::Down)
			{
<<<<<<< Updated upstream
				moverAbajo();
=======
				moverIzquierda();
			}
			if (evento->key.code == Keyboard::A)
			{
				moverDerecha();
>>>>>>> Stashed changes
			}
			if (evento->key.code == Keyboard::Left)
			{
				moverIzquierda();
			}

		}
	}
}

void Juego::crearGrid()
{
	pantallaJuego->draw(*fondoPantalla);

	obj = new ListaOrtogonal();
	obj->cargarNivel("Mapas/Nivel1.txt");
	obj->cargarLista(9, 9, head);
	cargaMapa(head);
	cout << "Base cargada";
	pantallaJuego->display();
}

void Juego::actualizaMapa(char caracter, float x, float y, Texture* Tmuros, Sprite* Smuro) {
	
	//$ cajas
	if (caracter == '$') {
		IntRect posicion(128, 256, 128, 128);
		Smuro->setTextureRect(posicion);
	}

	//@ personaje
	if (caracter == '@') {
		IntRect posicion(0, 640, 128, 128);
		Smuro->setTextureRect(posicion);
	}
	if (caracter == 'X') {
		IntRect posicion(0, 640, 128, 128);
		Smuro->setTextureRect(posicion);
	}

	Smuro->setPosition(x, y);
	pantallaJuego->draw(*Smuro);
}

void Juego::cargaBaseMapa(char caracter, float x, float y, Texture* Tmuros, Sprite* Smuro) {

	IntRect posicion(1408, 768, 128, 128);
	Smuro->setTextureRect(posicion);
	Smuro->setPosition(x, y);
	pantallaJuego->draw(*Smuro);

	//# paredes
	if (caracter == '#') {
		IntRect posicion(1152, 768, 128, 128);
		Smuro->setTextureRect(posicion);
	}
	//. metas
	if (caracter == '.') {
		IntRect posicion(1408, 896, 128, 128);
		Smuro->setTextureRect(posicion);
	}
	if (caracter == 'M') {
		IntRect posicion(512, 256, 128, 128);
		Smuro->setTextureRect(posicion);
	}
	Smuro->setPosition(x, y);
	pantallaJuego->draw(*Smuro);
}

void Juego::cargaMapa(Nodo* head) {

	cout << "cargar mapa" << endl;
	
	
	texturaFondo->loadFromFile("resource/fondoLadrillos.jpg");
	fondoPantalla->setTexture(*texturaFondo);
	fondoPantalla->setScale(((float)pantallaJuego->getSize().x / fondoPantalla->getTexture()->getSize().x), ((float)pantallaJuego->getSize().y / fondoPantalla->getTexture()->getSize().y));
	pantallaJuego->draw(*fondoPantalla);

	Tmuros = new Texture();
	Smuro = new Sprite;

	Tmuros->loadFromFile("resource/1.png");
	Smuro->setTexture(*Tmuros);
	Smuro->setScale(800.f / Smuro->getTexture()->getSize().x, 400.f / Smuro->getTexture()->getSize().y);

	Nodo* aux1 = NULL, * aux2 = NULL, * aux3 = NULL ;

	float x = 200;
	float y = 50;
	if (head != NULL)
	{
		aux1 = head;
		while (aux1 != NULL)
		{
			aux2 = aux1;
			while (aux2 != NULL)
			{
				cargaBaseMapa(aux2->getDato(), x, y, Tmuros, Smuro);
				actualizaMapa(aux2->getDato(), x, y, Tmuros, Smuro);
				
				aux2 = aux2->getSig();
				x = x + 62;
			}
			x = 200;
			aux1 = aux1->getAbajo();
			y = y + 50;
		}
	}
}

void Juego::Mover()
{
	Nodo* p = NULL, * q = NULL,*actual = NULL, *arriba = NULL;
	if (head != NULL)
	{
		p = head;
		while (p != NULL)
		{
			q = p;
			while (q != NULL)
			{
				if (q->getDato() == '@')
				{
					actual = q;
					cout<<"encontrado"<<endl;
				}
				if (q->getDato() == 'X')
				{
					actual = q;
					cout << "encontrado" << endl;
				}
				q = q->getSig();
			}
			p = p->getAbajo();
		}
	}
	else
		cout << "Lista vacia...";

	arriba = actual->getArriba();

	//=============ARRIBA CON CAJA====================//
	if (arriba->getDato() == '$' && arriba->getArriba()->getDato() == '0' && actual->getDato() == 'X') {    //Si personaje tiene arriba caja y hay espacio...
		arriba->setDato('@');
		arriba->getArriba()->setDato('$');
		actual->setDato('.');
		cout << "arriba" << endl;
	}
	if (arriba->getDato() == '$' && arriba->getArriba()->getDato() == '0') {    //Si personaje tiene arriba caja y hay espacio...
		arriba->setDato('@');
		arriba->getArriba()->setDato('$');
		actual->setDato('0');
		cout << "arriba" << endl;
	}
	if (arriba->getDato() == '$' && arriba->getArriba()->getDato() == '.') {    //Si personaje tiene arriba caja y siguiente es meta...
		arriba->setDato('@');
		arriba->getArriba()->setDato('M');
		actual->setDato('0');
		cout << "arriba" << endl;
	}
	if (arriba->getDato() == 'M' && arriba->getArriba()->getDato() == '0') {    //Si personaje tiene arriba caja y siguiente es meta...
		arriba->setDato('X');
		arriba->getArriba()->setDato('$');
		actual->setDato('0');
		cout << "arriba" << endl;
	}
	//=============ARRIBA SIN CAJA====================//
	if (actual->getDato() == 'X' && arriba->getDato() != '#') {//Si personaje est� en meta pero arriba hay muro no suba...
		arriba->setDato('@');
		actual->setDato('.');
		cout << "arriba" << endl;
	}
	if (arriba->getDato() == '0' ) {			//Si arriba de personaje es vac�o
		arriba->setDato(actual->getDato());
		actual->setDato('0');
		cout << "arriba" << endl;
	}
	if (arriba->getDato() == '.') {    //Si arriba de personaje hay meta setea X para saber que est� sobre...
		arriba->setDato('X');
		actual->setDato('0');
		cout << "arriba" << endl;
	}

	obj->desplegar(head);
	cargaMapa(head);
	pantallaJuego->display();
}

void Juego::moverDerecha()
{
	Nodo* p = NULL, * q = NULL, * actual = NULL, * derecha = NULL;
	if (head != NULL)
	{
		p = head;
		while (p != NULL)
		{
			q = p;
			while (q != NULL)
			{
				if (q->getDato() == '@')
				{
					actual = q;
					cout << "encontrado" << endl;
				}
				if (q->getDato() == 'X')
				{
					actual = q;
					cout << "encontrado" << endl;
				}
				q = q->getSig();
			}
			p = p->getAbajo();
		}
	}
	else
		cout << "Lista vacia...";

	derecha = actual->getSig();

	//=============ARRIBA CON CAJA====================//
	if (derecha->getDato() == '$' && derecha->getSig()->getDato() == '0' && actual->getDato() == 'X') {    //Si personaje tiene arriba caja y hay espacio...
		derecha->setDato('@');
		derecha->getSig()->setDato('$');
		actual->setDato('.');
		cout << "derecha" << endl;
	}
	if (derecha->getDato() == '$' && derecha->getSig()->getDato() == '0') {    //Si personaje tiene arriba caja y hay espacio...
		derecha->setDato('@');
		derecha->getSig()->setDato('$');
		actual->setDato('0');
		cout << "derecha" << endl;
	}
	if (derecha->getDato() == '$' && derecha->getSig()->getDato() == '.') {    //Si personaje tiene arriba caja y siguiente es meta...
		derecha->setDato('@');
		derecha->getSig()->setDato('M');
		actual->setDato('0');
		cout << "arriba" << endl;
	}
	if (derecha->getDato() == 'M' && derecha->getSig()->getDato() == '0') {    //Si personaje tiene arriba caja y siguiente es meta...
		derecha->setDato('X');
		derecha->getSig()->setDato('$');
		actual->setDato('0');
		cout << "derecha" << endl;
	}
	//=============ARRIBA SIN CAJA====================//
	if (actual->getDato() == 'X' && derecha->getDato() != '#') {//Si personaje est� en meta pero arriba hay muro no suba...
		derecha->setDato('@');
		actual->setDato('.');
		cout << "derecha" << endl;
	}
	if (derecha->getDato() == '0') {			//Si arriba de personaje es vac�o
		derecha->setDato(actual->getDato());
		actual->setDato('0');
		cout << "derecha" << endl;
	}
	if (derecha->getDato() == '.') {    //Si arriba de personaje hay meta setea X para saber que est� sobre...
		derecha->setDato('X');
		actual->setDato('0');
		cout << "derecha" << endl;
	}

	obj->desplegar(head);
	cargaMapa(head);
	pantallaJuego->display();
}
<<<<<<< Updated upstream
void Juego::moverAbajo()
{
	Nodo* p = NULL, * q = NULL, * actual = NULL, * Abajo = NULL;
=======

void Juego::moverIzquierda()
{
	Nodo* p = NULL, * q = NULL, * actual = NULL, * izquierda = NULL;
>>>>>>> Stashed changes
	if (head != NULL)
	{
		p = head;
		while (p != NULL)
		{
			q = p;
			while (q != NULL)
			{
				if (q->getDato() == '@')
				{
					actual = q;
					cout << "encontrado" << endl;
				}
				if (q->getDato() == 'X')
				{
					actual = q;
					cout << "encontrado" << endl;
				}
				q = q->getSig();
			}
			p = p->getAbajo();
		}
	}
	else
		cout << "Lista vacia...";

<<<<<<< Updated upstream
	Abajo = actual->getAbajo();

	//=============ARRIBA CON CAJA====================//
	if (Abajo->getDato() == '$' && Abajo->getAbajo()->getDato() == '0' && actual->getDato() == 'X') {    //Si personaje tiene Abajo caja y hay espacio...
		Abajo->setDato('@');
		Abajo->getAbajo()->setDato('$');
		actual->setDato('.');
		cout << "Abajo" << endl;
	}
	if (Abajo->getDato() == '$' && Abajo->getAbajo()->getDato() == '0') {    //Si personaje tiene Abajo caja y hay espacio...
		Abajo->setDato('@');
		Abajo->getAbajo()->setDato('$');
		actual->setDato('0');
		cout << "Abajo" << endl;
	}
	if (Abajo->getDato() == '$' && Abajo->getAbajo()->getDato() == '.') {    //Si personaje tiene Abajo caja y siguiente es meta...
		Abajo->setDato('@');
		Abajo->getAbajo()->setDato('M');
		actual->setDato('0');
		cout << "Abajo" << endl;
	}
	if (Abajo->getDato() == 'M' && Abajo->getAbajo()->getDato() == '0') {    //Si personaje tiene Abajo caja y siguiente es meta...
		Abajo->setDato('X');
		Abajo->getAbajo()->setDato('$');
		actual->setDato('0');
		cout << "Abajo" << endl;
	}
	//=============ARRIBA SIN CAJA====================//
	if (actual->getDato() == 'X' && Abajo->getDato() != '#') {//Si Abajo est� en meta pero arriba hay muro no suba...
		Abajo->setDato('@');
		actual->setDato('.');
		cout << "Abajo" << endl;
	}
	if (Abajo->getDato() == '0') {			//Si Abajo de personaje es vac�o
		Abajo->setDato(actual->getDato());
		actual->setDato('0');
		cout << "Abajo" << endl;
	}
	if (Abajo->getDato() == '.') {    //Si Abajo de personaje hay meta setea X para saber que est� sobre...
		Abajo->setDato('X');
		actual->setDato('0');
		cout << "Abajo" << endl;
=======
	izquierda = actual->getAnt();

	//=============IZQUIERDA CON CAJA====================//
	if (izquierda->getDato() == '$' && izquierda->getAnt()->getDato() == '0' && actual->getDato() == 'X') {    //Si personaje tiene IZQUIERDA caja y hay espacio...
		izquierda->setDato('@');
		izquierda->getAnt()->setDato('$');
		actual->setDato('.');
		cout << "izquierda" << endl;
	}
	if (izquierda->getDato() == '$' && izquierda->getAnt()->getDato() == '0') {    //Si personaje tiene IZQUIERDA caja y hay espacio...
		izquierda->setDato('@');
		izquierda->getAnt()->setDato('$');
		actual->setDato('0');
		cout << "derecha" << endl;
	}
	if (izquierda->getDato() == '$' && izquierda->getAnt()->getDato() == '.') {    //Si personaje tiene IZQUIERDA caja y siguiente es meta...
		izquierda->setDato('@');
		izquierda->getAnt()->setDato('M');
		actual->setDato('0');
		cout << "izquierda" << endl;
	}
	if (izquierda->getDato() == 'M' && izquierda->getAnt()->getDato() == '0') {    //Si personaje tiene IZQUIERDA caja y siguiente es meta...
		izquierda->setDato('X');
		izquierda->getAnt()->setDato('$');
		actual->setDato('0');
		cout << "derecha" << endl;
	}
	//=============IZQUIERDA SIN CAJA====================//
	if (actual->getDato() == 'X' && izquierda->getDato() != '#') {//Si personaje est� en meta pero IZQUIERDA hay muro no avence...
		izquierda->setDato('@');
		actual->setDato('.');
		cout << "izquierda" << endl;
	}
	if (izquierda->getDato() == '0') {			//Si IZQUIERDA de personaje es vac�o
		izquierda->setDato(actual->getDato());
		actual->setDato('0');
		cout << "izquierda" << endl;
	}
	if (izquierda->getDato() == '.') {    //Si IZQUIERDA de personaje hay meta setea X para saber que est� sobre...
		izquierda->setDato('X');
		actual->setDato('0');
		cout << "derecha" << endl;
>>>>>>> Stashed changes
	}

	obj->desplegar(head);
	cargaMapa(head);
	pantallaJuego->display();
<<<<<<< Updated upstream
}
=======
}
>>>>>>> Stashed changes
