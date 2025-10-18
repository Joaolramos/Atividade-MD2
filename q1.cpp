#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <limits>
#include <iomanip>     
#include <sstream>


typedef long long ll;

// ----------------------------------------------------------------------------
// FUNÇÕES AUXILIARES (Matematica Fundamental)
// ----------------------------------------------------------------------------

/**
 * @brief Calcula o Máximo Divisor Comum (MDC) usando o Algoritmo de Euclides
 * Implementação obrigatória (Etapa 1)
 * Exibe cada passo da iteração
 * @param a 1º número
 * @param b 2º número
 * @return O mdc(a, b)
 */
ll mdc(ll a, ll b) {
    std::cout << "    [Calculando mdc(" << a << ", " << b << ") via Algoritmo de Euclides]" << std::endl;
    ll original_a = a;
    ll original_b = b;
    ll temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
        std::cout << "      -> mdc(" << a << ", " << b << ")" << std::endl;
    }
    std::cout << "    [Resultado mdc(" << original_a << ", " << original_b << "): " << a << "]" << std::endl;
    return a;
}

/**
 * @brief Função de iteração g(x) para o método ρ de Pollard.
 * g(x) = (x^2 + 1) mod n
 * @param x O valor atual.
 * @param n O módulo.
 * @return O próximo valor na sequência.
 */
ll g(ll x, ll n) {
    return (x * x + 1) % n;
}

/**
 * @brief Estrutura para armazenar o resultado do Algoritmo Estendido de Euclides.
 * Armazena mdc(a, b), e os coeficientes x, y tais que ax + by = mdc(a, b).
 */
struct ResultadoEEA {
    ll mdc, x, y;
};

/**
 * @brief Implementa o Algoritmo Estendido de Euclides.
 * Implementação obrigatória (Etapa 2).
 * Exibe os passos da recursão.
 * @param a Primeiro número.
 * @param b Segundo número.
 * @return Um struct ResultadoEEA com {mdc, x, y}.
 */
ResultadoEEA euclidesEstendido(ll a, ll b) {
    std::cout << "    [EEA: Chamada com a=" << a << ", b=" << b << "]" << std::endl;
    if (a == 0) {
        // Caso base: mdc(0, b) = b. 0*x + b*y = b -> x=0, y=1
        std::cout << "    [EEA: Caso base. Retornando mdc=" << b << ", x=0, y=1]" << std::endl;
        return {b, 0, 1};
    }

    // Chamada recursiva
    std::cout << "    [EEA: Chamada recursiva com (b % a)=" << (b % a) << ", a=" << a << "]" << std::endl;
    ResultadoEEA res = euclidesEstendido(b % a, a);

    // Cálculo dos coeficientes no retorno da recursão
    ll x = res.y - (b / a) * res.x;
    ll y = res.x;

    std::cout << "    [EEA: Retornando de a=" << a << ", b=" << b << "]" << std::endl;
    std::cout << "      -> mdc=" << res.mdc << ", x=" << x << ", y=" << y << std::endl;
    return {res.mdc, x, y};
}

/**
 * @brief Calcula o inverso modular de e (mod z).
 * Usa o Algoritmo Estendido de Euclides.
 * Implementação obrigatória (Etapa 2).
 * @param e O número para o qual queremos o inverso (expoente público).
 * @param z O módulo (totiente z(n)).
 * @return O inverso modular d, tal que e*d ≡ 1 (mod z).
 */
ll inversoModular(ll e, ll z) {
    std::cout << "\nCalculando Expoente Privado D: (D * " << e << ") = 1 (mod " << z << ")" << std::endl;
    ResultadoEEA res = euclidesEstendido(e, z);

    if (res.mdc != 1) {
        // Isso não deve acontecer se 'e' foi escolhido corretamente
        std::cout << "ERRO FATAL: Inverso modular nao existe. mdc(" << e << ", " << z << ") = " << res.mdc << std::endl;
        return -1;
    }

    // O coeficiente 'x' (res.x) é o inverso.
    // Ele pode ser negativo, então normalizamos para o intervalo [0, z-1].
    // A fórmula (x % z + z) % z trata tanto x positivo quanto negativo.
    ll d = (res.x % z + z) % z;
    
    std::cout << "  Resultado do EEA: x (inverso) = " << res.x << std::endl;
    std::cout << "  Normalizando D: (" << res.x << " % " << z << " + " << z << ") % " << z << " = " << d << std::endl;
    return d;
}


