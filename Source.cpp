#include<cstdio> 
#include<cstdlib> 
#include <ctime>
#include <cmath>
#include <windows.h>
#include "carrier.h"
#include "bed.h""
void print_rotation(int rotation){
	switch (rotation){
	case 1: printf(" Direction North \n"); break;
	case 2: printf(" Direction South \n"); break;
	case 3:printf(" Direction West \n"); break;
	case 4:printf(" Direction East \n"); break;
	}

}

void bed_in_matrix(int **mat, int *positionbed){
	mat[positionbed[0]][positionbed[1]]=2;
	mat[positionbed[2]][positionbed[3]] = 2;
	mat[positionbed[4]][positionbed[5]] = 2;
	mat[positionbed[6]][positionbed[7]] = 2;


}
void affiche_mat(int **mat, int l, int c, int currentX, int currentY, int goalX, int goalY, int *positionbed, int currentX2,int currentY2){
	//Afficher une matrice
	bed_in_matrix(mat, positionbed);

	int i, j;
	for (i = 0; i<l; i++)
	{
		for (j = 0; j<c; j++){
			printf("%d ", (mat[i][j]));
		}
		printf("\n");



	}


	for (i = 0; i<l; i++)
	{
		printf("|");
		for (j = 0; j<c; j++){
			if (mat[i][j] == 2)
				printf("  B  ");
			else
				if (mat[i][j] == 0 && (i != currentY || j != currentX) && (i != goalY || j != goalX) && (i != currentY2 || j != currentX2))
				printf("  *  ");
				else if (mat[i][j] == 1 && (i != currentY || j != currentX) && (i != goalY || j != goalX) && (i != currentY2 || j != currentX2))
				printf("  X  ");
			else
				if ((i == currentY && j == currentX) || (i == currentY2 && j == currentX2))
					printf("  C  ");
				else
					if (i == goalY && j == goalX)
						printf("  W  ");
		   

		}
		printf("|\n");


	}


}
int sizeY = 10;
int sizeX = 12;
int* astar(int **labdata2D, int initX, int  initY, int goalX, int goalY){
	// Renvoie un tableau d'instruction à suivre pour aller au tresoir
	struct
		NODE{
		int x, y;
		int cost;
		int heuri;
		int xp, yp; //noeud précédent
		int open; //1 si appartient à l'openlist
		int close; // 1 si appartient à l'closelist
	}node[10][12]; //Cree un tableau 2D de structure

	int z, e; // ON initialise toutes les cases
	for (z = 0; z<sizeY; z++)
	{
		for (e = 0; e<sizeX; e++)
		{
			node[z][e].open = 0;
			node[z][e].close = 0;
			node[z][e].heuri = 1;
			node[z][e].cost = 1;
		}

	}



	int mapositionx, mapositiony; // ma position actuelle 

		mapositionx = initX;
		mapositiony = initY;



	node[mapositiony][mapositionx].cost = 0;
	node[mapositiony][mapositionx].heuri = node[(mapositiony + sizeY) % sizeY][mapositionx].cost + abs((mapositiony + sizeY) % sizeY - goalY) + abs(mapositionx - goalX);
	node[mapositiony][mapositionx].open = 0;
	node[mapositiony][mapositionx].close = 1;






	// On ajoute à l'openliste les cases possible

	while (!(mapositionx == goalX && mapositiony == goalY)){ //tant qu'on a pas le trésor on continue à chercher
		// On regarde si la case qu'on veut ajouter à l'open liste n'est pas déja ou dans la close liste ou openliste, et qu'il n'y a pas de mur 
		if ((labdata2D[(mapositiony - 1 + sizeY) % sizeY][mapositionx] == 0) && (node[(mapositiony - 1 + sizeY) % sizeY][mapositionx].open != 1) && (node[(mapositiony - 1 + sizeY) % sizeY][mapositionx].close != 1))


		{

			// Case en haut
			node[(mapositiony - 1 + sizeY) % sizeY][mapositionx].cost = node[mapositiony][mapositionx].cost + 1; // on ajoute 1 au cout
			node[(mapositiony - 1 + sizeY) % sizeY][mapositionx].heuri = node[(mapositiony - 1 + sizeY) % sizeY][mapositionx].cost + abs((mapositiony - 1 + sizeY) % sizeY - goalY) + abs(mapositionx - goalX); // on change l'heuristique
			node[(mapositiony - 1 + sizeY) % sizeY][mapositionx].xp = mapositionx; //le precedent de cette case est donc ma position actuelle
			node[(mapositiony - 1 + sizeY) % sizeY][mapositionx].yp = mapositiony;
			node[(mapositiony - 1 + sizeY) % sizeY][mapositionx].open = 1; // on ajoute à l'openliste


		}



		if ((labdata2D[(mapositiony + 1 + sizeY) % sizeY][mapositionx] == 0) && (node[(mapositiony + 1 + sizeY) % sizeY][mapositionx].open != 1) && (node[(mapositiony + 1 + sizeY) % sizeY][mapositionx].close != 1)) {
			// Case en bas
			node[(mapositiony + 1 + sizeY) % sizeY][mapositionx].cost = node[mapositiony][mapositionx].cost + 1;// on ajoute 1 au cout
			node[(mapositiony + 1 + sizeY) % sizeY][mapositionx].heuri = node[(mapositiony - 1 + sizeY) % sizeY][mapositionx].cost + abs((mapositiony + 1 + sizeY) % sizeY - goalY) + abs(mapositionx - goalX); // on change l'heuristique
			node[(mapositiony + 1 + sizeY) % sizeY][mapositionx].xp = mapositionx;//le precedent de cette case est donc ma position actuelle
			node[(mapositiony + 1 + sizeY) % sizeY][mapositionx].yp = mapositiony;
			node[(mapositiony + 1 + sizeY) % sizeY][mapositionx].open = 1; // on ajoute à l'openliste
		}

		if ((labdata2D[mapositiony][(mapositionx - 1 + sizeX) % sizeX] == 0) && (node[mapositiony][(mapositionx - 1 + sizeX) % sizeX].open != 1) && (node[mapositiony][(mapositionx - 1 + sizeX) % sizeX].close != 1)) {
			// Case à gauche
			node[mapositiony][(mapositionx - 1 + sizeX) % sizeX].cost = node[mapositiony][mapositionx].cost + 1;// on ajoute 1 au cout
			node[mapositiony][(mapositionx - 1 + sizeX) % sizeX].heuri = node[mapositiony][(mapositionx - 1 + sizeX) % sizeX].cost + abs((mapositionx - 1 + sizeX) % sizeX - goalX) + abs(mapositiony - goalY);// on change l'heuristique
			node[mapositiony][(mapositionx - 1 + sizeX) % sizeX].xp = mapositionx; //le precedent de cette case est donc ma position actuelle
			node[mapositiony][(mapositionx - 1 + sizeX) % sizeX].yp = mapositiony;
			node[mapositiony][(mapositionx - 1 + sizeX) % sizeX].open = 1; // on ajoute à l'openliste

		}

		if ((labdata2D[mapositiony][(mapositionx + 1 + sizeX) % sizeX] == 0) && (node[mapositiony][(mapositionx + 1 + sizeX) % sizeX].open != 1) && (node[mapositiony][(mapositionx + 1 + sizeX) % sizeX].close != 1)) {
			// Case à droite
			node[mapositiony][(mapositionx + 1 + sizeX) % sizeX].cost = node[mapositiony][mapositionx].cost + 1;// on ajoute 1 au cout
			node[mapositiony][(mapositionx + 1 + sizeX) % sizeX].heuri = node[mapositiony][(mapositionx + 1 + sizeX) % sizeX].cost + abs((mapositionx + 1 + sizeX) % sizeX - goalX) + abs(mapositiony - goalY);// on change l'heuristique
			node[mapositiony][(mapositionx + 1 + sizeX) % sizeX].xp = mapositionx; //le precedent de cette case est donc ma position actuelle
			node[mapositiony][(mapositionx + 1 + sizeX) % sizeX].yp = mapositiony;
			node[mapositiony][(mapositionx + 1 + sizeX) % sizeX].open = 1; // on ajoute à l'openliste


		}
		int x, y;
		int minheuri = 100; //Etape où on recherce quoi mettre dans la close liste
		for (y = 0; y<sizeY; y++){

			for (x = 0; x<sizeX; x++)
			{
				if
					(node[y][x].open == 1)
				{
					if (node[y][x].heuri<minheuri) // on parcourt les cases et on cherche le minimum d'heurisitique
					{
						minheuri = node[y][x].heuri;
						mapositionx = x;
						mapositiony = y;
					}


				}

			}
		} // ON a trouvé quoi mettre dans la close liste
		node[mapositiony][mapositionx].open = 0;
		node[mapositiony][mapositionx].close = 1;

	}
	// On reconsititue le chemin en remontant précedent par précedent
	int xchemin, ychemin, tempx;
	int indice = 0;
	int costfinale = node[mapositiony][mapositionx].cost;
	//cout finale de notre chemin
	int *chemin = (int*)malloc(sizeof(int)*costfinale); // on cree le tableau de commande
	xchemin = mapositionx;
	ychemin = mapositiony;
	int in;


	for (in = 1; in <= costfinale; in++){

		if (xchemin - node[ychemin][xchemin].xp>0 && xchemin - node[ychemin][xchemin].xp<sizeX - 1)
		{
			chemin[costfinale - in] = 7; // grâce au calcul on sait qu'on est allé a droite, comme on reconstitue à l'envers on fait costfinale-in notre indice 


		}
		else {
			if (xchemin - node[ychemin][xchemin].xp<0 || xchemin - node[ychemin][xchemin].xp == sizeX - 1)
			{
				chemin[costfinale - in] = 6;
				// gauche

			}

			else {
				if (ychemin - node[ychemin][xchemin].yp>0 && ychemin - node[ychemin][xchemin].yp<sizeY - 1)
				{
					chemin[costfinale - in] = 5;
					// en bas


				}
				else {
					chemin[costfinale - in] = 4;
					// en haut	
				}
			}

		}
		tempx = xchemin;
		xchemin = node[ychemin][xchemin].xp;
		ychemin = node[ychemin][tempx].yp;
	}


	for (indice = 0; indice<costfinale; indice++){
		printf("chemin[%d]=%d\n", indice, chemin[indice]);
	}
	return chemin;

}
int **make2D(int*labData, int sizeX, int sizeY){
	int **labdata2D = (int **)malloc(sizeof(int*)*sizeY);
	int i, j, k;
	// Transforme le tableau en 2D
	k = 0;
	for (i = 0; i<sizeY; i++){
		labdata2D[i] = (int *)malloc(sizeof(int)*sizeX);
		for (j = 0; j<sizeX; j++){

			labdata2D[i][j] = labData[k];
			printf("labdata[%d]=%d\n", k, labdata2D[i][j]);

			k++;
		}

	}
///	affiche_mat(labdata2D, sizeY, sizeX, 0, 0, 1, 1);


	return labdata2D;
}

