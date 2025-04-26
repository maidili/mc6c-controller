# mc6c-controller

Deskripsi
Project ini adalah sistem kontrol motor untuk mobil RC berbasis ESP32.
Menggunakan sinyal PWM dari receiver RC untuk mengendalikan kecepatan dan arah belok motor DC melalui driver motor.

Fitur utama:
Throttle dikonversi dari range sinyal input (-225 sampai 283) menjadi 0%–100% kecepatan maju.
Steering dikontrol secara proporsional untuk membedakan kecepatan motor kanan dan kiri.
Failsafe otomatis menghentikan motor saat tidak ada sinyal dari receiver.

Spesifikasi Teknis
Board: ESP32 (ESP32-D0WD-V3 tested)
Motor Driver: L298N

Receiver Input:
Channel 3 (Throttle)
Channel 4 (Steering)
Output PWM: 0–255 duty cycle
Baudrate Serial: 115200 (untuk debugging)

Wiring Diagram
Pin ESP32	Fungsi	Keterangan
14	Motor A IN1	Arah motor A
27	Motor A IN2	Arah motor A
12	Motor A PWM (ENA)	Kecepatan motor A
26	Motor B IN1	Arah motor B
25	Motor B IN2	Arah motor B
33	Motor B PWM (ENB)	Kecepatan motor B
36 (VP)	RC Channel 3 input	Throttle signal
39 (VN)	RC Channel 4 input	Steering signal

Cara Kerja
ESP32 membaca sinyal PWM dari receiver (pulseIn).
Throttle dikonversi dari -225 sampai 283 ke skala PWM 0 sampai 255.
Steering mempengaruhi distribusi kecepatan motor kanan dan kiri.
Motor dikendalikan maju berdasarkan nilai PWM.
Jika sinyal hilang, motor akan otomatis berhenti (failsafe).

Instalasi
Pastikan Arduino IDE sudah terinstal dan board ESP32 sudah ditambahkan.
Pilih board: ESP32 Dev Module.
Upload sketch ke ESP32 dengan kabel USB.
Pastikan semua wiring aman saat upload (cabut kabel dari motor driver jika perlu).
saat ingin mengupload pastikan catu daya dari baterai terlepas dengan sempurna!!!!

License
Proyek ini bebas digunakan untuk keperluan edukasi dan non-komersial.
Feel free to fork and improve! 🚀
