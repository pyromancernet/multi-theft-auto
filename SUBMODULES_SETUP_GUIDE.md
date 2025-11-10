# Guia de Configuração dos Submodules

## Status Atual

✅ **Completo:**
- SDK e Vendor movidos para projetos separados
- Todos os arquivos premake5.lua atualizados
- Buildactions corrigidos
- Arquivo .gitmodules criado
- Documentação criada

⏳ **Pendente (Próximos Passos):**

### 1. Criar Repositórios no GitHub

Crie dois novos repositórios no GitHub:

1. **mtasa-sdk** - Para os headers do SDK
   - URL sugerida: `https://github.com/multitheftauto-modern/mtasa-sdk.git`
   
2. **mtasa-vendors** - Para as bibliotecas vendor
   - URL sugerida: `https://github.com/multitheftauto-modern/mtasa-vendors.git`

### 2. Fazer Push dos Repositórios Externos

Assumindo que os diretórios `mtasa-sdk` e `mtasa-vendors` estão em `d:\Documents\Nova Community\`:

```powershell
# Para mtasa-sdk
cd "d:\Documents\Nova Community\mtasa-sdk"
git remote add origin https://github.com/multitheftauto-modern/mtasa-sdk.git
git branch -M main
git push -u origin main

# Para mtasa-vendors  
cd "d:\Documents\Nova Community\mtasa-vendors"
git remote add origin https://github.com/multitheftauto-modern/mtasa-vendors.git
git branch -M main
git push -u origin main
```

### 3. Adicionar os Submodules ao Repositório Principal

Depois que os repositórios estiverem no GitHub:

```powershell
cd "d:\Documents\Nova Community\multi-theft-auto"

# Adicionar submodules
git submodule add https://github.com/multitheftauto-modern/mtasa-sdk.git sdk
git submodule add https://github.com/multitheftauto-modern/mtasa-vendors.git vendor

# Commit
git add .gitmodules sdk vendor
git commit -m "Add SDK and Vendor submodules"
git push
```

### 4. Atualizar .gitmodules (se necessário)

Se você já tiver o arquivo `.gitmodules` criado, atualize as URLs:

```ini
[submodule "sdk"]
	path = sdk
	url = https://github.com/multitheftauto-modern/mtasa-sdk.git
[submodule "vendor"]
	path = vendor
	url = https://github.com/multitheftauto-modern/mtasa-vendors.git
```

### 5. Verificar a Configuração

```powershell
# Ver status dos submodules
git submodule status

# Testar o premake
premake5 vs2022
```

## Estrutura Final Esperada

```
multi-theft-auto/
├── .git/
├── .gitmodules
├── sdk/                    (submodule → mtasa-sdk)
│   ├── .git
│   ├── CLIENT/
│   ├── SERVER/
│   └── SHARED/
├── vendor/                 (submodule → mtasa-vendors)
│   ├── .git
│   ├── bass/
│   ├── cef3/
│   ├── discord-rpc/
│   └── ... (35 libraries)
├── Client/
├── Server/
├── Shared/
└── premake5.lua
```

## Notas Importantes

- Os submodules devem estar **dentro** do repositório `multi-theft-auto`
- Cada submodule é um repositório git independente
- URLs relativas (`../mtasa-sdk`) funcionam se todos os repos estiverem na mesma organização
- URLs absolutas são mais confiáveis para CI/CD

## Solução de Problemas

### Se os repositórios ainda não existem no GitHub:

Trabalhe com submodules locais temporariamente:

```powershell
# Use URLs relativas na mesma pasta
cd "d:\Documents\Nova Community\multi-theft-auto"
git submodule add ../mtasa-sdk sdk
git submodule add ../mtasa-vendors vendor
```

Depois atualize as URLs quando criar os repositórios remotos:

```powershell
git config submodule.sdk.url https://github.com/multitheftauto-modern/mtasa-sdk.git
git config submodule.vendor.url https://github.com/multitheftauto-modern/mtasa-vendors.git
git submodule sync
```
