#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char name[100];
	int score;
	int matches;
	int win;
	int draw;
	int lose;
	int goals;
	int goals_c;
} Team;

typedef struct {
	char name[100];
	int n_teams;
	Team *teams;
} Tournament;


// comparison (1 - bigger; -1 - smaller; 0 - equal)
int cmp(Team *t1, Team *t2) {

	if(t1->score > t2->score) return 1;
	if(t1->score < t2->score) return -1;
	if(t1->win > t2->win) return 1;
	if(t1->win < t2->win) return -1;
	if(t1->goals - t1->goals_c > t2->goals - t2->goals_c) return 1;
	if(t1->goals - t1->goals_c < t2->goals - t2->goals_c) return -1;
	if(t1->goals > t2->goals) return 1;
	if(t1->goals < t2->goals) return -1;
	if(t1->matches > t2->matches) return 1;
	if(t1->matches < t2->matches) return -1;

	return strcmp(t2->name, t1->name);
	
}

void quickSort(Team *teams, int left, int right){
    int pivot = left, i, j;
    Team aux;  

    for(i = left+1; i <= right; i++){       
		j = i;                     
		if(cmp(&teams[pivot], &teams[j]) < 0) {  
			aux = teams[j];               
			while(j > pivot){          
				teams[j] = teams[j-1];     
				j--;                    
			}
			pivot++; 
			teams[j] = aux;                               
        }  
    }


	if(pivot-1 >= left)             
		quickSort(teams, left, pivot-1);   

	if(pivot+1 <= right)            
		quickSort(teams, pivot+1, right);   
     
}

void scanStr(char *str, char end, int size) {
	char ch;
	int i = 0;
	
	ch = getchar();
	while(ch == '\n' || ch == '\r')
		ch = getchar();

	do {
		str[i++] = ch;
		ch = getchar();
	} while(ch != '\n' && ch != '\r' && ch != end && ch != EOF && i < size);
	str[i] = '\0';
}

void setScores(Tournament *t, int n_games) {
	int i, j, score1, score2, team1_i, team2_i;
	char team1[30], team2[30], ch;

	for(i = 0; i < n_games; i++) {

		team1[0] = '\0';
		team2[0] = '\0';
		score1 = 0;
		score2 = 0;
		team1_i = -1;
		team2_i = -1;

		j = 0;
		scanStr(team1, '#', 30);

		j = 0;
		while((ch = getchar()) != '@' && j < 10) { 
			score1 *= 10;
			score1 += (int) ch - 48;
			j++;
		}

		j = 0;
		while((ch = getchar()) != '#' && j < 10) {
			score2 *= 10;
			score2 += (int) ch - 48;
			j++;
		}

		scanStr(team2, '\0', 30);

		for(j = 0; j < t->n_teams; j++) {
			if(strcmp(t->teams[j].name, team1) == 0)
				team1_i = j;
			else if(strcmp(t->teams[j].name, team2) == 0)
				team2_i = j;
		}

		if(score1 > score2) {
			t->teams[team1_i].score += 3;
			t->teams[team1_i].win++;
			t->teams[team2_i].lose++;
		} else if(score1 < score2) {
			t->teams[team2_i].score += 3;
			t->teams[team2_i].win++;
			t->teams[team1_i].lose++;
		} else {
			t->teams[team1_i].score++;
			t->teams[team2_i].score++;
			t->teams[team1_i].draw++;
			t->teams[team2_i].draw++;
		}

		t->teams[team1_i].matches++;
		t->teams[team2_i].matches++;
		
		t->teams[team1_i].goals += score1;
		t->teams[team1_i].goals_c += score2;

		t->teams[team2_i].goals += score2;
		t->teams[team2_i].goals_c += score1;
		

	}
	
}



int main() {
	int n_tour, n_teams, n_games, i, j;
	Tournament *t;

	scanf("%d", &n_tour);

	t = malloc(n_tour*sizeof(Tournament));

	for (i = 0; i < n_tour; i++) {

		scanStr(t[i].name, '\0', 100);
		
		scanf("%d", &n_teams);
		t[i].teams = malloc(n_teams*sizeof(Team));
		t[i].n_teams = n_teams;
		for (j = 0; j < n_teams; j++) {
			scanStr(t[i].teams[j].name, '\0', 30);

			t[i].teams[j].score = 0;
			t[i].teams[j].matches = 0;
			t[i].teams[j].win = 0;
			t[i].teams[j].draw = 0;
			t[i].teams[j].lose = 0;
			t[i].teams[j].goals = 0;
			t[i].teams[j].goals_c = 0;
		}

		scanf("%d", &n_games);
		setScores(&t[i], n_games);

		quickSort(t[i].teams, 0, n_teams-1);

		printf("%s\n", t[i].name);
		for (j = 0; j < n_teams; j++) {
			printf("%d) %s %dp, %dg (%d-%d-%d), %dgd (%d-%d)\n", (j+1), t[i].teams[j].name, t[i].teams[j].score, t[i].teams[j].matches, t[i].teams[j].win, t[i].teams[j].draw, t[i].teams[j].lose, t[i].teams[j].goals - t[i].teams[j].goals_c, t[i].teams[j].goals, t[i].teams[j].goals_c);			
		}

		free(t[i].teams);

		if(i < n_tour-1)
			printf("\n");
	}

	free(t);
}