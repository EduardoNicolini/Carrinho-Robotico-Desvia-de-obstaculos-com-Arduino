// --- Bibliotecas Auxiliares ---
#include <AFMotor.h>         //Inclui biblioteca AF Motor
#include <Servo.h>           //Inclui biblioteca para controle de Servos
 
// --- Seleção dos Motores ---
AF_DCMotor motor1(1); //Seleção do Motor 1
AF_DCMotor motor2(2); //Seleção do Motor 1
AF_DCMotor motor3(3); //Seleção do Motor 1
AF_DCMotor motor4(4); //Seleção do Motor 1

// --- Mapeamento de Hardware ---
#define   serv        10                 //controle do Servo 1
#define   trig        A4                 //Saída para o pino de trigger do sensor
#define   echo        A5                 //Entrada para o pino de echo do sensor

// --- Protótipo das Funções Auxiliares ---
float measureDistance();                //Função para medir, calcular e retornar a distância em cm
void trigPulse();                       //Função que gera o pulso de trigger de 10µs
void decision();                        //Função para tomada de decisão. Qual melhor caminho?
 
void robot_forward(unsigned char v);    //Função para movimentar robô para frente
void robot_backward(unsigned char v);   //Função para movimentar robô para trás
void robot_left(unsigned char v);       //Função para movimentar robô para esquerda
void robot_right(unsigned char v);      //Função para movimentar robô para direita
void robot_stop(unsigned char v);       //Função para parar o robô

// --- Objetos ---
Servo servo1;                           //Cria objeto para o servo motor

// --- Variáveis Globais ---
unsigned char velocidade = 0x00;       //Armazena a velocidade dos motores (8 bits)

float dist_cm;                         //Armazena a distância em centímetros entre o robô e o obstáculo
float dist_right;                      //Armazena a distância em centímetros da direita
float dist_left;                       //Armazena a distância em centímetros da esquerda
         
// --- Configurações Iniciais ---
void setup()
{

    //A biblioteca configura as entradas e saídas pertinentes ao Motor Shield...     
    
   pinMode(trig, OUTPUT);                       //Saída para o pulso de trigger
   pinMode(serv, OUTPUT);                       //Saída para o servo motor
   pinMode(echo, INPUT);                        //Entrada para o pulso de echo
   
   servo1.attach(serv);                         //Objeto servo1 no pino de saída do servo
     
   digitalWrite(trig, LOW);                     //Pino de trigger inicia em low
     
   servo1.write(80);                            //Centraliza servo
    
   delay(500);                                  //Aguarda meio segundo antes de iniciar
    
    velocidade = 0xFF; //Inicia velocidade no valor máximo
  
} //end setup


// --- Loop Infinito ---
void loop()
{
      
     robot_forward(velocidade);
     delay(80);
  
     dist_cm = measureDistance();
  
     if(dist_cm < 20) //distância menor que 20 cm?
     {
         decision();
     }
      
} //end loop

// --- Desenvolvimento das Funções Auxiliares ---

float measureDistance()                       //Função que retorna a distância em centímetros
{
  float pulse;                                //Armazena o valor de tempo em µs que o pino echo fica em nível alto
        
  trigPulse();                                //Envia pulso de 10µs para o pino de trigger do sensor
  
  pulse = pulseIn(echo, HIGH);                //Mede o tempo em que echo fica em nível alto e armazena na variável pulse
    
  return (pulse/58.82);                      //Calcula distância em centímetros e retorna o valor
    
} //end measureDistante

void trigPulse()                             //Função para gerar o pulso de trigger para o sensor HC-SR04
{
   digitalWrite(trig,HIGH);                  //Saída de trigger em nível alto
   delayMicroseconds(10);                    //Por 10µs ...
   digitalWrite(trig,LOW);                   //Saída de trigger volta a nível baixo

} //end trigPulse

void decision()                              //Compara as distâncias e decide qual melhor caminho a seguir
{
   robot_stop(velocidade);                   //Para o robô
   delay(500);                               //Aguarda 500ms
   servo1.write(10);                          //Move sensor para direita através do servo
   delay(500);                               //Aguarda 500ms
   dist_right = measureDistance();           //Mede distância e armazena em dist_right
   delay(2000);                              //Aguarda 2000ms
   servo1.write(125);                        //Move sensor para esquerda através do servo
   delay(500);                               //Aguarda 500ms
   dist_left = measureDistance();            //Mede distância e armazena em dis_left
   delay(2000);                               //Aguarda 2000ms
   servo1.write(90);                         //Centraliza servo
   delay(500);
   
   if(dist_right > dist_left)                //Distância da direita maior que da esquerda?
   {                                         //Sim...
   
      robot_backward(velocidade);            //Move o robô para trás
      delay(600);                            //Por 600ms
      robot_right(velocidade);               //Move o robô para direita
      delay(2000);                           //Por 2000ms
      robot_forward(velocidade);             //Move o robô para frente
   
   } //end if
   
   else                                      //Não...
   {
   
      robot_backward(velocidade);            //Move o robô para trás
      delay(600);                            //Por 600ms
      robot_left(velocidade);                //Move o robô para esquerda
      delay(2000);                            //Por 2000ms
      robot_forward(velocidade);              //Move o robô para frente
   
   } //end else
  
} //end decision

 
void robot_forward(unsigned char v)
{
     motor1.setSpeed(v);
     motor1.run(FORWARD);
     motor2.setSpeed(v);
     motor2.run(FORWARD);
     motor3.setSpeed(v);
     motor3.run(FORWARD);
     motor4.setSpeed(v);
     motor4.run(FORWARD);

} //end robot forward

void robot_backward(unsigned char v)
{
     motor1.setSpeed(v);
     motor1.run(BACKWARD);
     motor2.setSpeed(v);
     motor2.run(BACKWARD);
     motor3.setSpeed(v);
     motor3.run(BACKWARD);
     motor4.setSpeed(v);
     motor4.run(BACKWARD);

} //end robot backward

void robot_left(unsigned char v)
{
     motor1.setSpeed(v);
     motor1.run(FORWARD);
     motor2.setSpeed(v);
     motor2.run(FORWARD);
     motor3.setSpeed(v);
     motor3.run(BACKWARD);
     motor4.setSpeed(v);
     motor4.run(BACKWARD);

} //end robot left

void robot_right(unsigned char v)
{
     motor1.setSpeed(v);
     motor1.run(BACKWARD);
     motor2.setSpeed(v);
     motor2.run(BACKWARD);
     motor3.setSpeed(v);
     motor3.run(FORWARD);
     motor4.setSpeed(v);
     motor4.run(FORWARD);

} //end robot right

void robot_stop(unsigned char v)
{
     motor1.setSpeed(v);
     motor1.run(RELEASE);
     motor2.setSpeed(v);
     motor2.run(RELEASE);
     motor3.setSpeed(v);
     motor3.run(RELEASE);
     motor4.setSpeed(v);
     motor4.run(RELEASE);

} //end robot stop
