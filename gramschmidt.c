#include<stdio.h>
#include<math.h>
#pragma warning(disable:4996)
#define Inum 100

struct vector {
	double ing[Inum];
};
void print(struct vector*,int,int);
void GramSchmidt(struct vector*, int, int);
double innerProduct(struct vector*,int,int,int);
int main(void)
{
	//N:ベクトルの本数
	//ingnum:列ベクトルの要素数
	int N, ingnum;

	
	printf("ベクトルの本数、ベクトルの成分数(行の数)を入力してください。\n");
	printf("（例　3 3）＝ベクトルの本数３、成分数３\n");

	scanf("%d %d", &N, &ingnum);


	//a[] : a[1]から定義（a[0]は使用しない）
	struct vector a[Inum];
	int i, j;
	printf("ベクトルを入力してください。\n");
	printf("例 1\n");
	printf("   2\n");
	printf("   4\n");
	for (i = 1; i <= N; i++) {
		printf("%d本目のベクトルを入力してください。\n",i);
		for (j = 1; j <= ingnum; j++) {
			scanf("%lf", &a[i].ing[j]);
		}
	}

	//入力されたベクトルの出力
	printf("入力されたベクトル\n");
	print(a, ingnum, N);

	//一列ずつ正規直交化を行う。
	for (i = 1; i <= N; i++) {
		GramSchmidt(a, ingnum, i);
	}

	printf("正規直交化させたベクトル\n");
	print(a,ingnum,N);

	return 0;
}
void print(struct vector a[], int ingnum, int N)
{
	int i, j;
	for (j = 1; j <= ingnum; j++) {
		for (i = 1; i <= N; i++) {
			printf("%9f", a[i].ing[j]);
			if (i != 3) {
				printf("|");
			}
		}
		printf("\n");
	}
}
void GramSchmidt(struct vector a[], int ingnum, int i)
{
	double num = 0;
	int j;
	int k;
	double sum = 0;
	//i 現在正規直交化を行っているベクトル

	//直交化
	if (i != 1) {


		//ｊつ目の正規直交化ベクトルにおいて
		for (j = 1; j < i; j++) {
			//内積を出す(各項）
			sum = innerProduct(a, ingnum, i, j);
			//各項を引く
			for (k = 1; k <= ingnum; k++) {
				a[i].ing[k] -= sum*a[j].ing[k];
			}
			sum = 0;
		}
	}

	//正規化(構造体の配列a[i]にそれぞれベクトル、大きさの情報を格納する)
	for (j = 1; j <= ingnum; j++) {
		num += (a[i].ing[j])*(a[i].ing[j]);
	}

	for (j = 1; j <= ingnum; j++) {
		a[i].ing[j] = a[i].ing[j] / sqrt(num);
	}
	num = 0;

}
double innerProduct(struct vector a[], int ingnum, int i, int j)
{
	//i:現在直交化してるi番目のベクトル
	//j:直交化するにあたり使用する単位ベクトル
	int k;
	double inner;
	inner = 0;
	for (k = 1; k <= ingnum; k++) {
		inner += (a[i].ing[k] * a[j].ing[k]);
	}

	return inner;
	
}
