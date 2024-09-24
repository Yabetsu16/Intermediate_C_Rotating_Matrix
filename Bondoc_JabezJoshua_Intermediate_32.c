#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct matrix {
	int rows;
	int cols;
	char *cells;
};

void fill_matrix(struct matrix g)
{
	int row,col;

	for( row=0; row<g.rows; row++ )
		for( col=0; col<g.cols; col++ )
			*(g.cells+(row*g.cols)+col) = (rand() % 26) + 'a';
}

void output_matrix(struct matrix g)
{
	int row,col;

	for( row=0; row<g.rows; row++ )
	{
		for( col=0; col<g.cols; col++ )
			printf(" %c",*(g.cells+(row*g.cols)+col));
		putchar('\n');
	}
}

void rotate_matrix(struct matrix *g)
{
	struct matrix *r;
	int rsize,x,y,i;

	r = (struct matrix *)malloc( sizeof(struct matrix) );
	if( r==NULL )
	{
		fprintf(stderr,"Unable to allocate new matrix\n");
		exit(1);
	}
	r->rows = g->cols;
	r->cols = g->rows;
	rsize = r->rows*r->cols;
	r->cells = (char *)malloc( sizeof(char)*rsize );
	if( r->cells==NULL )
	{
		fprintf(stderr,"Unable to allocate cell memory\n");
		exit(1);
	}

	i = 0;
	for( x=0; x<g->cols; x++ )
	{
		for( y=g->rows-1; y>=0; y-- )
		{
			*(r->cells+i) = *(g->cells+(g->cols*y)+x);
			i++;
		}
	}

	for( i=0; i<rsize; i++ )
		*(g->cells+i) = *(r->cells+i);
	g->cols = r->cols;
	g->rows = r->rows;

	free(r->cells);
	free(r);
}

int main()
{
	struct matrix grid[3] = {
		{ 8, 3, NULL },
		{ 5, 5, NULL },
		{ 4, 6, NULL }
	};
	int x;

	srand( (unsigned)time(NULL) );

	for( x=0; x<3; x++ )
	{
		grid[x].cells = \
			(char *)malloc( sizeof(char)*grid[x].rows*grid[x].cols );
		if( grid[x].cells==NULL )
		{
			fprintf(stderr,"Memory allocation error on grid #%d\n",
					x
				   );
			exit(1);
		}
	}

	for( x=0; x<3; x++ )
	{
		fill_matrix(grid[x]);
		printf("Original matrix %d:\n",x+1);
		output_matrix(grid[x]);
		rotate_matrix(&grid[x]);
		printf("Rotated matrix: %d:\n",x+1);
		output_matrix(grid[x]);
	}

	return(0);
}
