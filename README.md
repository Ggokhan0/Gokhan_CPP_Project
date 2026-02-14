# 🚀 G-Task Core (Gelişmiş Görev Yönetim Sistemi)

G-Task Core, C++ dili kullanılarak geliştirilmiş, terminal tabanlı bir verimlilik aracıdır. Bu proje, temel programlama mantığının ötesine geçerek **Nesne Yönelimli Programlama (OOP)** prensiplerini ve **Kalıcı Veri Depolama (Data Persistence)** tekniklerini uygulamalı olarak sergilemek amacıyla tasarlanmıştır.

## 🛠️ Teknik Altyapı ve Özellikler
Bu sistem arka planda belirli bir mimariyi takip eden profesyonel bir yazılımdır:

* **Veri Kalıcılığı (Persistence):** Görevler, çalışma dizinindeki `.dat` uzantılı bir dosyada saklanır. Bu sayede uygulama kapatılsa dahi veriler bir sonraki oturumda otomatik olarak yüklenir.
* **OOP Yaklaşımı:** `IsUnitesi` sınıfı veri modellemesini sağlarken, `SistemKontrol` sınıfı iş mantığını (Business Logic) yönetir.
* **Zaman Damgası (Timestamping):** C++ `<ctime>` kütüphanesi kullanılarak her görev oluşturulduğu anın sistem saatini otomatik olarak alır.
* **Hata Yönetimi:** `try-catch` blokları ve `cin` temizleme mekanizmaları ile kullanıcı hatalarına karşı dayanıklıdır.



## 📋 Kullanım Rehberi
Program etkileşimli bir ana menü üzerinden yönetilir:
1. **Listeyi Görüntüle:** Tüm görevleri şık bir tablo formatında listeler.
2. **Yeni Görev Ekle:** Otomatik ID ataması ile yeni iş kayıtları oluşturur.
3. **Durum Güncelle:** Mevcut görevlerin durumunu (Beklemede, Aktif, Tamamlandı) değiştirir.
4. **Görevi Sil:** ID üzerinden kayıt temizleme işlemi yapar.
5. **Kaydet ve Çık:** Verileri senkronize ederek oturumu kapatır.

## 🚀 Kurulum (Derleme)
Sisteminizde bir C++ derleyicisi olması yeterlidir:

```bash
git clone [https://github.com/Gokhan0/Gokhan_CPP_Project.git](https://github.com/Gokhan0/Gokhan_CPP_Project.git)
cd Gokhan_CPP_Project
g++ gorev_yoneticisi.cpp -o gtask_core
./gtask_core
