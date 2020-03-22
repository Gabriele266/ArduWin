/*
Autore: Cavallo Gabriele
Versione: 1.3
Descrizione: file che contiene funzioni per la gestione della posizione
*/

#ifndef LOC_CPP
#define LOC_CPP



// Struttura che definisce la posizione
struct location {
	int x;
	int y;
};

// Incrementa una struttura location
static void inflate(signed int step, location lac) {
	lac.x += step;
	lac.y += step;
}


// Incrementa la x della posizione
static void increaseX(signed int step, location *loc) {
	loc->x += step;
}

static void increaseX(signed int step, location loc) {
	loc.x += step;
}

static void increaseY(signed int step, location *loc) {
	loc->y += step;
}

static void increaseY(signed int step, location loc) {
	loc.x += step;
}

static void normalize(location *loc) {
	if (loc->x > 19) {
		loc->x = 19;
	}
	if (loc->x < 0) {
		loc->x = 0;
	}
	if (loc->y < 0) {
		loc->y = 0;
	}
	if (loc->y > 3) {
		loc->y = 3;
	}
}

static int getX(location l) {
	return l.x;
}

static int getX(location *l) {
	return l->x;
}

static int getY(location l) {
	return l.y;
}

static int getY(location *l) {
	return l->y;
}

// Determina se il punto l esiste
static bool exists(location l) {
	if (l.x >= 0 && l.y >= 0) {
		return true;
	}
	else {
		return false;
	}
}

// Indica se cur si trova nell' area espressa da point
static bool isInArea(location cur, location __point, int size_x) {
	// Controllo che tutte le posizioni esistano
	if (exists(cur) && exists(__point)) {
		if (cur.x >= __point.x && cur.x <= (__point.x + size_x) && cur.y == __point.y) {
			return true;
		}
		else {
			return false;
		}
	}
}

// COnverte in striga una tupla
static char* toString(location loc, bool showLetters = true) {
	// Variabile da restituire
	char  result[20];
	// Se l'utente vuole le lettere
	if (showLetters) {
		// Copio la x
		itoa(loc.x, result, 10);
		strcat(result, "; ");
		itoa(loc.y, result, 10);
		strcat(result, ";");
	}
	else {

	}
}

/// Crea una location che parte a 0, 0
static location createLocation(){
    location loc;
    loc.x = 0;
    loc.y = 0;
    return loc;
}

static location createLocation(int x, int y) {
	location loc;
	loc.x = x;
	loc.y = y;
	return loc;
}

static location getLocationByPointer(location *ptr){
	location loc;
	loc.x = ptr->x;
	loc.y = ptr->y;

	return loc;
}



#endif

