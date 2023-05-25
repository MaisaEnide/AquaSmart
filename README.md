# AquaSmart
**Projeto Mackenzie** - Objetos inteligentes conectados

O sistema tem como objetivo repor a água do aquario de modo a ficar sempre em niveis adequados, e tambem, realizar o monitoramento do nivel do reservatório de água tratada.


**Componentes:**
* ESP8266 Node MCU
* Protoboard
* Rele
* 2 Sensores bóia
* Jumpers
* Fonte de 5 volts para alimentação do relé
* Bomba de recalque submersa


**Conexões:**

Uma fonte externa de 5v tambem deverá estar alimentando a protoboard para o correto funcionamento do relé, visto que a placa ESP8266 NodeMCU só possui pino de 3v
<img src="https://github.com/MaisaEnide/AquaSmart/blob/main/Diagrama.jpg" width = "auto"/>


**Instalação:**

Uma bóia-sensor, que neste exemplo está conectada ao pino D1 do nodeMCU, deverá ser instalada no tanque do reservatório de agua, onde também deverá estar a bomba de recalque. Já a bóia sensor do aquario, que está conectada ao pino D2, deverá ser instalada no aquario. 


**Leitura dos sensores:**

A medida que a água do aquario evapora, o sistema irá consultar se o reservatório está em niveis adequados de água, estando em nivel adequado, o sistema ligará a bomba de recalque e fará a reposição de água previamente tratada, porem se o sistema verificar que o reservatório está em nivel critico, ele cortará o acionamento da bomba de recalque. Através da conexão MQTT o usuario poderá companhar via internet o estado do reservatório.


**Upload do programa na IDE Arduino:**

1. Carregar o pacote de placas do modulo ESP8266 na IDE Arduino: Arquivo -> Preferencias e colar a URL: https://arduino.esp8266.com/stable/package_esp8266com_index.json no campo -> URLs Adicionais para Gerenciadores de Placas.
2. Escolher a placa: Tools -> Board -> esp8266 -> NodeMCU 1.0 (ESP-12E Module). 
3. Tools -> Port e selecionar a porta USB correspondente a conexâo da placa. 
4. Adionar as blibliotecas ESP8266WiFi.h  e PubSubClient.h: Sketch -> Include Library -> Manage Libraries. 
5. Abrir o programa: File -> Open. Inserir nome e senha da Rede e grabar o programa na placa clicando em Upload. 

**Conexão MQTT**

Em um Broker MQTT: 
1. Host -> test.mosquitto.org.
2. Porta -> 1883. 
3. Após conectar, fazer a inscrição no tópico -> Monitoramento/reservatorio.



