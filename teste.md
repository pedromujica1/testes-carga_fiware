Com base no segundo PDF ("ESM - Cap. 5 - Princípios de Projeto.pdf"), seguem as resoluções dos exercícios de fixação.

---

### 1. Descreva três benefícios da propriedade de projeto chamada ocultamento de informação (information hiding)?

Três benefícios do ocultamento de informação são:
1.  **Redução do impacto de mudanças:** Ao isolar detalhes internos que podem mudar (como a estrutura de dados usada), alterações nesses detalhes não afetam outros módulos que dependem apenas da interface pública.
2.  **Maior compreensão do código:** Cada módulo pode ser estudado e entendido de forma independente, pois sua complexidade interna fica oculta.
3.  **Aumento do reúso:** Módulos bem encapsulados podem ser reutilizados em contextos diferentes, pois suas dependências externas são apenas suas interfaces públicas e bem definidas.

---

### 2. Suponha que um programador adote a seguinte estratégia... ele conclui a tarefa movendo as classes para o mesmo arquivo.

- **Qual propriedade de projeto ele estará melhorando?**  
  Ele estará melhorando o **acoplamento estrutural** entre diretórios (ou pacotes), pois ao colocar duas classes que frequentemente mudam juntas no mesmo arquivo, ele reduz as dependências cruzadas entre diferentes partes do sistema.

- **Qual propriedade de projeto estará sendo afetada de modo negativo?**  
  Ele estará prejudicando a **coesão** do arquivo/pacote, pois o arquivo passará a conter classes que originalmente tinham responsabilidades diferentes (coesão baixa), e também poderá prejudicar o **ocultamento de informação**, pois detalhes de implementação de uma classe ficam mais expostos à outra.

---

### 3. Classitis... Usando os conceitos de acoplamento e coesão, como podemos explicar o problema causado por essa “doença”?

A *classitis* (proliferação de classes pequenas) pode levar a:
- **Baixa coesão indireta:** cada classe individualmente pode ser coesa, mas a responsabilidade de uma funcionalidade maior fica espalhada por várias classes.
- **Alto acoplamento entre classes:** para realizar uma tarefa simples, muitas classes precisam interagir, criando uma rede densa de dependências. Isso aumenta a complexidade do sistema e torna a manutenção mais difícil.

---

### 4. Defina:
(a) **Acoplamento aceitável:** Classe A usa classe B, B oferece um serviço útil para A, B possui uma interface estável e A chama apenas métodos públicos da interface de B.

(b) **Acoplamento ruim:** Classe A não referencia diretamente B, mas mudanças em B podem impactar A (acoplamento evolutivo). Ou A depende de detalhes internos de B.

(c) **Acoplamento estrutural:** A dependência que existe quando A possui uma referência direta no código para B (ex: chamada de método, herança, acesso a atributo público).

(d) **Acoplamento evolutivo (ou lógico):** Ocorre quando duas classes ou módulos tendem a mudar juntos por razões conceituais, mesmo sem dependência estrutural direta. Exemplo: alterar um protocolo ou formato de dados que várias classes interpretam.

---

### 5. Dê um exemplo de:
(1) **Acoplamento estrutural e aceitável:**  
A classe `ControleRemoto` chama o método `aumentarVolume()` da classe `TV`. A interface de `TV` é estável e serve bem ao controle.

(2) **Acoplamento estrutural e ruim:**  
A classe `ControleRemoto` acessa diretamente o atributo público `volume` da classe `TV`, ou chama `tv.getCircuito().getAmplificador().setGanho(10)` (quebra de encapsulamento e cadeia longa).

---

### 6. É possível que uma classe A esteja acoplada a uma classe B sem ter uma referência para B em seu código? Se sim, esse acoplamento será aceitável ou será um acoplamento ruim?

Sim, é possível. Esse é o **acoplamento evolutivo** (ou lógico).  
Geralmente é considerado **ruim**, pois mudanças em B podem quebrar A mesmo sem dependência estrutural explícita. Exemplo: ambas dependem de um mesmo formato de arquivo ou convenção global.

---

### 7. Suponha um programa em que todo o código está implementado no método main. Ele tem um problema de coesão ou acoplamento? Justifique.

Tem problema de **coesão** (baixa coesão), pois o método `main` acumula múltiplas responsabilidades (entrada, processamento, saída, lógica de negócio).  
O **acoplamento** não é o foco principal, pois não há vários módulos para se acoplarem. Mas há forte acoplamento implícito entre todas as partes da lógica.

---

### 8. Qual princípio de projeto é violado pelo seguinte código?

```java
void onclick() {
    num1 = textfield1.value();
    c1 = BD.getConta(num1)
    num2 = textfield2.value();
    c2 = BD.getConta(num2)
    valor = textfield3.value();
    beginTransaction();
    try {
        c1.retira(valor);
        c2.deposita(valor);
        commit();
    } catch() { rollback(); }
}
```

Princípio violado: **Princípio da Responsabilidade Única (SRP)** – o método `onclick` faz muitas coisas: obter dados da UI, acessar banco de dados, lógica de negócio (transferência), controle de transação. Também viola **Ocultamento de Informação**, pois mistura camadas.

---

### 9. ...Suponha que você poderá escolher apenas dois dos três conceitos... Qual eliminaria? Justifique.