/**
 * @brief Realiza a exponenciação modular (base^exp) % mod.
 * Usa o método de "quadrados e multiplicações" (square-and-multiply).
 * Esta é a implementação base.
 * Exibe o passo-a-passo do cálculo.
 * @param base A base da potência.
 * @param exp O expoente.
 * @param mod O módulo.
 * @return O resultado de (base^exp) % mod.
 */
ll exponenciacaoModularBase(ll base, ll exp, ll mod) {
    ll res = 1;
    base %= mod; // Reduz a base inicial

    std::cout << "    [Iniciando exponenciacao modular: " << base << "^" << exp << " % " << mod << "]" << std::endl;

    while (exp > 0) {
        // Se o expoente é ímpar, multiplica o resultado pela base atual
        if (exp % 2 == 1) {
            res = (res * base) % mod;
            std::cout << "    -> exp e impar (" << exp << "). res = (res * base) % mod = " << res << std::endl;
        }

        // Eleva a base ao quadrado (para a próxima potência de 2)
        base = (base * base) % mod;
        // Divide o expoente por 2 (deslocamento de bit)
        exp /= 2;

        if (exp > 0) {
            std::cout << "    -> Quadrando a base: base = (base^2) % mod = " << base << ". Novo exp = " << exp << std::endl;
        }
    }
    std::cout << "    [Resultado final da exponenciacao: " << res << "]" << std::endl;
    return res;
}

/**
 * @brief Verifica (de forma simples) se um número é primo.
 * Usado para a seleção de teorema na Etapa 3.
 */
