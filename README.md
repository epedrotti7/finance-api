
# Para startar a API

Certifique-se de ter o compilador do c++ instalado
```
sudo apt install g++
```

É necessário subir a imagem do banco através do docker, certifique-se de ter o Docker instalado
Com o Docker instalado, execute o comando

```
docker-compose up -d
```
Após executar esse comando, teremos nossa imagem do banco MySQL, feito isso, temos que rodar nossas migrations.

# Instalar as seguintes dependencias

# MySQL Connector
https://dev.mysql.com/downloads/connector/cpp/ 
```
sudo apt install libmysqlclient-dev
```

# Asio
https://think-async.com/Asio/ 
```
sudo apt install libasio-dev
```

# Boost
https://www.boost.org/
```
sudo apt install libboost-all-dev 
```

# Clonar o repositorio do Crow C++ na raiz do projeto
https://crowcpp.org/master/getting_started/setup/linux/

# Conceda permissão de execução ao script
chmod +x make.sh

# Execute o script
./make.sh

O servidor irá startar na porta definida e a api estara apta para receber requisicoes.