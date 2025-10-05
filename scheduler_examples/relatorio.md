# Sistemas Operativos 2025/26
## Trabalho Prático 1 — Simulador de Escalonamento

---

### 1. Autores
- Daniil Kachkovskyy, a22405296

### 2. Repositório GitHub
- URL: <link para o repositório>

### 3. Resultados

Cada algoritmo foi executado pelo menos **3 vezes** em cada cenário.  
Os valores apresentados são **médias** dos resultados obtidos.

---

## Cenário 1 (run_apps.sh)

| Aplicação | Métrica (segs) | FIFO   | SJF    | RR     | MLFQ  |
|-----------|----------------|--------|--------|--------|-------|
| A         | Tempo Execução | 10     | 10     | 10     | 10    |
| A         | Tempo Resposta | 23.333 | 16.663 | 29.49  | 29.49 |
| B         | Tempo Execução | 15     | 15     | 15     | 15    |
| B         | Tempo Resposta | 45     | 31.657 | 39.987 | 39.49 |
| C         | Tempo Execução | 20     | 20     | 20     | 20    |
| C         | Tempo Resposta | 23.333 | 36.660 | 44.99  | 44.99 |

---

## Cenário 2 (run_apps2.sh)

| Aplicação | Métrica (segs) | FIFO   | SJF    | RR     | MLFQ   |
|-----------|----------------|--------|--------|--------|--------|
| A         | Tempo Execução | 5      | 5      | 5      | 5      |
| A         | Tempo Resposta | 10.663 | 14     | 23.32  | 22.99  |
| B         | Tempo Execução | 10     | 10     | 10     | 10     |
| B         | Tempo Resposta | 17.333 | 23.993 | 33.65  | 33.487 |
| C         | Tempo Execução | 4      | 4      | 4      | 4      |
| C         | Tempo Resposta | 7.333  | 8.997  | 19.653 | 18.987 |
| D         | Tempo Execução | 2      | 2      | 2      | 2      |
| D         | Tempo Resposta | 32.997 | 2      | 11.98  | 11.15  |
| E         | Tempo Execução | 3      | 3      | 3      | 3      |
| E         | Tempo Resposta | 15.997 | 4.997  | 16.483 | 16.647 |
| F         | Tempo Execução | 15     | 15     | 15     | 15     |
| F         | Tempo Resposta | 36.663 | 38.993 | 38.98  | 38.98  |

---

## Cenário 3 (run_appsio.sh)

> ⚠️ Apenas aplicável a **MLFQ**.

| Aplicação | Métrica (segs) | FIFO | SJF  | RR   | MLFQ   |
|-----------|----------------|------|------|------|--------|
| A         | Tempo Execução | n.d. | n.d. | n.d. | 2      |
| A         | Tempo Resposta | n.d. | n.d. | n.d. | 23.913 |
| B         | Tempo Execução | n.d. | n.d. | n.d. | 2      |
| B         | Tempo Resposta | n.d. | n.d. | n.d. | 24.28  |
| C         | Tempo Execução | n.d. | n.d. | n.d. | 30     |
| C         | Tempo Resposta | n.d. | n.d. | n.d. | 35.27  |

---

## Cenário 4 (run_appsio2.sh)

> ⚠️ Apenas aplicável a **MLFQ**.

| Aplicação | Métrica (segs) | FIFO | SJF  | RR   | MLFQ    |
|-----------|----------------|------|------|------|---------|
| A         | Tempo Execução | n.d. | n.d. | n.d. | 34      |
| A         | Tempo Resposta | n.d. | n.d. | n.d. | 136.463 |
| B         | Tempo Execução | n.d. | n.d. | n.d. | 34      |
| B         | Tempo Resposta | n.d. | n.d. | n.d. | 136.927 |
| C         | Tempo Execução | n.d. | n.d. | n.d. | 60      |
| C         | Tempo Resposta | n.d. | n.d. | n.d. | 127.403 |

---

## 4. Tabela Resumo

| Cenário | Métrica (segs)       | FIFO   | SJF    | RR     | MLFQ    |
|---------|----------------------|--------|--------|--------|---------|
| 1       | Tempo Médio Execução | 15     | 15     | 15     | 15      |
| 1       | Tempo Médio Resposta | 30.555 | 28.327 | 38.156 | 37.99   |
| 2       | Tempo Médio Execução | 6.5    | 6.5    | 6.5    | 6.5     |
| 2       | Tempo Médio Resposta | 20.164 | 15.497 | 24.011 | 47.414  |
| 3       | Tempo Médio Execução | n.d.   | n.d.   | n.d.   | 11.333  |
| 3       | Tempo Médio Resposta | n.d.   | n.d.   | n.d.   | 27.821  |
| 4       | Tempo Médio Execução | n.d.   | n.d.   | n.d.   | 42.667  |
| 4       | Tempo Médio Resposta | n.d.   | n.d.   | n.d.   | 133.598 |
