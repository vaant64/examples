#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <math.h>
#include <mpi.h>

#define LEFT 0
#define RIGHT 1

#define F 2

#define GNUPLOT
FILE *out, *fp;

double a = 0.5;
double dx = 1;
double dt = 1;

double a2;
double dx2;
double dt2;

int x_lim;
int t_lim;

struct timeval tv1, tv2, dtv;
struct timezone tz;

void writeResult(double *Z, int x_lim) {   
	int i;
    	for (i = 0; i < x_lim; i++)
        	fprintf(out, "%d\t%lf\n", i*(int)dx, Z[i]);
    	fprintf(out, "\n");
    	fprintf(out, "\n\n");
}

void generateGnuplot(int t_lim) {
    	out = fopen("results.txt","w");
    	fp  = fopen("plot.dat","w");

    	fprintf(fp, "set cbrange [0.9:1]\n");
    	fprintf(fp, "set xrange [0:%d]\n", x_lim-(int)dx);
    	fprintf(fp, "set yrange [-10:10]\n");
    	fprintf(fp, "do for [i=0:%d]{\n", t_lim-(int)dt);
    	fprintf(fp, "plot 'results.txt' i i using 1:2 smooth bezier title 'Simulation'\npause 0.1}\npause -1\n");
}

double f(int x, double t_curr) {
    	if (t_curr <= 5 && x == x_lim-2) {
        	return F;
    	}
    	return 0;
}

void solver(double* Z0, double* Z1, int x_proc, double t_curr, int myrank, int total, double* left, double* right) {   
	int i;
    if (myrank) {
        i = 0;
        Z1[i] = dt2 * (a2*(*left-2*Z0[i]+Z0[i+1])/dx2 + f(myrank*x_proc + i, t_curr)) + 2*Z0[i]-Z1[i];
        *left = Z1[i];
    }

    for (i = 1; i < x_proc-1; i++) {
        Z1[i] = dt2 * (a2*(Z0[i-1]-2*Z0[i]+Z0[i+1])/dx2 + f(myrank*x_proc + i, t_curr)) + 2*Z0[i]-Z1[i];            
    }

    if (myrank != total-1) {
        i = x_proc-1;
        Z1[i] = dt2 * (a2*(Z0[i-1]-2*Z0[i]+*right)/dx2 + f(myrank*x_proc + i, t_curr)) + 2*Z0[i]-Z1[i];
        *right = Z1[i];
    }

	if (myrank) {
        MPI_Send((void*)left, 1, MPI_DOUBLE, myrank-1, RIGHT, MPI_COMM_WORLD);          
        MPI_Recv((void*)left, 1, MPI_DOUBLE, myrank-1, LEFT, MPI_COMM_WORLD, MPI_STATUS_IGNORE);     
    } 
    
    if (myrank != total-1) { 
        MPI_Send((void*)right, 1, MPI_DOUBLE, myrank+1, LEFT, MPI_COMM_WORLD);
        MPI_Recv((void*)right, 1, MPI_DOUBLE, myrank+1, RIGHT, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
}

int main(int argc, char **argv) {
	int i;
	int myrank, total;
	int x_proc;

	double *Z0;
    double *Z1;
	
	double *z0;
    double *z1;

    double left;
    double right;

    double t_curr = dt;
    int z_num = 1;

	int *displs;
    int *sendcounts;

	if (argc < 3) { printf("Некорректное число аргументов!\n"); exit(1); }

    x_lim = atoi(argv[1]);
    t_lim = atof(argv[2]);

	a2 = a*a;
	dx2 = dx*dx;
	dt2 = dt*dt;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &total);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    x_proc = x_lim / total;

    if (!myrank) {
        Z0 = (double*)calloc(x_lim, sizeof(double));
        Z1 = (double*)calloc(x_lim, sizeof(double));
    
        for (i = 0; i < x_lim; i++) {
            Z0[i] = 0;
			Z1[i] = 0;
        }

		#ifdef GNUPLOT
		generateGnuplot(t_lim);
        writeResult(Z0, x_lim);
		#endif
    }

    z0 = (double*)calloc(x_proc, sizeof(double)); 
    z1 = (double*)calloc(x_proc, sizeof(double));  

    sendcounts = (int*)calloc(total, sizeof(int));
	displs = (int*)calloc(total, sizeof(int));

    for (i = 0; i < total; i++)
        sendcounts[i] = x_proc;
    
    for (i = 0; i < total; i++)
        displs[i] = i * x_proc;

    MPI_Scatterv((void *)Z0, sendcounts, displs, MPI_DOUBLE,
		(void *)z0, x_proc, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    MPI_Scatterv((void *)Z1, sendcounts, displs, MPI_DOUBLE,
		(void *)z1, x_proc, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    left = z0[0];
    right = z0[x_proc-1];

	if (myrank) {
        MPI_Send((void*)&left, 1, MPI_DOUBLE, myrank-1, RIGHT, MPI_COMM_WORLD);         
        MPI_Recv((void*)&left, 1, MPI_DOUBLE, myrank-1, LEFT, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    if (myrank != total-1) { 
        MPI_Send((void*)&right, 1, MPI_DOUBLE, myrank+1, LEFT, MPI_COMM_WORLD);  
        MPI_Recv((void*)&right, 1, MPI_DOUBLE, myrank+1, RIGHT, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    if (!myrank)
        gettimeofday(&tv1, NULL);

    while (t_curr < t_lim) {
        if (z_num == 1)
            solver(z0, z1, x_proc, t_curr, myrank, total, &left, &right);
        else
            solver(z1, z0, x_proc, t_curr, myrank, total, &left, &right);

		#ifdef GNUPLOT
		double *Z_curr;
		double *z_curr;

		if (z_num == 1) { Z_curr = Z1; z_curr = z1; }
		else { Z_curr = Z0; z_curr = z0; }

		MPI_Gatherv((void*)z_curr, x_proc, MPI_DOUBLE,
			(void*)Z_curr, sendcounts, displs, MPI_DOUBLE, 0, MPI_COMM_WORLD);

		if (!myrank)
			writeResult(Z_curr, x_lim);
		MPI_Barrier(MPI_COMM_WORLD);
		#endif

        if (!myrank) {
            	z_num *= -1;
            	t_curr += dt;
        }
        MPI_Bcast((void*)&z_num, 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast((void*)&t_curr, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }

	if (!myrank) {
		gettimeofday(&tv2, NULL);
        timersub(&tv2, &tv1, &dtv);
		printf("Time: %ld.%ld sec\n", dtv.tv_sec, dtv.tv_usec/1000);
	}

	free(displs);
    free(sendcounts);
	free(z1);
    free(z0);

	if (!myrank) { free(Z1); free(Z0); }

    MPI_Finalize();
    exit(0);
}
