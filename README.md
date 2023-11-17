   # Yemek-Kart-Projesi
Yemek kartı projesinde kişilerin yemek yeme hakları boyunca yemek almaları sağlanmaktadır. Proje  ilk okul için tasarlanmıştır.
![devre](https://github.com/YunusEmreTom/Yemek-Kart-Projesi/assets/78315933/a9450d17-234f-473b-a7dc-35d7af9b144d)

Yemek kartı projesinde kullanılan malzemeler:
1. Arduino 
2. RFID Modülü 
3. Saat Modülü
4. SD Kart Modülü
5. Buzzer
6. Led (x2)
7. Drenç (x3)
   
Bu proje okul için yapıldığından yemek hakkı 1 ay sonunda sıfırlanmaktadır. Ayrıca aynı kişinin o gün içerisinde en fazla 1 kez yemek yeme hakkı olduğundan bir daha yemek yiyememektedir. Bunlardan dolayı saat modülü kullanılmıştır. 

RFID ile ilk başta öğrenci kart yükleme sorumlusuna giderek kartına o ayın yemek yeme hakkını karta yazdırmaktadıe. Kartlarda ilk olarak kartların okul tarafından belirlenen şifrsi ondan sonra öğrenci numarası ve o ayın ay numarası girilir. (ör. 12340211; 1234 okulun şifresi, 01 öğrencinin okul numarası, 11 şimdiki  ay) Sorumlu sadece ayı değiştirerek kartları yenilemektedir. Ayı geçmiş yada yanlış olan öğrenciler yemek yiyememektedirler. 

Ledlerin amacı kişiyi bilgilendirme amaçlıdır. Kırmızı led yanarsa eğer kişi yemek yiyememekte, Yeşil led yanarsa kişi yemek yiyebilmektedir. 

Buzzerın amacı kişiyi sesli olarakta bilgilendirmektir. Bu sadece kişi değil ayrıca yemek sorumlularını da bilgilendirmek içindir. 

SD kart modülünün amacı kişinin o günkü yemek yediği yada yemediğini tutmak içindir. Yani bir nebze log deftedir. Kişi eğer o gün içerisinde bir daha yemek yemeye gelirse bu defter sayesinde yemek sorumluları bilgilendirilir ve kişiye yemek yiyemez. 

NOT:
Bu projeyi yaparken SPI bağlantı kullanılıyor. SPI da ortak olarak kullanılan pinlerde vardır. Bu yüzden bazen hatalar çıkmakta ve arduino RFID modülünden veri çağıramamaktdadır. Bu sorunu drenç ile sorun çıkaran cihazın MISO pinine seri bağlayınca sorun çözülmektedir. 



