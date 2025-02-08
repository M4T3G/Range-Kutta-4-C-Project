#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
    int n;
    double *katsayilar;
    int *us;
    double a;
    double b;
} Denklem;

void polinomAl(Denklem *denklem) {
    int i;
    if(denklem->n>0){     //Denklemde x'li terim yoksa dogal olarak alamayacagýz.
    	denklem->katsayilar = (double *)malloc(denklem->n * sizeof(double));
    	denklem->us = (int *)malloc(denklem->n * sizeof(int));

    	printf("Polinom katsayilarini giriniz.\n");
    	for (i = 0; i < denklem->n; i++) {
    	    scanf("%lf", &denklem->katsayilar[i]);
    	}

    	printf("Polinom uslerini giriniz.\n");
    	for (i = 0; i < denklem->n; i++) {
    	    scanf("%d", &denklem->us[i]);
    	}		
	}
}

double turevHesapla(Denklem denklem, double x, double y) {
    int i;
    double toplam = 0;

    for (i = 0; i < denklem.n; i++) {
        toplam += denklem.katsayilar[i] * pow(x, denklem.us[i]);
    }
    
    toplam=toplam+denklem.b * y;
    toplam=toplam/denklem.a;

    return toplam;
}

void denklemYazdir(Denklem denklem) {
    int i;
    printf("Denkleminiz:\n");
    printf("%fy' = %fy  ", denklem.a, denklem.b);
    if(denklem.n>0){       //Denklemde x'li terim yoksa yazdýrmayacak
    	for (i = 0; i <= denklem.n - 1; i++) {
    	    printf(" +  %lfx^%d", denklem.katsayilar[i], denklem.us[i]);
    	}
    	//printf("%lfx^%d\n", denklem.katsayilar[denklem.n - 1], denklem.us[denklem.n - 1]);    	    	    	
	}

}

int main() {
    Denklem denklem;
    double x, y, t, h, k1, k2, k3, k4,cevap;
    int i, m = 0;
    denklem.katsayilar = NULL;
    denklem.us = NULL;
    printf("Birinci mertebeden yani 1.turevi alinan fonksiyonun(f') katsayisini giriniz.\n");
    scanf("%lf", &denklem.a);
    printf("Fonksiyonun(y) katsayisini giriniz.\n");
    scanf("%lf", &denklem.b);
    do{
    	printf("Kac tane x'li terim gireceksiniz?\n");
    	scanf("%d", &denklem.n);	
	}while(denklem.n<0);          //Kullanýcýnýn negatif terim sayýsý girmesini engelledik
    polinomAl(&denklem);
    denklemYazdir(denklem);
    printf("\nx baslangic degeri giriniz.\n");
    scanf("%lf", &x);
    printf("y baslangic degerini giriniz.\n");
    scanf("%lf", &y);
    printf("Adim buyuklugu(h) degerinizi giriniz.\n");
    scanf("%lf", &h);        
    printf("Cevabini bulmak istediginiz hedef degeri giriniz.\n");
    scanf("%lf", &t);
    printf("Denklemin istenilen degerdeki gercek sonucunu giriniz.\n");
    scanf("%lf",&cevap);
    //i dedigimiz sayý iterasyon sayýsý. Hedef deðerden baþlangýc degerini çýkarýp adým buyuklugune bolerek bulduk. Cýkan sonuc double oldugu icin typecast yaptýk
    i = (int)(fabs((t - x)) / h);
    if(x>t){
    	h=-h;     // eger geriye dogru gitmemiz gerekirse h degerini güncelledik. Ornek 0.2 baslangýc noktasýndan 0 hedef noktasýna gitmemiz istenirse geri gitmeliyiz
	}
    while (m < i) {                  //iterasyon sayýsý kadar ilerlettik while dongusunu
        k1 = h*turevHesapla(denklem, x, y);
        printf("\nk1=%lf\n",k1);
        k2 = h*turevHesapla(denklem, x + 0.5 * h, y + 0.5 * k1);
        printf("k2=%lf\n",k2);
        k3 = h*turevHesapla(denklem, x + 0.5 * h, y + 0.5 * k2);
        printf("k3=%lf\n",k3);
        k4 = h*turevHesapla(denklem, x + h, y + k3);
        printf("k4=%lf\n",k4);
        y = y +(k1 + 2 * k2 + 2 * k3 + k4)/6 ;
        x = x + h;          
        printf("iterasyon=%d   y(%lf) da sonucumuz= %lf\n",m+1,x,y);
        m++;     //while dongusunu ilerletmek icin m degiskenini ustte tanýmladýk ve burada artýrdýk
    }
    printf("Mutlak hata=%lf\n",fabs(cevap-y));        // Mutlak hata hesaplayabilmek icin kullanýcýdan gercek cevabý aldýk ve arasýndaki farkýn mutlak degerini aldýk
    free(denklem.katsayilar);
    free(denklem.us);
    return 0;
}

