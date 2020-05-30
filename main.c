#include <stdio.h>
#include <stdlib.h>

int IsNumberNat(const char *txt) { // to check if char is number
	if (NULL == txt || *txt == '\0')
		return 0;
	int dotCount = 0, plusCount = 0, minusCount = 0;
	while(*txt)
	{
		char c = *txt;
		switch(c)
		{   
			case '.':
				if (++dotCount > 0)
					return 0;
				break;
			case '-':
				if (++minusCount > 0)
					return 0;
				break;
			case '+':	
				if (++plusCount > 1)
					return 0;
				break;
			case '\n':
				break;
			default:
				if (c < '0' || c > '9')
					return 0;
		}
		txt++;
	}
	return 1;
}

int GetNumber(const char *txt) { // to get number from char
	int num = 0;
	while(*txt)
	{
   		if(*txt == '\n')
   			*txt++;
   		else if(*txt == '+')
   			*txt++;
   		else
   			num = num*10 + (*txt++ - '0');
	}
	return num;
}

int main(int argc, char *argv[]) {
	int flag = 0, flag1 = 0, flag2 = 0, zerCnt = 0, lines, cols, i, j, n, k, maxElem = 0, minElem = 101, minInLine = 101, minInCol = 101, minElOther = 101;
	char inp[2];
	struct elem{
		int num;
		int status;
	}matr[5][5];
	while(flag == 0) // waiting for correct input
	{
		printf("\nInput count of lines (5 max): ");
		fgets(inp, sizeof(inp), stdin);
		fflush(stdin);
		if(IsNumberNat(inp) == 1 && GetNumber(inp) > 0 && GetNumber(inp) < 6) // integer [1;5]
		{
			lines = GetNumber(inp); // int lines from char
			flag = 1;
		}
		else
			printf("\n--- Number must be natural and [1;5] ---\n");
	}
	while(flag == 1) // waiting for correct input
	{
		printf("\nInput count of columns (5 max): ");
		fgets(inp, sizeof(inp), stdin);
		fflush(stdin);
		if(IsNumberNat(inp) == 1 && GetNumber(inp) > 0 && GetNumber(inp) < 6) // integer [1;5]
		{
			cols = GetNumber(inp); // int columns from char
			flag = 0;
		}
		else
			printf("\n--- Number must be natural and [1;5] ---\n");
	}
	srand(time(NULL));
	for(i = 0; i < lines; i++) // generation of numbers
	{
		puts("");
		for(j = 0; j < cols; j++)
		{
			matr[i][j].num = rand() % 90 + 10; // from 10 to 100
			if(matr[i][j].num > maxElem)
				maxElem = matr[i][j].num; // max element
			if(matr[i][j].num < minElem)
				minElem = matr[i][j].num; // min element
			printf("%d ", matr[i][j].num); // output
		}
	}
	if(lines > cols)
	{
		while(cols != lines) // adding columns with max from matr
		{
			for(i = 0; i < lines; i++)
				matr[i][cols].num = maxElem;
			cols++;
		}
	}
	else if(lines < cols)
	{
		while(lines != cols) // adding lines with max from matr
		{
			for(i = 0; i < cols; i++)
				matr[lines][i].num = maxElem;
			lines++;
		}
	}
	for(i = 0; i < lines; i++) // work with min in lines
	{
		minInLine = 101;
		for(j = 0; j < cols; j++) 
			if(matr[i][j].num < minInLine)
				minInLine = matr[i][j].num;
		for(j = 0; j < cols; j++)
			matr[i][j].num -= minInLine; // minus min from line
	}
	puts("");
	for(i = 0; i < lines; i++) // output
	{
		puts("");
		for(j = 0; j < cols; j++)
			printf("%d ", matr[i][j].num);
	}
	for(i = 0; i < cols; i++) // work with min in columns
	{
		minInCol = 101;
		for(j = 0; j < lines; j++) 
			if(matr[j][i].num < minInCol)
				minInCol = matr[j][i].num;
		for(j = 0; j < lines; j++) 
			matr[j][i].num -= minInCol; // minus min from column
	}
	puts("");
	for(i = 0; i < lines; i++) // output
	{
		puts("");
		for(j = 0; j < cols; j++)
			printf("%d ", matr[i][j].num);
	}
	while(flag1 == 0)
	{
		for(i = 0; i < lines; i++) // change the status of an element on the same row or column as 0
		{
			for(j = 0; j < cols; j++)
			{
				if(matr[i][j].num == 0 && matr[i][j].status == 0) // inactive 0
				{
					n = 0;
					k = 0;
					while(k < cols)
					{
						matr[n][k].status = 1; // elements on the same line
						k++;
					}
					k = 0;
					while(n < lines)
					{
						matr[n][k].status = 1; // elements on the same column
						n++;
					}
					matr[i][j].status = 2;
				}
			}
		}
		for(i = 0; i < lines; i++)
		{
			for(j = 0; j < cols; j++)
			{
				if(matr[i][j].status == 0) // status of inactive 0
					if(minElOther < matr[i][j].num)
						minElOther = matr[i][j].num; // min element from remaining
			}
		}
		for(i = 0; i < lines; i++)
		{
			for(j = 0; j < cols; j++)
			{
				if(matr[i][j].status == 2)
					matr[i][j].num += minElOther; // + min element from remaining
				if(matr[i][j].status == 0)
					matr[i][j].num -= minElOther; // - min element from remaining
			}
		}
		while(flag2 == 0) // check if 0 only one at current line and column
		{
			for(i = 0; i < lines; i++)
			{
				for(j = 0; j < cols; j++)
				{
					if(matr[i][j].num == 0 && matr[i][j].status != 0)
					{
						n = 0;
						k = 0;
						while(k < cols)
						{
							matr[n][k].num = 2; // changing status of elements at the same line and column with 0
							k++;
						}
						k = 0;
						while(n < lines)
						{
							matr[n][k].num = 2; // changing status of elements at the same line and column with 0
							n++;
						}
						matr[i][j].status = 3; // status of 0 which will be solution
					}
				}
			}
			flag2 = 1; // exit from cycle
		}
		flag1 = 1; // exit from cycle
		puts("gg");
		for(i = 0; i < lines; i++) // output
		{
			puts("");
			for(j = 0; j < cols; j++)
				if(matr[i][j].status == 3)
					printf("%d ", matr[i][j].num); // output number if it is solution
				else
					printf("."); // output '.' if it is not solution
		}
	}
	return 0;
}

