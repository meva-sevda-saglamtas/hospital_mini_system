#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<unistd.h>
#include<cmath>
using namespace std;
struct doktor{
string kullanici_adi;
string sifre;
string isim;
string soyisim;
};
struct hasta{
    string ad;
    string soyad;
    string cinsiyet;
    int yas;
    int ID;
    string tanı;
};
struct node{
 hasta hasta_bilgileri;
 node* onceki;
 node* sonraki;
};
struct ameliyat{
    string ameliyat_adi;
    string ameliyat_tarihi;
    float ameliyat_saati;
    string isim;
    string soyisim;
    int hasta_ID; 
    float ameliyat_ucreti;
};
struct ameliyat_node{
    ameliyat ameliyat_bilgileri;
    ameliyat_node*onceki_a;
    ameliyat_node*sonraki_a;
};
struct dairesel_node_hasta{
     hasta hasta_bilgileri;
     dairesel_node_hasta*sonraki_h;
     dairesel_node_hasta*onceki_h;
};
struct doktor_node{
    doktor doktor_bilgileri;
    doktor_node*sonraki;
    doktor_node*onceki;
};
struct dairesel_node_ameliyat{
    ameliyat ameliyat_bilgileri;
    dairesel_node_ameliyat*sonraki_a;
    dairesel_node_ameliyat*onceki_a;
};
struct tek_yonlu_dairesel_ameliyat_node{
   ameliyat ameliyat_bilgileri;
    tek_yonlu_dairesel_ameliyat_node*sonraki;
};
struct dairesel_node_hasta_puan{
    hasta hasta_bilgileri;
    int oncelik_puani;
    dairesel_node_hasta_puan*onceki_hasta;
    dairesel_node_hasta_puan*sonraki_hasta;
};
struct tek_yonlu_dairesel_node{
hasta hasta_bilgileri;

tek_yonlu_dairesel_node*sonraki;
};
struct hastane{
int dr_perf;
int hasta_memnuniyet;
int hizmet_kalitesi;
};
struct degerlendir_node{
hastane hastane_bilgileri;
degerlendir_node*sonraki;
};
void tek_yonlu_hasta_ekle(tek_yonlu_dairesel_node*&bas_d,const string& cinsiyet,int yas ,int id){
hasta yeni_hasta={"","",cinsiyet,yas,id,""};
tek_yonlu_dairesel_node*yeni_dugum=new tek_yonlu_dairesel_node;
yeni_dugum->hasta_bilgileri=yeni_hasta;

if(bas_d==nullptr){
    bas_d=yeni_dugum;
    bas_d->sonraki=bas_d;
}else{
    tek_yonlu_dairesel_node*temp=bas_d;
    while(temp->sonraki!=bas_d){
        temp=temp->sonraki;
    }
    temp->sonraki=yeni_dugum;
    yeni_dugum->sonraki=bas_d;
}
}
void tek_yonlu_hasta_sil(tek_yonlu_dairesel_node*& bas_d, int id) {
    if (bas_d == nullptr) {
        cout << "Liste bos, silme islemi yapilamaz." << endl;
        return;
    }

    tek_yonlu_dairesel_node* silinecek = nullptr;
    tek_yonlu_dairesel_node* onceki = nullptr;
    tek_yonlu_dairesel_node* temp = bas_d;

    // İlk düğümü kontrol et
    if (temp->hasta_bilgileri.ID == id) {
        silinecek = bas_d;
        while (temp->sonraki != bas_d) {
            temp = temp->sonraki;
        }
        temp->sonraki = bas_d->sonraki; // İlk düğümü atla
        bas_d = bas_d->sonraki; // Baş işaretçisini güncelle
        delete silinecek; // Düğümü sil
        return;
    }

    // İlk düğüm değilse diğer düğümleri kontrol et
    onceki = bas_d;
    temp = bas_d->sonraki;
    while (temp != bas_d) {
        if (temp->hasta_bilgileri.ID == id) {
            silinecek = temp;
            onceki->sonraki = temp->sonraki; // Silinecek düğümü atla
            delete silinecek; // Düğümü sil
            return;
        }
        onceki = temp;
        temp = temp->sonraki;
    }

    cout << "Belirtilen ID'ye sahip hasta bulunamadi." << endl;
}
int ucret_olustur(int hasta_ID){ 
   float ücret=1;
   for(int i=1; i<hasta_ID%10+1;i++){
    ücret*=i;
    ücret+=10;
   }
   return ücret;
}

