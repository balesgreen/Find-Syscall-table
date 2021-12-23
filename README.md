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
  
  - Talvez essa explicação tenha ficado bem rasa, mas caso você queira compreender um pouco mais sobre o kprobe, recomendo você ler <a href="https://www.kernel.org/doc/html/latest/trace/kprobes.html">aqui</a>. Bom, mas agora é hora de darmos continuidade a nossa explicação.

<img src="https://imgur.com/beA9ozL.png">

  - Temos aqui então a primeira parte da estrutura do nosso software. O que está acontecendo nessa função é o seguinte. Simplesmente nós declaramos uma estrutura kprobe com o campo <code>.symbol_name</code> predefinido como <code>kallsyms_lookup_name()</code>. A primeira vez em que o kprobe é registrado, podemos então desreferenciar o <code>.addr</code> para obtermos o endereço de memória.

<img src="https://imgur.com/E1gH3HN.png">

 - Bom. Partindo agora para a próxima estrutura do nosso código, podemos observar a função de inicialização de carregamento do nosso módulo no Kernel. Primeiramente nós estamos registrando em nosso Kernel o kprobe para que possamos procurar pela função que declaramos no campo <code>.symbol_name</code> na primeira parte da estrutura do nosso software. Logo abaixo contamos com um <code>pr_alert()</code>, função essa que irá exibir um alerta nos logs de registros do kernel junto com a mensagem e logo afrente o endereço de memória que queríamos obter e caso o retorno for igual a 0, o nosso programa funcionará.
 
 <img src="https://imgur.com/vA2im7j.png">
 
 - Possuímos aqui então a nossa última estrutura do nosso código. Essa estrutura é responsável por descarregar o buffer do Kernel e com isso a nossa mensagem que foi exibida após nós termos encontrado o endereço e memória, será apagado.
<br><br>

# Conhecendo outros métodos de captura sem utilizarmos o software

  - Podemos fazer capturas do endereço de memória sem precisarmos utilizar o software que descrevemos acima. Bom, são alguns pequenos comandos que podemos incorporar em nosso terminal para que possamos receber o resultado do que queríamos encontrar. Podemos utilizar o seguinte comando: <code>sudo cat /proc/kallsyms | grep kallsyms_lookup_name > address.txt</code> e após isso, digite <code>cat address.txt</code> e veja o retorno que você recebeu dentro do arquivo de texto. Bom, o retorno será o endereço de memória que você estava procurando. Simples, não? 
<br><br>

# Iniciando o módulo e descarregando o buffer do kernel

  - Para que a gente possa utilizar o nosso software e capturar o nosso endereço de memória, precisamos primeiramente montar o nosso módulo utilizando o comando <code>make</code>. Vá até o caminho onde está este projeto e digite <code>make</code> no terminal e após todo o módulo ter sido montado, é hora de você executa-lo. Digite <code>insmod FindSyscall.ko</code> e confira nos logs de registro do kernel utilizando o comando <code>dmesg</code>.

<img src="https://imgur.com/Vg2R5Bh.png">

<b>Esse foi o endereço retornado em minha máquina e na sua máquina o endereço será diferente do meu. E para descarregarmos o buffer do kernel, apenas digite <code>rmmod FindSyscall.ko</code> e o seu Kernel não terá mais nada se digitar <code>dmesg</code>. </b>

<br><br>

Bom, esse conteúdo aqui foi super necessário para que nós pudessemos dar continuidade aos nosso projeto, então criei esse tópico específico para continuarmos os nossos estudos sobre LKM e RK. Não esquecendo, esse código não foi eu quem criei mas com base no que estudei, me interessei em explica-lo para todos vocês sobre o meu código. O criador do código é o <a href="https://github.com/f0lg0">f0lg0</a>, então todos os créditos do código será para ele.
<br><br>

Esppero que vocês tenham gostado desse tópico e se você estiver interessado em criar seu rootkit, continue lendo meus tópicos, todos os dias estarei trazendo aqui mais tópicos com o mesmo intuito e com isso iremos criar o nosso Rootkit 5.x.x! Espero vocês no próximo Git! Até breve!
<br>

~# Mark Disconnected...
