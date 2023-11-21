   # Yemek-Kart-Projesi
Yemek kartı projesinde kişilerin yemek yeme hakları boyunca yemek almaları sağlanmaktadır. Proje  ilk okul için tasarlanmıştır.
![yemekkarti2_bb](https://github.com/YunusEmreTom/Yemek-Kart-Projesi/assets/78315933/61cf2e64-8009-4de1-baf1-c5d948f5c893)


Yemek kartı projesinde kullanılan malzemeler:
1. Arduino 
2. RFID Modülü
3. Buzzer
4. Led (x2)
5. Drenç (x3)
   
Bu proje okul için yapıldığından yemek hakkı 1 ay sonunda sıfırlanmaktadır. Ayrıca aynı kişinin o gün içerisinde en fazla 1 kez yemek yeme hakkı olduğundan bir daha yemek yiyememektedir.

RFID ile ilk başta öğrenci kart yükleme sorumlusuna giderek kartına o ayın yemek yeme hakkını karta yazdırmaktadıe. Kartlarda ilk olarak kartların okul tarafından belirlenen şifrsi ondan sonra öğrenci numarası ve o ayın içersinde yemek yeme hakkı girilir. (ör. 12340211; 1234 okulun şifresi, 01 öğrencinin okul numarası, 11 yemek yeme hakkı) Sorumlu yemek yeme hakları sayısını değiştirerek kartları yenilemektedir. Yemek yeme hakkı olmayan yada kartı yanlış olan öğrenciler yemek yiyememektedirler. 

Ledlerin amacı kişiyi bilgilendirme amaçlıdır. Kırmızı led yanarsa eğer kişi yemek yiyememekte, Yeşil led yanarsa kişi yemek yiyebilmektedir. 

Buzzerın amacı kişiyi sesli olarakta bilgilendirmektir. Bu sadece kişi değil ayrıca yemek sorumlularını da bilgilendirmek içindir. 
