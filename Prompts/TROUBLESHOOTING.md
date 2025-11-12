# Solução de Problemas - Instalação

## Problemas Comuns durante a Configuração

### 1. Erro ao Baixar CEF (Chromium Embedded Framework)

**Mensagem de Erro:**
```
ERROR: Download failed
Failed to download https://cef-builds.spotifycdn.com/cef_binary_...
```

**Causas Possíveis:**
- Conexão de internet instável
- Servidor Spotify CDN temporariamente indisponível
- Firewall/proxy bloqueando o download

**Soluções:**
1. **Retentativas Automáticas**: Execute `retry-downloads.bat` que tentará automaticamente 3 vezes
2. **Aguarde e Tente Novamente**: O servidor pode estar temporariamente fora do ar
3. **Verifique sua Conexão**: Teste sua conexão de internet
4. **Desabilite Firewall/Proxy**: Temporariamente desabilite firewall/antivírus para testar
5. **Compere o arquivo manualmente**: Visite https://cef-builds.spotifycdn.com/

---

### 2. Erro ao Baixar Unifont

**Mensagem de Erro:**
```
ERROR: Download failed
Failed to download https://github.com/multitheftauto/unifont/releases/download/...
```

**Causas Possíveis:**
- GitHub temporariamente indisponível
- Limite de taxa do GitHub excedido
- Problemas de conectividade

**Soluções:**
1. **Aguarde 30-60 minutos** e execute `retry-downloads.bat` novamente
2. **Baixe manualmente** de: https://github.com/multitheftauto/unifont/releases
3. Coloque o arquivo em: `Shared/data/MTA San Andreas/MTA/cgui/unifont.ttf`

---

### 3. Erro ao Baixar Discord-RPC

**Mensagem de Erro:**
```
ERROR: Download failed
Failed to download https://github.com/multitheftauto/discord-rpc/archive/...
```

**Causas Possíveis:**
- Repositório Discord-RPC temporariamente indisponível
- GitHub API rate limiting
- Problemas de conectividade com GitHub

**Soluções:**
1. **Execute `retry-downloads.bat`** para retentativas automáticas
2. **Aguarde 1 hora** antes de tentar novamente (GitHub rate limiting)
3. **Baixe manualmente**:
   - Discord-RPC: https://github.com/multitheftauto/discord-rpc/releases
   - RapidJSON: https://github.com/multitheftauto/rapidjson/releases

---

## Scripts Disponíveis

### `win-create-projects.bat`
- Script principal que executa TODAS as etapas de setup
- Baixa CEF, Unifont, Discord-RPC
- Gera arquivos de projeto VS2022

**Execução:**
```batch
cd Prompts
win-create-projects.bat
```

### `retry-downloads.bat`
- Retenta apenas os downloads que falharam
- Tenta automaticamente 3 vezes com intervalo de 10 segundos
- Muito útil para problemas de conexão intermitente

**Execução:**
```batch
cd Prompts
retry-downloads.bat
```

---

## Pré-requisitos

Certifique-se que tem:
- ✅ Internet ativa
- ✅ Windows 7 ou superior (para win-create-projects.bat)
- ✅ Visual Studio 2022 (para compilação)
- ✅ ~2GB de espaço livre em disco (para downloads)

---

## Próximos Passos

Após completar a configuração com sucesso:

1. Abra `Build/MTASA.sln` no Visual Studio 2022
2. Selecione a configuração (Debug ou Release)
3. Selecione a plataforma (x86 ou x64)
4. Compile

---

## Suporte Adicional

Se os problemas persistirem:

1. Verifique sua conexão de internet
2. Tente em uma rede diferente
3. Aguarde algumas horas (servidores podem estar sobrecarregados)
4. Verifique se firewall/antivírus está bloqueando
5. Considere usar VPN se houver restrições geográficas

Para reportar problemas persistentes, visite: https://github.com/multitheftauto/