void ameliyat_ekle(ameliyat_node*&bas_a,string ameliyat_adi,string ameliyat_tarihi,float ameliyat_saati,string isim,string soyisim,int hasta_ID,float ameliyat_ücreti){
ameliyat_ücreti= ucret_olustur(hasta_ID);
ameliyat yeni_ameliyat={ameliyat_adi,ameliyat_tarihi,ameliyat_saati,isim,soyisim,hasta_ID,ameliyat_ücreti};
ameliyat_node*yeni_Dugum= new ameliyat_node;
yeni_Dugum->ameliyat_bilgileri=yeni_ameliyat;
yeni_Dugum->sonraki_a=nullptr;
yeni_Dugum->onceki_a=nullptr;

if(bas_a==nullptr){
bas_a=yeni_Dugum;
return;
}
ameliyat_node*gecici_a=bas_a;
while(gecici_a->sonraki_a!=nullptr){
    gecici_a=gecici_a->sonraki_a;
}
gecici_a->sonraki_a=yeni_Dugum;
yeni_Dugum->onceki_a=gecici_a;
}
void tek_yonlu_ameliyat_ekle(tek_yonlu_dairesel_ameliyat_node*&bas_A,int hasta_ID,float ücret){
    ücret= ucret_olustur(hasta_ID);
    ameliyat yeni_ameliyat={"","",0,"","",hasta_ID,ücret};
    tek_yonlu_dairesel_ameliyat_node*yeni_dugum=new tek_yonlu_dairesel_ameliyat_node;
    yeni_dugum->ameliyat_bilgileri=yeni_ameliyat;
    if(bas_A==nullptr){
        bas_A=yeni_dugum;
        bas_A->sonraki=bas_A;
    }else{
        tek_yonlu_dairesel_ameliyat_node*temp=bas_A;
        while(temp->sonraki!=bas_A){
            temp=temp->sonraki;
        }
        temp->sonraki=yeni_dugum;
        yeni_dugum->sonraki=bas_A;
    }
}
void tek_yonlu_ameliyat_sil(tek_yonlu_dairesel_ameliyat_node*&bas_A,int hasta_ID){
    if(bas_A==nullptr){
        cout<<"liste boş, lütfen önce ameliyat ekleyiniz..."<<endl;
        return;
    }
    if(bas_A->ameliyat_bilgileri.hasta_ID==hasta_ID){
        tek_yonlu_dairesel_ameliyat_node*silinecek=bas_A;
        while(silinecek->sonraki!=bas_A){
            silinecek=silinecek->sonraki;
        }
        silinecek->sonraki=bas_A->sonraki;
        bas_A=bas_A->sonraki;
        delete silinecek;
        return;
    }
    tek_yonlu_dairesel_ameliyat_node*temp=bas_A;
    while(temp->sonraki!=bas_A&&temp->sonraki->ameliyat_bilgileri.hasta_ID!=hasta_ID){
        temp=temp->sonraki;
    }
    if(temp->sonraki==bas_A){
        cout<<"silinecek ameliyat bulunamadı..."<<endl;
        return;
    }
    tek_yonlu_dairesel_ameliyat_node*silinecek=temp->sonraki;
    temp->sonraki=silinecek->sonraki;
    delete silinecek;
}
void ameliyat_detayları(ameliyat_node*bas_a){
    ameliyat_node*gecici_a=bas_a;
    if(gecici_a==nullptr){
        cout<<"kayıtlı ameliyat yok"<<endl;
    }
    while(gecici_a!=nullptr){
        cout<<"ameliyat: "<<gecici_a->ameliyat_bilgileri.ameliyat_adi<<" | "<<"tarihi: "<<gecici_a->ameliyat_bilgileri.ameliyat_tarihi<<" | "<<"saati: "<<gecici_a->ameliyat_bilgileri.ameliyat_saati<<" | "<<"hasta adı-soyadı: "<<gecici_a->ameliyat_bilgileri.isim<<" "<<gecici_a->ameliyat_bilgileri.soyisim<<" | "<<"hastanın ID si:"<<gecici_a->ameliyat_bilgileri.hasta_ID<<endl;
        cout<<"-----------------------------------------------------------"<<endl;
        gecici_a=gecici_a->sonraki_a;
    }
}
void ameliyat_sil(ameliyat_node*bas_a,int hasta_ID){
    if(bas_a==nullptr){
        cout<<"liste boş, lütfen önce ameliyat ekleyiniz..."<<endl;
        return;
    }
    if(bas_a->ameliyat_bilgileri.hasta_ID==hasta_ID){
        ameliyat_node*silinecek_a=bas_a;
        bas_a=bas_a->sonraki_a;
        if (bas_a!=nullptr){
            bas_a->onceki_a=nullptr;    
        }
        delete silinecek_a;
            cout<<"ameliyat başarıyla silindi..."<<endl;
            return;
    }
    ameliyat_node*gecici_a=bas_a;
    while(gecici_a!=nullptr&&gecici_a->ameliyat_bilgileri.hasta_ID!=hasta_ID){
        gecici_a=gecici_a->sonraki_a;
    }
    if(gecici_a==nullptr){
        cout<<"silinecek ameliyat bulunamadı..."<<endl;
        return;
    }
    //silinen hastayı listeden çıkarma:
   
    if(gecici_a->onceki_a!=nullptr){
        gecici_a->onceki_a->sonraki_a=gecici_a->sonraki_a;
    }
    if(gecici_a->sonraki_a!=nullptr){
        gecici_a->sonraki_a->onceki_a=gecici_a->onceki_a;
    }
    delete gecici_a;
    cout<<"ameliyat başarıyla silindi..."<<endl;
}
void ücret_hesapla(ameliyat_node*bas_a,int hasta_ID){
    ameliyat_node*gecici_a=bas_a;
    if(gecici_a==nullptr){
        cout<<"kayıtlı ameliyat yok"<<endl;
    }
    while(gecici_a!=nullptr){
        if(gecici_a->ameliyat_bilgileri.hasta_ID==hasta_ID){
            cout<<"ameliyat ücreti: "<<gecici_a->ameliyat_bilgileri.ameliyat_ucreti<<endl;
        }
        gecici_a=gecici_a->sonraki_a;
    }
}
void hasta_ekleme(node*&bas,string isim,string soyisim, string cinsiyet,int yas, int ID,string tanı){
   hasta yeni_hasta= {isim,soyisim,cinsiyet,yas,ID,tanı};
   node* yeni_dugum = new node;
   yeni_dugum->hasta_bilgileri=yeni_hasta;
   yeni_dugum->sonraki=nullptr;
   yeni_dugum->onceki=nullptr;
   if (bas==nullptr){
    bas=yeni_dugum;
    return;
   }
   node* gecici=bas;
   while(gecici->sonraki!=nullptr){
    gecici=gecici->sonraki;
   }
   gecici->sonraki=yeni_dugum;
   yeni_dugum->onceki=gecici;
}
void hasta_detayları(node*bas){
    node*gecici=bas;
    if(gecici==nullptr){
        cout<<"hasta bulunamadı..."<<endl;
    }
    while(gecici!=nullptr){
        cout<<"hasta adı: "<<gecici->hasta_bilgileri.ad<<" "<<gecici->hasta_bilgileri.soyad<<" | "<<"cinsiyet: "<<gecici->hasta_bilgileri.cinsiyet<<" | "<<"yaş: "<<gecici->hasta_bilgileri.yas<<" | "<<" ID: "<<gecici->hasta_bilgileri.ID<<" | "<<"tanı: "<<gecici->hasta_bilgileri.tanı<<endl;
        gecici=gecici->sonraki;
    }
}
void hasta_sil(node*bas,int ID){
    if(bas==nullptr){
        cout<<"liste boş, lütfen önce hasta ekleyiniz..."<<endl;
        return;
    }
    if(bas->hasta_bilgileri.ID==ID){
        node*silinecek=bas;
        bas=bas->sonraki;
        if (bas!=nullptr){
            bas->onceki=nullptr;    
        }
        delete silinecek;
            cout<<"hasta başarıyla silindi..."<<endl;
            return;
    }
    node*gecici=bas;
    while(gecici!=nullptr&&gecici->hasta_bilgileri.ID!=ID){
        gecici=gecici->sonraki;
    }
    if(gecici==nullptr){
        cout<<"silinecek hasta bulunamadı..."<<endl;
        return;
    }
    //silinen hastayı listeden çıkarma:
   
    if(gecici->onceki!=nullptr){
        gecici->onceki->sonraki=gecici->sonraki;
    }
    if(gecici->sonraki!=nullptr){
        gecici->sonraki->onceki=gecici->onceki;
    }
    delete gecici;
    cout<<"hasta başarıyla silindi..."<<endl;
}
void hasta_aktar(node*bas,dairesel_node_hasta*dairesel_bas_h){
    node*gecici=bas;
    if(gecici==nullptr){
        cout<<"hasta bulunamadı..."<<endl;
    }
    while(gecici!=nullptr){
        dairesel_node_hasta*yeni_dugum_h=new dairesel_node_hasta;
        yeni_dugum_h->hasta_bilgileri=gecici->hasta_bilgileri;
        yeni_dugum_h->sonraki_h=nullptr;
        yeni_dugum_h->onceki_h=nullptr;
        if(dairesel_bas_h==nullptr){
            dairesel_bas_h=yeni_dugum_h;
        }else{
            dairesel_node_hasta*gecici_h=dairesel_bas_h;
            while(gecici_h->sonraki_h!=nullptr){
                gecici_h=gecici_h->sonraki_h;
            }
            gecici_h->sonraki_h=yeni_dugum_h;
            yeni_dugum_h->onceki_h=gecici_h;
        }
        gecici=gecici->sonraki;
    }
    while(dairesel_bas_h->sonraki_h!=nullptr){
        dairesel_bas_h=dairesel_bas_h->sonraki_h;
        cout<<"hasta ad-soyad: "<<dairesel_bas_h->hasta_bilgileri.ad<<" "<<dairesel_bas_h->hasta_bilgileri.soyad<<endl;
    }
}
void ameliyat_aktar(ameliyat_node* bas_a, dairesel_node_ameliyat* dairesel_bas_a) {
    ameliyat_node* gecici_a = bas_a;
    if (gecici_a == nullptr) {
        cout << "ameliyat bulunamadı..." << endl;
    }
    while (gecici_a != nullptr) {
        dairesel_node_ameliyat* yeni_dugum_a = new dairesel_node_ameliyat;
        yeni_dugum_a->ameliyat_bilgileri = gecici_a->ameliyat_bilgileri;
        yeni_dugum_a->sonraki_a = nullptr;
        yeni_dugum_a->onceki_a = nullptr;
        if (dairesel_bas_a == nullptr) {
            dairesel_bas_a = yeni_dugum_a;
        } else {
            dairesel_node_ameliyat* gecici_b = dairesel_bas_a;
            while (gecici_b->sonraki_a != nullptr) {
                gecici_b = gecici_b->sonraki_a;
            }
            gecici_b->sonraki_a = yeni_dugum_a;
            yeni_dugum_a->onceki_a = gecici_b;
        }
        gecici_a = gecici_a->sonraki_a;
    }

    // Burada bütün hastaları yazdırma işlemi gerçekleştirilecek
    dairesel_node_ameliyat* gecici_b = dairesel_bas_a;
    while (gecici_b != nullptr) {
        cout << "ameliyat hastası: " << gecici_b->ameliyat_bilgileri.isim << " " << gecici_b->ameliyat_bilgileri.soyisim << endl;
        gecici_b = gecici_b->sonraki_a;
    }
}
int hesaplaOncelikPuanı(string cinsiyet, int yas) {
    int oncelik_puani = 0;

   
    if (cinsiyet == "erkek") {
        oncelik_puani += 2; 
    } else if (cinsiyet == "kadın") {
        oncelik_puani += 4; 
    }
    if (yas < 18) {
        oncelik_puani += 5; 
    } else if (yas >= 65) {
        oncelik_puani += 3; 
    }else{
        oncelik_puani+=4;
    }

    return oncelik_puani;
}
void hesapla_ve_yazdir_puan(node* bas, dairesel_node_hasta_puan* dairesel_bas_hp) {
    node* gecici = bas;
    if (gecici == nullptr) {
        cout << "Hasta bulunamadı..." << endl;
        return;
    }
    dairesel_node_hasta_puan* onceki = nullptr;
    while (gecici != nullptr) {
        int oncelik_puani = hesaplaOncelikPuanı(gecici->hasta_bilgileri.cinsiyet, gecici->hasta_bilgileri.yas);
        dairesel_node_hasta_puan* yeni_dugum_hp = new dairesel_node_hasta_puan;
        yeni_dugum_hp->hasta_bilgileri = gecici->hasta_bilgileri;
        yeni_dugum_hp->oncelik_puani = oncelik_puani;
        yeni_dugum_hp->onceki_hasta = nullptr;
        yeni_dugum_hp->sonraki_hasta = nullptr;

        // Yeni düğümü dairesel bağlı listeye ekle
        if (dairesel_bas_hp == nullptr) {
            dairesel_bas_hp = yeni_dugum_hp;
            yeni_dugum_hp->onceki_hasta = yeni_dugum_hp;
            yeni_dugum_hp->sonraki_hasta = yeni_dugum_hp;
        } else {
            yeni_dugum_hp->onceki_hasta = onceki;
            yeni_dugum_hp->sonraki_hasta = dairesel_bas_hp;
            onceki->sonraki_hasta = yeni_dugum_hp;
            dairesel_bas_hp->onceki_hasta = yeni_dugum_hp;
        }

        // Hasta bilgilerini ve puanlarını yazdır
        cout << "Hasta adı: " << gecici->hasta_bilgileri.ad << " " << gecici->hasta_bilgileri.soyad
             << " | Öncelik Puanı: " << oncelik_puani << endl;

        onceki = yeni_dugum_hp;
        gecici = gecici->sonraki;
    }
}

