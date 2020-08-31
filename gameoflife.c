#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"gol.h"

int main(int argc, char *argv[])
{
	struct universe u;
	int i = 0, skipNext = 0, number_of_generations = 5;
	memset(&u, 0, sizeof u);
	char *InputFileName, *OutputFileName;
	int checkCommand[5] = { 0, 0, 0, 0, 0 };
	int(*rule)(struct universe *u, int column, int row);
	rule = will_be_alive;
	FILE *infile = NULL, *outfile = NULL;
	for (i = 1; i < argc; i++)
	{
		if (skipNext != 0)
		{
			skipNext = 0;
			continue;
		}
		if (strlen(argv[i]) != 2)
		{
			fprintf(stderr, "Please use valid commands only\n");
			exit(1);
		}
		switch (argv[i][1])
		{
			case 'i':
				if (i + 1 != argc)
				{
					if (checkCommand[0] == 0)
					{
						InputFileName = argv[i + 1];
						skipNext = 1;
						checkCommand[0] = 1;
						break;
					}
					else
					{
						if (strcmp(InputFileName, argv[i + 1]) == 0)
						{
							skipNext = 1;
							break;
						}
						fprintf(stderr, "Contradicting commands entered\n");
						exit(1);
					}
				}
				else
				{
					fprintf(stderr, "Please enter a filename for -i\n");
					exit(1);
				}
			case 'o':
				if (i + 1 != argc)
				{
					if (checkCommand[1] == 0)
					{
						OutputFileName = argv[i + 1];
						skipNext = 1;
						checkCommand[1] = 1;
						break;
					}
					else
					{
						if (strcmp(OutputFileName, argv[i + 1]) == 0)
						{
							skipNext = 1;
							checkCommand[1] = 1;
							break;
						}
						else
						{
							fprintf(stderr, "Contradicting commands entered\n");
							exit(1);
						}
					}
				}
				else
				{
					fprintf(stderr, "Please enter a filename for -o\n");
					exit(1);
				}
			case 'g':
				if (i + 1 != argc)
				{
					if (checkCommand[2] == 0)
					{
						if (i + 1 != argc)
						{
							number_of_generations = atoi(argv[i + 1]);
							if (number_of_generations == 0 && argv[i + 1][0] != '0')
							{
								fprintf(stderr, "Please Enter a number for the command -g\n");
								exit(1);
							}
							checkCommand[2] = 1;
							skipNext = 1;
							break;
						}
						else
						{
							fprintf(stderr, "Please Enter a number for the command -g\n");
							exit(1);
						}
					}
					else
					{
						if (number_of_generations == atoi(argv[i + 1]))
						{
							checkCommand[2] = 1;
							skipNext = 1;
							break;
						}
						else
						{
							fprintf(stderr, "Contradicting commands entered\n");
							exit(1);
						}
					}
				}
				else
				{
					fprintf(stderr, "Please Enter a number for the command -g\n");
					exit(1);
				}

			case 's':
				checkCommand[3] = 1;
				break;
			case 't':
				rule = will_be_alive_torus;
				checkCommand[4] = 1;
				break;
			default:
				fprintf(stderr, "Please use valid commands only\n");
				exit(1);
				break;
		}
	}
	if (checkCommand[1] == 1)
	{
		outfile = fopen(OutputFileName, "w");
	}
	infile = fopen(InputFileName, "r");
	if (infile == NULL && checkCommand[0] == 0)
	{
		read_in_file(stdin, &u);
	}
	else
	{
		if (infile)
		{
			read_in_file(infile, &u);
		}
		else
		{
			fprintf(stderr, "input File not found\n");
			exit(1);
		}
	}
	for (i = 0; i < number_of_generations; i++)
	{
		evolve(&u, rule);
	}
	if (outfile)
	{
		write_out_file(outfile, &u);
	}
	else
	{
		write_out_file(stdout, &u);
	}
	if (checkCommand[3] == 1)
	{

		print_statistics(&u);
	}

	return 0;
}
