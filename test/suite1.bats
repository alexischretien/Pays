#!/usr/bin/env bats
@test "Format de sortie invalide" {
    run ../bin/run --output-format jpeg
    [ "$output" = "Erreur. Format de sortie \"jpeg\" invalide." ]
}

@test "Nom de fichier manquant pour format \"png\"" {
    run ../bin/run --output-format png
    [ "$output" = "Erreur. Le format \"png\" requiere un nom de fichier." ]
}

@test "Extension du fichier \"txt\" manquant" {
    run ../bin/run --output-format text --output-filename fichier
    [ "$output" = "Erreur. Extension \".txt\" du fichier manquant." ]
}

@test "Extension du fichier \"txt\" manquant (format par defaut)" {
    run ../bin/run --output-filename fichier
    [ "$output" = "Erreur. Extension \".txt\" du fichier manquant." ]
}

@test "Extension du fichier \"dot\" manquant" {
    run ../bin/run --output-format dot --output-filename fichier
    [ "$output" = "Erreur. Extension \".dot\" du fichier manquant." ]
}

@test "Extension du fichier \"png\" manquant" {
    run ../bin/run --output-format png --output-filename fichier
    [ "$output" = "Erreur. Extension \".png\" du fichier manquant." ]
}

@test "Mauvaise extension du fichier de format \"txt\"" {
    run ../bin/run --output-format text --output-filename fichier.dot
    [ "$output" = "Erreur. L'extension du fichier devrait etre \".txt\"." ]
}

@test "Mauvaise extension du fichier de format \"txt\" (format par defaut)" {
    run ../bin/run --output-filename fichier.png
    [ "$output" = "Erreur. L'extension du fichier devrait etre \".txt\"." ]
}

@test "Mauvaise extension du fichier de format \"dot\"" {
    run ../bin/run --output-format dot --output-filename fichier.txt
    [ "$output" = "Erreur. L'extension du fichier devrait etre \".dot\"." ]
}

@test "Mauvaise extension du fichier de format \"png\"" {
    run ../bin/run --output-format png --output-filename fichier.dot
    [ "$output" = "Erreur. L'extension du fichier devrait etre \".png\"." ]
}

@test "Le nom du fichier contient plus qu'un point" {
    run ../bin/run --output-filename fichier.txt.txt
    [ "$output" = "Erreur. Le nom du fichier ne doit contenir qu'un seul point." ]
}

@test "Le nom du fichier contient un caractere plus petit que ASCII 48 - cas limite" {
    run ../bin/run --output-filename /fichier.txt
    [ "$output" = "Erreur. Le caractere '/' est illegal pour le nom du fichier." ]
}

@test "Le nom du fichier contient un caractere plus petit que ASCII 48 - cas general" {
    run ../bin/run --output-filename f+ichier.txt
    [ "$output" = "Erreur. Le caractere '+' est illegal pour le nom du fichier." ]
}

@test "Le nom du fichier contient un caractere plus grand que ASCII 57 et plus petit que ASCII 65 - cas limite de la borne minimale" {
    run ../bin/run --output-filename fi:chier.txt
    [ "$output" = "Erreur. Le caractere ':' est illegal pour le nom du fichier." ]
}

@test "Le nom du fichier contient un caractere plus grand que ASCII 57 et plus petit que ASCII 65 - cas limite de la borne maximale" {
    run ../bin/run --output-filename fic@hier.txt
    [ "$output" = "Erreur. Le caractere '@' est illegal pour le nom du fichier." ]
}

@test "Le nom du fichier contient un caractere plus grand que ASCII 57 et plus petit que ASCII 65 - cas general" {
    run ../bin/run --output-filename fich?ier.txt
    [ "$output" = "Erreur. Le caractere '?' est illegal pour le nom du fichier." ]
}

@test "Le nom du fichier contient un caractere plus grand que ASCII 90 et plus petit que ASCII 97 - cas limite de la borne minimale" {
    run ../bin/run --output-filename fichi[er.txt
    [ "$output" = "Erreur. Le caractere '[' est illegal pour le nom du fichier." ]
}

@test "Le nom du fichier contient un caractere plus grand que ASCII 90 et plus petit que ASCII 97 - cas limite de la borne maximale" {
    run ../bin/run --output-filename fichie\`r.txt
    [ "$output" = "Erreur. Le caractere '\`' est illegal pour le nom du fichier." ]
}

@test "Le nom du fichier contient un caractere plus grand que ASCII 90 et plus petit que ASCII 97 - cas general" {
    run ../bin/run --output-filename fichier^.txt
    [ "$output" = "Erreur. Le caractere '^' est illegal pour le nom du fichier." ]
}

@test "Le nom du fichier contient un caractere plus grand que ASCII 122 - cas limite" {
    run ../bin/run --output-filename fic{hier.txt
    [ "$output" = "Erreur. Le caractere '{' est illegal pour le nom du fichier." ]
}

@test "Le nom du fichier contient un caractere plus grand que ASCII 122 - cas general" {
    run ../bin/run --output-filename fic~hier.txt
    [ "$output" = "Erreur. Le caractere '~' est illegal pour le nom du fichier." ]
}

@test "Le pays demande n'existe pas"  {
    run ../bin/run --country codeBidon
    [ "$output" = "Erreur. La recherche ne retourne aucun pays." ]
}

@test "La region demande n'existe pas" {
    run ../bin/run --region regionBidon
    [ "$output" = "Erreur. La recherche ne retourne aucun pays." ]
}
