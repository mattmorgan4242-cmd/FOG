# Falling Objects Game

Skrypt należy uruchomić w terminalu obsługującym pliki .sh, np. Git Bash lub MSYS2.

## Jak uruchomić:

1. Zainstaluj Git, CMake oraz kompilator C++
2. Otwórz terminal
3. Pobierz repozytorium

    ```bash
    git clone https://github.com/mattmorgan4242-cmd/FOG
    ```

4. Przejdź do folderu z projektem

    ```bash
    cd FOG
    ```

5. Pobierz wymagane biblioteki

    ```bash
    git submodule update --init --depth 1
    ```

6. Uruchom projekt

   ```bash
    ./run.sh
   ```

Gra zostanie automatycznie skompilowana i uruchomiona.

## Sterowanie

← – ruch w lewo
→ – ruch w prawo