int doktor_girisi(vector<doktor>&doktor_listesi) {
    // Doktorları ekleme
    doktor dr1 = {"berk_sag", "berk123", "Dr.Berk", "Sağlamtaş"};
    doktor dr2 = {"cema_ars", "cema123", "Dr.Cem Ali", "Arslan"};
    doktor dr3 = {"rumi_kap", "rumi123", "Dr.Rumeysa", "Kaplan"};
    doktor dr4 = {"sinoşum_sag", "sinoş123", "Dr.Sinan", "Sağlamtaş"};
    doktor dr5 = {"ustun_ars", "ustun123", "Dr.Üstünay", "Arslan"};
    
    // Doktorları vektöre ekleme
    doktor_listesi.insert(doktor_listesi.begin(),dr1);
    doktor_listesi.push_back(dr2);
    doktor_listesi.push_back(dr3);
    doktor_listesi.push_back(dr4);
    doktor_listesi.push_back(dr5);
    
    int kodlu_giris_denemesi=0;
    int giris_denemesi=0;
    string rastgele_string;
    int uzunluk=8;
    while(kodlu_giris_denemesi<3&&giris_denemesi<3){
    
        cout<<"kullanıcı adını giriniz:"<<endl;
        string kullanici_adi;
        cin>>kullanici_adi;
        cout<<"şifreyi giriniz:"<<endl; 
        string sifre;
        cin>>sifre;
        giris_denemesi++;
        rastgele_string="";
        for(size_t i=0;i<doktor_listesi.size();++i){
            if(kullanici_adi==doktor_listesi[i].kullanici_adi&&sifre==doktor_listesi[i].sifre){
                cout<<"giriş başarılı..."<<endl;
                cout<<"---------------------------"<<endl;
                return 0;
            }
        }
        cout<<"kullanıcı adı ya da şifre hatalı..."<<endl;
         cout<<"kalan giris hakkınız: "<<3-giris_denemesi<<endl;
        for(int i=0;i<uzunluk;i++){
            char rastgele_harf='a'+rand()%26;
            rastgele_string +=rastgele_harf;
        }
        cout<<rastgele_string<<endl;
        cout<<"yukarıdaki kodu giriniz: "<<endl;
        string kod; 
        cin>>kod;
        if(kod==rastgele_string){
            cout<<"kodu doğru girdiniz"<<endl;
            cout<<"---------------------------"<<endl;
            cout<<"kulllanıcı adı ve şifreyi tekrardan girebilirsiniz:"<<endl;
            rastgele_string="";
        }else{
            cout<<"kodu yanlış girdiniz..."<<endl;
            rastgele_string="";
            kodlu_giris_denemesi++;
            rastgele_string="";
        cout<<"güvenlik kodunu doğru girebilmek için kalan hakkınız: "<<3-kodlu_giris_denemesi<<endl;
        cout<<"tekrardan güvenlik kodunu giriniz:"<<endl;
         for(int ii=0;ii<uzunluk;++ii){
            char rastgele_harf='b'+rand()%26;
            rastgele_string +=rastgele_harf;
         }
         cout<<rastgele_string<<endl;
         cin>>kod;
         if(kod==rastgele_string){
            cout<<"kodu doğru girdiniz"<<endl;
            cout<<"----------------------------"<<endl;
            cout<<"kullanıcı adı ve şifreyi tekrardan girebilirsiniz:"<<endl;
         }else{
              cout<<"kodu yanlış girdiniz..."<<endl;
            kodlu_giris_denemesi++;
        cout<<"kalan hakkınız: "<<3-kodlu_giris_denemesi<<endl;
        rastgele_string="";
        cout<<"tekrardan güvenlik kodunu giriniz:"<<endl;
         for(int iii=0;iii<uzunluk;++iii){
            char rastgele_harf='c'+rand()%26;
            rastgele_string +=rastgele_harf;
         }
         cout<<rastgele_string<<endl;
         cin>>kod;
         if(kod==rastgele_string){
            cout<<"kodu doğru girdiniz... tekrardan giriş yapabilirsiniz"<<endl;
            cout<<"----------------------------"<<endl;
         }else{
            kodlu_giris_denemesi++;
            cout<<"maalesef giriş hakkınız doldu..."<<endl;
         }
        }
    }
}
if(kodlu_giris_denemesi>=3||giris_denemesi>=3){
    cout<<"daha sonra tekrar deneyiniz..."<<endl;
   sleep(120);
   doktor_girisi(doktor_listesi);
}
return 0;
}
void doktor_ekle(doktor_node*& doktor_bas, string isim, string soyisim) {
    doktor_node* yeni_dugum = new doktor_node;
    yeni_dugum->doktor_bilgileri.kullanici_adi = ""; 
    yeni_dugum->doktor_bilgileri.sifre = "";
    yeni_dugum->doktor_bilgileri.isim = isim;
    yeni_dugum->doktor_bilgileri.soyisim = soyisim;
    yeni_dugum->onceki = nullptr;
    yeni_dugum->sonraki = nullptr;

    if (doktor_bas == nullptr) {
        doktor_bas = yeni_dugum;
        yeni_dugum->onceki = yeni_dugum;
        yeni_dugum->sonraki = yeni_dugum;
        return;
    }
    doktor_node* son = doktor_bas->onceki;
    son->sonraki = yeni_dugum;
    yeni_dugum->onceki = son;
    yeni_dugum->sonraki = doktor_bas;
    doktor_bas->onceki = yeni_dugum;
}

