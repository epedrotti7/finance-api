# Passo a passo utilizando o WSL2 do Windows
-> Startar a imagem pelo Docker desktop -> Acessar settings -> resources -> WSL integration

Ativar a distro escolhida e salvar.

# Pre requisitos
sudo apt update
sudo apt install -y apt-transport-https software-properties-common

# repo da microsoft
wget https://packages.microsoft.com/config/ubuntu/20.04/packages-microsoft-prod.deb -O packages-microsoft-prod.deb
sudo dpkg -i packages-microsoft-prod.deb

# instalar o sk do .net
sudo apt update
sudo apt install -y dotnet-sdk-5.0

# instalar o asp.net
sudo apt install -y aspnetcore-runtime-5.0
sudo apt install -y dotnet-runtime-5.0

# clone o repositorio e rode o comando dentro da pasta raiz
dotnet restore

# execute a api
dotnet run
