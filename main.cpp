

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <algorithm>

using namespace std;

// Görev Durumları
enum GorevDurumu { BEKLEMEDE, DEVAM_EDIYOR, TAMAMLANDI };

class IsUnitesi {
public:
    int id;
    string baslik;
    string detay;
    GorevDurumu durum;
    string kayit_tarihi;

    IsUnitesi(int _id, string _b, string _d, GorevDurumu _s) {
        id = _id;
        baslik = _b;
        detay = _d;
        durum = _s;
        
        // Zaman damgası oluşturma
        time_t simdi = time(0);
        char* dt = ctime(&simdi);
        string s(dt);
        kayit_tarihi = s.substr(0, s.length() - 1); 
    }

    string durumMetni() const {
        switch(durum) {
            case BEKLEMEDE: return "Beklemede";
            case DEVAM_EDIYOR: return "Devam Ediyor";
            case TAMAMLANDI: return "Tamamlandi";
            default: return "Bilinmiyor";
        }
    }
};

class SistemKontrol {
private:
    vector<IsUnitesi> veri_havuzu;
    const string VERI_YOLU = "sistem_kayitlari.dat";

public:
    SistemKontrol() {
        verileriYukle();
    }

    void yeniGorevOlustur() {
        string b, d;
        int yeniId = (veri_havuzu.empty()) ? 1001 : veri_havuzu.back().id + 1;

        cout << "\n[SISTEM] Yeni Gorev Girisi" << endl;
        cout << "Baslik: ";
        cin.ignore();
        getline(cin, b);
        cout << "Detayli Aciklama: ";
        getline(cin, d);

        veri_havuzu.push_back(IsUnitesi(yeniId, b, d, BEKLEMEDE));
        cout << ">> Veri sisteme islendi." << endl;
    }

    void tabloyuYazdir() {
        if (veri_havuzu.empty()) {
            cout << "\n[!] Sistemde kayitli gorev bulunamadi." << endl;
            return;
        }

        cout << "\n" << setfill('-') << setw(75) << "" << endl;
        cout << left << setw(8) << "ID" << setw(20) << "BASLIK" << setw(18) << "DURUM" << "KAYIT TARIHI" << endl;
        cout << setfill('.') << setw(75) << "" << setfill(' ') << endl;

        for (const auto& is : veri_havuzu) {
            cout << left << setw(8) << is.id 
                 << setw(20) << (is.baslik.length() > 18 ? is.baslik.substr(0, 16) + ".." : is.baslik)
                 << setw(18) << is.durumMetni() 
                 << is.kayit_tarihi << endl;
        }
        cout << setfill('-') << setw(75) << "" << endl;
    }

    void durumGuncelle() {
        int hedefId, secim;
        tabloyuYazdir();
        if (veri_havuzu.empty()) return;
        
        cout << "\nGuncellenecek Gorev ID: ";
        cin >> hedefId;

        for (auto& is : veri_havuzu) {
            if (is.id == hedefId) {
                cout << "Yeni Durum (0:Beklemede, 1:Devam Ediyor, 2:Tamamlandi): ";
                cin >> secim;
                is.durum = static_cast<GorevDurumu>(secim);
                cout << ">> Durum senkronize edildi." << endl;
                return;
            }
        }
        cout << "[HATA] Kayit bulunamadi." << endl;
    }

    void kayitSil() {
        int hedefId;
        cout << "\nSilinecek Gorev ID: ";
        cin >> hedefId;

        auto it = remove_if(veri_havuzu.begin(), veri_havuzu.end(), [hedefId](IsUnitesi const& i) {
            return i.id == hedefId;
        });

        if (it != veri_havuzu.end()) {
            veri_havuzu.erase(it, veri_havuzu.end());
            cout << ">> Kayit sistemden temizlendi." << endl;
        } else {
            cout << "[HATA] Islem basarisiz: ID bulunamadi." << endl;
        }
    }

    void verileriKaydet() {
        ofstream dosya(VERI_YOLU);
        for (const auto& i : veri_havuzu) {
            dosya << i.id << "|" << i.baslik << "|" << i.detay << "|" << i.durum << "|" << i.kayit_tarihi << endl;
        }
        dosya.close();
    }

    void verileriYukle() {
        ifstream dosya(VERI_YOLU);
        if (!dosya.is_open()) return;
        string satir;
        while (getline(dosya, satir)) {
            try {
                size_t p1 = satir.find('|');
                size_t p2 = satir.find('|', p1 + 1);
                size_t p3 = satir.find('|', p2 + 1);
                size_t p4 = satir.find('|', p3 + 1);

                int id = stoi(satir.substr(0, p1));
                string b = satir.substr(p1 + 1, p2 - p1 - 1);
                string d = satir.substr(p2 + 1, p3 - p2 - 1);
                GorevDurumu s = static_cast<GorevDurumu>(stoi(satir.substr(p3 + 1, p4 - p3 - 1)));
                string kt = satir.substr(p4 + 1);

                IsUnitesi gecici(id, b, d, s);
                gecici.kayit_tarihi = kt;
                veri_havuzu.push_back(gecici);
            } catch (...) { continue; }
        }
        dosya.close();
    }
};

int main() {
    SistemKontrol kontrolcu;
    int islem = 0;

    do {
        cout << "\n--- GOKHAN GOREV MERKEZI v1.1 ---" << endl;
        cout << "1. Listeyi Goruntule\n2. Yeni Gorev Ekle\n3. Durum Guncelle\n4. Gorevi Sil\n5. Verileri Kaydet ve Cik\n>> Seciminiz: ";
        if (!(cin >> islem)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch(islem) {
            case 1: kontrolcu.tabloyuYazdir(); break;
            case 2: kontrolcu.yeniGorevOlustur(); break;
            case 3: kontrolcu.durumGuncelle(); break;
            case 4: kontrolcu.kayitSil(); break;
            case 5: 
                kontrolcu.verileriKaydet(); 
                cout << "Veriler kaydedildi. Oturum sonlandiriliyor..." << endl; 
                break;
            default: cout << "Gecersiz islem kodu." << endl;
        }
    } while (islem != 5);

    return 0;
}
