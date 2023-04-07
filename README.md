
# Para startar a API

É necessário subir a imagem do banco através do docker, certifique-se de ter o Docker instalado
Com o Docker instalado, execute o comando

```
docker-compose up -d
```
Após executar esse comando, teremos nossa imagem do banco MariaDB, feito isso, temos que rodar nossas migrations.

# Conceda permissão de execução ao script
chmod +x make.sh

# Execute o script
./make.sh

O servidor irá startar na porta definida e a api estara apta para receber requisicoes.

```
https://crowcpp.org/master/getting_started/setup/linux/
```

Connector C++
https://mariadb.com/docs/skysql/connect/programming-languages/cpp/