void doktorlari_yazdir(doktor_node* doktor_bas) {
    if (doktor_bas == nullptr) {
        cout << "Doktor bulunamadı." << endl;
        return;
    }
    doktor_node* iter = doktor_bas;
    do {
        cout << "Doktor adı: " << iter->doktor_bilgileri.isim << " " << iter->doktor_bilgileri.soyisim << endl;
        iter = iter->sonraki;
    } while (iter != doktor_bas);
}


void hasta_demo(tek_yonlu_dairesel_node*bas_d){
     if (bas_d == nullptr) {
        cout << "Liste bos." << endl;
        return;
    }
    int toplamKadin = 0;
    int toplamErkek = 0;
    int toplamGenc = 0;
    int toplamYasli = 0;
    int toplamYetiskin = 0;

    tek_yonlu_dairesel_node* temp = bas_d;
    do {
        if (temp->hasta_bilgileri.cinsiyet == "kadın") {
            toplamKadin++;
        } else {
            toplamErkek++;
        }
        if (temp->hasta_bilgileri.yas <= 18) {
            toplamGenc++;
        } else if (temp->hasta_bilgileri.yas >= 65) {
            toplamYasli++;
        } else {
            toplamYetiskin++;
        }
        temp = temp->sonraki;
    } while (temp != bas_d);

    cout << "Toplam kadin hasta sayisi: " << toplamKadin << endl;
    cout << "Toplam erkek hasta sayisi: " << toplamErkek << endl;
    cout << "Toplam genc hasta sayisi (18 yas alti): " << toplamGenc << endl;
    cout << "Toplam yasli hasta sayisi (65 yas ve ustu): " << toplamYasli << endl;
    cout << "Toplam yetiskin hasta sayisi (18-65 yas arasi): " << toplamYetiskin << endl; 
}
void hastane_geliri(tek_yonlu_dairesel_ameliyat_node*bas_A){
    if(bas_A==nullptr){
    cout<<"kayıt bulunamadı..."<<endl;
    }
    tek_yonlu_dairesel_ameliyat_node*temp=bas_A;
    float toplam_ücret=0;
   do{
         toplam_ücret+=temp->ameliyat_bilgileri.ameliyat_ucreti;
         temp=temp->sonraki;
   }while(temp!=bas_A);
   cout<<"hastanenin ameliyatlardan kazandığı gelir: "<<toplam_ücret<<" TL"<<endl;
}
void hastane_degerlendir(degerlendir_node*& bas_D) {
    int dr_perf, hasta_mem, hizmet_kal;
    cout << "Doktor performansını 1 ile 5 arasında değerlendirin: (1 en kötü 5 en iyi)" << endl;
    cin >> dr_perf;
    cout << "Hasta memnuniyetini 1 ile 5 arasında değerlendirin: (1 en kötü 5 en iyi)" << endl;
    cin >> hasta_mem;
    cout << "Hizmet kalitesini 1 ile 5 arasında değerlendirin: (1 en kötü 5 en iyi)" << endl;
    cin >> hizmet_kal;
    degerlendir_node* yeni_dugum = new degerlendir_node;
    yeni_dugum->hastane_bilgileri.dr_perf = dr_perf;
    yeni_dugum->hastane_bilgileri.hasta_memnuniyet = hasta_mem;
    yeni_dugum->hastane_bilgileri.hizmet_kalitesi = hizmet_kal;
    if (bas_D == nullptr) {
        bas_D = yeni_dugum;
        bas_D->sonraki = bas_D; 
    } else {
        degerlendir_node* temp = bas_D;
        while (temp->sonraki != bas_D) {
            temp = temp->sonraki;
        }
        temp->sonraki = yeni_dugum;
        yeni_dugum->sonraki = bas_D; 
}
}
void degerlendirme_yazdir(degerlendir_node* bas_D) {
    if (bas_D == nullptr) {
        cout << "Değerlendirme bulunamadı..." << endl;
        return;
    }
    degerlendir_node* gecici_D = bas_D;
    do {
        cout << "Doktor performansı: " << gecici_D->hastane_bilgileri.dr_perf << " | "
             << "Hasta memnuniyeti: " << gecici_D->hastane_bilgileri.hasta_memnuniyet << " | "
             << "Hizmet kalitesi: " << gecici_D->hastane_bilgileri.hizmet_kalitesi << endl;
        gecici_D = gecici_D->sonraki;
    } while (gecici_D != bas_D);
}

