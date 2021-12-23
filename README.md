# Procurando a Syscall Table em Linux Kernel 5.x.x

📁 Cabeçalho

  - 📌Criando um software para capturas de sys_call_tables() em kernel 5.x.x
    - 📌Explicação geral sobre todo o corpo do software
    - 📌Conhecendo outros métodos de capturas sem utilizarmos o software
    - 📌Iniciando o módulo e descarregando o buffer do kernel
<br><br>

<h1>🔮 Criando um software para capturas de sys_call_tables() em kernel 5.x.x </h1>
<br>

  - Vamos apresentar então o nosso código aqui:
  
  <img src="https://imgur.com/rtkqHyZ.png">
  
  - Bom, podemos observar que no nosso cabeçalho de includes, temos um novo include chamado <code>kprobe</code>. Temos muito o que falar a respeito dele nesse tópico e por isso separei mais um capítulo para explicar de forma bem explicada como nós conseguimos pegar o endereço do sys_call_table() no kernel 5.x.x. Mas então... o que seria o kprobe?
  <br>
  <code>Kprobe é uma biblioteca muito importante para esse projeto, já que o Kernel sofreu diversas modificações em suas atualizações. Hoje posso dizer que existe uma maior dificuldade em conseguirmos hookar uma syscall para que possamos fazer um Rootkit (já que esse é o seu intuito de está lendo esse git). Bom, vamos deixar de enrolação e vamos falar o que é a library kprobe. O sistema kprobe permite inserir pontos de interrupção dinamicamente em um Kernel em execução. Básicamente iremos utiliza-lo para cumprir a função do kallsyms_lookup_name() para pesquisar a si mesmo.</code>
  <br><br>
  
  - Talvez essa explicação tenha ficado bem rasa, mas caso você queira compreender um pouco mais sobre o kprobe, recomendo você ler <a href="https://www.kernel.org/doc/html/latest/trace/kprobes.html">aqui</a>.