Eliminaria a **herança**.  
Motivo: herança pode ser substituída por composição + interfaces na maioria dos casos, enquanto encapsulamento (information hiding) e polimorfismo são fundamentais para modularidade, extensibilidade e baixo acoplamento.

---

### 10. Qual princípio de projeto é violado pelo seguinte código?

```java
void sendMail(ContaBancaria conta, String msg) {
    Cliente cliente = conta.getCliente();
    String endereco = cliente.getMailAddress();
    // Envia mail
}
```

Violação do **Princípio de Demeter** (Lei de Demeter): o método navega por uma cadeia `conta.getCliente().getMailAddress()`.  
**Alteração sugerida:** adicionar um método `conta.getMailAddressDoCliente()` que encapsula o acesso.

---

### 11. Qual princípio de projeto é violado pelo seguinte código?

```java
void imprimeDataContratacao(Funcionario func) {
    Date data = func.getDataContratacao();
    String msg = data.format();
    System.out.println(msg);
}
```

Violação do **Princípio da Responsabilidade Única** (SRP): o método `imprimeDataContratacao` formata a data **e** imprime.  
**Alteração sugerida:** separar em dois métodos: um que formata (`formatarDataContratacao`) e outro que imprime.

---

### 12. Considerando pré e pós-condições, qual princípio é violado pelo código?

Código:
```java
class A { int f(int x) { // pre: x > 0 ... return exp; } // pos: exp > 0 }
class B extends A { int f(int x) { // pre: x > 10 ... return exp; } // pos: exp > -50 }
```

Violação do **Princípio de Substituição de Liskov (LSP)**. A subclasse `B` enfraquece a pré-condição (mais restritiva: `x > 10` ao invés de `x > 0`) e enfraquece a pós-condição (`exp > -50` ao invés de `exp > 0`). Objetos de `B` não podem substituir objetos de `A` em todos os contextos.

---

### 13. Calcule o CBO e LCOM da seguinte classe:

```java
class A extends B {
    C f1, f2, f3;
}
```

- **CBO (Coupling Between Objects):**  
  Herda de `B` → 1. Usa `C` como tipo de três atributos → 1 (não conta múltiplas vezes a mesma classe). Total **CBO = 2**.

- **LCOM (Lack of Cohesion of Methods):**  
  Não há métodos declarados em `A`. Se não há métodos, considera-se **LCOM = 0** (coesão máxima por vacuidade).

---

### 14. Qual das seguintes classes é mais coesa? Justifique computando LCOM.

**Classe A:**
```java
class A {
    X x = new X();
    void f() { x.m1(); }
    void g() { x.m2(); }
    void h() { x.m3(); }
}
```
- Métodos: f, g, h. Todos usam o atributo `x`.  
- Pares de métodos que compartilham atributos: (f,g), (f,h), (g,h) → 3 pares.  
- LCOM = 0 (coesão máxima).

**Classe B:**
```java
class B {
    X x = new X();
    Y y = new Y();
    Z z = new Z();
    void f() { x.m(); }
    void g() { y.m(); }
}
```
- f usa `x`, g usa `y`. Nenhum atributo compartilhado.  
- Pares de métodos que compartilham atributos: nenhum.  
- LCOM = número de pares que não compartilham = 1 par (f,g) → **LCOM = 1**.

**Conclusão:** Classe A é mais coesa (LCOM 0) do que B (LCOM 1).

---

### 15. Por que a métrica LCOM mede a ausência e não a presença de coesão?

Porque LCOM conta **pares de métodos que não compartilham atributos**. Quanto maior o valor, menor a coesão. O nome "Lack of Cohesion" (falta de coesão) indica exatamente isso: mede a **ausência** de coesão.

---

### 16. Todos os métodos de uma classe devem ser considerados no cálculo de LCOM? Sim ou não? Justifique.

Sim, todos os métodos da classe devem ser considerados, inclusive construtores e getters/setters, pois eles também participam do uso dos atributos. Excluir métodos poderia mascarar falta de coesão.

---

### 17. A definição de complexidade ciclomática é independente de linguagem de programação. Sim ou não? Justifique.

Sim, a definição é independente. A complexidade ciclomática baseia-se no grafo de fluxo de controle (nós = comandos/blocos, arestas = fluxo entre eles), que pode ser extraído de qualquer linguagem de programação estruturada.

---

### 18. Dê um exemplo de código com complexidade ciclomática mínima. Qual é essa complexidade?

Exemplo:
```java
void exemplo() {
    int a = 1;
    int b = 2;
    int c = a + b;
}
```
Complexidade ciclomática mínima para um único caminho linear é **1**.

---

### 19. Análise das versões monolítica e OO (frequência de termos):

- **Vantagens da solução OO sobre a monolítica, extrapolando para sistema maior:**
  - **Separação de responsabilidades:** cada classe (ex: `WordFrequencyCounter`, `StopWordFilter`, `TermFrequencyPrinter`) tem uma única função.
  - **Baixo acoplamento:** classes interagem por interfaces bem definidas; mudar uma classe não exige mudanças nas outras.
  - **Facilidade de manutenção e evolução:** novos formatos de saída, novos filtros de stop words ou novas fontes de texto podem ser adicionados sem modificar o código existente.
  - **Testabilidade:** cada classe pode ser testada isoladamente.
  - **Paralelização do desenvolvimento:** diferentes desenvolvedores podem trabalhar em diferentes classes simultaneamente, enquanto no monolítico todos mexem no mesmo arquivo/função.
