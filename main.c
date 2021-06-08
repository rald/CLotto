#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

#define RANDOM_PICK 0
#define SAMPLES_MAX 1000000
#define NEEDED 6
#define REMAINING 45
#define MIN 1
#define MAX REMAINING



int l[] = {13,19,22,25,33,39};



double drand48() {
	return rand()/(RAND_MAX+1.0);
}

void print(int *a,int n) {
	for(int i=0;i<n;i++) {
		printf("%2d ",a[i]);
	}
}

int* draw(int a,int b) {
	int *w=malloc(sizeof(*w)*a);
	int n=a,r=b,min=1,max=b;
	int j=0;
	for(int i=0;i<a;i++) w[i]=0;
	for(int i=min;i<=max;i++) {
		if(((double)n/r)>drand48()) {
			w[j++]=i;
			n--;
		}
		r--;
	}
	return w;
}

int cmp(const void *a,const void *b) {
	return (*(int*)a)-(*(int*)b);
}

int check(int *a,int *b) {
	int n=0;
	qsort(a,6,sizeof(*a),cmp);
	qsort(b,6,sizeof(*b),cmp);
	for(int i=0;i<6;i++) {
		if(a[i]==b[i]) n++; else break;
	}
	return n;
}

void count(int *w,int n,int min,int max,int **f) {
	for(int i=0;i<n;i++) {
		(*f)[w[i]-min]++;
	}
}

void graph(int *f,int min,int max,int k) {
	int c=30;
	for(int i=0;i<max-min+1;i++) {
		if(f[i]) {
			printf(". %2d -> %6.2f%% ",i+min,(double)f[i]/k*100);
			int p=((double)f[i]/k*c);
			for(int j=0;j<p;j++) printf("#");
			for(int j=0;j<c-p;j++) printf("-");
			printf("\n");
		}
	}
}

void wins(int *t,int n,int g,int o) {
	int c=30;
	for(int i=0;i<n-g+1;i++) {
		if(t[i]) {
			printf("# %2d -> %6.2f%% ",i+g,(double)t[i]/o*100);
			int p=((double)t[i]/o*c);
			for(int j=0;j<p;j++) printf("#");
			for(int j=0;j<c-p;j++) printf("-");
			printf(" %d\n",t[i]);
		}
	}
}

int main() {
	int n=NEEDED,r=REMAINING;
	int min=MIN,max=MAX;
	int g=4;
	int c=0;
	int o=0;
	size_t k=SAMPLES_MAX;
	int* w=NULL;
	int* f=malloc(sizeof(*f)*(r+1));
	int* t=malloc(sizeof(*t)*(n-g+1));

	srand(time(NULL));

	if(RANDOM_PICK)	for(int i=0;i<n;i++) l[i]=rand()%(max-min+1)+min;

	qsort(l,6,sizeof(*l),cmp);
	print(l,6); printf("\n");

	for(int i=0;i<n-g+1;i++) t[i]=0;
	for(int i=0;i<max-min+1;i++) f[i]=0;

	for(size_t i=0;i<k;i++) {

		w=draw(n,r);

		count(w,n,min,max,&f);

		c=check(l,w);

		if(c>=g) {
			o++;
			t[c-g]++;
			print(w,6);
			printf(" -> %d\n",c);
		}

		free(w);
		w=NULL;
	}

	graph(f,min,max,k);

	wins(t,n,g,o);

	free(t);
	t=NULL;

	free(f);
	f=NULL;

	return 0;
}
