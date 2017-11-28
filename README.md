# Projeto de Redes de Computadores - 2/2017
Este projeto visa o entendimento dos conceitos da disciplina Redes de Computadores se utilizando de ferramentas de simulação e análise de tráfego.
Os integrantes do grupo para o desenvolvimento do projeto são:
  * Eduardo de Azevêdo dos Santos
  * Pedro Eugênio Carvalho
  * Luiz Felipe Carvalho Duarte
  * Yero Távora

### Regras para a manutenção do Repositório

  * Para clonar o repositório, digite `git clone https://github.com/gerudoking/redes2-2017.git`
  * Antes de começar a trabalhar, comece com um `git pull`
  * Ao completar suas mudanças, execute um `git add <arquivo a adicionar>`. Para facilitar, pode usar `*` no lugar de `<arquivo a adicionar>`
  * Logo após, digite `git commit -m "mensagem de commit"`. A mensagem de commit deve estar entre aspas e deve ser relevante, explicando bem as suas mudanças no código.
  * Após commitar, dê um `git push`.
  * Voilà!
  
### Makefile para executar a simulação
Para se executar a simulação, pode se usar o seguinte Makefile:

```
all: run

SCR_DIR = src
NS3_DIR = #caminho para o ns3
PROGRAM_NAME = base

validate_ns3_dir:
ifeq ("$(NS3_DIR)", "")
	$(error Favor prover o diretorio do ns3. Exemplo: NS3_DIR = ~/Desktop/ns3/)
endif
ifeq ($(wildcard $(NS3_DIR)/waf), )
	$(error O diretorio do NS3 provido nao possui o arquivo waf, logo e invalido. Para mudar o diretorio, mude o valor de NS3_DIR)
endif

run: validate_ns3_dir
		rm -rf $(NS3_DIR)/scratch/$(SCR_DIR)
		cp -r src/. $(NS3_DIR)/scratch/
		cd $(NS3_DIR); \
		./waf configure --build-profile=debug --enable-examples --enable-tests; \
		./waf --run $(PROGRAM_NAME)
  ```