int main(){  
 node*bas=nullptr;
 ameliyat_node*bas_a=nullptr;
 doktor_node*doktor_bas=nullptr;
 dairesel_node_hasta*dairesel_bas_h=nullptr;
 dairesel_node_ameliyat*dairesel_bas_a=nullptr;
 dairesel_node_hasta_puan*dairesel_bas_hp=nullptr;
 tek_yonlu_dairesel_node*bas_d=nullptr;
 tek_yonlu_dairesel_ameliyat_node*bas_A=nullptr;
 degerlendir_node*bas_D=nullptr;
 //doktorları yazdırma işlemi için doktorları dairesel bağlı listeye ekleyelim:
 doktor_ekle(doktor_bas,"Dr.berk","saglamtas");
 doktor_ekle(doktor_bas,"Dr.cem ali","arslan");
 doktor_ekle(doktor_bas,"Dr.rumeysa","kaplan");
 doktor_ekle(doktor_bas,"Dr.sinan","saglamtas");
 doktor_ekle(doktor_bas,"Dr.üstünay","arslan");
 //önceden eklenmiş hastalar olsun diye:
 hasta_ekleme(bas,"ali","galvan","erkek",25,153319,"grip");
 hasta_ekleme(bas,"sevda","sag","kadın",21,153320,"beyin hasarı");
 hasta_ekleme(bas,"meva","saglam","kadın",17,120023,"kaporta yanmış");
 hasta_ekleme(bas,"sinem","can","kadın",66,120024,"psikolojisi bozuk");
tek_yonlu_hasta_ekle(bas_d,"erkek",25,153319);
tek_yonlu_hasta_ekle(bas_d,"kadın",21,153320);
tek_yonlu_hasta_ekle(bas_d,"kadın",17,120023);
tek_yonlu_hasta_ekle(bas_d,"kadın",66,120024);
//önceden eklenmiş ameliyatlar olsun diye:
ameliyat_ekle(bas_a,"apandisit","12/12/2024",14.30,"merve","dalyan",123456,0);
ameliyat_ekle(bas_a,"kalp ameliyatı","13/05/2024",10.00,"ismail","koru",123457,0);
ameliyat_ekle(bas_a,"beyin nakli","14/05/2024",09.00,"mustafa","mahir",123458,0);
tek_yonlu_ameliyat_ekle(bas_A,123456,0);
tek_yonlu_ameliyat_ekle(bas_A,123457,0);
tek_yonlu_ameliyat_ekle(bas_A,123458,0);
cout<<"MEVA VAKIF HASTANESİNE Hoşgeldiniz... doktor girişi için 1 e hasta girişi için 2 ye değerlendirme için 3 e basınız: "<<endl;
int giris;
cin>>giris;
if(giris==1){
    cout<<"doktor girişi için belirtilen işlemleri yapnız:"<<endl;
    cout<<"-----------------------------------------------"<<endl;
    vector<doktor>doktor_listesi;
 doktor_girisi(doktor_listesi);
    cout<<"hasta sistemine hoşgeldiniz lütfen aşağıdaki seçeneklerden seçim yapınız:"<<endl;
    int devam=1;
    while(devam!=0){
 cout<<"doktor sistemine hoşgeldiniz lütfen yapmak istediğiniz işlemi seçin:"<<endl;
 cout<<"1-hasta ekle"<<endl;
 cout<<"2-ID bilgisi kullanarak hasta sil"<<endl;
 cout<<"3-hasta detaylarını getir"<<endl;
 cout<<"4-ameliyat ekle"<<endl;
 cout<<"5-ameliyatı sil"<<endl;
 cout<<"6-ameliyat detaylarını getir"<<endl;
 cout<<"7- ID'ye göre ameliyat ücretini hesapla"<<endl;
 cout<<"8-ana menüye dön"<<endl;
 cout<<"9-çıkış"<<endl;
 int secim;
 cin>>secim;
 if (secim==1){
 cout<<"hasta ekleme işlemi seçildi..."<<endl;
    int tamam_mı_devam_mı=1;
    while(tamam_mı_devam_mı!=0){
        cout<<"hasta adını giriniz"<<endl;
        string isim;
        cin>>isim;
        cout<<"hasta soyadını giriniz"<<endl;
        string soyisim;
        cin>>soyisim;
        cout<<"hasta cinsiyetini giriniz"<<endl;
        string cinsiyet;
        cin>>cinsiyet;
        cout<<"hasta yaşını giriniz"<<endl;
        int yas;
        cin>>yas;
        cout<<"hasta ID bilgisini giriniz"<<endl;
        int ID;
        cin>>ID;
        cout<<"hasta tanısını giriniz"<<endl;
        string tanı;
        cin>>tanı;
        hasta_ekleme(bas,isim,soyisim,cinsiyet,yas,ID,tanı);
        tek_yonlu_hasta_ekle(bas_d,cinsiyet,yas,ID);
        cout<<"hasta eklemeye devam etmek için 1 e bitirmek için 0 a basınız:"<<endl;
        cin>>tamam_mı_devam_mı;
    };
    cout<<"başka işlem yapmak istiyorsanız 1 e istemiyorsanız 0 a basınız: "<<endl;
        cin>>devam;
    }else if(secim==2){
        cout<<"ID bilgisi kullanarak hasta silme işlemi seçildi..."<<endl;
        cout<<"silinecek hasta ID bilgisini giriniz: "<<endl;
        int ID2;
        cin>>ID2;
        hasta_sil(bas,ID2);
        tek_yonlu_hasta_sil(bas_d,ID2);
    cout<<"başka işlem yapmak istiyorsanız 1 e istemiyorsanız 0 a basınız: "<<endl;
        cin>>devam;
    }else if(secim==3){
        cout<<"hasta detaylarını getirme işlemi seçildi..."<<endl;
        hasta_detayları(bas);
        cout<<"başka işlem yapmak istiyorsanız 1 e istemiyorsanız 0 a basınız: "<<endl;
        cin>>devam;
    }else if(secim==4){
        cout<<"ameliyat ekleme işlemi seçildi..."<<endl;
        int tamam_ya_da_devam=1;
        while(tamam_ya_da_devam!=0){ 
            cout<<"ameliyat adını giriniz: "<<"(lütfen bitişik şekilde ya da _ kullanarak yazın)"<<endl;
            string ameliyat_adı;
            cin>>ameliyat_adı;
            cout<<"ameliyat tarihini girin: "<<"(gg/aa/yyyy)"<<endl;
            string tarih;
            cin>>tarih;
            cout<<"ameliyat saatini girin: "<<"(sa.dk)"<<endl;
            float saat;
            cin>>saat;
            cout<<"ameliyat olacak hastanın ismini giriniz:"<<endl;
            string isim2;
            cin>>isim2;
            cout<<"ameliyat olacak hastanın soyismini giriniz:"<<endl;
            string soyisim2;
            cin>>soyisim2;
            int ID_a;
            cout<<"ameliyat olacak hastanın ID sini giriniz:"<<endl;
            cin>>ID_a;
            ameliyat_ekle(bas_a,ameliyat_adı,tarih,saat,isim2,soyisim2,ID_a,0);
            tek_yonlu_ameliyat_ekle(bas_A,ID_a,0);
            cout<<"ameliyat eklemeye devam etmek istiyorsanız 1 e istemiyorsanız 0 a basın: "<<endl;
            cin>>tamam_ya_da_devam;
        };
        cout<<"başka işlem yapmak istiyorsanız 1 e istemiyorsanız 0 a basınız: "<<endl;
        cin>>devam;
    }else if(secim==5){
        int tamam_devam=1;
        while(tamam_devam!=0){        
        cout<<"ameliyatı silme işlemi seçildi..."<<endl;
        cout<<"silinecek ameliyatın ID sini giriniz: "<<endl;
        int ID_A;
        cin>>ID_A;
        ameliyat_sil(bas_a,ID_A);
        tek_yonlu_ameliyat_sil(bas_A,ID_A);
        cout<<"ameliyatı silmeye devam etmek istiyorsanız 1 e istemiyorsanız 0 a basınız: "<<endl;
        cin>>tamam_devam;
        }
        cout<<"başka işlem yapmak istiyorsanız 1 e istemiyorsanız 0 a basınız: "<<endl;
        cin>>devam;
    }else if(secim==6){
        cout<<"ameliyat detaylarını getirme işlemi seçildi..."<<endl;
            ameliyat_detayları(bas_a);
        cout<<"başka işlem yapmak istiyorsanız 1 e istemiyorsanız 0 a basınız: "<<endl;
        cin>>devam;
    }else if(secim==7){
        int yeto=1;
        while(yeto!=0){
        cout<<"ID'ye göre ameliyat ücretini hesapla işlemi seçildi..."<<endl;
        cout<<"ameliyat ücretini hesaplamak istediğiniz hastanın ID sini giriniz: "<<endl;
        int ID_A;
        cin>>ID_A;
        ücret_hesapla(bas_a,ID_A);
        cout<<"başka ücret hesaplamak istiyorsanız 1 e istemiyorsanız 0 a basınız: "<<endl;
        cin>>yeto;
        }
        cout<<"başka işlem yapmak istiyorsanız 1 e istemiyorsanız 0 a basınız: "<<endl;
        cin>>devam;
    }else if(secim==8){
        cout<<"ana menüye dönme işlemi seçildi..."<<endl;
        main();
        return 0;
    }else if (secim==9){
        cout<<"çıkış yapılıyor..."<<endl;
        return 0;
    }else{
        cout<<"geçersiz seçim yaptınız..."<<endl;
        cout<<"tekrar deneyiniz..."<<endl;
        devam=1;
    }
    }
}else if(giris==2){
    int hasta_devam=1;
    while(hasta_devam!=0){
     cout<<"hasta girişine hoşgeldiniz..."<<endl;
     cout<<"---------------------------------"<<endl;
     cout<<"lütfen yaoacağınız işlemi seçiniz: "<<endl;
     cout<<"1-hastane doktorlarını yazdır"<<endl;
     cout<<"2-tüm hastaları yazdır"<<endl;
     cout<<"3-ameliyat hastalarını yazdır"<<endl;
     cout<<"4-hastaların öncelik puanlarını yazdır"<<endl;
     cout<<"5-ana menüye dön"<<endl;
     cout<<"6-çıkış"<<endl;
     cout<<"---------------------------------"<<endl;
        int secim2;
        cin>>secim2;
    if(secim2==1){
        cout<<"doktor yazdırma işlemi seçildi..."<<endl;
        doktorlari_yazdir(doktor_bas);
        cout<<"başka işlem yapmak istiyorsanız 1 e istemiyorsanız 0 a basın:"<<endl;
        cin>>hasta_devam;
    }else if(secim2==2){
        cout<<"tüm hastaları yazdırma işlemi seçildi..."<<endl;
        hasta_aktar(bas,dairesel_bas_h);
        cout<<"başka işlem yapmak istiyorsanız 1 e istemiyorsanız 0 a basın:"<<endl;
        cin>>hasta_devam;
    }else if(secim2==3){
        cout<<"ameliyat hastalarını yazdırma işlemi seçildi..."<<endl;
        ameliyat_aktar(bas_a,dairesel_bas_a);
        cout<<"başka işlem yapmak istiyorsanız 1 e istemiyorsanız 0 a basın:"<<endl;
        cin>>hasta_devam;
    }else if(secim2==4){
        cout<<"hastaların öncelik puanlarını yazdırma işlemi seçildi..."<<endl;
        hesapla_ve_yazdir_puan(bas,dairesel_bas_hp);

        cout<<"başka işlem yapmak istiyorsanız 1 e istemiyorsanız 0 a basın:"<<endl;
        cin>>hasta_devam;
    }else if (secim2==5){
        cout<<"ana menüye dönülüyor..."<<endl;
        main();
        return 0;
    }else if(secim2==6){
        cout<<"çıkış yapılıyor..."<<endl;
        return 0;
    }
    }
}else if(giris==3){
    int d_devam=1;
    while(d_devam!=0){
cout<<"değerlendirme kısmına hoşgeldiniz..."<<endl;
cout<<"---------------------------------"<<endl;
cout<<"lütfen yapmak istediğiniz işlemi seçiniz: "<<endl;
cout<<"-----------------------------------------------"<<endl;
cout<<"1-hastaların demografik yapısını göster"<<endl;
cout<<"2-hastanenin ameliyatlardan kazandığı para miktarını göster"<<endl;
cout<<"3-hastaneyi değerlendir"<<endl;
cout<<"4-değerlendirme sonuçlarını göster"<<endl;
cout<<"5-ana menüye dön"<<endl;
cout<<"6-çıkış"<<endl;
int secim3;
cin>>secim3;
if(secim3==1){
cout<<"hastaların demografik yapısını gösterme işlemi seçildi..."<<endl;
hasta_demo(bas_d);
cout<<"başka işlem yapmak istiyorsanız 1 e istemiyorsanız 0 a basın:"<<endl;
cin>>d_devam;
}else if(secim3==2){
    cout<<"hastanenin ameliyatlardan kazandığı para miktarını gösterme işlemi seçildi..."<<endl;
    hastane_geliri(bas_A);
cout<<"başka işlem yapmak istiyorsanız 1 e istemiyorsanız 0 a basın:"<<endl;
cin>>d_devam;
}else if(secim3==3){
    cout<<"hastaneyi değerlendirme işlemi seçildi..."<<endl;
    hastane_degerlendir(bas_D);
cout<<"başka işlem yapmak istiyorsanız 1 e istemiyorsanız 0 a basın:"<<endl;
cin>>d_devam;
}else if(secim3==4){
    cout<<"değerlendirme sonuçlarını gösterme işlemi seçildi..."<<endl;
    degerlendirme_yazdir(bas_D);
    cout<<"başka işlem yapmak istiyorsanız 1 e istemiyorsanız 0 a basın:"<<endl;
    cin>>d_devam;
}else if(secim3==5){
cout<<"ana menüye dönülüyor..."<<endl;
main();
}else if(secim3==6){
cout<<"çıkış yapılıyor..."<<endl;
return 0;
}else{
 cout<<"geçersiz giriş yaptınız..."<<endl;
}
    }
}else{
    cout<<"geçersiz giriş yaptınız..."<<endl;
}
return 0;
}