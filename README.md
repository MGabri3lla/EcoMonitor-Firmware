# EcoMonitor: Monitoramento de Temperatura e Luminosidade

## Sobre o Projeto

O EcoMonitor é um sistema embarcado criado para monitorar o ambiente de home office. O projeto tem como foco acompanhar temperatura, umidade e luminosidade em tempo real, ajudando a manter um espaço mais confortável para estudo ou trabalho.

Os dados são coletados pelos sensores e exibidos diretamente no display, além de utilizar alertas visuais quando o ambiente estiver fora das condições ideais.

---

## Hardware Utilizado

* **Microcontrolador:** ESP32 DevKit V1
  Escolhido por possuir conexão Wi-Fi integrada.

* **Sensores:**

  * DHT22 → temperatura e umidade
  * LDR → luminosidade

* **Interface:**

  * Display LCD 16x2 com módulo I2C
  * LED RGB para alertas visuais

---

## Estrutura do Firmware (C++)

O sistema foi desenvolvido na Arduino IDE utilizando C++.

### Funcionamento do código

* **Controle de tempo:**
  Foi utilizado `millis()` no lugar de `delay()` para evitar travamentos durante a execução. Assim, as leituras acontecem a cada 30 segundos de forma mais estável.

* **Organização do código:**
  As funções foram separadas em partes como conexão Wi-Fi, atualização do display e controle dos alertas, deixando o projeto mais organizado e fácil de manter.

* **Monitoramento contínuo:**
  O sistema verifica constantemente os dados dos sensores e ativa alertas visuais caso algum valor esteja fora do padrão definido.

---

## Objetivo do Projeto

O projeto foi desenvolvido com o objetivo de aplicar conceitos de sistemas embarcados e IoT, utilizando sensores e automação para monitoramento ambiental em tempo real.