bool ehPrimo(ll n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    // Verifica fatores da forma 6k ± 1
    for (ll i = 5; i * i <= n; i = i + 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}


/**
 * @brief
 * @param base
 * @param exp
 * @param n
 * @param z_n
 * @return 
 */
ll exponenciacaoModularInteligente(ll base, ll exp, ll n, ll z_n) {
    std::cout << "\nCalculando (" << base << "^" << exp << ") % " << n << std::endl;
    std::cout << "  Verificando condicoes para reducao de expoente..." << std::endl;
    
    ll exp_reduzido = exp;

    // 1. Verifica Teorema de Fermat
    // (Atenção: No RSA, 'n' NUNCA é primo, mas o requisito pede a verificação)
    if (ehPrimo(n)) {
        std::cout << "  Condicao: Modulo 'n' (" << n << ") E PRIMO." << std::endl;
        std::cout << "  Aplicando Pequeno Teorema de Fermat." << std::endl;
        exp_reduzido = exp % (n - 1);
        std::cout << "  Expoente " << exp << " reduzido para " << exp_reduzido << " = (" << exp << " % " << (n - 1) << ")" << std::endl;
    } 
    // Se n não é primo (caso padrão do RSA)
    else {
        std::cout << "  Condicao: Modulo 'n' (" << n << ") e COMPOSTO." << std::endl;
        
        // Criamos um 'mdc' silencioso aqui só para a verificação,
        // pois a função 'mdc' principal imprime muitos passos.
        ll a_temp = base, b_temp = n, temp;
        while (b_temp != 0) { temp = b_temp; b_temp = a_temp % b_temp; a_temp = temp; }
        ll mdc_base_n = a_temp;

        // 2. Verifica Teorema de Euler
        if (mdc_base_n == 1) {
            std::cout << "  Condicao: mdc(base=" << base << ", n=" << n << ") = 1." << std::endl;
            std::cout << "  Aplicando Teorema de Euler." << std::endl;
            exp_reduzido = exp % z_n;
            std::cout << "  Expoente " << exp << " reduzido para " << exp_reduzido << " = (" << exp << " % z(n)=" << z_n << ")" << std::endl;
        } 
        // 3. Fallback (Divisão Euclidiana)
        else {
            std::cout << "  Condicao: mdc(base=" << base << ", n=" << n << ") = " << mdc_base_n << " (diferente de 1)." << std::endl;
            std::cout << "  Aplicando Teorema da Divisao Euclidiana (calculo direto)." << std::endl;
            std::cout << "  (Nao foi possivel aplicar Euler para reducao do expoente)." << std::endl;
            // O expoente não é reduzido, usamos o original.
            exp_reduzido = exp;
        }
    }

    // Chama a função base de exponenciação com o expoente (possivelmente) reduzido
    return exponenciacaoModularBase(base, exp_reduzido, n);
}


// ----------------------------------------------------------------------------
// ETAPA 1: FATORAÇÃO (MÉTODO ρ DE POLLARD)
// ----------------------------------------------------------------------------

/**
 * @brief Encontra um fator primo de N usando o método ρ de Pollard (com semente inicial).
 * Implementação obrigatória (Etapa 1).
 * Usa o algoritmo de detecção de ciclo de Floyd (tartaruga e lebre).
 * Exibe cada passo da iteração.
 * @param n O número composto a ser fatorado.
 * @param seed A semente inicial (x0).
 * @return Um fator primo de n.
 */
ll pollardRho(ll n, ll seed = 2) {
    std::cout << "\nIniciando Metodo rho de Pollard para N = " << n << " (semente x0=" << seed << ")" << std::endl;
    
    if (n == 1) return 1;
    if (n % 2 == 0) {
        std::cout << "  Fator trivial encontrado (par): 2" << std::endl;
        return 2;
    }

    ll x = seed; // Tartaruga
    ll y = seed; // Lebre
    ll d = 1;
    int iter = 0;

    std::cout << "  Iter " << iter << ": x=" << x << ", y=" << y << ", d=1" << std::endl;

    while (d == 1) {
        iter++;
        // Tartaruga: x = g(x)
        x = g(x, n);
        // Lebre: y = g(g(y))
        y = g(g(y, n), n);
        
        // Calcula a diferença absoluta
        ll diff = std::abs(x - y);
        std::cout << "  Iter " << iter << ": x=" << x << ", y=" << y << ", |x-y|=" << diff << std::endl;
        
        // Calcula o mdc(diff, n)
        d = mdc(diff, n);

        // Caso de falha: o ciclo encontrou n.
        // Isso significa que a função g(x) e/ou a semente falharam.
        // Recomeçamos com uma semente diferente (seed + 1).
        if (d == n) {
            std::cout << "  Falha (d=N). O ciclo encontrou N. Reiniciando com semente " << (seed + 1) << "..." << std::endl;
            return pollardRho(n, seed + 1);
        }
    }

    std::cout << "Fator nao trivial encontrado: " << d << std::endl;
    return d;
}

// ----------------------------------------------------------------------------
// ETAPA 3: PRÉ-CODIFICAÇÃO
// ----------------------------------------------------------------------------

// Mapas para converter entre caracteres e códigos numéricos
std::map<char, std::string> char_para_codigo;
std::map<std::string, char> codigo_para_char;

/**
 * @brief Inicializa os mapas de pré-codificação.
 * A=11, ..., Z=36, Espaço=00
 */
void inicializarMapas() {
    char_para_codigo[' '] = "00";
    codigo_para_char["00"] = ' ';
    for (int i = 0; i < 26; i++) {
        std::string codigo = std::to_string(i + 11);
        char c = 'A' + i;
        char_para_codigo[c] = codigo;
        codigo_para_char[codigo] = c;
    }
}

/**
 * @brief Converte uma mensagem de texto em uma string numérica.
 * @param texto A mensagem original.
 * @return A string de códigos (ex: "OLA" -> "252211").
 */
std::string preCodificar(std::string texto) {
    std::string codificado = "";
    for (char c : texto) {
        c = toupper(c); // Converte para maiúscula
        if (char_para_codigo.count(c)) {
            codificado += char_para_codigo[c];
        } else {
            // Se for um caractere inválido (pontuação, etc.), trata como espaço
            codificado += "00"; 
        }
    }
    return codificado;
}

/**
 * @brief Reconverte uma string numérica em texto.
 * @param codigos A string de códigos (ex: "252211").
 * @return A mensagem decifrada (ex: "OLA").
 */
std::string posDecodificar(std::string codigos) {
    std::string texto = "";
    // Processa a string de 2 em 2 caracteres (blocos)
    for (size_t i = 0; i < codigos.length(); i += 2) {
        std::string bloco = codigos.substr(i, 2);
        if (codigo_para_char.count(bloco)) {
            texto += codigo_para_char[bloco];
        } else {
            texto += '?'; // Indica um bloco desconhecido/inválido
        }
    }
    return texto;
}

/**
 * @brief Função auxiliar para ler um número N com validação de intervalo.
 */
ll lerN(std::string prompt) {
    ll N;
    while (true) {
        std::cout << prompt;
        if (std::cin >> N && N >= 100 && N <= 9999) {
            // Limpa o buffer de entrada (remove o '\n')
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return N;
        } else {
            std::cout << "Entrada invalida. Digite um numero entre 100 e 9999." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}


// ----------------------------------------------------------------------------
// FUNÇÃO PRINCIPAL (main)
// ----------------------------------------------------------------------------

int main() {
    // Inicializa o sistema de codificação A=11, B=12...
    inicializarMapas();

    std::cout << "==========================================" << std::endl;
    std::cout << " IMPLEMENTACAO DO SISTEMA RSA COMPLETO" << std::endl;
    std::cout << "==========================================" << std::endl;

    // ----------------------------------------------------
    // ETAPA 1: FATORAÇÃO
    // ----------------------------------------------------
    std::cout << "\n--- ETAPA 1: FATORACAO (rho de Pollard) ---" << std::endl;
    std::cout << "Cada Ni deve ser produto de primos distintos (ex: 1147 = 31*37)." << std::endl;
    
    ll N1 = lerN("Digite o primeiro numero composto N1 (100-9999): ");
    ll N2 = lerN("Digite o segundo numero composto N2 (100-9999): ");

    // Fatora N1 para encontrar p
    ll p = pollardRho(N1);
    // Fatora N2 para encontrar q
    ll q = pollardRho(N2);

    std::cout << "\n------------------------------------------" << std::endl;
    std::cout << "Fatores Primos RSA Definidos:" << std::endl;
    std::cout << "  p (de N1=" << N1 << ") = " << p << std::endl;
    std::cout << "  q (de N2=" << N2 << ") = " << q << std::endl;

    // ----------------------------------------------------
    // ETAPA 2: GERAÇÃO DAS CHAVES
    // ----------------------------------------------------
    std::cout << "\n--- ETAPA 2: GERACAO DAS CHAVES RSA ---" << std::endl;

    // Cálculo do módulo n
    ll n = p * q;
    std::cout << "Modulo (n = p * q): " << n << std::endl;

    // Cálculo do Totiente de Euler z(n)
    ll z_n = (p - 1) * (q - 1);
    std::cout << "Totiente (z(n) = (p-1)*(q-1)): " << z_n << std::endl;

    // Escolha do expoente público E
    ll e = 2;
    std::cout << "Escolhendo expoente publico E (menor E > 1 tal que mdc(E, z(n))=1)..." << std::endl;
    while (e < z_n) {
        if (mdc(e, z_n) == 1) {
            std::cout << "Expoente publico E encontrado: " << e << std::endl;
            break;
        }
        e++;
    }
    if (e == z_n) {
        std::cout << "ERRO: Nao foi possivel encontrar 'e'. Tente outros p e q." << std::endl;
        return 1;
    }

    // Cálculo do expoente privado D
    ll d = inversoModular(e, z_n);
    if (d == -1) {
        return 1; // Erro já reportado pela função
    }
    std::cout << "Expoente privado D encontrado: " << d << std::endl;

    // Impressão das chaves
    std::cout << "\n------------------------------------------" << std::endl;
    std::cout << "CHAVES RSA GERADAS:" << std::endl;
    std::cout << "  Chave Publica (n, e): (" << n << ", " << e << ")" << std::endl;
    std::cout << "  Chave Privada (n, d): (" << n << ", " << d << ")" << std::endl;
    std::cout << "------------------------------------------" << std::endl;

    // ----------------------------------------------------
    // ETAPA 3: CODIFICAÇÃO E DECODIFICAÇÃO
    // ----------------------------------------------------
    std::cout << "\n--- ETAPA 3: CRIPTOGRAFIA E DESCRIPTOGRAFIA ---" << std::endl;
    
    // Leitura da mensagem
    std::string mensagem;
    std::cout << "Digite a mensagem para criptografar (A-Z, espaco): ";
    std::getline(std::cin, mensagem);

    // Pré-codificação
    std::string mensagem_codificada = preCodificar(mensagem);
    std::cout << "Mensagem Original: \"" << mensagem << "\"" << std::endl;
    std::cout << "Mensagem Pre-Codificada (A=11..Z=36, Esp=00): " << mensagem_codificada << std::endl;

    // --- CODIFICAÇÃO (CRIPTOGRAFIA) ---
    std::cout << "\n--- Processo de Criptografia (C = M^e % n) ---" << std::endl;
    std::vector<ll> blocos_cifrados;
    std::string visualizacao_cifrada = "";

    // Processa a mensagem em blocos de 2 dígitos
    for (size_t i = 0; i < mensagem_codificada.length(); i += 2) {
        std::string bloco_str = mensagem_codificada.substr(i, 2);
        ll M = std::stoll(bloco_str); // Converte string "XX" para número XX

        std::cout << "Codificando bloco '" << bloco_str << "' (M=" << M << "):" << std::endl;
        // C = M^e (mod n)
        ll C = exponenciacaoModularInteligente(M, e, n, z_n);
        
        blocos_cifrados.push_back(C);
        visualizacao_cifrada += std::to_string(C) + " ";
    }
    std::cout << "\nMensagem Cifrada (blocos): " << visualizacao_cifrada << std::endl;


    // --- DECODIFICAÇÃO (DESCRIPTOGRAFIA) ---
    std::cout << "\n--- Processo de Descriptografia (M = C^d % n) ---" << std::endl;
    std::string blocos_decifrados_str = "";

    for (ll C : blocos_cifrados) {
        std::cout << "Decodificando bloco (C=" << C << "):" << std::endl;
        // M = C^d (mod n)
        ll M_decifrado = exponenciacaoModularInteligente(C, d, n, z_n);

        // Formata o número M de volta para 2 dígitos (ex: 5 -> "05")
        std::stringstream ss;
        ss << std::setw(2) << std::setfill('0') << M_decifrado;
        std::string bloco_decifrado_str = ss.str();

        blocos_decifrados_str += bloco_decifrado_str;
    }

    std::cout << "\nBlocos Decifrados (numerico): " << blocos_decifrados_str << std::endl;

    // Pós-decodificação
    std::string mensagem_decifrada = posDecodificar(blocos_decifrados_str);
    std::cout << "Mensagem Pos-Decodificada (texto): \"" << mensagem_decifrada << "\"" << std::endl;


    // --- VERIFICAÇÃO FINAL ---
    std::cout << "\n--- Verificacao Final ---" << std::endl;
    std::cout << "Mensagem Original.....: \"" << mensagem << "\"" << std::endl;
    std::cout << "Mensagem Decifrada....: \"" << mensagem_decifrada << "\"" << std::endl;

    // Comparamos as strings após a pré-codificação e pós-decodificação
    // para ignorar problemas de maiúsculas/minúsculas da entrada.
    if (mensagem_codificada == blocos_decifrados_str) {
        std::cout << "\nSUCESSO: A mensagem decifrada e identica a original!" << std::endl;
    } else {
        std::cout << "\nFALHA: As mensagens sao diferentes." << std::endl;
        std::cout << "Original (pre-cod): " << mensagem_codificada << std::endl;
        std::cout << "Decifrada (pos-cod): " << blocos_decifrados_str << std::endl;
    }

    return 0;
}