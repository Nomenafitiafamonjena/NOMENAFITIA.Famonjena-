#include "/home/mac/liat.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s [-c numero | -n numero] <nom-fichier>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *nom;
    int num = 10;

    if (strcmp(argv[1], "-c") == 0) {
        if (argc < 4) {
            fprintf(stderr, "Usage: %s -c numero <nom-fichier>\n", argv[0]);
            exit(EXIT_FAILURE);
        }
        num = atoi(argv[2]);
        nom = argv[3];
        tail(nom, num);
    } else if (strcmp(argv[1], "-n") == 0) {
        if (argc < 4) {
            fprintf(stderr, "Usage: %s -n numero <filename>\n", argv[0]);
            exit(EXIT_FAILURE);
        }
        num = atoi(argv[2]);
        nom = argv[3];
        tail_lignes(nom, num);
    } else {
        fprintf(stderr, "Unknown option: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    return 0;
}

void tail(const char *nom, int numero) {
    FILE *file = fopen(nom, "rb");
    if (!file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);

    if (numero > file_size) {
        numero = file_size;
    }

    fseek(file, -numero, SEEK_END);

    char buffer[1];
    while (fread(buffer, 1, 1, file)) {
        fwrite(buffer, 1, 1, stdout);
    }

    fclose(file);
}

void tail_lignes(const char *nom, int ligne) {
    FILE *file = fopen(nom, "r");
    if (!file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    char **lignes = malloc(ligne * sizeof(char *));
    for (int i = 0; i < ligne; i++) {
        lignes[i] = malloc(MAX* sizeof(char));
    }

    int count = 0;
    while (fgets(lignes[count % ligne], MAX, file)) {
        count++;
    }

    int start = count > ligne ? count % ligne : 0;
    int total_lines = count < ligne ? count : ligne;

    for (int i = 0; i < total_lines; i++) {
        printf("%s", lignes[(start + i) % ligne]);
    }

    for (int i = 0; i < ligne; i++) {
        free(lignes[i]);
    }
    free(lignes);

    fclose(file);
}


