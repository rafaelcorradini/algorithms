#include <stdio.h>
#include <stdlib.h>

#define FC 1
#define MVR 1

#define limite 1 // colocar limite de 10^6 iteracoes

typedef struct {
	int value;
	int x; // x of constraint
	int y; // y of constraint
	int con; // 1 - bigger; -1 - smaller; 0 - no constraint 
	int pre;
	int degree;
	int *fc;
} Square;

void printBoard(Square **board, int dim, int cnt, int *n) {
	int i, j;

	printf("\n%d: \n", cnt);
	if(*n > 1000000 && limite) {
		printf("Número de atribuicoes excede limite máximo\n");
	} else {
		for (i = 0; i < dim; i++) {
			for (j = 0; j < dim; j++) {
				printf("%d ", board[i][j].value);
			}
			printf("\n");
		}
	}
	
}

// increases(1) or decreases(-1) the column and row degree 
void degree(Square **board, int dim, int i, int j, int dir, int *max_i, int *max_j) {
	int c, x, y, flag = 1, degree = 0;

	*max_i = 0;
	*max_j = 0;

	if(dir == 0) {

		for (x = 0; x < dim; x++) {
			for (y = 0; y < dim; y++) {
				if(board[x][y].value == 0) {
					if(flag) {
						*max_i = x;
						*max_j = y;
						flag = 0;
					}

					if(board[x][y].degree > degree) {
						degree = board[*max_i][*max_j].degree;
						*max_i = x;
						*max_j = y;
					}	
				}
			}
		}
	} else {
		for (c = 0; c < dim; c++) {
			if(c != i) 
				board[c][j].degree += dir;
			if(c != j)
				board[i][c].degree += dir;

			if(board[i][c].degree > degree && board[i][c].value == 0 && !board[i][c].pre) {
				degree = board[*max_i][*max_j].degree;
				*max_i = i;
				*max_j = c;
			}

			if(board[c][j].degree > degree && board[c][j].value == 0 && !board[c][j].pre) {
				degree = board[*max_i][*max_j].degree;
				*max_i = c;
				*max_j = j;
			}
		}
	}
}

int getEmptySquare(Square **board, int dim, int *i, int *j, int *max_i, int *max_j) {
	int x, y, flag = 1;

	if(MVR) {
		(*i) = *max_i;
		(*j) = *max_j;

		if(board[*i][*j].value != 0) {
			degree(board, dim, *i, *j, 0, max_i, max_j);
			if(board[*i][*j].value != 0)
				return 0;
		}
	} else {
		do {
			if((*j) < dim-1) {
				(*j)++;
			} else {
				(*i)++;
				(*j) = 0;	
			}
			if((*i) >= dim)
				return 0;
		} while(board[*i][*j].value != 0);
	}

	

	return 1;
}


int setSquare(Square **board, int dim, int i, int j, int value, int *max_i, int *max_j) {
	int x, y, c;

	if(board[i][j].con != 0) {
		x = board[i][j].x;
		y = board[i][j].y;
		if(board[x][y].value != 0)
			if((board[i][j].con == -1 && value > board[x][y].value) || (board[i][j].con == 1 && value < board[x][y].value))
				return 0;
	}

	if(FC) {
		for(c = 0; c < dim; c++) {
			if(c != i)
				board[c][j].fc[value]++;
			if(c != j)
				board[i][c].fc[value]++;
		}
	} else {
		for(c = 0; c < dim; c++) {
			if(board[c][j].value == value || board[i][c].value == value) 
				return 0;
		}
	}


	board[i][j].value = value;

	if(MVR) 
		degree(board, dim, i, j, 1, max_i, max_j);

	return 1;
}

int back(Square **board, int dim, int i, int j, int *max_i, int *max_j, int *n) {
	int value, c, res;

	(*n)++;	

	if(*n > 1000000 && limite)
		return -1;

	if(!getEmptySquare(board, dim, &i, &j, max_i, max_j))
		return 1;
		

	for (value = 1; value <= dim; value++) {
		if((FC && board[i][j].fc[value] == 0) || !FC) {
			if (setSquare(board, dim, i, j, value, max_i, max_j)) {
				res = back(board, dim, i, j, max_i, max_j, n);

				if(res == -1)
					return -1;

				if(res)
					return 1;
				else {
					board[i][j].value = 0;

					if(MVR)
						degree(board, dim, i, j, -1, max_i, max_j);

					if(FC) {
						for(c = 0; c < dim; c++) {
							if(c != i)
								board[c][j].fc[value]--;
							if(c != j)
								board[i][c].fc[value]--;
						}
					}
				}
	
			}
		}
		
	}

	
	return 0;
}

int solve(Square **board, int dim, int *max_i, int *max_j, int *n) {
	return back(board, dim, 0, -1, max_i, max_j, n);
}

void freeBoard(Square **board, int dim) {
	int i,j;

	for (i = 0; i < dim; i++) {
		for (j = 0; j < dim; j++) {
			if(FC)
				free(board[i][j].fc);
		}
		free(board[i]);
	}
	free(board);
}



int main() {
	Square **board;
	int dim, con, i, j, x1, x2, y1, y2, c, *max_i, *max_j, value, *n, cnt, a;

	max_i = malloc(sizeof(int));
	max_j = malloc(sizeof(int));
	n = malloc(sizeof(int));

	scanf("%d", &cnt);
	for (a = 0; a < cnt; ++a) {
		*max_i = 0;
		*max_j = 0;
		*n = 0;

		scanf("%d %d", &dim, &con);

		board = (Square**) malloc(dim*sizeof(Square*));
		for (i = 0; i < dim; i++) {
			board[i] = (Square*) malloc(dim*sizeof(Square));
			for (j = 0; j < dim; j++) {
				scanf("%d", &board[i][j].value);

				board[i][j].degree = 0;
				board[i][j].con = 0;
				if(board[i][j].value == 0)
					board[i][j].pre = 0;
				else
					board[i][j].pre = 1;

				if(FC) {
					board[i][j].fc = (int*) malloc((dim+1)*sizeof(int));
					for (c = 1; c < dim+1; c++) {
						board[i][j].fc[c] = 0;
					}
				}
			}
		}

		if(FC) {
			for (i = 0; i < dim; i++) {
				for (j = 0; j < dim; j++) {
					value = board[i][j].value;
					if(value != 0) {
						for (c = 0; c < dim; c++) {
							board[i][c].fc[value]++;
							board[c][j].fc[value]++;
						}
					}
				}
			}
		}


		if(MVR) {
			for (i = 0; i < dim; i++) {
				for (j = 0; j < dim; j++) {
					if(board[i][j].value != 0) {
						degree(board, dim, i, j, 1, max_i, max_j);
					}
				}
			}
		}

		for (i = 0; i < con; i++) {
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			x1--;
			x2--;
			y1--;
			y2--;
			board[x1][y1].x = x2;
			board[x1][y1].y = y2;
			board[x1][y1].con = -1;
			board[x2][y2].x = x1;
			board[x2][y2].y = y1;
			board[x2][y2].con = 1;
		}

		solve(board, dim, max_i, max_j, n);

		printBoard(board, dim, a, n);
		freeBoard(board, dim);
	}

	free(n);
	free(max_i);
	free(max_j);	
}