#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

typedef long long ll;
typedef unsigned long long ull;

/* ------------------------------------------------------------
   Funções utilitárias
------------------------------------------------------------ */

/* Algoritmo de Euclides */
ll gcd_ll(ll a, ll b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b != 0) {
        ll t = b;
        b = a % b;
        a = t;
    }
    return a;
}

/* Algoritmo de Euclides Estendido:
   retorna gcd(a,b) e preenche x,y tais que a*x + b*y = gcd */
ll extended_gcd(ll a, ll b, ll *x, ll *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    ll x1, y1;
    ll g = extended_gcd(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return g;
}

/* Inverso modular de a mod m (retorna -1 se não existir) */
ll modinv(ll a, ll m) {
    ll x, y;
    ll g = extended_gcd(a, m, &x, &y);
    if (g != 1) return -1;
    ll res = x % m;
    if (res < 0) res += m;
    return res;
}

/* Exponenciação modular rápida (por quadrados sucessivos) */
ull powmod(ull base, ull exp, ull mod) {
    ull res = 1 % mod;
    ull b = base % mod;
    while (exp > 0) {
        if (exp & 1ULL) res = ((__uint128_t)res * b) % mod;
        b = ((__uint128_t)b * b) % mod;
        exp >>= 1;
    }
    return res;
}

/* Teste de primalidade simples (trial division) */
int is_prime(ull n) {
    if (n < 2) return 0;
    if (n % 2 == 0) return (n == 2);
    ull r = sqrt((double)n);
    for (ull i = 3; i <= r; i += 2)
        if (n % i == 0) return 0;
    return 1;
}

/* Função totiente de Euler φ(n) por fatoração simples */
ull phi_from_n(ull n) {
    ull result = n, temp = n;
    for (ull p = 2; p * p <= temp; ++p) {
        if (temp % p == 0) {
            while (temp % p == 0) temp /= p;
            result = result / p * (p - 1);
        }
    }
    if (temp > 1) result = result / temp * (temp - 1);
    return result;
}

/* ------------------------------------------------------------
   (a) Implementação funcional
------------------------------------------------------------ */
int main() {
    printf("=== QUESTAO 04 (Bônus) ===\n");

    ll H, G, Zn;
    printf("\nEntre com H, G e Zn (para divisao modular H ÷ G mod Zn): ");
    if (scanf("%lld %lld %lld", &H, &G, &Zn) != 3) {
        printf("Entrada invalida.\n");
        return 0;
    }

    printf("\n-- Divisao Modular --\n");
    printf("H = %lld, G = %lld, Zn = %lld\n", H, G, Zn);

    ll g = gcd_ll(G, Zn);
    printf("mdc(G, Zn) = %lld\n", g);

    if (g != 1) {
        printf("Nao existe inverso modular de G em Zn (gcd != 1).\n");
    } else {
        ll inv = modinv(G, Zn);
        printf("Inverso modular de G mod Zn = %lld\n", inv);
        if (inv < 0) {
            printf("Inverso negativo, ajustando: inv + Zn = %lld\n", inv + Zn);
            inv = (inv + Zn) % Zn;
        }
        ll result = ((H % Zn) * (inv % Zn)) % Zn;
        printf("Resultado: (H * inv) mod Zn = %lld\n", result);
    }

    /* Cálculo de a^x mod n1 */
    ll a, x, n1;
    printf("\nEntre com a, x e n1 (para calcular a^x mod n1): ");
    if (scanf("%lld %lld %lld", &a, &x, &n1) != 3) {
        printf("Entrada invalida.\n");
        return 0;
    }

    printf("\n-- Potencia Modular --\n");
    printf("a = %lld, x = %lld, n1 = %lld\n", a, x, n1);

    if (is_prime((ull)n1)) {
        printf("n1 eh primo -> Pequeno Teorema de Fermat (reduz expoente mod n1-1)\n");
        ull reduced = (ull)(x % (n1 - 1));
        printf("x mod (n1-1) = %llu\n", reduced);
        ull res = powmod((ull)a, reduced, (ull)n1);
        printf("Resultado a^x mod n1 = %llu\n", res);
    } else {
        ull g2 = gcd_ll(a, n1);
        if (g2 == 1) {
            ull phi = phi_from_n((ull)n1);
            printf("mdc(a,n1)=1 -> Teorema de Euler com phi(n1)=%llu\n", phi);
            ull reduced = (ull)(x % phi);
            ull res = powmod((ull)a, reduced, (ull)n1);
            printf("Resultado a^x mod n1 = %llu\n", res);
        } else {
            printf("mdc(a,n1)!=1 -> exponenciacao direta\n");
            ull res = powmod((ull)a, (ull)x, (ull)n1);
            printf("Resultado a^x mod n1 = %llu\n", res);
        }
    }

    /* Exemplo do enunciado */
    printf("\n-- Exemplo do Enunciado --\n");
    ll H_ex = 7, G_ex = 3, Zn_ex = 11, x_ex = 10, n1_ex = 13, a_ex = 2;

    printf("Valores: H=%lld, G=%lld, Zn=%lld, a=%lld, x=%lld, n1=%lld\n",
           H_ex, G_ex, Zn_ex, a_ex, x_ex, n1_ex);

    ll inv_ex = modinv(G_ex, Zn_ex);
    ll divmod = ((H_ex % Zn_ex) * (inv_ex % Zn_ex)) % Zn_ex;
    printf("Divisao modular (H*inv) mod Zn = %lld\n", divmod);

    ull reduced = (ull)(x_ex % (n1_ex - 1));
    ull res_ex = powmod((ull)a_ex, reduced, (ull)n1_ex);
    printf("a^x mod n1 (Fermat) = %llu\n", res_ex);

    printf("\nFim da parte (a).\n");

    return 0;
}

/* ------------------------------------------------------------
   (b) Parte teórica – Verdadeiro (V) ou Falso (F)
------------------------------------------------------------

1) O algoritmo de Euclides estendido é utilizado para calcular o inverso modular de um número.   V
2) Se mdc(G, Zn) ≠ 1, o programa ainda consegue encontrar o inverso de G em Zn.                   F
3) A operação (H * inverso) % Zn representa a divisão modular de H por G.                         V
4) Se n1 for primo, o código aplica o Pequeno Teorema de Fermat para simplificar a^x mod n1.      V
5) A função powMod implementa o cálculo de potência modular utilizando multiplicações diretas
   sem otimização.                                                                                F
6) Quando o resultado do inverso é negativo, o código ajusta o valor somando o módulo m0.         V
7) O cálculo de φ(n1) (totiente de Euler) é utilizado apenas quando n1 não é primo.               V
------------------------------------------------------------ */
