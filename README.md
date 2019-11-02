# Trabalho de Informática Industrial II - Rede CAN

Trabalho realizado por Guilherme Piveti Filho e Paulo Masnik para a disciplina de Informática Industrial II sobre a implementação de rede CAN em uma aplicação.

## Contextualização

Este projeto foi desenvolvido para simular um sistema de sensoreamento de área com risco de explosão, em que se deve garantir que não exista chamas, temperatura excessiva e muita incidência solar. Dessa forma foi criada uma rede de módulos, em que cada módulo se instala um sensor ligado à um microcontrolador e um módulo CAN-BUS responsáveis por fazer a leitura do sensor e transmitir os dados à um microncontrolador. Este último controlador fica responsável por analizar os dados e exibir ao usuário final.

Para garantir a segurança do sistema foi definida prioridade para sensores mais críticos através da definição de endereços menores (bits dominantes). A lista de endereçamentos/prioridade ficou definida de acordo com a tabela a seguir:

| Sensor  | Endereço(DEC) | Endereço(BIN) |
| ------------- | ------------- | ------------- |
| Sensor de chamas  | 0  |  000  |
| Sensor de temperatura  | 1  |  001  |
| Sensor de luminosidade  | 2  |  010  |


### Pré-requisitos
Este projeto implementa a biblioteca CAN disponível em https://github.com/sandeepmistry/arduino-CAN

### Procedimentos

Após a gravação do Firmware do arquivo Sender.ino nos Arduinos UNO dos sensores deve-se acoplar a shield desenvolvida. Depois deve-se selecionar com o uso de jumpers o endereçamento do sensor que será utilizado em cada módulo, de acordo com a tabela de prioridades contida neste documento, e selecionar o tipo de leitura a ser feita (Analógia/Digital). Por exemplo, para um módulo com sensor de temperatura ( Endereço 0b001 e saída analógica):

![PCB](https://github.com/guipiveti/RedeCAN/blob/master/Imagens/Placas.png)

Após a gravação do Firmware do arquivo Receiver.ino no Arduino principal deve-se interligar todas as saídas HIGH dos módulos CAN-BUS e todas a saídas LOW.

Agora basta energizar os microntontroladores e acompanhar os dados e alertas dos sensores pelo Serial Monitor do Arduino principal(Receiver).

### Atenção

Em caso de erro na inicialização do módulo CAN-BUS de algum dos equipamentos uma luz LED vermelha se acenderá, indicando que as conexões do módulo devem ser revisadas e o equipamento reiniciado.
