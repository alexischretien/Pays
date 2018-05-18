#!/usr/bin/env bats

@test "Afficher format texte (format par defaut) sur Canada" {
    run ../bin/run --country can
    [ "${lines[0]}" = "Name: Canada" ]
    [ "${lines[1]}" = "Code: CAN" ]
    [ "${lines[2]}" = "------------------------------" ]
}

@test "Afficher format texte sur Canada" {
    run ../bin/run --output-format text --country can {
    [ "${lines[0]}" = "Name: Canada" ]
    [ "${lines[1]}" = "Code: CAN" ]
    [ "${lines[2]}" = "------------------------------" ]
}

@test "Afficher format texte sur Canada avec --show-capital" {
    run ../bin/run --country can --show-capital
    [ "${lines[0]}" = "Name: Canada" ]
    [ "${lines[1]}" = "Code: CAN" ]
    [ "${lines[2]}" = "Capital: Ottawa" ]
    [ "${lines[3]}" = "------------------------------" ]
}

@test "Afficher format texte sur Canada avec --show-languages" {
    run ../bin/run --country can --show-languages
    [ "${lines[0]}" = "Name: Canada" ]
    [ "${lines[1]}" = "Code: CAN" ]
    [ "${lines[2]}" = "Languages: English, French" ]
    [ "${lines[3]}" = "------------------------------" ]
}

@test "Afficher format texte sur Canada avec --show-borders" {
    run ../bin/run --country can --show-borders
    [ "${lines[0]}" = "Name: Canada" ]
    [ "${lines[1]}" = "Code: CAN" ]
    [ "${lines[2]}" = "Borders: USA" ] 
    [ "${lines[3]}" = "------------------------------" ]
}

@test "Afficher format texte sur Canada avec --show-capital --show-languages --show-borders" {
    run ../bin/run --country can --show-capital --show-languages --show-borders
    [ "${lines[0]}" = "Name: Canada" ]
    [ "${lines[1]}" = "Code: CAN" ]
    [ "${lines[2]}" = "Capital: Ottawa" ]
    [ "${lines[3]}" = "Languages: English, French" ]
    [ "${lines[4]}" = "Borders: USA" ]
    [ "${lines[5]}" = "------------------------------" ]
}

@test "Afficher format texte du premier pays du fichier JSON (Aruba)" {
    run ../bin/run --country abw --show-capital --show-languages --show-borders
    [ "${lines[0]}" = "Name: Aruba" ]
    [ "${lines[1]}" = "Code: ABW" ]
    [ "${lines[2]}" = "Capital: Oranjestad" ]
    [ "${lines[3]}" = "Languages: Dutch, Papiamento" ]
    [ "${lines[4]}" = "Borders:" ]
    [ "${lines[5]}" = "------------------------------" ]
}

@test "Afficher format texte du dernier pays du fichier JSON (Zimbabwe)" {
    run ../bin/run --country zwe --show-capital --show-languages --show-borders
    [ "${lines[0]}" = "Name: Zimbabwe" ]
    [ "${lines[1]}" = "Code: ZWE" ]
    [ "${lines[2]}" = "Capital: Harare" ]
    [ "${lines[3]}" = "Languages: Chewa, Chibarwe, English, Kalanga, Khoisan, Ndau, Northern Ndebele, Shona, Sotho, Tonga, Tsonga, Tswana, Venda, Xhosa, Zimbabwean Sign Language" ]
    [ "${lines[4]}" = "Borders: BWA MOZ ZAF ZMB" ]
    [ "${lines[5]}" = "------------------------------" ]
}

@test "La commande --country a priorite sur la commande --region" {
    run ../bin/run --region europe --country can --show-capital --show-languages --show-borders
    [ "${lines[0]}" = "Name: Canada" ]
    [ "${lines[1]}" = "Code: CAN" ]
    [ "${lines[2]}" = "Capital: Ottawa" ]
    [ "${lines[3]}" = "Languages: English, French" ]
    [ "${lines[4]}" = "Borders: USA" ]
    [ "${lines[5]}" = "------------------------------" ]
} 