int main(){
	int*	labData = (int*)calloc(sizeX * sizeY, sizeof(int));
	int i;
	for (i = 0; i < sizeX; i++)    labData[i] = 1;
	for (i = 0; i < sizeX; i++)    labData[sizeX*i + (sizeX - 1)] = 1;
	for (i = 0; i < sizeX; i++)    labData[sizeX*(i)] = 1;
	for (i = 0; i < sizeX; i++)    labData[(sizeY - 1)*sizeX + i] = 1;
	srand(time(NULL));
	int goalX = (rand() % (sizeX - 3)) + 1;
	int goalY = (rand() % (sizeY - 3)) + 1;
	int myX = (rand() % (sizeX - 3)) + 1;
	int myY = (rand() % (sizeY - 3)) + 1;

	int **tabun = make2D(labData, sizeX, sizeY);
	int positionbed[8] = { 5,5 , 5,7, 6,5, 6, 7 };
	Bed theBed = Bed(positionbed, 70, 150);
	Carrier firstcarrier = Carrier(myX, myY, 37, 44, 1);
	int *leftup = theBed.get_up_left_corner();
	int *leftdown = theBed.get_down_left_corner();
	int *rightup = theBed.get_up_right_corner();
	int *rightdown = theBed.get_down_right_corner();
	int mindistance = abs(leftup[1] - myX) + abs(leftup[0] - myY);
	goalX = leftup[1];
	goalY = leftup[0];
	printf("leftdown Y  %d leftdown X  %d \n", leftdown[1], leftdown[0]);

	
	if (mindistance> abs(leftdown[1] - myX) + abs(leftdown[0] - myY)){
		goalX = leftdown[1];
		goalY = leftdown[0];
		mindistance = abs(leftdown[1] - myX) + abs(leftdown[0] - myY);
	}
	if (mindistance> abs(rightup[1] - myX) + abs(rightup[0] - myY)){
		goalX = rightup[1];
		goalY = rightup[0];
		mindistance = abs(rightup[1] - myX) + abs(rightup[0] - myY);

	}
	if (mindistance> abs(rightdown[1] - myX) + abs(rightdown[0] - myY)){
		goalX = rightdown[1];
		goalY = rightdown[0];
		mindistance = abs(rightdown[1] - myX) + abs(rightdown[0] - myY);

	}
	
	///abs((mapositiony + sizeY) % sizeY - goalY) + abs(mapositionx - goalX);
	int *chemin = astar(tabun, myX, myY, goalX, goalY);

	printf("Respect thats all I ask for goalY %d goalX %d  \n", goalY, goalX);
	affiche_mat(tabun, sizeY, sizeX, myX, myY, goalX, goalY, positionbed, 5, 5);
	int step=0; // wil

	int cpt = 0;
	bool wemove = false;
	do {
		switch (chemin[cpt])
		{
			
		case 4:
			if (firstcarrier.get_rotation() == 1 || firstcarrier.get_rotation() == 2){
				myY = (myY + sizeY - 1) % sizeY;
				printf("X %d ", myX);
				printf("Y %d ", myY);
				if (firstcarrier.get_rotation() == 1) printf("Move Forward"); else printf("Move Backward");
				wemove = true;
				print_rotation(firstcarrier.get_rotation());
				printf("Number of step :%d\n", step++);
				break;
			
			}
			else {
				firstcarrier.set_rotation(1);
				printf("X %d ", myX);
				printf("Y %d ", myY);
				printf("Rotation of 45 degree");
				print_rotation(firstcarrier.get_rotation());
				printf("Number of step :%d\n", step++);

				break;

			}
			 
		case 5:
			if (firstcarrier.get_rotation() == 1 || firstcarrier.get_rotation() == 2){
				myY = (myY + sizeY + 1) % sizeY;
				printf("X %d ", myX);
				printf("Y %d ", myY);
				if (firstcarrier.get_rotation() == 2) printf("Move Forward"); else printf("Move Backward");
				wemove = true;
				print_rotation(firstcarrier.get_rotation());
				printf("Number of step :%d\n", step++);

				break;

			}
			else {
				firstcarrier.set_rotation(2);
				printf("X %d ", myX);
				printf("Y %d ", myY);
				printf("Rotation of 45 degree");
				print_rotation(firstcarrier.get_rotation());
				printf("Number of step :%d\n", step++);

				break;

			}

		case 6:
			if (firstcarrier.get_rotation() == 3 || firstcarrier.get_rotation() == 4){
				myX = (myX + sizeX - 1) % sizeX;
				printf("X %d ", myX);
				printf("Y %d ", myY);
				if (firstcarrier.get_rotation() == 3) printf("Move Forward"); else printf("Move Backward");
				wemove = true;
				print_rotation(firstcarrier.get_rotation());
				printf("Number of step :%d\n", step++);

				break;

			}
			else {
				firstcarrier.set_rotation(3);
				printf("X %d ", myX);
				printf("Y %d ", myY);
				printf("Rotation of 45 degree");
				print_rotation(firstcarrier.get_rotation());
				printf("Number of step :%d\n", step++);

				break;

			}

		case 7:
			if (firstcarrier.get_rotation() == 3 || firstcarrier.get_rotation() == 4){
				myX = (myX + sizeX + 1) % sizeX;
				printf("X %d ", myX);
				printf("Y %d ", myY);
				if (firstcarrier.get_rotation() == 4) printf("Move Forward"); else printf("Move Backward");
				wemove = true;
				print_rotation(firstcarrier.get_rotation());
				printf("Number of step :%d\n", step++);

				break;

			}
			else {
				firstcarrier.set_rotation(4);
				printf("X %d ", myX);
				printf("Y %d ", myY);
				printf("Rotation of 45 degree");
				print_rotation(firstcarrier.get_rotation());
				printf("Number of step :%d\n", step++);

				break;

			}

		}
		//getchar();
		Sleep(2000);
		///system("cls");
		printf("just before X %d\n", myX);
		printf("just before Y %d\n", myY);
		affiche_mat(tabun, sizeY, sizeX, myX, myY, goalX, goalY, positionbed,5,5);
		if(wemove==true) cpt++;
		wemove = false;
	} while (myX != goalX || myY != goalY);

	return 0;
}



