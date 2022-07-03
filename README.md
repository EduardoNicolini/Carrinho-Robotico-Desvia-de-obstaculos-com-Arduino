# Carrinho Robotico Desvia de obstaculos com Arduino

O objetivo do projeto é fazer o robo desviar de obstáculos tomando decisões para onde deve ir de forma autonoma.

Ao ligar o robo permanece em linha reta até encontrar um obstaculo detectado pelo sensor ultrassônico hc-sr04 instalaco em um micro servo instalado a frente do robo,
A tomada de decisão segue pela leitura da distancia de 20 centimetros ou a desejar escolhida pelo programador.
O servo gira o sensor ultrassônico em um angulo de 90 graus a esquerda para, calcula a distancia e armazena em uma variavel.
Faz o meso processo girando o sensor para a direita e armazena a distancia em outra variavel.
Aciona os 4 motores para traz e vira para o lado e segue em linha reta para o lado em que a distancia calculada foi a maior. 

- Materiais

  Arduino Uno. 
  Sensor ultrassônico hc-sr04.
  Motor Shield L293D - Driver Ponte H para Arduino.
  Micro Servo 9G SG90.
  Motor Dc 3-6v Com Caixa De Redução E Eixo Duplo + Roda 68mm
  2 Bateria Li-ion 18650 6800mah 3.7v - Recarregável.
  
  

