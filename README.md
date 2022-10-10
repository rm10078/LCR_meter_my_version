
# Digital LCR Meter

The digital LCR Meter project is my 2nd year college project.
Our regular Multimeter is not able to measure the inductance and capacitance. I try to make a LCR Meter at a very low cost. I use atmega328p uc (only microcontroller) .


# Feature
* Resistance (50 to 470k)
* Capacitance (10nF to 2000uF)
* Inductance   (10uH to 4000mH)
* LED forward voltage 
* Internal battery status
* PWM signal output (16 bit)
* Rechargeable battery 
# Device photo
## Prototype
![App Screenshot](https://github.com/rm10078/LCR_meter_my_version/blob/main/image_lcr_meter/prototype.jpeg?raw=true)
## Final 
![App Screenshot](https://github.com/rm10078/LCR_meter_my_version/blob/main/image_lcr_meter/bat_sta.jpg?raw=true)

# Circuit diagram and photo

- [@Diagram](https://github.com/rm10078/LCR_meter_my_version/blob/main/diagram_lcr_meter/LCR_Meter_diagram_w.pdf)

# All code

- [@Code](https://github.com/rm10078/LCR_meter_my_version/tree/main/lcr_meter_v4)

# Working process

I use a resonance circuit for inductance , RC circuit for capacitance and voltage divider circuit for resistance.

# Testing photo

* Resistance 150R
![App Screenshot](https://github.com/rm10078/LCR_meter_my_version/blob/main/image_lcr_meter/150r.jpg?raw=true)
* Resistance 10k
![App Screenshot](https://github.com/rm10078/LCR_meter_my_version/blob/main/image_lcr_meter/10_k.jpg?raw=true)
* Resistance 100k
![App Screenshot](https://github.com/rm10078/LCR_meter_my_version/blob/main/image_lcr_meter/100_k.jpg?raw=true)
* Capacitance 1uF
![App Screenshot](https://github.com/rm10078/LCR_meter_my_version/blob/main/image_lcr_meter/cap_test_1uf.jpg?raw=true)
* capacitance 1.5uF
![App Screenshot](https://github.com/rm10078/LCR_meter_my_version/blob/main/image_lcr_meter/cap_test_1_5uf.jpg?raw=true)
* capacitance 4.7uF
![App Screenshot](https://github.com/rm10078/LCR_meter_my_version/blob/main/image_lcr_meter/cap_test_4_7uf.jpg?raw=true)
* inductance  2.2mH
![App Screenshot](https://github.com/rm10078/LCR_meter_my_version/blob/main/image_lcr_meter/ind_2_2.jpg?raw=true)
* inductance  2.5mH
![App Screenshot](https://github.com/rm10078/LCR_meter_my_version/blob/main/image_lcr_meter/ind_2_5.jpg?raw=true)
* Green LED
![App Screenshot](https://github.com/rm10078/LCR_meter_my_version/blob/main/image_lcr_meter/led_f_voltage.jpg?raw=true)
* Battery status
![App Screenshot](https://github.com/rm10078/LCR_meter_my_version/blob/main/image_lcr_meter/bat_sta.jpg?raw=true)
* PWM signal output
![App Screenshot](https://github.com/rm10078/LCR_meter_my_version/blob/main/image_lcr_meter/pwm_output.jpg?raw=true)


# Current Work

The device result is good but i try to make the result more accurate. Also i try to use stm32 uc because the stm32 has a 12 bit adc and the uc is 32 bit. It's so fast. I use a resonance circuit for inductance measurement and an rc circuit for capacitor. But I want to use the Hartley oscillator and Colpitts oscillator.

# About me

First of all, a big thanks for visiting my profile. My name is Rajib. I am pursuing B.tech in EIE(applied electronics and instrumentation engineering). If you have any questions send me an email.

## 🔗 Links
Gmail-  rm10078@gmail.com
[![linkedin](https://img.shields.io/badge/linkedin-0A66C2?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/rajib-manna-41155a228/)


