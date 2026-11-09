# 🌡️ Estufa Inteligente IoT — Projeto de Circuitos Eletrônicos

Projeto desenvolvido para o **Projeto de Circuitos Eletrônicos** da Formação **IoT Specialist da [DIO](https://www.dio.me/)**, simulando o controle automático de temperatura de uma **estufa de hortaliças** no simulador [TinkerCad](https://www.tinkercad.com/), com programação em linguagem C para Arduino.

## 📋 Funcionalidades (conforme especificação do projeto)

| Requisito | Comportamento |
|---|---|
| (a) | Fazer a leitura da temperatura (sensor TMP36) |
| (b) | Acionar o motor do ventilador quando a temperatura for **igual ou maior a 30 °C** |
| (c) | Acima de **50 °C**, acender o **LED vermelho** e tocar a **buzina** (emergência) |

## 🧰 Componentes do circuito

- 1x Arduino Uno R3
- 1x Sensor de temperatura TMP36
- 1x LED vermelho (emergência)
- 1x Resistor 220 Ω (LED)
- 1x Buzzer / buzina piezoelétrica
- 1x Motor DC (ventilador)
- 1x Transistor NPN 2N2222 (aciona o motor)
- 1x Resistor 1 kΩ (base do transistor)
- 1x Diodo 1N4007 (proteção do motor)
- 1x Bateria 9 V + suporte (alimentação do motor)
- Jumpers e protoboard

## 🔌 Esquema de ligação

### Sensor de temperatura TMP36

| Pino do TMP36 | Ligação |
|---|---|
| VS (perna 1, +) | 5 V do Arduino |
| VOUT (perna 2, saída) | A0 do Arduino |
| GND (perna 3, −) | GND do Arduino |

### LED vermelho (emergência)

| Componente | Ligação |
|---|---|
| Ânodo do LED (perna longa, +) | Pino 12 do Arduino (via resistor de 220 Ω) |
| Cátodo do LED (perna curta, −) | GND do Arduino |

### Buzzer (buzina)

| Componente | Ligação |
|---|---|
| Terminal (+) | Pino 8 do Arduino |
| Terminal (−) | GND do Arduino |

### Motor do ventilador (via transistor)

O Arduino não fornece corrente suficiente para o motor, então o transistor atua como **interruptor eletrônico** entre a bateria 9 V e o motor:

| Componente | Ligação |
|---|---|
| Base do 2N2222 | Pino 9 do Arduino (via resistor de 1 kΩ) |
| Emissor do 2N2222 | GND comum (GND do Arduino + − da bateria) |
| Coletor do 2N2222 | Terminal (−) do motor |
| Terminal (+) do motor | + da bateria 9 V |
| Diodo 1N4007 | Em paralelo com o motor (cátodo para o +), protege o transistor contra picos de tensão |

> ⚠️ **Importante:** o GND da bateria 9 V e o GND do Arduino devem estar **interligados** (GND comum), senão o transistor não é acionado.

## 💻 Código

O código-fonte em linguagem C (Arduino) está em [`codigo/estufa_iot.ino`](codigo/estufa_iot.ino).

Pontos-chave da lógica:

- **Leitura do TMP36:** `analogRead(A0)` retorna 0–1023; converte-se para tensão (`valor × 5 / 1023`) e aplica-se a fórmula do sensor: `temperatura = (tensão − 0,5) × 100`.
- **Ventilador:** `digitalWrite(PINO_MOTOR, HIGH)` quando `temperatura >= 30 °C`.
- **Emergência:** LED + `tone(pino, 1000)` quando `temperatura > 50 °C`.

## ▶️ Como simular no TinkerCad

1. Acesse [tinkercad.com](https://www.tinkercad.com/) e entre na sua conta (ou crie uma gratuita).
2. Clique em **Circuitos → Criar novo circuito**.
3. Arraste os componentes listados acima para a área de trabalho.
4. Faça as ligações conforme o esquema de ligação (dica: use cores diferentes para 5 V, GND e sinais).
5. Clique em **Código**, mude o editor para o modo **Texto** e cole o conteúdo de [`codigo/estufa_iot.ino`](codigo/estufa_iot.ino).
6. Clique em **Iniciar simulação**.
7. **Teste os cenários:**
   - Clique no TMP36 e arraste o controle de temperatura para **abaixo de 30 °C** → ventilador desligado, LED apagado, buzina silenciosa.
   - Ajuste para **entre 30 °C e 50 °C** → ventilador **liga**.
   - Ajuste para **acima de 50 °C** → ventilador ligado + **LED vermelho aceso e buzina tocando** (emergência).
8. Opcional: copie o **link de compartilhamento** do circuito e cole neste README na seção abaixo.

### 🔗 Link do circuito no TinkerCad

> *(cole aqui o link de compartilhamento do seu circuito)*

## 📚 Referências

- Desafio da DIO: [Projeto de Circuitos Eletrônicos](https://web.dio.me/lab/projeto-de-circuitos-eletronicos) (instruções em [`docs/Projetos_Circuito_Eletronico_IoT.pdf`](docs/Projetos_Circuito_Eletronico_IoT.pdf))
- Vídeo do expert com o passo a passo: [Projeto de Circuitos Eletrônicos (YouTube)](https://youtu.be/VM1zXosbdUs)
- Documentação do TMP36: [Analog Devices](https://www.analog.com/en/products/tmp36.html)

## 👨‍💻 Autor

Frederico Silvestre Leoncio — Formação IoT Specialist, DIO.
