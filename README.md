# 🎮 Jokenpô Bare-Metal para BeagleBone Black

Projeto final da disciplina de **Técnicas de Programação para Sistemas Embarcados I (TPSE I)** da **Universidade Federal do Ceará (UFC) – Campus Quixadá**.

O projeto consiste na implementação do clássico jogo **Pedra, Papel e Tesoura (Jokenpô)** utilizando desenvolvimento **Bare-Metal** na **BeagleBone Black (AM335x)**, explorando diversos periféricos do processador ARM Cortex-A8, como **GPIO, UART, Timers e Interrupções**.

---

## 🎯 Objetivo

Desenvolver um sistema embarcado capaz de executar o jogo Jokenpô sem sistema operacional, utilizando acesso direto aos registradores do processador AM335x.

Durante o desenvolvimento foram aplicados conceitos fundamentais de Sistemas Embarcados, como:

* Programação Bare-Metal
* Manipulação direta de registradores
* Comunicação Serial (UART)
* GPIO
* Timers
* Interrupções
* Modularização de software

---

## 🛠️ Hardware Utilizado

* BeagleBone Black (AM335x)
* LEDs
* Push Buttons
* Computador com terminal serial (Minicom)

---

## 🚀 Funcionalidades

* Inicialização dos periféricos da BeagleBone Black.
* Comunicação serial via UART0.
* Menu interativo no terminal serial.
* Controle dos GPIOs.
* Tratamento de interrupções.
* Utilização de Timers para controle temporal do jogo.
* Implementação da lógica completa do jogo Pedra, Papel e Tesoura.
* Organização modular do software.

---

## 📂 Estrutura do Projeto

```text
Projeto-Jokenpo/
├── bin/
│   └── spl.boot
├── inc/
│   ├── clock_module.h
│   ├── control_module.h
│   ├── game.h
│   ├── gpio.h
│   ├── hw_types.h
│   ├── interruption.h
│   ├── menus.h
│   ├── pad.h
│   ├── soc_AM335x.h
│   ├── timers.h
│   └── uart.h
├── obj/
├── src/
│   ├── clock_module.c
│   ├── control_module.c
│   ├── game.c
│   ├── gpio.c
│   ├── interruption.c
│   ├── main.c
│   ├── memmap.ld
│   ├── menus.c
│   ├── pad.c
│   ├── start.s
│   ├── timers.c
│   └── uart.c
├── makefile
└── README.md
```

---

## 📁 Organização dos Diretórios

| Diretório  | Descrição                                                                            |
| ---------- | ------------------------------------------------------------------------------------ |
| `src/`     | Implementação dos módulos da aplicação.                                              |
| `inc/`     | Arquivos de cabeçalho contendo definições, registradores e interfaces dos módulos.   |
| `obj/`     | Arquivos objeto gerados durante a compilação.                                        |
| `bin/`     | Contém o arquivo `spl.boot` utilizado para carregar a aplicação na BeagleBone Black. |
| `makefile` | Automatiza todo o processo de compilação e geração do executável.                    |

---

## 📚 Principais Módulos

| Módulo             | Responsabilidade                                                      |
| ------------------ | --------------------------------------------------------------------- |
| `main.c`           | Inicializa o sistema e coordena a execução da aplicação.              |
| `game.c`           | Implementa toda a lógica do jogo Pedra, Papel e Tesoura.              |
| `gpio.c`           | Configuração e controle dos GPIOs utilizados pelo projeto.            |
| `uart.c`           | Comunicação serial entre a BeagleBone Black e o computador.           |
| `timers.c`         | Configuração e utilização dos temporizadores de hardware (DMTimers).  |
| `interruption.c`   | Configuração e tratamento das interrupções do sistema.                |
| `menus.c`          | Exibição dos menus e interação com o usuário pelo terminal serial.    |
| `pad.c`            | Configuração do multiplexamento dos pinos (PinMux).                   |
| `clock_module.c`   | Configuração dos módulos de clock necessários para os periféricos.    |
| `control_module.c` | Configuração dos registradores do módulo de controle do AM335x.       |
| `start.s`          | Código de inicialização do ARM Cortex-A8 e vetor de interrupções.     |
| `memmap.ld`        | Script do linker responsável pelo mapeamento de memória da aplicação. |

---

## ⚙️ Como Compilar

Na raiz do projeto, execute:

```bash
make
```

Ao final da compilação será gerado o arquivo:

```text
bin/spl.boot
```

---

## 🚀 Como Executar

1. Compile o projeto utilizando o `make`.
2. Carregue o arquivo `bin/spl.boot` na BeagleBone Black utilizando o U-Boot.
3. Abra um terminal serial (como o Minicom).
4. Execute a aplicação.
5. Interaja com o menu do jogo exibido na UART.

---

## 🎮 Como Jogar

O jogador interage com o sistema através do menu disponibilizado pela UART.

Durante a partida:

* Escolha uma das opções disponíveis (Pedra, Papel ou Tesoura).
* O sistema realiza a jogada do adversário.
* O resultado da rodada é processado pela lógica do jogo.
* O vencedor é informado ao usuário pelo terminal serial.

---

## 🧠 Conceitos Aplicados

* Programação Bare-Metal
* ARM Cortex-A8
* AM335x
* Manipulação de Registradores
* GPIO
* UART
* DMTimer
* Interrupções
* Pin Multiplexing
* Modularização de Software
* Desenvolvimento de Drivers
* Sistemas Embarcados

---

## 📖 Tecnologias Utilizadas

* Linguagem C
* Assembly ARM
* GNU ARM Toolchain
* Make
* U-Boot
* Minicom
* BeagleBone Black

---

## 🎓 Contexto Acadêmico

Este projeto foi desenvolvido como **Projeto Final** da disciplina **Técnicas de Programação para Sistemas Embarcados I (TPSE I)**, ministrada na **Universidade Federal do Ceará (UFC) – Campus Quixadá**.

O objetivo foi integrar, em uma única aplicação, os principais conceitos estudados ao longo da disciplina, incluindo configuração de periféricos, comunicação serial, tratamento de interrupções, temporizadores e programação Bare-Metal.

---

## 👨‍💻 Autor

**Fábio Rodrigues Borges Filho**

Graduando em Engenharia de Computação
Universidade Federal do Ceará (UFC) – Campus Quixadá

GitHub: **https://github.com/F4BINH00**
