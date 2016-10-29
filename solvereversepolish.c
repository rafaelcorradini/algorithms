#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// Estrutura Pilha
typedef union {
	double f;
	char c;
} Element;

struct node {
	struct node *next;
	Element el;
	int type; 		// 0 - double; 1 - char (tipo que será usado no Element do node)
};

typedef struct node Node;

typedef struct {
	Node *top;
	int n;
} Stack;


Stack *init() {
	Stack *q;

	q = malloc(sizeof(Stack));
	q->n = 0;
	q->top = NULL;
	return q;
}

int isEmpty(Stack *q) {
	if(q->n > 0)
		return 0;
	return 1;
}

int push(Stack *q, Element el, int type) {
	Node *n;

	if((n = malloc(sizeof(Node))) == NULL)
		return 0;

	n->el = el;
	n->type = type;

	if(isEmpty(q))
		n->next = NULL;
	else
		n->next = q->top;

	q->top = n;
	q->n++;
	
	return 1;
}

Node *top(Stack *q) {
	if(isEmpty(q))
		return NULL;
	return q->top;
}

Element pop(Stack *q) {
	Node *aux = q->top;
	Element el;

	if(isEmpty(q))
		return el;

	el = q->top->el;

	if(q->n > 1) {
		q->top = q->top->next;
	} else {
		q->top = NULL;
	}
	free(aux);
	q->n--;

	return el;
}

void printStack(Stack *q) {
	Node *n;
	for(n = q->top; n != NULL; n = n->next) {
		if(n->type)
			printf("%c", n->el.c);
		else
			printf("%f", n->el.f);
		
	}
}

int freeStack(Stack *q) {
	Node *n = q->top;
	Node *aux;

	while(n != NULL) {
		aux = n->next;
		free(n);
		n = aux;
		
	}
	free(q);
	return 1;
}

// Fim da Estrutura Pilha



// Cria um vetor com todos os números reais(doubles) que estão na string
// e Troca os números na string pelo indíce do vetor criado.
double *fix(char *e, int size) {
	int z = 0, i = 0, is_dec = 0, is_n = 0;
	double res = 0, c = 0, *n;

	n = malloc(size*sizeof(double));

	while(i < size) {
		if((e[i] > 47 && e[i] < 58) || e[i] == '.') {
			c = (int) e[i] - 48;

			if(e[i] == '.') {
				is_dec = 1;
			}

			if(is_dec == 0) {
				if(is_n == 0)
					res = c;
				else
					res = res*10 + c;
			} else if(e[i] != '.') {
				res = res+c/pow(10, is_dec++);
			}

			e[i] = (char)z+48;

			is_n = 1;
		} else {
			is_dec = 0;
			is_n = 0;
		}
		

		if(i > 0)
			if(is_n == 0 && (e[i-1] > 47 && e[i-1] < 58)) 
				n[z++] = res;
		i++;
	}


	if(e[i-1] > 47 && e[i-1] < 58) 
		n[z++] = res;

	return n;
}

// verifica a prioridade do operador, retorna 1 caso a tenha prioridade sobre b
// 2 caso b tenha prioridade sobre a, e 0 caso tenham a mesma prioridade
int precedence(char a, char b) {
	if((a == '+' || a == '-') && (b == '*' || b == '/'))
		return -1;
	else if((b == '+' || b == '-') && (a == '*' || a == '/'))
		return 1;
	else 
		return 0;
}

// Coverte a expressão para uma Notação Polonesa Inversa
Stack *covertToPolish(char *e, int size) {
	Stack *tokens;
	int i = 0, z = -1, neg = 0;
	double *n = fix(e, size);
	Stack *out;
	Element el;

	tokens = init();
	out = init();

	while(i < size) {
		if(e[i] > 47 && e[i] < 58) {
			if(z != (e[i] - '0')) {
				z = (e[i] - '0');
				
				if(neg) {
					el.f = (-1)*n[z];
					neg = 0;
				} else {
					el.f = n[z];
				}
				push(out, el, 0);
			}
		} else if(e[i] == '*' || e[i] == '/' || e[i] == '-' || e[i] == '+') {
			if(i > 0) {					
				if(e[i-1] == '(' || e[i-1] == '*' || e[i-1] == '/') {
					if(e[i] == '-')
						neg = 1;			
				} else {
					if(!isEmpty(tokens)) {
						el = top(tokens)->el;

						while(precedence(e[i], el.c) <= 0 && (el.c > 41 && el.c < 48) && top(tokens)->type) {
							push(out, pop(tokens), 1);
							if(top(tokens) != NULL)
								el = top(tokens)->el;
							else
								break;
						}
					}
					
					el.c = e[i];
					push(tokens, el, 1);
				}
			} else if(e[i] == '-' && e[i+1] != '(') {
				neg = 1;
			} else if(e[i] == '-' && e[i+1] == '(') {
				el.f = 0;
				push(out, el, 0);
			} 
			
		} else if(e[i] == '(') {
			el.c = e[i];
			push(tokens, el, 1);
		} else if(e[i] == ')') {	
			while(top(tokens)->el.c != '(')  {
				push(out, pop(tokens), 1);
			}
			pop(tokens);
		} else if(e[i] != '.') {
			el.c = e[i];
			push(out, el, 1);
		}
		i++;
	} 



	while(!isEmpty(tokens)) 
		push(out, pop(tokens), 1);


	// deixa o resultado negativo
	if(e[0] == '-' && e[1] == '(') {
		el.c = '-';
		push(out, el, 1);
	}

	free(n);

	freeStack(tokens);

	return out;
}

// Resolve a expressão Polonesa com uma recursão e finalmente retorna o resultado
double solvePolish(Stack *q) {
	char c;
	Element el;
	int type;
	double a, b;

	type = top(q)->type;
	el = pop(q);

	if(type) {
		c = el.c;
		a = solvePolish(q);
		b = solvePolish(q);
		if(c == '+')
			return a + b;
		else if(c == '-')
			return b - a;
		else if(c == '/')
			return b / a;
		else if(c == '*')
			return b * a;
	}

	return el.f;
}

int main() {
	char *e;
	Stack *out;

	scanf("%m[^\n]", &e);
	out = covertToPolish(e, strlen(e));

	printf("%.7g\n", solvePolish(out));
	
	freeStack(out);
	free(e);

	return 0;
}