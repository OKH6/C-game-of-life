#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gol.h"

void evolve(struct universe *u, int(*rule)(struct universe *u, int column, int row))
{
	u->numAlive = 0;
	u->numDead = 0;
	int i, j;
	char *newGen = (char*) calloc(u->row *u->column, sizeof(char));
	int status;
	for (i = 0; i < u->row; i++)
	{
		for (j = 0; j < u->column; j++)
		{
			status = rule(u, j, i);
			if (status == 0)
			{*(newGen + i *u->column + j) = '.';
				u->numDead++;
			}
			else
			{*(newGen + i *u->column + j) = '*';
				u->numAlive++;
			}
		}
	}

	free(u->array);
	u->array = newGen;
	newGen = NULL;
	u->aliveSoFar = u->aliveSoFar + u->numAlive;
	u->totalCellsSoFar = u->totalCellsSoFar + u->numAlive + u->numDead;
}

int will_be_alive_torus(struct universe *u, int column, int row)
{
	if (row >= u->row || column >= u->column || column < 0 || row < 0 )
	{
		fprintf(stderr, "Invalid memory location out of universe bounds\n");
		exit(1);
		/*code */
	}

	int status = 0, Alive = 0, Dead = 0, i = 0;
	status = is_alive(u, column, row);
	int n[7];
	if (column - 1 < 0)
	{
		n[0] = is_alive(u, u->column - 1, row);
		if (row - 1 >= 0)
		{
			n[3] = is_alive(u, u->column - 1, row - 1);
		}
		else
		{
			n[3] = is_alive(u, u->column - 1, u->row - 1);
		}

		if (row + 1 < u->row)
		{
			n[6] = is_alive(u, u->column - 1, row + 1);
		}
		else
		{
			n[6] = is_alive(u, u->column - 1, 0);
		}
	}
	else
	{
		n[0] = is_alive(u, column - 1, row);
		if (row - 1 >= 0)
		{
			n[3] = is_alive(u, column - 1, row - 1);
		}
		else
		{
			n[3] = is_alive(u, column - 1, u->row - 1);
		}

		if (row + 1 < u->row)
		{
			n[6] = is_alive(u, column - 1, row + 1);
		}
		else
		{
			n[6] = is_alive(u, column - 1, 0);
		}
	}

	if (column + 1 == u->column)
	{
		n[1] = is_alive(u, 0, row);
		if (row - 1 >= 0)
		{
			n[4] = is_alive(u, 0, row - 1);
		}
		else
		{
			n[4] = is_alive(u, 0, u->row - 1);
		}

		if (row + 1 < u->row)
		{
			n[7] = is_alive(u, 0, row + 1);
		}
		else
		{
			n[7] = is_alive(u, 0, 0);
		}
	}
	else
	{
		n[1] = is_alive(u, column + 1, row);
		if (row - 1 >= 0)
		{
			n[4] = is_alive(u, column + 1, row - 1);
		}
		else
		{
			n[4] = is_alive(u, column + 1, u->row - 1);
		}

		if (row + 1 < u->row)
		{
			n[7] = is_alive(u, column + 1, row + 1);
		}
		else
		{
			n[7] = is_alive(u, column + 1, 0);
		}
	}

	if (row - 1 < 0)
	{
		n[2] = is_alive(u, column, u->row - 1);
	}
	else
	{
		n[2] = is_alive(u, column, row - 1);
	}

	if (row + 1 == u->row)
	{
		n[5] = is_alive(u, column, 0);
	}
	else
	{
		n[5] = is_alive(u, column, row + 1);
	}

	// n[0]= is_alive(u, column - 1, row);
	// n[1] = is_alive(u, column + 1, row);
	// n[2] = is_alive(u, column, row - 1);
	// n[3] = is_alive(u, column - 1, row - 1);
	// n[4] = is_alive(u, column + 1, row - 1);
	// n[5] = is_alive(u, column, row + 1);
	// n[6] = is_alive(u, column - 1, row + 1);
	// n[7] = is_alive(u, column + 1, row + 1);
	for (i = 0; i < 8; i++)
	{
		//printf("%d\n",n[i]);
		if (n[i] == 0)
		{
			Dead = Dead + 1;
		}
		else
		{
			Alive = Alive + 1;
		}
	}

	if (status == 1)
	{
		if (Alive == 2 || Alive == 3)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if (Alive == 3 && status == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int will_be_alive(struct universe *u, int column, int row)
{
	if (row >= u->row || column >= u->column || column < 0 || row < 0 )
	{
		fprintf(stderr, "Invalid memory location out of universe bounds\n");
		exit(1);
		/*code */
	}

	int status = 0, Alive = 0, Dead = 0, i = 0;
	status = is_alive(u, column, row);
	int n[7];
	if (column - 1 < 0)
	{
		n[0] = 0;
		n[3] = 0;
		n[6] = 0;
	}
	else
	{
		n[0] = is_alive(u, column - 1, row);
		if (row - 1 < 0)
		{
			n[3] = 0;
		}
		else
		{
			n[3] = is_alive(u, column - 1, row - 1);
		}

		if (row + 1 == u->row)
		{
			n[6] = 0;
		}
		else
		{
			n[6] = is_alive(u, column - 1, row + 1);
		}
	}

	if (column + 1 == u->column)
	{
		n[1] = 0;
		n[4] = 0;
		n[7] = 0;
	}
	else
	{
		n[1] = is_alive(u, column + 1, row);
		if (row - 1 < 0)
		{
			n[4] = 0;
		}
		else
		{
			n[4] = is_alive(u, column + 1, row - 1);
		}

		if (row + 1 == u->row)
		{
			n[7] = 0;
		}
		else
		{
			n[7] = is_alive(u, column + 1, row + 1);
		}
	}

	if (row - 1 < 0)
	{
		n[2] = 0;
	}
	else
	{
		n[2] = is_alive(u, column, row - 1);
	}

	if (row + 1 == u->row)
	{
		n[5] = 0;
	}
	else
	{
		n[5] = is_alive(u, column, row + 1);
	}

	// n[0]= is_alive(u, column - 1, row);
	// n[1] = is_alive(u, column + 1, row);
	// n[2] = is_alive(u, column, row - 1);
	// n[3] = is_alive(u, column - 1, row - 1);
	// n[4] = is_alive(u, column + 1, row - 1);
	// n[5] = is_alive(u, column, row + 1);
	// n[6] = is_alive(u, column - 1, row + 1);
	// n[7] = is_alive(u, column + 1, row + 1);
	for (i = 0; i < 8; i++)
	{
		//printf("%d\n",n[i]);
		if (n[i] == 0)
		{
			Dead = Dead + 1;
		}
		else
		{
			Alive = Alive + 1;
		}
	}

	if (status == 1)
	{
		if (Alive == 2 || Alive == 3)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if (Alive == 3 && status == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int is_alive(struct universe *u, int column, int row)
{
	if (*(u->array + row *u->column + column) == '.')
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void write_out_file(FILE *outfile, struct universe *u)
{
	int i, j, col, row = 0;
	col = u->column;
	row = u->row;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			putc(*(u->array + i *col + j), outfile);
		}

		putc('\n', outfile);
	}
}

void read_in_file(FILE *infile, struct universe *u)
{
	char c, *A;
	int i, col = 0, row = 1, current = 0, count = 0, dead = 0, alive = 0;
	A = malloc(sizeof(char) *512);
	if (A == NULL)
	{
		fprintf(stderr, "couldnt allocate memory\n");
		exit(1);
	}

	for (i = 0;
		(fscanf(infile, "%c", &c) == 1); i++)
	{
		if (c == '\n' && col == 0)
		{
			col = i;
			row++;
			count = 0;
			A = realloc(A, sizeof(char) *row *col);
			if (A == NULL)
			{
				fprintf(stderr, "couldnt allocate memory\n");
				exit(1);
			}

			current = (row - 1) *col;
			continue;
		}
		else if (c == '\n')
		{
			if (count != col)
			{
				fprintf(stderr, "invalid file format\n");
				exit(1);
			}

			count = 0;
			row++;
			current = (row - 1) *col;
			A = realloc(A, sizeof(char) *row *col);
			if (A == NULL)
			{
				fprintf(stderr, "couldnt allocate memory\n");
				exit(1);
			}

			continue;
		}

		if (c == '.' || c == '*')
		{
			if (c == '.')
			{
				dead++;
			}
			else
			{
				alive++;
			}

			if (count > 511)
			{
				fprintf(stderr, "invalid file format, row too long\n");
				exit(1);
			}

			*(A + current) = c;
			current++;
			count++;
		}
		else
		{
			fprintf(stderr, "invalid file format wrong charecters\n");
			exit(1);
		}
	}

	row--;
	if (col == 0)
	{
		fprintf(stderr, "File is empty\n");
		exit(1);
	}

	A = realloc(A, sizeof(char) *row *col);
	if (A == NULL)
	{
		fprintf(stderr, "Couldnt allocate enough memory\n");
		exit(1);
	}

	//A=realloc(A,sizeof(char)*row*col);
	u->aliveSoFar = alive;
	u->totalCellsSoFar = dead + alive;
	u->numDead = dead;
	u->numAlive = alive;
	u->column = col;
	u->row = row;
	u->array = A;
	A = NULL;

}

void print_statistics(struct universe *u)
{
	double average;
	double percentage;
	average = u->aliveSoFar / u->totalCellsSoFar;
	average = average * 100;
	percentage = u->numAlive / (u->numAlive + u->numDead);
	percentage = percentage * 100;
	fprintf(stdout, "%.3f%% of cells currently alive\n", percentage);
	fprintf(stdout, "%.3f%% of cells alive on average\n", average);

}
