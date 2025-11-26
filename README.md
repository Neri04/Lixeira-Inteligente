# Lixeira Inteligente: Otimização da Coleta de Resíduos com Medição de Volume via IoT

Este repositório contém os arquivos e a documentação do projeto desenvolvido pelos alunos da Faculdade de Computação e Informática da Universidade Presbiteriana Mackenzie.

## 📋 Sobre o Projeto
O projeto consiste no desenvolvimento de um protótipo de lixeira inteligente baseada em IoT, projetada para otimizar o processo de coleta de resíduos sólidos urbanos. O sistema monitora o nível de preenchimento da lixeira em tempo real e envia alertas quando a coleta é necessária.

O objetivo é demonstrar a viabilidade de uma solução de baixo custo capaz de reduzir deslocamentos desnecessários e otimizar rotas de coleta, alinhando-se às metas do ODS 11 da Agenda 2030 da ONU.

## 👥 Integrantes
* **Lucas Giovannetti Motta Horn**
* **Thiago de Oliveira Silva**
* **Aaron Nur de Paula Magalhães**
* **Gabriel Nobrega Neri**
* **Orientador:** Prof. Wallace Santana

## 🚀 Arquitetura e Tecnologias

O sistema opera através da seguinte arquitetura integrada:

1.  **Hardware/Simulação (Wokwi):**
    * **ESP32 (Sensor):** Conectado a um sensor ultrassônico **HC-SR04**. Mede a distância livre na lixeira, calcula o volume ocupado e publica via MQTT.
    * **ESP32 (Atuador):** Conectado a um LED. Assina o tópico MQTT e acende o LED caso a lixeira esteja cheia (< 15cm livres).
2.  **Comunicação:** Protocolo **MQTT** para troca de mensagens entre dispositivos e servidor.
3.  **Backend (AWS):**
    * **Node-RED:** Hospedado em uma instância EC2 Linux na AWS. Recebe os dados MQTT, processa a lógica de "Lixeira Cheia" e envia notificações via WhatsApp API.
4.  **Banco de Dados:**
    * **InfluxDB:** Banco de dados de séries temporais (TSDB) hospedado na nuvem, armazenando histórico de volume e timestamps.
5.  **Visualização:**
    * **Grafana:** Dashboards conectados ao InfluxDB para monitoramento em tempo real (Gauge de volume atual e Gráfico de histórico por hora).

## 🛠️ Estrutura do Repositório

* `/firmware`: Códigos C++ utilizados nos ESP32 (Sensor e Atuador).
* `/backend`: Arquivo JSON com o fluxo de nós (nodes) do Node-RED.
* `/database`: Detalhes da estrutura (Bucket e Measurements) do InfluxDB.
* `/dashboards`: Arquivo JSON para importação dos painéis no Grafana.
* `/simulacao`: Link e arquivos da simulação no Wokwi.

## 📊 Resultados e Dashboards

O sistema permite a visualização de dois painéis principais:
1.  **Status Atual:** Medidor (Gauge) indicando o volume preenchido em tempo real.
2.  **Histórico:** Gráfico temporal mostrando a evolução do lixo durante o dia, permitindo identificar horários de pico.

## 🔗 Links Úteis
* [Link para Simulação Wokwi](INSERIR_LINK_AQUI)
* [Artigo Completo (PDF)](docs/artigo_final.pdf)

---
*Projeto desenvolvido para a disciplina de Projetos de Objetos Inteligentes Conectados - 2025.*
